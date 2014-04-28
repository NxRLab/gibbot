function spong()
path(path, './mbot')

% kg & m^2*kg
M(1)=1; % link 1 CoM mass
M(2)=0.083; %link 1 Inertia about CoM
M(3)=1; % link 2 CoM mass
M(4)=0.33; % link 2 Inertia about CoM

% meters
L(1)=0.5; % link 1 distance to CoM
L(2)=1;  % link 1 link length
L(3)=1; % link 2 distance to CoM
L(4)=2;  % link 2 link length

% m/s^2
g=9.8; % gravity

% external forces, e.g., dissipative and control forces
U = @controller2;

% initial condition and state
X0=zeros(8,1);
X0(3) = -pi/2;
X0(4) = 0;

% monkeybot simulation parameters
S = struct('U', U, 'M', M, 'L', L, 'g', g, 'ton', 3, 'tdelta', 1, 'color', 'bg');
options = odeset('RelTol',1e-9,'AbsTol',1e-9);

% swing up
tspan=0:.1:15;
mplot = mbot_plot('all', S);
opts = odeset(options);
F = mbot_eom('dof2', S);
[T1, X1] = ode45(F, tspan, X0, opts);
UU = zeros(length(T1), 2);
for i = 1:length(T1)
    [ui vi] = U(T1(i), X1(i,:), S);
    UU(i,:) = [sum(ui), vi];
end

opts = odeset(options);
tspan=15:.1:20;
[T2, X2] = ode45(@linode, tspan, X1(end,:), opts);

mplot([], [], 'init');
for i = 1:length(T1)
    mplot(T1(i), X1(i,:)', '');
end

X2(:,3) = X2(:,3) + pi;
for i = 1:length(T2)
   mplot(T2(i), X2(i,:)', '');
end

figure
plot(T1, [X1(:,4), UU]);
legend('q4', 'u', 'v');

end

function [U, v] = controller2(t, X, S)
alpha = pi/10;
kd = 8;
kp = 20;

% parameters
c2 = cos(X(4));

s1 = sin(X(3));
s2 = sin(X(4));
s12 = sin(X(3) + X(4));

M = S.M;
L = S.L;
g = S.g;

% mass matrix = [a b;b c]
a = M(2)+M(4)+M(1)*L(1)^2+M(3)*L(2)^2+M(3)*L(3)^2+2*M(3)*L(3)*L(2)*c2;
b = M(3)*L(3)^2+M(3)*L(3)*L(2)*c2+M(4);
c = M(4)+M(3)*L(3)^2;

% coriolis/centrifugal forces = [-d*X(8) -d(X(7)+X(8)); d*X(7) 0]
d = M(3)*L(3)*L(2)*s2;

% gravity = g*[e+f; f]
e = (M(1)*L(1)+M(3)*L(2))*s1;
f = M(3)*L(3)*s12;

% controller
q2d = alpha*atan(X(7));
v = kp*(q2d-X(4))-kd*X(8);
U = [0;0;0;-(1/a)*(b*e*g-a*f*g+b*f*g-a*d*X(7)^2 - ...
    2*b*d*X(7)*X(8)-b*d*X(8)^2+b^2*v-a*c*v)];
end

function U = controller1(t, X, S)
kd = 8;
kp = 20;
% parameters
c2 = cos(X(4));

s1 = sin(X(3));
s2 = sin(X(4));
s12 = sin(X(3) + X(4));

M = S.M;
L = S.L;
g = S.g;

% mass matrix = [a b;b c]
a = M(2)+M(4)+M(1)*L(1)^2+M(3)*L(2)^2+M(3)*L(3)^2+2*M(3)*L(3)*L(2)*c2;
b = M(3)*L(3)^2+M(3)*L(3)*L(2)*c2+M(4);
c = M(4)+M(3)*L(3)^2;

% coriolis/centrifugal forces = [-d*X(8) -d(X(7)+X(8)); d*X(7) 0]
d = M(3)*L(3)*L(2)*s2;

% gravity = g*[e+f; f]
e = (M(1)*L(1)+M(3)*L(2))*s1;
f = M(3)*L(3)*s12;

% controller follows constant reference of pi
v = -kd*X(7) + kp*(pi - X(3));
U = [0;0;0;
    (b-c*a/b)*v+d*(c/b*(X(7)*X(8)+(X(7)+X(8))*X(8))+X(7)^2) - ...
    g*(c/b*(e+f)-f)];
end

function dX = linode(t, X)
dX = zeros(8,1);

A = [
    0 0 1 0;
    0 0 0 1;
    12.49 -12.54 0 0;
    -14.49 29.36 0 0
    ];

B = [0;0;-2.98;5.98];

K = [-242.52 -96.33 -104.59 -49.05];
u = -K*X([3 4 7 8]);


dX([3 4 7 8]) = A*X([3 4 7 8]) + B*u;
end

function [value, stop, direction] = event(t, X)

value = X(3) - pi;
stop = 1;
direction = 0;
end