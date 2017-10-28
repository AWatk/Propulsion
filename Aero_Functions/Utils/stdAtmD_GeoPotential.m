function rho = stdAtmD_GeoPotential(altitude)
% STDATMD_GEOPOTENTIAL Returns density as a function of altitude for the 
% standard Earth atmosphere model. The function is based on the hydrostatic
% equation and a linear interpolation of temperature boundary conditions 
% within the atmosphere.
% NOTE: THIS FUNCTION REQUIRES GEOPOTENTIAL ALTITUDE INSTEAD OF GEOMETRIC!
%
% For more information, see <a href="matlab: 
% web('http://www.aerostudents.com/files/aerodynamicsA/relationsPressureHeight.pdf')">this online pdf</a>.
%
% USAGE:
%  rho = STDATMD_GEOPOTENTIAL(altitude)
%
%  Input: altitude
%  Output: rho
% 
%  Variable: [Units]
%         T: [K]
%  altitude: [m] (geopotential)
%         P: [Pa]
%       rho: [kg/m^3] 
%
% See also STDATMD, STDATMP_GEOPOTENTIAL, STDATMT_GEOPOTENTIAL
% if altitude <0 
%     altitude = 0;
% elseif altitude > 105000
if altitude < 0 || altitude > 105000
    error('stdAtmD_GeoPotential:InvalidAltitude',...
        'Input Altitude, %0.1f, is not within the valid range of [0,%0.1f]',...
        altitude, 105000);
end

rho_sea_level = 1.225;  % [kg/m^3] 
g0 = 9.81;              % [m/s^2] gravity at sea level
R = 287.058;            % [J/(kg*K)] gas constant for air

% Initial condition for density to end recursion
if altitude == 0
    rho = rho_sea_level;
    return;
end

% List of atmosphere sections where temperature is defined
altList = [0 11000 25000 47000 53000 79000 90000 105000];

% Calculate rho1 using rho0, T0, T1, the hydrostatic equation, and the
% equation of state (see description and link at top of file)
for i=2:length(altList)
    
    %finds where the altitude is located within altList defined above
    if altitude <= altList(i)
        
        %define altitude at which to calculate T0,rho0
        alt0 = altList(i-1);
        
        %Makes use of recursion to calculate rho0 and T0
        rho0 = stdAtmD_GeoPotential(alt0);
        T0 = stdAtmT_GeoPotential(alt0);
        
        %Calculates T1 based on linear interpolation (see stdAtmT_GeoPotential)
        T1 = stdAtmT_GeoPotential(altitude);      
        
        if T1-T0 == 0   % Case 1: Altitude is in isotherm
            rho = rho0*exp(-(g0/(R*T1))*(altitude-alt0));
        else            % Case 2: Altitude is in a gradient
            a = (T1-T0)/(altitude-alt0);
            rho = rho0 * (T1/T0)^(-(g0/(a*R)+1));
        end
        return; %exit the for loop early
    end
end
end