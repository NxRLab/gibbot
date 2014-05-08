import serial
import time
import struct
ser = serial.Serial(2) #COM 3       7 -> COM 8
ser.baudrate = 115200  #set the baud rate
ser.timeout = 1        #1s timeout

x=0
##Single Read/Write
while x < 256:
    senddata = chr(255-x)
    ser.write(senddata) 
    received = ser.read(1)
    if senddata == received:
        print "yes", hex(ord(received))
    else:
        print "fail"
        break
    x = x+1

####Burst Read/Write
##numbbytes = 256
##while x < numbbytes:
##    senddata = chr(x)
##    ser.write(senddata)
##    x = x+1;
##x = 0
##time.sleep(1)
##print ser.inWaiting() 
##received = ser.read(numbbytes)
##while x < numbbytes:
##    if received[x] == chr(x):
##        print "yes", hex(x)
##    else:
##        print "fail", hex(ord(received[x]))
##    x = x+1
##    

