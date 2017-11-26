load dane2.txt
we = dane2';
net = newc(minmax(we), 5); 
w = net.IW{1} 
plot(we(1,:),we(2,:),'b+', w(:,1),w(:,2),'go') 
hold on 
net.trainParam.epochs = 50; 
net = train(net, we); 
w = net.IW{1} 
plot(we(1,:),we(2,:),'b+', w(:,1),w(:,2),'ro') 
hold off 
vec2ind( sim(net, [0.1; 0.1]) )