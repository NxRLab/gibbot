function entry = menu_entry(cmd,description,action,args)
% Makes an entry in a text based menu
%
%   entry = menu_entry(cmd,description)
%   entry = menu_entry(cmd,description,action)
%   entry = menu_entry(cmd,description,action,args)
%
%   Input Arguments:
%       cmd - character that the user must enter to activate the menu entry.  
%               Note that q is reserved for quitting, and o for options
%       description - string that is displayed in the menu that describes
%                     the action
%       action (optional) - function handle to the action that should be executed when
%                           the menu is activated. Defaults to null_action.
%                           Every function has the form
%                           [menu,other] = action(menu,cmd,...).   
%                                   menu - the parent menu
%                                   cmd - the executed command
%                                   ... - user provided arguments
%                                   menu - returns the menu.  This allows
%                                          menu actions to modify the menu
%                                          itself
%                                   other - any other outputs to return.
%                                   this will be the status returned by
%                                   run_menu if it exits based on the
%                                   command that caused the action
%                                   the function may also choose to return
%                                   no arguments, which is good practice
%                                   unless you intend to modify the menu
%       args (optional)   - cell array containing the arguments for the
%                           action. 
%                          

    nin = nargin;
    if nin < 3
        action = @null_action;
    end
    if nin < 4
        args = {};
    end
    if ~iscell(args)
        args = {args};
    end
    if strcmp(cmd,'q') || strcmp(cmd,' ') 
        error('make_entry:cmd cmd cannot be a ''q'', a '' ''');
    end
    
    if(length(cmd) > 1)
        error('make_entry:cmd cmd must be one character in length.');
    end
    entry.cmd = cmd;
    entry.description = description;
    entry.action = action;
    entry.args = args;
end