%iteration number
nriter = 10^7;
n = 1;
m = 2;
k = 2;

A = rand(m,k,nriter) + repmat(m*eye(m),1,1,nriter);
B = rand(k,n,nriter);
C = rand(m,n,nriter);

s = tic; %start
for i = 1:nriter
    C(:,:,i) = A(:,:,i) * B(:,:,i);
end

toc(s) %stop

% Elapsed time is 24.373877 seconds.
% I have tried the same amount of iterative time I used in xcode, but 
% MATLAB consumed so much elapsed time so I changed it to 10^7.