import tkinter as tk
from tkinter import ttk
import serial_tools
import data_graph
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib import style
import matplotlib

style.use("ggplot")
matplotlib.use("TkAgg")

def init_gui():
    app = SensorGlove()
    app.geometry("1280x720")
    app.mainloop()

class SensorGlove(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)

        # tk.Tk.iconbitmap(self, default="sw-caution.gif")
        tk.Tk.wm_title(self, "Sensor Glove Gui")

        self.container = tk.Frame(self)
        self.container.grid(row=0, column=0)
        self.container.grid_rowconfigure(0, weight=1)
        self.container.grid_columnconfigure(0, weight=1)

        self.large_font = ("Verdana", 12)
        self.title_font = ("Times", 16)
        self.normal_font = ("Helvetica", 10)
        self.small_font = ("Helvetica", 8)

        self.create_menu(self.container)
        self.frames = {}

        self.serial_port = serial_tools.SerialPort()
        self.dg = data_graph.DataGraph(self, self.serial_port)

        for F in (IntroPage, HelpPage, MainPage):
            frame = F(self.container, self)
            self.frames[F] = frame
            frame.grid(row=0, column=0, sticky="nsew")

        self.show_frame(IntroPage)

    def show_frame(self, cont):
        self.frame = self.frames[cont]
        self.frame.tkraise()

    def create_menu(self, container):
        menubar = tk.Menu(container)

        filemenu = tk.Menu(menubar, tearoff=0)
        filemenu.add_command(label="Save Graph", command=lambda: print("Not supported just yet!"))
        filemenu.add_command(label="Export Excel", command=lambda: print("Not supported just yet!"))
        filemenu.add_separator()
        filemenu.add_command(label="Exit", command=lambda: quit())
        menubar.add_cascade(label="File", menu=filemenu)

        submenu = tk.Menu(menubar, tearoff=1)
        submenu.add_command(label="Sensor Calibration", command=lambda: print("Not supported just yet!"))
        submenu.add_command(label="Save settings", command=lambda: print("Not supported just yet!"))
        menubar.add_cascade(label="Settings", menu=submenu)

        editmenu = tk.Menu(menubar, tearoff=1)
        editmenu.add_command(label="Help Menu", command=lambda: self.show_frame(HelpPage))
        editmenu.add_separator()
        editmenu.add_command(label="Print Name", command=lambda: self.print_name())
        menubar.add_cascade(label="Help", menu=editmenu)

        tk.Tk.config(self, menu=menubar)


class IntroPage(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.parent = parent
        self.controller = controller
        self.label1 = tk.Label(self, text="Welcome to Sensor Glove Gui!")
        self.label1.grid(row=0, column=0)

        self.label2 = tk.Label(self, text="Designed by the Flexible Electronics Lab @ UCSD")
        self.label2.grid(row=1, column=0)

        button4 = ttk.Button(self, text="Load Sensitivity", command=lambda: self.controller.dg.get_sensitivity())
        button4.grid(row=2, column=0)

        button5 = ttk.Button(self, text="Connect to Sensor Glove", command=lambda:
                             self.controller.serial_port.select_port())
        button5.grid(row=3, column=0)

        self.button1 = ttk.Button(self, text="Start!", command=lambda: controller.show_frame(MainPage))
        self.button1.grid(row=4, column=0)

        self.button2 = ttk.Button(self, text="Quit", command=lambda: quit())
        self.button2.grid(row=5, column=0)

        self.button3 = ttk.Button(self, text="Help Me!", command=lambda: controller.show_frame(HelpPage))
        self.button3.grid(row=6, column=0)


class HelpPage(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)

        self.label = tk.Label(self, text="Welcome to Help Menu!")
        self.label.grid(row=0, column=0)

        self.button1 = tk.Button(self, text="go Back to intro Page", command=lambda: controller.show_frame(IntroPage))
        self.button1.grid(row=1, column=0)


class MainPage(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.parent = parent
        self.controller = controller
        self.create_checkbox()
        self.create_button()

        canvas_frame = tk.Frame(self)
        canvas = FigureCanvasTkAgg(self.controller.dg.live_plot_figure, canvas_frame)
        canvas.show()
        canvas.get_tk_widget().pack()
        canvas_frame.grid(row=6, column=0, columnspan=5)

        toolbar_frame = tk.Frame(self)
        toolbar = NavigationToolbar2TkAgg(canvas, toolbar_frame)
        toolbar.update()
        canvas._tkcanvas.pack()
        toolbar_frame.grid(row=7, column=0, columnspan=2)

    def create_checkbox(self):
        button = []
        palm = tk.Frame(self)
        palm.grid(row=0, column=0, columnspan=4)
        fingers = tk.Frame(self)
        fingers.grid(row=0, column=5, columnspan=4)
        palm_title = tk.Label(palm, text='Palm')
        palm_title.grid(row=0)
        right_title = tk.Label(fingers, text='Fingers')
        right_title.grid(row=0)
        for n in range(1, 25):
            checkbox_name = "Sensor %d" % n
            if n > 12:
                button.append(tk.Checkbutton(fingers, text=checkbox_name, onvalue=1, offvalue=0,
                                             command=lambda m=n: self.controller.dg.update_checkbox_sensors(m)))
                if n > 20:
                    row = 3
                    column = 5 + (n-21)
                elif n > 16:
                    row = 2
                    column = 5 + (n-17)
                else:
                    row = 1
                    column = 5 + (n-13)
            else:
                button.append(tk.Checkbutton(palm, text=checkbox_name, onvalue=1, offvalue=0,
                                             command=lambda m=n: self.controller.dg.update_checkbox_sensors(m)))
                if n > 8:
                    row = 3
                    column = 0 + (n-9)
                elif n > 4:
                    row = 2
                    column = 0 + (n-5)
                else:
                    row = 1
                    column = 0 + (n-1)
            button[n-1].grid(row=row, column=column)

    def create_button(self):
        button_frame = tk.Frame(self)
        button2 = tk.Button(button_frame, text="Start", command=lambda: [self.controller.dg.calibrate_glove(),
                            self.controller.dg.record_start()])
        button2.grid(row=0, column=0)
        button3 = tk.Button(button_frame, text="Stop", command=lambda: self.controller.dg.record_stop())
        button3.grid(row=0, column=1)
        button_frame.grid(row=4, column=1)


def main():
    init_gui()


if __name__ == "__main__":
    main()
