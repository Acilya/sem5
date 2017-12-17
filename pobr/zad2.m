clc;
clf;
clear variable;
 
path = 'ATT\s';
 
K = 20; % liczba klas
L = 1; % liczba obrazkow z klasy
KL = K*L; % rozmiar obrazka

m = 16;
n = 14;
mn = m*n; % rozmiar zmniejszonego obrazka
num = 200; % liczba punktow
M = 112;
N = 92;
BIN = 32; %
X = fix((N-5)*rand(1,num))+1;
Y = fix((M-5)*rand(1,num))+1;
VR=zeros(num,1);
BWS=zeros(mn,KL);
BWH=zeros(BIN,KL);
BWR = zeros(num,KL); % baza wzorcow losowych punktow

%----------------- Rejestracja-----------------------
figure(1);
clf;
step=0;
for k=1:K
    for l=1:L
        step=step+1;
        adr = [path, num2str(k), '\', num2str(l), '.pgm']; % adres danego obrazka
        face = imread(adr);
        face = double(face)/255;
        [M,N,q] = size(face); % pobranie rozmiaru obrazka
        subplot(121); % obraz po lewej stronie ekranu
        imshow(face);
        title(['Face ', num2str(k), '\', num2str(l)]);
        xlabel(num2str([M,N,q]));
        ylabel('Baza ATT');
        hold on;
        plot(X,Y,'*g');
        hold off;
       
        % Random
        for j=1:num
            VR(j) = face(Y(j),X(j));
        end
        subplot(322);
        plot(VR);
        grid;
        title('Random');
        BWR(:,step)=VR';
       
        % Scale
        miniFace = imresize(face, [m n]);
        VS = miniFace(:);
        subplot(324);
        plot(VS);
        grid;
        title('Scale');
        BWS(:,step)=VS;
       
        % Histogram
        VH = imhist(face,BIN);
        subplot(326);
        bar(VH,'b');
        grid;
        title('Histogram');
        BWH(:,step)=VH;
        pause(.1);
    end;
end;

%----------Wyswietlenie wszystkich cech---
figure(2);clf;
subplot(311);
plot(BWR);grid;
title(['Random for ',num2str(num), '  wspo³rzednych']);
subplot(312);
plot(BWS);grid;
title('Scale');
subplot(313);
plot(BWH);grid;
title('Histogram');
return

%----------------- Rozpoznowanie---------------------
licznikS=0;
licznikR=0;
licznikH=0;
figure(3);
clf;
for k=1:K
    for l=1:L
        adr = [path, num2str(k), '\', num2str(l), '.pgm']; % adres danego obrazka
        face = imread(adr);
        face = double(face)/255;
        [M,N,q] = size(face); % pobranie rozmiaru obrazka
        subplot(121); % obraz po lewej stronie ekranu
        imshow(face);
        title(['Face ', num2str(k), '\', num2str(l)]);
        xlabel(num2str([M,N,q]));
        ylabel('Baza ATT');
        hold on;
        plot(X,Y,'*g');
        hold off;
       
        % Random
        for j=1:num
            VR(j) = face(Y(j),X(j));
        end
        subplot(322);
        plot(VR);
        grid;
        title('Random');
       
        % Scale
        miniFace = imresize(face, [m n]);
        VS = miniFace(:);
        subplot(324);
        plot(VS);
        grid;
        title('Scale');
       
        % Histogram
        VH = imhist(face,BIN);
        subplot(326);
        bar(VH,'b');
        grid;
        title('Histogram');
        pause(.1);
    end;
end;

%---------

