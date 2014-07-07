import serial
import time
import struct
import msvcrt
import sys

ser = serial.Serial(2) #COM 3       7 -> COM 8
ser.baudrate = 115200  #set the baud rate
ser.timeout = 1        #1s timeout
y=0
#clear encoder
ser.write('94Q1') #Turn on motor at minimum duty cycle
time.sleep(.1)
ser.write('j') #kick motor
while y <1:
    ##Ramp up
    ser.write('8')
    time.sleep(1)
    if msvcrt.kbhit():
        break
    ##Read ADC
    ser.write('0')
    while (ser.inWaiting()<2):
       if msvcrt.kbhit():
           fail = True
           break
    if (ser.inWaiting()>2):
        print ser.read(ser.inWaiting)
    else:
        received = ser.read(2)
        results = struct.unpack('H', received)
        output = round(float(results[0]-2048)*33/4096,4)
        print 'High Current: ' + str(output) + 'A'
    time.sleep(1)           
    if msvcrt.kbhit():
        break
    ##Ramp down
    ser.write('9')
    time.sleep(2)
    if msvcrt.kbhit():
        break

    ##Read ADC
    ser.write('0')
    while (ser.inWaiting()<2):
       if msvcrt.kbhit():
           fail = True
           break
    if (ser.inWaiting()>2):
        print ser.read(ser.inWaiting)
    else:
        received = ser.read(2)
        results = struct.unpack('H', received)
        output = round(float(results[0]-2048)*33/4096,4)
        print 'Low Current:  ' + str(output) + 'A'

        
    ##read encoder
    ser.write('2')
    while (ser.inWaiting()<12):
       if msvcrt.kbhit():
           fail = True
           break
    if (ser.inWaiting()>12):
        print ser.read(ser.inWaiting)
    else:
        received = ser.read(12)
        results = struct.unpack('iii', received)
        print 'Top: ' + str(results[2]) + ' Mot: ' + str(results[1]) + ' Bot: ' + str(results[0])

    ##toggle Magnet
    ser.write('cf')
    if msvcrt.kbhit():
        break

    time.sleep(1)
    if msvcrt.kbhit():
        break
    
ser.write('95')  
ser.close()
