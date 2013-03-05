function [slns, X] = mbode(N, U, S)

if isfield(S, 'options')
    odeoptions = S.options;
else
    odeoptions = odeset('RelTol',1e-6,'AbsTol',1e-6);
end

if isfield(S, 't0')
    t = S.t0;
else
    t = 0;
end

k = 1;
p = S.p;
X = S.X0;
slns(N) = ode45(@(t, x) 0*x, 0:1, X, odeoptions); % get fields in struct
F = @(t, X) mbeom(t, X, @(t, X) U(t, X, S), p);
% F = @(t, X) S.T*mbeom(t, X, @(t, X) U(t, X, S), p);

for n = 1:N
    % tspan = [t, t + 1 + 0*S.T(k)];
    tspan = [t, t + S.T(k)];
    
    % integrate
    slns(n) = ode45(F, tspan, X, odeoptions);

    % impact
    X = mbimp(slns(n).y(:,end), p);
    
    % update
    t = slns(n).x(end);
    
    k = k + 1;
    if k > numel(S.T)
        k = 1;
    end
end
end