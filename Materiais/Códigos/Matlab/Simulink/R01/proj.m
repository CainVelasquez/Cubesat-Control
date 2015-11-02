%% Inicializa motores

% Structure
% Motor
% Flywheel
% Coupling
% Eletronics
% Cubesat/Labsim/Mmp

%% Cubesat

% ---------------- Structure ---------------- %

% Dimensions
Cubesat.structure.length.side.width = 0.1;              % [m] - width
Cubesat.structure.length.side.height = 0.1;          % [m] - height
Cubesat.structure.length.thickness = 0.0065;            % [m] - trickness

% Volume
Cubesat.structure.volume.side = ((Cubesat.structure.length.side.width)*(Cubesat.structure.length.side.height)*(Cubesat.structure.length.thickness)); % [m^3] - Volume 1 side
Cubesat.structure.volume.cover = ((Cubesat.structure.length.side.width)*(Cubesat.structure.length.side.width)*(Cubesat.structure.length.thickness)); % [m^3] - Volume 1 cover
Cubesat.structure.volume = (((Cubesat.structure.volume.side)*(4))+((Cubesat.structure.volume.cover)*(2)));

Cubesat.structure.coupling.volume = 3*((17276.06)/(1000*1000*1000)); % [m^3] - Volume 3 couplings

% Density
Cubesat.structure.dens = 1050;                           % [kg/m^3] - Average density of plastic

Cubesat.structure.coupling.dens = 1050;                           % [kg/m^3] - Average density of plastic

% Mass
Cubesat.structure.coupling.mass = ((Cubesat.structure.coupling.dens)*(Cubesat.structure.coupling.volume));   % [kg] - mass

Cubesat.structure.mass = (((Cubesat.structure.dens)*(Cubesat.structure.volume))+(Cubesat.structure.coupling.mass));   % [kg] - mass

% Inertia

structureinertiaJzz = (((Cubesat.structure.mass)*(((Cubesat.structure.length.side.width)^2)+((Cubesat.structure.length.side.width)^2)))/12);


% ---------------- Motor ---------------- %

% Motor Data - Order Number 339260 (A with Hall sensors)
Cubesat.motor.V = 12.0;                     % [V] - Nominal voltage
Cubesat.motor.w0 = ((7970*2*pi())/60);    % [rad/s] - No load speed
Cubesat.motor.i0 = (75.6*(10^-3));        % [A] - No load current

% Dynamics
% Cubesat.motor.w1 = ((10400*2*pi())/60); % [rad/s] - Nominal speed (190)
% Cubesat.motor.w1 = ((2500*2*pi())/60);  % [rad/s] - Nominal speed (RW-DJD-001_v30)
% Cubesat.motor.w1 = ((4000*2*pi())/60);  % [rad/s] - Nominal speed (RW-MOTOR-SPEC)
Cubesat.motor.w1 = ((3240*2*pi())/60);    % [rad/s] - Nominal speed (Proj_R01)
Cubesat.motor.T1 = (7.92*(10^-3));        % [Nm] - Nominal torque (max. continuous torque)
Cubesat.motor.i1 = 0.609;                 % [A] - Nominal current (max. continuous current)
Cubesat.motor.T2 = (15.7*(10^-3));        % [Nm] - Stall torque
Cubesat.motor.i2 = 1.19;                  % [A] - Starting current
Cubesat.motor.effmax = 0.57;              % [%] - Max. efficiency
Cubesat.motor.Rrup = 10.1;                % [ohm] - Terminal resistance phase to phase
CubesatmotorRrup = 10.1;                % [ohm] - Terminal resistance phase to phase
% Cubesat.motor.Lrup = 2.04;              % [mH] - Terminal inductance phase to phase
Cubesat.motor.Lrup = ((2.04)/1000);       % [H] - Terminal inductance phase to phase
CubesatmotorLrup = ((2.04)/1000);       % [H] - Terminal inductance phase to phase
% Cubesat.motor.Tconst = 13.2;            % [mNm/A] - Torque constant
Cubesat.motor.Tconst = ((13.2)/1000);     % [Nm/A] - Torque constant
CubesatmotorTconst = ((13.2)/1000);     % [Nm/A] - Torque constant
% Cubesat.motor.Sconst = 724;             % [rpm/V] - Speed constant
Cubesat.motor.Sconst = (60/((724)*(2)*(pi())));               % [V/rad/sec] - Speed constant
CubesatmotorSconst = (60/((724)*(2)*(pi())));               % [V/rad/sec] - Speed constant
Cubesat.motor.STgradient = 551;           % [rpm/mNm] - Speed / torque gradient
Cubesat.motor.Mtc = 80.3;                 % [ms] - Mechanical time constant
Cubesat.motor.b = ((2)/(10^(-5)));        % [N.m.s] - motor viscous friction constant
Cubesatmotorb = 0.01;        % [N.m.s] - motor viscous friction constant

