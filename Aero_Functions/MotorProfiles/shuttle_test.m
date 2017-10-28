theta = 20;

m = 86400;

tspan = [0 2000];

y0 = [0 0 0 0];

sol = ode45(@(t,y) shuttlefunc(t,y,m,theta),tspan,y0);

time = tspan(1):10:tspan(2);

[y, yp] = deval(sol, time);

plot(time,y(2,:));