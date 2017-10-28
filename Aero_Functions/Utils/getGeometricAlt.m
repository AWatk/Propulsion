function alt_geometric = getGeometricAlt(altitude)
% GETGEOMETRICALT  Returns the geopotential altitude corresponding to a
% given geometric altitude
%
% Usage:
%  alt_geopotential = GETGEOMETRICALT(altitude)
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
%  Output: alt_geometric
% 
% Variable:         [Units]
% altitude:         [m] (geopotential)
% alt_geopotential: [m] (geometric)
% 
% See also GETGEOMETRICALT_ENGLISH

%Define earth's mean radius (NASA standard)
r = R0;  %meters

%calculate geometric height
alt_geometric = -(r*altitude)/(altitude-r);


end