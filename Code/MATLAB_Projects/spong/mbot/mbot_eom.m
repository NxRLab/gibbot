function F = mbot_eom(dof, S)
%MBOT_EOM Returns handles to the equations of motion and mass matrix
%   for the Monkeybot.  The degrees of freedom, dof, can be 2 ('dof2') or
%   4 ('dof4').  S is a struct containing external forces,
%   masses/intertias, lengths, and gravity.  The state space of the
%   solution is R^2 x T^2 x TR^2, TT^2.

switch dof
    case 'dof2'
        F = @(t, X) dof2(t, X, S);
    case 'dof4'
        F = @(t, X) dof4(t, X, S);
    case 'impact'
        F = @(X, Si) ff2sw(X, Si);
    case 'pfaffian'
        F = @(t, X) dofP(t, X, S);
end
end

function dX = dofP(t, X, S)
A = S.A;
MM = mbot_utils('mass', t, X, S);

P = eye(8);
if ~isempty(A)
    P(5:8,5:8) = eye(4) - MM\A'/(A/MM*A')*A;
end

dX = P*dof4(t, X, S);
end

function dX = dof4(t, X, S)
dX = zeros(8,1);

% parameters
c1 = cos(X(3));
c12 = cos(X(3)+X(4));

s1 = sin(X(3));
s2 = sin(X(4));
s12 = sin(X(3)+X(4));

U = S.U;
M = S.M;
L = S.L;
g = S.g;

% mass matrix
MM = mbot_utils('mass', t, X, S);

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

% update state
dX(1:4) = X(5:8);
dX(5:8) = MM\(U(t,X,S) - c - G);
end

function dX = dof2(t, X, S)
dX = zeros(8,1);

% parameters
c2 = cos(X(4));

s1 = sin(X(3));
s2 = sin(X(4));
s12 = sin(X(3) + X(4));

u = S.U(t,X,S);
u = u(3:4);
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

% update state
dX(1:4) = X(5:8);
dX(7:8) = MM\(u - c - G);
end

function [X S P] = ff2sw(X, S)
%FF2SW returns the post-impact velocities from free flight to swinging
[X S] = mbot_utils('flip', 0, X, S);

% parameters
c1 = cos(X(3));
c2 = cos(X(4));
c12 = cos(X(3)+X(4));

s1 = sin(X(3));
s12 = sin(X(3)+X(4));

M = S.M;
L = S.L;

% pre- to post-velocity impact map
d=(M(2)+L(2)^2*M(3)+M(1)*L(1)^2)*(M(4)+M(3)*L(3)^2) - ...
    L(2)^2*M(3)^2*L(3)^2*c2^2;

P=[
    0, 0, 0, 0;
    0, 0, 0, 0;
    ((L(2)*M(3)+M(1)*L(1))*(M(4)+M(3)*L(3)^2)*c1 - ...
    L(2)*M(3)^2*L(3)^2*c2*c12)/d, ...
    ((L(2)*M(3)+M(1)*L(1))*(M(4)+M(3)*L(3)^2)*s1 - ...
    L(2)*M(3)^2*L(3)^2*c2*s12)/d, 1, 0;
    
    (-(L(2)*M(3)+M(1)*L(1))*c1*(M(4)+M(3)*L(3)^2+L(2)*M(3)*L(3)*c2) + ...
    M(3)*L(3)*(M(2)+L(2)^2*M(3)+M(1)*L(1)^2+L(2)*M(3)*L(3)*c2)*c12)/d, ...
    (-(L(2)*M(3)+M(1)*L(1))*(M(4)+M(3)*L(3)^2+L(2)*M(3)*L(3)*c2)*s1 + ...
    M(3)*L(3)*(M(2)+L(2)^2*M(3)+M(1)*L(1)^2+L(2)*M(3)*L(3)*c2)*s12)/d, 0, 1
    ];

X(5:8)=P*X(5:8);
end