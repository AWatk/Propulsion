function alt_geometric = getGeometricAlt_English(altitude)
% GETGEOMETRICALT  Returns the geopotential altitude corresponding to a
% given geometric altitude
% NOTE: This function returns English units
%
% Usage:
%  alt_geopotential = GETGEOMETRICALT_ENGLISH(altitude)
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
% altitude:         [ft] (geopotential)
% alt_geopotential: [ft] (geometric)
% 
% See also GETGEOMETRICALT

%instead of replicating code for the english version, just convert altitude
%to meters and use the metric version
alt_geometric = getGeometricAlt(0.3048*altitude);

%convert the metric output to english
alt_geometric = alt_geometric / 0.3048; 


end