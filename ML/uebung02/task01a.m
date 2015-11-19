clear all;
close all;
rng('default'); % get same initial weights everytime

%init
noNeurons = 100;
state_t = ones(1,noNeurons);
state_prev = state_t;

%parameters
lambda=0.2;

a_deviation = 5;
rndMean = 0;
a = a_deviation.*randn(noNeurons,noNeurons) + rndMean; 

b_deviation = 1;
b = b_deviation.*randn(noNeurons,1) + rndMean;

x = 0;
loops = 100;

stateOverTime = ones(loops,1);
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
    stateOverTime(k) = state_t(21);
    state_prev = state_t;
    
    % display gray image of states
    stateSize = 20;
    for i=1:abs(sqrt(noNeurons))
        for j=1:abs(sqrt(noNeurons))
            A((1+(i-1)*stateSize):(i*stateSize),(1+(j-1)*stateSize):(j*stateSize)) = state_t((i-1)*abs(sqrt(noNeurons))+j);
        end
    end
    figure(1);
    imshow(A);
    title('Neuron Activities')

    
    y(k)=sum(state_t);
    k
end

aFig = figure(2);
set(aFig, 'Position', [0 500 500 300])
scatter(1:loops,stateOverTime);
title('Activity of Neuron 21');


bFig = figure(3);
set(bFig, 'Position', [0 0 500 300])
scatter(1:loops,y);
title('Output over time')

