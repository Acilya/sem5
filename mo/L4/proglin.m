f = [2 1.5 3]; % ceny (kanapki/pierogi/slodycze)
A = [4 6 15; 2 2 0; 5 3 4; 7 3 12]; % zawartosci skladnikow (bialko/tluszcz/wit/weglowodany)
b = [250; 60; 100; 220]; % min ilosci skladnikow
Aeq = [];
beq = [];
lb = [0 0 0];
ub = [];

[x, fval] = linprog(f, -A, -b, Aeq, beq, lb, ub); % szukamy min f dla A*x >= b (a nie <=)
x = ceil(x); % x - ilosci produktow

disp(['Kanapki: ', num2str(x(1))])
disp(['Pierogi: ', num2str(x(2))])
disp(['Slodycze: ', num2str(x(3))])
disp(['Cena: ', num2str(f*x)])
disp(['Ilosc bialka: ', num2str(A(1,:)*x)])
disp(['Ilosc tluszczu: ', num2str(A(2,:)*x)])
disp(['Ilosc witamin: ', num2str(A(3,:)*x)])
disp(['Ilosc weglowodanow: ', num2str(A(4,:)*x)])