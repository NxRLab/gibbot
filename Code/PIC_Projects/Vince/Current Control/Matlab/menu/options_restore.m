function menu = options_restore(menu,cmd)
% Restores options to there default state, except for the serial port
    rmenu = root_menu(menu);
     options_entries = rmenu.options_default;
     for i=1:length(options_entries)
            if isfield(options_entries{i},'default') %the options menu can have non option entries                                   
                rmenu.options.(options_entries{i}.name) = options_entries{i}.default;
                rmenu.options_default{i} = options_entries{i};
            end
     end
      menu = replace_root(menu,rmenu);
end