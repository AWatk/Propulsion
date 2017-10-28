%
%  cleans up all the mess
%  closes everything and clears everything


diary off
fclose('all');
% close all hidden
h = findobj('Type','figure');
delete(h)
close all hidden
clear all
clear global
clear java
clear variables
clear functions
clear classes
clc
