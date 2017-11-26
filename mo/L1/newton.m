function min = newton()
e = 0.001;
h = 0.005;
a = 0;
b = 6;
it = 0;
f = 'x^3 + x^2 - 20*x';
y = inline(f);
xn = (b - a) / 2;
der1 = (y(xn+h) - y(xn)) / h;
der2 = (y(xn+2*h) - 2*y(xn+h) + y(xn)) / h^2;
xn1 = xn - der1 / der2;
while abs(xn1 - xn) > e
    xn = xn1;
    der1 = (y(xn+h) - y(xn)) / h;
    der2 = (y(xn+2*h) - 2*y(xn+h) + y(xn)) / h^2;
    xn1 = xn - der1 / der2;
    it = it + 1;
end
display(it);
min = xn1;
end