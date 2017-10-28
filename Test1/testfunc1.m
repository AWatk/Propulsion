function dy = testfunc1(t,y,ws,cd)
% y = [px py vx vy]
dy = zeros(4,1);
rho = 1.23*((288-0.0065*y(2))/288)^4.25;

%geometry
l = 2.5;
d = 0.14;
a = 0.25*pi*d^2;

m = 15;
ws = [ws; 0];
V = [y(3); y(4)]; %rocket velocity vector, what we actually care about
Vapp = V - ws; % Apparent velocity vector
Vapp_unit = Vapp/norm(Vapp); % unit vector for apparent velocity
if isnan(Vapp_unit(1))
    Vapp_unit = [0;1]; 
end
Vnorm = norm(Vapp);
up = [0;1]; % vertical unit vector

dy(1) = y(3);
dy(2) = y(4);
dvdt = Vapp_unit*( -0.5*cd*rho*a*Vnorm^2)/m - up*g(R0+y(2));
dy(3) = dvdt(1);
dy(4) = dvdt(2);


end