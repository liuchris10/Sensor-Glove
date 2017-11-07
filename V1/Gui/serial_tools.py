import serial
import serial.tools.list_ports
import tkinter as tk


class SerialPort(object):
    def __init__(self):
        self.serial = serial.Serial()

    def select_port(self):
        popup_serial = tk.Toplevel()
        popup_serial.grab_set()
        popup_serial.geometry("500x500")
        popup_serial.wm_title("Serial Port Selection")
        label = tk.Label(popup_serial, text="Select Serial Port:")
        label.grid(row=0, column=0)

        port_com_num = 0
        port_name = "hello"
        port_baud_speed = "9600"

        port_list_frame = tk.Frame(popup_serial)
        port_list_frame.grid(row=0, column=0, sticky='ns')

        scrollbar = tk.Scrollbar(port_list_frame, orient="vertical")
        scrollbar.grid(row=1, column=0, rowspan=3, sticky="nsw")
        serial_list = tk.Listbox(port_list_frame, yscrollcommand=scrollbar.set)
        serial_list.config(yscrollcommand=scrollbar.set)
        scrollbar.config(command=serial_list.yview)
        serial_list.grid(row=1, column=1)

        ports = list(serial.tools.list_ports.comports())
        print(ports)
        for p in ports:
            # insert serial_list.insert(tk.END, ports(p))
            print(p)

        serial_list.insert(tk.END, "Hello")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")
        serial_list.insert(tk.END, "What's up")

        port_info_frame = tk.Frame(popup_serial)
        port_info_frame.grid(row=0, column=1, sticky='ns')

        port_info_title = tk.Label(port_info_frame, text="Com Port Information")
        port_info_title.grid(row=0, column=0)
        com_num_label = tk.Label(port_info_frame, text="COM Number:")
        com_num_label.grid(row=1, column=0)
        com_name_label = tk.Label(port_info_frame, text="COM Name:")
        com_name_label.grid(row=2, column=0)
        baud_rate_label = tk.Label(port_info_frame, text="Baud Rate:")
        baud_rate_label.grid(row=3, column=0)

        com_num_var = tk.StringVar(port_info_frame, value=port_com_num)
        com_num = tk.Label(port_info_frame, textvariable=com_num_var)
        com_num.grid(row=1, column=1)

        com_name_var = tk.StringVar(port_info_frame, value=port_name)
        com_name = tk.Label(port_info_frame, textvariable=com_name_var)
        com_name.grid(row=2, column=1)

        com_baud_var = tk.IntVar(port_info_frame, value=port_baud_speed)
        com_baud = tk.Label(port_info_frame, textvariable=com_baud_var)
        com_baud.grid(row=3, column=1)

        def port_list_select(event):
            selection_index = int(event.widget.curselection()[0])
            selection_value = event.widget.get(selection_index)
            com_num_var.set(selection_index)
            com_name_var.set(selection_value)
            com_baud_var.set(selection_index*15)

        serial_list.bind('<<ListboxSelect>>', port_list_select)

        b1 = tk.Button(popup_serial, text="Select this Serial Port", command=lambda: [self.open_serial_port(
            str(com_num_var.get()), int(com_baud_var.get())), popup_serial.destroy()])
        b1.grid(row=1, column=0)

        b2 = tk.Button(popup_serial, text="Cancel", command=popup_serial.destroy)
        b2.grid(row=1, column=1)

        popup_serial.mainloop()

    def open_serial_port(self, com_num, baud_rate):
        # self.serial.baudrate = baud_rate
        # self.serial.port = com_num
        # self.serial.open()
        print("Serial Port Open")

    def close_serial_port(self):
        # self.serial.close()
        print("Serial Port Closed")

    def flush_input(self):
        self.serial.flushInput()

    def input_buffer_length(self):
        byte_length = self.serial.inWaiting()
        return byte_length

    def read_8(self):
        return self.serial.read()

    def read_line(self):
        return self.serial.readline()

    def read_text(self):
        startbit = b's'
        endbit = b'\n'
        message = []
        while True:
            buffer = self.serial.read()
            if buffer == startbit:
                while buffer != endbit:
                    buffer = self.serial.read()
                    message.append(chr(buffer[0]))
                break
            else:
                self.serial.flushInput()
        message = message[:-1]
        string_buffer = ''.join(message)
        return string_buffer

    def text_to_decimal(self):
        return float(self.read_text())

    def wait(self):
        self.serial.inWaiting()

    def write_8(self, data):
        message = data.encode('utf-8')
        self.serial.write(message)

    def write_dec(self, data):
        if data > 256:
            m1 = str.encode(chr(data))
            self.serial.write(m1)
        else:
            m1 = str.encode(chr(0))
            m2 = str.encode(chr(data))
            self.serial.write(m1)
            self.serial.write(m2)

    def read_num(self):
        temp_a = self.serial.read()
        number = ord(temp_a)
        return number

    def read_dec(self):
        temp_a = self.serial.read()
        temp_b = self.serial.read()
        temp_c = (temp_b[0] << 8) | temp_a[0]
        return temp_c

    def read_32(self):
        temp_a = self.serial.read()
        temp_b = self.serial.read()
        temp_c = self.serial.read()
        temp_d = self.serial.read()
        value = (temp_d[0] << 24) | (temp_c[0] << 16) | (temp_b[0] << 8) | temp_a[0]
        print(value)

    def print_sensor(self):
        temp_a = self.serial.read()
        temp_b = self.serial.read()
        sensor = (temp_b[0] << 8) | temp_a[0]
        print('Sensor Value: {:f}'.format(sensor))

    def read_hex(self):
        temp_a = self.serial.read()
        temp_b = self.serial.read()
        temp_c = (temp_b[0] << 8) | temp_a[0]
        temp_a = hex(temp_c)
        return temp_a

    def print_32(self):
        temp_a = self.read_8()
        temp_b = self.read_8()
        temp_c = self.read_8()
        temp_d = self.read_8()
        temp_e = (temp_b[0] << 8) | temp_a[0]
        temp_f = (temp_c[0] << 8) | temp_d[0]
        print(temp_e)
        print(temp_f)

    def print_id(self):
        device_id = self.read_hex()
        print('Device ID: ' + repr(device_id))

    def print_voltage(self):
        analog = self.read_dec()
        voltage = (analog/1024 * 5)
        print('Voltage: {:f}'.format(voltage))

    @staticmethod
    def print_name():
        print("Huggie!")
