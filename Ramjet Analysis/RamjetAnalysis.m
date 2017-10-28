
% (1) Start the assignment with an ideal Ramjet analysis upto Mach 4, for
% an ambient at 220K and sound speed = 295 m/s; burner temperatures 2000K,
% 2500K.  Plot variation of specific thrust and fuel air ratio and
% propulsive efficiency vs. velocity.
% (1) See Prep Code - Device and Flight Constraints
% (1) See Figures
%
% (2) Establish a polynomial dependence of diffuser stag pressure ratio
% as a function of Mach Number.  Use burner thermal efficiency of 98%,
% stagnation pressure ratio of 95%,  and nozzle stagnation pressure ratio
% of 95%
% (2) See Prep Code - Device Constraints and PolyFit
%
% (3) Conduct real ramjet analysis incorporating stag pressure ratios,
% and assuming exit pressure = ambient pressure; plot specific thrust
% and fuel air ratio, and propulsive efficiency
%
% (4) Use real values of specific heat and specific heat ratio from
% website or tables like these:
% https://www.ohio.edu/mechanical/thermo/property_tables/air/air_Cp_Cv.html
% (5) Extrapolate thermodynamic values as needed, if actual values not
% found.
% (4-5) See SpecificHeat Function
%
% (6) Assignment due Tuesday April 12th, with code.


% NOTE: Figure plots are commented out except for comparison plots.
%% Prep Code
clear; close all; clc; format compact;
cd('D:\Documents\Vanderbilt-Grad\Classes2014_16\Aerospace Propulsion')

% Device Constraints
Tburner = [2000 2500];
pi_d = 0.95;    % P2t/P0t
pi_b = 0.98;    % P3t/P2t
pi_noz = 0.95;  % P4t/P3t
pi_star = pi_d*pi_b*pi_noz;

Qr = 45000;

% Flight Conditions
Ma = [1 1.5 2 2.5 3 3.5 4];   % [-], Mach Number Range for N = 4
PStagRatio = [1 0.98 0.95 0.90 0.82 0.76 0.63]; % P Ratios for N = 4
Tamb = 220;                         % [K], Ambient Temperature
a0 = 295;                            % [m/s], Ambient Speed of Sound

% Polynomial Fit of Ma and PStagRatio data
[Ma,PStagRatio] = Mach2PStag(Ma,PStagRatio); %P2t/P0t

fignum = 3;

%% Ideal Analysis
[cp0,~,gamma0,~] = SpecificHeat(Tamb); % [-], Air Properties

% Preallocation
Tsp_IDEAL = zeros(2,length(Ma));
f_IDEAL = zeros(2,length(Ma));
eta_prop_IDEAL = zeros(2,length(Ma));

% fuel air ratio - f = mdot_0 / mdot_f
for i = 1:length(Tburner)
    f_IDEAL(i,:) = (Tburner(i) - Tamb*(1+(gamma0-1)/2*Ma.^2))/(Qr/cp0 - Tburner(i));
end
%       if ishandle(fignum) == 0
%    figure(fignum)
%     plot(Ma,f_IDEAL);
%    title('AFR IDEAL (-) vs. Ma (-)');
%    xlabel('Ma (-)'); ylabel('AFR IDEAL (-)'); axis tight;
%    xlim([1 4])
%    legend('T = 2000 K','T = 2500 K','Location','Northeast');
% else  end
% fignum = fignum + 1;


% Specific Thrust (T/mdot) = V4 - V0
% THIS IS THE IDEAL CASE IN THE SIMPLEST FORM
% for i = 1:length(Tburner)
% Tsp_IDEAL(i,:) = a0.*Ma.*(sqrt(Tburner(i)./(Tamb*(1+(gamma0-1)/2*Ma.^2)))-1);
% end

for i = 1:length(Tburner)
    [~,~,gamma0,R0] = SpecificHeat(Tamb);
    [~,~,gamma4,R4] = SpecificHeat(Tamb);
    BIGpi(i,:) = (1*pi_star)^((gamma4-1)/gamma4)*(1+(gamma0-1)/2*Ma.^2).^((gamma4-gamma0)/(gamma4*(gamma0-1)));
    V4V0(i,:) = (gamma4*R4)/(gamma0*R0)*(Tburner(i)./(Tamb*(1+(gamma0-1)/2*Ma.^2))).*(1./BIGpi(i,:))*(2/(gamma4-1)).*((BIGpi(i,:).*(1+(gamma0-1)/2*Ma.^2))-1)./Ma.^2;
    Tsp_IDEAL(i,:) = a0*Ma.*((1+f_IDEAL(i,:)).*sqrt(V4V0(i,:))-1);
end
%       if ishandle(fignum) == 0
%    figure(fignum)
%     plot(Ma,Tsp_IDEAL);
%    title('Tsp IDEAL (-) vs. Ma (-)');
%    xlabel('Ma (-)'); ylabel('Tsp IDEAL (m/s  or  N*s/kg)'); axis tight;
%    xlim([1 4])
%    legend('T = 2000 K','T = 2500 K','Location','Northeast');
% else end
% fignum = fignum + 1;


