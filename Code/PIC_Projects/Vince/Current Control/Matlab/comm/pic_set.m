function pic_set(menu,cmd,port,prmpt,fmt,defaults) %#ok<INUSL>
%   This menu action prompts the user to enter values and sends the entered values to the
%   pic
%
%   pic_set(menu,cmd,port,prmpt,fmt)
%   pic_set(menu,cmd,port)
%   Input Arguments:
%       menu - the parent menu
%       cmd - the command from the menu entry
%       prmpt - The text with which to prompt the user
%       fmt - The format string for the user input, compatible with fscanf,
%       defaults - The default values to write if the user enters a blank
%                  line
%
%   The user will be prompted, and then will enter values.  These values
%   will be sent to the pic, in the format:
%   menu_path
%   printf(fmt,entered_values).
%
%   For Example, assume that this command comes from a submenu.
%   so the user had to press s, then c to get here
%   if the format string is "%d %f", and the user enters
%   10 0.2
%   The PIC will recieve
%   s
%   c
%   10 0.2
    redo = true;
    while redo
        inp = input(prmpt,'s');
        [outs, cnt,err] = sscanf(inp,fmt); 
        if ~isempty(err)
            disp('Input is in the wrong format. Try again.');        
        elseif sum(fmt == '%') ~= cnt && ~isempty(outs);
            disp('Not enough parameters. Try again.');
        else
            redo = false;
        end
    end
    if isempty(outs)
        outs = defaults;
    end
    write_pic(port,[fmt,'\n'],outs);
end