function entry = pic_entry(cmd,description,action,args)
% Makes a menu entry that communicates with the menu running on the pic
%   The menu should have a port option
%
%   entry = pic_entry(cmd,description)
%   entry = pic_entry(cmd,description,action)
%   entry = pic_entry(cmd,description,action,args)
%
%   Input Arguments:
%       cmd - the string that causes the command to be executed
%       description - a description of the command
%       action - handle to the function to execute
%               action(menu,cmd,port,args) (note the addition of the port
%               argument, which is always expected to be present but is
%               unnneeded for a regular menu entry)
%       args - additional arguments to the action
%   Output Arguments:
%       entry - a menu entry that communicates with the pic
%
%   This makes a menu entry, but the result of this menu being selected
%       is sent to the PIC prior to the action being performed.
%       The menu acknowledgment from the PIC is read after the action is
%       performed
  nin = nargin;
  if nin < 3
      action = @(menu,cmd,port) null_action(menu,cmd);
  end
  
  if nin < 4
      args = {};
  end
  
   %wrap the action with code to communicate with the pic
   function wrapper(menu,cmd,varargin)
       rmenu = root_menu(menu);
       port = rmenu.options.port.value;
       for i=1:length(menu.sub_cmd)
            write_pic(port,'%s\n',menu.sub_cmd(i));
       end
       write_pic(port,'%s\n',cmd);
       action(menu,cmd,port,varargin{:});
       read_pic(port,'%s');
   end
    entry = menu_entry(cmd,description,@wrapper,args);
end