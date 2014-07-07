function mbplot(type, n, N, slns, S)
% uniform color for all plots
S.color = 'bg';

switch type
    case 'anim'
        animate(n, N, slns, S);
    case 'lpp'
        lpp(n, N, slns, S);
end
end

function animate(n, N, slns, S)
figure;
axis equal

for j = N
    i = 2 - mod(j, 2);
    t = linspace(slns(j).x(1), slns(j).x(end), n);
    
    
    mwin = 1*sum(S.p(i,3:4))*ones(1,4);
    mwin(1) = - mwin(1);
    mwin(3) = - mwin(3);

    
    for X = deval(slns(j), t);
        P = mbqnt('xy', X, S.p(i,:));
        
        % plot
        figure(gcf)
        
        % draw links
        plot(P(1:3,1)', P(1:3,2)', [S.color(i) '-']);
        hold on
        plot(P(3:5,1)', P(3:5,2)', [S.color(mod(i, 2) + 1) '-']);
        
        % draw points of interest
        plot(P(1,1), P(1,2), 'co', 'MarkerSize', 5);
        plot(P(2,1), P(2,2), [S.color(1) '.'], 'MarkerSize', 15);
        plot(P(3,1), P(3,2), 'ro', 'MarkerSize', 5);
        plot(P(4,1), P(4,2), [S.color(2) '.'], 'MarkerSize', 15);
        plot(P(5,1), P(5,2), 'co', 'MarkerSize', 5);
        axis([X(1) X(1) X(2) X(2)] + mwin)
        grid on;
        hold off
    end
end
end

function lpp(~, N, slns, ~)
N0 = N(1);

if mod(N0, 2)
    xb = [slns(N0).y(4,1), slns(N0+1).y(3,end), ...
        slns(N0+1).y(3,1), slns(N0).y(4,end)];
    vb = [slns(N0).y(8,1), slns(N0+1).y(7,end), ...
        slns(N0+1).y(7,1), slns(N0).y(8,end)];
    
    xg = [slns(N0+1).y(4,1), slns(N0).y(3,end), ...
        slns(N0).y(3,1), slns(N0+1).y(4,end)];
    vg = [slns(N0+1).y(8,1), slns(N0).y(7,end), ...
        slns(N0).y(7,1), slns(N0+1).y(8,end)];
else
    xb = [slns(N0+1).y(4,1), slns(N0).y(3,end), ...
        slns(N0).y(3,1), slns(N0+1).y(4,end)];
    vb = [slns(N0+1).y(8,1), slns(N0).y(7,end), ...
        slns(N0).y(7,1), slns(N0+1).y(8,end)];
    
    xg = [slns(N0).y(4,1), slns(N0+1).y(3,end), ...
        slns(N0+1).y(3,1), slns(N0).y(4,end)];
    vg = [slns(N0).y(8,1), slns(N0+1).y(7,end), ...
        slns(N0+1).y(7,1), slns(N0).y(8,end)];
end

figure;
subplot(1,2,2);

subplot(1,2,1);
plot(xb(1), vb(1), '*k', xb(1:2), vb(1:2), '--b', xb(3:4), vb(3:4), '--b')
title('blue link phase portrait')
xlabel('\theta')
ylabel('\omega')
axis equal
hold on;

subplot(1,2,2);
plot(xg(3), vg(3), '*k', xg(1:2), vg(1:2), '--g', xg(3:4), vg(3:4), '--g')
title('green link phase portrait')
xlabel('\theta')
ylabel('\omega')
axis equal
hold on;

for i = N
    if mod(i, 2)
        % even impact => green is fixed, blue is swinging
        subplot(1,2,2);
        plot(slns(i).y(3,:), slns(i).y(7,:), 'g');
        
        subplot(1,2,1);
        plot(slns(i).y(4,:), slns(i).y(8,:), 'b');
    else
        % odd impact => opposite of even impact
        subplot(1,2,1);
        plot(slns(i).y(3,:), slns(i).y(7,:), 'b');
        
        subplot(1,2,2);
        plot(slns(i).y(4,:), slns(i).y(8,:), 'g');
    end
end
end