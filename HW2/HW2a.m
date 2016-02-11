%% Dexter Watkins  Propulsion - Homework 2

%% Problem Definition
% Calculate position, velocity, and acceleration as a function of time for
% a rocket from launch until apogee. Use a numerical method to solve this
% problem.  Examine the following five cases.
%
% # A single rocket motor and constant air density (1.2 kg/m3)
% # A single rocket motor and density as a function of height
% # Same as case two, with the addition of two monopropellant thrusters
% # Same as case three, but varying Cd from 0.4-0.6 in steps of 0.05
% # Same as case three, but varying dry mass from 14-16 in steps of 0.25
%
%% Specified Properties and Assumptions
% 
% # Rocket has a dry mass of 14.34 kg
% # The rocket has a cross-sectional area of 0.015327 square meters
% # The rocket has a drag coefficient of 0.5,cases 1-4 and 0.45 for case 5
% # The main motor has a mass of 1.755 kg and mass flow rate of 0.8357 kg/s
% # The main motor will fire from t0 to t+2.1 seconds
% # The main motor produces a thrust of 1760 N;
% # The Mono-Props are 0.08 kg each, with a mass flux of 0.01 kg/s each
% # The Mono-Props will fire from t+1 to t+9 seconds
% # Each Mono-Prop produces a thust of 10 N;
% 
%% Governing Equations
% The equation of motion for the flight vehicle is determined by the
% following system of equations:
%
% $$r'' = (Thrust - m*g0*R0^2/r^2 -(r'/abs(r'))*(0.5*Cd*rho*A*r'^2))/m$$
% $$m' = \sum(m'_{fired-thrusters})$$
%
% For easier use, the system of equations is rewritten as a system of
% purely first order equations, as follows:
%
% $$y'_1 = y_2$$
%
% $$y'_2 = (Thrust - y_3*g0*R0^2/y_1^2 -(y_2/abs(y_2))*(0.5*Cd*rho*A*y_2^2))/y_3$$
%
% $$y'_3 = \sum(m'_{fired-thrusters})$$
% 
% Where $$y_1$ is position, $$y_2$ is velocity, and $$y_3$ is mass
%
%% Problem Setup
% A custom matlab class named "Vehicle" is used to encapsulate vehicle
% properties such as its state vector, cross-sectional area, and drag 
% coefficient. Additionally, the Vehicle class will contain system
% components such as thrusters and structures.  Each of these components
% will contain properties such as current mass, fuel mass, thrust produced,
% fuel flow rate, etc.
%
% The system of differential equations will be solved using matlab's built
% in ode45 solver.  The ode45 solver gets it name from the 4th and 5th
% order runge kutta numerical techniques it uses.  Ode45 first estimates a
% time step and approximates a solution using the 4th order method.  The 
% 5th order method is then evaluated and the difference between the two is 
% taken to be the method's error.  This error is compared to the 
% user-specified error tolerance (default 0.1%).  If the error is too 
% large, a smaller time step is chosen and the solution re-evaluated.
%
% In order to use ode45, a function must be defined that calculates the
% system of equations in the following way:  
% 
% $$y_1' = f_1(t,y)$$
% ...       
% $$y_n' = f_n(t,y)$$
% 
% As a system of equations that satisfies this criterion has already been 
% developed, all that is needed are initial conditions and the start 
% and end times. 
%  
%  
%% Rocket Construction

% Define rocket vehicle
rocket_name = 'Rocket';
% Define earth's mean radius
R0 = 6.371e6;  % m
sv = zeros(1,9); % state vector: [x y z vx vy vz ax ay az]
sv(1) = R0; %initially at earth's surface
area = 0.015327;
cd = 0.5;
CS = 'Cartesian';
Units = 'Metric';
r = Vehicle(rocket_name,sv,area,cd,CS,Units);

% Define rocket body
bname = 'Body';
bmass = 14.34;
b = Structure(bname, bmass, CS, Units);

