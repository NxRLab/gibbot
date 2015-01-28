function Map = mbmap(S, U, FDT, DX0, DU)
% variables
T = S.T;
X0 = S.X0;
U = @(t, X) U(t, X, S);
p = S.p;
odeoptions = S.options;

% map
tspan = [0, T];
F = @(t, X) mbeom(t, X, U, p);
flow = ode45(F, tspan, X0, odeoptions);

if isfield(flow, 'ie') && ~isempty(flow.ie)
    s = [3 4 7 8];
    X = mbimp(deval(flow, flow.xe), p);
    c = arrayfun(@(i) norm(X(s,i) - S.X0(s)), 1:numel(flow.xe));
    [~, i] = min(c)
    X = deval(flow, flow.xe(i));
else
    X = flow.y(:,end);
end

H = mbimp(X, p);

% map struct
Map.H = H;
Map.flow = flow;

if nargin == 2
    return;
end

% derivative of map w.r.t to initial condition, X0
if ~isempty(DX0)
    dUdX0 = @(t, X) zeros(numel(X0),1);
    dflow = DX(flow, DX0, U, dUdX0, p, odeoptions);
    dX = dflow.y(:,end);
    dHdX0 = DH(X, dX, p);
    
    % map struct
    Map.dflow = dflow;
    Map.dHdX0 = dHdX0;
end

% derivative of map w.r.t to controls, u
if ~isempty(DU)
    DU = @(t, X) DU(t, X, S);

    dX0 = zeros(2*numel(X0), 1);
    dctls = DX(flow, dX0, U, DU, p, odeoptions);
    X = deval(flow, dctls.x(end));

    % apply Leibniz rule?
    if isempty(FDT)
        FdT = 0;
    else
        % FdT = FDT(dctls.x(:), flow, F, S);
        disp('time derivative disabled')
        FdT = FDT(dctls.x(end), flow, F, S);
    end
    
    % dctls.y = reshape(FdT + dctls.y(:), size(dctls.y));
    % dctls.y = FdT + dctls.y(:,end);
    dX = dctls.y(:,end);
    dHdu = DH(X, dX, p);
    
    % map struct
    Map.dctls = dctls;
    Map.dHdu = dHdu;
end
end