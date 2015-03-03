function menu = root_menu(menu)
%   Get the base menu from a series of submenu
%    
%   menu = root_menu(menu)
%
%   Input Arguments:
%       menu - the input menu
%   Output Arguments:
%       menu -  the top level menu
    while isfield(menu,'parent')
        menu = menu.parent;
    end
end