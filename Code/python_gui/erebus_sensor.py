#*************************************************************************************************
#
#     File Name: erebus_sensor.py
#       Project: Erebus Labs Sensor
# Revision Date: 04/07/2014
#   Description: This file contains the main Erebus Sensors program
#
#*************************************************************************************************

# System Imports
import tkinter as tk

# Project Imports
from sensor import ErebusSensor

class ErebusGUI(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
        self.pack()
        self.createWidgets()

    def createWidgets(self):

        self.tTitle = tk.Label(self)
        self.tTitle["text"] = "Erebus Labs Sensor"
        self.tTitle["font"] = ("Helvetica", 20, 'bold italic')
        self.tTitle.pack(side="top")

        self.bConnectSensor = tk.Button(self)
        self.bConnectSensor["text"] = "Connect to Erebus Sensor"
        self.bConnectSensor["command"] = self.connectSensor
        self.bConnectSensor.pack(side="left")

        self.bExit = tk.Button(self)
        self.bExit["text"] = "Exit"
        self.bExit["command"] = root.destroy
        self.bExit.pack(side="right")

    def connectSensor(self):
        print("Connecting...")

root = tk.Tk()
app = ErebusGUI(master=root)
app.mainloop()

