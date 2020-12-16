clc 
clear
close all

%% Sys Parameters 
mp = 0.294;
mc = 0.378;
g = 9.82;
L = 0.14;
d = 0.001;

s = -1;
%mc = M
%mp = m
%% Sys matrices 

A = [0, 0 ,1, 0; 
     0, -d1/mc, (g*mp)/mc, 0;
     0, 0, 0 ,1;
     0, -s*d1/(L*mc), -s*(g*(mc+mp))/(L*mc), 0];
 
B = [0; 1/mc; 0; s*1/(L*mc)];

C = [1, 0, 0, 0]; %q1 as input (position of the cart

D = zeros(size(C,1), size(B,2));

Vd = 0.1*eye(4);
Vn = 1;

BF = [B, Vd, 0*B];


sysC = ss(A, BF, C, [0,0,0,0,0,Vn])
sysFull = ss(A, BF, eye(4),zeros(4,size(BF,2)));

%% Kalman Filter 
Kf = (lqr(A',C', Vd,Vn))';

sysKf = ss(A-Kf*C, [B Kf], eye(4), 0*[B Kf]);
