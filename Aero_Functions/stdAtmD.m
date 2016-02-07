function rho = stdAtmD(altitude)
% STDATMD  Returns density as a function of altitude for the standard
% Earth atmosphere model. The function is based on linear interpolation of 
% temperature boundary conditions within the atmosphere
% 
% Usage:
%  rho = STDATMD(altitude)
%
%  Input: altitude
% Output: rho
% 
%  Variable: [Units]
%       rho: [kg/m^3]
%  altitude: [m] (geometric)
%
% See also STDATMD_ENGLISH, STDATMP, STDATMT

%return the equivalent geopotential altitude for a given geometric(true)
%altitude
alt_geopotential = getGeopotentialAlt(altitude);

%calculate P based on standard model
rho = stdAtmD_GeoPotential(alt_geopotential);

end