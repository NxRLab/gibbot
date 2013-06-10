from Tkinter import *
from GibbotModel import *

class InputFrame(Frame):

    def __init__(self, parent, controllerTypes, timeScale, defaultBot, restartCallback):
        Frame.__init__(self, parent)
        self.controllerTypes = controllerTypes
        self.restartCallback = restartCallback

        controllerNames = [c.name for c in controllerTypes]

        # variables
        self.controllerVar = StringVar(self)
        self.controllerVar.set(controllerNames[0])
        self.q1InitVar = StringVar(self)
        self.q1InitVar.set(defaultBot.q1)
        self.q2InitVar = StringVar(self)
        self.q2InitVar.set(defaultBot.q2)
        self.q1dInitVar = StringVar(self)
        self.q1dInitVar.set(defaultBot.q1d)
        self.q2dInitVar = StringVar(self)
        self.q2dInitVar.set(defaultBot.q2d)
        self.q1Var = StringVar(self)
        self.q1Var.set(defaultBot.q1)
        self.q2Var = StringVar(self)
        self.q2Var.set(defaultBot.q2)
        self.q1dVar = StringVar(self)
        self.q1dVar.set(defaultBot.q1d)
        self.q2dVar = StringVar(self)
        self.q2dVar.set(defaultBot.q2d)
        self.timeScaleVar = StringVar(self)
        self.timeScaleVar.set(timeScale)
        self.timeElapsedVar = StringVar(self)
        self.timeElapsedVar.set(0.0)

        # row 0
        Label(self, text="Controller:").grid(row=0, column=0)
        OptionMenu(self, self.controllerVar, *controllerNames).grid(row=0, column=1, columnspan=2, sticky=W+E)

        # row 1
        Label(self, text="Time scale:").grid(row=1)
        e = Entry(self, textvariable=self.timeScaleVar)
        e.bind('<Return>', self.restart)
        e.grid(row=1, column=1, columnspan=2)

        # row 2
        Label(self, text="Initial", width=10, anchor=W).grid(row=2, column=1, sticky=W)
        Label(self, text="Current", width=10, anchor=W).grid(row=2, column=2, sticky=W)

        # rows 3-6
        rowData = [['q1', self.q1InitVar, self.q1Var],
                   ['q2', self.q2InitVar, self.q2Var],
                   ['q1d', self.q1dInitVar, self.q1dVar],
                   ['q2d', self.q2dInitVar, self.q2dVar]]
        for i in range(len(rowData)):
            row = i + 3
            [name, initVar, var] = rowData[i]
            Label(self, text=name).grid(row=row)
            e = Entry(self, textvariable=initVar, width=10)
            e.grid(row=row, column=1)
            e.bind('<Return>', self.restart)
            Label(self, textvariable=var, anchor=W, width=20).grid(row=row, column=2, sticky=W)

        # row 7
        Label(self, text='Elapsed time:').grid(row=7, columnspan=2)
        Label(self, textvariable=self.timeElapsedVar, width=20, anchor=W).grid(row=7, column=2, sticky=W)

        # row 8
        Button(self, text="Restart", command=self.restart).grid(row=8, columnspan=3, sticky=W+E)

    def update(self, bot, t):
        self.q1Var.set(bot.q1)
        self.q2Var.set(bot.q2)
        self.q1dVar.set(bot.q1d)
        self.q2dVar.set(bot.q2d)
        self.timeElapsedVar.set(t)

    def restart(self, event=None):
        controllerName = self.controllerVar.get()
        for c in self.controllerTypes:
            if c.name == controllerName:
                controllerType = c
        timeScale = float(self.timeScaleVar.get())
        q1 = float(self.q1InitVar.get())
        q2 = float(self.q2InitVar.get())
        q1d = float(self.q1dInitVar.get())
        q2d = float(self.q2dInitVar.get())
        bot = GibbotModel(0, 0, q1, q2, q1d, q2d)
        self.restartCallback(controllerType, timeScale, bot)

