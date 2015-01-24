function dU = DU(t, X, S)
% control for each time step?
if numel(t) > 1
   S.ctls = repmat(S.ctls, numel(t), 1);
end

% dU is 2 x 4
dU = zeros(numel(X), 1);

% dU(1:8:end) = 0;
dU(2:8:end) = 0;
% dU(3:8:end) = 0;
dU(4:8:end) = 1;
% dU(5:8:end) = 0;
dU(6:8:end) = 0;
% dU(7:8:end) = 0;
dU(8:8:end) = 1;
end