#*************************************************************************************************
#
#     File Name: erebus_sensor.py
#       Project: Erebus Labs Sensor
# Revision Date: 03/27/2014
#   Description: This file defines the ErebusSensor class
#
#*************************************************************************************************

import serial
import struct
import sys
import os
from glob import glob

class ErebusSensor:

  def __init__(self):
    """Determines which COM port the Erebus Sensor is connected to and returns the serial handle

    Inputs: None

    Outputs: 
      Name      Type    Purpose
      handle    Serial  handle to Erebus Labs serial port connection
                        If serial communication cannot be established, None is returned
    """

    acquired = 0

    self.command_size = 5 # number of bytes in each command

    self.commands = {
      'IDENTIFY'       :b'I',
      'DUMP_DATA'      :b'D',
      'CHANGE_SETTINGS':b'C',
      'NEXT'           :b'X',
      'SUCCESS'        :b'Y',
      'FAILURE'        :b'N'}

    self.responses = {
      'SUCCESS'   :b'Y',
      'FAIL'      :b'N',
      'IDENTIFIER':b'E'}

    self.settings = {
      'BLINK_RATE':0}

    for port in self.scan_ports():

      try:
        
        self.handle = serial.Serial(port,
                                    baudrate=115200, 
                                    bytesize=serial.EIGHTBITS,
                                    parity=serial.PARITY_EVEN,
                                    xonxoff=0,
                                    rtscts=0,
                                    stopbits=serial.STOPBITS_ONE,
                                    timeout=3)

        self.send_command('IDENTIFY')

        response = self.handle.read(1)

        if response == self.responses['IDENTIFIER']:
          acquired = 1
          break
      
      except serial.SerialException:
          continue

    if not acquired:
      self.handle = None

  def scan_ports(self):

    ports = []

    if os.path.exists('/dev/serial/by-id'):
        entries = os.listdir('/dev/serial/by-id')
        dirs = [os.readlink(os.path.join('/dev/serial/by-id', x))
                for x in entries]
        ports.extend([os.path.normpath(os.path.join('/dev/serial/by-id', x))
                     for x in dirs])

    return ports

  def send_command(self, command, target=0, value=0):

    out = struct.pack('>chh', self.commands[command], target, value)
    self.handle.write(out)
    return 

  def is_connected(self):
    if self.handle != None:
      return self.handle.isOpen()
    else:
      return False


  def get_data(self):
    if not self.is_connected():
      return None

    data = []
    points_sent = 0
    packet_format_string = '>'+'h'*32
    points_received = -1

    try:
      self.send_command('DUMP_DATA')
    except OSError:
      return -1

    for x in range(3):
    
      while True:
        package = self.handle.read(64)
        packet = struct.unpack(packet_format_string, package)

        for word in packet:
          if not word & 0xF000:
            data.append(word)
            points_sent += 1

          elif word & 0x4000:
            continue

          elif word & 0x8000:
            points_received = packet[1]
            break

        if points_received >= 0:
          break

      if points_received == points_sent:
        self.send_command('SUCCESS')
        result = 1
      else:
        self.send_command('FAIL')
        result = 0

      if result == 1:
        break
      else:
        try:
          self.send_command('DUMP_DATA')
        except OSError:
          return -1
      
    if result:    
      return data
    else:
      return None

  def request_id(self):
    try:
      self.send_command('IDENTIFY')
    except OSError:
      return -1
    return self.handle.read(1)

  def change_setting(self, setting, new_value):
    status = 0
    try:
      self.send_command('CHANGE_SETTINGS', self.settings[setting], new_value)
    except OSError:
      status = -1

    if self.handle.read(1) == self.responses['SUCCESS']:
      status = 1

    return status

