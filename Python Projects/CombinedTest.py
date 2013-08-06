import serial
import numpy as np
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import matplotlib.animation as animation

#ser.timeout = 1  #1s timeout; use later

class Scope:
    def __init__(self, ax, maxt=20, dt=0.02):
        self.ax = ax
        self.dt = dt
        self.maxt = maxt
        self.tdata = [0]
        self.ydata = [0]
        self.line = Line2D(self.tdata, self.ydata)
        self.ax.add_line(self.line)
        self.ax.set_ylim(-.1, 70000.1)
        self.ax.set_xlim(0, self.maxt)

    def update(self, y):
        lastt = self.tdata[-1]
        if lastt > self.tdata[0] + self.maxt: # reset the arrays
            self.tdata = [self.tdata[-1]]
            self.ydata = [self.ydata[-1]]
            self.ax.set_xlim(self.tdata[0], self.tdata[0] + self.maxt)
            self.ax.figure.canvas.draw()

        t = self.tdata[-1] + self.dt
        self.tdata.append(t)
        self.ydata.append(y)
        self.line.set_data(self.tdata, self.ydata)
        return self.line,


def emitter(p=0.05):
    'return a random value with probability p, else 0'
    ser = serial.Serial(7) #COM 8
    ser.baudrate = 115200
    for x in range (0,100):#while True: #it will repeat the for loop
        received = ser.read(2)
        i1leftbit= ord(received[0]) <<8
        i1rightbit=ord(received[1])
        i1final=i1leftbit|i1rightbit
        print x
        #i1final=500+100*np.random.rand(1)
        print i1final
        #if (i1final==0):#65535):
        #    ser.close()
        #    #quit()
        #    yield 500+100*np.random.rand(1)
        yield i1final# 500+100*np.random.rand(1)
    ser.close()

fig, ax = plt.subplots()
scope = Scope(ax)

# pass a generator in "emitter" to produce data for the update func
ani = animation.FuncAnimation(fig, scope.update, emitter, interval=10,
    blit=True)

plt.show()

ser.close()
