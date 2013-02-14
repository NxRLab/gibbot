function chkderiv2(der, U, DT, DX0, DU)
options = optimset('Algorithm','interior-point','FinDiffType','central',...
    'DerivativeCheck','on','GradObj','on','MaxFunEvals',0,'Display','off');

p.x0 = [pi pi 0 0]';
p.u0 = [0 0 0 0]';
p.solver = 'fmincon';
p.options = options;
p.lb = [-1 -1 -1 -1]';
p.ub = [1 1 1 1]';

p.x0 = rand(size(p.x0)).*(p.ub-p.lb) + p.lb;
p.u0 = rand(size(p.u0)).*(p.ub-p.lb) + p.lb;
p.objective = @(x) cost(x, p.x0, p.u0, der, U, DT, DX0, DU);
fmincon(p);
end

function [v, g] = cost(z, x0, u0, der, U, DT, DX0, DU)
s = [3 4 7 8];
T = 1.077398914708292;
o = odeset('RelTol',1e-12,'AbsTol',1e-12);

switch der(2)
    case 'x'
        S = mbmdl(z, u0, T, o);
        DT = [];
        DU = [];
    case 'u'
        S = mbmdl(x0, z, 0*z(1) + T, o);
        DX0 = [];
end

m = mbmap(S, U, DT, DX0, DU);

switch der
    case 'xx'
        f = m.flow.y(s,end);
        df = reshape(m.dflow.y(:,end),4,4);
    case 'hx'
        f = m.H(s);
        df = reshape(m.dHdX0,4,4);
    case 'xu'
        f = m.flow.y(s,end);
        df = reshape(m.dctls.y(:,end),4,4);
    case 'hu'
        f = m.H(s);
        df = reshape(m.dHdu,4,4);
end

v = f'*f/2;
g = f'*df;
end