#*************************************************************************************************
#
#     File Name: communication.py
#       Project: Erebus Labs Sensor
# Revision Date: 03/21/2014
#   Description: This file handles serial communications for the Erebus Labs sensor user interface
#
#*************************************************************************************************

import serial


def handshake():
  """Determines which COM port the Erebus Sensor is connected to and returns the serial handle

  Inputs: None

  Outputs: 
    Name      Type    Purpose
    handle    Serial  handle to Erebus Labs serial port connection
                      If serial communication cannot be established, None is returned
  """

  # Nothing here yet!

  return

if __name__ == "__main__":
  # This function will run handshake if this file is run by itself
  handshake()
    