% Inertia
% Cubesat.motor.inertia = 0.543;          % [g*cm^2] - Rotor inertia
Cubesat.motor.rotorinertia = ((13.9)/((1000)*(100)*(100)));     % [kg*m^2] - Rotor inertia
Cubesatmotorrotorinertia = ((13.9)/((1000)*(100)*(100)));     % [kg*m^2] - Rotor inertia

% Mass
Cubesat.motor.mass = 0.032;               % [kg] - Weight of motor

% Dynamical Requirements

% Electrical Requirements


% ---------------- Flywheel ---------------- %

% Dimensions
Cubesat.flywheel.ring.O.length.r = (0.0160);                % [m] - radius ring outer
Cubesat.flywheel.ring.O.length.t = (0.0050);                % [m] - thickness ring outer
Cubesat.flywheel.ring.O.length.h = (0.0140);                % [m] - height ring outer

Cubesat.flywheel.ring.I.length.r = (0.0050);                % [m] - radius ring outer
Cubesat.flywheel.ring.I.length.t = (0.0030);                % [m] - thickness ring outer
Cubesat.flywheel.ring.I.length.h = (0.0090);                % [m] - height ring outer


Cubesat.flywheel.disk.length.r = (0.0160);                  % [m] - radius disk
Cubesat.flywheel.disk.length.h = (0.0030);                  % [m] - height disk


% Density
% Cubesat.flywheel.dens = 7850;                % [kg/m^3] - Average density of steel
Cubesat.flywheel.dens = 8000;              % [kg/m^3] - Average density of stainless steel
% Cubesat.flywheel.dens = 2697;              % [kg/m^3] - Average density of aluminum

% Volume

Cubesat.flywheel.ring.O.volume = ((pi())*(((Cubesat.flywheel.ring.O.length.r)^2)-(((Cubesat.flywheel.ring.O.length.r)-(Cubesat.flywheel.ring.O.length.t))^2))*(Cubesat.flywheel.ring.O.length.h));  % [m^3] - Volume Ring Outer 
Cubesat.flywheel.ring.I.volume = ((pi())*(((Cubesat.flywheel.ring.I.length.r)^2)-(((Cubesat.flywheel.ring.I.length.r)-(Cubesat.flywheel.ring.I.length.t))^2))*(Cubesat.flywheel.ring.I.length.h));  % [m^3] - Volume Ring Inner
Cubesat.flywheel.disk.volume = ((pi())*((Cubesat.flywheel.disk.length.r)^2)*(Cubesat.flywheel.disk.length.h));  % [m^3] - Disk Volume
Cubesat.flywheel.volume = ((Cubesat.flywheel.ring.O.volume)+(Cubesat.flywheel.ring.I.volume)+(Cubesat.flywheel.disk.volume));


% Mass
Cubesat.flywheel.ring.O.mass = ((Cubesat.flywheel.dens)*(Cubesat.flywheel.ring.O.volume));    % [kg] - Ring Outer Mass
Cubesat.flywheel.ring.I.mass = ((Cubesat.flywheel.dens)*(Cubesat.flywheel.ring.I.volume));    % [kg] - Ring Inner Mass
Cubesat.flywheel.disk.mass = ((Cubesat.flywheel.dens)*(Cubesat.flywheel.disk.volume));        % [kg] - Disk mass
Cubesat.flywheel.mass = ((Cubesat.flywheel.disk.mass)+(Cubesat.flywheel.ring.O.mass)+(Cubesat.flywheel.ring.I.mass));          % [kg] - Flywheel mass

