classdef Structure < Component
    properties
        %none atm
    end
    
    methods
        %       Ctor******************************************************
        function obj = Structure(name, mass, CS, Units)
            if nargin == 0
                compargs{1} = 0;
                compargs{2} = 'Cartesian';
                compargs{3} = 'Metric';
            elseif nargin == 4
                compargs{1} = name;
                compargs{2} = mass;
                compargs{3} = CS;
                compargs{4} = Units;
            else
                error('Component:Arguments', 'Wrong number of input args');
            end
            obj@Component(compargs{:});
            
        end
        %       /Ctor*****************************************************
        
    end
    
    methods (Access = protected)
        %       Overloaded Functions**************************************
        
        %overload this function in subclasses!
        function totalMass = getTotalMass(obj)
            totalMass = obj.privatemass;
        end
        
        %       /Overloaded Functions*************************************
    end
end