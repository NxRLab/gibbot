data=load('data.txt');
sensed=data(:,1);
effort=data(:,2);
desired=data(:,3);

plot(0:size(data,1)-1,sensed,0:size(data,1)-1,effort,0:size(data,1)-1,desired);

legend('Sensed current','Control signal','Desired current');