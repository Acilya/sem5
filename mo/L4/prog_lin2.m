f = [100 200];
A = [5 25; 0.5 0; 100 250; 10 10];
b = [500; 15; 7500; 400];

[x, fval] = linprog(-f, A, b); % miax f dla A*x <= b

disp(['Zysk: ', num2str(f*x)])
disp(['Ilosc krzesel: ', num2str(x(1))])
disp(['Ilosc stolow: ', num2str(x(2))])
disp(['Uzytego drewna: ', num2str(A(1,:)*x)])
disp(['Uzytej skory: ', num2str(A(2,:)*x)])
disp(['Uzytego kleju: ', num2str(A(3,:)*x)])
disp(['Naklad pracy: ', num2str(A(4,:)*x)])