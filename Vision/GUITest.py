from Tkinter import *

class Example(Frame):

    def __init__(self, parent):
        Frame.__init__(self, parent)

        self.parent = parent 
        self.initUI()

    def initUI(self):

        self.parent.title("Colors")
        self.pack(fill=BOTH, expand=1)

        canvas = Canvas(self)

        canvas.create_oval(10, 10, 80, 80, outline="red", fill="green", width=2)
        canvas.create_oval(110, 10, 210, 80, outline="#f11", fill="#1f1", width=2)
        canvas.create_rectangle(230, 10, 290, 60, outline="black", fill="red", width=2)
        canvas.create_arc(30, 200, 90, 100, start=0, extent=210, outline="black", fill="blue", width=2)

        points = [150, 100, 200, 120, 240, 180, 210, 200, 150, 150, 100, 200]
        canvas.create_polygon(points, outline='black', fill='light green', width=2)

        canvas.pack(fill=BOTH, expand=1)


def main():
    root = Tk()
    ex = Example(root)
    root.geometry("400x400+100+100") # WIDTHxHEIGHT+X+Y
    root.mainloop()


if __name__ == '__main__':
    main()
