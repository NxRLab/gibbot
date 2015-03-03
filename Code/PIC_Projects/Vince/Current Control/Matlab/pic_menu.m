% Displays the menu for interfacing with the pic

% create the prompt for entering serial port
port_prompt = sprintf('Enter the NU32 communication serial port (i.e ');
if isunix()
    port_prompt = [port_prompt, sprintf('/dev/ttyUSBx')];
elseif ismac()
    port_prompt = [port_prompt, sprintf('/dev/tty.usbserial-xxxxxxxx')];
elseif ispc()
    port_prompt = [port_prompt, sprintf('COMx')];
end
port_prompt = [port_prompt, sprintf(')')];

% create the options menu
options_entries = {
                    option_entry('p','port','Port name',port_prompt,'default',@(x) true,@port_open);
                    option_entry('u','show_u','Show control','Display control effort (Y/n)',...
                        'n',@(x)any(strcmpi(x,{'y','n'})));
                    option_entry('t','tune_samp','Tuning samples','Samples to take when tuning',...
                        '100',@(x) str2double(x) >= 0 && str2double(x) <= 1000,@str2double);
                    option_entry('h','hold_samp','Holding samples','Samples to take when holding',...
                        '400',@(x) str2double(x) >= 0,@str2num);
                    option_entry('x','xtra_samp','Tracking samples','Additional samples to take when tracking',...
                        '200',@(x)str2double(x) >= 0,@str2num);         
                    option_entry('g','goto_samp','Goto samples','Samples to take when going to an angle',...
                        '500',@(x)str2double(x) >= 0,@str2num);
                    option_entry('m','layout','Menu layout','Layout of the menu (must restart menu) (flat/tree)',...
                                'flat',@(x)any(strcmpi(x,{'flat','tree'})));
                    menu_entry('d','Restore defaults',@options_restore) 
                  };
options_menu = make_menu('Options Menu',options_entries);
clear port; %port is handled by the menu now
%make the submenu for current loop tuning.
current_entries={
                    pic_entry('k','View/Modify gains',@pic_get_set,{'%d %d', 'Kp: %d Ki: %d\n', 'Enter Kp and Ki, as integers (blank aborts): '});
                    pic_entry('r','Tune',@control_plot,'tune_samp');
                    pic_entry('b','Brake motors');
                    pic_entry('c','Coast motors');
                 };
current_menu = make_menu('Current Loop Menu',current_entries);


%make the submenu for motion control loop tuning
gain_args = cell(1,3);
[gain_args{:}] = gains();
motion_entries={
                pic_entry('k','View/Modify gains',@pic_get_set,gain_args);
                pic_entry('l','Load trajectory',@select_traj);
                pic_entry('x','Execute trajectory',@control_plot,'xtra_samp');
                pic_entry('h','Hold position',@control_plot,'hold_samp');
                pic_entry('g','Goto angle',@goto_exec,'goto_samp');
               };
clear gain_args;
           
motion_menu = make_menu('Motion Loop Menu',motion_entries);
% make the submenu for the diagnostics
diagnostic_entries={
                    pic_entry('e','Encoder count',@pic_get,{'%d','Encoder Count: %d\n'});
                    pic_entry('d','Motor angle',@pic_get,{'%d','Motor at %d degrees.\n'});
                    pic_entry('r','Reset angle');
                    pic_entry('a','Read ADC',@pic_get,{'%d','ADC Ticks: %d\n'});
                    pic_entry('i','Read current',@pic_get,{'%d','Current (mA): %d\n'});
                    pic_entry('p','Specify PWM',@pic_set,{'Enter PWM as a signed percentage in the range [-100,100]: ','%d',0});
                    pic_entry('x','Get state',@pic_state);
                    };
diagnostic_menu = make_menu('Diagnostics Menu',diagnostic_entries);
menu_entries={
                menu_entry('i','Current loop',@sub_menu,current_menu);
                menu_entry('m','Motion loop',@sub_menu,motion_menu);          
                menu_entry('d','Diagnostics',@sub_menu,diagnostic_menu);
                pic_entry('s','Save gains to flash');
                pic_entry('l','Load gains from flash');
                menu_entry('o','Options',@tree_menu,options_menu);
              };
menu = make_menu('Main Menu',menu_entries,options_entries,@(menu)(port_close()));
if exist('options.mat','file')
    f = open('options.mat');
    if(strcmpi(f.options.layout.str,'flat'))
        menu = flatten_menu(menu);
    end
else
    menu = flatten_menu(menu);
end
run_menu(menu);
