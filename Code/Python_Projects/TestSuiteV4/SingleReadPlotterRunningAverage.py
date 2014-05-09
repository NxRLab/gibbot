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
output2= []
avebin = 10
runave = []
runave2 = []

ser.write("a") #tell gibbot to read ADC for 3 seconds
for i in range(64):
    ser.write("b") #ask for 16 data points (32 bytes)
    while (ser.inWaiting() != 32):
        pass
    received = ser.read(ser.inWaiting());
    outputtup=struct.unpack( "HHHHHHHHHHHHHHHH", received)
    output= output + list(outputtup[0:16])
output2[:] = [float(x-2048)*33/4096 for x in output] #ADC counts * 3.3V/(4096counts * 0.1V/A )
s = 'StDev = ' +str(round(np.std(np.array(output2)),4))
m = 'Mean = ' + str(round(np.mean(np.array(output2)),4))

for i in range(len(output)-avebin):
    runave.append(float(sum(output[i:i+avebin]))/avebin)
print runave
runave2[:] = [float(x-2048)*33/4096 for x in runave]

s2 = 'StDev = ' +str(round(np.std(np.array(runave2)),4))
m2 = 'Mean = ' + str(round(np.mean(np.array(runave2)),4))

plt.figure(1)
plt.subplot(221)
plt.plot(output2)
plt.xlim(0, 1024)
plt.ylabel('Amps')
plt.subplots_adjust(bottom=0.2)
plt.xlabel('Max = ' + str(round(max(output2),3)) + 'A, Min = ' + str(round(min(output2),3)) +'A')
plt.ticklabel_format(useOffset=False)

plt.subplot(222)
n, bins, patches = plt.hist(output2, max(output)+1-min(output), alpha=0.75)
plt.xlabel('ADC Counts, '+s + ', ' + m)
plt.ticklabel_format(useOffset=False)

plt.subplot(223)
plt.plot(runave2)
plt.xlim(0, 1024-avebin)
plt.xlabel('Max = ' + str(round(max(runave),3)) + 'A, Min = ' + str(round(min(runave),3)) +'A')
plt.ticklabel_format(useOffset=False)

plt.subplot(224)
n, bins, patches = plt.hist(runave2, max(output)+1-min(output), alpha=0.75)
plt.xlabel('Amps, '+ s2 + ', ' + m2)
plt.ticklabel_format(useOffset=False)

plt.show()      #show the plot
ser.close()     #close the COM port
