NSLNS = 0;

%% Ruina short solution
th1 = 0.582250216793815;
th2 = pi - 2*th1;
x0 = -[th1;th2;0;0];
T = 2.450688411986252;
U = @(t,X,S) [0 0 0 0]';
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'Ruina short';

%% Ruina long solution
th1 = 1.077398914708292;
th2 = pi - 2*th1;
x0 = -[th1;th2;0;0];
T = 2.508001197970272;
U = @(t,X,S) [0 0 0 0]';
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'Ruina long';

%% Ruina overhead short solution
th1 = 2.970448901508585;
th2 = pi - 2*th1;
x0 = [th1;th2;0;0];
T = 5.222027100797385;
U = @(t,X,S) [0 0 0 0]';
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'Ruina overhead short';

%% Ruina overhead long solution
th1 = 2.681526755579172;
th2 = pi - 2*th1;
x0 = [th1;th2;0;0];
T = 3.9184302720274995;
U = @(t,X,S) [0 0 0 0]';
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'Ruina overhead long';

%% Passive overhead 1 solution
th1 = 3.0095461914241954;
th2 = pi - 2*th1;
x0 = -[th1;th2;0;0];
T = 13.751248986583683;
U = @(t,X,S) [0 0 0 0]';
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'Ruina overhead 1';

%% brachiating up an incline, strange periodicity
% slope = 0.03;
% inter = pi - 0.914538581242468;
% x0 = [inter/2 - slope;
%     pi - inter;
%     -0.137028014768253;
%     -0.051181565503457];

x0 = [1.018087600792090;
    1.082330013256065;
    -0.128245982315845;
    -0.000559814071643];

