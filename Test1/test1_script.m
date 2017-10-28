%set up problem
cd = 0.45;
y0 = [0 1600 0 -5]; %[px py vx vy]

tspan = [0 50];
time = tspan(1):0.1:tspan(2);
%--------------------------------------------
% Scenario (i)
%--------------------------------------------

sol1 = ode45(@(t,y) testfunc1(t,y,0,cd),tspan, y0);
[y1 yp1] = deval(sol1, time);
index = find(y1(2,:)>=800);
y1 = y1(:,index);
yp1 = yp1(:,index);
time1 = time(index);

figure(1)
plot(time1,y1(2,:));
title('Vertical Position vs Time');
xlabel('Time (s)');
ylabel('Position (m)');

figure(2)
plot(time1,y1(4,:));
title('Vertical Velocity vs Time');
xlabel('Time (s)');
ylabel('Velocity (m/s)');


%--------------------------------------------
% Scenario (ii)
%--------------------------------------------

sol2 = ode45(@(t,y) testfunc1(t,y,5,cd),tspan, y0);
[y2 yp2] = deval(sol2, time);
index = find(y2(2,:)>=800);
y2 = y2(:,index);
yp2 = yp2(:,index);
time2 = time(index);

figure(3)
plot(time2,y2(2,:));
title('Vertical Position vs Time');
xlabel('Time (s)');
ylabel('Position (m)');

figure(4)
plot(time2,atand(y2(3,:)./-y2(4,:)));
title('Angular vs Time');
xlabel('Time (s)');
ylabel('Angle (Theta)');

%--------------------------------------------
% Scenario (iii)
%--------------------------------------------

% NOTE: The moment that is applied to the rocket from the thruster is 
% Thrust * Moment Arm = 5 * 0.307 = 1.535
% Angular acceleration is then alpha = 12*M/(m*L^2) which is 0.1965 for this problem.
% The time to reach 180 degress from 0 is then sqrt(180/(0.5*alpha) = ~ 42
% seconds
% The fight time of the rocket is only ~32 seconds
% Therefore, the rocket will hit the ground before fully uprighting
% Ground collision is ignored and I give the (negative) value for height at
% which the rocket fully rights itself.

y0 = [0 1600 0 -5 0 0]; %[px py vx vy theta omega]

sol3 = ode45(@(t,y) testfunc2(t,y),tspan,y0);
[y3 yp3] = deval(sol3,time);
index = find(y3(5,:)<=180);
% index = 1:1:length(y3(2,:));
y3 = y3(:,index);
yp3 = yp3(:,index);
time3 = time(index);



figure(5)
plot(time3,y3(2,:));
title('Vertical Position vs Time');
xlabel('Time (s)');
ylabel('Position (m)');

figure(6)
plot(time3,y3(5,:));
title('Angule vs Time');
xlabel('Time (s)');
ylabel('Angle (Theta)');

h = y3(2,end);

fprintf('The height at which the rocket turns completely over is %2.2f meters \n',h);









