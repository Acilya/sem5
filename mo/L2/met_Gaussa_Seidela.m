v = -5:0.1:5;
epsilon = 0.01;
[x, y] = meshgrid(v);
f = '2*x.^2+y.^2+x.*y-6*x-5*y+8';
z = 2*x.^2+y.^2+x.*y-6*x-5*y+8;
F = inline(f);

figure(1)
contour(x,y,z,50)
hold on

x0 = -5;
y0 = -5;
xn = x0;
yn = y0;

while true
    xn_stale = xn;
    yn_stale = yn;
    a = -5;
    b = 5;
    while(abs(b-a) > epsilon)
        xm = (a+b) / 2;
        x1 = (a+xm) / 2;
        x2 = (b+xm) / 2;
        if F(x1,yn) < F(x2,yn)
            b = xm;
        elseif F(xm,yn) < F(x2,yn)
            a = x1;
            b = x2;
        else
            a = xm;
        end
    end
    xn = xm;
    line([xn_stale xn], [yn yn]);
    a = -5;
    b = 5;
    while(abs(b-a) > epsilon)
        xm = (a+b) / 2;
        x1 = (a+xm) / 2;
        x2 = (b+xm) / 2;
        if F(xn,x1) < F(xn,xm)
            b = xm;
        elseif F(xn,xm) < F(xn,x2)
            a = x1;
            b = x2;
        else
            a = xm;
        end
    end
    yn = xm;
    line([xn xn], [yn_stale yn]);
    if sqrt((xn - xn_stale).^2 + (yn - yn_stale).^2) < epsilon
        break;
    end
end
