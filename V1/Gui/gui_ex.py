import serial
import numpy as np
from matplotlib import pyplot as plt
from drawnow import *

port1 = serial.Serial(port='COM4', baudrate=9600, bytesize=serial.EIGHTBITS, stopbits=serial.STOPBITS_ONE, timeout=None)

plt.ion()  # set plot to animated

rawdata = [] # Raw Data from Arduino.
pressure = [] # Transforming the Data from the Arduino into something Useful
count = 0

def makeFig(): #Create a function that makes our desired plot
    plt.ylim(0,65535)                                 #Set y min and max values
    plt.title('My Live Streaming Sensor Data from Arduino')      #Plot the title
    plt.grid(True)                                  #Turn the grid on
    plt.ylabel('Raw Data')                            #Set ylabels
    plt.plot(rawdata, 'ro-', label='Raw Values')       #plot the temperature
    plt.legend(loc='upper left')                    #plot the legend
    plt2=plt.twinx()                                #Create a second y axis
    plt.ylim(0,500)                           #Set limits of second y axis- adjust to readings you are getting
    plt2.plot(pressure, 'b^-', label='Pressure (Pa)') #plot pressure data
    plt2.set_ylabel('Pressrue (Pa)')                    #label second y axis
    plt2.ticklabel_format(useOffset=False)           #Force matplotlib to NOT autoscale y axis
    plt2.legend(loc='upper right')                  #plot the legend

# start data collection
while 1:
    while(port1.inWaiting()==0):
        pass
    indicator = port1.read()
    if indicator == b's':
        temp_a = port1.read()
        temp_b = port1.read()
        data = (temp_b[0] << 8) | temp_a[0]
    print(data)
    rd = float(data)
    p = (rd/65535)*500
    rawdata.append(rd)
    pressure.append(p)
    drawnow(makeFig)
    plt.pause(.000001)
    count = count + 1
    if (count > 50):
        rawdata.pop(0)
        pressure.pop(0)
