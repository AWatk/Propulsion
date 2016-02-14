classdef Vehicle < handle
    % Vehicle A vehicle with components such as thrusters,structures, etc.
    %   Vehicle in general is a container class for all vehicle
    %   subcomponents. For now, these subcomponents are either thrusters or
    %   structures.
    %   The Vehicle class is responsible for keeping track of
    %   the desired unit and coordinate system used, and for conglomerating
    %   properties from components such as mass, thrust generated, etc.
    %   Finally, the Vehicle class contains vehicle properties such as the
    %   state vector, cross-sectional area, drag coefficient, etc.
    
    properties
        name = 'vehicle';
        sv = zeros(1,9); % 1x9 3D state vector [position velocity acceleration] of CoM
        area = 0; % Cross-sectional area of vehicle
        cd = 0; % Drag coefficient of vehicle
        
        
    end
    
    properties(Dependent)
        Units % Unit system used (Metric, English)
        CoordinateSystem % Coordinate system used (Cartesian, Spherical)
        mass % Total mass of the vehicle
        mass_fuel % Total mass of fuel onboard the vehicle
        mass_flowrate % Total mass consumption rate
        thrust % Total thrust produced by vehicle
    end
    
    properties(SetAccess = private)
        Thrusters % Access point for thrusters in the vehicle READ ONLY
        Structures % Access point for structures in the vehicle READ ONLY
    end
       
    properties(Access = private)
        PrivateUnits = 'Metric';
        PrivateCoordinateSystem = 'Cartesian';
        ThrustersMap = containers.Map(); % Map of all thrusters on vehicle
        StructuresMap = containers.Map(); % Map of all structures on vehicle
        
    end
    
    properties(Access = private, Constant)
        ConversionFactors = [3.28084,...  % ft/m
            2.20462,... % lbm/kg
            0.224809,... % lbf/N
            1,... % unitless
            3.28084^2,... % ft^2/m^2
            ]; % Conversion factors for basic units
        
        UnitConversionIndex = ...,
            {'sv', 1;   % index of proper conversion factor
            'area', 5;
            'cd', 4;
            }
        ComponentsList = {
            'ThrustersMap',...
            'StructuresMap'
            };
    end
    
    methods
        
        %       Ctor******************************************************
        function obj = Vehicle(name,sv,area,cd,CS,Units)
            if nargin > 0
                switch(CS)
                    case 'Cartesian'
                    case 'Spherical'
                        obj.PrivateCoordinateSystem = CS;
                    otherwise
                        error('Vehicle:InvalidCoordinateSystem',...
                            'Coordinate System ''%s'' is not supported',...
                            CS);
                end
                switch(Units)
                    case 'Metric'
                    case 'English'
                        obj.PrivateUnits = Units;
                    otherwise
                        error('Vehicle:InvalidUnits',...
                            'Units ''%s'' is not supported', Units);
                end
                if ~ischar(name)
                    error('Component:InvalidValue',...
                        'Component name, %s, must be of type char',name);
                else
                    obj.name = name;
                end
                if ~isequal(size(sv),[1,9])
                    error('Vehicle:InvalidValue',...
                        'State vector must be 1x9 vector');
                else
                    obj.sv = sv;
                end
                if area <= 0
                    error('Vehicle:InvalidValue',...
                        'Vehicle area must be positive and nonzero');
                else
                    obj.area = area;
                end
                if cd < 0
                    error('Vehicle:InvalidValue',...
                        'Vehicle drag coefficient must be non-negative');
                else
                    obj.cd = cd;
                end
            end
        end
        %       /Ctor*****************************************************
        
        %       Get Functions*********************************************
        function units = get.Units(obj)
            units = obj.PrivateUnits;
        end
        
        function coordinatesystem = get.CoordinateSystem(obj)
            coordinatesystem = obj.PrivateCoordinateSystem;
        end
        
        function mass_fuel = get.mass_fuel(obj)
            mass_fuel = 0;
            for k=keys(obj.(obj.ComponentsList{1})) %ThrustersMap
                mass_fuel = mass_fuel + obj.(obj.ComponentsList{1})(k{1}).mass_fuel;
            end
        end
        
        function mass_flowrate = get.mass_flowrate(obj)
            mass_flowrate = 0;
            for k=keys(obj.(obj.ComponentsList{1})) %ThrustersMap
                mass_flowrate = mass_flowrate + obj.(obj.ComponentsList{1})(k{1}).mass_flowrate;
            end
        end
        
        function mass = get.mass(obj)
            mass = 0;
            %sum mass of components
            for c=obj.ComponentsList
                for k=keys(obj.(c{1}))
                    mass = mass + obj.(c{1})(k{1}).mass();
                end
            end
        end
        
        function thrust = get.thrust(obj)
            thrust = 0;
            for k=keys(obj.(obj.ComponentsList{1})) %ThrustersMap
                thrust = thrust + obj.(obj.ComponentsList{1})(k{1}).thrust;
            end
        end
        
        
        function thrusterlist = get.Thrusters(obj)
            %             if ~ischar(name)
            %                 error('Vehicle:InvalidValue',...
            %                     'The input value, %s, is not a valid name',name);
            %             end
            %             if isKey(obj.ThrustersMap,name)
            %                 thruster = obj.ThrustersMap(name);
            %             else
            %                 error('Vehicle:InvalidComponent',...
            %                     'There is no attached thruster named %s', name);
            %             end
            thrusterlist = obj.ThrustersMap;
        end
        
        function structurelist = get.Structures(obj)
            %             if ~ischar(name)
            %                 error('Vehicle:InvalidValue',...
            %                     'The input value, %s, is not a valid name',name);
            %             end
            %             if isKey(obj.StructuresMap,name)
            %                 structure = obj.StructuresMap(name);
            %             else
            %                 error('Vehicle:InvalidComponent',...
            %                     'There is no attached structure named %s', name);
            %             end
            structurelist = obj.StructuresMap;
        end
        
        %       /Get Functions********************************************
        
        %       Set Functions*********************************************
        function set.Units(obj,newUnits)
            switch(newUnits)
                case 'Metric'
                    if ~strcmp(obj.PrivateUnits, newUnits)
                        obj.PrivateUnits = newUnits;
                        convertPropertyUnits(obj,1./obj.ConversionFactors);
                    end
                case 'English'
                    if ~strcmp(obj.PrivateUnits, newUnits)
                        obj.PrivateUnits = newUnits;
                        convertPropertyUnits(obj,obj.ConversionFactors);
                    end
                otherwise
                    error('Vehicle:InvalidValue',...
                        'Units ''%s'' is not supported', newUnits);
            end
        end
        
        function set.CoordinateSystem(obj,newCS)
            switch(newCS)
                case 'Cartesian'
                    if ~strcmp(obj.PrivateCoordinateSystem, newCS)
                        convertPropertyCoordinates(obj,newCS);
                        obj.PrivateCoordinateSystem = newCS;
                    end
                case 'Spherical'
                    if ~strcmp(obj.PrivateCoordinateSystem, newCS)
                        convertPropertyCoordinates(obj,newCS);
                        obj.PrivateCoordinateSystem = newCS;
                    end
                    
                otherwise
                    error('Vehicle:InvalidValue',...
                        'Coordinate System ''%s'' is not supported',...
                        newCS);
            end
        end
        
        function set.sv(obj,sv)
            if ~isequal(size(sv),[1,9])
                error('Vehicle:InvalidValue',...
                    'State vector must be 1x9 vector');
            else
                obj.sv = sv;
            end
        end
        
        
        %       /Set Functions********************************************
        
        %       Additional Functions**************************************
        function attach(obj,component)
            if ~isa(component, 'Component')
                error('Vehicle:InvalidComponent',...
                    'Cannot attach the non-Component object of type %s',...
                    class(component));
            end
            component.CoordinateSystem = obj.CoordinateSystem;
            switch(class(component))
                case 'Thruster'
                    obj.ThrustersMap(component.name) = component;
                case 'Structure'
                    obj.StructuresMap(component.name) = component;
            end
        end
        function detach(obj,componentType, name)
            if nargin == 0
                %TODO add logic to detach all components
            else
                
                switch(componentType)
                    case 'Thruster'
                        if isKey(obj.ThrustersMap,name)
                            remove(obj.ThrustersMap,name);
                        else
                            error('Vehicle:InvalidValue',...
                                'The input value, %s, is not a valid name',name);
                        end
                        
                    case 'Structure'
                        if isKey(obj.StructuresMap,name)
                            remove(obj.StructuresMap,name);
                        else
                            error('Vehicle:InvalidValue',...
                                'The input value, %s, is not a valid name',name);
                        end
                        
                    otherwise
                        error('Vehicle:Component',...
                            '%s is not a valid component type', componentType);
                end
            end
        end
        
        function fireThruster(obj,name)
            if ~ischar(name)
                error('Vehicle:InvalidValue',...
                    'The input value, %s, is not a valid name',name);
            end
            if isKey(obj.ThrustersMap,name)
                thruster = obj.ThrustersMap(name);
            else
                error('Vehicle:InvalidComponent',...
                    'There is no attached thruster named %s', name);
            end
            thruster.state = 1;
            obj.ThrustersMap(name) = thruster;
        end
        
        function shutoffThruster(obj,name)
            if ~ischar(name)
                error('Vehicle:InvalidValue',...
                    'The input value, %s, is not a valid name',name);
            end
            if isKey(obj.ThrustersMap,name)
                thruster = obj.ThrustersMap(name);
            else
                error('Vehicle:InvalidComponent',...
                    'There is no attached thruster named %s', name);
            end
            thruster.state = 0;
            obj.ThrustersMap(name) = thruster;
        end
        
        function toggleThruster(obj,name)
            if ~ischar(name)
                error('Vehicle:InvalidValue',...
                    'The input value, %s, is not a valid name',name);
            end
            if isKey(obj.ThrustersMap,name)
                thruster = obj.ThrustersMap(name);
            else
                error('Vehicle:InvalidComponent',...
                    'There is no attached thruster named %s', name);
            end
            thruster.state = ~thruster.state;
            obj.ThrustersMap(name) = thruster;
        end
        
        function thrusters = listThrustersOn(obj)
            thrusters = cell(1,obj.(obj.ComponentsList{1}).Count);
            i = 1;
            for k=keys(obj.(obj.ComponentsList{1})) %ThrustersMap
                if obj.(obj.ComponentsList{1})(k{1}).state
                    thrusters{i} = obj.(obj.ComponentsList{1})(k{1}).name;
                    i = i+1;
                end
            end
            thrusters(cellfun('isempty',thrusters)) = [];
        end
        
        function sol = propagate(obj,tspan,varargin)
            % Propagate the vehicle through space and time
            
            % Ensure all thrusters that are on have enough fuel to fire for
            % the entire time span
            for t = obj.listThrustersOn
                tmp = obj.Thrusters(t{1});
                if tmp.mass_fuel - (tspan(2)-tspan(1))*tmp.mass_flowrate <0
                    error('Vehicle:Thruster',...
                        ['Thruster "%s" cannot fire for the '...
                        'duration of time span [%0.1f %0.1f].'],...
                        tmp.name,tspan(1),tspan(2));
                end
            end
            
            % ensure we are in spherical coordinates
            tmpCS = obj.CoordinateSystem; %store it to change back later
            obj.CoordinateSystem = 'Spherical';
            
            % define rho, either using standard model or provided value
            if nargin == 2
                rho = @(z) stdAtmD(z-6.371e6);
            elseif nargin == 3
                rho = @(z) varargin{1};
            else
                error('Wrong number of inputs');
            end
            
            % define initial conditions y0
            % y0 = [position velocity mass]
            y0 = zeros(3,1);
            y0(1) = obj.sv(3);
            y0(2) = obj.sv(6);
            y0(3) = obj.mass;
            
            % define ode45 derivative function
            % System of equations:
            %   y1' = y2
            %   y2' = (1/y3)(T - y3*g*y1 - 0.5*cd*rho(y1)*area*y2^2)
            %   y3' = mass_flowrate
            function dy = odefun(~,y,rho,obj) % This is a nested function
                dy = zeros(3,1);
                dy(1) = y(2);
                dy(2) = (1/y(3))*(obj.thrust ...
                    - y(3)*g(y(1)) ...
                    -(y(2)/abs(y(2)+1e-10))*0.5*obj.cd*...
                    rho(y(1))*obj.area*y(2)^2);
                dy(3) = -obj.mass_flowrate;
            end
            
            % run ode45 solver with anonymous function call to parameterize
            % odefun 
            sol = ode45(@(t,y) odefun(t,y,rho,obj),tspan,y0);
            
            % update vehicle (state vector,mass)
            % sv first
            [y, yp] = deval(sol,tspan(2));
            obj.sv(3) = y(1);
            obj.sv(6) = y(2);
            obj.sv(9) = yp(2);
            % then mass
            for k = obj.listThrustersOn
                tmp = obj.Thrusters(k{1});
                tmp.mass_fuel = tmp.mass_fuel-(tspan(2)-tspan(1))*tmp.mass_flowrate;
                obj.Thrusters(k{1}) = tmp;
            end
                        
            %convert to original coordinate system
            obj.CoordinateSystem = tmpCS;
        end
        
        %       /Additional Functions*************************************
    end %/methods
    
    %       Helper Functions******************************************
    methods(Access = private)
        function convertPropertyUnits(obj,cf)
            for prop=obj.UnitConversionIndex'
                if ~strcmp(prop{1}, 'sv')
                    obj.(prop{1}) = obj.(prop{1})*cf(prop{2});
                else
                    if strcmp(obj.PrivateCoordinateSystem, 'Cartesian')
                        obj.(prop{1}) = obj.(prop{1})*cf(prop{2});
                    elseif strcmp(obj.PrivateCoordinateSystem, 'Spherical')
                        Sv = obj.sv;
                        obj.sv(3) = Sv(3)*cf(prop{2});
                        obj.sv(6) = Sv(6)*cf(prop{2});
                        obj.sv(9) = Sv(9)*cf(prop{2});
                    end
                end
            end
        end
        
        function convertPropertyCoordinates(obj,newCS)
            Sv = obj.sv;
            switch(obj.PrivateCoordinateSystem)
                case 'Cartesian'
                    if strcmp(newCS, 'Spherical')
                        [az,el,r] = cart2sph(Sv(1),Sv(2),Sv(3));
                        [vaz,vel,vr] = cart2sph(Sv(4),Sv(5),Sv(6));
                        [aaz, ael, ar] = cart2sph(Sv(7),Sv(8),Sv(9));
                        obj.sv = [az,el,r,vaz,vel,vr,aaz,ael,ar];
                    end
                case 'Spherical'
                    if strcmp(newCS, 'Cartesian')
                        [x,y,z] = sph2cart(Sv(1),Sv(2),Sv(3));
                        [vx,vy,vz] = sph2cart(Sv(4),Sv(5),Sv(6));
                        [ax,ay,az] = sph2cart(Sv(7),Sv(8),Sv(9));
                        obj.sv = [x,y,z,vx,vy,vz,ax,ay,az];
                    end
            end
        end
    end
    
end