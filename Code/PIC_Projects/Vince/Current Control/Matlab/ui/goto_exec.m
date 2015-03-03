function goto_exec(menu,cmd,port,samples)
% Loads a goto trajectory and executes it
%
%   goto_exec(menu,cmd,port,nsamples)
%
%   Input Arguments:
%       menu - the menu that led to this function being called
%       cmd  - the specific command that led to this function being called
%       port - the serial port
%       samples - name of option that stores the number of samples
%   Output Arguments:
%       data    - the data that was retrieved
%       handles - cell array handles to the plots that were created
%   Data will be plotted in the current figure
    angs = input('Enter angle in degrees: ','s');
    [angle,cnt,err] = sscanf(angs,'%d');
    if cnt ~= 1 || ~isempty(err)
        disp('Invalid input, aborting command.');   
        write_pic(port,'%d\n',-1); % tell the pic to abort the command
    else
        write_pic(port,'%d\n',0);
        write_pic(port,'%d\n',angle);
        control_plot(menu,cmd,port,samples);
    end        
end