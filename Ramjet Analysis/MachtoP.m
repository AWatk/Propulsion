function [M,Pratio] = MachtoP(M,Pratio)
% Create a polynomial fit between Ma and the stagnation pressure ratios
p = polyfit(M,Pratio,3);
Ma_int = 1:0.1:4;
Pratio = p(1)*Ma_int.^3+p(2)*Ma_int.^2+p(3)*Ma_int.^1+p(4);
Ma_int = horzcat(0,Ma_int);
Pratio = horzcat(1,Pratio);
M = Ma_int;
if ishandle(2) == 0
    figure(2)
    plot(Ma_int,Pratio);
    axis([0 4 0 1.01]);
    title('Stagnation Pressure Ratio vs. Ma');
    xlabel('Ma'); ylabel('Stagnation Pressure Ratio'); axis tight;
else end
end
