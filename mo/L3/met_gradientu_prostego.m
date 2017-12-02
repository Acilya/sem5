v = -5:0.1:5;
lambda = 0.1;
h = 0.1;
epsilon = 0.2;
[x, y] = meshgrid(v);
f = '2*x.^2+y.^2+x.*y-6*x-5*y+8';
z = 2*x.^2+y.^2+x.*y-6*x-5*y+8;
F = inline(f);

figure(1)
contour(x,y,z,50)
hold on

x0 = -5;
y0 = -5;
xxn = [x0; y0];
xn = x0;
yn = y0;

while true
    grad1 = (F(xn+h, yn) - F(xn, yn)) / h;
    grad2 = (F(xn, yn+h) - F(xn, yn)) / h;
    Grad = [grad1; grad2];
    if norm(Grad) < epsilon
        break;
    else
        xxn = xxn - (Grad / norm(Grad)) * lambda;
        x0 = xn;
        y0 = yn;
        xn = xxn(1,1);
        yn = xxn(2,1);
    end
    plot([x0 xn], [y0 yn], '-')
    hold on;
end
[xn yn]