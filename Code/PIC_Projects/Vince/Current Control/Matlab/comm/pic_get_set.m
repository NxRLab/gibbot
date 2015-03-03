function pic_get_set(menu,cmd,port,sfmt,pfmt,prompt) 
%   This menu action reads data from the pic, displays it, then
%   prompts the user to enter new values
%
%   pic_get(menu,cmd,port,sfmt,pfmt)
%
%   Input Arguments:
%       menu - the parent menu
%       cmd - the command from the menu entry
%       sfmt - the fscanf format string for reading/writing to/from the PIC
%       prompt - The user prompt displayed to query the new parameters
%       pfmt - The fprintf format string for displaying the results to the
%               user
%
%   First, the full submenu command path will be issued to the PIC
%       so if this was launched from the user selecting 's', then 'c'
%       the pic will recieve
%       s
%       c
%       The PIC should then return data compatible with the sfmt format
%       string. Finally, The PIC should expect data compatible with the
%       sfmt string
    [m, orig] = pic_get(menu,cmd,port,sfmt,pfmt); %#ok<ASGLU> % get and display the original values
    pic_set(menu,cmd,port,prompt,sfmt,orig);  % prompt for new values       
end