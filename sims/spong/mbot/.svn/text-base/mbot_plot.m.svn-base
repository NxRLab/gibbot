function h = mbot_plot(type, S)
switch type
    case 'all'
        h = @(t, X, flag) plot_all(t, X, flag, S);
    case 'flipped'
        h = @(t, X, flag) plot_pos(t, X, flag, S);
end

end

function status = plot_pos(t, X, flag, S)
persistent P;
switch flag
    case 'init'   
        pos = get(0,'DefaultUicontrolPosition');
        pos(1) = pos(1) - 15;
        pos(2) = pos(2) - 15;
        uicontrol( ...
            'Style','pushbutton', ...
            'String','Stop', ...
            'Position',pos, ...
            'Callback',@StopButtonCallback, ...
            'Tag','stop');
        
        ud = get(gcbf,'UserData');
        ud.stop = 0;
        set(gcf,'UserData',ud);
    case'done'
        tall = P(:,1);
        
        Xall = P(:,2:end);
        figure(gcf)
        plot(tall, Xall);
    case []
        for i = 1:length(t)
           Xf = mbot_utils('flip', t(i), X(:,i), S);
          
           P = [P; t(i) Xf([1 2 5 6])'];
        end
end
ud = get(gcf,'UserData');
status = ud.stop;
end

function status = plot_all(t, X, flag, S)
persistent mwin;
status = 0;

switch flag
    case 'init'
        mwin = sum(S.L)*ones(1,4);
        mwin(1) = - mwin(1);
        mwin(3) = - mwin(3);
        
        pos = get(0,'DefaultUicontrolPosition');
        pos(1) = pos(1) - 15;
        pos(2) = pos(2) - 15;
        uicontrol( ...
            'Style','pushbutton', ...
            'String','Stop', ...
            'Position',pos, ...
            'Callback',@StopButtonCallback, ...
            'Tag','stop');
        
        ud = get(gcbf,'UserData');
        ud.stop = 0;
        set(gcf,'UserData',ud);
    case 'done'
    case []        
        for i = 1:length(t)
            P = mbot_utils('xy', t(i), X(:,i), S);
            E = sum(mbot_utils('energy', t(i), X(:,i), S));
            
            %plot
            figure(gcf)
            subplot(3,1,1)
            
            % draw links
            plot(P(1:3,1)', P(1:3,2)', [S.color(1) '-']);
            hold on
            plot(P(3:5,1)', P(3:5,2)', [S.color(2) '-']);
            
            % draw points of interest
            plot(P(1,1), P(1,2), 'co', 'MarkerSize', 5);
            plot(P(2,1), P(2,2), [S.color(1) '.'], 'MarkerSize', 15);
            plot(P(3,1), P(3,2), 'ro', 'MarkerSize', 5);
            plot(P(4,1), P(4,2), [S.color(2) '.'], 'MarkerSize', 15);
            plot(P(5,1), P(5,2), 'co', 'MarkerSize', 5);
            axis([X(1) X(1) X(2) X(2)] + mwin)
            %axis([X(1) + mwin(1), X(1) + mwin(2), -2, 2])
            axis equal
            grid on;
            hold off
            
            subplot(3,1,2)
            hold on
            plot(P(1,1), P(1,2), 'co', 'MarkerSize', 5);
            plot(P(2,1), P(2,2), 'g.', 'MarkerSize', 15);
            plot(P(3,1), P(3,2), 'r.', 'MarkerSize', 15);
            plot(P(4,1), P(4,2), 'g.', 'MarkerSize', 15);
            plot(P(5,1), P(5,2), 'co', 'MarkerSize', 5);
            
            subplot(3,1,3)
            hold on
            if isfield(S, 'tdiv')
                plot(t(i)/S.tdiv, E, '-');
            else
                plot(t(i), E, '-');
            end
        end
        
        ud = get(gcf,'UserData');
        status = ud.stop;
end
end

function StopButtonCallback(src,eventdata)
    ud = get(gcbf,'UserData'); 
    ud.stop = 1; 
    set(gcbf,'UserData',ud);    
end  % StopButtonCallback
