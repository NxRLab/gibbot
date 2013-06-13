import time
from Tkinter import *
from GibbotModel import *
from InputFrame import *
from GibbotFrame import *
from Controller import *


controllerTypes = [
    ThrashSwingController,
    Controller,
    SpongSwingUpController,
    SpongBalanceController
]

defaultBot = GibbotModel(0, 0, 0, 0, 0, 0)

DT = .01
TIME_SCALE = 1
FPS = 40


class SimulatorApp(Tk):
    def __init__(self):
        Tk.__init__(self)
        self.title('Python Gibbot Simulator')

        self.controller = controllerTypes[0]()
        self.bot = defaultBot
        self.timeScale = 1
        self.t = 0

        self.inputFrame = InputFrame(self, controllerTypes, TIME_SCALE, defaultBot, self.restart)
        self.inputFrame.grid(row=0, column=0, sticky=N+W)

        self.gibbotFrame = GibbotFrame(self)
        self.gibbotFrame.grid(row=0, column=1, sticky=N+S+E+W)
        self.rowconfigure(0, weight=1)
        self.columnconfigure(1, weight=1)


        self.animate()

    def animate(self):
        frameStartTime = time.time()
        frameInterval = 1.0/FPS

        # update UI
        self.inputFrame.update(self.bot, self.t)
        self.gibbotFrame.update(self.bot)

        # advance physics
        simulationInterval = frameInterval * self.timeScale
        simulationTicks = int(simulationInterval / DT)
        for i in xrange(0, simulationTicks):
            controlTorque = self.controller.control(self.bot)
            self.bot.advanceState(controlTorque, DT)
        self.t += simulationInterval

        # schedule next frame
        waitTime = frameStartTime + frameInterval - time.time()
        millis = int(waitTime * 1000)
        if millis < 1:
            millis = 1
        self.after(millis, self.animate)

    def restart(self, controllerType, timeScale, bot):
        print '** RESTART **'
        self.controller = controllerType()
        self.timeScale = timeScale
        self.bot = bot
        self.t = 0




if __name__ == '__main__':
    app = SimulatorApp()
    app.geometry("800x500+100+100") # WIDTHxHEIGHT+X+Y
    app.mainloop()

