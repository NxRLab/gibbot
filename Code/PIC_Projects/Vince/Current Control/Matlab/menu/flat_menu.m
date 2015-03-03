function [menu, status] = flat_menu(menu,cmd,parent_cmd,action,varargin)
    status = '';

    old_subcmd = menu.sub_cmd;
    
    %simulate the submenu command

    menu.sub_cmd = [menu.sub_cmd,parent_cmd];
    real_sub = menu.(cmd).cmd;
    
    try
        if nargout(action) == 1
            menu = action(menu,real_sub,varargin{:});
        elseif nargout(action) == 2
            [menu, status] = action(menu,real_sub,varargin{:});
        else
            action(menu,real_sub,varargin{:});
        end
    catch err
        menu.sub_cmd = old_subcmd;
        rethrow(err);
    end
    menu.sub_cmd = old_subcmd;
end