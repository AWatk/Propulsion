function T = stdAtmT_English(altitude)
% STDATMT_ENGLISH returns temperature as a function of altitude for the standard
% Earth atmosphere model. The function is based on linear interpolation of 
% temperature boundary conditions within the atmosphere
% NOTE: This function is in English units
% 
% Usage:
%  T = STDATMT_ENGLISH(altitude)
%
%  Input: altitude
% Output: T
% 
% Variable: [Units]
% altitude: [ft] (geometric)
%        T: [R] 
%
% See also STDATMT, STDATMD_ENGLISH, STDATMP_ENGLISH

%instead of replicating code for the english version, just convert altitude
%to meters and use the metric version
T = stdAtmT(0.3048*altitude);

%convert the metric output to english
T = T * (518.69)/(288.16); % converion factor is (english)/(metric)

end