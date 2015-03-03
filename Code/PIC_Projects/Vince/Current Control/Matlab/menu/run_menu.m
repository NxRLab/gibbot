function [menu, status] = run_menu(menu,times)
% This displays the menu to the user
%
%   [menu, status] = run_menu(menu)
%   [menu, status] = run_menu(menu,times)
%
%   Input Arguments:
%       menu - a menu created with make_menu
%       times - (optional) the number of times to cycle through the menu before
%               quitting.  If blank, defaults to infinite
%
%   Output Arguments:
%       status - the status of the last command, or blank if its menu
%                 action does not return a value
    nin = nargin;
    if nin < 2
        times = inf;
    end

    status = [];
    has_quit = false;

    if ~isfield(menu,'parent')
        if ~exist('options.mat','file') % if options are not saved, save the defaults
            options_save('options.mat',menu.options);
        end
        menu.options = options_load('options.mat',menu,menu.options_default);
    end
    while ~has_quit && times > 0
        times = times - 1;
        try
            menu_display(menu);
         
            selection = input('What Do You Want? ','s'); % prompt the user
            disp('------------------------------------------');
            if menu.flat
                if isfield(menu,selection)
                    has_quit = menu.(selection).cmd == 'q';
                end
            else
                has_quit = selection == 'q';
            end
            if has_quit
                disp('Goodbye!');
                status = 'q';
            elseif isfield(menu,selection)
                action = menu.(selection).action;
                nout = nargout(action);
                if nout == 1
                    menu = action(menu,selection,menu.(selection).args{:});
                elseif nout > 1
                    status = cell(nout-1,1);
                    [menu, status{:}] = action(menu,selection,menu.(selection).args{:});
                else
                    action(menu,selection,menu.(selection).args{:});
                    status = [];              
                end
                %unbox the status cells
                if iscell(status) && all(size(status) == [1,1])
                    status = status{1};
                end
            else
                disp(['I Don''t Know How To ''',selection,'''. Please Try Again.']);
            end
            disp('------------------------------------------');
        catch err
            fprintf('Error %s\n',err.message);
        end
    end
    if ~isfield(menu,'parent')
        options_save('options.mat',menu.options);
    end
    menu.onquit(menu);
end