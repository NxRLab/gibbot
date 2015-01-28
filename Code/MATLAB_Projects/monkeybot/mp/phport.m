function phport(slns, N, p)
N0 = N(1);

for i = N
    slns(i).y = mbqnt('dom', slns(i).y, p);
end

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