clear all;
close all;
rng('default');

%init
noNeurons = 100;
state_t = ones(1,noNeurons);
state_prev = state_t;


%parameters
lambda=0.2;

a_deviation = 0.05;
rndMean = 0;
a = a_deviation.*randn(noNeurons,noNeurons) + rndMean; 

b_deviation = 1;
b = b_deviation.*randn(noNeurons,1) + rndMean;

w = ones(1,noNeurons);

x = 0;
loops = 200;

y_t = 10.*sin(100.*(1:loops));
y = ones(loops,1);

for k=1:loops
    %% t+1
    for i=1:noNeurons
        activity = 0;
        for j=1:noNeurons
            activity = activity + a(i,j)*state_prev(j);
        end
        state_t(i) = (1-lambda)*state_prev(i) + lambda*tanh(activity+b(i)*x);
    end
    state_prev = state_t;
    
    y(k)=sum(w.*state_t);
    normalize = norm(state_t)^2;
    dy = y_t(k)-y(k);
    for i = 1:noNeurons
        w(i) = 1*(dy*state_t(i))/normalize;
    end
end

hold on
%figure(1);
plot(1:loops,y,'r');

%figure(2);
plot(1:loops,y_t,'g');
hold off
