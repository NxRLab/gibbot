function [I,B] = spmodel2(filename,dt,r1,m1)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

%initialize variables

g = 9.81;

%import data from text file 
A = importdata(filename); 
B = A - A(1)*ones(length(A),1);
%convert to rad/s 
T = 2*pi/(4*1800)*B;  

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

for j = 1:(length(T)) 
    t(j) = dt*(j-1);
end

%using least squares method, find estimate for I and B

dl = [Tdd,Td];
dr = -m1*g*r1*cos(T)-m1*r1^2*Tdd;
A = dl'*dl;
B = dl'*dr;
X = A\B;

I = X(1);
B = X(2);

[te,x]=ode45(@(te,x) F(te,x,r1,m1,g,I,B),t,[0,0]);
xdd = (-r1*m1*g*cos(x(:,1)) - B*x(:,2))/(I+m1*r1^2);
x = x(:,1);

R = Tdd - xdd;
subplot(3,1,1);
plot(t,T,t,Td,t,Tdd)
title('Encoder Data')
xlabel('Time (s)')
ylabel('Position, Velocity, or Acceleration')

subplot(3,1,2);
plot(t,Tdd,te,xdd,'o')
title('Model vs. Data')
xlabel('Time (s)')
ylabel('rad/2^2')

subplot(3,1,3);
plot(t,R)
title('Residuals')
xlabel('Time (s)')
ylabel('Residual')
end


