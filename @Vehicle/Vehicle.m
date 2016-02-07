classdef Vehicle
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
        sv = zeros(1,9); % 1x9 3D state vector [position velocity acceleration] of CoM
        area = 0; % Cross-sectional area of vehicle
        cd = 0; % Drag coefficient of vehicle
        
        
    end
    
    properties(Dependent)
        Units % Unit system used (Metric, English)
        CoordinateSystem % Coordinate system used (Cartesian, Spherical)
        
    end
    
    properties(SetAccess=private, Dependent)
        mass % Total mass of the vehicle
        fuelmass % Total mass of fuel onboard the vehicle
        massDot % Total mass consumption rate
        thrust % Total thrust produced by vehicle
        
    end
    
    properties(Access = private)
        PrivateUnits = 'Metric';
        PrivateCoordinateSystem = 'Cartesian';
        ThrustersMap = containers.Map(); % Map of all thrusters on vehicle
        StructuresMap = containers.Map(); % Map of all structures on vehicle
        
    end
    
    properties(Access = private, Constant)
        ConversionFactors = [.3048,...  % ft/m
            2.20462,... % lbm/kg
            0.224809,... % lbf/N
            1,... % unitless
            .3048^2,... % ft^2/m^2
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
        function obj = Vehicle(sv,area,cd,CS,Units)
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
                obj.sv = sv;
                obj.area = area;
                obj.cd = cd;
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
        
        function mass = get.mass(obj)
            mass = 0;
            %sum mass of components
            for c=obj.ComponentsList'
                for k=keys(obj.(c{1}))
                    mass = mass + obj.(c{1})(k{1}).mass;
                end
            end
        end
        
        function thruster = thrusters(obj,name)
            if ~ischar(name)
                error('Vehicle:InvalidValue',...
                    'The input value, %s, is not a valid name',name);
            end
            if isKey(obj.Thrustersmap,name)
                thruster = obj.Thrustersmap(name);
            else
                error('Vehicle:InvalidComponent',...
                    'There is no attached thruster named %s', name);
            end
        end
        
        function structure = structures(obj,name)
            if ~ischar(name)
                error('Vehicle:InvalidValue',...
                    'The input value, %s, is not a valid name',name);
            end
            if isKey(obj.Structuresmap,name)
                structure = obj.Structuresmap(name);
            else
                error('Vehicle:InvalidComponent',...
                    'There is no attached structure named %s', name);
            end
        end
        
        %       /Get Functions********************************************
        
        %       Set Functions*********************************************
        function obj = set.Units(obj,newUnits)
            switch(newUnits)
                case 'Metric'
                    if ~strcmp(obj.PrivateUnits, newUnits)
                        obj.PrivateUnits = newUnits;
                        obj =convertPropertyUnits(obj,1./obj.ConversionFactors);
                    end
                case 'English'
                    if ~strcmp(obj.PrivateUnits, newUnits)
                        obj.PrivateUnits = newUnits;
                        obj = convertPropertyUnits(obj,obj.ConversionFactors);
                    end
                otherwise
                    error('Vehicle:InvalidValue',...
                        'Units ''%s'' is not supported', newUnits);
            end
        end
        
        function obj = set.CoordinateSystem(obj,newCS)
            switch(newCS)
                case 'Cartesian'
                    if ~strcmp(obj.PrivateCoordinateSystem, newCS)
                        obj = convertPropertyCoordinates(obj,newCS);
                        obj.PrivateCoordinateSystem = newCS;
                    end
                case 'Spherical'
                    if ~strcmp(obj.PrivateCoordinateSystem, newCS)
                        obj = convertPropertyCoordinates(obj,newCS);
                        obj.PrivateCoordinateSystem = newCS;
                    end
                    
                otherwise
                    error('Vehicle:InvalidValue',...
                        'Coordinate System ''%s'' is not supported',...
                        newCS);
            end
        end
        
        function obj = set.sv(obj,sv)
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
        
        %       /Additional Functions*************************************
    end %/methods
    
    %       Helper Functions******************************************
    methods(Access = private)
        function obj = convertPropertyUnits(obj,cf)
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
        
        function obj = convertPropertyCoordinates(obj,newCS)
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