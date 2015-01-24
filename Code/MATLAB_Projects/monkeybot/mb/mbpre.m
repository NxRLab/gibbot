function xpre = mbpre(xpost, p)
% parameters
b = p(2);
d1 = p(3);
d2 = p(4);
k1 = p(6);
k2 = p(7);

% post-impact state
y3 = xpost(1:4:end);
y4 = xpost(2:4:end);
y7 = xpost(3:4:end);
y8 = xpost(4:4:end);

% pre-impact state
x3 = -pi + y3 + y4;
x4 = -y4;
x7 = -((2*d2*(b*d1 - k2)*y7.*cos(y4) + (y7 + y8).*(d1^2 - d1*d2 ...
    + 2*b*d2*k1 - 2*k1*k2 + d1*(d1 - d2).*cos(2*y4)))./((-1 + b)*d1^2 ...
    + d1*(d2 + b*d2 - 2*k2) + 2*k1*(-(b*d2) + k2) ...
    + (-1 + b)*d1*(d1 - d2)*cos(2*y4)));
x8 = (b*d1^2*y7 - d1*d2*y7 + 2*b*d2*k1*y7 - 2*d1*k2*y7 + d1^2*y8 ...
    - d1*d2*y8 + 2*b*d2*k1*y8 - 2*k1*k2*y8 - 2*(d2*k2*y7 ...
    + d1^2*(y7 + y8) - b*d1*(d2*y7 + k1*(y7 + y8))).*cos(y4) ...
    + d1*(b*d1*y7 + d1*y8 - d2*(y7 + y8)).*cos(2*y4))./((-1 + b)*d1^2 ...
    + d1*(d2 + b*d2 - 2*k2) + 2*k1*(-(b*d2) + k2) ...
    + (-1 + b)*d1*(d1 - d2)*cos(2*y4));

xpre = zeros(size(xpost));
xpre(1:4:end) = mbqnt('(-pi, pi]', x3, p);
xpre(2:4:end) = mbqnt('(-pi, pi]', x4, p);
xpre(3:4:end) = x7;
xpre(4:4:end) = x8;