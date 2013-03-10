import pyoptitrack
from Tkinter import *

SCALE = .5

class BlobFrame(Frame):

    def __init__(self, parent, cameras):
        Frame.__init__(self, parent)

        self.parent = parent
        self.cameras = cameras

        self.initUI()
        self.animate()

    def initUI(self):
        self.parent.title("Blobs")
        self.pack(fill=BOTH, expand=1)

        self.canvas = Canvas(self)
        self.canvas.pack(fill=BOTH, expand=1)

        self.colors = ['red', 'green', 'blue', 'orange', 'purple']

    def animate(self):
        self.drawBlobs()
        self.after(1, self.animate)
        
    def drawBlobs(self):
        self.canvas.delete(ALL)
        
        for camera in self.cameras:
            blobs = pyoptitrack.getBlobsForCamera(camera)
            if not blobs:
                print 'skipping blobless frame'
                continue
            for blob in blobs:
                x = blob[0] * SCALE
                y = blob[1] * SCALE
                R = 4
                self.canvas.create_oval(x-R, y-R, x+R, y+R, fill=self.colors[camera], \
                                        outline="black", width=1)

def main():
    print "initializing cameras..."
    pyoptitrack.waitForInitialization()
    cameras = pyoptitrack.getCameraList()
    for camera in cameras:
        pyoptitrack.startCamera(camera)
        pyoptitrack.setIntensityForCamera(camera, 0)
    
    root = Tk()
    blobFrame = BlobFrame(root, cameras)
    dims = pyoptitrack.getDimensionsForCamera(cameras[0])
    dims = (dims[0]*SCALE, dims[1]*SCALE)
    root.geometry("%dx%d+0+0" % dims) # WIDTHxHEIGHT+X+Y
    root.mainloop()
    pyoptitrack.shutdown()


if __name__ == '__main__':
    main()

