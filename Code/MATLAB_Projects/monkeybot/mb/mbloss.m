function [dke dpe] = mbloss(state, X, S)
if any(size(X) == 4)
    % matrix must be 4 x N
    x3 = X(1:4:end);
    x4 = X(2:4:end);
    x7 = X(3:4:end);
    x8 = X(4:4:end);
else    
    x3 = X(3:8:end);
    x4 = X(4:8:end);
    x7 = X(7:8:end);
    x8 = X(8:8:end);
end

x3 = reshape(x3, numel(x3), 1);
x4 = reshape(x4, numel(x4), 1);
x7 = reshape(x7, numel(x7), 1);
x8 = reshape(x8, numel(x8), 1);

% we are solving for dE = Epost - Epre = 0, where post and pre are the
% post- and pre-impact energy levels.  We can write the equation entirely
% in terms of the post or pre-impact variables and solve for the post- or
% pre-impact angular velocity of the first link.

if strcmp(state, 'pre')
    impact = 'pre2post';
else
    impact = 'post2pre';
end

% parameters
b = S.p(2);
g = S.p(5);

% here we take advantage of the fact that pre/post angles of x4 are related
% by a negative sign and that P(x4) and M(x4) are only made up of cosines.
% This type of symmetry does not hold for other functions and variables

P = mbqnt(impact, x4, S.p);
M = mbqnt('mm2', x4, S.p);

m1 = M(1:4:end);
m2 = M(2:4:end);
m3 = M(3:4:end);
m4 = M(4:4:end);

p1 = P(1:4:end);
p2 = P(2:4:end);
p3 = P(3:4:end);
p4 = P(4:4:end);

Q = Inf(size(P));
% Q started with pre-impact state, Q = (PMP-M)
Q(1:4:end) = -m1 + p1.*(m1.*p1 + m2.*p2) + p2.*(m3.*p1 + m4.*p2);
Q(2:4:end) = -m2 + p1.*(m1.*p3 + m2.*p4) + p2.*(m3.*p3 + m4.*p4);
Q(3:4:end) = -m3 + (m1.*p1 + m2.*p2).*p3 + (m3.*p1 + m4.*p2).*p4;
Q(4:4:end) = -m4 + p3.*(m1.*p3 + m2.*p4) + p4.*(m3.*p3 + m4.*p4);

dpe = g*(b + 1)*(cos(x3) + cos(x3 + x4));
if strcmp(state, 'post')
    % flip the sign to get Q = M - P\M/P
    Q = -Q;
    dpe = -dpe;
end

% note that Q is symmetric, so we could just solve a simpler form of dke
dke = (x7.*(Q(1:4:end).*x7 + Q(3:4:end).*x8) ...
    + x8.*(Q(2:4:end).*x7 + Q(4:4:end).*x8))/2;