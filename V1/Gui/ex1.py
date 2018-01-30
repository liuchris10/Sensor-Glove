import serial
import string
def main():
    ser = serial.Serial()
    ser.baudrate = 115200
    ser.port = 'COM10'
    ser.open()

    while 1:
        try:
            number1 = ser.read()
            print(number1)

        except serial.SerialTimeoutException:
            print('Data could not be read')


if __name__ == "__main__":
    main()

