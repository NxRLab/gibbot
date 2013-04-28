from Tkinter import *
from MonkeyBot import *

class InputFrame(Frame):

    def __init__(self, parent, controllerDict, restartFunction):
        Frame.__init__(self, parent)
        self.controllerDict = controllerDict
        self.restartFunction = restartFunction

        controllerList = tuple(sorted(controllerDict.keys()))

        # variables
        self.controllerVar = StringVar(self)
        self.controllerVar.set(controllerList[0])
        self.q1InitVar = StringVar(self)
        self.q1InitVar.set(0)
        self.q2InitVar = StringVar(self)
        self.q2InitVar.set(0)
        self.q1dInitVar = StringVar(self)
        self.q1dInitVar.set(0)
        self.q2dInitVar = StringVar(self)
        self.q2dInitVar.set(0)
        self.q1Var = StringVar(self)
        self.q1Var.set(0)
        self.q2Var = StringVar(self)
        self.q2Var.set(0)
        self.q1dVar = StringVar(self)
        self.q1dVar.set(0)
        self.q2dVar = StringVar(self)
        self.q2dVar.set(0)
        self.timeScaleVar = StringVar(self)
        self.timeScaleVar.set(1.0)

        # row 0
        Label(self, text="Controller:").grid(row=0, column=0)
        OptionMenu(self, self.controllerVar, *controllerList).grid(row=0, column=1, columnspan=2, sticky=W+E)

        # row 1
        Label(self, text="Time scale:").grid(row=1)
        Entry(self, textvariable=self.timeScaleVar).grid(row=1, column=1, columnspan=2)

        # row 2
        Label(self, text="Initial", width=10).grid(row=2, column=1)
        Label(self, text="Current", width=10).grid(row=2, column=2)

        # rows 3-6
        Label(self, text="q1").grid(row=3)
        e = Entry(self, textvariable=self.q1InitVar, width=10)
        e.grid(row=3, column=1)
        e.bind('<Return>', self.restart)
        Label(self, textvariable=self.q1Var).grid(row=3, column=2)
        Label(self, text="q2").grid(row=4)
        e = Entry(self, textvariable=self.q2InitVar, width=10)
        e.grid(row=4, column=1)
        e.bind('<Return>', self.restart)
        Label(self, textvariable=self.q2Var).grid(row=4, column=2)
        Label(self, text="q1d").grid(row=5)
        e = Entry(self, textvariable=self.q1dInitVar, width=10)
        e.grid(row=5, column=1)
        e.bind('<Return>', self.restart)
        Label(self, textvariable=self.q1dVar).grid(row=5, column=2)
        Label(self, text="q2d").grid(row=6)
        e = Entry(self, textvariable=self.q2dInitVar, width=10)
        e.grid(row=6, column=1)
        e.bind('<Return>', self.restart)
        Label(self, textvariable=self.q2dVar).grid(row=6, column=2)

        # row 7
        Button(self, text="Restart", command=self.restart).grid(row=7, columnspan=3, sticky=W+E)

    def update(self, bot):
        self.q1Var.set(bot.q1)
        self.q2Var.set(bot.q2)
        self.q1dVar.set(bot.q1d)
        self.q2dVar.set(bot.q2d)

    def restart(self, event=None):
        controller = self.controllerDict[self.controllerVar.get()]
        timeScale = float(self.timeScaleVar.get())
        q1 = float(self.q1InitVar.get())
        q2 = float(self.q2InitVar.get())
        q1d = float(self.q1dInitVar.get())
        q2d = float(self.q2dInitVar.get())
        bot = MonkeyBot(q1, q2, q1d, q2d)
        self.restartFunction(controller, timeScale, bot)

