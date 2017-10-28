function dy = testfunc2(t,y)
% y = [px py vx vy theta omega]
dy = zeros(5,1);
rho = 1.23*((288-0.0065*y(2))/288)^4.25;
theta = y(5);

if theta > 180
    theta = mod(theta,180);
end
if theta >90
    theta = 180 - theta;
end

cda = -7.99e-07*theta^3 + 1.07e-4*theta^2 +1.19e-03*theta + 1.16e-02;

%geometry
l = 2.5;

m = 15;

M = 5*0.307; %thrust times moment arm

V = [y(3); y(4)]; %rocket velocity vector, what we actually care about
Vapp = V; % Apparent velocity vector
Vapp_unit = Vapp/norm(Vapp); % unit vector for apparent velocity
if isnan(Vapp_unit(1))
    Vapp_unit = [0;1]; 
end
Vnorm = norm(Vapp);
up = [0;1]; % vertical unit vector

dy(1) = y(3);
dy(2) = y(4);
dvdt = Vapp_unit*( -0.5*cda*rho*Vnorm^2)/m - up*g(R0+y(2));
dy(3) = dvdt(1);
dy(4) = dvdt(2);
dy(5) = y(6);
dy(6) = (12*M/(m*l^2))*(180/pi);
% dy(6) = 0;


end