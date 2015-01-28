function DF = mbot_jac(dof, S)
switch dof
    case 'dof2'
        DF = @(X) jac2(X, S);
    case 'dof4'
        DF = @(X) jac4(X, S);
end
end

function dFdX = jac4(X, S)
dFdX = zeros(8);

% parameters
c1 = cos(X(3));
c2 = cos(X(4));
c12 = cos(X(3)+X(4));

s1 = sin(X(3));
s2 = sin(X(4));
s12 = sin(X(3)+X(4));

M = S.M;
L = S.L;
g = S.g;

% coriolis/centrifugal forces
c = [
    0, 0, -((M(1)*L(1)+M(3)*L(2))*s1*X(7)+M(3)*L(3)*s12*(X(7)+X(8))), ...
    -M(3)*L(3)*s12*(X(7)+X(8));
    0, 0, (M(1)*L(1)+M(3)*L(2))*c1*X(7)+M(3)*L(3)*c12*(X(7)+X(8)), ...
    M(3)*L(3)*c12*(X(7)+X(8));
    0, 0, -M(3)*L(3)*L(2)*s2*X(8), -M(3)*L(3)*L(2)*s2*(X(7)+X(8));
    0, 0, M(3)*L(3)*L(2)*s2*X(7), 0
    ]*X(5:8);

% gravity
G = g*[0; M(1)+M(3);(M(1)*L(1)+M(3)*L(2))*s1+M(3)*L(3)*s12; M(3)*L(3)*s12];

% mass matrix
MM = mbot_utils('mass', t, X, S);

% x[t]: zero(4,1)

% y[t]: zero(4,1)

% \[Theta]1[t]:
dMdx3 = [0, 0, -((L(2)*M(3)+M(1)*L(1))*s1)-M(3)*L(3)*s12, -(M(3)*L(3)*s12);
    0, 0, (L(2)*M(3)+M(1)*L(1))*c1+M(3)*L(3)*c12, M(3)*L(3)*c12;
    -((L(2)*M(3)+M(1)*L(1))*s1)-M(3)*L(3)*s12, ...
    (L(2)*M(3)+M(1)*L(1))*c1+M(3)*L(3)*c12, 0, 0;
    -(M(3)*L(3)*s12), M(3)*L(3)*c12, 0, 0];

dcdx3 = [-(M(3)*L(3)*c12*X(8)*(X(7)+X(8))) + ...
    X(7)*(-((L(2)*M(3)+M(1)*L(1))*c1*X(7))-M(3)*L(3)*c12*(X(7)+X(8)));
    -(M(3)*L(3)*s12*X(8)*(X(7)+X(8))) + ...
    X(7)*(-((L(2)*M(3)+M(1)*L(1))*s1*X(7))-M(3)*L(3)*s12*(X(7)+X(8)));
    0;
    0];
dGdx3 = g*[0; 0; ((L(2)*M(3)+M(1)*L(1))*c1+M(3)*L(3)*c12); M(3)*L(3)*c12];
dFdx3 = GradF(MM, c, G, dMdx3, dcdx3, dGdx3);

% \[Theta]2[t]:
dMdx4 = [0, 0, -(M(3)*L(3)*s12), -(M(3)*L(3)*s12);
    0, 0, M(3)*L(3)*c12, M(3)*L(3)*c12;
    -(M(3)*L(3)*s12), M(3)*L(3)*c12, -2*L(2)*M(3)*L(3)*s2, ...
    -(L(2)*M(3)*L(3)*s2);
    -(M(3)*L(3)*s12), M(3)*L(3)*c12, -(L(2)*M(3)*L(3)*s2), 0];
dcdx4 = [-(M(3)*L(3)*c12*X(7)*(X(7)+X(8)))-M(3)*L(3)*c12*X(8)*(X(7)+X(8));
    -(M(3)*L(3)*s12*X(7)*(X(7)+X(8)))-M(3)*L(3)*s12*X(8)*(X(7)+X(8));
    -(L(2)*M(3)*L(3)*c2*X(7)*X(8))-L(2)*M(3)*L(3)*c2*X(8)*(X(7)+X(8));
    L(2)*M(3)*L(3)*c2*X(7)^2];
dGdx4 = [0; 0; g*M(3)*L(3)*c12; g*M(3)*L(3)*c12];
dFdx4 = GradF(MM, c, G, dMdx4, dcdx4, dGdx4);

% (x^\[Prime])[t]: zero(4,1)

% (y^\[Prime])[t]: zero(4,1)

% (\[Theta]1^\[Prime])[t]:
dMdx7 = zeros(4,4);
dcdx7 = [
    -((L(2)*M(3)+M(1)*L(1))*s1*X(7))+(-((L(2)*M(3)+M(1)*L(1))*s1) - ...
    M(3)*L(3)*s12)*X(7)-M(3)*L(3)*s12*X(8)-M(3)*L(3)*s12*(X(7)+X(8));
    (L(2)*M(3)+M(1)*L(1))*c1*X(7)+((L(2)*M(3)+M(1)*L(1))*c1 + ...
    M(3)*L(3)*c12)*X(7)+M(3)*L(3)*c12*X(8)+M(3)*L(3)*c12*(X(7)+X(8));
    -2*L(2)*M(3)*L(3)*s2*X(8);
    2*L(2)*M(3)*L(3)*s2*X(7)];
