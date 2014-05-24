"""
     File Name: interface.py
       Project: Erebus Labs Sensor
   Description: This file defines the ErebusSensor class

"""

import serial
import struct
import sys
import os
import time
from glob import glob
from datetime import datetime

# Module Level Variables

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
"""
Contains settings for the Erebus Sensor and packs them into a bytes object for 
transmission over USB.

Members:
    SENSOR          contains the bitfield designating the sensor in use
    SAMPLE_UNIT     contains the bitfield designating the time unit for samples
    SAMPLE_INTERVAL contains the bitfield designating number of SAMPLE_UNITS that should
                        pass between samples

Methods:
    __init__        initializes Settings object 
    pack            packs settings into 24-bit bytes object for transmission over USB
"""
    def __init__(self, sensor=sensorOptions[0], unit=unitOptions[0], interval=1):
    """
    Initializes Settings object.

    Arguments:
        sensor      integer bitfield designating the sensor in use
        unit        integer bitfield designating the sample unit
        interval    integer bitfield designating the sample interval
    """
        self.SENSOR = sensor
        self.SAMPLE_UNIT = unit
        self.SAMPLE_INTERVAL = interval
        return

    def pack(self):
    """
    Packs settings into 24-bit bytes object for transmission over USB.

    Arguments:
        <None>
    """

        sensor_index = (sensorOptions.index(self.SENSOR)).to_bytes(1, byteorder='big')
        unit_index  = unitOptions.index(self.SAMPLE_UNIT).to_bytes(1, byteorder='big')
        interval = self.SAMPLE_INTERVAL.to_bytes(1, byteorder='big')

        packed = struct.pack('>ccc', sensor_index, unit_index, interval)
        return packed

