function state = H202_Profile(varargin)
% H202_PROFILE() Returns a NX2 array containing time (s), mass, and 
% thrust (N) values for a Cesaroni L1720 solid rocket motor. Each row is in
% the form [time, mass, thrust].
% 
% H202_PROFILE(T) Returns the mass (kg) thrust value (N) at a specific time
% T (s) in the form of [time,mass, thrust];

% NOTE: The last time stamp is an absurdly large number for time and 0 for
% thrust so that the thrust for any given time after ignition can be
% calculated using a simple linear interpolation function.

% time = [0:1:9,1e20];
% mass = [0.16, 0.16:-0.02:0, 0];
% thrust = zeros(1,11);
time = [0,2,4.5,1e20];
mass = [.5/2.2, .5/2.2, 0, 0];
thrust = [0, 0, 0, 0];
t = [time',mass', thrust'];
 
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