close all
clc
clear
sim('zad3')
m = str2num(get_param('zad3/Subsystem', 'm')); 
l = str2num(get_param('zad3/Subsystem', 'l'));
l_max = l + max(r);
t=0.01;
for i=1 : length(r)
    la = l + r(i);
    x= -la*sin(th(i));
    y= -la*cos(th(i));
    plot(x,y,'b.','MarkerSize',5*m)
    hold on
    axis([-1.1*l_max 1.1*l_max -1.1*l_max 1.1*l_max])
    %line([0 x],[0 y],'Color','r','LineWidth',2)
    args = [10 1 0.2];
    [xs,ys] = spring(0,0,x,y,10,1, 0.2); 
    plot(xs,ys,'LineWidth',2)
    hold off
    pause(t)
end