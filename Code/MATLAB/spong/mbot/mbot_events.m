function h = mbot_events(type, S)
switch type
    case 'zero impact'
        h = @(t, X) zimpact(t, X, S);
    case 'zero height'
        h = @(t, X) zheight(t, X, S);
    case 'target energy'
        h = @(t, X) tenergy(t, X, S);
    case 'zero angular velocity'
        h = @(t, X) zangvel(t, X, S);
    case 'zero down'
        h = @(t, X) zdown(t, X, S);
    case 'zero cost'
        h = @(t, X) zcost(t, X, S);
end
end

function [value, stop, direction] = zcost(t, X, S)
F = mbot_eom('dof2', S);
L = S.L;

th1=X(3);
th12=X(3)+X(4);
dth1=X(7);
dth2=X(8);

J = [-L(2)*cos(th1)-L(4)*cos(th12); dth1; dth2];
dJdX = sparse([1 1 2 3], [3 4 7 8], ...
    [L(2)*sin(th1)+L(4)*sin(th12),L(4)*sin(th12),1,1],3, 8);
DCDT = J'*dJdX*F(t, X);

value = DCDT;
stop = 0;
direction = 1;
end

function [value, stop, direction] = zdown(~, X, ~)
value=norm(X);
stop=1;
direction=0;
end

function [value, stop, direction] = zimpact(t, X, S)
P=mbot_utils('power', t, X, S);
value=P(1);
stop=1;
direction=1;
end

function [value, stop, direction] = zangvel(~, X, ~)
value=X(7);
stop=1;
direction=0;
end

function [value, stop, direction] = zheight(t, X, S)
R=mbot_utils('xy', t, X, S);

value = R(5,2);
stop = 1;
direction = 0;
end

function [value, stop, direction] = tenergy(t, X, S)
E = sum(mbot_utils('energy', t, X, S));

value = E + 36;
stop = 1;
direction = 0;
end