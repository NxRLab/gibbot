from math import *

class MonkeyBot:
    def __init__(self, q1, q2, q1d=0, q2d=0):
        self.q1 = q1
        self.q2 = q2
        self.q1d = q1d
        self.q2d = q2d

    def __repr__(self):
        return '(q1={}, q2={}, q1d={}, q2d={})'.format(self.q1, self.q2, self.q1d, self.q2d)

    def advanceState(self, controller, dt):
        # third order
        (q1dd, q2dd) = self.getKinematicAccelerations()
        q2dd += controller(self)

        # second order
        self.q1d += q1dd * dt
        self.q2d += q2dd * dt

        # first order
        self.q1 += self.q1d * dt
        self.q2 += self.q2d * dt

        # normalize angles
        self.q1 = self.q1 % (pi*2)
        if self.q1 > pi:
            self.q1 -= 2*pi
        self.q2 = self.q2 % (pi*2)
        if self.q2 > pi:
            self.q2 -= 2*pi

    def getKinematicAccelerations(self):
        return (0, 0) # Still need to implement...

