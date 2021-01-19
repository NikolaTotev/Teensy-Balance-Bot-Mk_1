clc 
clear all
close all
%% 
%m = 0.294;
%M =  0.378;
%L = 0.14;
g = -9.82;
%{
d = 0.01;
%}

m = 1;
M = 5;
L = 2;
%g = -10;
d = 1;
d1 = 0.01;
d2 = 0.01;

s = 1; % pend up => (s=1)

%% System matrices


A = [0 1 0 0;
     0 -d/M -(m*g)/M 0;
     0 0 0 1;
     0 -(s*d)/(M*L) -(s*(m+M)*g)/(M*L) 0];

B = [0; 1/M; 0; (s*1)/(M*L)];

%{
A = [0, 0 ,1, 0;   
     0, (g*m)/M, -d1/M, -d2/(L*M);   
     0, 0, 0 ,1;     
     0, (g*(M+m))/(L*M), -d1/(L*M), (-d2*(M+m))/(L*L*M*m)];
 
B = [0; 0; 1/M; 1/(L*M)];
%}


C = [1,1,1,1];
D = zeros(size(C,1), size(B,2));


linSys = ss(A,B,C,D);
Am = linSys.a;
Bm = linSys.b;
Cm = linSys.c;
Dm = linSys.d;

x0 = [0; 0; pi; .5];

%% System analysis

eig(A)
Ctrb_Mat = ctrb(A,B);
rank(Ctrb_Mat)

%% Pole placement 
%desEigs = [-1; -2; -3; -4];
%K = place(A,B, desEigs)

%% LQR

Q = [1 0 0 0;
     0 1 0 0;
     0 0 1 0;
     0 0 0 1;];
R = 1;

K = lqr(A,B,Q,R);

eig(A-B*K)

%% Observability test

D = zeros(size(C,1), size(B,2));
ObsvMatr = obsv(A,C);
rank(ObsvMatr);

% Sys augment with disturbances 
Vd = 0.1*eye(4);
Vn = 1;
BF = [B, Vd, 0*B];

sysC = ss(A,BF,C,[0 0 0 0 0 Vn]);
sysFullOutput = ss(A, BF, eye(4), zeros(4,size(BF,2)));

%% Kalman Filter 
Kf = (lqr(A', C', Vd, Vn))';

sysKF = ss(A-Kf*C, [B Kf], eye(4), 0*[B Kf]);

dt = 0.01;
t= dt:dt:50;
uDIST = randn(4,size(t,2));
uNOISE = randn(size(t));

u= 0*t;
u(100:120) = 100;
u(1500:1520) = -100;

uAUG = [u; Vd*Vd*uDIST; uNOISE];
[y,t] = lsim(sysC, uAUG, t);
plot(t,y);

[xtrue,t] = lsim(sysFullOutput, uAUG, t);
hold
plot(t, xtrue(:,1),'r','LineWidth', 2.0)

[x,t] = lsim(sysKF, [u; y'], t);
plot(t,x(:,1),'k--', 'LineWidth', 2.0)

figure
plot(t, xtrue, '-', t,x,'--', 'LineWidth', 2)



