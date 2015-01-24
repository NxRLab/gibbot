function X = mddelta(x, h, n)
% generate x + h and x - h
hx = h*eye(n);
hx = [hx(:); -hx(:)];
y = repmat(x, 2*n, 1) + hx;
y = reshape(y, n, numel(y)/n);

if n > 1
    xterms = zeros(1, n);
    xterms(1) = 1;
    xterms(end) = 1;
    
    % +/+ cross terms
    A = unique(perms(xterms), 'rows')';
    % fix A, so it's ordered: (x3,x4), (x3, x7), (x3, x8), (x4, x7), (x4, x8),
    % (x7, x8)
    A = A(:, end:-1:1);
    
    % +/- cross terms
    ind = find(A);
    ind = ind(2:2:end);
    B = A;
    B(ind) = -A(ind);
    
    hx = h*[A -A B -B];
    hx = hx(:);
    z = repmat(x, numel(hx)/n, 1) + hx;
    z = reshape(z, n, numel(z)/n);
    
    X = [x y z];
else
    X = [x y];
end
end