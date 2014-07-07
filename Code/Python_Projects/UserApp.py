import time
from Tkinter import *
import PIL.Image
import PIL.ImageTk
import math
import copy
from GibbotModel import *
from Controller import *

"""
UserApp presents a window that shows the board, the Gibbot, and the goal (a banana).

The user can click on the board to update the goal.
The Gibbot will swing until it is close to the goal.

All behavior is simulated, but this interface could be used with real hardware.
"""


BOARD_SIZE = (2.4384, 1.8288) # 8' x 6' in meters

START_BOT = GibbotModel(1, 1, -pi/4, -pi/2)

DT = .01
FPS = 40
GOAL_RADIUS = START_BOT.l1 * math.sqrt(2)/2 # meters away from goal
BOARD_PAD = START_BOT.l1 + START_BOT.l2 # mimimum meters to border where clamping is allowed

FULLSCREEN_MODE = False

class UserApp(Tk):
    def __init__(self):
        Tk.__init__(self)
        self.title('Gibbot User Input')

        self.initCanvas()

        self.bot = START_BOT
        self.t = 0
        self.goal = (1.8, 1.0)
        self.controller = None

        self.after(1, self.animate)

    def initCanvas(self):
        self.c = Canvas(self, bg='#555555')

        self.border = self.c.create_rectangle(0, 0, 50, 50, fill='white', width=3)

        self.line = self.c.create_line(0, 0, 50, 50, 100, 100, fill="black", width=3)
        self.o1 = self.c.create_oval(0, 0, 10, 10, outline="black", fill="red", width=1)
        self.o2 = self.c.create_oval(50, 50, 60, 60, outline="black", fill="red", width=1)
        self.o3 = self.c.create_oval(100, 100, 110, 110, outline="black", fill="red", width=1)

        self.targetImage = PIL.Image.open('banana.png')
        self.targetPhoto = PIL.ImageTk.PhotoImage(self.targetImage)
        self.target = self.c.create_image(0, 0, image=self.targetPhoto)

        self.c.bind('<Button-1>', self.mousePressed)

        self.c.bind("<Escape>", self.escapePressed)

        self.c.pack(fill=BOTH, expand=1)

    def boardScaleAndOffset(self):
        w = self.winfo_width()
        h = self.winfo_height()

        scaleW = w / BOARD_SIZE[0]
        scaleH = h / BOARD_SIZE[1]
        if scaleW < scaleH:
            scale = scaleW
            xOffset = 0
            yOffset = (h + scale*BOARD_SIZE[1]) / 2
        else:
            scale = scaleH
            xOffset = (w - scale*BOARD_SIZE[0]) / 2
            yOffset = h
        return scale, (xOffset, yOffset)

    def pointToBoard(self, screenPoint):
        x = (screenPoint[0] - self.offset[0]) / self.scale
        y = (self.offset[1] - screenPoint[1]) / self.scale
        return x, y

    def pointToScreen(self, boardPoint):
        x = self.offset[0] + boardPoint[0] * self.scale
        y = self.offset[1] - boardPoint[1] * self.scale
        return x, y

    def mousePressed(self, event):
        x, y = self.pointToBoard((event.x, event.y))
        if x < BOARD_PAD:
            x = BOARD_PAD
        elif x > BOARD_SIZE[0] - BOARD_PAD:
            x = BOARD_SIZE[0] - BOARD_PAD
        if y < BOARD_PAD:
            y = BOARD_PAD
        elif y > BOARD_SIZE[1] - BOARD_PAD:
            y = BOARD_SIZE[1] - BOARD_PAD
        self.goal = (x,y)
        print 'Goal set to', self.goal

        d1sq = (self.bot.x1 - x)**2 + (self.bot.y1 - y)**2
        d3sq = (self.bot.x3 - x)**2 + (self.bot.y3 - y)**2
        if d3sq < d1sq:
            self.bot.switch()
            print 'switch for goal'
        self.controller = ThrashSwingController()
        
    def escapePressed(self, e):
        print 'esc'
        e.widget.quit()

    def updateUI(self):
        self.scale, self.offset = self.boardScaleAndOffset()
        def coords(obj, *raw):
            N = len(raw)
            if N % 2:
                raise ValueError('An even number of coordinates is required')
            adjusted = []
            for i in xrange(0, N, 2):
                adjusted += map(int, self.pointToScreen((raw[i], raw[i+1])))
            self.c.coords(obj, *adjusted)
        def ovalCenter(oval, x, y, r=0.02):
            coords(oval, x-r, y-r, x+r, y+r)

        # draw board
        coords(self.border, 0, 0, BOARD_SIZE[0], BOARD_SIZE[1])

        # draw gibbot
        x1 = self.bot.x1
        y1 = self.bot.y1
        x3 = self.bot.x3
        y3 = self.bot.y3
        x2 = self.bot.x2
        y2 = self.bot.y2
        ovalCenter(self.o1, x1, y1)
        ovalCenter(self.o2, x3, y3)
        ovalCenter(self.o3, x2, y2)
        coords(self.line, x1, y1, x2, y2, x3, y3)

        # draw banana
        imSize = int(.2*self.scale)
        thumb = self.targetImage.copy()
        thumb.thumbnail((imSize, imSize), PIL.Image.ANTIALIAS)
        self.targetPhoto = PIL.ImageTk.PhotoImage(thumb)
        self.c.itemconfigure(self.target, image=self.targetPhoto)
        coords(self.target, self.goal[0], self.goal[1])

    def animate(self):
        frameStartTime = time.time()
        frameInterval = 1.0/FPS

        # update UI
        self.updateUI()

        # advance physics
        if self.controller:
            oldBot = copy.copy(self.bot)
            simulationTicks = int(frameInterval / DT)
            for i in xrange(0, simulationTicks):
                controlTorque = self.controller.control(self.bot)
                controlTorque = max(min(controlTorque, self.bot.maxTorque), -self.bot.maxTorque)
                self.bot.advanceState(controlTorque, DT)
            self.t += frameInterval

            destAngle = math.atan2(self.goal[1]-self.bot.y1, self.goal[0]-self.bot.x1)
            interMagnetAngle = math.atan2(self.bot.y3-self.bot.y1, self.bot.x3-self.bot.x1)
            if abs(destAngle-interMagnetAngle) < 0.1:
                goalDistSq = (self.bot.x3 - self.goal[0])**2 + (self.bot.y3 - self.goal[1])**2
                if goalDistSq < GOAL_RADIUS**2:
                    self.controller = None
                    self.bot.q1d = 0
                    self.bot.q2d = 0
                else:
                    self.controller = ThrashSwingController()
                    self.bot.switch()
                    print 'switch during control'

        # schedule next frame
        waitTime = frameStartTime + frameInterval - time.time()
        millis = int(waitTime * 1000)
        if millis < 1:
            millis = 1
        self.after(millis, self.animate)


if __name__ == '__main__':
    app = UserApp()
    if FULLSCREEN_MODE:
        app.overrideredirect(1)
        w, h = app.winfo_screenwidth(), app.winfo_screenheight()
        app.geometry("{}x{}+0+0".format(w,h)) # WIDTHxHEIGHT+X+Y
        app.lift()
    else:
        app.geometry("800x500+100+100") # WIDTHxHEIGHT+X+Y
    app.focus_set()
    app.mainloop()

