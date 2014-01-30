function posmap(slns, N)

th1 = mbqnt('(-pi, pi]', arrayfun(@(s) s.y(3, 1), slns));
th2 = mbqnt('(-pi, pi]', arrayfun(@(s) s.y(4, 1), slns));

h = jet(numel(N));
for i = N
    plot(th1(i), th2(i), '*', 'Color', h(i - N(1) + 1,:))
    hold on;
end
hold off;

figure;
subplot(2,1,1);
plot(th1(1:2:end), th2(1:2:end), '--');
xlabel('link 1 fixed: \theta1')
ylabel('link 1 fixed: \theta2')
hold on;
subplot(2,1,2);
plot(th1(2:2:end), th2(2:2:end), '--');
xlabel('link 2 fixed: \theta1')
ylabel('link 2 fixed: \theta2')
hold on;
for i = N
    if mod(i, 2)
        subplot(2,1,1);
        plot(th1(i), th2(i), '*', 'Color', h(i - N(1) + 1,:));
    else
        subplot(2,1,2);
        plot(th1(i), th2(i), '*', 'Color', h(i - N(1) + 1,:));
    end
end
hold off;

figure;
subplot(2,2,1);
plot(th1(1:2:end), th2(1:2:end), '--');
axis square
hold on;
subplot(2,2,2);
plot(diff(th1(1:2:end)), 'k*--');
hold on;
plot(diff(th2(1:2:end)), 'r*--');
axis square
subplot(2,2,3);
plot(th1(2:2:end), th2(2:2:end), '--');
hold on;
subplot(2,2,4);
plot(diff(th1(2:2:end)), 'k--*');
hold on;
plot(diff(th2(2:2:end)), 'r*--');
axis square
for i = N
    if mod(i, 2)
        subplot(2,2,1);
        plot(th1(i), th2(i), '*', 'Color', h(i - N(1) + 1,:));
    else
        subplot(2,2,3);
        plot(th1(i), th2(i), '*', 'Color', h(i - N(1) + 1,:));
    end
end

subplot(2,2,1);
xlabel('link 1 fixed: \theta1')
ylabel('link 1 fixed: \theta2')

subplot(2,2,2);
xlabel('k-th impact')
ylabel('\theta[k] - \theta[k-1]')
legend('\theta1', '\theta2')

subplot(2,2,3);
xlabel('link 2 fixed: \theta1')
ylabel('link 2 fixed: \theta2')

subplot(2,2,4);
xlabel('k-th impact')
ylabel('v[k] - v[k-1]')
legend('\theta1', '\theta2')

hold off;