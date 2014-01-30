function Y = mbimp(X, p)
% parameters
b = p(2);
d1 = p(3);
d2 = p(4);
k1 = p(6);
k2 = p(7);

% state
if sum(size(X) == 4)
    x3 = X(1:4:end);
    x4 = X(2:4:end);
    x7 = X(3:4:end);
    x8 = X(4:4:end);
else
    x1 = X(1:8:end);
    x2 = X(2:8:end);
    x3 = X(3:8:end);
    x4 = X(4:8:end);
    x7 = X(7:8:end);
    x8 = X(8:8:end);
end

s3 = sin(x3);
s34 = sin(x3 + x4);
c3 = cos(x3);
c4 = cos(x4);
cd4 = cos(2*x4);
c34 = cos(x3 + x4);

div = d1^2 - 2*k1*k2 + d1^2*cd4;

% impact map
Y = zeros(size(X));
if sum(size(X) == 4)
    Y(1:4:end) = pi + x3 + x4;
    Y(2:4:end) = -x4;
    Y(3:4:end) = (x7.*(d1^2 - d1*d2 + 2*b*d2*k1 - 2*k1*k2 ...
        - 2*d1*(d1 - b*k1)*c4 + d1*(d1 - d2)*cd4))./div + (x8.*(d1 - d2 ...
        + (2*d2*k1*(b*d1 - k2))./div))/d1;
    
    Y(4:4:end) = (x8.*(-d1^2 + d1*d2 - 2*b*d2*k1 + 2*k1*k2 ...
        + 2*d2*(-(b*d1) + k2).*c4 + d1*(-d1 + d2)*cd4))./div ...
        + (x7.*(-(b*(d1^2 + 2*d2*k1)) + d1*(d2 + 2*k2) ...
        + 2*(d1^2 - b*d1*(d2 + k1) + d2*k2)*c4 + d1*(-(b*d1) + d2)*cd4))./div;
else
    Y(1:8:end) = x1 + d1*s3 + d2*s34;
    Y(2:8:end) = x2 - d1*c3 - d2*c34;
    Y(3:8:end) = pi + x3 + x4;
    Y(4:8:end) = -x4;
    % Y(5:8:end) = Y(6:8:end) = 0
    Y(7:8:end) = (x7.*(d1^2 - d1*d2 + 2*b*d2*k1 - 2*k1*k2 ...
        - 2*d1*(d1 - b*k1)*c4 + d1*(d1 - d2)*cd4))./div + (x8.*(d1 - d2 ...
        + (2*d2*k1*(b*d1 - k2))./div))/d1;
    
    Y(8:8:end) = (x8.*(-d1^2 + d1*d2 - 2*b*d2*k1 + 2*k1*k2 ...
        + 2*d2*(-(b*d1) + k2).*c4 + d1*(-d1 + d2)*cd4))./div ...
        + (x7.*(-(b*(d1^2 + 2*d2*k1)) + d1*(d2 + 2*k2) ...
        + 2*(d1^2 - b*d1*(d2 + k1) + d2*k2)*c4 + d1*(-(b*d1) + d2)*cd4))./div;
end
end