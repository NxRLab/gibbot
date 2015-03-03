function menu = flatten_menu(menu)
% Converts a menu with submenus into a flat menu
%
%   menu = flatten_menu(menu)
%
%   Input Arguments:
%       menu - the menu to flatten
%   Output Arguments:
%       menu - return a flattened menu
%
    menu.tree_menu = menu; %save the hierarchical menu
    menu.flat = true;
    
    % find the submenus
    submenu_pos = cellfun(@(x)(isequal(x.action,@sub_menu)),menu.entries);   
    submenus = menu.entries(submenu_pos);
    
    % other entries
    othermenus = menu.entries(~submenu_pos);
    
    % the number of entries in the other column
    other = 1 + length(menu.options) + sum(submenu_pos == 0); 
    max_entries = other;
    for i=1:length(submenus)
        cm = submenus{i}.cmd;
        menu = rmfield(menu,cm);
        submenus{i} = submenus{i}.args{1};
        submenus{i}.sub_cmd = cm;
        max_entries = max(max_entries,length(submenus{i}.entries));
    end
    
    max_cols = 4;
    
    if length(submenus) < max_cols
      ncols = length(submenus);
    else
      ncols = max_cols;
    end
    
    %allocate the lines
    %menu.lines = cell(ncols,max_entries + 1);
    
    %how far each column has been filled
    filled = ones(1,ncols);
    
    % create the menu display
    letter = 'a';
    added = {};
    function updateMenu(i,title,ent,subcmd)
    %updates a column in the menu
    %   i - the column
    %   title - the title of the column
    %   ent - the entries in the column (cell array)
    %   subcmd - the parent menu command or empty if none
        menu.lines{filled(i),i} = title;
        filled(i) = filled(i) + 1;
        for j=1:length(ent)
           if ~isempty(subcmd) %if this is a submenu
                %make the action a flat menu adapter
                %the field has already been removed
                ent{j}.args = [{subcmd}, {ent{j}.action}, ent{j}.args];
                ent{j}.action = @flat_menu;                
           else
                %remove the original menu entry from the struct, 
                if ~ismember(ent{j}.cmd,added) 
                    %if we added the letter explicitly we don't want to
                    %remove it
                    menu = rmfield(menu,ent{j}.cmd);
                end
                if ~strcmp(ent{j}.cmd,'q')
                    ent{j}.args = [ent{j}.cmd,{ent{j}.action},ent{j}.args];
                    ent{j}.action = @translate_menu;
                end
           end
           %give the entry a new menu entry
           menu.(letter) = ent{j};
           added = [added,{letter}]; %#ok<AGROW>
           menu.lines{filled(i),i} = [letter,': ',ent{j}.description];
           filled(i) = filled(i) + 1;

           if letter(end) == 'z'
               letter = [letter,'a']; %#ok<AGROW>
           else
               letter(end) = letter(end) + 1;
           end
        end
    end
    curr_dex = 1; %the current menu index
    while curr_dex <= length(submenus)
        for i = 1:ncols
            updateMenu(i,submenus{curr_dex}.title,submenus{curr_dex}.entries,submenus{curr_dex}.sub_cmd);        
            curr_dex = curr_dex + 1;
            if curr_dex > length(submenus)
                break;
            end
        end
    end
    %
    filled = [filled,1];
    quit_entry.cmd = 'q';
    quit_entry.description = 'Quit';
    updateMenu(mod(i,max_cols)+1,'Other Menu',[othermenus;{quit_entry}],'');    
    
    
end