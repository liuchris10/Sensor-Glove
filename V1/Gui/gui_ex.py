import serial
import numpy as np
from matplotlib import pyplot as plt

port1 = serial.Serial(port='COM7', baudrate=9600, bytesize=serial.EIGHTBITS, stopbits=serial.STOPBITS_ONE, timeout=None)

plt.ion()  # set plot to animated

ydata = [0] * 50
ax1 = plt.axes()

# make plot
line, = plt.plot(ydata)
plt.ylim([0, 65536])

# start data collection
while 1:
    try:
        indicator = port1.read()
        if indicator == b's':
            temp_a = port1.read()
            temp_b = port1.read()
            data = (temp_b[0] << 8) | temp_a[0]
        print(data)
        # ymin = 0
        # ymax = 65536
        # plt.ylim([ymin, ymax])
        # ydata.append(data)
        # del ydata[0]
        # line.set_xdata(np.arange(len(ydata)))
        # line.set_ydata(ydata)  # update the data
        # plt.draw()  # update the plot
    except port1.SerialTimeoutException:
        print('Data could not be read')