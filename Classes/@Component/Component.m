classdef Component
    
    properties
        name
    end
    
    properties(Dependent)
        Units % Unit system used (Metric, English)
        CoordinateSystem % Coordinate system used (Cartesian, Spherical)
        mass
    end
    
    properties(Access=protected)
        PrivateUnits = 'Metric';
        PrivateCoordinateSystem = 'Cartesian';
        
        privatemass = 0;
    end
    
    properties(Access=protected, Constant)
        ConversionFactors = [3.28084,...  % ft/m
            2.20462,... % lbm/kg
            0.224809,... % lbf/N
            1,... % unitless
            3.28084^2,... % ft^2/m^2
            ]; % Conversion factors for basic units
        
        UnitConversionIndex = ...,
            {'privatemass', 2;   % index of proper conversion factor
            }
    end
    
    methods
        
        %       Ctor******************************************************
        function obj = Component(name,mass, CS, Units)
            if nargin > 0
                switch(CS)
                    case 'Cartesian'
                    case 'Spherical'
                        obj.PrivateCoordinateSystem = CS;
                    otherwise
                        error('Component:InvalidCoordinateSystem',...
                            'Coordinate System ''%s'' is not supported',...
                            CS);
                end
                switch(Units)
                    case 'Metric'
                    case 'English'
                        obj.PrivateUnits = Units;
                    otherwise
                        error('Component:InvalidUnits',...
                            'Units ''%s'' is not supported', Units);
                end
                if ~ischar(name)
                    error('Component:InvalidValue',...
                        'Component name, %s, must be of type char',name);
                else
                    obj.name = name;
                end
                obj.privatemass = mass;
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
            mass = obj.getTotalMass();
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
                    error('Component:InvalidValue',...
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
                    error('Component:InvalidValue',...
                        'Coordinate System ''%s'' is not supported',...
                        newCS);
            end
        end
    end
    %       /Set Functions********************************************
    
    %       Helper Functions******************************************
    methods(Access = protected)
        function obj = convertPropertyUnits(obj,cf)
            for prop=obj.UnitConversionIndex'
                obj.(prop{1}) = obj.(prop{1})*cf(prop{2});
            end
        end
        
        function obj = convertPropertyCoordinates(obj,newCS)
            switch(obj.PrivateCoordinateSystem)
                case 'Cartesian'
                    % placeholder for when things change based on CS
                case 'Spherical'
                    % placeholder for when things change based on CS
            end
        end
        
        
    end
    %       /Helper Functions*****************************************
    
    methods(Access = protected)
        %       Overloaded Functions*************************************
        %overload this function in subclasses!
        function totalMass = getTotalMass(obj)
            totalMass = obj.privatemass;
        end
        
        %       /Overloaded Functions************************************
    end
    
end