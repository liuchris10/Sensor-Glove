import tkinter as tk
from tkinter import ttk

import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import matplotlib.animation as animation
from matplotlib import style

from matplotlib import pyplot as plt
from drawnow import *

import serial_1 as sp1

import pandas as pd
import numpy as np
import sys
import time

LARGE_FONT = ("Verdana", 12)
TITLE_FONT = ("Times",16)
NORM_FONT = ("Helvetica", 10)
SMALL_FONT = ("Helvetica", 8)
style.use("ggplot")


rawdata = []  # Raw Data from Arduino.
pressure = []  # Transforming the Data from the Arduino into something Useful
seconds = [] #Time Since Data has been Captured

f = Figure(figsize=(5,5), dpi=100)
a = f.add_subplot(111)
plt.ion()
start_time = 0
stop_time = 0
record = 0

def init_gui():
    app = SensorGlove()
    ani = animation.FuncAnimation(f,recordData,interval=100)
    app.geometry("1280x720")
    app.mainloop()

def popupmsg(msg):
    popup = tk.Tk()
    popup.wm_title("Pop-Up Message!")
    label = ttk.Label(popup, text=msg, font=NORM_FONT)
    label.grid(row=0,column=0)
    B1 = ttk.Button(popup, text="Okay", command = popup.destroy)
    B1.grid(row=0,column=1)
    popup.mainloop()

def record_start(value):
    global record
    global start_time
    if value == 0:
        record = 1
        start_time = time.time()

def record_stop(value):
    global record
    global start_time
    if value == 1:
        record = 0
        start_time = 0

def print_Name1():
        print("Carl!")


def makeFig():  # Create a function that makes our desired plot
    b = plt.figure(1)
    plt.ylim(0, 65535)  # Set y min and max values
    plt.title('Live Arduino Data')  # Plot the title
    plt.grid(True)  # Turn the grid on
    plt.ylabel('Raw Data')  # Set ylabels
    plt.plot(rawdata, 'ro-', label='Raw Values')  # plot the temperature
    plt.legend(loc='upper left')  # plot the legend
    plt2 = plt.twinx()  # Create a second y axis
    plt.ylim(0, 500)  # Set limits of second y axis- adjust to readings you are getting
    plt2.plot(pressure, 'b^-', label='Pressure (Pa)')  # plot pressure data
    plt2.set_ylabel('Pressrue (Pa)')  # label second y axis
    plt2.ticklabel_format(useOffset=False)  # Force matplotlib to NOT autoscale y axis
    plt2.legend(loc='upper right')  # plot the legend
    return b

def recordData(i):
    # start data collection
    global record
    data = 0
    if (record == 1):
        while (sp1.wait() == 0):
            pass
        indicator = sp1.read_8()
        if indicator == b's':
            data = sp1.read_dec()
        print(data)
        rd = float(data)
        p = (rd / 65535) * 500
        count = time.time() - start_time
        rawdata.append(rd)
        pressure.append(p)
        seconds.append(count)
        a.clear()
        a.plot(seconds, rawdata)
        # plt.pause(.000001)
        # count = count + 1
        # if (count > 50):
        #     rawdata.pop(0)
        #     pressure.pop(0)

