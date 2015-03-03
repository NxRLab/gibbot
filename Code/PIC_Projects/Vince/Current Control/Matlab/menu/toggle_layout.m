function menu = toggle_layout(menu,cmd)
% Changes the menu layout from hierarchical to flat or from flat
%   to hierarchical
%
%   menu = toggle_layout(menu,cmd)
%
%   Input Arguments:
%       see menu_entry.m
%
%   Output Arguments:
%       menu - the menu, converted to the appropriate form
    if menu.flat
        menu.tree_menu.options = menu.options;
        menu = menu.tree_menu;
        menu.flat = false;
    else
        menu = flatten_menu(root_menu(menu));
    end
end