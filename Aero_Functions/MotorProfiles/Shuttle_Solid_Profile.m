function state = Shuttle_Solid_Profile(varargin)
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
     0,     1170000,        24000000;
     120,   164000,         24000000;
     120+1e-12,   0,              0;
     1e20,  0,              0;
     ];
 
 if isempty(varargin) 
     state = t;
 elseif length(varargin) == 1
     time = varargin{1};
    mass = interp1(t(:,1),t(:,2),time);
    thrust = interp1(t(:,1),t(:,3),time);
    state = [time, mass, thrust];
 else
     error('Wrong number of inputs');
 end

end