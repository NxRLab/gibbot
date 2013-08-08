import serial
import numpy as np
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import matplotlib.animation as animation

k=0
j=0

class Scope:
    def __init__(self, ax, maxt=0, dt=1):
        self.ax = ax
        self.dt = dt
        self.maxt = maxt        #starting endvalue of the x-axis
        self.mint = -150        #starting startvalue of the x-axis
        self.tdata = [0]*150    #initialize an empty 150-spot time array
        for x in range(1,151):  #fill the time array with values from -149 to 0
            self.tdata[x-1] = x-150
        self.ydata = [0]*150    #initialize an empty 150-spot data array
        self.line = Line2D(self.tdata, self.ydata)
        self.ax.add_line(self.line)
        self.ax.set_ylim(-0.1, 3600.1) #set the y-axis range
        self.ax.set_xlim(self.mint, self.maxt) #set the x-axis range
    def update(self, y):
        global j
        global k 
        if k>149:
            j=j+1
            self.tdata.pop(0)       #remove the first element
            self.tdata.append(j)    #add to the end
            
            self.ax.set_xlim(self.tdata[0], self.tdata[0] - self.mint) #adjust the x-axis
            self.ax.figure.canvas.draw()  #redraw

            self.ydata.pop(0)       #remove the first element
            self.ydata.append(y)    #add to the end

            self.line.set_data(self.tdata, self.ydata)
        else:     
            self.ax.figure.canvas.draw()
            self.ydata[k]=y
            self.line.set_data(self.tdata, self.ydata)
            k=k+1
        return self.line,



fig, ax = plt.subplots()
scope = Scope(ax)


ser = serial.Serial(2) #COM 3       7 -> COM 8
ser.baudrate = 230400  #set the baud rate
ser.timeout = 1        #1s timeout

def emitter():
    """Read the encoder, i1, i2, i3 and state from the dsPIC
    To read the encoder: leftbit takes received[1], rightbit takes received[0]
    To read i1: leftbit takes received[3], rightbit takes received[2]
    To read i2: leftbit takes received[5], rightbit takes received[4]
    To read i3: leftbit takes received[7], rightbit takes received[6]
    The state is in received[8]
    """
    ser.write("a")              #instruct the gibbot to start sending
    received = ser.read(10)     #read 9 info bytes and a tenth end-byte
    ser.write("q")              #isntruct the gibbot to stop sending
    leftbyte= ord(received[1]) <<8
    rightbyte=ord(received[0])
    final=leftbyte|rightbyte    #put reading together
    print "Value: ", final      #print reading
    yield final


#animator
ani = animation.FuncAnimation(fig, scope.update, emitter, interval=10,
    blit=True)

plt.show()      #show the plot
ser.close()     #close the COM port
