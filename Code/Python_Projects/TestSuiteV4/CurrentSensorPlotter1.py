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

ser.write("l") #tell gibbot to read ADC for 1 second
for i in range(64):
    ser.write("m") #ask for 16 data points (32 bytes)
    while (ser.inWaiting() != 32):
        pass
    received = ser.read(ser.inWaiting());
    outputtup=struct.unpack( "HHHHHHHHHHHHHHHH", received)
    output= output + list(outputtup[0:16])
    """The way the current sensor is setup on the V5 PCB, increasing the
    current will result in a decreasing voltage to the ADC.  Additionally,
    the V5 PCB had an offset in the ADC count such that at 0A it was reading
    in the range of .086-.095A or the 8mA/ADC count resolution of the dsPIC ADC.
    The .09 negates the offset.
    """
output2[:] = [(float(2048-x)*33/4096)+.07 for x in output] #ADC counts * 3.3V/(4096counts * 0.1V/A )
s = 'StDev = ' +str(round(np.std(np.array(output2)),4))
m =  'Mean = ' + str(round(np.mean(np.array(output2)),4))

plt.figure(1)
plt.subplot(121)
plt.plot(output2,'|')
plt.xlim(0, 1024)
plt.xlabel('')
plt.ylabel('Amps')
plt.subplots_adjust(bottom=0.2)
plt.xlabel('Time (ms) \n \n Max = ' + str(round(max(output2),3)) + 'A, Min = ' + str(round(min(output2),3)) +'A')
plt.ticklabel_format(useOffset=False)

plt.subplot(122)
n, bins, patches = plt.hist(output2,1+max(output)-min(output), alpha=0.75)
plt.xlabel('Amps, '+s + ', ' + m)
plt.ticklabel_format(useOffset=False)

plt.show()      #show the plot
ser.close()     #close the COM port
