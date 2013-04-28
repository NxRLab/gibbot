from Tkinter import *
from MonkeyBot import *
from InputFrame import *
from MonkeyFrame import *


CONTROLLERS = {
    "1. Null": "The null controller",
    "2. Spong": "The spong controller"
}


class SimulatorApp(Tk):
    def __init__(self):
        Tk.__init__(self)
        self.title('Python Monkey Simulator')

        self.inputFrame = InputFrame(self, CONTROLLERS, self.restart)
        self.inputFrame.grid(row=0, column=0)

        self.monkeyFrame = MonkeyFrame(self)
        self.monkeyFrame.grid(row=0, column=1)

    def restart(self, controller, timeScale, bot):
        print controller
        print timeScale
        print bot
        self.inputFrame.update(bot)
        self.monkeyFrame.update(bot)



if __name__ == '__main__':
    app = SimulatorApp()
    app.geometry("800x600+100+100") # WIDTHxHEIGHT+X+Y
    app.mainloop()
