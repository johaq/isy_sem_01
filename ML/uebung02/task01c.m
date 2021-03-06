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
lambda=0.2;
epsilon = 1; % learning rate

a_deviation = 0.1;
rndMean = 0;
a = a_deviation.*randn(noNeurons,noNeurons) + rndMean; 

b_deviation = 1;
b = b_deviation.*randn(noNeurons,1) + rndMean;

w = ones(1,noNeurons);

x = 0; % inputs
loops = 100;

amplitude = 100;
frequency = 0.1;
samplingrate = 1;
y_t = amplitude.*sin(frequency.*(0:samplingrate:loops*samplingrate-samplingrate)); %target function
y = ones(loops,1); %outputs

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
    
    %online adaption
    normalize = norm(state_t)^2;
    dy = y_t(k)-y(k);
    for i = 1:noNeurons
        w(i) = w(i) + epsilon*(dy*state_t(i))/normalize;
    end
end

hold on
plot(0:samplingrate:loops*samplingrate-samplingrate,y,'r');

plot(0:samplingrate:loops*samplingrate-samplingrate,y_t,'g');
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
plot(loops*samplingrate-samplingrate:samplingrate:2*(loops*samplingrate-samplingrate),y,'r');
