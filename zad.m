clc;
clf;
clear variable;

path = 'ATT\s'; % http://www.cl.cam.ac.uk/Research/DTG/attarchive:pub/data/att_faces.zip 

BWS = []; % baza wzorcow skal
BWH = []; % baza wzorcow histogramow
K = 20; % liczba klas
L = 1; % liczba obrazkow z klasy
m = 16; 
n = 14;
mn = m*n; % rozmiar zmniejszonego obrazka
num = 200; % liczba punktow
M = 112; 
N = 92;
KL = K*L; % rozmiar obrazka
BIN = 32; %
BWR = zeros(num,K); % baza wzorcow losowych punktow
X = fix((N-5)*rand(1,num))+1;
Y = fix((M-5)*rand(1,num))+1;

% Rejestracja
figure(1);
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
    end
end