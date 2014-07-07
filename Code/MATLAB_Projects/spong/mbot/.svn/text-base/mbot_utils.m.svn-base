function [out, varargout] = mbot_utils(info, t, X, S)
switch lower(info)
    case 'xy'
        [out varargout{1}] = q2x(X, S);
    case 'energy'
        out = energy(X, S);
    case 'power'
        out = power(t, X, S);
    case 'mass'
        out = mm(X, S);
    case 'flip'
        [out varargout{1}] = flipXY(X, S);
end
end

function [XY dXYdt] = q2x(X, S)
%Q2X converts configuration space coordinates to cartesian coordinates.
L = S.L;

x=X(1);
y=X(2);
w1=X(7);
w2=X(7)+X(8);

c1=cos(X(3));
c12=cos(X(3)+X(4));

s1=sin(X(3));
s12=sin(X(3)+X(4));

% location of 1st CoM
x1=L(1)*s1+x;
y1=-L(1)*c1+y;

% location of bottom of 1st link
x2=L(2)*s1+x;
y2=-L(2)*c1+y;

% location of 2nd CoM
x3=x2+L(3)*s12;
y3=y2-L(3)*c12;

% location of bottom of 2nd link
x4=x2+L(4)*s12;
y4=y2-L(4)*c12;

XY = [x y; x1 y1;x2 y2; x3 y3; x4 y4];

% velocities
dXYdt = [X(5), X(6);
    X(5)+L(1)*c1*w1, X(6)+L(1)*s1*w1;
    X(5)+L(2)*c1*w1+L(3)*c12*w2, X(6)+L(2)*s1*w1+L(3)*s12*w2;
    X(5)+L(2)*c1*w1+L(4)*c12*w2, X(6)+L(2)*s1*w1+L(4)*s12*w2
    ];
end

function E = energy(X, S)

c1 = cos(X(3));
c12 = cos(X(3)+X(4));

M = S.M;
L = S.L;
g = S.g;

MM = mm(X, S);

ke = 1/2*X(5:8)'*MM*X(5:8);
pe = g*(M(1)*(X(2)-L(1)*c1) + M(3)*(X(2)-L(3)*c12-L(2)*c1));

E = [ke pe];
end

function P=power(t, X, S)
% d(KE)/dt = d/dt (dq/dt*MM*dq/dt) = dq/dt*MM*d^2(q)/dt^2 +
% 1/2*dq/dt*d(MM)/dt*dq/dt

% parameters
c1 = cos(X(3));
c12 = cos(X(3)+X(4));

s1 = sin(X(3));
s2 = sin(X(4));
s12 = sin(X(3)+X(4));

M = S.M;
L = S.L;
g = S.g;

% velocity and acceleration
F = mbot_eom('dof4', S);
dXdt = F(t, X);

% components for dMM/dt
dAdt = [0 0;0 0];
dBdt = [
    -(L(2)*M(3)+M(1)*L(1))*s1*X(7)-M(3)*L(3)*s12*(X(7)+X(8)), ...
    -M(3)*L(3)*s12*(X(7)+X(8));
    
    (L(2)*M(3)+M(1)*L(1))*c1*X(7)+M(3)*L(3)*c12*(X(7)+X(8)), ...
    M(3)*L(3)*c12*(X(7)+X(8))];
dCdt = [
    -2*L(2)*M(3)*L(3)*s2*X(8), -L(2)*M(3)*L(3)*s2*X(8);
    -L(2)*M(3)*L(3)*s2*X(8), 0];
dMMdt = [dAdt dBdt; dBdt' dCdt];

% mass matrix
MM = mm(X, S);

% rate of change of KE and PE
dKEdt = dXdt(1:4)'*MM*dXdt(5:8)+0.5*dXdt(1:4)'*dMMdt*dXdt(1:4);
dPEdt = g*((L(2)*M(3)+M(1)*L(1))*s1+M(3)*L(3)*s12)*dXdt(3) + ...
    g*M(3)*L(3)*s12*dXdt(4);

P = [dKEdt dPEdt];
end

function MM = mm(X, S)
%MM returns the mass matrix

% parameters
c1 = cos(X(3));
c2 = cos(X(4));
c12 = cos(X(3)+X(4));

s1 = sin(X(3));
s12 = sin(X(3)+X(4));

M = S.M;
L = S.L;

% entries of mass matrix
A = [M(1)+M(3), 0;
    0, M(1)+M(3)];

B = [(M(1)*L(1)+M(3)*L(2))*c1+M(3)*L(3)*c12, M(3)*L(3)*c12;
    (M(1)*L(1)+M(3)*L(2))*s1+M(3)*L(3)*s12, M(3)*L(3)*s12];

C = [M(2)+M(4)+M(1)*L(1)^2+M(3)*L(2)^2+M(3)*L(3)^2+2*M(3)*L(3)*L(2)*c2, ...
    M(3)*L(3)^2+M(3)*L(3)*L(2)*c2+M(4);
    M(3)*L(3)^2+M(3)*L(3)*L(2)*c2+M(4), M(4)+M(3)*L(3)^2];

MM = [A B; B' C];
end

function [X S] = flipXY(X, S)
%flips the base x/y points

% parameters
M = S.M;
L = S.L;

t1=X(3);
t12=X(3)+X(4);
w1=X(7);
w2=X(7)+X(8);

% flip coordinates & parameters
X=[X(1)+L(2)*sin(t1)+L(4)*sin(t12);
    X(2)-L(2)*cos(t1)-L(4)*cos(t12);
    pi+t12;
    -X(4);
    X(5)+L(2)*cos(t1)*w1+L(4)*cos(t12)*w2;
    X(6)+L(2)*sin(t1)*w1+L(4)*sin(t12)*w2;
    w2;
    -X(8)];

S.M=[M(3) M(4) M(1) M(2)];
S.L=[L(4)-L(3) L(4) L(2)-L(1) L(2)];

if isfield(S, 'color')
    % flip the color of the links for mplot
    S.color=fliplr(S.color);
end

%reduce angles to be more workable
if(X(3)>pi)
    X(3)=X(3)-2*pi;
end
if(X(3)<-pi)
    X(3)=X(3)+2*pi;
end
if(X(4)>pi)
    X(4)=X(4)-2*pi;
end
if(X(4)<-pi)
    X(4)=X(4)+2*pi;
end
end