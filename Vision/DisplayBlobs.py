import pyoptitrack
from Tkinter import *

SCALE = .5

leftBlobs = []
rightBlobs = []

class BlobFrame(Frame):

    def __init__(self, parent):
        Frame.__init__(self, parent)

        self.parent = parent

        self.initUI()
        self.animate()

    def initUI(self):
        self.parent.title("Blobs")
        self.pack(fill=BOTH, expand=1)

        self.canvas = Canvas(self)
        self.canvas.pack(fill=BOTH, expand=1)

    def animate(self):
        self.drawFrame()
        self.after(1, self.animate)

    def drawFrame(self):
        self.canvas.delete(ALL)
        self.drawBlobs(leftBlobs, 'red')
        self.drawBlobs(rightBlobs, 'green')
        
    def drawBlobs(self, blobs, color):
        for blob in blobs:
            x = blob[0] * SCALE
            y = blob[1] * SCALE
            R = 4
            self.canvas.create_oval(x-R, y-R, x+R, y+R, fill=color, \
                                    outline="black", width=1)

def gotBlobs(camera, blobs):
    global leftBlobs, rightBlobs
    try:
        if camera == cameras[0]:
            leftBlobs = [(b[1], b[0]) for b in blobs]
        elif camera == cameras[1]:
            rightBlobs = [(b[1]+dims[1], b[0]) for b in blobs]
    except Exception as e:
        print e

def main():
    global cameras, dims
    print "Initializing cameras..."
    pyoptitrack.waitForInitialization()
    cameras = pyoptitrack.getCameraList()

    for i in range(2):
        pyoptitrack.startCamera(cameras[i], i, gotBlobs)
        pyoptitrack.setIntensityForCamera(cameras[i], 0)
    
    root = Tk()
    blobFrame = BlobFrame(root)
    dims = pyoptitrack.getDimensionsForCamera(cameras[0])
    dims = (dims[1]*SCALE*2, dims[0]*SCALE)
    root.geometry("%dx%d+0+0" % dims) # WIDTHxHEIGHT+X+Y
    root.mainloop()

    print 'Shutting down...'
    pyoptitrack.shutdown()


if __name__ == '__main__':
    main()

