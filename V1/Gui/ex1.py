import serial_1 as sp1
import gui

def main():
    #sp1.print_ID()
     # while 1:
     #     try:
     #        indicator = sp1.read_8()
     #        if indicator == b'v':
     #           sp1.print_Voltage()
     #        if indicator == b'i':
     #           sp1.print_ID(sp1)
     #        if indicator == b's':
     #           sp1.print_Sensor()
     #        if indicator == b'f':
     #           idea = sp1.read_dec()
     #           print(idea)
     #        if indicator == b'h':
     #           idea1 = hex(sp1.read_dec()-57344)
     #           print(idea1)
     #
     #     except sp1.SerialTimeoutException:
     #            print('Data could not be read')

    gui.init_gui()

if __name__ == "__main__":
    main()

