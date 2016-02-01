%% Dexter Watkins  Propulsion - Homework 1

%% Problem Definition
% Calculate radius, velocity, and acceleration as a function of time for a
% spacecraft moving radially (and only radially) away from the earth. Use a
% numerical method to solve this problem.  Examine the case with and
% without onboard propulsion
%% Specified Properties and Assumptions
% 
% 
% # The vehicle is initially moving at escape velocity (11.2 km/s)
% # The vehicle starts at earth's surface (R0 = 6400 km)
% # Non-conservative forces can be ignored (earth's atmosphere)
% # The vehicle's mass is 400kg, 80kg of which is fuel
% # If onboard propulsion is used, fuel consumption is 3.33e-6 kg/s
% # If onboard propulsion is used, 70 mN of thrust is generated.
% # The vehicle's flight can be modeled as a 2-body problem
% 
%% Governing Equations
% The equation of motion for the flight vehicle is determined by the
% following system of equations:
%
% $$r'' = -g0*R0^2/r^2 + Thrust/(m(t))$$
%  
% $$m' = -3.33*10^-6$$
%  
% For easier use, the system of equations is rewritten as a system of
% purely first order equations, as follows:
%  
% $$y_1' = y_2$$
%  
% $$y_2' = -g0*R0^2/r^2 + Thrust/(y_3)$$
%  
% $$y_3' = -3.33*10^-6$$
%
% Where $$y_1$ is radius, $$y_2$ is velocity, and $$y_3$ is mass.

%% Problem Setup
% A custom matlab class named "Vehicle" is used to encapsulate vehicle
% properties such as fuel mass, fuel consumption rate, thrust produced, and
% the vehicle's state vector.  While overkill for this particular problem,
% this custom class will provide a good foundation for future assignments,
% and more importantly my own research.  As such, this class will be
% further developed and refined as the semester continues.  For further
% documentation, see the section "Vehicle Class".
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
% The following code initializes the unit and coordinate system, celestial
% constands, and vehicle properties. Two vehicles corresponding to the two
% cases evaluated are then instantiated.
%  
%  
%%
% Define units and coordinate system
units = 'Metric';
CS = 'Spherical';
%%
% Define celestial body constants
g0 = 9.81; %m/s^2
R0 = 6400000; %m
%%
% Define vehicle properties
vehicleMass = 400; %kg
fuelMass = 80; %kg
dmdt = -3.33e-6; %kg/sec
Thrust = 0.07; %N
%%
% Construct vehicle state vector
r = R0; %m initial radius
escapeVelocity = sqrt(2*g0*R0^2/r); %m/s
drdt = escapeVelocity; %initial radial velocity m/s
sv = [0 0 r 0 0 drdt 0 0 0]; %state vector [pos vel accel]
%%
% Instantiate vehicles
baseVehicle = Vehicle(vehicleMass, 0, 0, sv, 0, CS, units); %base w/o Thrust
thrustVehicle = Vehicle(vehicleMass, fuelMass,...
    dmdt, sv, Thrust, CS, units); %vehicle w/Thrust
%% Solver Execution
% After defining a time span over which to solve the problem, the ode45
% solver is ready to be run. The homework1_propagate() defined within the
% vehicle class is called, which contains the ode45 solver setup.
% 
%%
% Define/Calculate Time Spans
t0 = 0; %s initial time
tf = fuelMass/abs(dmdt); %s final time when fuel
%%
% Run ode45 solver
baseSolution = baseVehicle.homework1_propagate([t0 tf]);
thrustSolution = thrustVehicle.homework1_propagate([t0 tf]);

%% 
% Plot and discuss results
%%
%set line width
lw = 3;
%% Position Analysis
% While the baseline vehicle appears to be asymptotically approaching some
% value, it is actually unbounded and will increase to infinity.This is due
% to the fact that the vehicle was initially moving at escape velocity,
% meaning that it's velocity will only be zero at infinity.
%
% The thrusted vehicle, on the other hand, will clearly continue its
% outward trajectory indefinitely, as earth's gravity is quickly reduced to
% a value so small as to be considered negligible compared to thrust.
posfig = figure(1);
plot(baseSolution.time, baseSolution.position, 'b',...
    thrustSolution.time, thrustSolution.position, 'k','LineWidth',lw);
