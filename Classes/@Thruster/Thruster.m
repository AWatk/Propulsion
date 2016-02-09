classdef Thruster < Component
    
    properties
        mass_fuel = 0;
    end
    
    properties (Dependent)
        mass_flowrate
        thrust
        state
    end
    
    properties (Access = protected)
        privatemass_flowrate = 0;
        privatethrust = 0;
        privatestate = false;
    end
    
    methods
        %       Ctor******************************************************
        function obj = Thruster(name, mass, CS, Units, mass_fuel, mass_flowrate,thrust)
            if nargin == 0
                compargs{1} = 0;
                compargs{2} = 'Cartesian';
                compargs{3} = 'Metric';
            elseif nargin == 7
                compargs{1} = name;
                compargs{2} = mass;
                compargs{3} = CS;
                compargs{4} = Units;
            else
                error('Component:Arguments', 'Wrong number of input args');
            end
            obj@Component(compargs{:});
            obj.mass_fuel = mass_fuel;
            obj.privatemass_flowrate = mass_flowrate;
            obj.privatethrust = thrust;
            
        end
        %       /Ctor*****************************************************
        
        %       Get Functions*********************************************
        function mass_flowrate = get.mass_flowrate(obj)
            if obj.privatestate && obj.mass_fuel > 0
                mass_flowrate = obj.privatemass_flowrate;
            else
                mass_flowrate = 0;
            end
        end
        
        function thrust = get.thrust(obj)
            if obj.privatestate && obj.mass_fuel > 0
                thrust = obj.privatethrust;
            else
                thrust = 0;
            end
        end
        
        function state = get.state(obj)
            state = obj.privatestate;
        end
        
        
        %       /Get Functions********************************************
        
        %       Set Functions*********************************************
        function obj = set.mass_flowrate(obj,val)
            if val <= 0
                obj.privatemass_flowrate = val;
            else
                error('Component:Value',...
                    'mass_flowrate must be zero or negative');
            end
        end
        
        function obj = set.thrust(obj,val)
            if val >=0
                obj.privatethrust = val;
            else
                error('Component:Value',...
                    'Thrust must be non-negative');
            end
        end
        
        function obj = set.state(obj,val)
            switch(val)
                case 'On'
                    obj.privatestate = true;
                case 'Off'
                    obj.privatestate = false;
                case true
                    obj.privatestate = true;
                case false
                    obj.privatestate = false;
                otherwise
                    error('Component:Value',...
                        ['Invalid thruster state, %s, valid states are'...
                        'On, Off, true, and false'], val);
                    
            end
        end
        
        
        %       /Set Functions********************************************
    end
    
    methods (Access = protected)
        %       Overloaded Functions**************************************
        
        %overload this function in subclasses!
        function totalMass = getTotalMass(obj)
            totalMass = obj.privatemass + obj.mass_fuel;
        end
        
        %       /Overloaded Functions*************************************
    end
end