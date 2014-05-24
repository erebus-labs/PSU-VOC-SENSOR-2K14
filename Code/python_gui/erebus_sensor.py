"""
     File Name: erebus_sensor.py
       Project: Erebus Labs Sensor
   Description: This file contains the main Erebus Sensor interface program.
"""

# System Imports
import tkinter 

# Project Imports
import erebus_sensor.gui 

def main():

    root = tkinter.Tk()
    app = erebus_sensor.gui.ErebusGUI(master=root)
    app.mainloop()

if __name__ == '__main__':
    main()

