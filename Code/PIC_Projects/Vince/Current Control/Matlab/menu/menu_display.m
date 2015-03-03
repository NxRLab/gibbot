function menu_display(menu)
%   Displays the menu
%
%   Input Arguments:
%       menu - the menu to display
    fprintf('\n%s:\n',menu.title);    
    if menu.flat
        for i = 1:size(menu.lines,1)
            for j = 1:size(menu.lines,2)
                fprintf('%-25s',menu.lines{i,j});
            end
            fprintf('\n');
        end
    else
        for i = 1:length(menu.entries)   %print out the menu entries
            disp([' ',menu.entries{i}.cmd,': ',menu.entries{i}.description]);
        end
        if ~isfield(menu,'parent')
            disp(' q: Quit');
        else
            disp(' q: Back');
        end
    end
    fprintf('\n');
end