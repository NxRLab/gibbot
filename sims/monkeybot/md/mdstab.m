function [e dg] = mdstab(nimp, S, U)
h = 1e-5;
n = 4;
dx = mddelta(zeros(n,1), h, n);
[~, ndx] = size(dx);

S.X0 = repmat(S.X0, 1, ndx);
S.X0([3 4 7 8], :) = S.X0([3 4 7 8], :) + dx;
S.options = odeset('RelTol',1e-8,'AbsTol',1e-7);

[~, X] = mbode(nimp, U, S);
X = reshape(X, 8, ndx);
X = mbqnt('dom', X, S.p);
X = X([3 4 7 8], :);

c = X - S.X0([3 4 7 8], :);
[~, dg] = mddif(c, h, n);

dg = dg + eye(n);

e = eig(dg);