% Define main thruster
mname = 'Main';
mmass = 0;
mmass_fuel = 1.755;
mmass_flowrate = 1.755/2.1;
mthrust = 1760;
main = Thruster(mname,mmass,CS,Units,mmass_fuel, mmass_flowrate,mthrust);

% Define monoprop1
mp1name = 'Mono1';
mpmass = 0;
mpmass_fuel = 0.08;
mpmass_flowrate = 0.01;
mpthrust = 10;
mp1 = Thruster(mp1name,mpmass,CS,Units,mpmass_fuel,mpmass_flowrate,mpthrust);

% Define monoprop2
mp2name = 'Mono2';
mp2 = Thruster(mp2name,mpmass,CS,Units,mpmass_fuel,mpmass_flowrate,mpthrust);

% Attach components to rocket
r.attach(b);
r.attach(main);
r.attach(mp1);
r.attach(mp2);

%% Simulation Setup and Execution

% Case 1 Setup
xintmain = 0:0.1:2.0; %setup time interval to be used
xintcoast = 2.1:0.1:22; %setup time interval to be used
xint = [xintmain xintcoast];
rho = 1.2; % constant density kg/m3
tspanmain = [0 2.1];
tspancoast = [2.1 22];
r.toggleThruster(mname); % fire main thruster

% Execute Case 1
[y1_1, yp1_1] = deval(r.propagate(tspanmain,rho),xintmain);
[y1_2, yp1_2] = deval(r.propagate(tspancoast,rho),xintcoast);
y1 = {[y1_1 y1_2]};
yp1 = {[yp1_1 yp1_2]};

% Case 2 Setup
r.attach(main); % reset main thruster
r.sv = sv; % reset state vector
r.toggleThruster(mname);

% Execute Case 2
[y2_1, yp2_1] = deval(r.propagate(tspanmain),xintmain);
[y2_2, yp2_2] = deval(r.propagate(tspancoast),xintcoast);
y2 = {[y2_1 y2_2]};
yp2 = {[yp2_1 yp2_2]};

% Case 3 Setup
r.attach(main); % reset main thruster
r.toggleThruster(mname);
r.sv = sv; % reset state vector
tspanMain = [0 1];
tspanMixed = [1 2.1];
tspanMono = [2.1 9];
tspanCoast = [9 22];

% Execute Case 3
[y3_1, yp3_1] = deval(r.propagate(tspanMain),0:0.1:.9);
r.toggleThruster(mp1name);
r.toggleThruster(mp2name);
[y3_2, yp3_2] = deval(r.propagate(tspanMixed),1:0.1:2);
[y3_3, yp3_3] = deval(r.propagate(tspanMono), 2.1:0.1:8.9);
[y3_4, yp3_4] = deval(r.propagate(tspanCoast), 9:0.1:22);
y3 = {[y3_1 y3_2 y3_3 y3_4]}; % combine the time span results
yp3 = {[yp3_1 yp3_2 yp3_3 yp3_4]}; % combine the time span results

% Case 4 Setup
cd = 0.4:0.05:0.6; % vary cd


% Execute Case 4
i = 1;
y4 = {};
yp4 = y4;
for c = cd
    r.attach(main); % reset main thruster
    r.attach(mp1); % reset monoprops
    r.attach(mp2); % reset monoprops
    r.toggleThruster(mname);
    r.sv = sv; % reset state vector
    r.cd = c;
    [y4_1, yp4_1] = deval(r.propagate(tspanMain),0:0.1:.9);
    r.toggleThruster(mp1name);
    r.toggleThruster(mp2name);
    [y4_2, yp4_2] = deval(r.propagate(tspanMixed),1:0.1:2);
    [y4_3, yp4_3] = deval(r.propagate(tspanMono), 2.1:0.1:8.9);
    [y4_4, yp4_4] = deval(r.propagate(tspanCoast), 9:0.1:22);
    y4{i} = [y4_1 y4_2 y4_3 y4_4]; % combine the time span results
    yp4{i} = [yp4_1 yp4_2 yp4_3 yp4_4]; % combine the time span results
    i = i+1;
