from math import *
import numpy as np

def getKMatrix(self):


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

    B = (m1*r1 + m2*l1)/(m2*r2)         # Beta

    G = (g*dt**2)/dx                    # Gamma = 1

    K1 = (1./dx)*(I2/(m2*r2)+r2)

    K2 = (1./dx)*((I1+m1*r1**2)/(m2*r2) + (l1**2)/r2)

    D = l1/dx                           # Delta


    A = np.array([[0,0,1,0],[0,0,0,1],[(-(b*g*K1*c1) + d1*g*c2*c12)/(K1*K2 - (q1**2)*(c2**2)),(-2*(q1**2)*c2*s2*(K1*(-(g*u) - b*g*s1 + d1*((q1d + q2s)**2)*s2) + d1*c2*(d1*(q1d**2)*s2 + g*(-u + s12))))/((K1*K2 - (q1**2)*(c2**2))**2) + (d1*K1*((q1d + q2s)**2)*c2 + d1*c2*(d1*(q1d**2)*c2 + g*c12) - d1*s2*(d1*(q1d**2)*s2 + g*(-u + s12)))/(K1*K2 - (q1**2)*(c2**2)),(2*d1*K1*(q1d + q2d)*s2 + 2*(q1**2)*q1d*c2*s2)/(K1*K2 - (q1**2)*(c2**2)),(2*d1*K1*(q1d + q2d)*s2)/(K1*K2 - (q1**2)*(c2**2))],[-((g*(K1 + K2 + 2*d1*c2)*c12 + (K1 + d1*c2)*(-(b*g*c1) - g*c12))/(K1*K2 - (q1**2)*(c2**2))),(2*(q1**2)*c2*s2*((K1 + d1*c2)*(-(b*g*s1) + d1*q2d*(2*q1d + q2d)*s2 - g*s12) + (K1 + K2 + 2*d1*c2)*(d1*(q1d**2)*s2 + g*(-u + s12))))/((K1*K2 - (q1**2)*(c2**2))**2) - ((K1 + d1*c2)*(d1*q2d*(2*q1d + q2d)*c2 - g*c12) + (K1 + K2 + 2*d1*c2)*(d1*(q1d**2)*c2 + g*c12) - d1*s2*(-(b*g*s1) + d1*q2d*(2*q1d + q2d)*s2 - g*s12) - 2*d1*s2*(d1*(q1d**2)*s2 + g*(-u + s12)))/(K1*K2 - (q1**2)*(c2**2)),-((2*d1*q2d*(K1 + d1*c2)*s2 + 2*d1*q1d*(K1 + K2 + 2*d1*c2)*s2)/(K1*K2 - (q1**2)*(c2**2))),-(((K1 + d1*c2)*(d1*q2d*s2 + d1*(2*q1d + q2d)*s2))/(K1*K2 - (q1**2)*(c2**2)))]])

    B = np.array([0,0,-(g*K1) - d1*g*c2 1/(K1*K2 - (q1**2)*(c2**2)),g K1 + K2 + 2*d1*c2 1/(K1*K2 - (q1**2)*(c2**2))])

    '''Still need to add Q and R matrices along with figure out whether "g" in the A/B Matrices should be gravity or Gamma'''

    '''Using scipy.linalg.solve_continuous_are(a, b, q, r) I will be returned P (a 4x4 Matrix). Finally I solve for K using the equation K = (R^-1)*(B^T)*P.'''


