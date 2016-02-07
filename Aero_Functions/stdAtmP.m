function P = stdAtmP(altitude)
% STDATMP  Returns pressure as a function of altitude for the standard
% Earth atmosphere model. The function is based on linear interpolation of 
% temperature boundary conditions within the atmosphere
%
% For more information, see <a href="matlab: 
% web('http://www.aerostudents.com/files/aerodynamicsA/relationsPressureHeight.pdf')">this online pdf</a>.
%
% Usage:
%  P = STDATMP(alt)
% 
%  Input: altitude
%  Output: P
% 
%  Variable: [Units]
%         P: [N/m^2]
%  altitude: [m] (geometric)
%
% See also STDATMP_ENGLISH, STDATMD, STDATMT

%return the equivalent geopotential altitude for a given geometric(true)
%altitude
alt_geopotential = getGeopotentialAlt(altitude);

%calculate P based on standard model
P = stdAtmP_GeoPotential(alt_geopotential);

end