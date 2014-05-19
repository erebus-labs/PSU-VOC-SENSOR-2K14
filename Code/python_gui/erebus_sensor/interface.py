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
import time
from glob import glob
from datetime import datetime

# Module Level Variablesi

# Do not change the order of the variables in these tuples
# Their indexes are used by the device firmware
sensorOptions = ('Light Sensor', 'Temperature Sensor')
unitOptions = ('Seconds', 'Minutes', 'Hours', 'Days')
maxInterval = pow(2, 8) - 1 

settings = {
    'SAMPLE_UNIT'     :0x01.to_bytes(1,byteorder='big'),
    'SAMPLE_INTERVAL' :0x02.to_bytes(1,byteorder='big'),
    'SENSOR'          :0x03.to_bytes(1,byteorder='big')}

months = {
    1  : 'January',
    2  : 'February',
    3  : 'March',
    4  : 'April',
    5  : 'May',
    6  : 'June',
    7  : 'July',
    8  : 'August',
    9  : 'September',
    10 : 'October',
    11 : 'November',
    12 : 'December'}
    

class Settings:
    def __init__(self, sensor=sensorOptions[0], unit=unitOptions[0], interval=1):
        self.SENSOR = sensor
        self.SAMPLE_UNIT = unit
        self.SAMPLE_INTERVAL = interval

    def pack(self):

        sensor_index = (sensorOptions.index(self.SENSOR)).to_bytes(1, byteorder='big')
        unit_index  = unitOptions.index(self.SAMPLE_UNIT).to_bytes(1, byteorder='big')
        interval = self.SAMPLE_INTERVAL.to_bytes(1, byteorder='big')

        packed = struct.pack('>ccc', sensor_index, unit_index, interval)
        return packed

