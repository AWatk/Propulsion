%% Dexter Watkins  Propulsion - Homework 1



%% Problem Definition
% Describe the problem



%% Problem Setup
% Define units, constants, and vehicle properties for the problem

% Define units and coordinate system
units = 'Metric';
CS = 'Spherical';

% Define celestial body constants
g0 = 9.81; %m/s^2
R0 = 6400000; %m

% Define vehicle properties
vehicleMass = 400; %kg
fuelMass = 80; %kg
dmdt = -3.33e-6; %kg/sec
Thrust = 0.07; %N

%Construct vehicle state vector
r = R0; %m initial radius
escapeVelocity = sqrt(2*g0*R0^2/r); %m/s
drdt = escapeVelocity; %initial radial velocity m/s
sv = [0 0 r 0 0 drdt 0 0 0]; %state vector [pos vel accel]

%instantiate vehicles
baseVehicle = Vehicle(vehicleMass, 0, 0, sv, 0, CS, units); %base w/o Thrust
thrustVehicle = Vehicle(vehicleMass, fuelMass,...
    dmdt, sv, Thrust, CS, units); %vehicle w/Thrust


%% Solver Execution
% Set solver options and prepare to run
%Run ode45 solver for both baseline and thrusted vehicles

% Define/Calculate Time Spans
t0 = 0; %s initial time
tf = fuelMass/abs(dmdt); %s final time when fuel

baseSolution = baseVehicle.homework1_propagate([t0 tf]);
thrustSolution = thrustVehicle.homework1_propagate([t0 tf]);

%% Analysis
% Plot and discuss results

posfig = figure(1);
plot(baseSolution.time, baseSolution.position, 'bd',...
    thrustSolution.time, thrustSolution.position, 'kd');

velfig = figure(2);
plot(baseSolution.time, baseSolution.velocity, 'bd',...
    thrustSolution.time, thrustSolution.velocity, 'kd');