class DataBlock:
"""
Contains a block of data samples and their header.

Members:
    sensor          indicates the sensor used for this block of samples
    sample_unit     indicates the sampling unit for this block of data samples
    sample_interval indicates the sample interval for this block of samples
    second          second field of data sample start time
    minute          minute field of data sample start time
    hour            hour field of data sample start time
    day             day of month field of data sample start time
    year            year field of data sample start time
    data            list of data samples
    data_points     count of how many samples are present in this block

Methods:
    __init__        initializes the DataBlock object
    add_sample      adds a 16-bit sample to the list of samples
    end             called when no more samples will be added to the block. Stores the 
                        number of samples in data_points
"""
    def __init__(self):
    """
    Initializes DataBlock object.

    Arguments: 
        <None>
    """
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
    """
    Adds a 16-bit sample to the list of samples.

    Arguments:
        word    16-bit sample to add to this block
    """
        self.data.append(word)
        return

    def end(self):
    """
    Called when no more samples will be added to the block. Stores the number of samples
    in data_points.

    Arguments: 
        <None>
    """
        self.data_points = len(self.data)
        return

    def __str__(self):
    """
    Returns formatted string of the data block for printing.

    Arguments:
        <None>
    """
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
"""
Provides an interface for sending commands to and receiving information from the Erebus
Labs sensor.

Members:
    command_size    Number of bytes in each command that may be sent to the sensor
    reply_size      Expected size of replies from the sensor
    commands        dictionary mapping command bit patterns to bytes objects
    replies         dictionary mapping replies (both host and device) to bytes objects
    sample_codes    maps valid sample units to bytes objects
    data_codes      maps markers found in dumped data to their bit patterns
    handle          serial.Serial object that communicates with the sensor

Methods:
    __init__        Attempts to establish communication with sensor and initializes the
                        ErebusSensor object
    _scanPorts      Pings available serial ports with requests for the Erebus Sensor
                        "Identify" command, looking for the sensor's reply

"""

    def __init__(self):
        """
        Attempts to establish communication with sensor and initializes the ErebusSensor 
        object.
  
        Arguments:
            <None>
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
            'UPDATE_RTC'      :0x06.to_bytes(1,byteorder='big'),
            'NEXT'            :0x07.to_bytes(1,byteorder='big')}
  
        self.replies = { # these replies go in both directions
            'IDENTIFIER'      :0x10.to_bytes(1,byteorder='big'),
            'SUCCESS'         :0x20.to_bytes(1,byteorder='big'),
            'FAIL'            :0x30.to_bytes(1,byteorder='big')}
  
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
  
                if response == self.replies['IDENTIFIER']:
                    acquired = 1
                    break
          
            except serial.SerialException:
                continue
  
        if not acquired:
            self.handle = None
            return None
  
        return
  
    def _scanPorts(self):
    """
    Pings available serial ports with requests for the Erebus Sensor "Identify" command,
    looking for the sensor's reply.

    Only compatibile with Linux at this time. Once the Cypress USBUART driver issue is
    resolved, a method for establishing communication with the sensor on a Windows
    system should be added.

    Arguments:
        <None>
    """
  
        ports = []
    
        if os.path.exists('/dev/serial/by-id'):
              entries = os.listdir('/dev/serial/by-id')
              dirs = [os.readlink(os.path.join('/dev/serial/by-id', x))
                      for x in entries]
              ports.extend([os.path.normpath(os.path.join('/dev/serial/by-id', x))
                           for x in dirs])
    
        return ports
  
    def _sendCommand(self, command):
    """
    Retrieves the required bytes object for a command, packs it, and writes it out to
    the sensor handle.

    Arguments:
        command     string representation of command to send (must be a key in this
                        object's commands dictionary)
    """
        command = self.commands[command]
        print("Sending Command: {}".format(command))
        out = struct.pack('>c', command)
        self.handle.write(out)

        return 

    def _sendReply(self, reply):
    """
    Retrieves the required bytes object for a reply, packs it, and writes it out to
    the sensor handle.

    Arguments:
        reply   string representation of reply to send (must be a key in this
                        object's replies dictionary)
    """

        reply = self.replies[reply]
        print("Sending Reply: {}".format(reply))
        out = struct.pack('>c', reply)
        self.handle.write(out)

        return 


  
    def getData(self):
    """
    Sends the DUMP_DATA command to the sensor and parses incoming packets sent in
    response.

    Arguments:
        <None>
    """

        bytes_received = -1
        bytes_sent = 0
        blocks = []
        packet_format_string = '>'+'h'*32

        # We will make three attempts to get a successful dump
        for x in range(3):

            # initialize empty list of 2-byte chunks
            word_list = []
            try:
              self._sendCommand('DUMP_DATA')
            except OSError:
                # Serial port closed
                return -1

            # construct continuous list of 16-bit words out of incoming packets until the
            # last ones are received

            while True:
                # retrieve first 64 bytes
                package = self.handle.read(64)
                
                if len(package) < 64:
                    if package == self.replies['FAIL']:
                        return 1
                    continue

                packet = struct.unpack(packet_format_string, package)

                # Check for no data before iterating over packet
                if ((packet[0] & 0xF000) >> 12)  == self.data_codes['NO_DATA']:
                    self._sendReply('SUCCESS')
                    return []

                # iterate over packet while checking high-order bytes for markers
                for i, word in enumerate(packet):
                    message = (word & 0xF000) >> 12
                
                    if message == self.data_codes['END_DATA']:
                        # if end of data dump, the word after the END_DATA marker
                        # contains the number of bytes sent
                        bytes_sent = packet[i+1]
                        break

                    elif message == self.data_codes['PAD_BYTE']:
                        break

                    else:
                        word_list.append(word)

                # propogate break out of this loop as well if transmission is done
                if message == self.data_codes['END_DATA']:
                    break

                # send next 64-byte packet
                self._sendCommand('NEXT')


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

            # byte counts match, we can break out of this loop as well and parse the data
            # if not, restart at outermost loop and send dump data command again
            if not result:
              break

        # turn word list into an iterator
        iter_word_list = iter(word_list)

        # iterate over data list and parse - build a new SampleBlock object every time
        # a new block is encountered
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

                # Skip over pad bytes used in header for alignment
                next(iter_word_list)
                next(iter_word_list)

        for data_block in blocks:
            data_block.end()

        if not result:    
            return blocks
        else:
            return 1

    def close(self):
    """
    Closes the serial.Serial handle to the sensor.

    Arguments:  
        <None>
    """
        self.handle.close()
        return

    def isConnected(self):
    """
    Reports whether or not the device is connected

    Arguments:  
        <None>
    """
        if self.handle != None:
            return self.handle.isOpen()
        else:
            return False

    def getSettings(self):
    """
    Retrieves the current settings in the sensor and returns a Settings object
    containing them.

    Arguments:
        <None>
    """
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
    """
    Sends the APPLY_SETTINGS command to the sensor followed by the new settings.

    Arguments:
        sensor_string   string representation of the sensor selection
        unit_string     string representation of the sample unit
        interval        integer interval
    """
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
    """
    Waits for a SUCCESS or FAIL reply from the sensor. Eight attempts are made before
    reporting fail.

    Arguments:
        <None>
    """
        
        for x in range(8):
            reply = self.handle.read(self.reply_size)
            # incoming data comes in off the wire as packed bytes - we must compare
            # the retrieved reply against the corresponing bytes objects in the
            # replies dictionary, not against the string keys
            if reply in self.replies.values():
                break;
            time.sleep(0.25)
        else:
            return 1

        if reply == self.replies['SUCCESS']:
            return 0
        else:
            return 1

    def update_RTC(self):
    """
    Sends the current local time to the sensor so it can update its real-time clock.

    Arguments:
        <None>
    """
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

    def ptr_reset(self):
    """
    Sends the HARD_RESET command to the sensor to force it to reset the sample block
    pointers to default values.

    Arguments:
        <None>
    """
        self._sendCommand('HARD_RESET')
        return self._await_result()
                
