function [menu, status] = sub_menu(parent,cmd,menu)
% This menu action launches a submenu
%
%   sub_menu(parent,cmd,menu)
%
%   Input Arguments:
%       cmd - the command that launched this submenu
%       menu - the submenu that should be launched
    menu.sub_cmd = [parent.sub_cmd,cmd]; %indicate what parent menu command launched the submenu
    menu.parent = parent;
    [menu, status] = run_menu(menu); 
    menu = menu.parent;
end