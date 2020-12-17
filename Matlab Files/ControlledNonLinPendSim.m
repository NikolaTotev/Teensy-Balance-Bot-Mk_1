tspan = 0:.001:30;

if(s==-1)
    y0 = [0; 0; 0; 0];
    [t,y] = ode45(@(t,y)NonLinearPendModel(y,m,M,L,g,d,-K*(y-[4;0;0;0])),tspan,y0);
elseif(s==1)
    y0 = [-3 ; 0; pi+0.1; 0];
    [t,y] = ode45(@(t,y)NonLinearPendModel(y,m,M,L,g,d,-K*(y-[2;0;pi;0])),tspan,y0);
else
end    


for k=1:100:length(t)
    DrawPend(y(k,:),m,M,L);
end


figure 
plot(t,y);
