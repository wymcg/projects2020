% plot exercise 
t=linspace(0,10,1000);
y=1-exp(-t);

figure(1)
plot(t,y)
xlabel('Time [s]')
ylabel('y(t)')
title('IEEE better than ACM')
legend('y=1-exp(-t)')

% EE210 problem
clf;    % clear all figure
clear;  % clear the workspace
% define var
R=2;
C=16/3;
L=4;

%define P Q vectors, time vectors and input
P=[1/C R/(L*C)];
Q=[1 R/L 1/(L*C)];
t=-60:0.1:60;   % startpoint: interval : endpoint
f=7.*(t>0)-3.*(t<0);

% generate the output
v=lsim(P,Q,f,t); % Plot simulated time response of dynamic system to arbitrary inputs; simulated response data

figure(1)
plot(t,v);