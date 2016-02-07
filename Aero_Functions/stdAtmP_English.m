function P = stdAtmP_English(altitude)
% STDATMP_ENGLISH  Returns pressure as a function of altitude for the standard
% Earth atmosphere model. The function is based on linear interpolation of 
% temperature boundary conditions within the atmosphere
% NOTE: This function returns English units
%
% Usage:
%  P = STDATMP_ENGLISH(altitude)
% 
%  Input: altitude
% Output: P
% 
%  Variable: [Units]
%         P: [lb/ft^2]
%  altitude: [ft] (geometric)
%
% See also STDATMP, STDATMD_ENGLISH, STDATMT_ENGLISH

%instead of replicating code for the english version, just convert altitude
%to meters and use the metric version
P = stdAtmP(0.3048*altitude);

%convert the metric output to english
P = P * (2116.2)/(1.01325e5); % converion factor is (english)/(metric)

end