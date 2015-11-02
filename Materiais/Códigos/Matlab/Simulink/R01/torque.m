function [T] = torque(proj,spec)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

% Motor Torque
    [Tmotor] = [0 0 0;0 0 0;0 0 ((((proj.motor.V)*(proj.motor.i1))*(proj.motor.effmax))/(proj.motor.w1))];  % [Nm] - Motor Torque

% Friction Torque
    [Tfriction] = [0 0 0;0 0 0;0 0 0.0001]; % [Nm] - Friction Torque
    
% Cubesat Torque
    [T] = ((Tmotor)-(Tfriction));           % [Nm] - Cubesat Torque
end