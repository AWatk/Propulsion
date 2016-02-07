function T = stdAtmT_GeoPotential(altitude)
% STDATMT_GEOPOTENTIAL Returns temperature as a function of altitude for 
% the standard Earth atmosphere model. The function is based on a linear 
% interpolation of temperature boundary conditions within the atmosphere.
% NOTE: THIS FUNCTION REQUIRES GEOPOTENTIAL ALTITUDE INSTEAD OF GEOMETRIC!
%
% For more information, see <a href="matlab: 
% web('http://www.aerostudents.com/files/aerodynamicsA/relationsPressureHeight.pdf')">this online pdf</a>.
%
% USAGE:
%  T = STDATMT_GEOPOTENTIAL(altitude)
%
%  Input: altitude
%  Output: T
% 
%  Variable: [Units]
%         T: [K]
%  altitude: [m] (geopotential)
%
% See also STDATMT, STDATMP_GEOPOTENTIAL, STDATMD_GEOPOTENTIAL

if altitude < 0 || altitude > 105000
    error('stdAtmT_GeoPotential:InvalidAltitude',...
        'Input Altitude, %0.1f, is not within the valid range of [0,%0.1f]',...
        altitude, 105000);
end

% Sections of the atmosphere based on temperature profile
altList = {};
altList{1} = {0, 288.16};
altList{2} = {11000, 216.66};
altList{3} = {25000, 216.66};
altList{4} = {47000, 282.66};
altList{5} = {53000, 282.66};
altList{6} = {79000, 165.66};
altList{7} = {90000, 165.66};
altList{8} = {105000, 225.66};

% Interpolation of Temperature based on altitude
for i=1:length(altList)
    if altitude <= altList{i}{1}
        if altitude == altList{i}{1}
            T = altList{i}{2};
        else
            T0 = altList{i-1}{2};
            T1 = altList{i}{2};
            alt0 = altList{i-1}{1};
            alt1 = altList{i}{1};
            a = (T1-T0)/(alt1-alt0);
            T = T0 + a*(altitude-alt0);
        end
        return;
    end
end
end