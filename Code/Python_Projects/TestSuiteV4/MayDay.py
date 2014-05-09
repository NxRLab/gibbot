import serial
import struct
import re
import time
import numpy as np
from matplotlib.lines import Line2D
from matplotlib.widgets import CheckButtons, Button, Slider
import matplotlib.gridspec as gridspec
import matplotlib.pyplot as plt
import matplotlib.animation as animation
j =0
k =0
packsize = 20
xlim = 5
class Scope:
    def __init__(self, ax, dt=0.01):
        self.ax = ax
        self.dt = dt
        self.tdata = [0]
        self.ydata = [0]
        self.line = Line2D(self.tdata, self.ydata, color="red", label="Data1")
        self.ax.add_line(self.line)
        
    def update(self, y):
        global k
        t = list(np.linspace(self.tdata[-1]+self.dt,self.tdata[-1]+packsize*self.dt,packsize))
        if k<(xlim/self.dt/packsize):
            k=k+1
        else:
            pass
            del self.tdata[0:packsize]       #remove the first element
            del self.ydata[0:packsize]
            self.ax.set_xlim(self.tdata[0], self.tdata[-1]) #adjust the x-axis
        self.tdata=self.tdata+t    #add to the end
        self.ydata=self.ydata+y
        self.line.set_data(self.tdata, self.ydata)
        return self.line,
    
    def comm1(self, event):
        ser.write("q") #increase
        print "inc\r\n"
    def comm2(self, event):
        ser.write("w") #decrease
        print 'dec\r\n'
    def comm3(self, event):
        ser.write("a") #reverse
        print 'rev\r\n'
    def comm4(self, event):
        ser.write("b") #onoff
        print 'onoff\r\n'
    def comm5(self,event):
        ser.write("h") #onoff
        x=0
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
    def comm6(self,event):
        ser.write("u") #reset encoder
    def comm7(self,event):
        ser.write("i") #read encoder
        while(ser.inWaiting()<4):
            pass
        received = ser.read(4)
        print struct.unpack("l",received)
    def comm8(self,event):
        ser.write("m") #toggle magnet
        
    def sendTorque(self, val):
        num = int(round(val))
        cmd = 'm'+chr(num+192)  # Encode slider value [-63,+63] as a byte [129, 255]
        ser.write(cmd)
        print 'm'+str(num)

    def init(self):
        self.line.set_data([], [])
        return self.line,
    def close(self, event):
        plt.close()
        
def emitter():
    """Read the encoder, i1, i2, i3 and state from the dsPIC
    To read the encoder: leftbit takes received[1], rightbit takes received[0]
    To read i1: leftbit takes received[3], rightbit takes received[2]
    To read i2: leftbit takes received[5], rightbit takes received[4]
    To read i3: leftbit takes received[7], rightbit takes received[6]
    The state is in received[8]
    """
    output = [0]*packsize
    for inc in range(packsize):
        ser.write("z") #instruct the gibbot to start sending
        while(ser.inWaiting() < 2):
            pass
        received = ser.read(ser.inWaiting())
        leftbyte= ord(received[1]) <<8
        rightbyte=ord(received[0])
        output[inc] = float((leftbyte|rightbyte)-2048)*33/4096    #put reading together     
    print output[0]    
    yield output
    
#Create Figure 1
plt.close('all')                    #Close existing plots
fig, ax = plt.subplots()
scope = Scope(ax)
plt.subplots_adjust(left=0.2)

#mng = plt.get_current_fig_manager() #Resize to fullscreen
#mng.resize(*mng.window.maxsize())

#Format current and encoder axes
ax.set_xlim(0, xlim)
ax.set_ylim(-0.1, 6)

#Draw buttons
closeax = plt.axes([0.9, 0.25, 0.1, 0.1])
close = Button(closeax, 'Close')
close.on_clicked(scope.close)

comm1ax = plt.axes([0.1, 0.01, 0.1, 0.05])
comm1 = Button(comm1ax, 'Increase')
comm1.on_clicked(scope.comm1)
comm2ax = plt.axes([0.2, 0.01, 0.1, 0.05])
comm2 = Button(comm2ax, 'Decrease')
comm2.on_clicked(scope.comm2)
comm3ax = plt.axes([0.3, 0.01, 0.1, 0.05])
comm3 = Button(comm3ax, 'Reverse')
comm3.on_clicked(scope.comm3)
comm4ax = plt.axes([0.4, 0.01, 0.1, 0.05])
comm4 = Button(comm4ax, 'On/Off')
comm4.on_clicked(scope.comm4)
comm5ax = plt.axes([0.5, 0.01, 0.1, 0.05])
comm5 = Button(comm5ax, 'I2C')
comm5.on_clicked(scope.comm5)
comm6ax = plt.axes([0.6, 0.01, 0.1, 0.05])
comm6 = Button(comm6ax, 'Clear')
comm6.on_clicked(scope.comm6)
comm7ax = plt.axes([0.7, 0.01, 0.1, 0.05])
comm7 = Button(comm7ax, 'Read')
comm7.on_clicked(scope.comm7)
comm8ax = plt.axes([0.8, 0.01, 0.1, 0.05])
comm8 = Button(comm8ax, 'Magnet')
comm8.on_clicked(scope.comm8)


#Open serial port
ser = serial.Serial(2) #COM 3       7 -> COM 8
ser.baudrate = 115200  #set the baud rate
ser.timeout = 1        #1s timeout

# pass a generator in "emitter" to produce data for the update func
ani = animation.FuncAnimation(fig, scope.update, emitter, scope.init, interval=10,
    blit=True)

plt.show()