end

% Case 5 Setup
m = (bmass-0.5):0.25:(bmass+1.5); % vary mass
r.cd = 0.5;

% Execute Case 5
i = 1;
y5 = {};
yp5 = y5;

for c = m(1:4)
    r.attach(main); % reset main thruster
    r.attach(mp1); % reset monoprops
    r.attach(mp2); % reset monoprops
    r.toggleThruster(mname);
    r.sv = sv; % reset state vector
    r.Structures(bname) = Structure(bname, c, CS, Units);
    [y5_1, yp5_1] = deval(r.propagate(tspanMain),0:0.1:.9);
    r.toggleThruster(mp1name);
    r.toggleThruster(mp2name);
    [y5_2, yp5_2] = deval(r.propagate(tspanMixed),1:0.1:2);
    [y5_3, yp5_3] = deval(r.propagate(tspanMono), 2.1:0.1:8.9);
    [y5_4, yp5_4] = deval(r.propagate(tspanCoast), 9:0.1:22);
    y5{i} = [y5_1 y5_2 y5_3 y5_4]; % combine the time span results
    yp5{i} = [yp5_1 yp5_2 yp5_3 yp5_4]; % combine the time span results
    i = i+1;
end
tspanCoastFat = [9 22]; %this is a useless variable,same as tspancoast
for c = m(5:end)
    r.attach(main); % reset main thruster
    r.attach(mp1); % reset monoprops
    r.attach(mp2); % reset monoprops
    r.toggleThruster(mname);
    r.sv = sv; % reset state vector
    r.Structures(bname) = Structure(bname, c, CS, Units);
    [y5_1, yp5_1] = deval(r.propagate(tspanMain),0:0.1:.9);
    r.toggleThruster(mp1name);
    r.toggleThruster(mp2name);
    [y5_2, yp5_2] = deval(r.propagate(tspanMixed),1:0.1:2);
    [y5_3, yp5_3] = deval(r.propagate(tspanMono), 2.1:0.1:8.9);
    [y5_4, yp5_4] = deval(r.propagate(tspanCoastFat), 9:0.1:22);
    y5{i} = [y5_1 y5_2 y5_3 y5_4]; % combine the time span results
    yp5{i} = [yp5_1 yp5_2 yp5_3 yp5_4]; % combine the time span results
    i = i+1;
end


%% Case 1-3 Analysis
% Case 1, with a constant value for density (1.2 kg/m3) slightly
% underperformed Case 2, which had density as a function of height.  This
% is due to density quickly diverging from Case 1's constant value as the
% rocket ascended to apogee.  This shows up again in the velocity graph, as
% case 2 maintains a slightly higher velocity over time.  Case 3 stands
% out, as the addition of monopropellant boosters give a clear boost in
% altitude. A small (but noticeable) increase in acceleration can be
% observed at t+1, when the monoprops fire, as well as a correspondign drop
% in accleration at t+9 when they stop.

% plot position
figure(1)
x1 = xint(y1{1}(2,:)>=0);
pos1 = y1{1}(1,y1{1}(2,:)>=0)-R0;
x2 = xint(y2{1}(2,:)>=0);
pos2 = y2{1}(1,y2{1}(2,:)>=0)-R0;
x3 = xint(y3{1}(2,:)>=0);
pos3 = y3{1}(1,y3{1}(2,:)>=0)-R0;

plot(x1,pos1,x2,pos2,x3,pos3);
ylabel('Position (m)');
xlabel('Time (s)');
legend('Case 1', 'Case 2', 'Case 3', 'Location', 'SouthEast');

% plot velocity
figure(2)
vel1 = y1{1}(2,y1{1}(2,:)>=0);
vel2 = y2{1}(2,y2{1}(2,:)>=0);
vel3 = y3{1}(2,y3{1}(2,:)>=0);

