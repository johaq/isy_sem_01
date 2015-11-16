clear all;
close all;
rng('default');

%init
noNeurons = 100;
state_t = ones(1,noNeurons);
state_prev = state_t;

%parameters
lambda=0.2;

a_deviation = 0.1;
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
    for i=1:abs(sqrt(noNeurons))
        for j=1:abs(sqrt(noNeurons))
            A((1+(i-1)*100):(i*100),(1+(j-1)*100):(j*100)) = state_t((i-1)*abs(sqrt(noNeurons))+j);
        end
    end
    figure(1);
    title('Neuron Activities')
    imshow(A);
    
    y(k)=sum(state_t);
    k
end

figure(2);
title('Activity of Neuron 21')
scatter(1:loops,stateOverTime);

figure(3);
title('Output over time')
scatter(1:loops,y);
