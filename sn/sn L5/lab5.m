% utworzenie wzorcow znakow (litery A-G, cyfry 1-3) na matrycach 5x5 
% -1 - piksel bialy, 1 - czarny
A = [-1 -1 1 -1 -1; -1 1 -1 1 -1; -1 1 1 1 -1; -1 1 -1 1 -1; -1 1 -1 1 -1];
B = [-1 1 1 1 -1; -1 1 -1 1 -1; -1 1 1 -1 -1; -1 1 -1 1 -1; -1 1 1 1 -1];
C = [-1 -1 1 1 -1; -1 1 -1 -1 -1; -1 1 -1 -1 -1; -1 1 -1 -1 -1; -1 -1 1 1 -1];
D = [-1 1 1 -1 -1; -1 1 -1 1 -1; -1 1 -1 1 -1; -1 1 -1 1 -1; -1 1 1 -1 -1];
E = [-1 1 1 1 -1; -1 1 -1 -1 -1; -1 1 1 -1 -1; -1 1 -1 -1 -1; -1 1 1 1 -1];
F = [-1 1 1 1 -1; -1 1 -1 -1 -1; -1 1 1 -1 -1; -1 1 -1 -1 -1; -1 1 -1 -1 -1];
G = [-1 -1 1 1 -1; -1 1 -1 -1 -1; -1 1 -1 1 1; -1 1 -1 -1 1; -1 1 1 1 -1];
m1 = [-1 -1 1 -1 -1; -1 1 1 -1 -1; -1 -1 1 -1 -1; -1 -1 1 -1 -1; -1 1 1 1 -1];
m2 = [-1 1 1 1 -1; -1 -1 -1 1 -1; -1 1 1 1 -1; -1 1 -1 -1 -1; -1 1 1 1 -1];
m3 = [-1 1 1 1 -1; -1 -1 -1 1 -1; -1 1 1 1 -1; -1 -1 -1 1 -1; -1 1 1 1 -1];
%subplot(3,4,1)
%imagesc(A)
%subplot(3,4,2)
%imagesc(B)
%subplot(3,4,3)
%imagesc(C)
%subplot(3,4,4)
%imagesc(D)
%subplot(3,4,5)
%imagesc(E)
%subplot(3,4,6)
%imagesc(F)
%subplot(3,4,7)
%imagesc(G)
%subplot(3,4,9)
%imagesc(m1)
%subplot(3,4,10)
%imagesc(m2)
%subplot(3,4,11)
%imagesc(m3)

% przeksztalcenie matryc na wektory kolumnowe
vA = reshape(A, 25, 1);
vB = reshape(B, 25, 1);
vC = reshape(C, 25, 1);
vD = reshape(D, 25, 1);
vE = reshape(E, 25, 1);
vF = reshape(F, 25, 1);
vG = reshape(G, 25, 1);
v1 = reshape(m1, 25, 1);
v2 = reshape(m2, 25, 1);
v3 = reshape(m3, 25, 1);

% utworzenie macierzy z wzorcami (1 kolumna - 1 wzorzec)
M = [vA vB vC vD vE vF vG v1 v2 v3];

net = newhop(M); % utworzenie sieci Hopfielda
w = net.LW{1,1} % wagi sieci
b = net.b{1,1}  % wagi wejsc progowych
% symulacja dzialania sieci dla wzorcow z macierzy M:
[y,pf,af] = sim(net, 10, {}, M) 
y' 
% dzialanie sieci dla wzorca a (znieksztalcone znaki):
a =[-1 1 1 1 -1; -1 -1 -1 1 -1; -1 1 1 1 -1; -1 1 -1 -1 -1; -1 1 1 1 -1];
a2 = reshape(a, 25, 1);
[y,pf,af] = sim(net, {1 20}, {}, {a2}); % ilosc iteracji - 20
y1 = cell2mat(y) 
a3 = reshape(y1(:,end),5,5);
subplot(1,2,1)
imagesc(a)
subplot(1,2,2)
imagesc(a3)