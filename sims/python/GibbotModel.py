from math import *

class GibbotModel:
    def __init__(self, q1, q2, q1d=0, q2d=0):
        self.q1 = q1
        self.q2 = q2
        self.q1d = q1d
        self.q2d = q2d

    def __repr__(self):
        return '(q1={}, q2={}, q1d={}, q2d={})'.format(self.q1, self.q2, self.q1d, self.q2d)

    def advanceState(self, controller, dt):
        # second order
        (q1dd, q2dd) = self.getAccelerations(controller)

        # first order
        self.q1d += q1dd * dt
        self.q2d += q2dd * dt

        # zeroth order
        self.q1 += self.q1d * dt
        self.q2 += self.q2d * dt

        # normalize angles [-pi, +pi]
        self.q1 = self.q1 % (pi*2)
        if self.q1 > pi:
            self.q1 -= 2*pi
        self.q2 = self.q2 % (pi*2)
        if self.q2 > pi:
            self.q2 -= 2*pi

    def getAccelerations(self, controller):
        q1 = self.q1
        q2 = self.q2
        q1d = self.q1d
        q2d = self.q2d
        s1 = sin(q1)
        c1 = cos(q1)
        s2 = sin(q2)
        c2 = cos(q2)
        q1dd = 0 # still need to implement...
        q2dd = 0

        q2dd += controller(self)

        return (q1dd, q2dd)