posfig.Units = 'normalized';
posfig.Position = [0.05 0.5 0.42 0.42];
title('Radial Distance of Baseline and Thrusted Vehicles');
ylabel('Distance (m)');
xlabel('Time (Days)');
legend('Baseline Vehicle', 'Thrusted Vehicle', 'Location', 'NorthWest');

%% Velocity Analysis
% Again, the velocity of the baseline vehicle approaches zero, but since it
% was initially going at escape velocity, it will only be zero at infinity
%
% The thrusted vehicle's velocity initially decays in the same way as the
% unthrusted, since earth's gravity is initially much greater than its
% thruster. But as radius increases, earth's gravity decrease quadratically
% and the vehicle's thrust sooner overtakes it and starts to acclerate the
% vehicle.
velfig = figure(2);
plot(baseSolution.time, baseSolution.velocity, 'b',...
    thrustSolution.time, thrustSolution.velocity, 'k','LineWidth',lw);
velfig.Units = 'normalized';
velfig.Position = [0.55 0.5 0.42 0.42];
title('Velocity of Baseline and Thrusted Vehicles');
ylabel('Velocity (m/s)');
xlabel('Time (Days)');
legend('Baseline Vehicle', 'Thrusted Vehicle');

%% Acceleration Analysis
% As can be seen in the following three graphs, the vehicle's acceleration
% is initially dominated by earth's presence, before leveling out to nearly
% zero in the base case or nearly 70mn/vehicle_mass in the thrusted case.
% In the early time stages, the baseline and thrusted vehicle's 
% acceleration is almost indistinguishable.
accelfig = figure(3);
plot(baseSolution.time, baseSolution.acceleration, 'b',...
    thrustSolution.time, thrustSolution.acceleration, 'k','LineWidth',lw);
accelfig.Units = 'normalized';
accelfig.Position = [0.05 0.02 0.40 0.40];
title('Acceleration of Baseline and Thrusted Vehicles');
ylabel('Acceleration (m/s^2)');
xlabel('Time (Days)');
legend('Baseline Vehicle', 'Thrusted Vehicle', 'Location', 'SouthEast');

accelfig_init = figure(4);
plot(baseSolution.time, baseSolution.acceleration, 'b',...
    thrustSolution.time, thrustSolution.acceleration, 'k','LineWidth',lw);
accelfig_init.Units = 'normalized';
accelfig_init.Position = [0.05 0.02 0.40 0.40];
accelfig_init.CurrentAxes.XLim = [0 0.05];
title('Initial Acceleration of Baseline and Thrusted Vehicles');
ylabel('Acceleration (m/s^2)');
xlabel('Time (Days)');
legend('Baseline Vehicle', 'Thrusted Vehicle', 'Location', 'SouthEast');

accelfig_end = figure(5);
plot(baseSolution.time, baseSolution.acceleration, 'b',...
    thrustSolution.time, thrustSolution.acceleration, 'k','LineWidth',lw);
accelfig_end.Units = 'normalized';
accelfig_end.Position = [0.05 0.02 0.40 0.40];
accelfig_end.CurrentAxes.YLim = [-1e-4 2.5e-4];
title('Long Term Acceleration Difference of Baseline and Thrusted Vehicles');
ylabel('Acceleration (m/s^2)');
xlabel('Time (Days)');
legend('Baseline Vehicle', 'Thrusted Vehicle', 'Location', 'SouthEast');

%% Mass Analysis
% Mass is constant with time for the base case, since there is no
% propulsion and therefore no fuel consumption
%
% Mass decreases linearly for the propulsion case, as defined in the
% problem setup
massfig = figure(6);
plot(baseSolution.time, baseSolution.mass, 'b',...
    thrustSolution.time, thrustSolution.mass, 'k','LineWidth',lw);
massfig.Units = 'normalized';
massfig.Position = [0.55 0.02 0.40 0.40];
massfig.CurrentAxes.YLim = [300 420];
title('Mass of Baseline and Thrusted Vehicles');
ylabel('Mass (kg)');
xlabel('Time (Days)');
legend('Baseline Vehicle', 'Thrusted Vehicle', 'Location', 'SouthWest');
