import serial
import time
import struct
ser = serial.Serial(2) #COM 3       7 -> COM 8
ser.baudrate = 115200  #set the baud rate
ser.timeout = 1        #1s timeout
y = 0
while y<1:
    ser.write('b')
    time.sleep(.2)
    while (ser.inWaiting()<4):
        pass
    if (ser.inWaiting()>4):
        print ser.read(ser.inWaiting)
    else:
        received = ser.read(4)
        print struct.unpack('i', received)
    
