function f = mbeom(t, X, U, p)
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

% equations of motion
s3 = sin(x3);
s4 = sin(x4);
s34 = sin(x3 + x4);
c4 = cos(x4);

dx7 = (b*g*k1*s3 - c4*d1.*(g*(s34 - u4) + d1*s4.*x7.^2) - ...
    k1*(g*(u3 - u4) + d1*s4.*(x7 + x8).^2)) ./ (c4.^2*d1^2 - k1*k2);
dx8 = -(((2*c4*d1 + k1 + k2).*(g*(s34 - u4) + d1*s4.*x7.^2) + ...
    (c4*d1 + k1).*(-(b*g*s3) + g*(-s34 + u3) + ...
    d1*s4.*x8.*(2*x7 + x8))) ./ (-(c4.^2*d1^2) + k1*k2));

% f is 8 x 1
f = zeros(size(X));
f(3:8:end) = x7;
f(4:8:end) = x8;
f(7:8:end) = dx7;
f(8:8:end) = dx8;