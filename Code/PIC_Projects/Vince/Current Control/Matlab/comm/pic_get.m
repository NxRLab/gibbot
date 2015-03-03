function [menu, outs] = pic_get(menu,cmd,port,sfmt,pfmt) %#ok<INUSL>
%   This menu action reads data from the pic and then displays it
%
%   pic_get(menu,cmd,port,sfmt,pfmt)
%
%   Input Arguments:
%       menu - The parent menu
%       cmd  - The command from the menu entry
%       sfmt - The fscanf format string for reading from the PIC
%       pfmt - The fprintf format string for displaying the results to the
%               user
%   Output Arguments:
%        outs - The values read from the pic
%   First, the full submenu command path will be issued to the PIC
%       so if this was launched from the user selecting 's', then 'c'
%       the pic will recieve
%       s
%       c
%       The PIC should then return data compatible with the sfmt format
%       string
    outs = read_pic(port,sfmt);
    fprintf(pfmt,outs);
end