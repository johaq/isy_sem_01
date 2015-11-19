%% init
clear all;
close all;
rng('default'); % get same initial weights everytime
lFig = figure(1);
set(lFig, 'Position', [0 500 1400 250])

%init
noNeurons = 100;
state_t = ones(1,noNeurons);
state_prev = state_t;


%parameters
lambda = 0.2;
epsilon = 1;

a_deviation = 0.1;
rndMean = 0;
a = a_deviation.*randn(noNeurons,noNeurons) + rndMean; 

b_deviation = 1;
b = b_deviation.*randn(noNeurons,1) + rndMean;

w = ones(1,noNeurons);

x = 0;

loops = 100;
sample = 1:0.5:loops/2+0.5;
period = 5;
amplitude = 100;
h = floor((sample/period)+1/2);

y_t = arrayfun(@(t) (4*amplitude/period)*(abs(mod(t,period)-(period/2))-(period/4)),sample);
y = ones(loops,1);

%% learning target
for k=1:loops
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
        w(i) = w(i) + epsilon*(dy*state_t(i))/normalize;
    end
end

hold on
plot(1:0.5:loops/2+0.5,y,'r');

plot(sample,y_t,'g');
hold off

%% predict

for k=1:loops
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
        w(i) = w(i) + epsilon*(dy*state_t(i))/normalize;
    end
end

aFig = figure(2);
set(aFig, 'Position', [0 0 1400 250])
plot(loops/2+0.5:0.5:loops,y,'r');
