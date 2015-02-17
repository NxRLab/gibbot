function [B,I] = spmodel(filename,dt,r1,m1)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

%initialize variables

g = 9.81;

%import data from text file 
A = importdata(filename); 

%convert to rad/s 
T = 2*pi/(1800);  

%calculate theta dot using forward difference for first term, central for
%middle terms, and back for last term. 
Td(1) = (T(2)-T(1))/dt ;
for i = 2:(length(T)-1) 
    Td(i) = (T(i+1)-T(i-1))/(2*dt);
end
Td(length(T)) = (T(length(T))-T(length(T)-1))/dt; 
Td = Td';

%calculate theta doulble dot using forward difference for first term,
%central for middle terms, and back for last term.
Tdd(1) = (Td(2)-Td(1))/dt ;
for i = 2:(length(T)-1) 
    Tdd(i) = (Td(i+1)-Td(i-1))/(2*dt);
end
Tdd(length(T)) = (Td(length(T))-Td(length(T)-1))/dt; 
Tdd = Tdd';

%find total time
t(1) = 0;
for j = 2:(length(T)) 
    t(j) = dt*(j-1);
end

%preform least squares curve fit to determine Moment of inertia about the
%center of mass (Icm) and rotational damping(B) of the link
predicted = @(B,I,x,y) (-r1*m1*g*sin(x) + B*y)/(I+m1*r1^2);
model = fit([T, Td],Tdd,predicted, ...
    'StartPoint', [0, 0], ...
    'Lower', [-Inf, -Inf], ...
    'Robust', 'LAR' )
J = coeffvalues(model);
B = J(1);
I = J(2);

%Use least sqaure curve fit to estimate measured parameters and compare to
%measrued values.Return percent error.  
%r1:
%predicted = @(B,I,r,x,y) (-r*m1*g*sin(x) + B*y)/(I+m1*r^2);
% model = fit([T, Td],Tdd,predicted, ...
%     'StartPoint', [0, 0, 0], ...
%     'Lower', [0, 0, 0], ...
%     'Robust', 'LAR' )
% K = coeffvalues(model);
% r = K(3);
% r1perdiff = abs(r1 - r)/r*100;  
% 
% %m1: 
% predicted = @(B,I,m,x,y) (-r*m*g*sin(x) + B*y)/(I+m*r^2);
% model = fit([T, Td],Tdd,predicted, ...
%     'StartPoint', [0, 0, 0], ...
%     'Lower', [0, 0, 0], ...
%     'Robust', 'LAR' )
% L = coeffvalues(model);
% m = L(3);
% m1perdiff = abs(m1 - m)/m*100;  

%plot data from encoder: visually confirm the resolution given by dt is
%adequate. Also compare model to actual data.
Md = (-r1*m1*g*sin(T) + B*Td)/(I+m1*r1^2);

figure

subplot(2,1,1);
plot(t,T,t,Td,t,Tdd)
title('Encoder Data')
xlabel('Time (s)')
ylabel('Position, Velocity, or Acceleration')

subplot(2,1,2);
plot(t,Md,t,Tdd)
title('Model vs. Data')
xlabel('Time (s)')
ylabel('rad/2^2')
end