% propulsive efficiency - propulsive power / engine power output
% engine power output = mdot/2[(1+f)*V4^2 - V0^2]
% Ve and V0 are entry and exit velocities respectively
% propulsion power = F*V0 = mdot[(1+f)*V4 - V0]*V0
% F is force of thrust, V0 is flight velocity
% eta_p = (2[(1+f)*V4 - V0]*V0)/((1+f)*V4^2 - V0^2)
% V4 = T/mdot + V0
V0 = Ma*a0;                          % [m/s], Flight Velocity

for i = 1:length(Tburner)
    eta_prop_IDEAL(i,:) = (((1+f_IDEAL(i,:)).*(Tsp_IDEAL(i,:)+V0)   + V0).*V0)./ ...
        ((1+f_IDEAL(i,:)).*(Tsp_IDEAL(i,:)+V0).^2 + V0.^2);
end
%       if ishandle(fignum) == 0
%    figure(fignum)
%     plot(Ma,eta_prop_IDEAL);
%    title('CHECK LEGEND ENTRIES - Ideal Propulsive Efficiency (-) vs. Ma (-)');
%    xlabel('Ma (-)'); ylabel('Ideal Propulsive Efficiency (-)'); axis tight;
%    xlim([1 4])
%    legend('T = 2000 K','T = 2500 K','Location','Best');
% else end
% fignum = fignum + 1;

%% Real Analysis
% Preallocation
Tsp_REAL       = zeros(2,length(Ma));
f_REAL         = zeros(2,length(Ma));
eta_prop_REAL  = zeros(2,length(Ma));
BIGpi          = zeros(2,length(Ma));
V4V0           = zeros(2,length(Ma));

% fuel air ratio - f = mdot_0 / mdot_f
for i = 1:length(Tburner)
    [cp3,~,~,~] = SpecificHeat(Tburner(i));
    [cp0,~,gamma0,~] = SpecificHeat(Tamb);
    f_REAL(i,:) = (cp3*Tburner(i) - cp0*Tamb*(1+(gamma0-1)/2*Ma.^2))/(Qr - cp3*Tburner(i));
end
%       if ishandle(fignum) == 0
%    figure(fignum)
%     plot(Ma,f_REAL);
%    title('AFR REAL (-) vs. Ma (-)');
%    xlabel('Ma (-)'); ylabel('AFR REAL (-)'); axis tight;
%    xlim([1 4])
%    legend('T = 2000 K','T = 2500 K','Location','Northeast');
% else  end
% fignum = fignum + 1;


for i = 1:length(Tburner)
    [~,~,gamma0,R0] = SpecificHeat(Tamb);
    [~,~,gamma4,R4] = SpecificHeat(Tburner(i));
    BIGpi(i,:) = (1*pi_star)^((gamma4-1)/gamma4)*(1+(gamma0-1)/2*Ma.^2).^((gamma4-gamma0)/(gamma4*(gamma0-1)));
    V4V0(i,:) = (gamma4*R4)/(gamma0*R0)*(Tburner(i)./(Tamb*(1+(gamma0-1)/2*Ma.^2))).*(1./BIGpi(i,:))*(2/(gamma4-1)).*((BIGpi(i,:).*(1+(gamma0-1)/2*Ma.^2))-1)./Ma.^2;
    Tsp_REAL(i,:) = a0*Ma.*((1+f_REAL(i,:)).*sqrt(V4V0(i,:))-1);
end
%       if ishandle(fignum) == 0
%    figure(fignum)
%     plot(Ma,Tsp_REAL);
%    title('Tsp REAL (-) vs. Ma (-)');
%    xlabel('Ma (-)'); ylabel('Tsp REAL (m/s  or  N*s/kg)'); axis tight;
%    xlim([1 4])
%    legend('T = 2000 K','T = 2500 K','Location','Northeast');
% else end
% fignum = fignum + 1;

% propulsive efficiency - propulsive power / engine power output
% engine power output = mdot/2[(1+f)*V4^2 - V0^2]
% Ve and V0 are entry and exit velocities respectively
% propulsion power = F*V0 = mdot[(1+f)*V4 - V0]*V0
% F is force of thrust, V0 is flight velocity
% eta_p = (2[(1+f)*V4 - V0]*V0)/((1+f)*V4^2 - V0^2)
% V4 = T/mdot + V0
V0 = Ma*a0;                          % [m/s], Flight Velocity

for i = 1:length(Tburner)
    eta_prop_REAL(i,:) = (((1+f_REAL(i,:)).*(Tsp_REAL(i,:)+V0)   + V0).*V0)./ ...
        ((1+f_REAL(i,:)).*(Tsp_REAL(i,:)+V0).^2 + V0.^2);
