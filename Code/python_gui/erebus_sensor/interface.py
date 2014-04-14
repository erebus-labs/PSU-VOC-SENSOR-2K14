#*************************************************************************************************
#
#     File Name: interface.py
#       Project: Erebus Labs Sensor
# Revision Date: 04/13/2014
#   Description: This file defines the ErebusSensor class
#
#*************************************************************************************************

import serial
import struct
import sys
import os
from glob import glob

# Module Level Variables
sensorOptions = ('Light Sensor', 'Temperature Sensor')
unitOptions = ('Seconds', 'Minutes', 'Hours', 'Days')
maxInterval = pow(2, 16)

settings = {
    'SAMPLE_UNIT'     :0x01.to_bytes(1,byteorder='big'),
    'SAMPLE_INTERVAL' :0x02.to_bytes(1,byteorder='big'),
    'SENSOR'          :0x03.to_bytes(1,byteorder='big')}
  

class Settings:
    def __init__(self, sensor=sensorOptions[0], unit=unitOptions[0], interval=1):
        self.SENSOR = sensor
        self.SAMPLE_UNIT = unit
        self.SAMPLE_INTERVAL = interval

    def extractDiff(self, other):

        diffDict = {}

        for member in iter(settings):
            if getattr(self, member) != getattr(other, member):
                diffDict[member] = getattr(other, member)

        return diffDict

class DataDump:
    def __init__(self, startTime, sensor, sampleUnit, sampleInterval, samples):
        self.startTime = startTime
        self.sensor = sensor
        self.sampleUnit = sampleUnit
        self.sampleInterval = sampleInterval
        self.samples = samples

        return

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
            'IDENTIFY'        :0x01.to_bytes(1,byteorder='big'),
            'DUMP_DATA'       :0x02.to_bytes(1,byteorder='big'),
            'GET_SETTINGS'    :0x03.to_bytes(1,byteorder='big'),
            'CHANGE_SETTING'  :0x04.to_bytes(1,byteorder='big'),
            'HARD_RESET'      :0x05.to_bytes(1,byteorder='big')}
  
        self.responses = {
            'IDENTIFIER'      :0x01.to_bytes(1,byteorder='big'),
            'SUCCESS'         :0x02.to_bytes(1,byteorder='big'),
            'FAIL'            :0x03.to_bytes(1,byteorder='big')}
  
        self.sample_codes = {
            'SAMPLE_SEC'      :0x01.to_bytes(1,byteorder='big'),
            'SAMPLE_MIN'      :0x02.to_bytes(1,byteorder='big'),
            'SAMPLE_HOUR'     :0x03.to_bytes(1,byteorder='big'),
            'SAMPLE_DAY'      :0x04.to_bytes(1,byteorder='big')}
  
        for port in self._scanPorts():
  
            try:
                
                self.handle = serial.Serial(port,
                                            baudrate=115200, 
                                            bytesize=serial.EIGHTBITS,
                                            parity=serial.PARITY_EVEN,
                                            xonxoff=0,
                                            rtscts=0,
                                            stopbits=serial.STOPBITS_ONE,
                                            timeout=3)
  
                self._sendCommand('IDENTIFY')
  
                response = self.handle.read(1)
  
                if response == self.responses['IDENTIFIER']:
                    acquired = 1
                    break
          
            except serial.SerialException:
                continue
  
        if not acquired:
            self.handle = None
            return None
  
        return
  
    def _scanPorts(self):
  
        ports = []
    
        if os.path.exists('/dev/serial/by-id'):
              entries = os.listdir('/dev/serial/by-id')
              dirs = [os.readlink(os.path.join('/dev/serial/by-id', x))
                      for x in entries]
              ports.extend([os.path.normpath(os.path.join('/dev/serial/by-id', x))
                           for x in dirs])
    
        return ports
  
    def _sendCommand(self, command, target=0, value=0):
  
      if command in iter(self.commands):
          command = self.commands[command]
      else:
          command = self.responses[command]
  
      out = struct.pack('>chh', command, target, value)
  
      self.handle.write(out)
  
      return 
  
    def _getData(self):
      if not self.is_connected():
          return None
  
      data = []
      bytes_sent = 0
      packet_format_string = '>'+'h'*32
      bytes_received = -1
  
      try:
          self._sendCommand('DUMP_DATA')
      except OSError:
          return -1
  
      for x in range(3):
      
          while True:
              package = self.handle.read(64)
              packet = struct.unpack(packet_format_string, package)
  
              for word in packet:
                  message = (word & 0xF000) >> 12
                  if message == 0x0:
                      data.append(word)
                      bytes_sent += 2
  
                  elif message == 0x4:
                      continue
  
                  elif message == 0x8:
                      bytes_received = packet[1]
                      break
  
              if bytes_received >= 0:
                  break
  
          if bytes_received == bytes_sent:
              self._sendCommand('SUCCESS')
              result = 1
          else:
              self._sendCommand('FAIL')
              result = 0
      
          if result == 1:
              break
          else:
              try:
                  self._sendCommand('DUMP_DATA')
              except OSError:
                  return -1
      
      if result:    
          return data
      else:
          return None

    def _changeSetting(self, setting, new_value):
        status = 1
        try:
            self._sendCommand('CHANGE_SETTING', settings[setting], new_value)
        except OSError:
            status = -1
      
        if self.handle.read(1) == self.responses['SUCCESS']:
            status = 0
      
        return status

    def close(self):
        self.handle.close()
        return

    def isConnected(self):
        if self.handle != None:
            return self.handle.isOpen()
        else:
            return False

    def getSettings(self):
        retStructure = None
        settings_count = len(settings)
        try:
            self._sendCommand('GET_SETTINGS')
            package = self.handle.read(settings_count*2)
            packet = struct.unpack('<' + 'h'*settings_count, package)
            
            retStructure = Settings(sensor=sensorOptions(packet[0]),
                                    unit=unitOptions(packet[1]),
                                    interval=int(packet[2]))

        except OSError:
            pass

        return retStructure

    def applySettings(self, newSettings):
        status = 1
        
        for setting in newSettings:
            if self._changeSetting(setting, newSettings[setting]):
                break
        else:
            status = 0

        return status

                
                
