import serial_1 as sp1

def main():
    while 1:
        try:
            number1 = sp1.read_8()
            print(number1)
            number2 = sp1.read_dec()
            print(number2)
        except sp1.SerialTimeoutException:
            print('Data could not be read')


if __name__ == "__main__":
    main()

