function w = stdAtmWind(w0,z0,z)
% STDATMWIND  Returns wind speed for a given altitude based on a wind
% speed at a baseline altitude. w0 can be a scalar or a vector.
% 
% Usage:
%  w = STDATMWIND(w0,z0,z)
%
%  Input:   w0 - base wind vector (can be scalar)
%           z0 - base altitude
%           z  - specified altitude
% Output:   w - wind vector (or scalar) at specified altitude
% 
%  Variable: [Units]
%       w0:  m/s
%       z0: [m] (geometric)
%        z: [m] (geometric)
%

w = w0*(z/z0)^0.1428;
end