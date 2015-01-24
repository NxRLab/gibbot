function anim(slns, N, n, S)
figure;
axis equal

% record a movie
% movnum = 1;
% mov(1:numel(N)) = struct('cdata', [], 'colormap', []);

% number of solutions to animate
M = 1:numel(slns(1).y(:,end)) / 8;

% animation window
p = S.p;
x = slns(1).y(1:8:end,1);
y = slns(1).y(2:8:end,2);
L = p(3);
mwin = L*[-2 2 -2 2]*3 + 0*[min(x) max(x) min(y) max(y)];
% mwin = L*[-2 2 -2 2];% + [min(x) max(x) min(y) max(y)];

% get slope
% [PX0, PY0] = mbqnt('xy', slns(1).y(:,end), p);
% A = [cos(pi/2) sin(pi/2);-sin(pi/2) cos(pi/2)];
[lxe, lye] = mbqnt('xy', slns(end).y(:,end), p);

% animate
for j = N
    i = 2 - mod(j, 2);
    h = mod(i, 2) + 1;
    t = linspace(slns(j).x(1), slns(j).x(end), n);

    for X = deval(slns(j), t);
        [PX, PY] = mbqnt('xy', X, p);
        
        % plot
        figure(gcf)
        
        % draw links
        for k = M
            plot(PX(k,1:3), PY(k,1:3), [S.color(i) '-']);
            hold on
            plot(PX(k,3:5), PY(k,3:5), [S.color(h) '-']);
        end
        
        % draw points of interest
        plot(PX(:,1), PY(:,1), 'co', 'MarkerSize', 5);
        plot(PX(:,2), PY(:,2), [S.color(i) '.'], 'MarkerSize', 15);
        plot(PX(:,3), PY(:,3), 'ro', 'MarkerSize', 5);
        plot(PX(:,4), PY(:,4), [S.color(h) '.'], 'MarkerSize', 15);
        plot(PX(:,5), PY(:,5), 'co', 'MarkerSize', 5);
        
        
%         plot([0 lxe(end)], [0 lye(end)], 'k', 'LineWidth', 2);
% plot([0 5], [0 0], 'k', 'LineWidth', 2);
        
%         axis([-70 -50 -10 0])
%         axis([mean(PX(:,3)) mean(PX(:,3)) mean(PY(:,3)) mean(PY(:,3))])
%         mwin = mwin + [mean(PX(:,3)) mean(PX(:,3)) mean(PY(:,3)) mean(PY(:,3))];
%         axis(mwin);
        axis(mwin + [mean(PX(:,3)) mean(PX(:,3)) mean(PY(:,3)) mean(PY(:,3))])
        % mwin = [-2*3/4*L/n -2*3/4*L/n 0 0]/100 + mwin;
        % axis([-9 1 -2 2]);
        % axis([-9, 1, -3, 3])
%         axis equal
        % grid on;
        
%         a = A*[PX0(1,5);PY0(1,5)];
%         plot(PX0(1,[1 5]), PY0(1,[1 5]), 'k',-[0 a(1)], -[0 a(2)], 'k')
%         
%         a = A*[PX0(2,5);PY0(2,5)];
%         plot(PX0(2,[1 5]), PY0(2,[1 5]), 'k', [0 a(1)], [0 a(2)], 'k')
%         axis equal
        hold off
        
%         mov(movnum) = getframe(gcf);
%         movnum = movnum + 1;
    end
end

% Create AVI file.
% movie2avi(mov, 'mbot_sim.avi', 'compression', 'None');

end