% Inertia
        
flywheelinertiaJzz = ((((Cubesat.flywheel.ring.O.mass)*(((Cubesat.flywheel.ring.O.length.r)^2)+(((Cubesat.flywheel.ring.O.length.r)-(Cubesat.flywheel.ring.O.length.t))^2)))/2))+((((Cubesat.flywheel.ring.I.mass)*(((Cubesat.flywheel.ring.I.length.r)^2)+(((Cubesat.flywheel.ring.I.length.r)-(Cubesat.flywheel.ring.I.length.t))^2)))/2))+(((Cubesat.flywheel.disk.mass)*((Cubesat.flywheel.disk.length.r)^2))/2);
    

% ---------------- Coupling ---------------- %

% Mass
Cubesat.coupling.bearing.mass = 0.0080; % [kg] - http://medias.schaeffler.de/medias/hp.ec.br.pr/62*626;b4zp6gWrtzrb?clrsb=1
Cubesat.coupling.mass = (0.0010+(2*Cubesat.coupling.bearing.mass));


% ---------------- Electronics ---------------- %

% Mass
Cubesat.eletronics.mass = 0.300;


% ---------------- Cubesat ---------------- %

% Mass
Cubesat.mass = ((Cubesat.structure.mass)+(Cubesat.motor.mass)+(Cubesat.flywheel.mass)+(Cubesat.coupling.mass)+(Cubesat.eletronics.mass));                 % [kg] - total mass

