from math import *
import numpy as np
from GibbotModel import *

# All controllers should return an accelleration scalar (q2dd).
# Controllers shoud NOT modify the bot directly.

def nullController(bot):
    return 0

def spongCombined(bot):
    if bot.q1 < -3. or bot.q1 > 3.:
        return spongBalanceController(bot)
    else:
        return spongSwingUpController(bot)

def spongSwingUpController(bot):
    alpha = pi/10.
    #Our Gains
    #Spring force based on velocities(high limits velocities)
    kd = 8.
    kp = 20.    #Spring force based on position

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

def spongBalanceController(bot):

    #The papers A, B, and K matrices for their robot
    '''q1_adjusted = bot.q1 - pi if bot.q1 > 0 else bot.q1 + pi

    X = np.mat([[q1_adjusted],
                [bot.q2],
                [bot.q1d],
                [bot.q2d]])


    K = np.mat([-242.52, -96.33, -104.59, -49.05])'''

    #Our Calculated A, B, and K Matrices for the papers robot
    q1_adjusted = bot.q1 - pi if bot.q1 > 0 else bot.q1 + pi

    X = np.mat([[q1_adjusted],
                [bot.q2],
                [bot.q1d],
                [bot.q2d]])


    K = np.mat([-0.36783936, 0.91115534, 5.61962985, 3.58265142])

    # K = np.mat([-57.379, -23.5845, -45.0506, -21.1648])

    u = -K*X;
    return u


