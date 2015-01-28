function [C sln] = cntrplot(x, u, T, U, plotx, dx, ploty, dy)
% get nrow x ncol
m = numel(dy); % rows
n = numel(dx); % cols

% parse the inputs
if plotx(1) == 't'
    [Trep, xrep, urep] = Tsetup(T, dx, x, u, m);
    [xrep, urep] = XUsetup(ploty, dy, xrep, urep, x, u);
elseif ploty(1) == 't'
    [Trep, xrep, urep] = Tsetup(T, dy, x, u, n);
    [xrep, urep] = XUsetup(plotx, dx, xrep, urep, x, u);
else
    [Trep, xrep, urep] = Tsetup(T, 0, x, u, m*n);
    [dx, dy] = meshgrid(dx, dy);
    [xrep, urep] = XUsetup(plotx, dx, xrep, urep, x, u);
    [xrep, urep] = XUsetup(ploty, dy, xrep, urep, x, u);
end

% opt = odeset('RelTol',1e-8,'AbsTol',1e-7);
S = mbmdl(xrep, urep, max(Trep));
sln = mbode(1, U, S);

X = mbimp(deval(sln, Trep), S.p);
X = reshape(X, 8, numel(X)/8);
X = X([3 4 7 8], :);

% calc the cost
if plotx(1) == 't'
    C = reshape(X(:) - repmat(xrep, n, 1), size(X));
    C = mbqnt('dom', C, S.p);
    C = reshape(sum(C.^2), m, n);
elseif ploty(1) == 't'
    C = reshape(X(:) - repmat(xrep, m, 1), size(X));
    C = mbqnt('dom', C, S.p);
    C = reshape(sum(C.^2), n, m);
    C = C';
else
    C = reshape(X(:) - xrep, size(X));
    C = mbqnt('dom', C, S.p);
    C = reshape(sum(C.^2), m, n);
end
end

function [Trep, xrep, urep] = Tsetup(T, dt, x, u, N)
Trep = T + dt;
xrep = repmat(x, N, 1);
urep = repmat(u, N, 1);
end

function [xrep, urep] = XUsetup(p, d, xrep, urep, x, u)
% get number of elements per x/u
sx = numel(x);
su = numel(u);

% parse the input string to figure out where to add d
i = str2double(p(2:end));
if p(1) == 'x'
    xrep(i:sx:end) = x(i) + d;
elseif p(1) == 'u'
    urep(i:su:end) = u(i) + d;
end
end