dGdx7 = zeros(4,1);
dFdx7 = GradF(MM, c, G, dMdx7, dcdx7, dGdx7);

% (\[Theta]2^\[Prime])[t]:
dMdx8 = zeros(4,4);
dcdx8 = [
    -(M(3)*L(3)*s12*X(7))-M(3)*L(3)*s12*X(8)-M(3)*L(3)*s12*(X(7)+X(8));
    M(3)*L(3)*c12*X(7)+M(3)*L(3)*c12*X(8)+M(3)*L(3)*c12*(X(7) + X(8));
    -(L(2)*M(3)*L(3)*s2*X(7))-L(2)*M(3)*L(3)*s2*X(8) - ...
    L(2)*M(3)*L(3)*s2*(X(7)+X(8));
    0];
dGdx8 = zeros(4,1);
dFdx8 = GradF(MM, c, G, dMdx8, dcdx8, dGdx8);

dFdX(1:4, 5:8) = eye(4);
dFdX(5:8, 3) = dFdx3;
dFdX(5:8, 4) = dFdx4;
dFdX(5:8, 7) = dFdx7;
dFdX(5:8, 8) = dFdx8;
end

function dFdX = jac2(X, S)
dFdX = zeros(8);

% parameters
c1 = cos(X(3));
c2 = cos(X(4));
c12 = cos(X(3)+X(4));

s1 = sin(X(3));
s2 = sin(X(4));
s12 = sin(X(3)+X(4));

M = S.M;
L = S.L;
g = S.g;

% mass matrix
MM = [M(2)+M(4)+M(1)*L(1)^2+M(3)*L(2)^2+M(3)*L(3)^2+2*M(3)*L(3)*L(2)*c2,...
    M(3)*L(3)^2+M(3)*L(3)*L(2)*c2+M(4);
    M(3)*L(3)^2+M(3)*L(3)*L(2)*c2+M(4), M(4)+M(3)*L(3)^2];

% coriolis/centrifugal forces
c = [
    -M(3)*L(3)*L(2)*s2*X(8), -M(3)*L(3)*L(2)*s2*(X(7) + X(8));
    M(3)*L(3)*L(2)*s2*X(7), 0
    ]*X(7:8);

% gravity
G = g * [(M(1)*L(1)+M(3)*L(2))*s1+M(3)*L(3)*s12; M(3)*L(3)*s12];

% \[Theta]1[t]:
dMdx3 = [0, 0; 0, 0];

dcdx3 = [0; 0];

dGdx3 = [g*((L(2)*M(3)+M(1)*L(1))*c1+M(3)*L(3)*c12); g*M(3)*L(3)*c12];
dFdx3 = GradF(MM, c, G, dMdx3, dcdx3, dGdx3);

% \[Theta]2[t]:
dMdx4 = [-2*L(2)*M(3)*L(3)*s2, -(L(2)*M(3)*L(3)*s2); 
    -(L(2)*M(3)*L(3)*s2), 0];

dcdx4 = [-(L(2)*M(3)*L(3)*c2*X(7)*X(8))-L(2)*M(3)*L(3)*c2*X(8)*(X(7)+X(8));
    L(2)*M(3)*L(3)*c2*X(7)^2];

dGdx4 = [g*M(3)*L(3)*c12; g*M(3)*L(3)*c12];
dFdx4 = GradF(MM, c, G, dMdx4, dcdx4, dGdx4);

% (\[Theta]1^\[Prime])[t]:
dMdx7 = [0, 0; 0, 0];

dcdx7 = [-2*L(2)*M(3)*L(3)*s2*X(8); 2*L(2)*M(3)*L(3)*s2*X(7)];

dGdx7 = [0; 0];
dFdx7 = GradF(MM, c, G, dMdx7, dcdx7, dGdx7);

% (\[Theta]2^\[Prime])[t]:
dMdx8 = [0, 0; 0, 0];

dcdx8 = [-(L(2)*M(3)*L(3)*s2*X(7))-L(2)*M(3)*L(3)*s2*X(8) - ...
    L(2)*M(3)*L(3)*s2*(X(7)+X(8)); 0];

dGdx8 = [0; 0];
dFdx8 = GradF(MM, c, G, dMdx8, dcdx8, dGdx8);

dFdX(3:4, 7:8) = eye(2);
dFdX(7:8, 3) = dFdx3;
dFdX(7:8, 4) = dFdx4;
dFdX(7:8, 7) = dFdx7;
dFdX(7:8, 8) = dFdx8;
end

function dFdx = GradF(MM, c, G, dMdx, dGdx, dcdx)
dFdx = (MM\dMdx/MM)*(c + G) - MM\(dcdx + dGdx);
end