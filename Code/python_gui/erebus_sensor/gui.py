#*************************************************************************************************
#
#     File Name: gui.py
#       Project: Erebus Labs Sensor
# Revision Date: 04/13/2014
#   Description: This file contains the main Erebus Sensor gui class
#
#*************************************************************************************************

# System Imports
import tkinter as tk
import tkinter.messagebox as mb
import time
import copy
from datetime import datetime

# Project Imports
import erebus_sensor.interface as interface

class ErebusGUI(tk.Frame):
    def __init__(self, master=None):

        # Configure GUI-wide variables
        self.sensorHandle = None
        self.sensorSettings = None
        self.displayedSettings = interface.Settings()

        # Initialize Window
        tk.Frame.__init__(self, master)
        self.configureWindow()
        master.wm_title('Erebus Labs Sensor')


    def configureWindow(self):
        
        # *** Configure Top-Level Window ***
        self.grid(sticky=tk.N+tk.S+tk.E+tk.W)
        self.pack()
        top = self.winfo_toplevel()
        top.rowconfigure(0, weight=1)
        top.columnconfigure(0, weight=1)
        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)
        self['padx'] = 10
        self['pady'] = 10

        # *** Create Top-level Menu ***
        self.menuBar = tk.Menu(top, tearoff=0)
        top['menu'] = self.menuBar

        # Create File Menu Entry 
        self.subMenuFile = tk.Menu(self.menuBar, tearoff=0)
        self.menuBar.add_cascade(label='File', menu=self.subMenuFile)
        self.subMenuFile.add_command(label="Load Sensor Configuration")
        self.subMenuFile.add_command(label="Save Sensor Configuration")
        self.subMenuFile.add_command(label="Exit", command=self.quit)

        # Create Sensor Menu Entry 
        self.subMenuSensor = tk.Menu(self.menuBar, tearoff=0)
        self.menuBar.add_cascade(label="Sensor", menu=self.subMenuSensor)
        self.subMenuSensor.add_command(label="Get Data")
        self.subMenuSensor.add_command(label="Get Current Configuration",
                                       command=self.getSettings)
        self.subMenuSensor.add_command(label="Apply Current Configuration",
                                        command=self.applySettings)
        self.subMenuSensor.add_command(label="Reset Sensor")

        # Create Help Menu Entry
        self.subMenuHelp = tk.Menu(self.menuBar, tearoff=0)
        self.menuBar.add_cascade(label="Help", menu=self.subMenuHelp)
        self.subMenuHelp.add_command(label="User Guide")
        self.subMenuHelp.add_command(label="Technical Manual")
        self.subMenuHelp.add_command(label="About")

        # *** Create Sensor Button and Status Box ***

        # Create the Frame
        self.fStatus = tk.Frame(self)
        self.fStatus['borderwidth'] = 3 
        self.fStatus['padx'] = 10
        self.fStatus['pady'] = 10
        self.fStatus['relief'] = tk.GROOVE
        self.fStatus.grid(row=0, sticky=tk.E+tk.W)

        # Create Sensor Status Box
        self.lStatus = tk.Label(self.fStatus)
        self.lStatus['font'] = ('Helvetica', 16, 'bold')
        self.lStatus['width'] = 24
        self.lStatus['height'] = 3
        self.lStatus['foreground'] = 'black'
        self.lStatus.grid(row=0, column=0, padx=10, pady=10, sticky=tk.E+tk.W)

        # Create Connect Button
        self.bConnectSensor = tk.Button(self.fStatus)
        self.bConnectSensor['font'] = ('Helvetica', 12, 'bold')
        self.bConnectSensor['command'] = self.toggleSensor
        self.bConnectSensor['relief'] = tk.RAISED
        self.bConnectSensor.grid(row=0, column=1, padx=10, pady=10)

        # Initialize Connected and Button Text
        self._disconnectedMessage()

        # *** Create Settings Area ***
        self.fSettings = tk.Frame(self)
        self.fSettings['borderwidth'] = 3 
        self.fSettings['padx'] = 10
        self.fSettings['pady'] = 10
        self.fSettings['relief'] = tk.GROOVE
        self.fSettings.grid(row=1, sticky=tk.E+tk.W)
        
        # Create Header
        self.lStatusHeader = tk.Label(self.fSettings, text="Data Collection Settings")
        self.lStatusHeader['font'] = ('Helvetica', 14, 'bold')
        self.lStatusHeader.grid(row=0, column=0, columnspan=3, sticky=tk.W)
        
        # Create Section Labels
        self.lSettingSensor = tk.Label(self.fSettings, text="Sensor:")
        self.lSettingSensor['font'] = ('Helvetica', 12)
        self.lSettingSensor.grid(row=1, column=0, sticky=tk.E, padx=10)
        self.lSettingInterval = tk.Label(self.fSettings, text="Interval:")
        self.lSettingInterval['font'] = ('Helvetica', 12)
        self.lSettingInterval.grid(row=2, column=0, sticky=tk.E, padx=10)
        self.lSettingUnit = tk.Label(self.fSettings, text="Unit:")
        self.lSettingUnit['font'] = ('Helvetica', 12)
        self.lSettingUnit.grid(row=3, column=0, sticky=tk.E, padx=10)

        # Create Sensor Selection Dropdown
        self.sensorOptions = tk.StringVar()
        self.sensorOptions.set(self.displayedSettings.SENSOR)
        self.dSettingSensor = tk.OptionMenu(self.fSettings,
                                            self.sensorOptions,
                                            *interface.sensorOptions)
        self.dSettingSensor.grid(row=1, column=1, sticky=tk.E+tk.W, padx=20)

        # Create Interval Edit Box
        self.eSettingInterval = tk.Entry(self.fSettings)
        self.eSettingInterval["width"] =25 
        self.iSettingInterval = tk.StringVar()
        self.eSettingInterval["textvariable"] = self.iSettingInterval
        self.eSettingInterval["justify"] = tk.RIGHT
        self.eSettingInterval.insert(0, str(self.displayedSettings.SAMPLE_INTERVAL))
        self.eSettingInterval.grid(row=2, column=1, sticky=tk.E+tk.W, padx=20)

        self.lSettingInterval = tk.Label(self.fSettings)
        self.lSettingInterval["text"] = ("Interval must be between 0 and {}"
                                        .format(interface.maxInterval))
        self.lSettingInterval["font"] = ('Helvetica', 10)
        self.lSettingInterval.grid(row=2, column=2, padx=20)

        # Create Unit Selection Dropdown
        self.unitOptions = tk.StringVar()
        self.unitOptions.set(self.displayedSettings.SAMPLE_UNIT)
        self.dSettingUnit = tk.OptionMenu(self.fSettings,
                                          self.unitOptions,
                                          *interface.unitOptions)
        self.dSettingUnit.grid(row=3, column=1, sticky=tk.E+tk.W, padx=20)

        return

    def toggleSensor(self):

        if self.sensorHandle != None:
            self.disconnectSensor()
            self._disconnectedMessage()

        else:
            self.lStatus['background'] = 'yellow'
            self.lStatus['text'] = "Connecting..."
            proceed = mb.askokcancel("Connecting...",
                                     "This may take up to 30 seconds and cannot be "
                                     "interrupted. Click OK to continue.")

            if proceed and not self.connectSensor():
                self._connectedMessage()
            elif proceed:
                self._disconnectedMessage(warning="Could not establish communication "
                                                  "with Erebus Sensor.")
            else:
                self._disconnectedMessage()
                
        return

    def _connectedMessage(self):
        self.lStatus['background'] = 'green'
        self.lStatus['text'] = "Sensor Connected"
        self.bConnectSensor["text"] = "Disconnect Sensor"
        return

    def _disconnectedMessage(self, warning=None):
        self.lStatus['background'] = 'red'
        self.lStatus['text'] = "Sensor Not Connected"
        self.bConnectSensor["text"] = "Connect to Erebus Sensor"

        if warning:
            mb.showwarning("Failure", warning)

        return

    def _showNotConnected(self):
        mb.showerror("", "Erebus sensor is not currently connected. Please connect "
                         "the sensor and try again.")

        return

    def connectSensor(self):
        connectLimit = 12
        status = 1

        for x in range(connectLimit):
            self.sensorHandle = interface.ErebusSensor()
            if self.sensorHandle.isConnected():
                status = 0
                break

            time.sleep(3)

        return status

    def disconnectSensor(self):
        if self.sensorHandle != None:
            self.sensorHandle.close()
            self.sensorHandle = None
        return

    def getSettings(self):
        if self.sensorHandle == None:
            self._showNotConnected()
            return

        self.sensorSettings = self.sensorHandle.getSettings()

        self.sensorOptions.set(self.sensorSettings.SENSOR)
        self.eSettingInterval.delete(0, tk.END)
        self.eSettingInterval.insert(0, str(self.sensorSettings.SAMPLE_INTERVAL))
        self.unitOptions.set(self.sensorSettings.SAMPLE_UNIT)
        
        return

    def applySettings(self):
        if self.sensorHandle == None:
            self._showNotConnected()
            return

        if self.sensorSettings == None:
            self.sensorSettings = self.sensorHandle.getSettings()

        newSettings = self.sensorSettings.extractDiff(self.displayedSettings)

        if self.sensorHandle.applySettings(newSettings):
            mb.showerror("", "Settings update failed. Please try again.")

        self.sensorSettings = copy.deepcopy(self.displayedSettings)

        return

    def getData(self):
        if self.sensorHandle == None:
            self._showNotConnected()
            return
        
        dataBlocks = self.sensorHandle.getData()

        if dataBlocks:
            with open('datadump.txt', 'a') as fo:
                fo.write("".join(["\n\n", "*"*30,
                                  "\nErebus Sensor Data Dump",
                                  "\n{} Blocks of data samples".format(len(dataBlocks)),
                                  "\nDump Time: {}".format(str(datetime.now())),
                                  "\n", "*"*30]))

                for block in dataBlocks:
                    fo.write(str(block))
            
        elif dataBlocks == []:
            mb.showinfo("", "There were no data samples to retrieve from the device.")

        else:
            self._showNotConnected()

        return
            
        

