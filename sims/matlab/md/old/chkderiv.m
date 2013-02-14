function chkderiv(der)
options = optimset('Algorithm','interior-point','FinDiffType','central',...
    'DerivativeCheck','on','GradObj','on','MaxFunEvals',0,'Display','off');

p.x0 = [pi pi 0 0];
p.u0 = [0 0 0 0];
p.solver = 'fmincon';
p.options = options;
p.lb = [-pi -pi -2 -2];
p.ub = [pi pi 2 2];

p.x0 = rand(size(p.x0)).*(p.ub-p.lb) + p.lb;
p.u0 = rand(size(p.u0)).*(p.ub-p.lb) + p.lb;
p.objective = @(x) cost(x, p.x0, p.u0, der);
fmincon(p);
end

function [v, g] = cost(z, x0, u0, der)
s = [3 4 7 8];
o = odeset('RelTol',1e-8,'AbsTol',1e-8);

switch der(2)
    case 'x'
        S = mbmdl(z, u0, 1.077398914708292, o);
        DX0 = eye(4,4);
        DT = [];
        DUf = [];
    case 'u'
        S = mbmdl(x0, z, z(1) + 1.077398914708292, o);
        DX0 = zeros(4,4);
        DT = @FDT;
        DUf = @DU;
end

m = mbmap(S, @U, DT, DX0, DUf);

switch der
    case 'xx'
        f = m.flow.y(s,end);
        df = reshape(m.dflow.y(:,end),4,4);
    case 'hx'
        f = m.H(s,end);
        df = reshape(m.dHdX0,4,4);
    case 'xu'
        f = m.flow.y(s,end);
        df = reshape(m.dctls.y(:,end),4,4);
    case 'hu'
        f = m.H(s,end);
        df = reshape(m.dHdu,4,4);
end

v = f'*f/2;
g = f'*df;
end

function V = U(t, X, S)
if numel(t) > 1
   S.ctls = repmat(S.ctls(:), numel(t), 1); 
end

% V is 4 x 1
V = zeros(numel(X)/2, 1);

T = S.ctls(1:4:end);
b0 = S.ctls(2:4:end);
b1 = S.ctls(3:4:end);
b2 = S.ctls(4:4:end);

V(4:4:end) = b0 + b1 .* sin(pi*t./T) + b2 .* sin(2*pi*t./T);
end

function dU = DU(t, X, S)
% dU is 2 x 4
dU = zeros(numel(X), 1);
T = S.ctls(1);
b1 = S.ctls(3);
b2 = S.ctls(4);

dU(2:8:end) = -((b1.*pi*t.*cos((pi*t)./T))./T.^2) ...
    - (2*b2.*pi*t.*cos((2*pi*t)./T))./T.^2;
dU(4:8:end) = 1;
dU(6:8:end) = sin((pi*t)./T);
dU(8:8:end) = sin((2*pi*t)./T);
end

function FdT = FDT(t, flow, F, ~)
DT = [1 0 0 0];
X = deval(flow, t);
F = F(t, X(:));

% FdT is 4 x 4
FdT = zeros(2*numel(F), 1);

F1 = F(3:8:end);
F2 = F(4:8:end);
F3 = F(7:8:end);
F4 = F(8:8:end);

DT1 = DT(1:4:end);
DT2 = DT(2:4:end);
DT3 = DT(3:4:end);
DT4 = DT(4:4:end);

FdT(1:16:end) = DT1.*F1;
FdT(2:16:end) = DT1.*F2;
FdT(3:16:end) = DT1.*F3;
FdT(4:16:end) = DT1.*F4;
FdT(5:16:end) = DT2.*F1;
FdT(6:16:end) = DT2.*F2;
FdT(7:16:end) = DT2.*F3;
FdT(8:16:end) = DT2.*F4;
FdT(9:16:end) = DT3.*F1;
FdT(10:16:end) = DT3.*F2;
FdT(11:16:end) = DT3.*F3;
FdT(12:16:end) = DT3.*F4;
FdT(13:16:end) = DT4.*F1;
FdT(14:16:end) = DT4.*F2;
FdT(15:16:end) = DT4.*F3;
FdT(16:16:end) = DT4.*F4;
end