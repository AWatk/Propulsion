function [cp,cv,gamma,R] = Cp(temperature)


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
end