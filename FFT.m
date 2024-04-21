Fs = 1000;            % Sampling frequency                    
T = 1/Fs;             % Sampling period       
L = 16;             % Length of signal
t = (0:L-1)*T;        % Time vector
S = 0.8 + 0.7*sin(2*pi*50*t) + sin(2*pi*120*t);
X = S;
Y = fft(X);
writematrix(X,'X_16.txt')
writematrix(Y,'Y_16.txt')