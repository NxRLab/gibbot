import pyoptitrack
from Tkinter import *
import numpy as np
import traceback
import math

BOARD_SIZE = (1828.8, 1219.2) # 8' x 6' in millimeters
MAX_CLUSTER_DIST = 60 # in millimeters
CAMERA_OVERLAP = 50 # in millimeters
SCALE = .5

def get_transform_data(pts8, backward=True ):
    '''This method returns a perspective transform 8-tuple (a,b,c,d,e,f,g,h).
    
    Source: http://pythonpath.wordpress.com/tag/perspective-transform/
    
    Use to transform an image:
    X = (a x + b y + c)/(g x + h y + 1)
    Y = (d x + e y + f)/(g x + h y + 1)
     
    Image.transform: Use 4 source coordinates, followed by 4 corresponding
        destination coordinates. Use backward=True (the default)
         
    To calculate the destination coordinate of a single pixel, either reverse
        the pts (4 dest, followed by 4 source, backward=True) or use the same
        pts but set backward to False.
     
    @arg pts8: four source and four corresponding destination coordinates
    @kwarg backward: True to return coefficients for calculating an originating
        position. False to return coefficients for calculating a destination
        coordinate. (Image.transform calculates originating position.)
    '''
    assert len(pts8) == 8, 'Requires a tuple of eight coordinate tuples (x,y)'
     
    b0,b1,b2,b3,a0,a1,a2,a3 = pts8 if backward else pts8[::-1]
     
    # CALCULATE THE COEFFICIENTS
    A = np.array([[a0[0], a0[1], 1,     0,     0, 0, -a0[0]*b0[0], -a0[1]*b0[0]],
                 [    0,     0, 0, a0[0], a0[1], 1, -a0[0]*b0[1], -a0[1]*b0[1]],
                 [a1[0], a1[1], 1,     0,     0, 0, -a1[0]*b1[0], -a1[1]*b1[0]],
                 [    0,     0, 0, a1[0], a1[1], 1, -a1[0]*b1[1], -a1[1]*b1[1]],
                 [a2[0], a2[1], 1,     0,     0, 0, -a2[0]*b2[0], -a2[1]*b2[0]],
                 [    0,     0, 0, a2[0], a2[1], 1, -a2[0]*b2[1], -a2[1]*b2[1]],
                 [a3[0], a3[1], 1,     0,     0, 0, -a3[0]*b3[0], -a3[1]*b3[0]],
                 [    0,     0, 0, a3[0], a3[1], 1, -a3[0]*b3[1], -a3[1]*b3[1]]] )
    B = np.array([b0[0], b0[1], b1[0], b1[1], b2[0], b2[1], b3[0], b3[1]])
     
    return np.linalg.solve(A,B)

