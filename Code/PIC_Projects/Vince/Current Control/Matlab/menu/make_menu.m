function menu = make_menu(title,entries,options_entries,onquit)
% Makes a text based menu
%
%   menu = make_menu(title,entries)
%   menu = make_menu(title,entries,options_entries)
%
%   Input Arguments:
%       title   - the name of the menu
%       entries - cell array of menu_entries.  These are made by calling
%                 make_entry
%       options_entries (optional) - cell array of entries for options, made with
%                                   make_option
%       onquit (optional) - function to be called on quit
%                              onquit(menu.options)
%   Output Arguments:
%       menu - A text based menu that can be executed by running run_menu()
%       menu has the following fields
%       menu.(cmd) - one entry for every command
%       menu.entries - the original entries cell array
%       menu.sub_cmd - used for storing parent menus.  
%       menu.title - the name of the menu
   nin = nargin;
   if nin < 3
       options_entries = {};
   end
   if nin < 4
       onquit = @(x)x;
   end
   
   
    used_entries = cell(1,length(entries));
    for i=1:length(entries)
        used_entries{i} = 'q';
    end
    menu.entries = entries;
    
    %set the options menu
    if ~isempty(options_entries)
        %set the default options
        for i=1:length(options_entries)
            if isfield(options_entries{i},'default') %the options menu can have non option entries                                   
                menu.options.(options_entries{i}.name) = options_entries{i}.default;
                menu.options_default{i} = options_entries{i};
            end
        end
    else
        menu.options = {};
    end
    for i=1:length(entries)
        cmd = entries{i}.cmd;
        if ismember(cmd,used_entries)
            error(['make_menu:dup duplicate menu entry value ''',cmd,'''']);
        end
        used_entries{i} = cmd;
        menu.(cmd) = entries{i};
    end   
    menu.sub_cmd = '';
    menu.title = title;
    menu.onquit = onquit;
    menu.flat = false;
end