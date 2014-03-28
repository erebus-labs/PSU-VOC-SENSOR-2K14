#*************************************************************************************************
#
#     File Name: communication.py
#       Project: Erebus Labs Sensor
# Revision Date: 03/26/2014
#   Description: This file handles serial communications for the Erebus Labs sensor user interface
#
#*************************************************************************************************

import serial
import struct
import sys
import os
import os.path
from glob import glob
#import serialenum

# Global Table of Symbols

COMMANDS = {
  'IDENTIFY':b'I',
  'DUMP_DATA':b'D',
  'CHANGE_SETTINGS':b'C'
  }

RESPONSES = {
  'SUCCESS'   :b'Y',
  'FAIL'      :b'N',
  'IDENTIFIER':b'E'
  }

COMMAND_SIZE = 5 # number of bytes in each command

def scan_ports():
#  connected = []
#  for i in range(256):
#      try:
#          handle = serial.Serial(i)
#          s.close()
#          yield i
#      except serial.SerialException:
#          pass
#
#  return
  ports = []

  if os.path.exists('/dev/serial/by-id'):
      entries = os.listdir('/dev/serial/by-id')
      dirs = [os.readlink(os.path.join('/dev/serial/by-id', x))
              for x in entries]
      ports.extend([os.path.normpath(os.path.join('/dev/serial/by-id', x))
                   for x in dirs])
  print("List: {}".format(ports))
  for dev in glob('/dev/tty.*'):
      print("\n{}".format(dev))
      try:
          port = Serial(dev)
      except:
          pass
      else:
          ports.append(dev)

  return ports

def pack(command, target=0, value=0):

  request = struct.pack('<chh', command, target, value)


  return request

def acquire_sensor():
  """Determines which COM port the Erebus Sensor is connected to and returns the serial handle

  Inputs: None

  Outputs: 
    Name      Type    Purpose
    handle    Serial  handle to Erebus Labs serial port connection
                      If serial communication cannot be established, None is returned
  """
  status = 0


  request_identifier = pack(COMMANDS['IDENTIFY'])

  for port in scan_ports():


    try:
      
      print("\nTrying Port: {}".format(port))
      handle = serial.Serial(port,
                             baudrate=115200, 
                             bytesize=serial.EIGHTBITS,
                             parity=serial.PARITY_EVEN,
                             xonxoff=0,
                             rtscts=0,
                             stopbits=serial.STOPBITS_ONE)

      print("\nSending: {}".format(request_identifier))
      handle.write(request_identifier)

      response = handle.read(1)
      print("\nReply: {}".format(response))

      if response == RESPONSES['IDENTIFIER']:
        status = 1
        break

    except serial.SerialException:
      continue



  if status:
    return handle
  else:
    return None

def main():
  sensor_handle = acquire_sensor()
  if sensor_handle != None:
    print('\nSuccess')

  else:
    print('\nFailure')

  return

if __name__ == "__main__":
  main()
    
