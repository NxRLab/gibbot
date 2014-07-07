import serial
import time
import struct
import argparse

#Create an argument parser for command line interface
parser = argparse.ArgumentParser(description='Serial communication burst pass through test')
#Add arguments that can be passed through the command line
parser.add_argument('-v', '--verbose', action='store_true', help='Verbose output')
args = parser.parse_args()

#initialize serial port
ser = serial.Serial(2) #COM 3       7 -> COM 8
ser.baudrate = 115200  #set the baud rate
ser.timeout = 1        #1s timeout

x=0
fail=0
i=0
ser.write('a')
##Single Read/Write
while x < 256:
    senddata = chr(255-x)
    ser.write(senddata)
    
    while (ser.inWaiting != 1) & (i<100000):
        i=i+1
    i=0
    if ser.inWaiting()==1:
        received = ser.read(1)
        if senddata == received:
            if args.verbose == True:
                print "yes", hex(ord(received))   
        else:
            fail =1
            if args.verbose == True:
                print 'fail', hex(ord(received))
        x = x+1
    else:
        fail=1
        break

if fail == 0:
    print 'Completed pass through test'
else:
    print 'Pass through failed'
 
