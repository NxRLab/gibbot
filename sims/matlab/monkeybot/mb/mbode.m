function [slns, X] = mbode(N, U, S)

if isfield(S, 'options')
    odeoptions = S.options;
else
    odeoptions = odeset('RelTol',1e-6,'AbsTol',1e-6);
end

if isfield(S, 't0')    % For multiple runs time updates correctly
    t = S.t0;
else
    t = 0;
end

k = 1;
p = S.p;            % Get parameters
X = S.X0;           % Get initial conditions
slns(N) = ode45(@(t, x) 0*x, 0:1, X, odeoptions); % get fields in struct (Array initializations for number of impacts)

% if ode45 detects state for balancing controller then update F for
% balancing controller until ode45 recognizes balanced state

F = @(t, X) mbeom(t, X, @(t, X) U(t, X, S), p); 
% F = @(t, X) S.T*mbeom(t, X, @(t, X) U(t, X, S), p); % If you want to normalize time between 0 and 1

for n = 1:N
    % tspan = [t, t + 1 + 0*S.T(k)];
    tspan = [t, t + S.T(k)];       %Tell time you want it to run for (Time interval for integration)
    
    % integrate
    slns(n) = ode45(F, tspan, X, odeoptions);

    % impact
    X = mbimp(slns(n).y(:,end), p);
    
    % updates x-y coordinates (Don't need for swing up)
    t = slns(n).x(end);
    
    k = k + 1;                  %Used if you enter T as an array
    if k > numel(S.T)
        k = 1;
    end
end
end