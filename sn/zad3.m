load dane3d1.txt
we = dane3d1';
neurons = 4;
learning_rate = 0.01;
w = rand(neurons,1);
d = [];
for i = 1:neurons:
    d = [d norm(x-w(i)]
end
min(d)