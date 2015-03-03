function write_pic(port,fmt,varargin)
% Writes data to the PIC.  Used to ensure expected newline behavior.
%
%   write_pic(port,fmt,...)
%
%   Input Arguments:
%       port - the serial port, or 1 for output to the console
%       fmt - a printf compatible format string
%       ... - a list of variables corresponding to the format string
%
%   fprintf over serial port adds an extra newline if the format string
%           is just the desired output string.
    s = sprintf(fmt,varargin{:});
    if port.port == '1'
        fprintf('%s',s);
    else
        fprintf(port,'%s',s);
    end
end