function ref = step_ref(reflist)
%{
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
This function takes a list of positions and times and generates a trajectory
as a series of steps.

Example usage:  ref = makeStepRef([0, 0; 1.0, 90; 3.0, 45; 4.0, 0]);

This returns, in the array ref, a trajectory starting at time 0 seconds and 
0 degrees, then stepping to 90 degrees at time 1 second, then 45 degrees at 
3 seconds, then 0 at 4 seconds.  The array ref consists of len positions.  
Each represents the reference position, in degrees, spaced at time 1/f, where 
f is the frequency of the trajectory controller.

Note:  the first time must be 0.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%}

MOTOR_SERVO_RATE = 200;     % 200 Hz motion control loop

[numpos,numvars] = size(reflist);

if (numpos < 1) || (numvars ~= 2) 
  error('Input must be of form [t1,p1; ... tn,pn] for n >= 1.');
end



if reflist(1,1) ~= 0           % first time must be zero
    error('First time must be zero.')
end

%convert the list of times to the list of sample number
sample_list = reflist(:,1) * MOTOR_SERVO_RATE;

angle_list = reflist(:,2);

ref = zeros(1,max(sample_list));
last_sample = 0;
samp = 0;
for i=2:numpos
    if (sample_list(i,1)  <= sample_list(i-1,1))
        error('Times must be in ascending order.');
    end
    for samp = last_sample:(sample_list(i)-1)
        ref(samp+1) = angle_list(i-1);
    end
    last_sample = sample_list(i)-1;
end
ref(samp+1) = angle_list(end);

str = sprintf('The trajectory takes %5.3f seconds and consists of %d samples at %7.2f Hz.', ...
               reflist(end,1),length(ref),MOTOR_SERVO_RATE);
disp(str);
plot(ref);
ylabel('Motor angle (degrees)'); xlabel('Sample number');







  




  
  
  