class DataBlock:
    def __init__(self):
        self.sensor = -1
        self.sample_unit = -1
        self.sample_interval = -1
        self.second = -1
        self.minute = -1
        self.hour = -1
        self.day = -1
        self.month = -1
        self.year = -1
        self.data = []
        self.data_points = 0
        return

    def add_sample(self, word):
        self.data.append(word)
        return

    def end(self):
        self.data_points = len(self.data)
        return

    def __str__(self):
        s = []
        s.append("\n\n\nTotal Samples in this Block: {}".format(self.data_points))
        s.append("Sensor:\t{}".format(self.sensor))
        s.append("Sample Unit:\t{}".format(self.sample_unit))
        s.append("Sample Interval:\t{}".format(self.sample_interval))
        s.append("\nData Collection Start Time Stamp:")
        s.append("{}:{}:{}".format(self.hour, self.minute, self.second))
        s.append("{} {} {}".format(months[self.month], self.day, self.year))
        s.append("\nData Points:")
        s = s + [str(point) for point in self.data]

        return "\n".join(s)

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
  
        self.command_size = 1 # number of bytes in each command
        self.reply_size = 1
  
        self.commands = {
            'IDENTIFY'        :0x01.to_bytes(1,byteorder='big'),
            'DUMP_DATA'       :0x02.to_bytes(1,byteorder='big'),
            'GET_SETTINGS'    :0x03.to_bytes(1,byteorder='big'),
            'APPLY_SETTINGS'  :0x04.to_bytes(1,byteorder='big'),
            'HARD_RESET'      :0x05.to_bytes(1,byteorder='big'),
            'UPDATE_RTC'      :0x06.to_bytes(1,byteorder='big')}
  
        self.device_replies = {
            'IDENTIFIER'      :0x01.to_bytes(1,byteorder='big'),
            'SUCCESS'         :0x02.to_bytes(1,byteorder='big'),
            'FAIL'            :0x03.to_bytes(1,byteorder='big')}

        self.host_replies = {
            'SUCCESS'         :0x02.to_bytes(1,byteorder='big'),
            'FAIL'            :0x03.to_bytes(1,byteorder='big'),
            'NEXT'            :0x07.to_bytes(1,byteorder='big')}
  
        self.sample_codes = {
            'SAMPLE_SEC'      :0x01.to_bytes(1,byteorder='big'),
            'SAMPLE_MIN'      :0x02.to_bytes(1,byteorder='big'),
            'SAMPLE_HOUR'     :0x03.to_bytes(1,byteorder='big'),
            'SAMPLE_DAY'      :0x04.to_bytes(1,byteorder='big')}

        self.data_codes = {
            'START_BLOCK'     :0x2,
            'PAD_BYTE'        :0x4,
            'END_DATA'        :0x8,
            'NO_DATA'         :0xA}
  
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
  
                response = self.handle.read(self.reply_size)
  
                if response == self.device_replies['IDENTIFIER']:
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
  
    def _sendCommand(self, command):
        command = self.commands[command]
        print("Sending Command: {}".format(command))
        out = struct.pack('>c', command)
        self.handle.write(out)

        return 

    def _sendReply(self, reply):

        reply = self.host_replies[reply]
        print("Sending Reply: {}".format(reply))
        out = struct.pack('>c', reply)
        self.handle.write(out)

        return 


  
    def getData(self):

        bytes_received = -1
        bytes_sent = 0
        blocks = []
        packet_format_string = '>'+'h'*32

        for x in range(3):
            word_list = []
            try:
              self._sendCommand('DUMP_DATA')
            except OSError:
                print("Failed on Error.\n")
                return -1

            # construct continuous list of 16-bit words out of incoming packets until the
            # last ones are received
            while True:
                package = self.handle.read(64)
                self._sendReply('NEXT')
                print("Package Received: {}\n".format(package))
                if len(package) < 64:
                    continue

                packet = struct.unpack(packet_format_string, package)

                # Check for no data before iterating over packet
                if ((packet[0] & 0xF000) >> 12)  == self.data_codes['NO_DATA']:
                    continue

                for i, word in enumerate(packet):
                    message = (word & 0xF000) >> 12
                
                    if message == self.data_codes['END_DATA']:
                        bytes_sent = packet[i+1]
                        break

                    elif message == self.data_codes['PAD_BYTE']:
                        continue

                    else:
                        word_list.append(word)

                else:
                    continue #executes if the for loop ends before breaking

                break

            # calculate total bytes received (2 per word in word_list + 4 bytes for
            # trailer)
            bytes_received = (len(word_list) * 2) + 4
            print("Word List: {}".format(word_list))
            print("Bytes Received: {}".format(bytes_received))
            print("Bytes Sent: {}".format(bytes_sent))

            if bytes_received == bytes_sent:
              self._sendReply('SUCCESS')
              result = 0
            else:
              self._sendReply('FAIL')
              result = 1

            if not result:
              break

        iter_word_list = iter(word_list)

        for word in iter_word_list:
            message = (word & 0xF000) >> 12
            
            if not message:
                blocks[-1].add_sample(word)

            elif message == self.data_codes['START_BLOCK']:
                blocks.append(DataBlock())
                blocks[-1].year = next(iter_word_list)

                temp = next(iter_word_list)
                blocks[-1].sensor = sensorOptions[(temp & 0xFF00) >> 8]
                blocks[-1].sample_unit = unitOptions[temp & 0x00FF]

                temp = next(iter_word_list)
                blocks[-1].sample_interval = (temp & 0xFF00) >> 8
                blocks[-1].second = temp & 0x00FF

                temp = next(iter_word_list)
                blocks[-1].minute = (temp & 0xFF00) >> 8
                blocks[-1].hour = temp & 0x00FF

                temp = next(iter_word_list)
                blocks[-1].day = (temp & 0xFF00) >> 8
                blocks[-1].month = temp & 0x00FF

        for data_block in blocks:
            data_block.end()

        if not result:    
            return blocks
        else:
            return 1

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

            try:
                packet = struct.unpack('<' + 'B'*settings_count, package)
            except struct.error:
                return -1
            
            retStructure = Settings(sensor=sensorOptions[packet[0]],
                                    unit=unitOptions[packet[1]],
                                    interval=int(packet[2]))

        except OSError:
            return -1

        return retStructure

    def applySettings(self, sensor_string, unit_string, interval):
        status = 1

        newSettings = Settings(sensor=sensor_string,
                               unit=unit_string,
                               interval=interval)

        self._sendCommand('APPLY_SETTINGS')

        if not self._await_result():
            self.handle.write(newSettings.pack())
            return self._await_result()

        return 1

    def _await_result(self):
        
        for x in range(8):
            reply = self.handle.read(self.reply_size)
            if reply in self.host_replies.values():
                break;
            time.sleep(0.25)
        else:
            return 1

        if reply == self.host_replies['SUCCESS']:
            return 0
        else:
            return 1

    def update_RTC(self):
        status = 1
        now = time.localtime(time.time())

        self._sendCommand('UPDATE_RTC')

        time_block = struct.pack('>HBBBBB', 
                                 now[0],    # year
                                 now[5],    # second
                                 now[4],    # minute
                                 now[3],    # hour
                                 now[2],    # day of month
                                 now[1])    # month
        print("Time Packet Out: {}\n".format(time_block))

        if not self._await_result():
            self.handle.write(time_block)
            return self._await_result()

        return 1

    def hard_reset(self):
        self._sendCommand('HARD_RESET')
        return
                