plot(x1,vel1,x2,vel2,x3,vel3);
ylabel('Velocity (m/s)');
xlabel('Time (s)');
legend('Case 1', 'Case 2', 'Case 3');

%plot acceleration
figure(3)
acc1 = yp1{1}(2,y1{1}(2,:)>=0);
acc2 = yp2{1}(2,y2{1}(2,:)>=0);
acc3 = yp3{1}(2,y3{1}(2,:)>=0);

plot(x1,acc1,x2,acc2,x3,acc3);
ylabel('Acceleration (m/s2)');
xlabel('Time (s)');
legend('Case 1', 'Case 2', 'Case 3');

%% Case 4 Analysis
% Case 4 looks at the effect of varying the drag coefficient.  As can be
% seen in the altitude plot, a change of nearly 250 meters is evident
% between the minimum cd (0.4) and the maximum cd (0.6).  

% plot position
figure(4);
hold on;
legendval = cell(1,length(cd)+2);
cm = jet(length(cd));
for i=1:1:length(cd)
    plot(xint(y4{i}(2,:)>=0), y4{i}(1,y4{i}(2,:)>=0)-R0, 'color', cm(i,:));
    legendval{i} = ['Cd = ' num2str(cd(i))];
end
legendval{end-1} = 'Location';
legendval{end} = 'SouthEast';
ylabel('Position (m)');
xlabel('Time (s)');
legend(legendval{:});

% plot velocity
figure(5);
hold on;
legendval = legendval(1:end-2);
for i=1:1:length(cd)
    plot(xint(y4{i}(2,:)>=0), y4{i}(2,y4{i}(2,:)>=0), 'color', cm(i,:));
    legendval{i} = ['Cd = ' num2str(cd(i))];
end
ylabel('Velocity (m/s)');
xlabel('Time (s)');
legend(legendval{:});

% plot acceleration
figure(6);
hold on;
for i=1:1:length(cd)
    plot(xint(y4{i}(2,:)>=0), yp4{i}(2,y4{i}(2,:)>=0), 'color', cm(i,:));
    legendval{i} = ['Cd = ' num2str(cd(i))];
end
ylabel('Acceleration');
xlabel('Time (s)');
legend(legendval{:});

%% Case 5 Analysis
% Case 5 looks at the effect of varying the rocket's dry mass.  Please note
% that the dry mass does not include the mass of the monoprops fuel, hence
% the values that are 0.16kg less than the specified range of 14:0.25:16. A
% change of apogee of ~225 meters is evident between the maximum and
% minimum mass. 

% plot position
figure(7);
hold on;
legendval = cell(1,length(m)+2);
cm = jet(length(m));
for i=1:1:length(m)
    plot(xint(y5{i}(2,:)>=0), y5{i}(1,y5{i}(2,:)>=0)-R0, 'color', cm(i,:));
    legendval{i} = ['Mass = ' num2str(m(i))];
end
legendval{end-1} = 'Location';
legendval{end} = 'SouthEast';
ylabel('Position (m)');
xlabel('Time (s)');
legend(legendval{:});

% plot velocity
figure(8);
hold on;
legendval = legendval(1:end-2);
for i=1:1:length(m)
    plot(xint(y5{i}(2,:)>=0), y5{i}(2,y5{i}(2,:)>=0), 'color', cm(i,:));
    legendval{i} = ['Mass = ' num2str(m(i))];
end
ylabel('Velocity (m/s)');
xlabel('Time (s)');
legend(legendval{:});

% plot acceleration
figure(9);
hold on;
for i=1:1:length(m)
    plot(xint(y5{i}(2,:)>=0), yp5{i}(2,y5{i}(2,:)>=0), 'color', cm(i,:));
    legendval{i} = ['Mass = ' num2str(m(i))];
end
ylabel('Acceleration');
xlabel('Time (s)');
legend(legendval{:});
