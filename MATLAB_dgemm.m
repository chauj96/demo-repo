% number of iteration
nriter = 10^7;
n = 2;
m = 2;
k = 2;
alpha = 4;
beta = 2;

A = rand(n,n,nriter);
B = rand(n,n,nriter);
C = rand(n,n,nriter);


s = tic; %start
for i = 1:nriter
    C(:,:,i) = alpha * A(:,:,i) * B(:,:,i) + beta * C(:,:,i);
end
toc(s) %stop

% the average running time is 28.005 seconds.