#*************************************************************************************************
#
#     File Name: erebus_sensor.py
#       Project: Erebus Labs Sensor
# Revision Date: 04/12/2014
#   Description: This file contains the main Erebus Sensors program
#
#*************************************************************************************************

# System Imports
import tkinter as tk

# Project Imports
import sensor

class ErebusGUI(tk.Frame):
    def __init__(self, master=None):

        # Initialize Window
        tk.Frame.__init__(self, master)
        self.configureWindow()

        # Configure GUI-wide variables
        self.sensorHandle = None

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
        self.subMenuSensor.add_command(label="Get Current Configuration")
        self.subMenuSensor.add_command(label="Apply Current Configuration")
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
        self.lStatus = tk.Label(self.fStatus, text="Sensor Not Connected")
        self.lStatus['font'] = ('Helvetica', 16, 'bold')
        self.lStatus['width'] = 24
        self.lStatus['height'] = 3
        self.lStatus['background'] = 'red'
        self.lStatus['foreground'] = 'black'
        self.lStatus.grid(row=0, column=0, padx=10, pady=10, sticky=tk.E+tk.W)

        # Create Connect Button
        self.bConnectSensor = tk.Button(self.fStatus)
        self.bConnectSensor['text'] = "Connect to Erebus Sensor"
        self.bConnectSensor['font'] = ('Helvetica', 12, 'bold')
        self.bConnectSensor['command'] = self.connectSensor
        self.bConnectSensor['relief'] = tk.RAISED
        self.bConnectSensor.grid(row=0, column=1, padx=10, pady=10)

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

        # Create Fields
        self.sensorOptions = tk.StringVar()
        self.sensorOptions.set(sensor.sensorOptions[0])
        self.dSettingSensor = tk.OptionMenu(self.fSettings,
                                            self.sensorOptions,
                                            *sensor.sensorOptions)
        self.dSettingSensor.grid(row=1, column=1, sticky=tk.E+tk.W, padx=20)

        self.eSettingInterval = tk.Entry(self.fSettings)
        self.eSettingInterval["width"] =25 
        self.eSettingInterval.grid(row=2, column=1, sticky=tk.E+tk.W, padx=20)
        
        self.lSettingInterval = tk.Label(self.fSettings)
        self.lSettingInterval["text"] = ("Interval must be between 0 and {}"
                                        .format(sensor.maxInterval))
        self.lSettingInterval["font"] = ('Helvetica', 10)
        self.lSettingInterval.grid(row=2, column=2, padx=20)

        self.unitOptions = tk.StringVar()
        self.unitOptions.set(sensor.unitOptions[0])
        self.dSettingUnit = tk.OptionMenu(self.fSettings,
                                          self.unitOptions,
                                          *sensor.unitOptions)
        self.dSettingUnit.grid(row=3, column=1, sticky=tk.E+tk.W, padx=20)


    def connectSensor(self):
        print('Connecting...')

def main():

    root = tk.Tk()
    root.wm_title('Erebus Labs Sensor')
    app = ErebusGUI(master=root)
    app.mainloop()

if __name__ == '__main__':
    main()

