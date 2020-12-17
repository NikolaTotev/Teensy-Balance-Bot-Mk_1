clc 
clear
close all

%% Sys Parameters 
mp = 0.294;
mc = 0.378;
g = 9.82;
L = 0.14;
d1 = 0.001;
d2 = 0.001;
s = -1;
%mc = M
%mp = m
%% Sys matrices 
A = [0, 0 ,1, 0; 
      0, 0, 0 ,1;
      0, (g*mp)/mc, -d1/mc, -d2/(L*mc);
      0, (g*(mc+mp))/(L*mc), -d1/(L*mc), (-d2*(mc+mp))/(L*L*mc*mp)];
 
B = [0; 0; 1/mc;1/(L*mc)];



%% Output
C = [1 0 0 0]; %q1 as input (position of the cart
D = 0

%% Sys build
sys = ss(A, B, C, D)
eig(A) 

%% Sys analysis 

pole(sys) %Either of the two commands find the poles of the system. We do this to check if the system is stable or not
ControlabilityMatrix = ctrb(sys) 
ObvservabilityMatrix = obsv(sys)

rank(ControlabilityMatrix) %Rank must be 4 otherwise the system is not controlable
rank(ObvservabilityMatrix) %Rank must be 4 otherwise the system is not observable 

rlocus(sys)

x0 = [0; 5*pi/180; 0; 0;]

%% State feedback controller

desiredPoles = [-11; -11; -11; -1];
K = acker(A,B, desiredPoles)

Q = 10*eye(4);
R = 0.5;
K_LQR = lqr(A,B,Q,R)


%% Discrete time controller
Ts = 0.01;
sys_d = c2d(sys, Ts);

Ad = sys_d.a;
Bd = sys_d.b;
Cd = sys_d.c;
Dd = sys_d.d;

pole(sys_d)
disc_Poles = [0.9; 0.9; 0.9; 0.9];
%K_disc = acker(Ad,Bd, disc_Poles);
K_discLQR = dlqr(Ad,Bd,Q,R);
rlocus(sys_d)

%% Observer design

%Vd = 0.1*eye(4);
%Vn = 1;

%Kf = (lqr(Ad', Cd', Vn, Vd))';

disc_PolesOb = [-0.3235; 9.2180;-0.5275; 0.9045]*0.1;
Ob = acker(Ad',Cd',disc_PolesOb);
