#*************************************************************************************************
#
#     File Name: erebus_sensor.py
#       Project: Erebus Labs Sensor
# Revision Date: 04/13/2014
#   Description: This file contains the main Erebus Sensor interface program.
#
#*************************************************************************************************

# System Imports
import tkinter as tk

# Project Imports
import erebus_sensor.gui as gui

def main():

    root = tk.Tk()
    app = gui.ErebusGUI(master=root)
    app.mainloop()

if __name__ == '__main__':
    main()

