import serial
import numpy as np
from matplotlib.lines import Line2D
from matplotlib.widgets import CheckButtons, Button
import matplotlib.gridspec as gridspec
import matplotlib.pyplot as plt
import matplotlib.animation as animation
j =0
k =0
class Scope:
    def __init__(self, ax, dt=0.01):
        self.ax = ax[1]
        self.ax2 = ax[0]
        self.ax3 = ax[2]
        self.dt = dt
        self.arm1x = [0 , .5]
        self.arm1y = [0 , .5]
        self.arm2x = [0 , 0]
        self.arm2y = [0 , .5]
        self.tdata = [0]
        self.ydata1 = [1700]
        self.ydata2 = [1700]        
        self.arm1 = Line2D(self.arm1x, self.arm1y, color="purple", lw="18", solid_capstyle="round", marker="o", markerfacecolor="black", markersize=20)
        self.arm2 = Line2D(self.arm2x, self.arm2y, color="purple", lw="18", solid_capstyle="round", marker="o", markerfacecolor="black", markersize=20)
        self.ax2.add_line(self.arm1)
        self.ax2.add_line(self.arm2)


        self.line1 = Line2D(self.tdata, self.ydata1, color="red", label="Data1")
        self.line2 = Line2D(self.tdata, self.ydata2, color="blue", label="Data2")
        self.ax.add_line(self.line1)
        self.ax3.add_line(self.line2)       
        
    def update(self, y):
        global k
        t = self.tdata[-1] + self.dt
        
        if k<799:
            k=k+1
        else:
            self.tdata.pop(0)       #remove the first element
            self.ydata1.pop(0)
            self.ydata2.pop(0)             #remove the first element
            self.ax.set_xlim(self.tdata[0], self.tdata[-1]) #adjust the x-axis
            
        
        self.arm1.set_data([0, -np.sin(((y[0]-1800)*3.14)/1800)*.5],[0, -np.cos(((y[0]-1800)*3.14)/1800)*.5])
        self.tdata.append(t)    #add to the end
        self.ydata1.append(y[0])
        self.ydata2.append(y[1])
        self.line1.set_data(self.tdata, self.ydata1)
        self.line2.set_data(self.tdata, self.ydata2)
        return self.line1, self.line2, self.arm1
    
    def comm1(self, event):
        ser.write("o")
    def comm2(self, event):
        ser.write("p")
    def comm3(self, event):
        ser.write("w")
    def comm4(self, event):
        ser.write("q")

    def init(self):
        self.line1.set_data([], [])
        self.line2.set_data([], [])
        self.arm1.set_data([], [])
        return self.line1, self.line2, self.arm1
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
    output = [0]*10
    ser.write("o")              #instruct the gibbot to start sending
    received = ser.read(10)     #read 9 info bytes and a tenth end-byte
    ser.write("p")              #isntruct the gibbot to stop sending
    output[0]=(ord(received[1]) <<8)| ord(received[0])   #put reading together
    output[1]=(ord(received[3]) <<8)| ord(received[2])
    output[2]=(ord(received[5]) <<8)| ord(received[4])
    output[3]=(ord(received[7]) <<8)| ord(received[6])
    yield output

def func(label):
    if label == 'Data1': scope.line1.set_visible(not scope.line1.get_visible())
    elif label == 'Data2': scope.line2.set_visible(not scope.line2.get_visible())

#Create Figure 1
plt.close('all')                    #Close existing plots
fig = plt.figure()                  #Create figure
mng = plt.get_current_fig_manager() #Resize to fullscreen
mng.resize(*mng.window.maxsize())

#Create axes
ax = [0]*3  #define array that contains the names of each axes
#Create axis for gibbot animation using gridspec for more layout flexibility
gs1 = gridspec.GridSpec(1,1)                            
gs1.update(left=0.0, right=0.25, bottom=.12)
ax[0] = plt.subplot(gs1[0, 0], aspect="equal", axisbg='.75', frameon=False)

#Create axes for current and encoder plots
gs2 = gridspec.GridSpec(2,1)
gs2.update(left=0.25, right=0.85, bottom=.12, hspace=0.01)
ax[1] = plt.subplot(gs2[0, 0])
ax[2] = plt.subplot(gs2[1, 0], sharex=ax[1])

#Format gibbot animation axis
ax[0].set_xlim(-.7, .7)
ax[0].set_ylim(-.7, .7)
ax[0].get_xaxis().set_visible(False)
ax[0].get_yaxis().set_visible(False)

#Format current and encoder axes
ax[1].set_ylim(0,3600)
ax[1].set_xlim(0, 8)
ax[2].set_ylim(0, 1024)

#Create scope object
scope = Scope(ax)

#Draw legend
fig.legend([scope.line1, scope.line2], ['Encoder', 'Current'])

#Draw buttons
checkax = plt.axes([0.9, 0.4, 0.1, 0.15])
check = CheckButtons(checkax, ('Data1', 'Data2'), (True, True))
check.lines[0][0].set_color("Red")
check.lines[0][1].set_color("Red")
check.lines[1][0].set_color("Blue")
check.lines[1][1].set_color("Blue")
check.on_clicked(func)

closeax = plt.axes([0.9, 0.25, 0.1, 0.1])
close = Button(closeax, 'Close')
close.on_clicked(scope.close)

comm1ax = plt.axes([0.1, 0.01, 0.1, 0.05])
comm1 = Button(comm1ax, 'Data On')
comm1.on_clicked(scope.comm1)
comm2ax = plt.axes([0.2, 0.01, 0.1, 0.05])
comm2 = Button(comm2ax, 'Data off')
comm2.on_clicked(scope.comm2)
comm3ax = plt.axes([0.3, 0.01, 0.1, 0.05])
comm3 = Button(comm3ax, 'Swing')
comm3.on_clicked(scope.comm3)
comm4ax = plt.axes([0.4, 0.01, 0.1, 0.05])
comm4 = Button(comm4ax, 'Stop')
comm4.on_clicked(scope.comm4)

#Open serial port
ser = serial.Serial(2) #COM 3       7 -> COM 8
ser.baudrate = 230400  #set the baud rate
ser.timeout = 1        #1s timeout

# pass a generator in "emitter" to produce data for the update func
ani = animation.FuncAnimation(fig, scope.update, emitter, scope.init, interval=10,
    blit=True)

plt.show()
