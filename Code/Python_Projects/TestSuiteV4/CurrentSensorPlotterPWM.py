import serial
import struct
import time
import numpy as np
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import pylab

ser = serial.Serial(2) #COM 3       7 -> COM 8
ser.baudrate = 115200  #set the baud rate
ser.timeout = 1        #1s timeout
output = []
output2 = []
output3 = []
output4 = []

avebin = 10
runave = []
runave2 = []


ser.write("r") #tell gibbot to read ADC for 3 seconds
for i in range(64):
    ser.write("t") #ask for 16 data points (32 bytes)
    while (ser.inWaiting() != 32):
        pass
    received = ser.read(ser.inWaiting());
    outputtup=struct.unpack( "HHHHHHHHHHHHHHHH", received)
    output= output + list(outputtup[0:16])
output2[:] = [float(x-2048)*33/4096 for x in output] #ADC counts * 3.3V/(4096counts * 0.1V/A )
s = 'StDev = ' +str(round(np.std(np.array(output2)),4))
m =  'Mean = ' + str(round(np.mean(np.array(output2)),4))

ser.write("e") #turn motor on
time.sleep(1) #Wait for motor to settle
for i in range(4):
    ser.write("u") #increase speed
    time.sleep(.5) #Wait for motor to settle
    received = ser.read(ser.inWaiting());
    outputtup=struct.unpack("H", received)
    print str(int(outputtup[0])/10) + '%'

ser.write("r") #tell gibbot to read ADC for 3 seconds
for i in range(64):
    ser.write("t") #ask for 16 data points (32 bytes)
    while (ser.inWaiting() != 32):
        pass
    received = ser.read(ser.inWaiting());
    outputtup=struct.unpack( "HHHHHHHHHHHHHHHH", received)
    output3= output3 + list(outputtup[0:16])
output4[:] = [float(x-2048)*33/4096 for x in output3] #ADC counts * 3.3V/(4096counts * 0.1V/A )
s2 = 'StDev = ' +str(round(np.std(np.array(output4)),4))
m2 =  'Mean = ' + str(round(np.mean(np.array(output4)),4))

ser.write("y") #turn off motor
plt.figure(1)
plt.subplot(221)
plt.plot(output2,'|')
plt.xlim(0, 1024)
plt.ylabel('Amps')
plt.subplots_adjust(bottom=0.2)
plt.xlabel('Max = ' + str(round(max(output2),3)) + 'A, Min = ' + str(round(min(output2),3)) +'A')
plt.ticklabel_format(useOffset=False)

plt.subplot(222)
n, bins, patches = plt.hist(output,1+max(output)-min(output), alpha=0.75)
plt.xlabel('ADC Counts, '+s + ', ' + m)
plt.ticklabel_format(useOffset=False)

plt.subplot(223)
plt.plot(output4,'|')
plt.xlim(0, 1024)
plt.ylabel('Amps')
plt.subplots_adjust(bottom=0.2)
plt.xlabel('Max = ' + str(round(max(output4),3)) + 'A, Min = ' + str(round(min(output4),3)) +'A')
plt.ticklabel_format(useOffset=False)

plt.subplot(224)
n, bins, patches = plt.hist(output3, max(output3)+1-min(output3), alpha=0.75)
plt.xlabel('ADC Counts, '+ s2 + ', ' + m2)
plt.ticklabel_format(useOffset=False)

plt.show()      #show the plot
ser.close()     #close the COM port