class Camera:
    def __init__(self, UID, numericLabel):
        self.UID = UID
        self.blobs = []
        self.tBlobs = []
        self.transform = None
        pyoptitrack.startCamera(UID, numericLabel, self.gotBlobs)
        pyoptitrack.setIntensityForCamera(UID, 0)
        dims = pyoptitrack.getDimensionsForCamera(UID)
        self.dimensions = (dims[1], dims[0])
        
        self.cameraCorners = np.array([[0,0],
                                       [0, self.dimensions[1]],
                                       [self.dimensions[0], 0],
                                       self.dimensions],
                                      np.float32)
        self.worldCorners = np.array([[0,0],
                                      [0, BOARD_SIZE[1]],
                                      [BOARD_SIZE[0]/2, 0],
                                      [BOARD_SIZE[0]/2, BOARD_SIZE[1]]],
                                     np.float32)

    def gotBlobs(self, camera, blobs):
        try:
            # rotate coordinates 90 degrees and save
            self.blobs = [(b[1], self.dimensions[0]-b[0]) for b in blobs]
        except Exception as e:
            traceback.print_exc(e)

    def transformBlobs(self):
        cornerBlobs = None
        if len(self.blobs) >= 4:
            # calculate a new transform matrix

            for corner in self.cameraCorners:
                bestDist = float('inf')
                bestBlob = None
                for blob in self.blobs:
                    dist = np.linalg.norm(corner - blob)
                    if dist < bestDist:
                        bestDist = dist
                        bestBlob = blob
                if cornerBlobs == None:
                    cornerBlobs = np.array(bestBlob, np.float32)
                else:
                    cornerBlobs = np.vstack((cornerBlobs, bestBlob))

            pts8 = np.vstack((cornerBlobs, self.worldCorners))
            try:
                self.transform = get_transform_data(pts8, False)
            except np.linalg.LinAlgError:
                pass

        # populate tBlobs by applying transform blobs
        self.tBlobs = []
        if self.transform is not None:
            for b in self.blobs:
                padded = np.array((b[0], b[1], 1))
                T = self.transform
                x = (T[0]*b[0] + T[1]*b[1] + T[2])/(T[6]*b[0] + T[7]*b[1] + 1)
                y = (T[3]*b[0] + T[4]*b[1] + T[5])/(T[6]*b[0] + T[7]*b[1] + 1)
                
                # omit corner blobs from tBlobs
                isCorner = False
                for corner in self.worldCorners:
                    if (x - corner[0])**2 + (y - corner[1])**2 < 10**2:
                        isCorner = True
                        break
                if not isCorner:
                    self.tBlobs += [(x, y)]
    
    def clusterNodes(self):
        clusters = [[b] for b in self.tBlobs]

        def averageOfCluster(cluster):
            xSum = 0
            ySum = 0
            for blob in cluster:
                xSum += blob[0]
                ySum += blob[1]
            return (xSum/len(cluster), ySum/len(cluster))
        
        while True:
            bestDistSq = float('inf')
            bestPair = None
            for i in range(len(clusters)):
                a = clusters[i]
                aAvg = averageOfCluster(a)
                for j in range(i+1, len(clusters)):
                    b = clusters[j]
                    bAvg = averageOfCluster(b)
                    distSq = (aAvg[0]-bAvg[0])**2 + (aAvg[1]-bAvg[1])**2
                    if distSq < bestDistSq:
                        bestDistSq = distSq
                        bestPair = (a, b)
            if bestDistSq < MAX_CLUSTER_DIST**2:
                keeper = bestPair[0]
                keeper += bestPair[1]
                clusters.remove(bestPair[1])
            else:
                break
        
        self.nodes = {}
        for c in clusters:
            avg = averageOfCluster(c)
            if avg[0] > -CAMERA_OVERLAP and avg[0] - BOARD_SIZE[0]/2 < CAMERA_OVERLAP:
                self.nodes[len(c)] = avg

class BlobFrame(Frame):

    def __init__(self, parent, leftCamera, rightCamera):
        Frame.__init__(self, parent)

        self.parent = parent
        self.leftCamera = leftCamera
        self.rightCamera = rightCamera

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

        L = self.leftCamera
        R = self.rightCamera

        # raw
        """
        self.drawBlobs(self.leftCamera.blobs, '#833')
        rightBlobs = [(b[0] + BOARD_SIZE[0]/2, b[1]) \
                      for b in self.rightCamera.blobs]
        self.drawBlobs(rightBlobs, '#383')
        """

        # transformed
        L.transformBlobs()
        R.transformBlobs()
        self.drawBlobs(L.tBlobs, 'red')
        rightBlobs = [(b[0] + BOARD_SIZE[0]/2, b[1]) for b in R.tBlobs]
        self.drawBlobs(rightBlobs, 'green')

        # clustered
        self.leftCamera.clusterNodes()
        self.rightCamera.clusterNodes()
        
        def getNode(n):
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
        nodes = [getNode(1), getNode(2), getNode(3)]
        self.drawBlobs(nodes, '#00F')
        
        text = 'joint missing'
        if nodes[0]:
            text = 'joint position: (%d, %d) millimeters' % nodes[0]
        self.canvas.create_text(2, 2, text=text, anchor=NW)
        
        
    def drawBlobs(self, blobs, color):
        for blob in blobs:
            if not blob:
                continue
            x = blob[0] * SCALE
            y = blob[1] * SCALE
            R = 4
            self.canvas.create_oval(x-R, y-R, x+R, y+R, fill=color, \
                                    outline="black", width=1)

def main():
    print "Initializing cameras..."
    pyoptitrack.waitForInitialization()
    cameras = pyoptitrack.getCameraList()

    leftCamera = Camera(cameras[0], 0)
    rightCamera = Camera(cameras[1], 1)
    
    root = Tk()
    blobFrame = BlobFrame(root, leftCamera, rightCamera)
    dims = (BOARD_SIZE[0]*SCALE, BOARD_SIZE[1]*SCALE)
    root.geometry("%dx%d+0+0" % dims) # WIDTHxHEIGHT+X+Y
    root.mainloop()

    print 'Shutting down...'
    pyoptitrack.shutdown()


if __name__ == '__main__':
    main()

