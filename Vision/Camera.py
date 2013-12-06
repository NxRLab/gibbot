import pyoptitrack
from Tkinter import *
import numpy as np
import traceback
import math

BOARD_SIZE = (2394.0, 1231.9) # in millimeters
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
    def __init__(self, UID, numericLabel, isLeftCamera):
        self.UID = UID
        self.isLeftCamera = isLeftCamera
        self.blobs = []
        self.tBlobs = []
        self.transform = None
        pyoptitrack.startCamera(UID, numericLabel, self.gotBlobs)
        pyoptitrack.setIntensityForCamera(UID, 0)
        dims = pyoptitrack.getDimensionsForCamera(UID)
        self.dimensions = (dims[1], dims[0]) # rotate 90 degrees
        
        # [NW, SW, SE, NE]
        self.cameraCorners = np.array([[0,0],
                                       [0, self.dimensions[1]],
                                       self.dimensions,
                                       [self.dimensions[0], 0]],
                                      np.float32)
        self.worldCorners = np.array([[0,0],
                                      [0, BOARD_SIZE[1]],
                                      [BOARD_SIZE[0]/2, BOARD_SIZE[1]],
                                      [BOARD_SIZE[0]/2, 0]],
                                     np.float32)

    def gotBlobs(self, camera, blobs):
        try:
            # rotate coordinates 90 degrees and save
            self.blobs = [(b[1], self.dimensions[1]-b[0]) for b in blobs]
        except Exception as e:
            traceback.print_exc(e)

    def transformBlobs(self):
        blobs = self.blobs
        if len(blobs) < 4:
            self.transform = None
            self.tBlobs = []
            return

        # prepare to search for corner blobs
        cornerBlobs = [None]*4 # [NW, SW, SE, NE]
        if self.isLeftCamera:
            cornerIndexForNDistance = 0
            cornerIndexForSDistance = 1
            cornerIndexForNAngle = 3
            cornerIndexForSAngle = 2
        else:
            cornerIndexForNDistance = 3
            cornerIndexForSDistance = 2
            cornerIndexForNAngle = 0
            cornerIndexForSAngle = 1

        # find first 2 corner blobs by shortest distance to frame corner
        for cornerIdx in [cornerIndexForNDistance, cornerIndexForSDistance]:
            corner = self.cameraCorners[cornerIdx]
            bestDistSq = float('inf')
            bestBlob = None
            for blob in blobs:
                distSq = (corner[0]-blob[0])**2 + (corner[1]-blob[1])**2
                if distSq < bestDistSq:
                    bestDistSq = distSq
                    bestBlob = blob
            cornerBlobs[cornerIdx] = bestBlob

        # find other 2 corner blobs by angle from first 2 corner blobs
        bestNAngle = +math.pi
        bestNBlob = None
        bestSAngle = -math.pi
        bestSBlob = None
        NCornerBlob = cornerBlobs[cornerIndexForNDistance]
        SCornerBlob = cornerBlobs[cornerIndexForSDistance]
        if self.isLeftCamera:
            xScale = 1
        else:
            xScale = -1
        potentialAngleBlobs = set(blobs) - set([NCornerBlob, SCornerBlob])
        for blob in potentialAngleBlobs:
            hx = (blob[0] - NCornerBlob[0]) * xScale
            hy = blob[1] - NCornerBlob[1]
            NAngle = math.atan2(hy, hx)
            if NAngle < bestNAngle:
                bestNAngle = NAngle
                bestNBlob = blob
            lx = (blob[0] - SCornerBlob[0]) * xScale
            ly = blob[1] - SCornerBlob[1]
            SAngle = math.atan2(ly, lx)
            if SAngle > bestSAngle:
                bestSAngle = SAngle
                bestSBlob = blob
        cornerBlobs[cornerIndexForNAngle] = bestNBlob
        cornerBlobs[cornerIndexForSAngle] = bestSBlob

        # calculate a new transform matrix
        arrs = [np.array(corner, np.float32) for corner in cornerBlobs]
        pts8 = np.vstack((arrs[0], arrs[1], arrs[2], arrs[3], self.worldCorners))
        try:
            self.transform = get_transform_data(pts8, False)
        except np.linalg.LinAlgError:
            pass

        # populate tBlobs by applying transform blobs
        self.tBlobs = []
        if self.transform is not None:
            for b in blobs:
                if b not in cornerBlobs:
                    tb = self.fromCameraToBoard(b)
                    if tb:
                        self.tBlobs += [tb]

    def fromCameraToBoard(self, coord):
        T = self.transform
        if T is None:
            return None
        b = coord
        denom = T[6]*b[0] + T[7]*b[1] + 1
        if denom == 0:
            return None # Bad precision
        x = (T[0]*b[0] + T[1]*b[1] + T[2]) / denom
        y = (T[3]*b[0] + T[4]*b[1] + T[5]) / denom
        return (x, y)
    
    def clusterNodes(self):
        ''' Sets self.nodes as a dictionary where the key is the number of blobs in the cluster (1-3)
         and the value is the average position of the blobs as a tuple (x,y) '''

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
