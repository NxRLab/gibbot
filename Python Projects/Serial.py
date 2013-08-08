import serial
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import matplotlib.animation as animation
ser = serial.Serial(2) #COM3     #COM 8 needs 7
print ser.portstr
ser.baudrate = 115200
#ser.timeout = 1  #1s timeout; use later
received = ser.read(9) #read 9 bytes

#print "string: ", received

encleftbit= ord(received[0]) <<8
encrightbit=ord(received[1])
encfinal=encleftbit|encrightbit
print "encoder: ", encfinal
i1leftbit= ord(received[2]) <<8
i1rightbit=ord(received[3])
i1final=i1leftbit|i1rightbit
print "i1: ", i1final
i2leftbit= ord(received[4]) <<8
i2rightbit=ord(received[5])
i2final=i2leftbit|i2rightbit
print "i2: ", i2final
i3leftbit= ord(received[6]) <<8
i3rightbit=ord(received[7])
i3final=i3leftbit|i3rightbit
print "i3: ", i3final
state=ord(received[8])
print "state: ", state

ser.close()
