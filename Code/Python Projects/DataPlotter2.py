import matplotlib
matplotlib.use('TkAgg')
import numpy as np
from matplotlib.lines import Line2D
from matplotlib.widgets import CheckButtons, Button
import matplotlib.gridspec as gridspec
import matplotlib.pyplot as plt
import matplotlib.animation as animation
j =0
k =0
class Scope:
    def __init__(self, ax, maxt=10, dt=0.01):
        self.ax = ax[1]
        self.ax2 = ax[0]
        self.dt = dt
        self.maxt = maxt
        self.mint = 0 
        self.tdata = [0]
        self.ydata1 = [0.5]
        self.ydata2 = [0.5]
        self.arm1x = [0 , .5]
        self.arm1y = [0 , .5]
        self.arm2x = [0 , 0]
        self.arm2y = [0 , .5]
        self.line1 = Line2D(self.tdata, self.ydata1, color="red", label="Data1")
        self.line2 = Line2D(self.tdata, self.ydata2, color="blue", label="Data2")
        self.arm1 = Line2D(self.arm1x, self.arm1y, color="purple", lw="18", solid_capstyle="round", marker="o", markerfacecolor="black", markersize=20)
        self.arm2 = Line2D(self.arm2x, self.arm2y, color="purple", lw="18", solid_capstyle="round", marker="o", markerfacecolor="black", markersize=20)
        self.ax2.add_line(self.arm1)
        self.ax2.add_line(self.arm2)
        self.ax2.set_xlim(-.7, .7)
        self.ax2.set_ylim(-.7, .7)
        self.ax2.get_xaxis().set_visible(False)
        self.ax2.get_yaxis().set_visible(False)
        self.ax.add_line(self.line1)
        self.ax.add_line(self.line2)
        self.ax.set_ylim(-.1, 1.1)
        self.ax.set_xlim(self.mint, self.maxt)

    def update(self, y):
        global k
        t = self.tdata[-1] + self.dt
        
        if k<999:
            k=k+1
        else:
            self.tdata.pop(0)       #remove the first element
            self.ydata1.pop(0)
            self.ydata2.pop(0)             #remove the first element
            self.ax.set_xlim(self.tdata[0], self.tdata[-1]) #adjust the x-axis
            
        
        self.arm1.set_data([0, y[1]-.5],[0, y[0]-.5])
        self.tdata.append(t)    #add to the end
        self.ydata1.append(y[0])
        self.ydata2.append(y[1])
        self.line1.set_data(self.tdata, self.ydata1)
        self.line2.set_data(self.tdata, self.ydata2)
        return self.line1, self.line2, self.arm1
    
    def off(self, event):
        self.line1.set_visible(False)
        
    def on(self, event):
        self.line1.set_visible(True)

    def init(self):
        self.line1.set_data([], [])
        self.line2.set_data([], [])
        self.arm1.set_data([], [])
        return self.line1, self.line2, self.arm1
    def close(self, event):
        plt.close()
        
def emitter(p=0.03):
    global j
    data1 = np.sin(j)/2 + .5
    data2 = np.cos(j)/2 + .5
    'return a random value with probability p, else 0'
    yield [data1, data2]
    j=j+.01

def func(label):
    if label == 'Data1': scope.line1.set_visible(not scope.line1.get_visible())
    elif label == 'Data2': scope.line2.set_visible(not scope.line2.get_visible())


    
#fig, ax = plt.subplots(ncols=2)

#fig.subplots_adjust(bottom=0.2, right = 0.8, wspace=0)
plt.close('all')
fig = plt.figure()
ax = [0]*2
mng = plt.get_current_fig_manager()
mng.resize(*mng.window.maxsize())

gs1 = gridspec.GridSpec(1,1)
gs1.update(left=0.0, right=0.25)
ax[0] = plt.subplot(gs1[0, 0], aspect="equal")

gs2 = gridspec.GridSpec(1,1)
gs2.update(left=0.25, right=0.9)
ax[1] = plt.subplot(gs2[0, 0])

scope = Scope(ax)
fig.legend([scope.line1, scope.line2], ['Data1', 'Data2'])
checkax = plt.axes([0.9, 0.4, 0.1, 0.15])
check = CheckButtons(checkax, ('Data1', 'Data2'), (True, True))
check.on_clicked(func)

closeax = plt.axes([0.9, 0.25, 0.1, 0.1])
close = Button(closeax, 'Close')
close.on_clicked(scope.close)


# pass a generator in "emitter" to produce data for the update func
ani = animation.FuncAnimation(fig, scope.update, emitter, scope.init, interval=10,
    blit=True)

plt.show()
