import serial
import time
import struct
ser = serial.Serial(2) #COM 3       7 -> COM 8
ser.baudrate = 115200  #set the baud rate
ser.timeout = 1        #1s timeout
y=0
#clear encoder
ser.write('wwub')
while y <1:
    ##Ramp up
    ser.write('1')
    time.sleep(2)
    ##Ramp down
    ser.write('2')
    time.sleep(2)
    ##read encoder
    ser.write('i')
    while (ser.inWaiting() < 4):
        pass
    received = ser.read(ser.inWaiting());
    print 'Encoder= ' + str(list(struct.unpack( "l", received)))

    ##toggle Magnet
    ser.write('m')
    time.sleep(1)
    
    

##    ####Single Read/Write
##    ser.write('h')
##    x=0
##    while x < 256:
##        senddata = chr(255-x)
##        ser.write(senddata) 
##        received = ser.read(1)
##        if senddata == received:
##            pass
##            #print "yes", hex(ord(received))
##        else:
##            print "fail"
##            break
##        x = x+1
##    print 'Read Pass'
##    x=0
##    ser.write('k') 
##    ##Burst Read/Write
##    numbbytes = 256
##    while x < numbbytes:
##        senddata = chr(x)
##        ser.write(senddata)
##        x = x+1;
##    x = 0
##    time.sleep(1)
##    print ser.inWaiting() 
##    received = ser.read(numbbytes)
##    while x < numbbytes:
##        if received[x] == chr(x):
##            pass
##            #print "burst", hex(x)
##        else:
##            print 'fail', hex(ord(received[x]))
##        x = x+1
##    print 'Burst Read Pass'

    ##read ADC
    ser.write('z')
    while (ser.inWaiting <2):
        pass
    received = ser.read(2);
    print 'ADC = ' + str(struct.unpack("H", received))
    print ser.read(ser.inWaiting())
    ser.write('a')

ser.close()
