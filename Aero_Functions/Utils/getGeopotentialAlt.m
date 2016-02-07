function alt_geopotential = getGeopotentialAlt(altitude)
% GETGEOPOTENTIALALT  Returns the geopotential altitude corresponding to a
% given geometric altitude
%
% Usage:
%  alt_geopotential = GEOMTOGEOPOT(altitude)
%
% GEOPOTENTIAL ALTITUDE:
% Geopotential altitude is an equivalent altitude if gravity were a 
% constant (g0) instead of varying with radius. This come from analysis of
% the hydrostatic equation.
%
% For more information, see <a href="matlab: 
% web('http://www.aerostudents.com/files/aerodynamicsA/relationsPressureHeight.pdf')">this online pdf</a>.
% 
% GEOMETRIC ALTITUDE:
% Geometric altitude is simply the altitude above sea level that would be
% measured if you had a really long measuring tape
%
%  Input: altitude
%  Output: alt_geopotential
% 
% Variable:         [Units]
% altitude:         [m] (geometric)
% alt_geopotential: [m] (geopotential)
% 
% See also GETGEOPOTENTIALALT_ENGLISH

%Define earth's mean radius (NASA standard)
r = 6.371e6;  %meters

%calculate geopotential height
alt_geopotential = altitude*r/(r+altitude);


end