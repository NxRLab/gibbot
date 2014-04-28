function [DxF, DuF] = DF(t, X, U, p)
DxF = dFdX(t, X, U, p);
DuF = dFdU(X, p);
end

function dF = dFdU(X, p)
% parameters
d1 = p(3);
g = p(5);
k1 = p(6);
k2 = p(7);

% state
x4 = X(4:8:end);
c4 = cos(x4);

% dF is 4 x 2
dF = zeros(numel(X),1);

div = -(c4.^2*d1^2) + k1*k2;
r = c4*d1 + k1;
s = 2*c4*d1 + k1 + k2;

% dF(1:8:end) = 0;
% dF(2:8:end) = 0;
dF(3:8:end) = (g*k1)/div;
dF(4:8:end) = -((g*r)./div);
% dF(5:8:end) = 0;
% dF(6:8:end) = 0;
dF(7:8:end) = -((g*r)./div);
dF(8:8:end) = (g*s)./div;
end

function dF = dFdX(t, X, U, p)
% parameters
b = p(2);
d1 = p(3);
g = p(5);
k1 = p(6);
k2 = p(7);

% state
x3 = X(3:8:end);
x4 = X(4:8:end);
x7 = X(7:8:end);
x8 = X(8:8:end);

% control
u = U(t, X);
u3 = u(3:4:end);
u4 = u(4:4:end);

s3 = sin(x3);
s4 = sin(x4);
s34 = sin(x3 + x4);
c3 = cos(x3);
c4 = cos(x4);
cd4 = cos(2*x4);
c34 = cos(x3 + x4);

% dF is 4 x 4
dF = zeros(2*numel(X), 1);

div1 = -(c4.^2*d1^2) + k1*k2;
div2 = -div1;

% dF(1:16:end) = 0;
% dF(2:16:end) = 0;
dF(3:16:end) = (c34.*c4*d1*g - b*c3*g*k1)./div1;
dF(4:16:end) = (g*(b*c3.*(c4*d1 + k1) - c34.*(c4*d1 + k2)))./div1;
% dF(5:16:end) = 0;
% dF(6:16:end) = 0;

dF(7:16:end) = (-2*c4.*d1^2.*s4.*(-(b*g*k1*s3) + c4*d1*g.*s34 + g*k1*u3 ...
    - g*(c4*d1 + k1).*u4 + c4*d1^2.*s4.*x7.^2 + d1*k1*s4.*x7.^2 ...
    + 2*d1*k1*s4.*x7.*x8 + d1*k1*s4.*x8.^2) - (d1*(d1^2 + cd4*d1^2 ...
    - 2*k1*k2).*(g*s4.*u4 + (cd4*d1 + c4*k1).*x7.^2 + 2*c4*k1.*x7.*x8 ...
    + c4*k1.*x8.^2 + g*cos(x3 + 2*x4)))/2)./div1.^2;

dF(8:16:end) = (2*c4*d1^2.*s4.*((2*c4*d1 + k1 + k2).*(g*s34 ...
    - g*u4 + d1*s4.*x7.^2) + (c4*d1 + k1).*(-(b*g*s3) - g*s34 + g*u3...
    + 2*d1*s4.*x7.*x8 + d1*s4.*x8.^2)) ...
    - div1.*((2*c4*d1 + k1 + k2).*(c34*g + c4*d1.*x7.^2) ...
    - 2*d1*s4.*(g*s34 - g*u4 + d1*s4.*x7.^2) + (c4*d1 + k1).*(-(c34*g)...
    + 2*c4*d1.*x7.*x8 + c4*d1.*x8.^2) - d1*s4.*(-(b*g*s3) - g*s34 ...
    + g*u3 + 2*d1*s4.*x7.*x8 + d1*s4.*x8.^2)))./div1.^2;

dF(9:16:end) = 1;
% dF(10:16:end) = 0;
dF(11:16:end) = (2*d1*s4.*((c4*d1 + k1).*x7 + k1*x8))./div1;
dF(12:16:end) = (2*d1*s4.*((2*c4*d1 + k1 + k2).*x7 + (c4*d1 + k1).*x8))./div2;
% dF(13:16:end) = 0;
dF(14:16:end) = 1;
dF(15:16:end) = (2*d1*k1*s4.*(x7 + x8))./div1;
dF(16:16:end) = (2*d1*(c4*d1 + k1).*s4.*(x7 + x8))./div2;
end