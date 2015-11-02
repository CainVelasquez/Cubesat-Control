function [wcubesat] = angular_velocity(Jstructure,Jmotor,proj,spec)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here

% Motor Angular Velocity
      [wmotor] = [0 0 0;0 0 0;0 0 proj.motor.w1];  % [rad/s] - Angular Velocity
  
% Cubesat Angular Velocity
      [wcubesat] = ((inv(Jstructure))*(Jmotor)*(wmotor));                              % [rad/s] - Cubesat Angular Velocity

end