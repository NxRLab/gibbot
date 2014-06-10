import serial
import time
import struct
import msvcrt
import argparse
import sys

#Create an argument parser for command line interface
parser = argparse.ArgumentParser(description='Encoder value read test. Default state is to display all three encoder outputs. To display only a single encoder use the following arguments. ')

parser.add_argument('-c', '--cont', action='store_true', help='Continuous output')
parser.add_argument('-t', '--top', action='store_true', help='Display only top encoder data')
parser.add_argument('-m', '--motor', action='store_true', help='Display only motor encoder data')
parser.add_argument('-b', '--bot', action='store_true', help='Display only bottom encoder data')
args = parser.parse_args()

#initialize serial port
ser = serial.Serial(2) #COM 3       7 -> COM 8
ser.baudrate = 115200  #set the baud rate
ser.timeout = 1        #1s timeout

ser.write('1') #Set encoder values
if args.cont == True:
    print 'Press any key to quit'

once = True
printed = False
inc = 0
while args.cont == True or once == True:
    once = False
    if msvcrt.kbhit():
        break
    ser.write('2') #Request encoder values
    time.sleep(.2)
    while (ser.inWaiting()<12 ):
        if msvcrt.kbhit():
            break
    if (ser.inWaiting()>12):
        print ser.read(ser.inWaiting)
    else:
        received = ser.read(12)
        results = struct.unpack('iii', received)
        if args.top:
            sys.stdout.write('Top: ' + str(results[2]) + ' ')
            printed = True
        if args.motor:
            sys.stdout.write('Mot: ' + str(results[1]) + ' ')
            printed = True
        if args.bot:
            sys.stdout.write('Low: ' + str(results[0]) + ' ')
            printed = True
        if printed == False:
            sys.stdout.write('Top: ' + str(results[2]) + ' Mot: ' + str(results[1]) + ' Bot: ' + str(results[0]))
        print ''
print 'Test complete'
