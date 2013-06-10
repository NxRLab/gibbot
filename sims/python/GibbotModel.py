from math import *
import numpy as np

class GibbotModel:
    def __init__(self, x1, y1, q1, q2, q1d=0., q2d=0.):
        # State
        self.x1 = float(x1)
        self.y1 = float(y1)
        self.q1 = float(q1)
        self.q2 = float(q2)
        self.q1d = float(q1d)
        self.q2d = float(q2d)

        # Currently our gibbot guesstimated parameters
        # Link Masses (Kg)
        self.m1 = 1.0
        self.m2 = 1.0
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
        self.maxTorque = 5

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

    @property
    def m1x(self):
        return self.x1 + self.r1*cos(self.q1 + pi/2)
    @property
    def m1y(self):
        return self.y1 + self.r1*sin(self.q1 + pi/2)

    @property
    def m2x(self):
        return self.cx + self.r2*cos(self.q1 + pi/2 + self.q2)
    @property
    def m2y(self):
        return self.cy + self.r2*sin(self.q1 + pi/2 + self.q2)

    @property
    def energy(self):
        # Potential Energy: m * g * h
        pe1 = self.m1 * self.g * (self.y1 - self.m1y)
        pe2 = self.m2 * self.g * (self.y1 - self.m2y)

        # Kinetic Energy: 1/2 * mass * (tangential velocity)^2
        v1 = self.q1d * self.r1
        v2 = (self.q1d + self.q2d) * sqrt(self.m2x**2 + self.m2y**2)
        ke1 = 0.5 * self.m1 * v1**2
        ke2 = 0.5 * self.m2 * v2**2

        # print 'pe1={:.3f}, pe2={:.3f}, ke1={:.3f}, ke2={:.3f}'.format(pe1, pe2, ke1, ke2)
        return pe1 + pe2 + ke1 + ke2

    def __repr__(self):
        params = (self.x1, self.y1, self.q1, self.q2, self.q1d, self.q2d)
        return '(x1={}, y1={}, q1={}, q2={}, q1d={}, q2d={})'.format(*params)

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
        self.normalizeAngles()

    def advanceState(self, controller, dt):
        # second order
        (q1dd, q2dd) = self.getAccelerations(controller)

        # first order
        self.q1d += q1dd * dt
        self.q2d += q2dd * dt

        # zeroth order
        self.q1 += self.q1d * dt
        self.q2 += self.q2d * dt
        self.normalizeAngles()


    def normalizeAngles(self):
        # constrain to [-pi, +pi]
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

        U = controller.control(self)
        if U > self.maxTorque:
            print U, '>', self.maxTorque
            U = self.maxTorque
        elif U < -self.maxTorque:
            print U, '<', -self.maxTorque
            U = -self.maxTorque
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



