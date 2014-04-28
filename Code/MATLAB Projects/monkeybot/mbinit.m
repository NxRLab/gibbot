function mbinit
mb = fullfile(cd('.'), 'mb');
mp = fullfile(cd('.'), 'mp');
md = fullfile(cd('.'), 'md');
mm = fullfile(cd('.'), 'mm');
addpath(mb, mp, md, mm, '-end');
% 
% matlabpool close force local;
% 
% if ~matlabpool('size')
%     matlabpool local 2;
% end
