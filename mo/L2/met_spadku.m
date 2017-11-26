function minimal = met_spadku()
F = inline('2.*x.^2 + y.^2 + x.*y - 6.*x - 5.*y + 8');
vx = -5:0.1:5;
vy = -5:0.1:5;
[x,y] = meshgrid(vx, vy);
z = 2.*x.^2 + y.^2 + x.*y - 6.*x - 5.*y + 8;
contour(x,y,z,50)
x0 = -5;
y0 = -5;
hold on;
plot(x0, y0, 'r*');
alpha = 0.5;
min_found = false;
while ~min_found
    val(1) = F(x0, y0);
    val(2) = F(x0+alpha, y0);
    val(3)= F(x0-alpha, y0);
    val(4)= F(x0, y0+alpha);
    val(5)= F(x0, y0-alpha);
    [min_val, index] = min(val);
    switch index
        case 1
            min_found = true;
            break;
        case 2
            x0 = x0 + alpha;
        case 3
            x0 = x0 - alpha;
        case 4
            y0 = y0 + alpha;
        case 5
            y0 = y0 - alpha;
    end
    plot(x0, y0, 'r*')
end
minimal(1) = x0;
minimal(2) = y0;
end