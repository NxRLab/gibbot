function select_traj(menu,cmd,port) %#ok<INUSL>
% Guides the user through selecting a trajectory and loading them onto the
% pic

    function make_step(m,c) %#ok<INUSD>
            %make a step trajectory
            traj = input('Enter matrix [0, angle0; t1, angle1; ... ; tN, angleN] ');
            reference = int32(step_ref(traj));    
    end

    function make_cube(m,c) %#ok<INUSD>
        disp('Enter matrix [0, angle0; t1, angle1; ... ; tN, angleN], or ')
        traj = input('Enter matrix [0, angle0, velocity0; ...] ');
        reference = int32(cubic_ref(traj));
    end
    function make_traj(m,c,maker)
        % Guides the user through making a trajectory
        keep = false;
        while ~keep
            try            
                maker(m,c);
                s = input('Would you like to keep the trajectory [y/n]? ','s');
                keep = strcmpi(s,'Y');
            catch err
                disp(err.message)
            end
        end
    end
    menu_entries = {menu_entry('s','Step Trajectory',@make_traj,@make_step);
                    menu_entry('c','Cubic Trajectory',@make_traj,@make_cube);};
    tr_menu = make_menu('Define Trajectories', menu_entries);
    tr_menu.parent = menu;
    [menu, status] = run_menu(tr_menu,1); %#ok<ASGLU>
    if status == 'q'
       disp('Aborting trajectory creation...');
       write_pic(port,'%d\n',-1);
    else
        disp('Loading. Patience!')
        write_pic(port,'%d\n',length(reference));
        read_pic(port,'%s\n'); % read from the pic to check if the length is okay, will throw an error
                               % if the pic returns an error code
        for i=1:length(reference)
            write_pic(port,'%d\n',reference(i));
        end
    end
end