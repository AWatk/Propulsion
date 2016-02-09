function g = g(r)
% Calculates local gravity based on radius

% Define gravity at earth's surface
g0 = 9.81; % m/s2
% Define earth's mean radius (NASA standard)
R0 = 6.371e6;  % m

if r < R0
    g = g0;
else
    g = g0*R0^2/r^2;
end

end