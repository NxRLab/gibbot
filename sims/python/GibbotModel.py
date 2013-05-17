from math import *
import numpy as np

class GibbotModel:
    def __init__(self, q1, q2, q1d=0., q2d=0.):
        # State
        self.q1 = q1
        self.q2 = q2
        self.q1d = q1d
        self.q2d = q2d

        # Currently our gibbot guesstimated parameters
        # Link Masses
        self.m1 = 1. #3.083276839957533
        self.m2 = 1.5 #3.083276839957533
        # Link Lengths
        self.l1 = 1. #0.610
        self.l2 = 1. #0.610
        # Length to Link's Center of Mass
        self.r2 = .7 #6.37687066165708e-2
        self.r1 = .3 #self.l1 - self.r2
        # Moments of Inertia
        self.I1 = .33 #5.386568898408416e-2
        self.I2 = .33 #5.386568898408416e-2
        # Gravity
        self.g = 9.81
        # Torque
        self.MAX_T = 100

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



