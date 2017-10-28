% Will Dean (NGIS)
% 12/05/2012
% regexp function for cells of strings

function ind = cellFind(array,string,varargin)

if nargin == 2
    if ~iscell(array)
        error('First input must be a cell')
    end
    if ~ischar(string)
        error('Second input must be a string')
    end
    excludeFlag = false;
else if nargin == 3
        if ~iscell(array)
            error('First input must be a cell')
        end
        if ~ischar(string)
            error('Second input must be a string')
        end
        if strcmpi(varargin,'exclude')
            excludeFlag = true;
        else
            warning('MATLAB:InvalidInput','Comparison type not recognized.. Defaulting to ''include''')
            excludeFlag = false;
        end
    else
        error('Incorrect inputs')
    end
end

if excludeFlag
    ind = find(cellfun('isempty',regexp(array,string)));
else
    ind = find(~cellfun('isempty',regexp(array,string)));
end