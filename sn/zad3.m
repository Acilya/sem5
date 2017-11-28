load dane2.txt
in = dane2';

neurons = 5; % number of clusters = neurons
lr = 0.2; % learning rate
epochs = 150;

% setting weights of neurons
w = []; 
for i = 1:neurons
    w = [w; rand(1,2)];
end
w = w';
plot(w(1,:),w(2,:),'go') % neurons starting points
hold on

% learning the neurons
for x=1:epochs
    for k=1:length(in)
        d = []; % vector of distances of the sample from neurons
        for j = 1:neurons
            d = [d norm(in(:,k)-w(:,j))];
        end
        [winner, ind] = min(d); % the winner neuron (with minimal distance from the sample)
        w(:,ind) = w(:,ind) + lr * (in(:,k) - w(:,ind)); % new weights for the winner
    end
end

% learnt neurons
plot(in(1,:),in(2,:),'b+', w(1,:),w(2,:),'ro') 



