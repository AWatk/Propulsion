%% Dexter Watkins  Propulsion - Ramjet Homework

%% Problem Definition
% Calculate specific thrust, fuel-air ratio, and propulsive efficiency for
% an ideal and then real ramjet engine
%
% # Up to Mach 4
% # Establish polynomial dependence of diffuser stagnation pressure on Mach
% # Real analysis with perfect expansion
%
%% Specified Properties and Assumptions
%
% # Ambient temperature 220k
% # Speed of sound 295 m/s
% # Burner temperature 2000k and 2500k
% # Burner efficiency of 98%
% # Stagnation pressure ratio of 95%
% # nozzle stagnation pressure ratio of 95%
%

%% Code


Tburner = [2000 2500];
Pi_d = 0.95;    % P2t/P0t
Pi_b = 0.98;    % P3t/P2t
Pi_noz = 0.95;  % P4t/P3t
Pi_star = Pi_d*Pi_b*Pi_noz;

Qr = 45000;

% Flight Conditions
M = [1 1.5 2 2.5 3 3.5 4];   % [-], Mach Number Range for N = 4
Pratio = [1 0.98 0.95 0.90 0.82 0.76 0.63]; % P Ratios for N = 4
Tamb = 220;                         % [K], Ambient Temperature
a0 = 295;                            % [m/s], Ambient Speed of Sound


[M,Pratio] = MachtoP(M,Pratio); %P2t/P0t

fignum = 3;


[cp0,~,gamma0,~] = Cp(Tamb); % [-], Air Properties


Tsp_I = zeros(2,length(M));
f_I = zeros(2,length(M));
eta_prop_I = zeros(2,length(M));


for i = 1:length(Tburner)
    f_I(i,:) = (Tburner(i) - Tamb*(1+(gamma0-1)/2*M.^2))/(Qr/cp0 - Tburner(i));
end


for i = 1:length(Tburner)
    [~,~,gamma0,R0] = Cp(Tamb);
    [~,~,gamma4,R4] = Cp(Tamb);
    pi_tmp(i,:) = (1*Pi_star)^((gamma4-1)/gamma4)*(1+(gamma0-1)/2*M.^2).^((gamma4-gamma0)/(gamma4*(gamma0-1)));
    V4V0(i,:) = (gamma4*R4)/(gamma0*R0)*(Tburner(i)./(Tamb*(1+(gamma0-1)/2*M.^2))).*(1./pi_tmp(i,:))*(2/(gamma4-1)).*((pi_tmp(i,:).*(1+(gamma0-1)/2*M.^2))-1)./M.^2;
    Tsp_I(i,:) = a0*M.*((1+f_I(i,:)).*sqrt(V4V0(i,:))-1);
end

V0 = M*a0;                          % [m/s], Flight Velocity

for i = 1:length(Tburner)
    eta_prop_I(i,:) = (((1+f_I(i,:)).*(Tsp_I(i,:)+V0)   + V0).*V0)./ ...
        ((1+f_I(i,:)).*(Tsp_I(i,:)+V0).^2 + V0.^2);
end


%% Real Analysis
Tsp_R       = zeros(2,length(M));
f_R         = zeros(2,length(M));
eta_prop_R  = zeros(2,length(M));
pi_tmp          = zeros(2,length(M));
V4V0           = zeros(2,length(M));

% fuel air ratio - f = mdot_0 / mdot_f
for i = 1:length(Tburner)
    [cp3,~,~,~] = Cp(Tburner(i));
    [cp0,~,gamma0,~] = Cp(Tamb);
    f_R(i,:) = (cp3*Tburner(i) - cp0*Tamb*(1+(gamma0-1)/2*M.^2))/(Qr - cp3*Tburner(i));
end



for i = 1:length(Tburner)
    [~,~,gamma0,R0] = Cp(Tamb);
    [~,~,gamma4,R4] = Cp(Tburner(i));
    pi_tmp(i,:) = (1*Pi_star)^((gamma4-1)/gamma4)*(1+(gamma0-1)/2*M.^2).^((gamma4-gamma0)/(gamma4*(gamma0-1)));
    V4V0(i,:) = (gamma4*R4)/(gamma0*R0)*(Tburner(i)./(Tamb*(1+(gamma0-1)/2*M.^2))).*(1./pi_tmp(i,:))*(2/(gamma4-1)).*((pi_tmp(i,:).*(1+(gamma0-1)/2*M.^2))-1)./M.^2;
    Tsp_R(i,:) = a0*M.*((1+f_R(i,:)).*sqrt(V4V0(i,:))-1);
end

V0 = M*a0;                          % [m/s], Flight Velocity

for i = 1:length(Tburner)
    eta_prop_R(i,:) = (((1+f_R(i,:)).*(Tsp_R(i,:)+V0)   + V0).*V0)./ ...
        ((1+f_R(i,:)).*(Tsp_R(i,:)+V0).^2 + V0.^2);
end


%% Comparison Plots
fignum = fignum + 1;
if ishandle(fignum) == 0
    figure(fignum)
    plot(real(M),real(vertcat(Tsp_R,Tsp_I)));
    title('Real Tsp vs. Mach');
    xlabel('Mach'); ylabel('Tsp'); axis tight;
    xlim([1 4])
    legend('T_R = 2000 K','T_R = 2500 K','T_I = 2000 K','T_I = 2500 K','Location','Northeast');
end
fignum = fignum + 1;

if ishandle(fignum) == 0
    figure(fignum)
    plot(real(M),real(vertcat(eta_prop_R,eta_prop_I)));
    title('Real Propulsive Efficiency vs. Mach');
    xlabel('Mach'); ylabel('Propulsive Efficiency'); axis tight;
    xlim([1 4])
    legend('T_R = 2000 K','T_R = 2500 K','T_I = 2000 K','T_I = 2500 K','Location','Best');
end
fignum = fignum + 1;

if ishandle(fignum) == 0
    figure(fignum)
    plot(M,vertcat(f_R,f_I));
    title('Real Air-Fuel Ratio vs. Mach ');
    xlabel('Mach'); ylabel('AFR'); axis tight;
    xlim([1 4])
    legend('T_R = 2000 K','T_R = 2500 K','T_I = 2000 K','T_I = 2500 K','Location','Northeast');
end




