% This is a verification of an energy approach to solving the motion of a
% moving object with only drag and gravitational forces

rho = 1.2; %kg/m3
cd = 1.3; %drag coefficient
mass = 10; %kg
g = 9.8; %m/s2
A = 0.1; %m2

vt = sqrt(2*mass*g/(cd*rho*A));

%Baseline - ODE approach
y0 = zeros(2,1);
y0(1)= 0; %m/s
y0(2) = 100; %m/s
sol = ode45(@(t,y) [y(2) -g-(y(2)/abs(y(2))*.5*rho*A*cd*y(2)^2/mass)]',...
    [0 10],y0);
tspan = 1:0.1:10;
y = deval(sol,tspan);
basePos = y(1,:);
plot(tspan,basePos);

maxBase = max(basePos);

%energy approach analytical calculation
maxNRG = vt^2/(2*g)*log(1+100^2/vt^2);