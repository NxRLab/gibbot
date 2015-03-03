function options_save(fname,options) %#ok<INUSD>
%   Save options to a file
%
%   options_save(fname,options)
%
%   Input Arguments:
%       fname - the file name
%       options - the options values
    save(fname,'options');
end