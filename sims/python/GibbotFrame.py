import math
from Tkinter import *
from GibbotModel import *


class GibbotFrame(Frame):

    def __init__(self, parent):
        Frame.__init__(self, parent)

        self.c = Canvas(self)

        # edges
        self.line = self.c.create_line(0, 0, 50, 50, 100, 100, fill="black", width=3)

        # vertices
        self.o1 = self.c.create_oval(0, 0, 10, 10, outline="black", fill="red", width=1)
        self.o2 = self.c.create_oval(50, 50, 60, 60, outline="black", fill="red", width=1)
        self.o3 = self.c.create_oval(100, 100, 110, 110, outline="black", fill="red", width=1)

        # centers of mass
        self.c1 = self.c.create_oval(0, 0, 10, 10, outline="black", fill="blue", width=1)
        self.c2 = self.c.create_oval(0, 0, 10, 10, outline="black", fill="blue", width=1)

        self.c.pack(fill=BOTH, expand=1)

    def update(self, bot):
        S = 5
        w = self.winfo_width()
        h = self.winfo_height()
        L = (min(w,h) - S*4) / 2
        pxPerM = L / (bot.l1 + bot.l2)
        l1 = bot.l1 * pxPerM
        l2 = bot.l2 * pxPerM

        theta = bot.q1 + pi/2
        phi = theta + bot.q2

        # Links
        x1 = w/2
        y1 = h/2
        x2 = x1 + math.cos(theta) * l1
        y2 = y1 + math.sin(theta) * l1
        x3 = x2 + math.cos(phi) * l2
        y3 = y2 + math.sin(phi) * l2

        self.c.coords(self.line, x1, y1, x2, y2, x3, y3)
        self.c.coords(self.o1, x1-S, y1-S, x1+S, y1+S)
        self.c.coords(self.o2, x2-S, y2-S, x2+S, y2+S)
        self.c.coords(self.o3, x3-S, y3-S, x3+S, y3+S)

        # Centers of mass
        r1 = bot.r1 * pxPerM
        r2 = bot.r2 * pxPerM
        x1c = x1 + math.cos(theta) * r1
        y1c = y1 + math.sin(theta) * r1
        x2c = x2 + math.cos(phi) * r2
        y2c = y2 + math.sin(phi) * r2
        pxSqPerKg = 8**2 / max(bot.m1, bot.m2)
        S1 = sqrt(bot.m1 * pxSqPerKg)
        S2 = sqrt(bot.m2 * pxSqPerKg)

        self.c.coords(self.c1, x1c-S1, y1c-S1, x1c+S1, y1c+S1)
        self.c.coords(self.c2, x2c-S2, y2c-S2, x2c+S2, y2c+S2)
