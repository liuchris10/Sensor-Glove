import serial_1 as sp1
import tkinter as tk
from tkinter import ttk
import sys
import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import matplotlib.animation as animation
from matplotlib import style
from matplotlib import pyplot as plt

import urllib
import json

import pandas as pd
import numpy as np

LARGE_FONT = ("Verdana", 12)
TITLE_FONT = ("Times",16)
NORM_FONT = ("Helvetica", 10)
SMALL_FONT = ("Helvetica", 8)
style.use("ggplot")

f = Figure(figsize=(10,6), dpi=100)
a = f.add_subplot(111)

def init_gui():
    app = SensorGlove()
    app.geometry("1280x720")
    ani = animation.FuncAnimation(f, animate, interval=1000)
    app.mainloop()

def popupmsg(msg):
    popup = tk.Tk()
    popup.wm_title("Pop-Up Message!")
    label = ttk.Label(popup, text=msg, font=NORM_FONT)
    label.grid(row=0,column=0)
    B1 = ttk.Button(popup, text="Okay", command = popup.destroy)
    B1.grid(row=0,column=1)
    popup.mainloop()

def animate(i):
    dataLink = 'https://btc-e.com/api/3/trades/btc_usd?limit=2000'
    data = urllib.request.urlopen(dataLink)
    data = data.readall().decode("utf-8")
    data = json.loads(data)

    data = data["btc_usd"]
    data = pd.DataFrame(data)

    buys = data[(data['type'] == "bid")]
    buys["datestamp"] = np.array(buys["timestamp"]).astype("datetime64[s]")
    buyDates = (buys["datestamp"]).tolist()

    sells = data[(data['type'] == "ask")]
    sells["datestamp"] = np.array(sells["timestamp"]).astype("datetime64[s]")
    sellDates = (sells["datestamp"]).tolist()

    a.clear()

    a.plot_date(buyDates, buys["price"], "#00A3E0", label="buys")
    a.plot_date(sellDates, sells["price"], "#183A54", label="sells")

    a.legend(bbox_to_anchor=(0, 1.02, 1, .102), loc=3,
             ncol=2, borderaxespad=0)

    title = "BTC-e BTCUSD Prices\nLast Price: " + str(data["price"][1999])
    a.set_title(title)

def print_Name1():
        print("Carl!")

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
        subMenu.add_separator()
        subMenu.add_command(label="Exit", command=lambda: print_Name1())
        menubar.add_cascade(label="Settings", menu=subMenu)

        editMenu = tk.Menu(menubar, tearoff=1)
        editMenu.add_command(label="Help Menu", command=lambda: self.show_frame(Help_Page))
        editMenu.add_separator()
        editMenu.add_command(label="Exit", command=lambda: print_Name1())
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

        button2 = ttk.Button(self, text="Quit", command=quit)
        button2.grid(row=3, column=0)

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
        #self.parent.title('App')
        s_toggle = [0] * 26
        graph = tk.Frame(self)
        self.create_CheckBox()

        self.canvas = FigureCanvasTkAgg(f, graph)
        self.canvas.get_tk_widget().pack()

        self.toolbar = NavigationToolbar2TkAgg(self.canvas, graph)
        #toolbar.update()
        #canvas._tkcanvas.pack()
        graph.tkraise()
    def update_CheckBox_Sensors(self,s_toggle):
        #sp1.update_Sensor(8, int(s_toggle[b-1]))
        print(s_toggle)

    def create_CheckBox(self):
        s1_check = tk.Checkbutton(self, text="Sensor 1", onvalue = 1, offvalue = 0, command=lambda: self.update_CheckBox_Sensors(1))
        s1_check.grid(row=0, column=0)

        s2_check = tk.Checkbutton(self, text="Sensor 2", onvalue = 1, offvalue = 0, command =lambda: self.update_CheckBox_Sensors(2))
        s2_check.grid(row=1, column=0)
