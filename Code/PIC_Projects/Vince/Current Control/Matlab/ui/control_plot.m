function [data, handles] = control_plot(menu,cmd,port,nsamples)  
% Plots the control results from the pic
%
%   control_plot(menu,cmd,port)
%   control_port(menu,cmd,port,nsamples)
%
%   Input Arguments:
%       menu - the menu that led to this function being called
%       cmd  - the specific command that led to this function being called
%       port - the serial port
%       nsamples (optional) - See pic_plot.m
%   Output Arguments:
%       data    - the data that was retrieved
%       handles - cell array handles to the plots that were created
%   Data will be plotted in the current figure
    nin = nargin;
    if nin < 4
        nsamples = {};
    else
        nsamples = {nsamples};
    end
    [m,data,handles] = pic_plot(menu,cmd,port,'%d %d %d',nsamples{:}); %#ok<ASGLU>
    rmenu = root_menu(menu);
    if strcmpi(rmenu.options.show_u.value,'n')
        set(handles{3},'Visible','off');
        legend('r','y');
    else
        legend('r','y','u');
    end
    
    %  calculate an error norm
    score = norm(data(1,:)-data(2,:),1);
    fprintf('\nScore: %d\n',int32(score));
    title(sprintf('Response Score: %d',int32(score)));
    xlabel('Samples');  
    
end