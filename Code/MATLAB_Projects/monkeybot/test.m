N = 5; % # number of impacts
% initial state
x0 = [1.018087600792090; % q1
    1.082330013256065;   % q2
    -0.128245982315845;  % dq1/dt
    -0.000559814071643]; % dq2/dt

u = -0.313378362496681; % constant torque value
U = @(t,X,S) [0 0 0 u]'; % torque function (last two entries are d2q/dt2)
T = 2.575867383630918; % switching time
S = mbmdl(x0, u, T);  % create the robot structure

sln = mbode(N, U, S); % solve for N impacts with U as the forcing function
qntplot(sln, 1:N, U, S) % plot the post-impact (x,y) location of the pivot
anim(sln, 1:N, 30, S) % animate the swings using 30 points per swing.