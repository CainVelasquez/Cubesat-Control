function [Jstructure,Jmotor,CGflywheel,Jflywheel,Jtotal] = inertia(proj,spec)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here

% ATENÇÃO: a matriz de inércia não está considerando o desbalanceamento

% Calc

%     proj.structure.length.side.width
%     proj.structure.length.side.height
%     proj.structure.mass

%     proj.flywheel.ring.length.r
%     proj.flywheel.disk.length.r
%     proj.flywheel.ring.length.h
%     proj.flywheel.disk.length.h
%     proj.flywheel.mass
%     proj.flywheel.disk.mass
%     proj.flywheel.ring.mass

% Structure Inertia

    proj.structure.inertia.Jxx = (((proj.structure.mass)*(((proj.structure.length.side.width)^2)+((proj.structure.length.side.height)^2)))/12);
    proj.structure.inertia.Jxy = 0;
    proj.structure.inertia.Jxz = 0;
    
    proj.structure.inertia.Jyx = 0;
    proj.structure.inertia.Jyy = (((proj.structure.mass)*(((proj.structure.length.side.width)^2)+((proj.structure.length.side.height)^2)))/12);
    proj.structure.inertia.Jyz = 0;
    
    proj.structure.inertia.Jzx = 0;
    proj.structure.inertia.Jzy = 0;
    proj.structure.inertia.Jzz = (((proj.structure.mass)*(((proj.structure.length.side.width)^2)+((proj.structure.length.side.width)^2)))/12);
    
    [Jstructure] = [(proj.structure.inertia.Jxx) (proj.structure.inertia.Jxy) (proj.structure.inertia.Jxz); (proj.structure.inertia.Jyx) (proj.structure.inertia.Jyy) (proj.structure.inertia.Jyz); (proj.structure.inertia.Jzx) (proj.structure.inertia.Jzy) (proj.structure.inertia.Jzz)];
    
% Motor Inertia

    proj.motor.inertia.Jxx = 0;
    proj.motor.inertia.Jxy = 0;
    proj.motor.inertia.Jxz = 0;
    
    proj.motor.inertia.Jyx = 0;
    proj.motor.inertia.Jyy = 0;
    proj.motor.inertia.Jyz = 0;
    
    proj.motor.inertia.Jzx = 0;
    proj.motor.inertia.Jzy = 0;
    proj.motor.inertia.Jzz = (proj.motor.rotorinertia);
    
    [Jmotor] = [(proj.motor.inertia.Jxx) (proj.motor.inertia.Jxy) (proj.motor.inertia.Jxz); (proj.motor.inertia.Jyx) (proj.motor.inertia.Jyy) (proj.motor.inertia.Jyz); (proj.motor.inertia.Jzx) (proj.motor.inertia.Jzy) (proj.motor.inertia.Jzz)];
    
% Flywheel Center of Gravity    
    
    proj.flywheel.xG = 0;
    proj.flywheel.yG = 0;
    proj.flywheel.zG = ((((proj.flywheel.ring.O.mass)*((proj.flywheel.disk.length.h)+((proj.flywheel.ring.O.length.h)/2)))+((proj.flywheel.ring.I.mass)*((proj.flywheel.disk.length.h)+((proj.flywheel.ring.I.length.h)/2)))+((proj.flywheel.disk.mass)*((proj.flywheel.disk.length.h)/2)))/(proj.flywheel.mass));
    
    [CGflywheel] = [(proj.flywheel.xG);(proj.flywheel.yG);(proj.flywheel.zG)];
    

% Ring Outer Inertia 

    proj.flywheel.ring.O.inertia.Jxx = ((((proj.flywheel.ring.O.mass)*(((proj.flywheel.ring.O.length.r)^2)+(((proj.flywheel.ring.O.length.r)-(proj.flywheel.ring.O.length.t))^2)))/4)+(((proj.flywheel.ring.O.mass)*((proj.flywheel.ring.O.length.h)^2))/12)+((proj.flywheel.ring.O.mass)*(((-(proj.flywheel.zG)+(proj.flywheel.disk.length.h)+((proj.flywheel.ring.O.length.h)/2))^2))));
    proj.flywheel.ring.O.inertia.Jxy = 0;
    proj.flywheel.ring.O.inertia.Jxz = 0;
    
    proj.flywheel.ring.O.inertia.Jyx = 0;
    proj.flywheel.ring.O.inertia.Jyy = ((((proj.flywheel.ring.O.mass)*(((proj.flywheel.ring.O.length.r)^2)+(((proj.flywheel.ring.O.length.r)-(proj.flywheel.ring.O.length.t))^2)))/4)+(((proj.flywheel.ring.O.mass)*((proj.flywheel.ring.O.length.h)^2))/12)+((proj.flywheel.ring.O.mass)*(((-(proj.flywheel.zG)+(proj.flywheel.disk.length.h)+((proj.flywheel.ring.O.length.h)/2))^2))));
    proj.flywheel.ring.O.inertia.Jyz = 0;
    
    proj.flywheel.ring.O.inertia.Jzx = 0;
    proj.flywheel.ring.O.inertia.Jzy = 0;
    proj.flywheel.ring.O.inertia.Jzz = ((((proj.flywheel.ring.O.mass)*(((proj.flywheel.ring.O.length.r)^2)+(((proj.flywheel.ring.O.length.r)-(proj.flywheel.ring.O.length.t))^2)))/2));

    
