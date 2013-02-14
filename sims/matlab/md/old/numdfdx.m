function [dHx dXx dHu dXu] = numdfdx(x, u, hx, hu, idx, Sfun)
% size of grid
n = 3;
N = 1:n;

% variables
x = x(:, ones(n,1)) + kron([-1 0 1], hx(ones(size(x))));
u = u(:, ones(n,1)) + kron([-1 0 1], hu(ones(size(u))));
T = 2.508001197970272;

% functions
Hx = zeros(n,n,n,n);
Xx = zeros(n,n,n,n);

Hu = zeros(n,n,n,n);
Xu = zeros(n,n,n,n);

% compute derivative
for i = N
    for j = N
        for k = N
            for l = N
                % perturb solution around x0
                X = [x(1,i), x(2,j), x(3,k), x(4,l)];
                S = Sfun(X, u, T);
                [fh fx] = f(S);
                Hx(i,j,k,l) = fh(idx);
                Xx(i,j,k,l) = fx(idx);
                
                % perturb solution around u
                U = [u(1,i), u(2,j), u(3,k), u(4,l)];
                S = Sfun(x, U, T);
                [fh fx] = f(S);
                Hu(i,j,k,l) = fh(idx);
                Xu(i,j,k,l) = fx(idx);
            end
        end
    end
end

dHx = grad(Hx, hx);
dXx = grad(Xx, hx);

dHu = grad(Hu, hu);
dXu = grad(Xu, hu);
end

function [fh fx] = f(S)
s = [3 4 7 8];
o = odeset('RelTol',1e-6,'AbsTol',1e-6);
[sln fh] = mbode(1, S, o);

fh = fh(s);
fx = sln.y(s,end);
end

function dF = grad(F, h)
[dx2, dx1, dx3, dx4] = gradient(F, h);
dF = [dx1(2) dx2(2) dx3(2) dx4(2)];
end