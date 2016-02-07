function rho = stdAtmD_English(altitude)
% STDATMD  Returns density as a function of altitude for the standard
% Earth atmosphere model. The function is based on linear interpolation of 
% temperature boundary conditions within the atmosphere
% NOTE: This function returns English units
% 
% Usage:
%  rho = STDATMD_ENGLISH(altitude)
%
%  Input: altitude
% Output: rho
% 
%  Variable: [Units]
%       rho: [slug/ft^3]
%  altitude: [ft] (geometric)
%
% See also STDATMD, STDATMP_ENGLISH, STDATMT_ENGLISH

%instead of replicating code for the english version, just convert altitude
%to meters and use the metric version
rho = stdAtmD(0.3048*altitude);

%convert the metric output to english
rho = rho * (0.002377/1.2250); % converion factor is (english)/(metric)

end