class SensorGlove(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)

        tk.Tk.iconbitmap(self, default="sw-caution.gif")
        tk.Tk.wm_title(self, "Sensor Glove Gui")

        container = tk.Frame(self)
        container.grid(row=0,column=0)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.create_menu(container)
        self.frames = {}

        for F in (Intro_Page, Help_Page, Main_Page):
            frame = F(container, self)
            self.frames[F] = frame
            frame.grid(row=0, column=0, sticky="nsew")

        self.show_frame(Intro_Page)

    def show_frame(self, cont):
        frame = self.frames[cont]
        frame.tkraise()

    def create_menu(self, container):
        menubar = tk.Menu(container)

        fileMenu = tk.Menu(menubar, tearoff=0)
        fileMenu.add_command(label="Save Graph", command=lambda: popupmsg("Not supported just yet!"))
        fileMenu.add_command(label="Export Excel", command=lambda: popupmsg("Not supported just yet!"))
        fileMenu.add_separator()
        fileMenu.add_command(label="Exit", command=quit)
        menubar.add_cascade(label="File", menu=fileMenu)

        subMenu = tk.Menu(menubar, tearoff=1)
        subMenu.add_command(label="Sensor Calibration", command=lambda: popupmsg("Not supported just yet!"))
        subMenu.add_command(label="Save settings", command=lambda: popupmsg("Not supported just yet!"))
        menubar.add_cascade(label="Settings", menu=subMenu)

        editMenu = tk.Menu(menubar, tearoff=1)
        editMenu.add_command(label="Help Menu", command=lambda: self.show_frame(Help_Page))
        editMenu.add_separator()
        editMenu.add_command(label="Print Name", command=lambda: print_Name1())
        menubar.add_cascade(label="Help", menu=editMenu)

        tk.Tk.config(self, menu=menubar)


class Intro_Page(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self,parent)
        label1 = tk.Label(self, text=("Welcome to Sensor Glove Gui!"), font=LARGE_FONT)
        label1.grid(row=0,column=0)

        label2 = tk.Label(self, text=("Designed by the Flexible Electronics Lab @ UCSD"), font=TITLE_FONT)
        label2.grid(row=1, column=0)

        button1 = ttk.Button(self, text="Start!", command=lambda: controller.show_frame(Main_Page))
        button1.grid(row=2, column=0)

        #button2 = ttk.Button(self, text="Quit", command=_quit())
        #button2.grid(row=3, column=0)

        button3 = ttk.Button(self, text="Help Me!", command=lambda: controller.show_frame(Help_Page))
        button3.grid(row=4, column=0)


class Help_Page(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self,parent)

        label = tk.Label(self, text=("Welcome to Help Menu!"), font=TITLE_FONT)
        label.grid(row=0,column=0)

        button1 = ttk.Button(self, text="go Back to intro Page", command=lambda: controller.show_frame(Intro_Page))
        button1.grid(row=1,column=0)

        button2 = ttk.Button(self, text="Go Back to main Page", command=lambda: controller.show_frame(Main_Page))
        button2.grid(row=2,column=0)

class Main_Page(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.parent = parent
        self.create_CheckBox()
        self.create_Button()

        canvas_frame = tk.Frame(self)
        canvas_frame.grid(row=3, column=0,columnspan=2)
        canvas = FigureCanvasTkAgg(f, canvas_frame)
        canvas.show()
        canvas.get_tk_widget().pack(side=tk.BOTTOM)

        toolbar_frame = tk.Frame(self)
        toolbar_frame.grid(row=4,column=0,columnspan=2)
        toolbar = NavigationToolbar2TkAgg(canvas, toolbar_frame)
        toolbar.update()
        canvas._tkcanvas.pack(side=tk.TOP)


    def update_CheckBox_Sensors(self,s_toggle):
        #sp1.update_Sensor(8, int(s_toggle[b-1]))
        print(s_toggle)

    def create_CheckBox(self):
        s1_check = tk.Checkbutton(self, text="Sensor 1", onvalue = 1, offvalue = 0, command=lambda: self.update_CheckBox_Sensors(1))
        s1_check.grid(row=0, column=0)
        s2_check = tk.Checkbutton(self, text="Sensor 2", onvalue = 1, offvalue = 0, command =lambda: self.update_CheckBox_Sensors(2))
        s2_check.grid(row=1, column=0)
    def create_Button(self):
        button2 = ttk.Button(self, text="Start", command=lambda: record_start(record))
        button2.grid(row=2,column=0)
        button3 = ttk.Button(self, text="Stop", command=lambda: record_stop(record))
        button3.grid(row=2,column=1)

def main():
    init_gui()

if __name__ == "__main__":
    main()
