close all
clc
clear
sim('model1')
m=3;
l=10;
t=0.01;
for i=1 : length(fi)
    x= -l*sin(fi(i));
    y= -l*cos(fi(i));
    plot(x,y,'b.','MarkerSize',5*m)
    hold on
    axis([-1.1*l 1.1*l -1.1*l 1.1*l])
    line([0 x],[0 y],'Color','r','LineWidth',2)
    hold off
    pause(t)
end