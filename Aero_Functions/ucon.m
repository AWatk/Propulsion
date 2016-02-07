function newval = ucon(val, cU, dU)

cf = [ %primary dimensions list, order of LMFT
    3.28084,...  % ft/m
    2.20462,... % lbm/kg
    0.224809,...% lbf/N
    1.8,...     % R/K
    ];


cindex = {
    'm',       'ft',       cf(1);           %length
    'm/s',     'ft/s',     cf(1);           %velocity
    'm/s2',    'ft/s2',    cf(1);           %acceleration
    'm2',      'ft2',      cf(1)^2;         %area
    'm3',      'ft3',      cf(1)^3;         %volume
    'N',       'lbf',      cf(3);           %force
    'kg',      'lbm',      cf(2);           %mass
    'K',       'R',        cf(4);           %temperature
    'kg/m3',   'lbm/ft3',  cf(4)/cf(1)^3;   %density
    };


newval = val*getcf(cU, dU);

    function factor = getcf(cur,des)
       for c=cindex'
          if strcmp(cur,c{1}) && strcmp(des,c{2})
              factor = c{3};
              return
          elseif strcmp(cur,c{2}) && strcmp(des,c{1})
              factor = 1/c{3};
              return
          end
       end
       error('The unit conversion pair (%s,%s) is not supported',...
           cur,des);
    end


end