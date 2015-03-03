function port = port_open(pname)
%Opens the PIC32 communication serial port.
%   The name of the port is stored in settings.txt.  If that file does not exist, the
%   user will be prompted to enter a serial port name
%
%   port = port_open(pname)
%
%   Input Arguments:
%       pname - the name of the serial port.
%   Output Arguments:
%       The name of the serial port.
    BAUD = 115200;


    % create the user prompt    
    port_close();
pname='COM15'; %added to get around missing settings.txt file
    if strcmp(pname,'1') %allow for debugging by writing data to console
        port.port = '1';
    else
        port = serial(pname, 'BaudRate', BAUD, 'FlowControl', 'hardware'); %#ok<TNMLP>
        fopen(port);
    end


    
end