clc;
clear;
clear all;

sim('lab4');

t=0.01;

for i=1:length(x)
    plot(x(i), y(i), 'b.', 'MarkerSize', 50);
    axis([-4 4 -4 4])
    line([0 x(i)],[0 y(i)],'Color','r','LineWidth',2);
    pause(t);
end