% Ring Inner Inertia 


    proj.flywheel.ring.I.inertia.Jxx = ((((proj.flywheel.ring.I.mass)*(((proj.flywheel.ring.I.length.r)^2)+(((proj.flywheel.ring.I.length.r)-(proj.flywheel.ring.I.length.t))^2)))/4)+(((proj.flywheel.ring.I.mass)*((proj.flywheel.ring.I.length.h)^2))/12)+((proj.flywheel.ring.I.mass)*(((-(proj.flywheel.disk.length.h)-((proj.flywheel.ring.I.length.h)/2)+(proj.flywheel.zG))^2))));
    proj.flywheel.ring.I.inertia.Jxy = 0;
    proj.flywheel.ring.I.inertia.Jxz = 0;
    
    proj.flywheel.ring.I.inertia.Jyx = 0;
    proj.flywheel.ring.I.inertia.Jyy = ((((proj.flywheel.ring.I.mass)*(((proj.flywheel.ring.I.length.r)^2)+(((proj.flywheel.ring.I.length.r)-(proj.flywheel.ring.I.length.t))^2)))/4)+(((proj.flywheel.ring.I.mass)*((proj.flywheel.ring.I.length.h)^2))/12)+((proj.flywheel.ring.I.mass)*(((-(proj.flywheel.disk.length.h)-((proj.flywheel.ring.I.length.h)/2)+(proj.flywheel.zG))^2))));
    proj.flywheel.ring.I.inertia.Jyz = 0;
    
    proj.flywheel.ring.I.inertia.Jzx = 0;
    proj.flywheel.ring.I.inertia.Jzy = 0;
    proj.flywheel.ring.I.inertia.Jzz = ((((proj.flywheel.ring.I.mass)*(((proj.flywheel.ring.I.length.r)^2)+(((proj.flywheel.ring.I.length.r)-(proj.flywheel.ring.I.length.t))^2)))/2));

        
% Disk Inertia

    proj.flywheel.disk.inertia.Jxx = ((((proj.flywheel.disk.mass)*((proj.flywheel.disk.length.r)^2))/4)+(((proj.flywheel.disk.mass)*((proj.flywheel.disk.length.h)^2))/12)+((proj.flywheel.disk.mass)*((((proj.flywheel.zG)-((proj.flywheel.disk.length.h)/2))^2))));
    proj.flywheel.disk.inertia.Jxy = 0;
    proj.flywheel.disk.inertia.Jxz = 0;
    
    proj.flywheel.disk.inertia.Jyx = 0;
    proj.flywheel.disk.inertia.Jyy = ((((proj.flywheel.disk.mass)*((proj.flywheel.disk.length.r)^2))/4)+(((proj.flywheel.disk.mass)*((proj.flywheel.disk.length.h)^2))/12)+((proj.flywheel.disk.mass)*((((proj.flywheel.zG)-((proj.flywheel.disk.length.h)/2))^2))));
    proj.flywheel.disk.inertia.Jyz = 0;
    
    proj.flywheel.disk.inertia.Jzx = 0;
    proj.flywheel.disk.inertia.Jzy = 0;
    proj.flywheel.disk.inertia.Jzz = (((proj.flywheel.disk.mass)*((proj.flywheel.disk.length.r)^2))/2);
    
    
% Flywheel Inertia

    proj.flywheel.inertia.Jxx = ((proj.flywheel.disk.inertia.Jxx)+(proj.flywheel.ring.O.inertia.Jxx)+(proj.flywheel.ring.I.inertia.Jxx));
    proj.flywheel.inertia.Jxy = ((proj.flywheel.disk.inertia.Jxy)+(proj.flywheel.ring.O.inertia.Jxy)+(proj.flywheel.ring.I.inertia.Jxy));
    proj.flywheel.inertia.Jxz = ((proj.flywheel.disk.inertia.Jxz)+(proj.flywheel.ring.O.inertia.Jxz)+(proj.flywheel.ring.I.inertia.Jxz));
    
    proj.flywheel.inertia.Jyx = ((proj.flywheel.disk.inertia.Jyx)+(proj.flywheel.ring.O.inertia.Jyx)+(proj.flywheel.ring.I.inertia.Jyx));
    proj.flywheel.inertia.Jyy = ((proj.flywheel.disk.inertia.Jyy)+(proj.flywheel.ring.O.inertia.Jyy)+(proj.flywheel.ring.I.inertia.Jyy));
    proj.flywheel.inertia.Jyz = ((proj.flywheel.disk.inertia.Jyz)+(proj.flywheel.ring.O.inertia.Jyz)+(proj.flywheel.ring.I.inertia.Jyz));
    
    proj.flywheel.inertia.Jzx = ((proj.flywheel.disk.inertia.Jzx)+(proj.flywheel.ring.O.inertia.Jzx)+(proj.flywheel.ring.I.inertia.Jzx));
    proj.flywheel.inertia.Jzy = ((proj.flywheel.disk.inertia.Jzy)+(proj.flywheel.ring.O.inertia.Jzy)+(proj.flywheel.ring.I.inertia.Jzy));
    proj.flywheel.inertia.Jzz = ((proj.flywheel.disk.inertia.Jzz)+(proj.flywheel.ring.O.inertia.Jzz)+(proj.flywheel.ring.I.inertia.Jzz));

    [Jflywheel] = [proj.flywheel.inertia.Jxx proj.flywheel.inertia.Jxy proj.flywheel.inertia.Jxz; proj.flywheel.inertia.Jyx proj.flywheel.inertia.Jyy proj.flywheel.inertia.Jyz; proj.flywheel.inertia.Jzx proj.flywheel.inertia.Jzy proj.flywheel.inertia.Jzz];

% Cubesat Inertia

    [Jtotal] = ((Jmotor) + (Jflywheel) + (Jstructure)); % [kg.m^2] - Inertia Cubesat

end