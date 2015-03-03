function options = options_load(fname,menu,default)
% loads menu options from the given file and the options defaults
%   
%   options = options_load(fname, menu, default)
%
%   Input Arguments:
%       fname - the filename where the options are stored
%       menu - the menu the options are associated with
%       default - cell array of option entries the menu uses

    f = open(fname);
    f = f.options;
    for i = 1:length(default)
        name = default{i}.name;
        if isfield(f,name)
            options.(name)=[]; %#ok<AGROW>
            if strcmp(f.(name).str,'default')
               failed = true;
               while failed
                   try
                        m = default{i}.action(menu,default{i}.cmd,default{i}.args{:});
                        options.(name).str = m.options.(name).str;
                        options.(name).value = m.options.(name).value;
                        failed =false;
                   catch err
                       disp(err.message);
                   end
               end
            else
                options.(name).str = f.(name).str; %#ok<AGROW>
                options.(name).value = default{i}.parser(f.(name).str); %#ok<AGROW>
            end
        end
    end
end