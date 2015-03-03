function [format, user_display, user_prompt] = gains()
% called by pic_menu to determine the format of the user specified gains
% This should be editted by you. Note that in matlab strings are enclosed
%   by single quotation marks (i.e. 'this is a string').
%
%   Output Arguments:
%       format - printf/scanf compatible format string for reading/writing
%                your gains. (i.e '%d %d %f %f') requires 2 ints and 2
%                floats.
%       user_display - Message that is displayed to the user when reading
%                      the gains from the PIC.  Should use printf format
%                      specifiers (i.e %d) to show the value of a gain. 
%                      There should be 1 specifier in user_display for
%                      every specifier in format. Don't forget the \n!
%       user_prompt - Message for prompting the user to enter gains
    format = '%d %d %d';
    user_display = 'Kp: %d Ki: %d Kd: %d\n';
    user_prompt = 'Enter Kp, Ki, and Kd as ints (blank to abort): ';
end