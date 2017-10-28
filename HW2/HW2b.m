%% Dexter Watkins  Propulsion - Homework 2

%% Problem Definition
% Calculate apogee and drift at apogee as a function of side wind speed for
% a rocket from launch until apogee. Use a numerical method to solve this
% problem.  Examine the following four cases.
%
% # Side winds of (5,15,25 m/s) start after main engine cutoff and are constant
% # Same as above but the sidewinds are now amplified via the Atm BL
% # Same as above, but the side winds now start at rail exit (V_r = 30 m/s)
% # Same as above but the rocket now launches 5 degress into the wind
%
%% Specified Properties and Assumptions
% 
% # Rocket has a dry mass of 14.34 kg
% # The rocket has a cross-sectional area of 0.015327 square meters
% # The rocket has a drag coefficient of 0.45
% # The main motor follows the properties of the Cesaroni L1720
% # The Mono-Props are 0.08 kg each, with a mass flux of 0.01 kg/s each
% # The Mono-Props produce no thrust
% 
%% Governing Equations
% The equation of motion for the flight vehicle is determined by the
% following system of equations:
%
% $$\mathbf{P''} = (Thrust - 0.5*C_d*\rho*Area*norm(\mathbf{P'})^2)\hat{V} - (m*g)\hat{up}$$
% $$m' = \sum(m'_{fired-thrusters})$$
%
% For easier use, the system of equations is rewritten as a system of
% purely first order equations, as follows:
%
  
%% Define rocket and wind properties

cd = 0.45;

area = 0.015327; %m2

dryMass = 15.108; %kg

% rho = @(z) stdAtmD(z);
% ws = @(w0,z0,z) stdAtmWind(w0,z0,z);



%% Execute Simulation
tspan = [0 30];
time = tspan(1):0.01:tspan(2);
windspeed = [0 5 25]*0.44704; %mph to m/s
y0 = [0 0 0 0 0]';
cases = [6,7,8,9];
y6 = cell(length(cases),length(windspeed));
yp6 = y6;
x = cell(1,length(cases));
for j = 1:1:length(cases)
    for i = 1:1:length(windspeed)
        sol = ode45(@(t,y) func6(t,y,windspeed(i),cd,area,dryMass,cases(j)),...
            tspan,y0);
        [y6{j,i}, yp6{j,i}] = deval(sol,time);
    end
    x{i} = time(y6{j,i}(4,:)>=0);
end


%% Case 6 Analysis
% Introducing wind after MECO has very little effect. Apogee is nearly
% completely the same.  A small amount of drift <50 meters is seen at
% higher wind speeds.

curcase = 1;
titles = cell(1,length(cases));
for i = 1:length(cases)
   titles{i} = ['Case ' num2str(i+5)]; 
end
figure()
figlegend = cell(1,length(windspeed));
data = cell(1,2*length(windspeed));
for i = 1:length(windspeed)
    data{2*i-1} = time(y6{curcase,i}(4,:)>=0);
    data{2*i} = y6{curcase,i}(2,y6{curcase,i}(4,:)>=0);
    figlegend{i} = ['Windspeed = ' num2str(windspeed(i)) ' mph'];
end
plot(data{:});
xlabel('Time (s)');
ylabel('Vertical Position (m)');
legend(figlegend,'Location', 'SouthEast');
title(titles{curcase});

figure()
figlegend = cell(1,length(windspeed));
data = cell(1,2*length(windspeed));
for i = 1:length(windspeed)
    data{2*i-1} = time(y6{curcase,i}(4,:)>=0);
    data{2*i} = y6{curcase,i}(1,y6{curcase,i}(4,:)>=0);
    figlegend{i} = ['Windspeed = ' num2str(windspeed(i)) ' mph'];
end
plot(data{:});
xlabel('Time (s)');
ylabel('Horizontal Position (m)');
legend(figlegend,'Location', 'NorthWest');
title(titles{curcase});

figure()
figlegend = cell(1,length(windspeed));
data = cell(1,2*length(windspeed));
for i = 1:length(windspeed)
    data{2*i-1} = y6{curcase,i}(1,y6{curcase,i}(4,:)>=0);
    data{2*i} = y6{curcase,i}(2,y6{curcase,i}(4,:)>=0);
    figlegend{i} = ['Windspeed = ' num2str(windspeed(i)) ' mph'];
end
plot(data{:});
xlabel('Horizontal Position (m)');
ylabel('Vertical Position (m)');
legend(figlegend,'Location', 'SouthEast');
title(titles{curcase});

%% Case 7 Analysis
% Adding in wind amplification via the atmospheric boundary layer still did
% not affect apogee, but did increase drift up to 80m depending on the base
% wind speed that was set.

curcase = 2;
figure()
figlegend = cell(1,length(windspeed));
data = cell(1,2*length(windspeed));
for i = 1:length(windspeed)
    data{2*i-1} = time(y6{curcase,i}(4,:)>=0);
    data{2*i} = y6{curcase,i}(2,y6{curcase,i}(4,:)>=0);
    figlegend{i} = ['Windspeed = ' num2str(windspeed(i)) ' mph'];
end
plot(data{:});
xlabel('Time (s)');
ylabel('Vertical Position (m)');
legend(figlegend,'Location', 'SouthEast');
title(titles{curcase});

figure()
figlegend = cell(1,length(windspeed));
data = cell(1,2*length(windspeed));
for i = 1:length(windspeed)
    data{2*i-1} = time(y6{curcase,i}(4,:)>=0);
    data{2*i} = y6{curcase,i}(1,y6{curcase,i}(4,:)>=0);
    figlegend{i} = ['Windspeed = ' num2str(windspeed(i)) ' mph'];
end
plot(data{:});
xlabel('Time (s)');
ylabel('Horizontal Position (m)');
legend(figlegend,'Location', 'NorthWest');
title(titles{curcase});

figure()
figlegend = cell(1,length(windspeed));
data = cell(1,2*length(windspeed));
for i = 1:length(windspeed)
    data{2*i-1} = y6{curcase,i}(1,y6{curcase,i}(4,:)>=0);
    data{2*i} = y6{curcase,i}(2,y6{curcase,i}(4,:)>=0);
    figlegend{i} = ['Windspeed = ' num2str(windspeed(i)) ' mph'];
end
plot(data{:});
xlabel('Horizontal Position (m)');
ylabel('Vertical Position (m)');
legend(figlegend,'Location', 'SouthEast');
title(titles{curcase});

%% Case 8 Analysis
% Introducing side winds at the launch rail instead of after MECO resulted
% in a drastic change in behavior.  Instead of drifting WITH the wind as
% the rockets do in the earlier cases, the rocket now drifts INTO the wind.
% Additionally, since the rocket is going at a slower speed and is still
% thrusting when it turns into the wind, the drift is drastically higher,
% and the apogee lower.  Apogee peaks at 1639 m, with a corresponding drift
% of 218 m, while drift peaks at 903 m with a corresponding apogee of 1399.

curcase = 3;
figure()
figlegend = cell(1,length(windspeed));
data = cell(1,2*length(windspeed));
for i = 1:length(windspeed)
    data{2*i-1} = time(y6{curcase,i}(4,:)>=0);
    data{2*i} = y6{curcase,i}(2,y6{curcase,i}(4,:)>=0);
    figlegend{i} = ['Windspeed = ' num2str(windspeed(i)) ' mph'];
end
plot(data{:});
xlabel('Time (s)');
ylabel('Vertical Position (m)');
legend(figlegend,'Location', 'SouthEast');
title(titles{curcase});

figure()
figlegend = cell(1,length(windspeed));
dataxx = cell(1,2*length(windspeed));
for i = 1:length(windspeed)
    dataxx{2*i-1} = time(y6{curcase,i}(4,:)>=0);
    dataxx{2*i} = y6{curcase,i}(1,y6{curcase,i}(4,:)>=0);
    figlegend{i} = ['Windspeed = ' num2str(windspeed(i)) ' mph'];
end
plot(dataxx{:});
xlabel('Time (s)');
ylabel('Horizontal Position (m)');
legend(figlegend,'Location', 'SouthWest');
title(titles{curcase});

figure()
figlegend = cell(1,length(windspeed));
data = cell(1,2*length(windspeed));
for i = 1:length(windspeed)
    data{2*i-1} = y6{curcase,i}(1,y6{curcase,i}(4,:)>=0);
    data{2*i} = y6{curcase,i}(2,y6{curcase,i}(4,:)>=0);
    figlegend{i} = ['Windspeed = ' num2str(windspeed(i)) ' mph'];
end
plot(data{:});
xlabel('Horizontal Position (m)');
ylabel('Vertical Position (m)');
legend(figlegend,'Location', 'SouthWest');
title(titles{curcase});

%% Case 9 Analysis
% Launching with a launch rail located 5 degrees into the wind further
% decreased apogee and increased apogee drift, with a new peak apogee of
% 1606 m and a peak drift of 1076 m.

% curcase = 4;
% figure()
% figlegend = cell(1,length(windspeed));
% vposdata = cell(1,2*length(windspeed));
% for i = 1:length(windspeed)
%     vposdata{2*i-1} = time(y6{curcase,i}(4,:)>=0);
%     vposdata{2*i} = y6{curcase,i}(2,y6{curcase,i}(4,:)>=0);
%     figlegend{i} = ['Windspeed = ' num2str(windspeed(i)/0.44704) ' mph'];
% end
% plot(vposdata{:});
% xlabel('Time (s)');
% ylabel('Vertical Position (m)');
% legend(figlegend,'Location', 'SouthEast');
% title(titles{curcase});
% 
% figure()
% figlegend = cell(1,length(windspeed));
% hposdata = cell(1,2*length(windspeed));
% for i = 1:length(windspeed)
%     hposdata{2*i-1} = time(y6{curcase,i}(4,:)>=0);
%     hposdata{2*i} = y6{curcase,i}(1,y6{curcase,i}(4,:)>=0);
%     figlegend{i} = ['Windspeed = ' num2str(windspeed(i)/0.44704) ' mph'];
% end
% plot(hposdata{:});
% xlabel('Time (s)');
% ylabel('Horizontal Position (m)');
% legend(figlegend,'Location', 'SouthWest');
% title(titles{curcase});
% 
% figure()
% figlegend = cell(1,length(windspeed));
% veldata = cell(1,2*length(windspeed));
% for i = 1:length(windspeed)
%     veldata{2*i-1} = time(y6{curcase,i}(4,:)>=0);
%     veldata{2*i} = sqrt(y6{curcase,i}(4,y6{curcase,i}(4,:)>=0).^2 + y6{curcase,i}(3,y6{curcase,i}(4,:)>=0).^2);
%     figlegend{i} = ['Windspeed = ' num2str(windspeed(i)/0.44704) ' mph'];
% end
% plot(veldata{:});
% xlabel('Time (s)');
% ylabel('Vertical Velocity (m)');
% legend(figlegend,'Location', 'SouthWest');
% title(titles{curcase});
% 
% figure()
% massdata = cell(1,2*length(windspeed));
% for i = 1:length(windspeed)
%     massdata{2*i-1} = time(y6{curcase,i}(4,:)>=0);
%     massdata{2*i} = yp6{curcase,i}(5,y6{curcase,i}(4,:)>=0);
%     figlegend{i} = ['Windspeed = ' num2str(windspeed(i)/0.44704) ' mph'];
% end
% tmp = massdata{:,2};
% tmp(454:end) = tmp(453);
% massdata{:,2} = tmp
plot(massdata{:})
