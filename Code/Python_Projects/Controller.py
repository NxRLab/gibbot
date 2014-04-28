from math import *
import numpy as np
from GibbotModel import *

"""
Controller classes below.

A Controller has a 'control' method that accepts a GibbotModel as its only argument
and returns an accelleration scalar (q2dd).  Eventually, they will also return magnet commands.

Controllers may store an internal state.  Controllers shoud NOT modify the GibbotModel argument.
"""

class Controller:
    name = 'Null'
    def control(self, bot):
        return 0

class SpongSwingUpController(Controller):
    name = 'Spong Swing Up'
    def __init__(self):
        # Carefully tuned gains (will change if robot parameters change)
        self.kp = 470.       # Spring force based on position
        self.kd = 100.       # Spring force based on velocities (high limits velocities)
        self.alpha = pi/5   # q2 should stay within +/-alpha

    def control(self, bot):
        # gains
        kp = self.kp
        kd = self.kd
        alpha = self.alpha

        # parameters
        q1 = bot.q1
        q2 = bot.q2
        q1d = bot.q1d
        q2d = bot.q2d
        c2 = cos(q2)

        s1 = sin(q1)
        s2 = sin(q2)
        s12 = sin(q1 + q2)

        m1 = bot.m1
        I1 = bot.I1
        m2 = bot.m2
        I2 = bot.I2

        r1 = bot.r1
        l1 = bot.l1
        r2 = bot.r2
        l2 = bot.l2

        g = bot.g

        # mass matrix = [a b;b c]
        a = I1 + I2 + m1*r1**2 + m2*l1**2 + m2*r2**2 + 2.*m2*r2*l1*c2
        b = m2*r2**2 + m2*r2*l1*c2 + I2
        c = I2 + m2*r2**2

        # coriolis/centrifugal forces = [-d*q2d -d(q1d+q2d); d*q1d 0]
        d = m2*r2*l1*s2;

        # gravity = g*[e+f; f]
        e = (m1*r1 + m2*l1) * s1
        f = m2*r2*s12

        # controller
        q2d_hat = alpha*atan(q1d)
        v = kp*(q2d_hat - q2) - kd*q2d
        U = -(1./a)*(b*e*g - a*f*g+b*f*g-a*d*q1d**2
                     - 2.*b*d*q1d*q2d - b*d*q2d**2 + b**2*v - a*c*v)
        return U

class SpongBalanceController(Controller):
    name = 'Spong Balance'
    def control(self, bot):

        #The papers A, B, and K matrices for their robot
        '''q1_adjusted = bot.q1 - pi if bot.q1 > 0 else bot.q1 + pi

        X = np.mat([[q1_adjusted],
                    [bot.q2],
                    [bot.q1d],
                    [bot.q2d]])


        K = np.mat([-242.52, -96.33, -104.59, -49.05])'''

        #Our Calculated A, B, and K Matrices for the papers robot
        #bot.q1 = bot.q1 % (2*pi)
        #bot.q2 = bot.q2 % (2*pi)
        #q1_adjusted = bot.q1 - pi if bot.q1 > 0 else bot.q1 + pi

        # X = np.mat([[q1_adjusted],
        #             [bot.q2],
        #             [bot.q1d],
        #             [bot.q2d]])

        X = np.mat([[bot.q1],
                    [bot.q2],
                    [bot.q1d],
                    [bot.q2d]])

        Xd = np.mat([[pi],
                    [0],
                    [0],
                    [0]])

        tau = 2*pi
        e = X - Xd
        e[0] = e[0] % tau
        e[0] = e[0] - tau if e[0] > pi else e[0]
        e[1] = e[1] % tau
        e[1] = e[1] - tau if e[1] > pi else e[1]

        K = np.mat([-70.76723814, -21.38274773, -64.75693739, -22.72923491])
        u = -K*e;
        return u

class ThrashSwingController(Controller):
    name = 'Thrash, Swing'

    # states
    ThrashLeft=1
    ThrashRight=2
    SwingUp=3

    def __init__(self):
        self.swingUpController = SpongSwingUpController()
        self.state = self.SwingUp

    def control(self, bot):
        # Gains
        beginThrashEnergy = -5.1
        endThrashEnergy = 0
        thrashAngleLimit = pi/2

        energy = bot.energy
        #print energy

        # Did the energy cross a state change boundary?
        if self.state == self.SwingUp:
            if energy < beginThrashEnergy:
                avgMassX = (bot.m1*bot.m1x + bot.m2*bot.m2x) / (bot.m1 + bot.m2)
                if avgMassX < bot.x1:
                    self.state = self.ThrashRight
                else:
                    self.state = self.ThrashLeft
        elif self.state == self.ThrashLeft:
            if energy > endThrashEnergy:
                self.state = self.SwingUp
            elif bot.q2 > thrashAngleLimit:
                self.state = self.ThrashRight
        elif self.state == self.ThrashRight:
            if energy > endThrashEnergy:
                self.state = self.SwingUp
            elif bot.q2 < -thrashAngleLimit:
                self.state = self.ThrashLeft

        # Control for state
        if self.state == self.SwingUp:
            #print 'SWING UP'
            return self.swingUpController.control(bot)
        elif self.state == self.ThrashLeft:
            #print 'THRASH LEFT'
            return +bot.maxTorque
        elif self.state == self.ThrashRight:
            #print 'THRASH RIGHT'
            return -bot.maxTorque

