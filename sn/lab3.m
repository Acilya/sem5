close all;
clc;

% loading and random sorting of the data
we = load('dane_sin1a_i.txt');
wy = load('dane_sin1a_o.txt'); 
sort = randperm(length(wy));
we = we(sort,:)';
wy = wy(sort)';

% dividing the data to the learning and test data
in_learn = [];
in_test = [];
out_learn = [];
out_test = [];
procent = 30;
ratio = procent/100 * length(wy);
for i = 1:length(wy)
    if i <= ratio
        in_test = [in_test we(:,i)];
        out_test = [out_test wy(i)];
    else
        in_learn = [in_learn we(:,i)];
        out_learn = [out_learn wy(i)];
    end
end

% learning and testing the net
err = [];
spread = logspace(-2, 2, 100)';
for n = 1:length(spread)
    net = newgrnn(in_learn, out_learn, spread(n));
    y = sim(net, in_test);
    d = sum((out_test - y).^2);
    err = [err d];
end

% finding the best structure of the net
[min_d, spread_ind] = min(err);
spread(spread_ind)
figure;
hold on;
semilogx(spread, err); % error plot
