function [Jstructure,Jmotor,CGflywheel,Jflywheel,Jtotal,wcubesat,L,T] = evaluate(proj,spec)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

% Evaluate

[Jstructure,Jmotor,CGflywheel,Jflywheel,Jtotal] = inertia(proj,spec);

[wcubesat] = angular_velocity(Jstructure,Jmotor,proj,spec);

[L] = angular_momentum(Jtotal,wcubesat);

[T] = torque(proj,spec);

end