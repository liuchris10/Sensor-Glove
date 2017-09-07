import serial_1 as sp1
import string
def main():
    sp1.write_8('p')
    sp1.write_8('n')
    num_s = 3
    sp1.write_dec(num_s)
    sp1.write_dec(1)
    sp1.write_dec(2)
    sp1.write_dec(3)
    sp1.write_8('c')
    sp1.write_8('v')
    for x in range(1,6):
        digit1 = sp1.read_8()
        print(digit1)
        for y in range(0, num_s):
            number3 = sp1.read_dec()
            print(number3)
        print(sp1.read_8())

    sp1.write_8('z')
    for x in range(1,6):
        digit1 = sp1.read_8()
        print(digit1)
        number3 = sp1.read_dec()
        print(number3)
        number4 = sp1.read_dec()
        print(number4)
        number5 = sp1.read_dec()
        print(number5)


if __name__ == "__main__":
    main()