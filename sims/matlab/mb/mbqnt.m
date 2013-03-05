function [varargout] = mbqnt(info, X, p)
switch lower(info)
    case 'xy'
        [varargout{1}, varargout{2}] = q2x(X, p);
    case 'dxdy'
        [varargout{1}, varargout{2}] = dq2v(X, p);
    case 'energy'
        [varargout{1}, varargout{2}] = energy(X, p);
    case 'mass'
        varargout{1} = mm(X, p);
    case 'forces'
        [varargout{1}, varargout{2}] = forces(X, p);
    case 'dom'
        varargout{1} = fixstates(X);
    case '(-pi, pi]'
        varargout{1} = fixangles(X);
    case 'pre2post'
        varargout{1} = postimp(X, p);
    case 'post2pre'
        varargout{1} = preimp(X, p);
    case 'mm2'
        varargout{1} = mm2(X, p);
    case 'qpost'
        [varargout{1}, varargout{2}, varargout{3}] =  Qpost(X, p);
        
        % [varargout{1}, varargout{2}, varargout{3}] =  Qpost(X, p);
    case 'qpre'
        [varargout{1}, varargout{2}, varargout{3}] =  Qpre(X, p);
end
end

function [X Y] = q2x(X, p)
%Q2X converts configuration space coordinates to cartesian coordinates.
d1 = p(3);
d2 = p(4);
r1 = p(8);
r2 = p(9);

if sum(size(X) == 4)
    % matrix must be 4 x N
    c1=cos(X(1:4:end))';
    c12=cos(X(1:4:end)+X(2:4:end))';
    
    s1=sin(X(1:4:end))';
    s12=sin(X(1:4:end)+X(2:4:end))';
    
    x=zeros(size(c1));
    y=x;
else
    x=X(1:8:end);
    y=X(2:8:end);
    
    c1=cos(X(3:8:end));
    c12=cos(X(3:8:end)+X(4:8:end));
    
    s1=sin(X(3:8:end));
    s12=sin(X(3:8:end)+X(4:8:end));
end

% location of 1st CoM
x1=r1*s1+x;
y1=-r1*c1+y;

% location of bottom of 1st link
x2=d1*s1+x;
y2=-d1*c1+y;

% location of 2nd CoM
x3=x2+r2*s12;
y3=y2-r2*c12;

% location of bottom of 2nd link
x4=x2+d2*s12;
y4=y2-d2*c12;

X = [x x1 x2 x3 x4];
Y = [y y1 y2 y3 y4];
end

function [dX dY] = dq2v(X, p)
d1 = p(3);
d2 = p(4);
r1 = p(8);
r2 = p(9);

if sum(size(X) == 4)
    % matrix must be 4 x N
    c1=cos(X(1:4:end))';
    c12=cos(X(1:4:end)+X(2:4:end))';
    
    s1=sin(X(1:4:end))';
    s12=sin(X(1:4:end)+X(2:4:end))';
    
    w1 = X(3:4:end)';
    w12 = (X(3:4:end)+X(4:4:end))';
    
    dx=zeros(size(c1));
    dy=dx;
else
    dx=X(5:8:end);
    dy=X(6:8:end);
    
    c1=cos(X(3:8:end));
    c12=cos(X(3:8:end)+X(4:8:end));
    
    s1=sin(X(3:8:end));
    s12=sin(X(3:8:end)+X(4:8:end));
    
    w1 = X(7:8:end);
    w12 = X(7:8:end)+X(8:8:end);
end
% location of 1st CoM
dx1=r1*w1.*c1+dx;
dy1=r1*w1.*s1+dy;

% location of bottom of 1st link
dx2=d1*w1.*c1+dx;
dy2=d1*w1.*s1+dy;

% location of 2nd CoM
dx3=dx2+r2*w12.*c12;
dy3=dy2+r2*w12.*s12;

% location of bottom of 2nd link
dx4=dx2+d2*w12.*c12;
dy4=dy2+d2*w12.*s12;

dX = [dx dx1 dx2 dx3 dx4];
dY = [dy dy1 dy2 dy3 dy4];
end

function [KE, PE] = energy(X, p)

if sum(size(X) == 4)
    % matrix must be 4 x N
    x2 = 0;
    x3 = X(1:4:end);
    x4 = X(2:4:end);
    x5 = 0;
    x6 = 0;
    x7 = X(3:4:end);
    x8 = X(4:4:end);
else
    x2 = X(2:8:end);
    x3 = X(3:8:end);
    x4 = X(4:8:end);
    x5 = X(5:8:end);
    x6 = X(6:8:end);
    x7 = X(7:8:end);
    x8 = X(8:8:end);
end

c3 = cos(x3);
c4 = cos(x4);
c34 = cos(x3+x4);
s3 = sin(x3);
s34 = sin(x3+x4);