end
%       if ishandle(fignum) == 0
%    figure(fignum)
%     plot(Ma,eta_prop_REAL);
%    title('CHECK LEGEND ENTRIES - Real Propulsive Efficiency (-) vs. Ma (-)');
%    xlabel('Ma (-)'); ylabel('Real Propulsive Efficiency (-)'); axis tight;
%    xlim([1 4])
%    legend('T = 2000 K','T = 2500 K','Location','Best');
% else end

%% Comparison Plots
fignum = fignum + 1;
if ishandle(fignum) == 0
    figure(fignum)
    plot(Ma,vertcat(Tsp_REAL,Tsp_IDEAL));
    title('Tsp REAL (-) vs. Ma (-)');
    xlabel('Ma (-)'); ylabel('Tsp REAL (m/s  or  N*s/kg)'); axis tight;
    xlim([1 4])
    legend('T_R = 2000 K','T_R = 2500 K','T_I = 2000 K','T_I = 2500 K','Location','Northeast');
else end
fignum = fignum + 1;

if ishandle(fignum) == 0
    figure(fignum)
    plot(Ma,vertcat(eta_prop_REAL,eta_prop_IDEAL));
    title('CHECK LEGEND ENTRIES - Real Propulsive Efficiency (-) vs. Ma (-)');
    xlabel('Ma (-)'); ylabel('Real Propulsive Efficiency (-)'); axis tight;
    xlim([1 4])
    legend('T_R = 2000 K','T_R = 2500 K','T_I = 2000 K','T_I = 2500 K','Location','Best');
else end
fignum = fignum + 1;

if ishandle(fignum) == 0
    figure(fignum)
    plot(Ma,vertcat(f_REAL,f_IDEAL));
    title('AFR REAL (-) vs. Ma (-)');
    xlabel('Ma (-)'); ylabel('AFR REAL (-)'); axis tight;
    xlim([1 4])
    legend('T_R = 2000 K','T_R = 2500 K','T_I = 2000 K','T_I = 2500 K','Location','Northeast');
else end

end

function [Ma,PStagRatio] = Mach2PStag(Ma,PStagRatio)
% Create a polynomial fit between Ma and the stagnation pressure ratios
p = polyfit(Ma,PStagRatio,3);
Ma_int = 1:0.1:4;
PStagRatio = p(1)*Ma_int.^3+p(2)*Ma_int.^2+p(3)*Ma_int.^1+p(4);
Ma_int = horzcat(0,Ma_int);
PStagRatio = horzcat(1,PStagRatio);
Ma = Ma_int;
if ishandle(2) == 0
    figure(2)
    plot(Ma_int,PStagRatio);
    axis([0 4 0 1.01]);
    title('Stagnation Pressure Ratio (-) vs. Ma (-)');
    xlabel('Ma (-)'); ylabel('Stagnation Pressure Ratio (-)'); axis tight;
else end
end
function [cp,cv,gamma,R] = SpecificHeat(temperature)
% E.W. Lemmon, R.T. Jacobsen, S.G. Penoncello, and D. Friend,
% "Thermodynamic Properties of Air and Mixtures of Nitrogen, Argon, and
% Oxygen from 60 to 2000 K at Pressures to 2000 MPa," J. Phys. Chem.
% Ref. Data, Vol. 29, No. 3, (2000).
%
% For temperatures between 2000 K and 3500 K, the thermodynamic properties
% are based on data from Keenan, Chao, and Kaye, Gas Tables, Wiley, (1983).
% Note that these tables can be printed from the website associated with
% this text, www.cambridge.org/kleinandnellis

if temperature < 200
    warning('Temperature (%0.0f) outside of bounds (200-3500)',temperature)
    temperature = 200;
elseif temperature > 3499
    warning('Temperature (%0.0f) outside of bounds (200-3500)',temperature)
    temperature = 3499;
end
[num,~,~] = xlsread('SpecificHeatCapacity.xlsx','Sheet1','A1:E150');
[~,index] = min(abs(num(:,1)-temperature));

closest = num(index,1);
if closest > temperature
    index2 = index - 1;
else
    index2 = index + 1;
end
nextclose = num(index2,1);
location = index + min(abs(num(:,1)-temperature))/abs(nextclose-closest);

% Interpolate values for Cp, Cv, and Gamma given temperature
cp    = interp1(num(:,2),location,'linear');
cv    = interp1(num(:,3),location,'linear');
gamma = interp1(num(:,4),location,'linear');
R     = interp1(num(:,5),location,'linear');

if ishandle(1) == 0
    figure(1)
    plot(num(:,1),num(:,2)); hold on
    plot(num(:,1),num(:,3)); hold on
    plot(num(:,1),num(:,4)); hold on
    plot(num(:,1),num(:,5)); hold off
    title('Air Properties (Misc.) vs. Temperature (K)');
    xlabel('Temperature (K)'); ylabel('Air Properties (Misc.)'); axis tight;
    axis([200 3500 0 1.5]);
    legend('Cp','Cv','Gamma','R','Location','Best');
end

