close all;
clc;

% loading and random sorting of the data
we = load('dane_sin1a_i.txt');
wy = load('dane_sin1a_o.txt'); 
mix = randperm(length(wy));
we = we(mix,:)';
wy = wy(mix)';

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
results = [];
all_err = [];
for i = 1:100
    err = [];
    spread = logspace(-2, 2, 100)';
    for n = 1:length(spread)
        net = newgrnn(in_learn, out_learn, spread(n));
        y = sim(net, in_test);
        d = sum((out_test - y).^2);
        err = [err d];
    end
    % finding the best spread
    [min_d, spread_ind] = min(err);
    results = [results spread(spread_ind)];
    all_err = [all_err; err];
end

% finding the best mean spread and drawing a plot
mean(results)
mean_err = [];
for i = 1:size(all_err,2)
    mean_err = [mean_err mean(all_err(:,i))];
end
figure; % hold on is off because then the axis' scale is not logarythmic
semilogx(spread, mean_err); % error plot
