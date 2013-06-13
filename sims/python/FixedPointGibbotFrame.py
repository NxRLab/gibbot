import math
from Tkinter import *
from GibbotModel import *


class FixedPointGibbotFrame(Frame):

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
        scale = L / (bot.l1 + bot.l2)

        # Links
        x1 = w/2
        y1 = h/2
        x2 = x1 + bot.x2 * scale
        y2 = y1 - bot.y2 * scale
        x3 = x1 + bot.x3 * scale
        y3 = y1 - bot.y3 * scale

        self.c.coords(self.line, x1, y1, x2, y2, x3, y3)
        self.c.coords(self.o1, x1-S, y1-S, x1+S, y1+S)
        self.c.coords(self.o2, x2-S, y2-S, x2+S, y2+S)
        self.c.coords(self.o3, x3-S, y3-S, x3+S, y3+S)

        # Centers of mass
        m1x = x1 + bot.m1x * scale
        m1y = y1 - bot.m1y * scale
        m2x = x1 + bot.m2x * scale
        m2y = y1 - bot.m2y * scale
        pxSqPerKg = 8**2 / max(bot.m1, bot.m2)
        S1 = sqrt(bot.m1 * pxSqPerKg)
        S2 = sqrt(bot.m2 * pxSqPerKg)

        self.c.coords(self.c1, m1x-S1, m1y-S1, m1x+S1, m1y+S1)
        self.c.coords(self.c2, m2x-S2, m2y-S2, m2x+S2, m2y+S2)
