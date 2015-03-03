function A = read_pic(port,fmt)
% Reads from the pic, and issues an error if there is an error
%
%   A = read_pic(port,fmt,...)
%
%   Input Arguments:
%       port - the serial port, or 1 to read from the console
%       fmt - scanf format string
%   Output Arguments:
%       A - the output of the next line read, as parsed by sscanf
%
%   Lines begining with the alert character '\a' (ascii 7) will be interpreted as
%   errors, causing this function to issue an error
    if port.port == '1'
        s = input('Enter Output From PIC: ','s');
    else
        s = fscanf(port);
    end
    if ~isempty(s)
        if s(1) == 7 %7 is the ascii character for the bell or \a
            error(['read_pic:pic Error on the PIC: ',s(2:end)]);
        end
    end
    [A,cnt,err] = sscanf(s,fmt); %#ok<ASGLU>

    if ~isempty(err)
        error('read_pic:fmt PIC returned data that did not match the expected format.');
    end
end