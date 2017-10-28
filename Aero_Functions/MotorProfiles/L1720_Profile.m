function state = L1720_Profile(varargin)
% L1720_PROFILE() Returns a NX2 array containing time (s), mass, and 
% thrust (N) values for a Cesaroni L1720 solid rocket motor. Each row is in
% the form [time, mass, thrust].
% 
% L1720_PROFILE(T) Returns the mass (kg) thrust value (N) at a specific time
% T (s) in the form of [time,mass, thrust];

% NOTE: The last time stamp is an absurdly large number for time and 0 for
% thrust so that the thrust for any given time after ignition can be
% calculated using a simple linear interpolation function.

t = [%Time  Mass(kg)        Thrust (N)
     -1e20,  1.755,          0;
      0-1e-99,    1.755,           0;
      0,     1.755,          1840;
     0.01,  1.75491,        1840;
     0.02,  1.75241,        1840.85;
     0.03,  1.74557,        1840.85;
     0.04,  1.73657,        1946.7;
     0.05,  1.72759,        1836.31;
     0.06,  1.71906,        1754.4;
     0.07,  1.7108,         1728.19;
     0.08,  1.70273,        1667.95;
     0.09,  1.69493,        1617.8;
     0.1,   1.6873,         1596.63;
     0.2,   1.60806,        1740.64;
     0.3,   1.5257,         1727.93;        
     0.4,   1.44265,        1769.77;
     0.5,   1.35728,        1825.98;
     0.6,   1.26967,        1863.53;
     0.7,   1.18025,        1902.59;
     0.8,   1.08923,        1930.57;
     0.9,   0.997656,       1926.28;
     1.0,   0.90639,        1917.46;
     1.1,   0.81638,        1873.36;
     1.2,   0.728455,       1829.67;
     1.3,   0.641416,       1836.03;
     1.4,   0.554932,       1806.32;
     1.5,   0.46959,        1787.92;
     1.6,   0.385451,       1755.66;
     1.7,   0.302754,       1727.18;
     1.8,   0.221499,       1694.82;
     1.9,   0.140932,       1698.19;
     2.0,   0.0595941,      1727.43;
     2.02,  0.0431326,      1739.02;
     2.04,  0.0270803,      1641.24;
     2.05,  0.0196131,      1503.63;
     2.08,  0.00493302,     557.24;
     2.1,   0.0014358,      179.2;
     2.12,  0.000181493,    84.93;
     2.13,  0,              0;
     1e20,  0,              0;
     ];
 
 if isempty(varargin) 
     state = t;
 elseif length(varargin) == 1
     time = varargin{1};
    mass = interp1(t(:,1),t(:,2),time);
    thrust = interp1(t(:,1),t(:,3),time);
    state = [time', mass', thrust'];
 else
     error('Wrong number of inputs');
 end

end