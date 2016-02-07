function T = stdAtmT(altitude)
% STDATMT  Returns temperature as a function of altitude for the standard
% Earth atmosphere model. The function is based on linear interpolation of 
% temperature boundary conditions within the atmosphere
% 
% Usage:
%  T = STDATMT(altitude)
%
%  Input: altitude
%  Output: T
% 
%  Variable: [Units]
%         T: [K]
%  altitude: [m] (geometric)
%
% See also STDATMT_ENGLISH, STDATMD, STDATMP

%return the equivalent geopotential altitude for a given geometric(true)
%altitude
alt_geopotential = getGeopotentialAlt(altitude);

%calculate T based on standard model
T = stdAtmT_GeoPotential(alt_geopotential);

end