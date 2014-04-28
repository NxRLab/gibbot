from math import *
import numpy as np
import scipy as sp
from scipy import linalg


def getKMatrix():
    '''Computes the 1x4 gain matrix for the Spong balance controller'''

    # Gibbot physical params
    g = 9.81

    q1 = pi
    q2 = 0
    q1d = 0
    q2d = 0
    u = 0

    m1 = 1
    m2 = 1

    l1 = .267
    l2 = .267

    r1 = .107
    r2 = .156

    I1 = m1 * (l1**2 / 3 + .077**2 / 12)
    I2 = m2 * (l2**2 / 3 + 0.077**2 / 12)

    # Scaling/non-dimensionalizing
    dx = l1+l2
    dt = sqrt((l1+l2)/g)
    du = g*m2*r2

    # Simplification
    s1 = sin(q1)
    c1 = cos(q1)
    s2 = sin(q2)
    c2 = cos(q2)
    s12 = sin(q1+q2)
    c12 = cos(q1+q2)

    b = (m1*r1 + m2*l1)/(m2*r2)         # Beta

    G = (g*dt**2)/dx                    # Gamma = 1

    K1 = (1./dx)*(I2/(m2*r2)+r2)

    K2 = (1./dx)*((I1+m1*r1**2)/(m2*r2) + (l1**2)/r2)

    d1 = l1/dx                           # Delta

    # b = 18
    # G = 1
    # K1 = .276829359066204
    # K2 = 8.842649843207664
    # d1 = .5


    A = np.array([[0,0,1,0],[0,0,0,1],[(-(b*G*K1*c1) + d1*G*c2*c12)/(K1*K2 - (d1**2)*(c2**2)),(-2*(d1**2)*c2*s2*(K1*(-(G*u) - b*G*s1 + d1*((q1d + q2d)**2)*s2) + d1*c2*(d1*(q1d**2)*s2 + G*(-u + s12))))/((K1*K2 - (d1**2)*(c2**2))**2) + (d1*K1*((q1d + q2d)**2)*c2 + d1*c2*(d1*(q1d**2)*c2 + G*c12) - d1*s2*(d1*(q1d**2)*s2 + G*(-u + s12)))/(K1*K2 - (d1**2)*(c2**2)),(2*d1*K1*(q1d + q2d)*s2 + 2*(d1**2)*q1d*c2*s2)/(K1*K2 - (d1**2)*(c2**2)),(2*d1*K1*(q1d + q2d)*s2)/(K1*K2 - (d1**2)*(c2**2))],[-((G*(K1 + K2 + 2*d1*c2)*c12 + (K1 + d1*c2)*(-(b*G*c1) - G*c12))/(K1*K2 - (d1**2)*(c2**2))),(2*(d1**2)*c2*s2*((K1 + d1*c2)*(-(b*G*s1) + d1*q2d*(2*q1d + q2d)*s2 - G*s12) + (K1 + K2 + 2*d1*c2)*(d1*(q1d**2)*s2 + G*(-u + s12))))/((K1*K2 - (d1**2)*(c2**2))**2) - ((K1 + d1*c2)*(d1*q2d*(2*q1d + q2d)*c2 - G*c12) + (K1 + K2 + 2*d1*c2)*(d1*(q1d**2)*c2 + G*c12) - d1*s2*(-(b*G*s1) + d1*q2d*(2*q1d + q2d)*s2 - G*s12) - 2*d1*s2*(d1*(q1d**2)*s2 + G*(-u + s12)))/(K1*K2 - (d1**2)*(c2**2)),-((2*d1*q2d*(K1 + d1*c2)*s2 + 2*d1*q1d*(K1 + K2 + 2*d1*c2)*s2)/(K1*K2 - (d1**2)*(c2**2))),-(((K1 + d1*c2)*(d1*q2d*s2 + d1*(2*q1d + q2d)*s2))/(K1*K2 - (d1**2)*(c2**2)))]])

    B = np.array([[0],[0],[(-(G*K1) - d1*G*c2)/(K1*K2 - (d1**2)*(c2**2))],[(G*(K1 + K2 + 2*d1*c2))/(K1*K2 - (d1**2)*(c2**2))]])

    Q = np.array([[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]])

    R = np.array([[1]])

    P = sp.linalg.solve_continuous_are(A, B, Q, R)

    K = np.dot(np.linalg.inv(R), np.dot(B.transpose(),P))
    
    print "A = ", A
    print "B = ", B
    print "Q = ", Q
    print "R = ", R


    return K


if __name__ == '__main__':
    K = getKMatrix()
    print "K = ", K
