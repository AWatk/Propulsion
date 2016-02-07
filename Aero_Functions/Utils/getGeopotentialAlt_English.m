function alt_geopotential = getGeopotentialAlt_English(altitude)
% GETGEOPOTENTIALALT_ENGLISH  Returns the geopotential altitude
% corresponding to a given geometric altitude
% NOTE: This function returns English units
%
% Usage:
%  alt_geopotential = GEOMTOGEOPOT_ENGLISH(altitude)
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
% altitude:         [ft] (geometric)
% alt_geopotential: [ft] (geopotential)
% 
% See also GETGEOPOTENTIALALT

%instead of replicating code for the english version, just convert altitude
%to meters and use the metric version
alt_geopotential = getGeopotentialAlt(0.3048*altitude);

%convert the metric output to english
alt_geopotential = alt_geopotential / 0.3048; 

end