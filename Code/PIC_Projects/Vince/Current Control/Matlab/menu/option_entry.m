function entry = option_entry(cmd,name,description,prompt,default,validator,parser)
%   Makes an entry that allows the user to set options
%   These options persist in the menu and can be accessed by any entry
%
%   entry = option_entry(cmd,name,description,default)
%   entry = option_entry(cmd,name,description,default,validator)
%
%   Input Arguments:
%       cmd - The sequence used to change the option
%       name - The name of the option
%       description - a short description
%       prompt - A prompt to display to the user for data entry
%       default - default value for the option, as a value. If specified as
%                 'default', the user will be prompted as if they had
%                  selected the option from a menu
%       validator - ret = validator(x) x is the value entered by the user
%                   return false if the value is unacceptable
%       parser - ret = parser(str) 
%                       converts the string representation of the option
%                       as entered by the user into its value (optional)
%
%   Output Arguments:
%       entry - a menu entry for setting the option. Additional fields:
%               entry.name - the name of the option
%               entry.default - the default value
    nin = nargin;
    if nin < 6
        validator = @(x) true;
    end
    if nin < 7
        parser = @(x) x;    
    end

    
    function menu = option_action(menu,cmd) %#ok<INUSD>
        %this is the action when an option is executed.
        % we will replace the options in the root menu
        rmenu = root_menu(menu);

        disp(['Option ',name,' = ', rmenu.options.(name).str]);
        entered = input([prompt,': '],'s');
        if ~validator(entered)
            disp('Invalid Input. Option not changed.');
        elseif ~isempty(entered)
            rmenu.options.(name).str = entered;
            rmenu.options.(name).value = parser(entered);
        end
        menu = replace_root(menu,rmenu);
    end
    entry = menu_entry(cmd,description,@option_action);    
    entry.default.str = default;    
    entry.name = name;
    entry.parser = parser;
end