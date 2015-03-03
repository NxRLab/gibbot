function [menu, data, handles] = pic_plot(menu,cmd,port,fmt,nsamples)  %#ok<INUSL>
% Plots data from the PIC. Can be used as a pic_entry action function.
%
%   pic_plot(menu,cmd,port,fmt)
%   pic_port(menu,cmd,port,fmt,nsamples)
%
%   Input Arguments:
%       menu - the menu that led to this function being called
%       cmd  - the specific command that led to this function being called
%       port - the serial port
%       fmt  - format string for each sample (scanf style)
%       nsamples (optional) - the menu option field from which to get the number of
%                             samples to request. If unspecified the PIC
%                             tells us what to do.
%   Output Arguments:
%       data    - the data that was retrieved
%       handles - cell array handles to the plots that were created
%   Data will be plotted in the current figure

    nin = nargin;
    if nin < 5
        nsamples = {};
    end
   
    %request the samples
    if ~isempty(nsamples)
        rmenu = root_menu(menu);
        write_pic(port,'%d\n',rmenu.options.(nsamples).value);
    end
    
    % The pic will send the number of rows
    dims = read_pic(port,'%u %u');
   
    data = zeros(dims(1),dims(2));
    for i=1:dims(1)
        data(i,:) = read_pic(port,fmt);
    end
    
    % plot the data in the current figure
    t = 1:dims(1);
    handles = cell(1,dims(2));
    data = data.';
    clf;
    hold all;
    for i = 1:dims(2)
        handles{i}=plot(t,data(i,:));
    end
    hold off;
    
    
end
    
    