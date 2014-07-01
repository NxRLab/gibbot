import serial
import time
import struct
import argparse

#Create an argument parser for command line interface
parser = argparse.ArgumentParser(description='Serial communication burst pass through test')

parser.add_argument('-v', '--verbose', action='store_true', help='Verbose output')
args = parser.parse_args()

ser = serial.Serial(2) #COM 3       7 -> COM 8
ser.baudrate = 115200  #set the baud rate
ser.timeout = 1        #1s timeout

x=0
fail=0

ser.write('b')
####Burst Read/Write
numbbytes = 256
while x < numbbytes:
    senddata = chr(x)
    ser.write(senddata)
    x = x+1;
x = 0
time.sleep(1)
if ser.inWaiting() == numbbytes:    
    received = ser.read(numbbytes)
    while x < numbbytes:
        if received[x] == chr(x):
            if args.verbose == True:
                print 'yes', hex(x)
        else:
            fail =1
            if args.verbose == True:
                print 'Burst Pass Through Failed', hex(ord(received[x]))
        x = x+1
else:
    fail = 1
    
if fail == 0:
    print 'Completed burst pass through test'
else:
    print 'Burst pass through failed'
    
ser.close()
