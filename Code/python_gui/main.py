#*************************************************************************************************
#
#     File Name: main.py
#       Project: Erebus Labs Sensor
# Revision Date: 03/27/2014
#   Description: This file contains the main Erebus Sensors program
#
#*************************************************************************************************

from erebus_sensor import ErebusSensor

log_name = "dump.txt"

def main():
  
  sensor = ErebusSensor()

  if sensor.is_connected():
    print("\nConnected")
  else:
    print("\nNot Connected")
    return

  print("\nAvailable Commands:\n")
  print("\tI:\tIdentify Device")
  print("\tD:\tDump Data")
  print("\tC:\tChange Blink Rate")
  print("\tq:\tQuit")

  while True:
    response = input("\n\nPlease enter a command: ")
    
    if response == 'I':
      print("\nRequesting Identifier...")
      print("Reply: {}".format(str(sensor.request_id())))

    elif response == 'D':
      print("\nRequesting Data Dump...")
      print("Data dumped to {}".format(log_name))

    elif response == 'C':
      value = int(input("\tEnter new blink rate:").strip(" .\n\r"))
      limit = pow(2,16) - 1
      if value > limit:
        print("Value out of range. Setting blink period to {}".format(limit))
        value = limit
      result = sensor.change_setting('BLINK_RATE', value)
      if result != -1:
        print("New setting applied")
      else:
        print("Settings Adjustment Failed")
        
    elif response == 'q':
      break

    else:
      print("Not a valid choice.")

if __name__ == "__main__":
  main()
