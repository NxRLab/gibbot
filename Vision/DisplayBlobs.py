import pyoptitrack
from Tkinter import *
import numpy as np
import traceback
import math
from Camera import *

BOARD_SIZE = (2394.0, 1231.9) # in millimeters
MAX_CLUSTER_DIST = 60 # in millimeters
CAMERA_OVERLAP = 50 # in millimeters


class CameraFrame(Frame):
    def __init__(self, master, title, dimensions, padding=0):
        Frame.__init__(self, master) 
        self.dimensions = dimensions
        self.padding = padding

        Label(self, text=title).pack()

        c = Canvas(self, width=10000, height=10000)
        c.pack(fill=BOTH, expand=1)
        self.canvas = c

    def update(self, colorsAndPointLists, polygons=[]):
        c = self.canvas
        c.delete(ALL)

        # find scale factor and offset within canvas
        pad = self.padding
        wScreen = c.winfo_width()
        hScreen = c.winfo_height()
        wBoard = self.dimensions[0]
        hBoard = self.dimensions[1]
        wTotal = wBoard + 2*pad
        hTotal = hBoard + 2*pad
        rScreen = float(hScreen)/wScreen
        rTotal = float(hTotal)/wTotal
        if rScreen > rTotal:
            scale = float(wScreen)/wTotal
            off = (pad*scale, pad*scale + (hScreen - scale*hTotal)/2)
        else:
            scale = float(hScreen)/hTotal
            off = (pad*scale + (wScreen - scale*wTotal)/2, pad*scale)

        # draw background
        c.create_rectangle(off[0], off[1], off[0]+wBoard*scale, off[1]+hBoard*scale, fill='#CCC', width=0)

        # draw polygons
        for polyCoords in polygons:
            tPolyCoords = []
            for i in range(0, len(polyCoords), 2):
                x = off[0] + polyCoords[i]*scale
                y = off[1] + polyCoords[i+1]*scale
                tPolyCoords += [x, y]
            c.create_polygon(tPolyCoords, outline='black', fill='', width=1)

        # draw points
        for colorAndPointList in colorsAndPointLists:
            color, pointList = colorAndPointList
            for p in pointList:
                x = off[0] + p[0]*scale
                y = off[1] + p[1]*scale
                R = 4
                o = c.create_oval(x-R, y-R, x+R, y+R, fill=color, outline="black", width=1)
                def makeClickHandler(point):
                    def clicked(event):
                        print point
                    return clicked
                c.tag_bind(o, '<Button-1>', makeClickHandler(p))


class CameraDebugWindow(Tk):
    def __init__(self, leftCamera, rightCamera):
        Tk.__init__(self)
        self.leftCamera = leftCamera
        self.rightCamera = rightCamera
        self.title('Camera debug')

        self.columnconfigure(0, weight=1)
        self.columnconfigure(1, weight=1)
        self.rowconfigure(0, weight=1)
        self.rowconfigure(1, weight=1)

        self.leftFrame = CameraFrame(self, 'Raw left (px)', leftCamera.dimensions)
        self.leftFrame.grid(row=0, column=0)

        self.rightFrame = CameraFrame(self, 'Raw right (px)', rightCamera.dimensions)
        self.rightFrame.grid(row=0, column=1)

        self.bottomFrame = CameraFrame(self, 'Transformed and combined (mm)', (2394, 1232), padding=400)
        self.bottomFrame.grid(row=1, column=0, columnspan=2)

        self.animate()

    def animate(self):
        self.drawFrame()
        self.after(1, self.animate)

    def drawFrame(self):
        L = self.leftCamera
        R = self.rightCamera

        # raw blobs (units of pixels)
        self.leftFrame.update([['red', L.blobs]])
        self.rightFrame.update([['green', R.blobs]])

        # transformed blobs (units of mm)
        L.transformBlobs()
        R.transformBlobs()
        leftBlobs = L.tBlobs
        rightBlobs = [(b[0] + BOARD_SIZE[0]/2, b[1]) for b in R.tBlobs]

        # transform camera corners
        leftPolyCoords = []
        for corner in L.cameraCorners:
            coord = L.fromCameraToBoard(corner)
            if not coord:
                leftPolyCoords = None
                break
            leftPolyCoords += coord
        rightPolyCoords = []
        for corner in R.cameraCorners:
            coord = R.fromCameraToBoard(corner)
            if not coord:
                rightPolyCoords = None
                break
            rightPolyCoords += (coord[0] + BOARD_SIZE[0]/2, coord[1])

        # cluster non-corners into nodes
        L.clusterNodes()
        R.clusterNodes()
        
        def f(n): # returns location of the cluster with n blobs, combining left and right data
            if n in L.nodes:
                if n in R.nodes:
                    return ((L.nodes[n][0] + R.nodes[n][0] + BOARD_SIZE[0]/2)/2,
                            (L.nodes[n][1] + R.nodes[n][1])/2)
                else:
                    return L.nodes[n]
            else:
                if n in R.nodes:
                    return (R.nodes[n][0] + BOARD_SIZE[0]/2, R.nodes[n][1])
                else:
                    return None
        nodes = [x for x in [f(1), f(2), f(3)] if x is not None]
        
        polyCoords = [x for x in [leftPolyCoords, rightPolyCoords] if x is not None]
        colorToPoints = [['red', leftBlobs], ['green', rightBlobs], ['blue', nodes]]
        self.bottomFrame.update(colorToPoints, polyCoords)


def main():
    print "Initializing cameras..."
    pyoptitrack.waitForInitialization()
    print 'Running...'
    cameraIDs = pyoptitrack.getCameraList()

    leftCamera = Camera(cameraIDs[0], 0)
    rightCamera = Camera(cameraIDs[1], 1)
    
    root = CameraDebugWindow(leftCamera, rightCamera)
    root.geometry("800x800+100+100") # WIDTHxHEIGHT+X+Y
    root.mainloop()

    print 'Shutting down...'
    pyoptitrack.shutdown()


if __name__ == '__main__':
    main()

