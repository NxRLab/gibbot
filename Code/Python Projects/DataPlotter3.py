import matplotlib
matplotlib.use('TkAgg')
import numpy as np
from matplotlib.lines import Line2D
from matplotlib.widgets import Cursor, Button
import matplotlib.pyplot as plt
import matplotlib.animation as animation
j =0
k =0
class Scope:
    def __init__(self, ax, maxt=10, dt=0.01):
        self.ax = ax[1]
        self.dt = dt
        self.maxt = maxt
        self.mint = 0 
        self.tdata = [0]
        self.ydata1 = [0.5]
        self.ydata2 = [0.5]
        self.arm1x = [3 , 3]
        self.arm1y = [.2 , .3]
        plt.subplots_adjust(bottom=0.2)
        self.line1 = Line2D(self.tdata, self.ydata1, color="red")
        self.line2 = Line2D(self.tdata, self.ydata2, color="blue")
        self.arm1 = Line2D(self.arm1x, self.arm1y, color="black", lw =5, solid_capstyle="round")
        self.ax.add_line(self.arm1)
        
        self.ax.add_line(self.line2)
        self.ax.add_line(self.line1)
        self.ax.set_ylim(-.1, 1.1)
        self.ax.set_xlim(self.mint, self.maxt)

    def update(self, y):
        global k
        t = self.tdata[-1] + self.dt
        if k<999:
            t = self.tdata[-1] + self.dt
            self.tdata.append(t)
            self.ydata1.append(y[0])
            self.ydata2.append(y[1])
            self.line1.set_data(self.tdata, self.ydata1)
            self.line2.set_data(self.tdata, self.ydata2)
            k=k+1
        else:
            self.tdata.pop(0)       #remove the first element
            self.tdata.append(t)    #add to the end
            
            self.ax.set_xlim(self.tdata[0], self.tdata[-1]) #adjust the x-axis
            self.ax.figure.canvas.draw()  #redraw

            self.ydata1.pop(0)
            self.ydata2.pop(0)             #remove the first element
            self.ydata1.append(y[0])
            self.ydata2.append(y[1])
            self.line1.set_data(self.tdata, self.ydata1)
            self.line2.set_data(self.tdata, self.ydata2)
        return [self.line1, self.line2]

def emitter(p=0.03):
    global j
    data1 = np.sin(j)/2 + .5
    data2 = np.cos(j)/2 + .5
    'return a random value with probability p, else 0'
    yield [data1, data2]
    j=j+.01

fig, ax = plt.subplots(ncols=2)
scope = Scope(ax)

# pass a generator in "emitter" to produce data for the update func
ani = animation.FuncAnimation(fig, scope.update, emitter, interval=10,
    blit=True)

plt.show()
