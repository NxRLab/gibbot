function menu = replace_root( menu ,rmenu)
% returns a menu whose root is set to rmenu
%
%   menu = replace_root(menu, rmenu)
%
%   Input Arguments:
%       menu - the menu to modify
%       rmenu - the root menu
%
%   Output Arguments
%       menu - the same menu as before except (root_menu(menu) = rmenu
    i = 1;
    while isfield(menu,'parent')
        menus{i} = menu; %#ok<AGROW>
        menu = menu.parent;
        i = i + 1;
    end
    % replace the top menu with the new menu
    menus{i} = rmenu;
    %build the menus up from the bottom
    for i = length(menus):-1:2
        menus{i-1}.parent = menus{i};
    end
    menu = menus{1};
end

