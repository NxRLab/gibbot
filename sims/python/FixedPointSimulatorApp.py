import time
from Tkinter import *
from GibbotModel import *
from FixedPointInputFrame import *
from FixedPointGibbotFrame import *
from Controller import *


controllerTypes = [
    SpongSwingUpController,
    ThrashSwingController,
    Controller,
    SpongBalanceController
]

defaultBot = GibbotModel(0, 0, 0.5, 0, 0, 0)

DT = .01
TIME_SCALE = 1


class FixedPointSimulatorApp(Tk):
    def __init__(self):
        Tk.__init__(self)
        self.title('Fixed-Point Gibbot Simulator')

        self.controller = controllerTypes[0]()
        self.bot = defaultBot
        self.timeScale = TIME_SCALE
        self.t = 0 # elapsed simulation time

        self.inputFrame = FixedPointInputFrame(self, controllerTypes, TIME_SCALE, defaultBot, self.restart)
        self.inputFrame.grid(row=0, column=0, sticky=N+W)

        self.gibbotFrame = FixedPointGibbotFrame(self)
        self.gibbotFrame.grid(row=0, column=1, sticky=N+S+E+W)
        self.rowconfigure(0, weight=1)
        self.columnconfigure(1, weight=1)

        self.startTime = time.time()
        self.animate()

    def animate(self):
        self.animating = True
        frameStartTime = time.time()

        # update UI
        self.inputFrame.update(self.bot, self.t)
        self.gibbotFrame.update(self.bot)

        # advance physics
        while self.t / self.timeScale < frameStartTime - self.startTime:
            controlTorque = self.controller.control(self.bot)
            beforeQ1 = self.bot.q1
            self.bot.advanceState(controlTorque, DT)
            if abs(beforeQ1 - self.bot.q1) > 4:
                print '*** flipped at time', self.t, '***'
                self.animating = False
                return
            self.t += DT

        # schedule next frame
        self.after(1, self.animate)

    def restart(self, controllerType, timeScale, bot):
        print '** RESTART **'
        self.controller = controllerType()
        self.timeScale = timeScale
        self.bot = bot
        self.t = 0
        self.startTime = time.time()
        if not self.animating:
            self.animate()




if __name__ == '__main__':
    app = FixedPointSimulatorApp()
    app.geometry("800x500+100+100") # WIDTHxHEIGHT+X+Y
    app.mainloop()

