function qntplot(slns, N, U, S)
m = N(1);
M = numel(slns(1).y(:,end)) / 8;
color = jet(numel(N));

for i = N
    slns(i).y = mbqnt('dom', slns(i).y, S.p);
end

% figure;
% for i = N
%     [KE, PE] = mbqnt('energy', slns(i).y(:), S.p);
%     KE = reshape(KE, M, numel(slns(i).x));
%     PE = reshape(PE, M, numel(slns(i).x));
%     E = KE + PE;
%     
%     subplot(3,1,1)
%     plot(slns(i).x, E, 'Color', color(i - m + 1,:))
%     hold on;
%     plot(slns(i).x(end), E(end), 'k*');
%     
%     subplot(3,1,2)
%     plot(slns(i).x, KE, 'Color', color(i - m + 1,:))
%     hold on;
%     plot(slns(i).x(end), KE(end), 'k*');
%     
%     subplot(3,1,3)
%     plot(slns(i).x, PE, 'Color', color(i - m + 1,:))
%     hold on;
%     plot(slns(i).x(end), PE(end), 'k*');
% end
% subplot(3,1,1)
% title('total energy vs time')
% subplot(3,1,2)
% title('kinetic energy vs time')
% subplot(3,1,3)
% title('potential energy vs time')
% 
% figure;
% title('state vs time');
% s = [3 4 7 8];
% scol = ['b', 'g', 'r', 'k'];
% set(gca, 'ColorOrder', jet(length(S.X0)), 'NextPlot', 'replacechildren');
% for i = N
%     for j = 1:4
%         subplot(2,2,j)
%         plot(slns(i).x, slns(i).y(s(j),:), scol(j))
%         hold on;
%     end
% end
% 
% titles = {'\theta1 vs time', '\theta2 vs time', ...
%     'd\theta1 vs time', 'd\theta2 vs time'};
% for j = 1:4
%     subplot(2,2,j)
%     title(titles{j});
% end

figure;
for i = N
    [X, Y] = mbqnt('xy', slns(i).y(:), S.p);
    plot(X(:,1), Y(:,1), '*', 'Color', color(i - m + 1,:));
    hold on;
end
title('(x,y) position of fixed-link')
xlabel('x');
ylabel('y');
axis square

% figure;
% for i = N
%     t = linspace(slns(i).x(1), slns(i).x(end), 100);
%     
%     if mod(i, 2)
%         Uf = arrayfun(@(j) [0 0 0 1]*U(j, deval(slns(i), j), S), t);
%     else
%         Uf = arrayfun(@(j) [0 0 0 1]*U(j, deval(slns(i), j), S), t);
%     end
%     
%     plot(t, Uf, 'Color', color(i - m + 1,:))
%     hold on;
%     plot(t(end), Uf(end), 'k*');
% end
% title('control')