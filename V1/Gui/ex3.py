import serial_tools
import string
def main():
    sp1 = serial_tools.SerialPort()
    sp1.serial.baudrate = "9600"
    sp1.serial.port = "COM7"
    sp1.serial.open()
    sp1.write_8('p')
    sp1.write_8('n')
    num_s = 5
    sp1.write_dec(num_s)
    sp1.write_dec(1)
    sp1.write_dec(2)
    sp1.write_dec(3)
    sp1.write_dec(4)
    sp1.write_dec(5)
    sp1.write_8('c')
    sp1.write_8('v')
    x = 1
    while x < 7:
        startbit = b's'
        buffer = sp1.read_8()
        print(buffer)
        if buffer == startbit:
            for y in range(0, num_s):
                number3 = sp1.read_dec()
                print(number3)
            x = x + 1
        else:
            sp1.flush_input()

    sp1.write_8('z')


if __name__ == "__main__":
    main()