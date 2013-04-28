import math
from Tkinter import *
from MonkeyBot import *


class MonkeyFrame(Frame):

    def __init__(self, parent):
        Frame.__init__(self, parent)

        self.c = Canvas(self)

        # edges
        self.line = self.c.create_line(0, 0, 50, 50, 100, 100, fill="black", width=3)

        # vertices
        self.o1 = self.c.create_oval(0, 0, 10, 10, outline="black", fill="red", width=1)
        self.o2 = self.c.create_oval(50, 50, 60, 60, outline="black", fill="red", width=1)
        self.o3 = self.c.create_oval(100, 100, 110, 110, outline="black", fill="red", width=1)

        self.c.pack(fill=BOTH, expand=1)

    def update(self, bot):
    	w = self.winfo_width()
    	h = self.winfo_height()
    	S = 5
    	L = 50

    	x1 = w/2
    	y1 = h/2
    	x2 = x1 + math.cos(bot.q1) * L
    	y2 = y1 + math.sin(bot.q1) * L
    	x3 = x2 + math.cos(bot.q1 + bot.q2) * L
    	y3 = y2 + math.sin(bot.q1 + bot.q2) * L
    	self.c.coords(self.line, x1, y1, x2, y2, x3, y3)