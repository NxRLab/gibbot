import time
from Tkinter import *
import PIL.Image
import PIL.ImageTk
import math
from GibbotModel import *
from InputFrame import *
from GibbotFrame import *
from Controllers import *


BOARD_SIZE = (2.4384, 1.8288) # 8' x 6' in meters

START_BOT = GibbotModel(1, 1, -pi/4, -pi/2)

DT = .001
FPS = 40
GOAL_RADIUS = START_BOT.l1 * math.sqrt(2)/2 # meters away from goal

class UserApp(Tk):
    def __init__(self):
        Tk.__init__(self)
        self.title('Gibbot User Input')

        self.initCanvas()

        self.bot = START_BOT
        self.botIsVertical = False
        self.t = 0
        self.goal = (2.0, 1.0)

        print (self.bot.x1, self.bot.y1), (self.bot.cx, self.bot.cy), (self.bot.x2, self.bot.y2)

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

        self.c.pack(fill=BOTH, expand=1)

    def boardScaleAndOffset(self):
        w = self.winfo_width()
        h = self.winfo_height()

        scaleW = w / BOARD_SIZE[0]
        scaleH = h / BOARD_SIZE[1]
        if scaleW < scaleH:
            scale = scaleW
            xOffset = 0
            yOffset = (h - scale*BOARD_SIZE[1]) / 2
        else:
            scale = scaleH
            xOffset = (w - scale*BOARD_SIZE[0]) / 2
            yOffset = 0
        return (scale, (xOffset, yOffset))

    def mousePressed(self, event):
        (scale, offset) = self.boardScaleAndOffset()
        x = (event.x - offset[0]) / scale
        y = (event.y - offset[1]) / scale
        self.goal = (x,y)

        self.move()

    def update(self):
        (scale, offset) = self.boardScaleAndOffset()
        def coords(obj, *raw):
            N = len(raw)
            if N % 2:
                raise ValueError('An even number of arguments is required')
            adjusted = []
            for i in xrange(0, N, 2):
                x = offset[0] + scale*raw[i]
                y = offset[1] + scale*raw[i+1]
                adjusted += [int(x), int(y)]
            self.c.coords(obj, *adjusted)
        def ovalCenter(oval, x, y, r=0.02):
            coords(oval, x-r, y-r, x+r, y+r)

        # draw board
        coords(self.border, 0, 0, BOARD_SIZE[0], BOARD_SIZE[1])

        # draw gibbot
        x1 = self.bot.x1
        y1 = self.bot.y1
        x2 = self.bot.x2
        y2 = self.bot.y2
        cx = self.bot.cx
        cy = self.bot.cy
        ovalCenter(self.o1, x1, y1)
        ovalCenter(self.o2, x2, y2)
        ovalCenter(self.o3, cx, cy)
        coords(self.line, x1, y1, cx, cy, x2, y2)

        # draw banana
        imSize = int(.2*scale)
        thumb = self.targetImage.copy()
        thumb.thumbnail((imSize, imSize), PIL.Image.ANTIALIAS)
        self.targetPhoto = PIL.ImageTk.PhotoImage(thumb)
        self.c.itemconfigure(self.target, image=self.targetPhoto)
        coords(self.target, self.goal[0], self.goal[1])


    def animate(self):
        frameStartTime = time.time()
        frameInterval = 1.0/FPS

        # update UI
        self.update()

        # advance physics
        simulationTicks = int(frameInterval / DT)
        for i in xrange(0, simulationTicks):
            pass #self.bot.advanceState(nullController, DT)
        self.t += frameInterval

        # schedule next frame
        waitTime = frameStartTime + frameInterval - time.time()
        millis = int(waitTime * 1000)
        if millis < 1:
            millis = 1
        self.after(millis, self.animate)

    def move(self):
        bot = self.bot
        goal = self.goal
        diff1 = (goal[0] - bot.x1, goal[1] - bot.y1)
        diff2 = (goal[0] - bot.x2, goal[1] - bot.y2)
        dist1 = math.sqrt(diff1[0]**2 + diff1[1]**2)
        dist2 = math.sqrt(diff2[0]**2 + diff2[1]**2)
        if dist1 < dist2:
            diff = diff1
            dist = dist1
        else:
            diff = diff2
            dist = dist2
            bot.switch()
            print 'switch!'

        if abs(diff[0]) > GOAL_RADIUS:
            if self.botIsVertical:
                self.botIsVertical = False
                if diff[0] < 0:
                    bot.q1 = pi/4
                    bot.q2 = pi/2
                else:
                    bot.q1 = -pi/4
                    bot.q2 = -pi/2
            else:
                if diff[0] < 0:
                    bot.x1 -= bot.l1 * math.sqrt(2)
                else:
                    bot.x1 += bot.l1 * math.sqrt(2)
        elif abs(diff[1]) > GOAL_RADIUS:
            if diff[1] < 0:
                self.botIsVertical = True
                bot.q1 = -math.pi
                bot.q2 = 0
            else:
                bot.y1 = goal[1]


if __name__ == '__main__':
    app = UserApp()
    app.geometry("800x500+100+100") # WIDTHxHEIGHT+X+Y
    app.mainloop()