u = -0.313378362496681;
U = @(t,X,S) [0 0 0 u]';
T = 2.575867383630918;
S = mbmdl(x0, u, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'up1';

%% uphill climber
x0 = [1.097577912192168;
    0.906163553323463;
    -0.037549657597080;
    0.010357952981771];

u = -0.408329928629115;
U = @(t,X,S) [0 0 0 u]';
T = 2.517331549049402;
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'up2';

%% uphill climber
x0 = -[0.955924747810023;
    1.201152611453995;
    -0.114625002206396;
    -0.083772212082339];

u = 0.371120130190596;
U = @(t,X,S) [0 0 0 u]';
T = 2.594264298255292;
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'up3';

%% brachiating down an incline, possible spiral solution still blotch
x0 = [0.992667423201234;
    1.180641759414759;
    -0.197110013582639;
    -0.105919481637035];

u = [2.675867383630918; % T2
    -0.313378362496681];

T = u(1);
S = mbmdl(x0, u(2), T);
U = @(t, X, S) [0;0;0;u(2)];
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'down1 ctls';

%% brachiating down an incline
x0 = [0.924675349191732;
    1.353088748443709;
    -0.146010052777174;
    -0.355616609539763];

u = [2.775867383630918; % T2
    -0.413378362496681];

T = u(1);
S = mbmdl(x0, u(2), T);
U = @(t, X, S) [0;0;0;u(2)];
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'down2 ctls';

%% passive brachiating down an incline 1
% slope = 0.00054;
% x0 = [th1 th2 -0.126986816293506 -0.913375856139019]';
x0 = [-0.677675363048862;
    -1.947069801361313;
    0.103605148927435;
    -0.434685998758615];
u = 0;
U = @(t,X,S) [0 0 0 0]';
T = 1.946270044527813;
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'down1';

%% passive brachiating down an incline 2
% x0 = [-1.177398914708292, 5.296390483006377, 0, 0] <- found with
% slope = 0.1;
x0 = [-0.540509859099205;
    -2.162119308116608;
    0.112017268516448;
    -0.259410166495533];

u = 0;
U = @(t,X,S) [0 0 0 0]';
T = 2.036805339360215;
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'down2';

%% passive brachiating down an incline 3
% x0 = [-1.204385731001798, 5.296390483006377, 0, 0] <- found with
% slope = 0.126986816293506;
x0 = [-0.600485094771005;
    -2.064302969395578;
    0.115245400436062;
    -0.337089229219747];

u = 0;
U = @(t,X,S) [0 0 0 0]';
T =  1.989021501193575;
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'down3';

%% passive brachiating down an incline 4
% x0 =
% [0.935048859800099,1.615827963667178,0.051314135446306,0.624096645280910]
% <- found with (using brute force search), slow convergence
x0 = [0.899007452023613;
    1.657635947769655;
    0.019879161062132;
    0.616167556292246];

u = 0;
U = @(t,X,S) [0 0 0 0]';
T = 1.898995260532409;
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'down4';

%% passive brachiating down an incline 5
% found with (using brute force search), close to limit of period 1 slns
x0 = [0.492411657932034;
    2.244952815152862;
    -0.101696400111517;
    0.200221193918152];

u = 0;
U = @(t,X,S) [0 0 0 0]';
T = 2.087204325322404;
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'down5';

%% passive brachiating down an incline 6
% found with (using brute force search), close to limit of period 1 slns
x0 = [0.481059047955221;
    2.265067573529026;
    -0.098297056088443;
    0.187029955471123];

u = 0;
U = @(t,X,S) [0 0 0 0]';
T = 2.100965239320152;
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'down6';

%% passive brachiating down an incline
% slope = .1;  <- a slope value that the passive down climber converge to
% this one forms a large figure 8 as the velocity limit cycle
% x0 = [-0.682250216793815;
%   -1.977092220002163;
%   -0.126986816293506;
%   -0.913375856139019]; <-converges to final state

x0 = [-0.884700605443465;
    -2.294319538984310;
    -0.027724924525564;
    -0.017878320432234];

u = 0;
U = @(t,X,S) [0 0 0 0]';
T = 2.194002363974306;
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'down prd?';

%% climbing up solution
x0 = [1.076691821608184;
    1.102044044080353;
    0.000000014745591;
    -0.000000070913052];

u = [2.685017139552529; % T1
    -0.496305188068243; % u1
    2.375867383630918; % T2
    -0.313378362496681]; % u2

T = u(1:2:end);
S = mbmdl(x0, u, T);

f = @(t) mod(t,sum(S.T)) <= S.T(1);
U = @(t, X, S) [0;0;0;f(t)*u(2) + (~f(t))*u(4)];
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'up prd2';

% perturbation for climbing up solution
H = [-2.038446899557161;
    -1.168120157221315;
    1.806087736618433;
    -2.824678334627122;
    0.743783325287040;
    0.399474411741413;
    -0.024102356877803;
    0.166151759464206];

%% climbing up solution
x0 = [1.205416445820512;
    1.246766181625234;
    -0.166260136441319;
    -0.137641666450081];

u = [2.685017139552529; % T1
    -0.496305188068243; % u1
    2.675867383630918; % T2
    -0.313378362496681]; % u2

T = u(1:2:end);
S = mbmdl(x0, u, T);

f = @(t) mod(t,sum(S.T)) <= S.T(1);
U = @(t, X, S) [0;0;0;f(t)*u(2) + (~f(t))*u(4)];
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'very small up prd2';

%% climbing up solution 2 with spiral velocity, appears to be period 6
% x0 = [1.076691821608184; 0.988209010373425; -0.035265123706730;
%   -0.003526512370673];

x0 = [1.081589574148060;
    0.974415276921854;
    -0.033203039581499;
    0.001946476012091];

u = [2.327000055842979;
    0.164045596099582;
    2.580086143409019;
    -0.563725215482259];

T = u(1:2:end);
S = mbmdl(x0, u, T);
f = @(t) mod(t,sum(T)) <= T(1);
U = @(t, X, S) [0;0;0;f(t)*u(2) + (~f(t))*u(4)];
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'up prd6';

%% climbing up period 20 solution
% x0 = [0.865388735958930; % perturbed soln
%     1.253272160307315;
%     -0.000003931636720;
%     0.000000606250364];

x0 = [0.777908177217551;
    0.643441722368406;
    0.404292829097530;
    -0.600692846698753];

u = [2.907647804435199;
    -0.420116543257614;
    2.401549400807765;
    -0.450617239333640];

T = u(1:2:end);
S = mbmdl(x0, u, T);

f = @(t) mod(t,sum(S.T)) <= S.T(1);
U = @(t, X, S) [0;0;0;f(t)*u(2) + (~f(t))*u(4)];
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'up prd20';

%% climbing down solution with center velocity solution (with what appears
% to be two centers per link)
% x0 = [1.663465822876455;0.774537856518077;
%         -0.457755991490096;0.495468303559019];

x0 = [1.663529877339778;
    0.774466572501058;
    -0.457758983407065;
    0.495547893793525];

u = [2.341345641074031;
    -0.414454134082102;
    3.048963065127268;
    -0.403393319572229];

T = u(1:2:end);
S = mbmdl(x0, u, T);
f = @(t) mod(t,sum(T)) <= T(1);
U = @(t, X, S) [0;0;0;f(t)*u(2) + (~f(t))*u(4)];
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'dwn prd??';

%% passive brachiating down an incline period 2
% found by doing a grid search and then applying newton's method
% slope = -0.051413827156945;
x0 = [0.289862407707761;
    -2.634547708198982;
    0.326986454032026;
    -0.223718358059866];

u = 0;
U = @(t,X,S) [0 0 0 0]';
T = 2.285761325623969;
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'down prd 2';

%% unstable uphill climber
x0 = [1.057142857142857;
    1.020119778133858;
    -0.142857142857143;
    0];

u = -0.300969889789734;
U = @(t,X,S) [0 0 0 u]';
T = 2.545032192289546;
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'unstable up1?';

%% unstable uphill climber
x0 = [1.180796326794896;
    0.580000000000000;
    -0.131098736026140;
    -0.358229257604226];

u = [2.522760777883479; -0.351503145805066];
U = @(t,X,S) [0 0 0 u(2)]';
T = u(1);
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'unstable up2?';

%% limping downhill climber
x0 = [-0.535684270852612;
    -0.743142690539082;
    1.148420269523612;
    -1.480822521711319];

u = -0.923056436889871;
U = @(t,X,S) [0 0 0 u]';
T = 1.015700798968916;
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'limp down prd2';

%% Passive stable overhead
x0 = -[2.973099250614787;
    -2.80438229015798;
    -0.03462493847624186;
    0.005615756009928525];
T = 5.0654472377262705;
U = @(t,X,S) [0 0 0 0]';
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'Passive stable overhead';

%% Ruina solution 1
th1 = 0.05018923676372332;
th2 = pi - 2*th1;
x0 = [th1;th2;0;0];
T = 4.639889931877234;
U = @(t,X,S) [0 0 0 0]';
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'Ruina solution 1';

%% Ruina solution 2
th1 = 0.39446266286113674;
th2 = pi - 2*th1;
x0 = -[th1;th2;0;0];
T = 11.421577728252693;
U = @(t,X,S) [0 0 0 0]';
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'Ruina solution 2';
S.options = odeset('RelTol', 1e-12,'AbsTol', 1e-12);

%% Ruina solution 3
th1 = 0.7885100664735151;
th2 = pi - 2*th1;
x0 = -[th1;th2;0;0];
T = 12.178729368513206;
U = @(t,X,S) [0 0 0 0]';
S = mbmdl(x0, 0, T);
S.options = odeset('RelTol', 1e-13,'AbsTol', 1e-13);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'Ruina solution 3';

%% Walking solution
x0 = [-3.285959863772177;
    3.441592653589793;
    0.263272574893425;
    -0.033775497321736];
T = 1.796002778024140;
U = @(t,X,S) [0 0 0 0]';
S = mbmdl(x0, 0, T);
NSLNS = NSLNS + 1;
Solutions{NSLNS}.U = U;
Solutions{NSLNS}.S = S;
Solutions{NSLNS}.name = 'walking';