function min = golden_section()
e = 0.01;
a = 0;
b = 6;
it = 0;
f = 'x^3 + x^2 - 20*x';
y = inline(f);
while (b - a) > e
    x1 = a + 0.382 * (b - a);
    x2 = a + 0.618 * (b - a);
    if y(x1) > y(x2)
        a = x1;
    else
        b = x2;
    end
    it = it + 1;
end
display(it);
min = (a + b) / 2;
end