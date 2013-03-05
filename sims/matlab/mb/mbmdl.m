function S = mbmdl(x0, u, T, options)
% kg & m^2*kg
m = 3.083276839957533; % CoM
I = 5.386568898408416e-2; % Inertia about CoM

% meters
L = 0.610;  % link length
r2 = 6.37687066165708e-2; % link 2 distance to CoM
r1 = L - r2; % link 1 distance to CoM

% m/s^2
g = 9.81; % gravity

% dimensionalized constants
pd = [g I I L L m m r1 r2];

X0 = zeros(numel(x0)*2, 1);
X0(3:8:end) = x0(1:4:end);
X0(4:8:end) = x0(2:4:end);
X0(7:8:end) = x0(3:4:end);
X0(8:8:end) = x0(4:4:end);

S = mbgen(pd);
S.X0 = X0;
S.T = T;
S.ctls = u;

if nargin == 4
    S.options = options;
else
    S.options = odeset('RelTol',1e-6,'AbsTol',1e-6);
end