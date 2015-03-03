function [menu, status] = translate_menu(menu,cmd,parent_cmd,action,varargin)
%translate the new commands from the base menu into the old commands
    status = '';

    if nargout(action) == 1
        menu = action(menu,parent_cmd,varargin{:});
    elseif nargout(action) == 2
        [menu, status] = action(menu,parent_cmd,varargin{:});
    else
        action(menu,parent_cmd,varargin{:});
    end    
end