function P = stdAtmP_GeoPotential(altitude)
% STDATMP_GEOPOTENTIAL Returns pressure as a function of altitude for the 
% standard Earth atmosphere model. The function is based on the hydrostatic
% equation and a linear interpolation of temperature boundary conditions 
% within the atmosphere.
% NOTE: THIS FUNCTION REQUIRES GEOPOTENTIAL ALTITUDE INSTEAD OF GEOMETRIC!
%
% For more information, see <a href="matlab: 
% web('http://www.aerostudents.com/files/aerodynamicsA/relationsPressureHeight.pdf')">this online pdf</a>.
%
% USAGE:
%  P = STDATMP_GEOPOTENTIAL(altitude)
%
%  Input: altitude
%  Output: P
% 
%  Variable: [Units]
%         T: [K]
%  altitude: [m] (geopotential)
%         P: [Pa]
%
% See also STDATMP, STDATMD_GEOPOTENTIAL, STDATMT_GEOPOTENTIAL

if altitude < 0 || altitude > 105000
    error('stdAtmP_GeoPotential:InvalidAltitude',...
        'Input Altitude, %0.1f, is not within the valid range of [0,%0.1f]',...
        altitude, 105000);
end

g0 = 9.81;           % [m/s^2] gravity at sea level
R = 287.058;         % [J/(kg*K)] gas constant for air
P_sealevel = 101325; % [Pa] pressure at sea level

% Initial condition for pressure to end recursive calls
if altitude == 0
    P = P_sealevel;
    return;
end

% List of atmosphere sections where temperature is defined
altList = [0 11000 25000 47000 53000 79000 90000 105000];

% Calculate P1 using P0, T0, T1, the hydrostatic equation, and the equation
% of state (see description and link at top of file)
for i=2:length(altList)
    
    %finds where the altitude is located within altList defined above
    if altitude <= altList(i) 
                              
        %define altitude at which to calculate T0,P0                      
        alt0 = altList(i-1); 
        
        %Makes use of recursion to calculate P0 and T0
        P0 = stdAtmP_GeoPotential(alt0);
        T0 = stdAtmT_GeoPotential(alt0);
        
        %Calculates T1 based on linear interpolation (see stdAtmT_GeoPotential)
        T1 = stdAtmT_GeoPotential(altitude);
        
        if T1-T0 == 0   % Case 1: Altitude is in isotherm
            P = P0*exp(-(g0/(R*T1))*(altitude-alt0));
        else            % Case 2: Altitude is in a gradient temp. layer
            a = (T1-T0)/(altitude-alt0);
            P = P0 * (T1/T0)^(-g0/(a*R));
        end
        return; %exit the for loop early
    end
end
end