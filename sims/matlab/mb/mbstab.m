function [e, slns2, H] = mbstab(H, slns, N, U, S)
s = [3 4 7 8];
n = length(s);

if isvector(H)
    % create random perturbations in the range of -H to H in the form of a
    % m*n x n matrix [H1; H2; ...] where Hi is an n x n diagonal matrix
    % s.t. Hi(i,i) is perturbed by the same random amount for each i
    
    H = H(:); % make sure H is a column vector
    H = -kron(H, eye(n)) + 2*kron(H, diag(rand(n,1)));
    %     H = diag(-h*ones(n,1) + 2*h*rand(n,1));
end

% add perturbations to initial condition
m = numel(H) / n^2;
ind = repmat(logical([0; 0; 1; 1]), 2*m*n, 1);
X0 = zeros(8*m*n, 1);
X0(ind) = repmat(S.X0(s), m*n, 1) + H(:);

% integrate perturbations
if ~isfield(S, 'options')
    S.options = odeset('RelTol',1e-13,'AbsTol',1e-13);
end
S.X0 = X0;
slns2 = mbode(N, U, S);

% calculate eigenvalues
J = slns2(N).y(ind, end) - repmat(slns(N).y(s, end), m*n, 1);
J = reshape(J, size(H));

e = zeros(4, m);
for i = 0:m-1
    k = (1:4) + i*n;
    e(:, i+1) = abs(eig(J(k, :) / H(k,:)));
end