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
