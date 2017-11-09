from openpyxl import Workbook, load_workbook
import time
from tkinter.filedialog import askopenfilename, askdirectory
import tkinter as tk
from matplotlib.figure import Figure
import matplotlib.animation as animation


class DataGraph(object):
    def __init__(self, master, serial_port):
        self.master = master
        self.serial = serial_port
        #  See if I need a subplot to properly graph Live Data
        self.start_time = 0
        self.stop_time = 0
        self.record = 0  # Can Start Recording Data
        self.popup_enable = 0 # Popup Can be Shown
        self.sensors_switch = [0] * 24
        self.sensors_pressure = [[0 for x in range(1)] for y in range(1)]  # 2D Array of Sensor Pressure Values
        self.avail_sensors = []  # Initializing an Array of Possible Available Sensors
        self.seconds = [0]  # Time Since Data has been Captured
        self.num_sensors = 0
        self.calibration_filename = '_'
        self.sensitivity_filename = '_'
        self.destination_folder = '_'
        self.destination_filename = '_'
        self.calibration_values = [40000] * 24  # Calibration values of the CDC value when no pressure Applied
        self.sensitivity_values = [0] * 24  # Sensitivity of Capacitive Sensor (Pa/pf)

        self.live_plot_figure = Figure(figsize=(5, 5), dpi=100, tight_layout=True)
        self.a = self.live_plot_figure.add_subplot(1, 1, 1)

    def animate_graph(self, graph_frame):
        self.ani1 = animation.FuncAnimation(graph_frame, self.record_data, interval=100)

    def update_checkbox_sensors(self, s_toggle):
        self.avail_sensors = []
        if self.sensors_switch[s_toggle-1] == 0:
            self.sensors_switch[s_toggle-1] = 1
        else:
            self.sensors_switch[s_toggle-1] = 0
        for i in range(0, len(self.sensors_switch)):
            if self.sensors_switch[i] == 1:
                self.avail_sensors.append(i+1)
        self.num_sensors = len(self.avail_sensors)

    def record_start(self):
        if self.record == 0:
            self.serial.flush_input()
            self.sensors_pressure = [[0 for x in range(1)] for y in range(self.num_sensors)]
            self.serial.write_8('p')
            self.serial.write_8('n')
            self.serial.write_dec(self.num_sensors)
            for x in range(0, self.num_sensors):
                self.serial.write_dec(self.avail_sensors[x])
            self.serial.write_8('c')
            self.serial.write_8('v')
            self.record = 1
            self.start_time = time.time()

    def record_stop(self):
        if self.record == 1:
            self.record = 0
            self.popup_enable = 1
            self.serial.write_8('z')
            self.start_time = 0

    @staticmethod
    def quit_gui():
        quit()

    @staticmethod
    def print_name():
            print("Carl!")

    def ask_user_file(self, file_show):
        self.sensitivity_filename = askopenfilename()
        file_show.delete(0, tk.END)
        file_show.insert(0, self.sensitivity_filename)

    def ask_user_output_folder(self, folder_show):
        self.destination_filename = askdirectory()
        folder_show.delete(0, tk.END)
        folder_show.insert(0, self.destination_filename)

    def get_sensitivity(self):
        popup_sensitivity = tk.Toplevel()
        popup_sensitivity.grab_set()
        popup_sensitivity.geometry("1000x100")
        popup_sensitivity.wm_title("sensitivity Excel Data")
        label = tk.Label(popup_sensitivity, text="Select the sensitivity File For A Given Glove:")
        label.grid(row=0, column=0)

        b3 = tk.Button(popup_sensitivity, text="Browse:", command=lambda: self.ask_user_file(file_show))
        b3.grid(row=1, column=0)

        sensitivity_filename_string_var = tk.StringVar(popup_sensitivity, value=self.sensitivity_filename)
        file_show = tk.Entry(popup_sensitivity, textvariable=sensitivity_filename_string_var, width=150)
        file_show.grid(row=1, column=1)

        b1 = tk.Button(popup_sensitivity, text="Select Excel", command=lambda: [popup_sensitivity.destroy(), self.load_sensitivity(sensitivity_filename_string_var),
                                                                                popup_sensitivity.grab_release()])
        b1.grid(row=2, column=0)

        b2 = tk.Button(popup_sensitivity, text="Cancel", command=popup_sensitivity.destroy)
        b2.grid(row=2, column=1)

        popup_sensitivity.mainloop()

    def output_folder_popup(self):
        if self.popup_enable == 1:
            popup_output = tk.Toplevel()
            popup_output.grab_set()
            popup_output.geometry("1000x100")
            popup_output.wm_title("Select Output Folder to Save Data")
            label = tk.Label(popup_output, text="Output Folder:")
            label.grid(row=0, column=0)

            b4 = tk.Button(popup_output, text="Browse:", command=lambda:
                           self.ask_user_output_folder(folder_show))
            b4.grid(row=1, column=0)

            excel_folder_string_var = tk.StringVar(popup_output, value=self.destination_folder)
            folder_show = tk.Entry(popup_output, textvariable=excel_folder_string_var, width=150)
            folder_show.grid(row=1, column=1)

            label_file_name = tk.Label(popup_output, text="File Name:")
            label_file_name.grid(row=2, column=0)

            excel_file_string_var = tk.StringVar(popup_output, value=self.destination_filename)
            file_name_show = tk.Entry(popup_output, textvariable=excel_file_string_var, width=150)
            file_name_show.grid(row=2, column=1)

            b1 = tk.Button(popup_output, text="Save Excel File", command=lambda:
                           [self.save_data(str(excel_folder_string_var.get()) + '/' + str(excel_file_string_var.get()) +
                                           '.xlsx'), popup_output.destroy()])
            b1.grid(row=3, column=0)

            b2 = tk.Button(popup_output, text="Cancel", command=popup_output.destroy)
            b2.grid(row=3, column=1)

            self.popup_enable = 0
            popup_output.mainloop()

    def load_sensitivity(self, sensitivity_file_name):
        sensitivity_file = str(sensitivity_file_name.get())
        wb = load_workbook(sensitivity_file)
        ws_name = wb.get_sheet_names()[0]
        ws = wb.get_sheet_by_name(ws_name)

        for n in range(2, ws.max_row):
            if ws.cell(row=n, column=2).value != 0:
                self.sensitivity_values[n-2] = ws.cell(row=n, column=2).value
                self.avail_sensors.append(n-1)

    def calibrate_glove(self):
        print("Feature to be Added Soon!")

    def save_data(self, output_excel):
        print("Saved")
        self.destination_filename = output_excel
        wb = Workbook()
        ws = wb.active
        ws.title = "Sample #1"
        ws.cell(row=1, column=1, value="Time (s)")
        for k in range(0, self.num_sensors):
            title = "Sensor " + str(k) + ": (Pa)"
            ws.cell(row=1, column=2+k, value=title)
        # Storing the values in rows
        for i in range(1, len(self.seconds)):
            ws.cell(row=i + 1, column=1, value=self.seconds[i-1])
            for j in range(0, self.num_sensors):
                ws.cell(row=i + 1, column=2 + j, value=self.sensors_pressure[j][i-1])
        # Saving the Excel File
        wb.save(filename=self.destination_filename)
        self.sensors_pressure = [[0 for x in range(1)] for y in range(self.num_sensors)]  # Reinitializing Pressure from Sensor Array
        self.seconds = [0]  # Reinitializing Seconds Array

    def update_single_fig(self):
        self.a.clear()
        self.a.set_title("Individual Sensor Readout")  # Setting the Title of the Graph
        self.a.set_ylabel("Pressure (Psi)")  # Set ylabels to Pressure in Psi
        self.a.set_xlabel("Time (s)")  # Set xlabel to Time in Seconds

        # only show 20 seconds worth of data
        if self.seconds[-1] < 20:
            self.a.set_xlim([0, 20])
        else:
            time_low = self.seconds[-1] - 20
            self.a.set_xlim([time_low, self.seconds[-1]])

        # Setting the Y limit to show PSI from 0 - 5 psi
        self.a.set_ylim([0, 20])
        self.a.ticklabel_format(useOffset=False)

    @staticmethod
    def update_total_fig():
        print('Hello')

    def record_data(self, i):
        # start data collection
        startbit = b's'
        if self.record == 1:
            while self.serial.wait() == 0:
                pass
            while True:
                buffer = self.serial.read_8()
                if buffer == startbit:
                    for n in range(0, self.num_sensors):
                        temp1 = self.serial.read_dec()
                        print(temp1)
                        temp3 = (temp1 - self.calibration_values[self.avail_sensors[n]]) / (65535 - self.calibration_values[self.avail_sensors[n]]) * self.sensitivity_values[n]
                        self.sensors_pressure[n].append(temp3)  # Storing values in Larger Data Array
                    self.serial.flush_input()
                    break
                else:
                    self.serial.flush_input()

            count = time.time() - self.start_time
            self.seconds.append(count)

            self.update_single_fig()
            self.a.plot(self.seconds, self.sensors_pressure[0], self.seconds, self.sensors_pressure[1], self.seconds, self.sensors_pressure[2])
