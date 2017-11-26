v = -5:0.1:5;
lambda = 0.2;
h = 0.01;
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
xn = [x0; y0];
yn = y0;

while true
    xn_stale = xn;
    if norm([(F(xn+h,yn)-F(xn, yn))/h; (F(xn,yn+h)-F(xn,yn))/h]) < epsilon
        break;
    else
        grad1 = (F(xn+h, yn) - F(xn, yn)) / h;
        grad2 = (F(xn, yn+h) - F(xn, yn)) / h;
        grad = [grad1; grad2];
        xn = xn - (grad / norm(grad)) * lambda;
    end
end
