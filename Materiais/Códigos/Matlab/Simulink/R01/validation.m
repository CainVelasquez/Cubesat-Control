function mass = validation(proj,spec)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

%% Specifications

dim = 0;
mass = 0;
dyn = 0;


%% Dimensions

%     if ((proj.volante.R1 <= (specproj.diameter - (2*(specproj.thickness)))) && (proj.volante.h <= specproj.height))
%         dim = 1;
%     else
%         dim = 0;
%         disp('O projeto NÃO atende às especificações de dimensões.');
%     end

%% Mass

    if ((proj.structure.mass <= spec.structure.mass)&&(proj.motor.mass <= spec.motor.mass)&&(proj.flywheel.mass <= spec.flywheel.mass)&&(proj.coupling.mass <= spec.coupling.mass)&&(proj.eletronics.mass <= spec.eletronics.mass)&&(proj.mass <= spec.mass))
        mass = 1;
    else
        mass = 0;
        disp('O projeto NÃO atende às especificações de massa.');
    end
   
%% Dynamics

%     if ( (sum(ret1.L) > specproj.L) && ( proj.w1 <= specproj.wmax) )
%         dyn = 1;
%     else
%         dyn = 0;
%         disp('O projeto NÃO atende às especificações dinâmicas.');
%     end  

end