%% Laboratório de Simulações
% 
% % ---------------- Structure ---------------- %
% 
% % Mass
% Labsim.structure.mass = 1.0;   % [kg] - mass
% 
% % ---------------- Motor ---------------- %
% 
% % Motor Data
% Labsim.motor.V = 24;                     % [V] - Nominal voltage
% Labsim.motor.w0 = ((13100*2*pi())/60);   % [rad/s] - No load speed
% Labsim.motor.i0 = (347*(10^-3));         % [A] - No load current
% % Labsim.motor.w1 = ((10400*2*pi())/60); % [rad/s] - Nominal speed (190)
% % Labsim.motor.w1 = ((2500*2*pi())/60);  % [rad/s] - Nominal speed (RW-DJD-001_v30)
% % Labsim.motor.w1 = ((4000*2*pi())/60);  % [rad/s] - Nominal speed (RW-MOTOR-SPEC)
% % Labsim.motor.w1 = ((630*2*pi())/60);   % [rad/s] - Nominal speed (Proj_R01)
% Labsim.motor.w1 = ((8000*2*pi())/60);    % [rad/s] - Nominal speed (Proj_R01)
% Labsim.motor.T1 = (48.2*(10^-3));        % [Nm] - Nominal torque (max. continuous torque)
% Labsim.motor.i1 = 2.64;                  % [A] - Nominal current (max. continuous current)
% Labsim.motor.T2 = (773*(10^-3));         % [Nm] - Stall torque
% Labsim.motor.i2 = 45.8;                  % [A] - Starting current
% Labsim.motor.effmax = 0.84;              % [%] - Max. efficiency
% Labsim.motor.Rrup = 0.524;               % [ohm] - Terminal resistance phase to phase
% Labsim.motor.Lrup = 0.390;               % [mH] - Terminal inductance phase to phase
% Labsim.motor.Tconst = 16.9;              % [mNm/A] - Torque constant
% Labsim.motor.Sconst = 565;               % [rpm/V] - Speed constant
% Labsim.motor.STgradient = 17.5;          % [rpm/mNm] - Speed / torque gradient
% Labsim.motor.Mtc = 1.93;                 % [ms] - Mechanical time constant
% 
% % Inertia
% Labsim.motor.inertia = 10.5;              % [gcm^2] - Rotor inertia
% 
% % Mass
% Labsim.motor.mass = 0.17;                % [kg] - Weight of motor
% 
% % ---------------- Flywheel ---------------- %
% 
% % Dimensions
% Labsim.flywheel.disk.length.r = 0.130;          % [m] - disk radius
% Labsim.flywheel.ring.length.r = 0.140;          % [m] - ring radius
% Labsim.flywheel.disk.length.h = 0.005;          % [m] - disk height
% Labsim.flywheel.ring.length.h = 0.070;          % [m] - ring height
% % 
% % Class I
% % Labsim.flywheel.disk.length.r = 0.092;          % [m] - disk radius
% % Labsim.flywheel.ring.length.r = 0.102;          % [m] - ring radius
% % Labsim.flywheel.disk.length.h = 0.005;          % [m] - disk height
% % Labsim.flywheel.ring.length.h = 0.050;          % [m] - ring height
% % 
% % Class II
% % Labsim.flywheel.disk.length.r = 0.135;          % [m] - disk radius
% % Labsim.flywheel.ring.length.r = 0.145;          % [m] - ring radius
% % Labsim.flywheel.disk.length.h = 0.005;          % [m] - disk height
% % Labsim.flywheel.ring.length.h = 0.050;          % [m] - ring height
% % 
% % Class III
% % Labsim.flywheel.disk.length.r = 0.195;          % [m] - disk radius
% % Labsim.flywheel.ring.length.r = 0.205;          % [m] - ring radius
% % Labsim.flywheel.disk.length.h = 0.005;          % [m] - disk height
% % Labsim.flywheel.ring.length.h = 0.050;          % [m] - ring height
% 
% % Density
% % Labsim.flywheel.dens = 7860;              % [kg/m^3] - Average density of steel
% % Labsim.flywheel.dens = 8000;              % [kg/m^3] - Average density of stainless steel
% Labsim.flywheel.dens = 2697;                % [kg/m^3] - Average density of aluminum
% 
% % Volume
% % Labsim.flywheel.volume = (((pi())*(((Labsim.flywheel.length.R1)^2)-((Labsim.flywheel.length.R2)^2)))*(Labsim.flywheel.length.h)); % [m^3] - Volume
% Labsim.flywheel.disk.volume = ((Labsim.flywheel.dens)*(pi())*((Labsim.flywheel.disk.length.r)^2)*(Labsim.flywheel.disk.length.h));  % [m^3] - Disk Volume
% Labsim.flywheel.ring.volume = ((Labsim.flywheel.dens)*(pi())*(((Labsim.flywheel.ring.length.r)^2)-((Labsim.flywheel.disk.length.r)^2))*(Labsim.flywheel.ring.length.h));  % [m^3] - Ring Volume
% Labsim.flywheel.volume = ((Labsim.flywheel.disk.volume)+(Labsim.flywheel.ring.volume)); % [m^3] - Flywheel Volume
% 
% % Mass
% Labsim.flywheel.mass = ((Labsim.flywheel.dens)*(Labsim.flywheel.volume));              % [kg] - Flywheel mass
% 
% % ---------------- Coupling ---------------- %
% 
% % Mass
% Labsim.coupling.bearing.mass = 0.0080; % [kg] - http://medias.schaeffler.de/medias/hp.ec.br.pr/62*626;b4zp6gWrtzrb?clrsb=1
% Labsim.coupling.mass = (0.284+(2*Labsim.coupling.bearing.mass));
% 
% % ---------------- Electronics ---------------- %
% 
% % Mass
% Labsim.eletronics.mass = 0.300;
% 
% % ---------------- Labsim ---------------- %
% 
% % Mass
% Labsim.mass = ((Labsim.structure.mass)+(Labsim.motor.mass)+(Labsim.flywheel.mass)+(Labsim.coupling.mass)+(Labsim.eletronics.mass));   
% 
% %% Multi-Mission Plataform
% Mmp.motor.r = 5E3;
% Mmp.motor.v = 10;
% % ---------------- Structure ---------------- %
% 
% % ---------------- Motor ---------------- %
% 
% % ---------------- Flywheel ---------------- %
% 
% % ---------------- Coupling ---------------- %
% 
% % ---------------- Electronics ---------------- %
% 
% % ---------------- Mmp ---------------- %