function V = U(t, X, S)
% controls for each time step?
% if numel(t) > 1
%     S.ctls = repmat(S.ctls, numel(t), 1);
% end

% V is 4 x 1
V = zeros(numel(X)/2, 1);
V(1:4:end) = 0;
V(2:4:end) = 0;
V(3:4:end) = 0;
V(4:4:end) = S.ctls;

% V = [0;0;0;S.ctls];
end