a = p(1);
b = p(2);
d1 = p(3);
g = p(5);
k1 = p(6);
k2 = p(7);

KE = (a*(x5.^2 + x6.^2) + 2*c34.*x5.*x7 + 2*s34.*x6.*x7 ...
    + 2*b*(c3.*x5 + s3.*x6).*x7 + 2*c4*d1.*x7.^2 + k1*x7.^2 ...
    + k2*x7.^2 + 2*c34.*x5.*x8 + 2*s34.*x6.*x8 + 2*c4*d1.*x7.*x8 ...
    + 2*k1.*x7.*x8 + k1*x8.^2)/2;

PE = g*(a*x2 - b*c3 - c34);
end

% function P=power(X, S)
% % d(KE)/dt = d/dt (dq/dt*MM*dq/dt) = dq/dt*MM*d^2(q)/dt^2 +
% % 1/2*dq/dt*d(MM)/dt*dq/dt
%
% % parameters
% c1 = cos(X(3));
% c12 = cos(X(3)+X(4));
%
% s1 = sin(X(3));
% s2 = sin(X(4));
% s12 = sin(X(3)+X(4));
%
% M = S.M;
% L = S.L;
% g = S.g;
%
% % velocity and acceleration
% F = mbot_eom('dof4', S);
% dXdt = F(t, X);
%
% % components for dMM/dt
% dAdt = [0 0;0 0];
% dBdt = [
%     -(L(2)*M(3)+M(1)*L(1))*s1*X(7)-M(3)*L(3)*s12*(X(7)+X(8)), ...
%     -M(3)*L(3)*s12*(X(7)+X(8));
%
%     (L(2)*M(3)+M(1)*L(1))*c1*X(7)+M(3)*L(3)*c12*(X(7)+X(8)), ...
%     M(3)*L(3)*c12*(X(7)+X(8))];
% dCdt = [
%     -2*L(2)*M(3)*L(3)*s2*X(8), -L(2)*M(3)*L(3)*s2*X(8);
%     -L(2)*M(3)*L(3)*s2*X(8), 0];
% dMMdt = [dAdt dBdt; dBdt' dCdt];
%
% % mass matrix
% MM = mm(X, S);
%
% % rate of change of KE and PE
% dKEdt = dXdt(1:4)'*MM*dXdt(5:8)+0.5*dXdt(1:4)'*dMMdt*dXdt(1:4);
% dPEdt = g*((L(2)*M(3)+M(1)*L(1))*s1+M(3)*L(3)*s12)*dXdt(3) + ...
%     g*M(3)*L(3)*s12*dXdt(4);
%
% P = [dKEdt dPEdt];
% end

function MM = mm(X, p)
%MM returns the mass matrix

% parameters
c1 = cos(X(3));
c2 = cos(X(4));
c12 = cos(X(3)+X(4));

s1 = sin(X(3));
s12 = sin(X(3)+X(4));

a = p(1);
b = p(2);
d1 = p(3);
k1 = p(6);
k2 = p(7);

% entries of mass matrix
A = [a, 0; 0, a];

B = [b*c1+c12, c12; b*s1+s12, s12];

C = [k1 + k2 + 2*d1*c2, k1 + d1*c2; k1 + d1*c2, k1];

MM = [A B; B' C];
end

function [G, C] = forces(X, p)
b = p(2);
d1 = p(3);
g = p(5);

N = numel(X)/8;

x3 = reshape(X(3:8:end), N, 1);
x4 = reshape(X(4:8:end), N, 1);
x7 = reshape(X(7:8:end), N, 1);
x8 = reshape(X(8:8:end), N, 1);

C = [-(d1*sin(x4).*x7.*x8) - d1*sin(x4).*x8.*(x7 + x8), d1*sin(x4).*x7.^2];

G = [g*(b*sin(x3) + sin(x3 + x4)) , g*sin(x3 + x4)];
end

function X = fixstates(X)
if sum(size(X) == 4)
    % matrix must be 4 x N
    X(1:4:end) = fixangles(X(1:4:end));
    X(2:4:end) = fixangles(X(2:4:end));
else
    X(3:8:end) = fixangles(X(3:8:end));
    X(4:8:end) = fixangles(X(4:8:end));
end
end

function y = fixangles(x)
% make sure angles are btw (-pi pi]
ind = x > 2*pi;
x(ind) = mod(x(ind), 2*pi);
ind = x > pi;
x(ind) = x(ind) - 2*pi;

ind = x < -2*pi;
x(ind) = mod(x(ind), -2*pi);
ind = x <= -pi;
x(ind) = x(ind) + 2*pi;

y = x;
end

function P = postimp(x4, p)
b = p(2);
d1 = p(3);
d2 = p(4);
k1 = p(6);
k2 = p(7);

c4 = cos(x4);
cd4 = cos(2*x4);
div = d1^2 - 2*k1*k2 + d1^2*cd4;

P = zeros(numel(x4)*4, 1);
P(1:4:end) = (d1^2 - d1*d2 + 2*b*d2*k1 - 2*k1*k2 - 2*d1*(d1 - b*k1)*c4 ...
    + d1*(d1 - d2)*cd4) ./ div;
P(2:4:end) = (-(b*(d1^2 + 2*d2*k1)) + d1*(d2 + 2*k2) ...
    + 2*(d1^2 - b*d1*(d2 + k1) + d2*k2)*c4 + d1*(-(b*d1) + d2)*cd4) ./ div;
P(3:4:end) = (d1^2 - d1*d2 + 2*b*d2*k1 - 2*k1*k2 + d1*(d1 - d2)*cd4)./div;
P(4:4:end) = (-d1^2 + d1*d2 - 2*b*d2*k1 + 2*k1*k2 ...
    + 2*d2*(-(b*d1) + k2)*c4 + d1*(-d1 + d2)*cd4) ./ div;
end

function P = preimp(x4, p)
b = p(2);
d1 = p(3);
d2 = p(4);
k1 = p(6);
k2 = p(7);

c4 = cos(x4);
cd4 = cos(2*x4);
div = (-1 + b)*d1^2 + (-1 + b)*cd4*d1*(d1 - d2) + d1*(d2 + b*d2 - 2*k2) ...
    + 2*k1*(-(b*d2) + k2);

P = zeros(numel(x4)*4, 1);
P(1:4:end) = -((d1^2 + cd4*d1*(d1 - d2) - d1*d2 + 2*b*d2*k1 ...
    + 2*c4*d2*(b*d1 - k2) - 2*k1*k2)./div);
P(2:4:end) = (b*d1^2 + cd4*d1*(b*d1 - d2) - d1*d2 + 2*b*d2*k1 - 2*d1*k2 ...
    - 2*c4*(d1^2 - b*d1*(d2 + k1) + d2*k2))./div;
P(3:4:end) = -((d1^2 + cd4*d1*(d1 - d2) - d1*d2 + 2*b*d2*k1 ...
    - 2*k1*k2)./div);
P(4:4:end) = (d1^2 + cd4*d1*(d1 - d2) - d1*d2 + 2*b*d2*k1 - 2*c4*d1*(d1 ...
    - b*k1) - 2*k1*k2)./div;
end

function MM = mm2(x4, p)
% parameters
c2 = cos(x4);

d1 = p(3);
k1 = p(6);
k2 = p(7);

MM = zeros(4*numel(x4),1);
MM(1:4:end) = k1 + k2 + 2*d1*c2;
MM(2:4:end) = k1 + d1*c2;
MM(3:4:end) = k1 + d1*c2;
MM(4:4:end) = k1;
end

function [Q, P, M] = Qpost(x4, p)
P = preimp(x4, p);
M = mm2(x4, p);

m1 = M(1:4:end);
m2 = M(2:4:end);
m3 = M(3:4:end);
m4 = M(4:4:end);

p1 = P(1:4:end);
p2 = P(2:4:end);
p3 = P(3:4:end);
p4 = P(4:4:end);

Q = Inf(size(P));
% Q is post-impact state, Q = (M-P'\M/P)
Q(1:4:end) = m1 - p1.*(m1.*p1 + m2.*p2) - p2.*(m3.*p1 + m4.*p2);
Q(2:4:end) = m2 - p1.*(m1.*p3 + m2.*p4) - p2.*(m3.*p3 + m4.*p4);
Q(3:4:end) = m3 - (m1.*p1 + m2.*p2).*p3 - (m3.*p1 + m4.*p2).*p4;
Q(4:4:end) = m4 - p3.*(m1.*p3 + m2.*p4) - p4.*(m3.*p3 + m4.*p4);
end

function [Q, P, M] = Qpre(x4, p)
P = postimp(x4, p);
M = mm2(x4, p);

m1 = M(1:4:end);
m2 = M(2:4:end);
m3 = M(3:4:end);
m4 = M(4:4:end);

p1 = P(1:4:end);
p2 = P(2:4:end);
p3 = P(3:4:end);
p4 = P(4:4:end);

Q = Inf(size(P));
% Q is pre-impact state, Q = (P'MP - M)
Q(1:4:end) = -m1 + p1.*(m1.*p1 + m2.*p2) + p2.*(m3.*p1 + m4.*p2);
Q(2:4:end) = -m2 + p1.*(m1.*p3 + m2.*p4) + p2.*(m3.*p3 + m4.*p4);
Q(3:4:end) = -m3 + (m1.*p1 + m2.*p2).*p3 + (m3.*p1 + m4.*p2).*p4;
Q(4:4:end) = -m4 + p3.*(m1.*p3 + m2.*p4) + p4.*(m3.*p3 + m4.*p4);
end