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
import subprocess

# Project Imports
import erebus_sensor.interface as interface

class ErebusGUI(tk.Frame):
    """
    Provides the user interface for the Erebus Labs sensor.

    Members:
        <Too Many To List>  all GUI attributes
        sensorHandle        serial.Serial object that communicates with the sensor
        displayedSettings   the collection of sensor settings displayed in the user
                                interface
    Methods:
        configureWindow     initializes the tkinter window

    """

    def __init__(self, master=None):
        """
        Initializes the ErebusGUI object and displays the user interface.

        Arguments:
            master  tkinter.Tk root object
        """

        # Configure GUI-wide variables
        self.sensorHandle = None
        self.displayedSettings = interface.Settings()

        # Initialize Window
        tk.Frame.__init__(self, master)
        self.configureWindow()
        master.wm_title('Erebus Labs Sensor')


    def configureWindow(self):
        """
        Configures and applies attributes of the GUI window.

        Arguments:
            <None>
        """
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
        self.subMenuFile.add_command(label="Exit", command=self.quit)

        # Create Sensor Menu Entry 
        self.subMenuSensor = tk.Menu(self.menuBar, tearoff=0)
        self.menuBar.add_cascade(label="Sensor", menu=self.subMenuSensor)
        self.subMenuSensor.add_command(label="Get Data",
                                       command=self.getData)
        self.subMenuSensor.add_command(label="Get Current Configuration",
                                       command=self.getSettings)
        self.subMenuSensor.add_command(label="Apply Current Configuration",
                                       command=self.applySettings)
        self.subMenuSensor.add_command(label="Reset Sensor",
                                       command=self.resetSensor)


        # Create Help Menu Entry
        self.subMenuHelp = tk.Menu(self.menuBar, tearoff=0)
        self.menuBar.add_cascade(label="Help", menu=self.subMenuHelp)
        self.subMenuHelp.add_command(label="User Manual",
                                     command=self.openManual)
        self.subMenuHelp.add_command(label="Technical Manual",
                                     command=self.openTRM)
        self.subMenuHelp.add_command(label="About",
                                     command=self.showAbout)

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
        """
        Toggles the sensor status box based on sensor connectivity state.
            Status window possible states:
                Red     Not Connected
                Yellow  Connecting
                Green   Connected

        Arguments:
            <None>
        """

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
                if self.sensorHandle.update_RTC():
                    mb.showwarning("RTC Not Updated",
                                   "Warning: The sensor is connected, but the "
                                   "device's time could not be updated. Consider "
                                   "disconnecting and reconnecting the sensor.")
                    
            elif proceed:
                self._disconnectedMessage(warning="Could not establish communication "
                                                  "with Erebus Sensor.")
                self.sensorHandle = None
            else:
                self._disconnectedMessage()
                self.sensorHandle = None
                
        return

    def _connectedMessage(self):
        """
        Sets the status and connection buttons to the connected state.

        Arguments:
            <None>
        """
        self.lStatus['background'] = 'green'
        self.lStatus['text'] = "Sensor Connected"
        self.bConnectSensor["text"] = "Disconnect Sensor"
        return

    def _disconnectedMessage(self, warning=None):
        """
        Sets the status and connection buttons to the disconnected state and displays a
        warning dialog box if necessary.

        Arguments:
            warning     string to display as a warning message to the user 
        """
        self.lStatus['background'] = 'red'
        self.lStatus['text'] = "Sensor Not Connected"
        self.bConnectSensor["text"] = "Connect to Erebus Sensor"

        if warning:
            mb.showwarning("Failure", warning)

        return

    def _showNotConnected(self):
        """
        Displays an error message to the user indicating that their command failed
        because the sensor is not currently connected.

        Arguments:
            <None>
        """
        mb.showerror("", "Erebus sensor is not currently connected. Please connect "
                         "the sensor and try again.")

        return

    def connectSensor(self):
        """
        Creates the ErebusSensor object, attempts to connect to the sensor, and reports the
        result.

        Arguments:
            <None>
        """
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
        """
        Severs the USBUART connection with the sensor.
        Note: This does not send any commands to the device. The sensor does not know the
              connection has been severed. It only considers itself disconnected when the
              USB cable is unplugged.

        Arguments:
            <None>
        """
        if self.sensorHandle != None:
            self.sensorHandle.close()
            self.sensorHandle = None
        return

    def getSettings(self):
        """
        Retrives the current sample settings from the device and displays them for the user.

        Arguments:
            <None>
        """

        if self.sensorHandle == None:
            self._showNotConnected()
            return

        sensorSettings = self.sensorHandle.getSettings()
        if sensorSettings == -1:
            mb.showerror("", "Settings could not be retrieved. Please try again.")
            return

        self.sensorOptions.set(sensorSettings.SENSOR)
        self.eSettingInterval.delete(0, tk.END)
        self.eSettingInterval.insert(0, str(sensorSettings.SAMPLE_INTERVAL))
        self.unitOptions.set(sensorSettings.SAMPLE_UNIT)
        
        return

    def applySettings(self):
        """
        Retrieves the current settings from the GUI window that the user has selected and
        sends them to the sensor.

        Arguments:
            <None>
        """
        if self.sensorHandle == None:
            self._showNotConnected()
            return

        if self.sensorHandle.applySettings(self.sensorOptions.get(),
                                           self.unitOptions.get(),
                                           int(self.eSettingInterval.get().strip(' ,.'))):
            mb.showerror("", "Settings update failed. Please try again.")

        else:
            mb.showinfo("", "Settings update successful.")

        return

    def getData(self):
        """
        Initiates a dump of stored samples from the sensor and outputs the result in a test
        file called "datadump.txt".

        Arguments:
            <None>
        """
        if self.sensorHandle == None:
            self._showNotConnected()
            return
        
        dataBlocks = self.sensorHandle.getData()

        if isinstance(dataBlocks, list) and dataBlocks:
            with open('datadump.txt', 'a') as fo:
                fo.write("".join(["\n\n", "*"*30,
                                  "\nErebus Sensor Data Dump",
                                  "\n{} Blocks of data samples".format(len(dataBlocks)),
                                  "\nDump Time: {}".format(str(datetime.now())),
                                  "\n", "*"*30]))

                for block in dataBlocks:
                    fo.write(str(block))

            mb.showinfo("", "Data export successful.")
            
        elif dataBlocks == []:
            mb.showinfo("", "There were no data samples to retrieve from the device.")

        else:
            mb.showerror("", "There was an error retrieving data from the device. "
                             "Please try again.")
        return
            
    def resetSensor(self):
        """
        Initiates a reset of the sample block pointers on the device. This function MUST
        be called after the device is reprogrammed, before any samples are collected.

        Arguments:
            <None>
        """
        if self.sensorHandle == None:
            self._showNotConnected()
            return

        if self.sensorHandle.hard_reset():
            mb.showerror("", "There was an erorr resetting the device. Please try "
                             "again.")
        else:
            mb.showinfo("", "Reset successful.")

        return

    def showAbout(self):
        """
        Displays an information box with the GUI version

        Arguments:
            <None>
        """
        
        mb.showinfo("About", "Erebus Labs Stem Sensor\n"
                             "User Application Version 1.0\n"
                             "(C) 2014 Erebus Labs")
        
        return

    def openTRM(self):
        """
        Opens the Erebus Labs Sensor Technical Reference Manual
        This routine is not cross-platform. It must be modified to enable Windows
        support.

        Arguments:
            <None>
        """

        subprocess.call(['xdg-open', './documents/Technical_Reference_Manual.pdf'],
                         stderr=None,
                         stdout=None)
        return

    def openManual(self):
        """
        Opens the Erebus Labs Sensor User Manual
        This routine is not cross-platform. It must be modified to enable Windows
        support.

        Arguments:
            <None>
        """

        subprocess.call(['xdg-open', './documents/User_Manual.pdf'],
                         stderr=None,
                         stdout=None)
        return

