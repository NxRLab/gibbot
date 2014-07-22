function varargout = acrobot_position(varargin)
% ACROBOT_POSITION MATLAB code for acrobot_position.fig
%      ACROBOT_POSITION, by itself, creates a new ACROBOT_POSITION or raises the existing
%      singleton*.
%
%      H = ACROBOT_POSITION returns the handle to a new ACROBOT_POSITION or the handle to
%      the existing singleton*.
%
%      ACROBOT_POSITION('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in ACROBOT_POSITION.M with the given input arguments.
%
%      ACROBOT_POSITION('Property','Value',...) creates a new ACROBOT_POSITION or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before acrobot_position_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to acrobot_position_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help acrobot_position

% Last Modified by GUIDE v2.5 22-Jul-2014 12:37:47

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @acrobot_position_OpeningFcn, ...
                   'gui_OutputFcn',  @acrobot_position_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before acrobot_position is made visible.
function acrobot_position_OpeningFcn(hObject, ~, ~, varargin)
handles = guidata(hObject);

delete(instrfindall); %deletes any currently attached instruments
obj=serial('/dev/tty.usbmodem411'); %creates a new serial object 
fopen(obj); %opens the serial object, allowing us to write and read commands
set(obj, 'Terminator',{'LF',''}); %removes the newline cahracter when writing commands
fprintf(obj,'q'); %resets the counts to zero
handles.obj=obj; %saves the serial object to the handles structure so it can
                 % be used in other functions
                 
xlim(handles.axes1,[0,1000]);
ylim(handles.axes1,[0,1000]);
axis off
theta=0;

line([500,500],[1000,500],'Color','k','LineWidth',10)
newx=500+500*sind(theta);
newy=500-500*cosd(theta);
line([500,newx],[500,newy],'Color','b','LineWidth',10)


% Update handles structure
handles.output = hObject;
guidata(hObject, handles);


% --- Outputs from this function are returned to the command line.
function varargout = acrobot_position_OutputFcn(~, ~, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


function update_button_Callback(hObject, ~, ~)
cla 
cpr=117000; %the counts per rotation of our motor/gearhead combo
handles=guidata(hObject);
obj=handles.obj;
fprintf(obj,'l'); %sends command to read QEI value over USB
count=str2num(fscanf(obj)); %reads data from serial port to get encoder count
theta=count*(360/cpr)-(32768/cpr)*360; %converts the count to degrees and offsets 
                                       %to account for resetting to the middle
                                       %of the count
angle=sprintf('%.2f%c',theta,176);                                
set(handles.angle_display_text,'string',angle);
set(handles.count_display_text,'string',count);

%draw lines
line([500,500],[1000,500],'Color','k','LineWidth',10)
newx=500+500*sind(theta);
newy=500-500*cosd(theta);
line([500,newx],[500,newy],'Color','b','LineWidth',10)

guidata(hObject,handles); 


% --- Executes on button press in update_live_checkbox.
function update_live_checkbox_Callback(hObject, eventdata, handles)
while get(hObject,'Value')==1
    update_button_Callback(hObject,0,0)
    pause(0.05)
end
