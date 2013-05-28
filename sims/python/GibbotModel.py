from math import *
import numpy as np

class GibbotModel:
    def __init__(self, x1, y1, q1, q2, q1d=0., q2d=0.):
        # State
        self.x1 = x1
        self.y1 = y1
        self.q1 = q1
        self.q2 = q2
        self.q1d = q1d
        self.q2d = q2d

        # Currently our gibbot guesstimated parameters
        # Link Masses (Kg)
        self.m1 = 0.9
        self.m2 = 1.1
        # Link Lengths (m)
        self.l1 = 0.267
        self.l2 = 0.267
        # Length to Link's Center of Mass (m)
        self.r1 = .107
        self.r2 = .156
        # Moments of Inertia (Kg*m^2 - assume thin rectangular plate about its end)
        self.I1 = self.m1 * (self.l1**2 / 3 + 0.077**2 / 12)
        self.I2 = self.m2 * (self.l2**2 / 3 + 0.077**2 / 12)
        # Gravity
        self.g = 9.81
        # Torque
        self.MAX_T = 5

    @property
    def cx(self):
        return self.x1 + self.l1*cos(self.q1 + pi/2)

    @property
    def cy(self):
        return self.y1 + self.l1*sin(self.q1 + pi/2)

    @property
    def x2(self):
        return self.cx + self.l2*cos(self.q1 + pi/2 + self.q2)

    @property
    def y2(self):
        return self.cy + self.l2*sin(self.q1 + pi/2 + self.q2)

    def __repr__(self):
        return '(q1={}, q2={}, q1d={}, q2d={})'.format(self.q1, self.q2, self.q1d, self.q2d)

    def switch(self):
        x = self.x2
        y = self.y2
        q1 = self.q1 + self.q2 + pi
        q2 = -self.q2

        self.x1 = x
        self.y1 = y
        self.q1 = q1
        self.q2 = q2
        self.q1d = 0
        self.q2d = 0

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
        '''Initialize Parameters'''
        # Link Masses
        m1 = self.m1
        m2 = self.m2
        # Link Lengths
        l1 = self.l1
        l2 = self.l2
        # Length to Link's Center of Mass
        r1 = self.r1
        r2 = self.r2
        # Moments of Inertia
        I1 = self.I1
        I2 = self.I2
        # Gravity
        g = self.g

        # Scaling
        dx = l1+l2
        dt = sqrt((l1+l2)/g)
        du = g*m2*r2


        '''Simplified Variables'''
        B = (m1*r1 + m2*l1)/(m2*r2)         # Beta

        G = (g*dt**2)/dx                    # Gamma = 1

        K1 = (1./dx)*(I2/(m2*r2)+r2)

        K2 = (1./dx)*((I1+m1*r1**2)/(m2*r2) + (l1**2)/r2)

        D = l1/dx                           # Delta
		
        #print B, G, K1, K2, D


        '''State Updates'''

        q1 = self.q1
        q2 = self.q2
        q1d = self.q1d
        q2d = self.q2d
        qd = np.mat([[q1d],
                     [q2d]])
        s1 = sin(q1)
        c1 = cos(q1)
        s2 = sin(q2)
        c2 = cos(q2)
        s12 = sin(q1+q2)
        c12 = cos(q1+q2)

        U = controller(self)
        if U > self.MAX_T:
            print U, '>', self.MAX_T
            U = self.MAX_T
        elif U < -self.MAX_T:
            print U, '<', -self.MAX_T
            U = -self.MAX_T
        u = np.mat([[0],
                    [U]])

        M = dt * np.mat([[K1+K2+2*D*c2, D*c2+K1],
                    [K1+D*c2, K1]])


        C = dt * np.mat([[-D*s2*q2d, -D*s2*(q1d+q2d)],
                    [D*s2*q1d, 0]])

        g = G * np.mat([[B*s1+s12],
                        [s12]])


        M2 = np.linalg.inv(M)*(u-C*qd-g)

        q1dd = M2[0,0]
        q2dd = M2[1,0]

        return (q1dd, q2dd)



