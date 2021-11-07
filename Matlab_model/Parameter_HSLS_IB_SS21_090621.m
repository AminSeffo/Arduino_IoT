clear all;

%% Parameter des Mikrocontrollers
f_PWM = 50e3;   % PWM Frequenz [Hz]
sample_t = 1/1000; % Arduino-Regelfrequenz
TA = sample_t ; % Abtastzeit [s]