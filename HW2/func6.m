function dy = func6(t,y,ws,cd,a,m,scenario)
% y = [px py vx vy m]
dy = zeros(4,1);
rho = stdAtmD(y(2));

% mstate1 = L1720_Profile(t);
mstate1 = L1720_Profile_Basic(t);
mstate2 = H202_Profile(t);
m = m + mstate1(2) + mstate2(2);
dy(5) = m;
T = mstate1(3) + mstate2(3);


switch scenario
    case 6
        if t < 2.13
            ws = [0; 0];
        else
            ws = [ws; 0];
        end
    case 7
        if t < 2.13
            ws = [0;0];
        else
            ws = [stdAtmWind(ws,10,y(2));0];
        end
    case 8
        if y(4) < 30
            ws = [0;0];
        else
            ws = [stdAtmWind(ws,10,y(2));0];
        end
    case 9
        if y(4) < 30
            ws = [0;0];
        else
            ws = [stdAtmWind(ws,10,y(2));0];
        end
end

V = [y(3); y(4)]; %rocket velocity vector, what we actually care about
switch scenario
    case 9
        if y(4) < 30 && t < 2
            tmp = norm(V);
            V(1) = -sind(5)*tmp;
            V(2) = cosd(5)*tmp;           
        end
end
Vapp = V - ws; % Apparent velocity vector
Vapp_unit = Vapp/norm(Vapp); % unit vector for apparent velocity
if isnan(Vapp_unit)
    Vapp_unit = [0;1]; 
end
Vnorm = norm(Vapp);
up = [0;1]; % vertical unit vector

dy(1) = y(3);
dy(2) = y(4);
dvdt = Vapp_unit*(T - 0.5*cd*rho*a*Vnorm^2)/m - up*g(R0+y(2));
dy(3) = dvdt(1);
dy(4) = dvdt(2);


end