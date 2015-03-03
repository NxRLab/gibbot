function ref = cubic_ref(reflist)
% This function takes a list of "via point" times and positions and generates a 
% trajectory (positions as a function of time, in sample periods) using cubic 
% polynomials between via points.  
%
%   ref = cubic_ref(reflist)
%
%   Input Arguments:
%       reflist: points on the trajectory, cubic interpolation
%
%    Output Arguments:
%        Each element in ref represents the reference position,
%        in degrees, spaced at time 1/f, where f is the frequency of the trajectory controller.
%       
%       Example usage:  [ref,len] = makeCubicRef([0, 0; 1.0, 90; 1.5, -45; 2.5, 0]);
% 
%       This returns, in the array ref, a smooth trajectory starting at time 0 seconds 
%       and position (angle) 0 degrees, going to 90 degrees at time 1.0 seconds,
%       to -45 degrees at 1.5 seconds, and then to 0 degrees at 2.5 seconds. 
%   
%       An alternative usage is 
% 
%       ref = makeCubicRef([0, 0, 0; 1.0, 90, 200; 1.5, -45, 100; 2.5, 0, 0]);
% 
%       The entry before each semicolon is the desired angular velocity (in deg/s) at that
%       time.  This gives further control over the shape of the trajectory.
% 
%       Note:  the first time must be 0, and the first and last velocities should be 0.

MOTOR_SERVO_RATE = 200;     % 200 Hz motion control loop
dt = 1/MOTOR_SERVO_RATE;    % time per control cycle

[numpos,numvars] = size(reflist);

if (numpos < 2) || (numvars < 2) || (numvars > 3)
  error('Input must be of form [t1,p1; ... tn,pn] or [t1,p1,v1; ... tn,pn,vn] for n >= 2.');
end
reflist(1,1) = 0;           % first time must be zero
for i=1:numpos
  if (i>2)
    if (reflist(i,1) <= reflist(i-1,1))
      error('Times must be increasing in subsequent samples.');
    end
  end
end

timelist = reflist(:,1);
poslist = reflist(:,2);
if numvars == 3             % if via point speeds specified, use them 
  vellist = reflist(:,3);
 else                       % if via point speeds not specified, choose them
  vellist(1) = 0; vellist(numpos) = 0;
  if numpos >= 3
    for i=2:numpos-1
      vellist(i) = (poslist(i+1)-poslist(i-1))/(timelist(i+1)-timelist(i-1));
    end
  end
end

refCtr = 1;
for i=1:numpos-1            % go through each segment of trajectory
  timestart = timelist(i); timeend = timelist(i+1); 
  deltaT = timeend - timestart;
  posstart = poslist(i); posend = poslist(i+1);
  velstart = vellist(i); velend = vellist(i+1);
  a0 = posstart;            % calculate coeffs of traj pos = a0+a1*t+a2*t^2+a3*t^3
  a1 = velstart;
  a2 = (3*posend - 3*posstart - 2*velstart*deltaT - velend*deltaT)/(deltaT^2);
  a3 = (2*posstart + (velstart+velend)*deltaT - 2*posend)/(deltaT^3);
  while (refCtr-1)*dt < timelist(i+1)
    tseg = (refCtr-1)*dt - timelist(i);
    ref(refCtr) = a0 + a1*tseg + a2*tseg^2 + a3*tseg^3;  % add an element to ref array
    refCtr = refCtr + 1;
  end
end
len = refCtr-1;
str = sprintf('The trajectory takes %5.3f sec and consists of %d samples at %7.2f Hz.', ...
              timelist(numpos),len,MOTOR_SERVO_RATE);
disp(str);
plot(ref);
ylabel('Motor angle (degrees)'); xlabel('Sample number');







  




  
  
  

