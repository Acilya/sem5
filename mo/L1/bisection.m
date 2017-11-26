function min = bisection()
e = 0.01;
a = 0;
b = 6;
it = 0;
f = 'x^3 + x^2 - 20*x';
y = inline(f);
while (b - a) > e
    xm = (a + b) / 2;
    x1 = (a + xm) / 2;
    x2 = (xm + b) / 2;
    if y(x1) < y(xm)
        b = xm;
    elseif y(xm) < y(x2)
        a = x1;
        b = x2;
    else
        a = xm;
    end
    it = it + 1;
end
display(it);
min = (a + b) / 2;
end