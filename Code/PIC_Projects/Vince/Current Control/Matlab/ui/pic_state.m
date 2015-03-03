function pic_state(menu,cmd,port) %#ok<INUSL>
% Gets the state of the pic.  Reads the numeric value and
%   converts it to a string
%
%   pic_state(menu,cmd,port)
%
%   Input Arguments:
%       see pic_entry, this is a pic_entry action
    val = read_pic(port,'%d');
    switch val
        case 0
            disp('IDLE');
        case 1
            disp('PWM');
        case 2
            disp('TUNE (This is an Error!)');
        case 3
            disp('TRACK (This is an Error!)');
        case 4
            disp('HOLD')
        otherwise
            disp('State Unknown (????)');
    end
end