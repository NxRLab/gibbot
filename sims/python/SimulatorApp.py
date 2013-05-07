import time
from Tkinter import *
from GibbotModel import *
from InputFrame import *
from GibbotFrame import *
from Controllers import *


CONTROLLERS = {
    "1. Null": nullController,
    "2. Spong": spongController
}

DEFAULT_BOT = GibbotModel(1.077398914708292,  0.986794824173209, 0, 0)

DT = .001
TIME_SCALE = 1
FPS = 40


class SimulatorApp(Tk):
    def __init__(self):
        Tk.__init__(self)
        self.title('Python Gibbot Simulator')

        self.inputFrame = InputFrame(self, CONTROLLERS, TIME_SCALE, DEFAULT_BOT, self.restart)
        self.inputFrame.grid(row=0, column=0, sticky=N+W)

        self.gibbotFrame = GibbotFrame(self)
        self.gibbotFrame.grid(row=0, column=1, sticky=N+S+E+W)
        self.rowconfigure(0, weight=1)
        self.columnconfigure(1, weight=1)

        self.controller = nullController
        self.bot = DEFAULT_BOT
        self.timeScale = TIME_SCALE
        self.t = time.time() * self.timeScale
        self.startTime = self.t

        self.animate()

    def animate(self):
        frameStartTime = time.time()*self.timeScale
        frameEndTime = frameStartTime + 1.0/FPS*self.timeScale

        # update UI
        self.inputFrame.update(self.bot, self.t - self.startTime)
        self.gibbotFrame.update(self.bot)

        while self.t < frameEndTime:
            # advance physics
            self.bot.advanceState(self.controller, DT)
            self.t += DT

        # schedule next frame
        waitTime = frameEndTime - time.time()*self.timeScale
        millis = int(waitTime * 1000)
        if millis > 0:
            self.after(millis, self.animate)
        else:
            self.animate()

    def restart(self, controller, timeScale, bot):
        self.controller = controller
        self.timeScale = timeScale
        self.bot = bot

        self.t = time.time() * timeScale
        self.startTime = self.t




if __name__ == '__main__':
    app = SimulatorApp()
    app.geometry("800x500+100+100") # WIDTHxHEIGHT+X+Y
    app.mainloop()

