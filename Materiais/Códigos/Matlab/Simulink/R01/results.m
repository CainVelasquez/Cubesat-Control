function res = results(mass,proj,spec)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

res = 0;

% if (dim == 1 && mass == 1 && dyn == 1)
    if (mass == 1)
        fprintf('O projeto atende às especificações.\n');
        fprintf('\n   (proj)                              (spec)');
        fprintf('\nEstrutura: %f [kg] ---------- Estrutura: %f [kg]', proj.structure.mass, spec.structure.mass);
        fprintf('\nMotor: %f [kg] -------------- Motor: %f [kg]', proj.motor.mass, spec.motor.mass);
        fprintf('\nVolante: %f [kg] ------------ Volante: %f [kg]', proj.flywheel.mass, spec.flywheel.mass);
        fprintf('\nAcoplamento: %f [kg] -------- Acoplamento: %f [kg]', proj.coupling.mass, spec.coupling.mass);
        fprintf('\nEletrônica: %f [kg] --------- Eletrônica: %f [kg]\n', proj.eletronics.mass, spec.eletronics.mass);   
        fprintf('\nMassa Total: %f [kg] -------- Massa Total: %f [kg]\n', proj.mass, spec.mass);
    else
        fprintf('\nFavor atender às especificações.\n');
        fprintf('\n   (proj)                              (spec)');
        fprintf('\nEstrutura: %f [kg] ---------- Estrutura: %f [kg]', ((proj.structure.mass)+(proj.structure.coupling.mass)), spec.structure.mass);
        fprintf('\nMotor: %f [kg] -------------- Motor: %f [kg]', proj.motor.mass, spec.motor.mass);
        fprintf('\nVolante: %f [kg] ------------ Volante: %f [kg]', proj.flywheel.mass, spec.flywheel.mass);
        fprintf('\nAcoplamento: %f [kg] -------- Acoplamento: %f [kg]', proj.coupling.mass, spec.coupling.mass);
        fprintf('\nEletrônica: %f [kg] --------- Eletrônica: %f [kg]\n', proj.eletronics.mass, spec.eletronics.mass);   
        fprintf('\nMassa Total: %f [kg] -------- Massa Total: %f [kg]\n', proj.mass, spec.mass);
    end
    
    
    
%     fprintf('\nRaio externo: %f [mm] \n', proj.volante.R1*1000); % [m] para [mm]
%     fprintf('Raio interno: %f [mm] \n', proj.volante.R2*1000); % [m] para [mm]
%     fprintf('Altura: %f [mm] \n', proj.volante.h*1000); % [m] para [mm]
%     fprintf('Massa: %f [kg] \n(Volante:  + Motor:  + Eletr:  + Acopl: ) \n', proj.structure.mass);
%     fprintf('Massa Total: %f [kg] \n( Motor: %f + Volante:  +  Estrutura: %f + Eletr:  + Acopl: ) \n', proj.mass, proj.motor.mass, proj.structure.mass);
%     fprintf('\nMassa Total: %f [kg] \n( Motor: %f [kg] + Volante:  +  Estrutura: %f + Eletr:  + Acopl: ) \n', proj.mass, proj.motor.mass, proj.structure.mass);
%     fprintf('Momento Angular: %f [Nms] \n', sum(proj.volante.L));
%     fprintf('Momento de Inércia: %f [kg.m²] \n', J);
%     fprintf('Torque01: %f [Nm] \n', sum(Torque01));
%     fprintf('Torque Especificado: %f [Nm] \n', sum(Torque02));
%     fprintf('Velocidade: %f [rpm] \n', (((proj.w1)*60)/(2*pi()))); % [rad/s] para [rpm]
%     fprintf('Aceleração: %f [m/s^2] \n', sum(acel));
%     fprintf('Tempo: %f [s] \n', tempo);
%     fprintf('Tempo: %f [min] \n', tempo/60);
    

end

