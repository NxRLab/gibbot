function S = mbgen(pd, X0, T)
% non-dim parameters for symmetric links
[p, nd2d] = nondim(pd);
S.p = p;
S.nd2d = nd2d;

% uniform color for all plots
S.color = 'bg';

if nargin == 1
    return
end

% normalized initial conditions
dt = nd2d(end);
S.X0 = X0;
S.X0(1:4) = diag(nd2d(1:4))\X0(1:4);
S.X0(5:8) = diag(nd2d(1:4))\X0(5:8)*dt;

% normalized time
S.T = T/dt;
end

function [nd, nd2d] = nondim(pd)
g = pd(1); % gravity
I1 = pd(2); % link 1 Inertia about CoM
I2 = pd(3); % link 2 Inertia about CoM
L1 = pd(4); % link 1 link length
L2 = pd(5); % link 2 link length
m1 = pd(6); % link 1 CoM mass
m2 = pd(7); % link 2 CoM mass
r1 = pd(8); % link 1 distance to CoM
r2 = pd(9); % link 2 distance to CoM

% normalized-variables-to-variables conversion factor
du = g*m2*r2;
dt = sqrt((L1 + L2)/g);
d = L1 + L2;
nd2d = [d, d, 1, 1, du, dt];

% normalized constants
alpha = (d*(m1 + m2))/(m2*r2);
beta = (m1*r1 + m2*L1)/(m2*r2);
delta1 = L1/d;
delta2 = L2/d;
gamma = (g*dt^2)/d;
kappa1 = (1/d)*(I2/(m2*r2) + r2);
kappa2 = (1/d)*((I1 + m1*r1^2)/(m2*r2) + L1^2/r2);
rho1 = r1/d;
rho2 = r2/d;

nd = [alpha, beta, delta1, delta2, gamma, kappa1, kappa2, rho1, rho2];
end