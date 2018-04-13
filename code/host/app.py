#!/usr/bin/env python

from appJar import gui
import serial

rawFile = ""
xyzFile = ""
ser = serial.Serial()

def updateMeter(percentComplete=0):
    # updates the status bar @ GUI bottom
    app.setMeter("progress", percentComplete)

# GUI Button Functions
def chooseRaw():
    # opens a dialogue to choose a file path for the raw read
    global rawFile
    rawFile = app.saveBox(title="Raw Destination")
    app.setLabel("raw", rawFile)

def readRaw():
    # opens the serial port & reads lines into the raw file (CSV)
    ser.port = app.getEntry("Serial Port: ")
    ser.baudrate = int(app.getEntry("Baud Rate: "))
    with open(rawFile, "w+") as outFile:
        ser.open()
        ser.write(b"go")
        line = ""
        again = True
        while ser.is_open and again:
            line = ser.readline()
            if (line != "end"):
                if (line == ";"):
                    outFile.write("\n")
                else:
                    outFile.write(test + ",")
            else:
                again = False
        ser.close()

def cancelRead():
    # stops an active read before it automatically finishes
    ser.close()

def chooseXYZ():
    # opens a dialogue to choose a file path for the xyz conversion
    global xyzFile
    xyzFile = app.saveBox(title="XYZ Destination")
    app.setLabel("xyz", xyzFile)

def writeXYZ():##
    # converts raw file data into xyz point cloud & writes to xyz file
    pass
#   with open(rawFile, "r") as inFile:
#       text = inFile.readlines()
#   with open(xyzFile, "w") as outFile:
#       # calc stuff & write
#       outFile.write()

# GUI (main loop wrapper)
with gui("TTFS Scanner Host", bg="white", font={"size":12}, padding=10, inPadding=10) as app:
    with app.frame("INTERFACE", row=0, column=0, sticky="NESW", stretch="BOTH"):
        with app.frame("LEFT", row=0, column=0, sticky="NESW", padding=10):
            app.startLabelFrame("Serial \u27a1 Raw")
            app.addLabelAutoEntry("Serial Port: ", words=["COM", "/dev/tty.usbserial-", "/dev/ttyACM0"])
            app.setAutoEntryNumRows("Serial Port: ", 2)
            app.addLabelNumericEntry("Baud Rate: ")
            app.buttons(["Raw Destination"], [chooseRaw])
            app.addLabel("raw", "[None]")
            app.buttons(["Read", "Cancel"], [readRaw, cancelRead])
            app.stopLabelFrame()

        with app.frame("RIGHT", row=0, column=1, sticky="NESW", padding=10):
            app.startLabelFrame("Raw \u27a1 XYZ")
            app.buttons(["XYZ Destination"], [chooseXYZ])
            app.addLabel("xyz", "[None]")
            app.buttons(["Convert to XYZ"], [writeXYZ])
            app.stopLabelFrame()

    with app.frame("STATUS", row=1, column=0, colspan=2):
        app.addMeter("progress")
        app.setMeterFill("progress", "green")
        app.setMeter("progress", 75)
