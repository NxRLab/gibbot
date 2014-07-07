function [f df d2f] = mddif(H, h, n)
% Each entry in H (m x N) is arranged, for example, for m = n = 4 as:
%     x1 x2 x3 x4
% f1  h1 h5 h9 .
% f2  h2 h6 .  .
% f3  h3 h7 .  .
% f4  h4 h8 .  h16
% with the following column layout:
% col: 1 = ind0
% f(x1, x2, x3, x4), etc.
% cols: 2:5 = indp
% f(x1 + h, x2, x3, x4), etc.
% cols: 6:9 = indm
% f(x1 - h, x2, x3, x4), etc.
% cols: 10:15 = indpp
% f(x1 + h, x2 + h, x3, x4)
% cols: 16:21 = indmm
% f(x1 - h, x2 - h, x3, x4)
% cols: 22:27 = indpm
% f(x1 + h, x2 - h, x3, x4), etc.
% cols: 28:33 = indmp
% f(x1 - h, x2 + h, x3, x4), etc.
% for the cross terms, the 1st column is (x1, x2), (x1, x3), (x1, x4), (x2,
% x3), (x2, x4), (x3,x4).
%
% If H is m x N x p then for each index p the m x N pattern above is
% expected for the first n-1 states.  The values associated with dimension
% p form the n-th state, so p should be at least 3, thus representing 0/+/-
% h of the n-th state.  The expected use for p is to represent time.

% get indices for single terms
ind0 = 1;
indp = 2:(n+1);
indm = (n+2):(2*n+1);

% calc derivatives
f = H(:,ind0);
df = (H(:,indp) - H(:,indm))/(2*h);
fxx = (H(:,indp) - repmat(2*H(:,ind0),1,n) + H(:,indm))/(h*h);
if n > 1
    % get the indices for the x-terms, note that the four x-terms can be
    % created from the same base matrix
    [m, N] = size(H);
    N = (N - indm(end)) / 4;
    indpp = (indm(end) + 1):(indm(end) + N);
    indmm = (indpp(end) + 1):(indpp(end) + N);
    indpm = (indmm(end) + 1):(indmm(end) + N);
    indmp = (indpm(end) + 1):(indpm(end) + N);
    
    % calc derivative
    fxy = (H(:,indpp) - H(:,indpm) - H(:,indmp) + H(:,indmm))/(4*h*h);
    d2f = zeros(n,n,m);
    
    % organize Hessian, so that d2fi is its own nxn matrix
    for i = 1:m
        k = 1; % offset into (j - 1) column of n x n Hessian of d2fi
        for j = 2:n % index into column (j - 1) to add appropriate x-terms
            kend = n - j + 1; % number of x-terms in column
            d2f(j:n,j-1,i) = fxy(i,k:(k+kend-1));
            k = k + kend; % advance to next row offset for column j
        end
        d2f(:,:,i) =  diag(fxx(i,:)) + d2f(:,:,i)' + d2f(:,:,i);
    end
else
    d2f = fxx;
end
end