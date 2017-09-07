import serial_1 as sp1
import string
def main():
    while 1:
        try:
            number1 = sp1.read_8()
            if number1 == b's':
                print(number1)
                number3 = sp1.read_dec()
                print(number3)
                number4 = sp1.read_dec()
                print(number4)
                number5 = sp1.read_dec()
                print(number5)
            else:
                sp1.flush_input()
            # number5 = sp1.read_8()
            # print(number5)
            # number6 = sp1.read_8()
            # print(number6)
            # number7 = sp1.read_dec()
            # print(number7)

            #print(sp1.text_to_decimal())

        except sp1.SerialTimeoutException:
            print('Data could not be read')


if __name__ == "__main__":
    main()

