clc;
close all;
clear all;
sim('zad3');
R = str2num(get_param('zad3/Subsystem', 'R')); 
rs = 0.2;
t = 0.01;
for i = 1:length(x)
    plot(0,0);
    daspect([1 1 1]);
    axis([-10 10 -10 10]);
    rectangle('Position', [-R, -R, 2*R, 2*R], 'Curvature', [1 1]);
    rectangle('Position', [x(i)-rs, y(i)-rs, 2*rs, 2*rs], 'Curvature', [1 1]);
    pause(t);
end
