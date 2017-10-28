function dy = shuttlefunc(t,y,m,theta)
% y = [px py vx vy]
dy = zeros(4,1);

mstate1 = Shuttle_External_Profile(t);
mstate2 = Shuttle_Solid_Profile(t);
m = m + mstate1(2) + mstate2(2);
T = mstate1(3) + mstate2(3);



% V = [y(3); y(4)]; %rocket velocity vector, what we actually care about

% V_unit = V/norm(V); % unit vector for apparent velocity
% if isnan(V_unit(1)) %very start
V_unit = [sind(theta);cosd(theta)];
% end
up = [0;1]; % vertical unit vector

dy(1) = y(3);
dy(2) = y(4);
dvdt = V_unit*T/m - up*g(R0+y(2));
dy(3) = dvdt(1);
dy(4) = dvdt(2);


end