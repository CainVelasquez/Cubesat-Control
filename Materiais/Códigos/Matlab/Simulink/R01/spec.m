%% Inicializa especificacoes

% Structures
% Communication Systems
% Power Systems
% Solar Panels
% Attitude Control Systems
% Antenna Systems
% Command & Data Handling
% Cameras & Payloads
% Launch Adapters
% Support Equipment



% Structure
% Motor
% Flywheel
% Coupling
% Eletronics
% Cubesat/Labsim/Mmp

%% Specification Cubesat

% ---------------- Structure ---------------- %

% Dimensions

% Mass
specCubesat.structure.mass = 0.665;   % [kg] - mass


% ---------------- Motor ---------------- %

% Motor Data

% Dynamics

% Mass
specCubesat.motor.mass = 0.050;               % [kg] - Weight of motor

% Dynamical Requirements
specCubesat.motor.L = 0.0108;                  % [N.m.s] - The angular momentum of the wheel at maximum operational speed (nominal) should be at least 12 Nms with a tolerance of 1%
specCubesat.theta = 0.1;                       % [deg] - The direction of rotation axis of the wheel shall be perpendicular to the mounting surface with a tolerance lower than or equal to 0.1 deg.
specCubesat.motor.imbst = 0.4;                 % [g.cm] - Residual static imbalance of the rotating parts shall be lower than 1.1 g.cm, and residual dynamic imbalance shall be lower than 10 g.cm2.
specCubesat.motor.imbdy = 1.0;                 % [g.cm^2] - Residual dynamic imbalance shall be lower than 1 g.cm2.
specCubesat.motor.Tmax = 0.000625;             % [N.m] - maximum motor torque
specCubesat.motor.Tlmax = 0.00001;             % [N.m] - maximum loss torque (friction torque)
specCubesat.motor.wmax = ((10400*2*pi())/60);  % [rad/s] - Nominal speed (RW-MOTOR-SPEC)
% specLabsim.motor.wmax = ((4000*2*pi())/60);  % [rad/s] - Nominal speed (RW-MOTOR-SPEC)

% Friction Torque
specCubesat.motor.Tfriction = 0.0001;          % [Nm] - Friction Torque


% ---------------- Flywheel ---------------- %

% Dimensions
specCubesat.flywheel.disk.length.r = 0.0270;          % [m] - disk radius
specCubesat.flywheel.ring.length.r = 0.0320;          % [m] - ring radius
specCubesat.flywheel.disk.length.h = 0.0010;          % [m] - disk height
specCubesat.flywheel.ring.length.h = 0.0100;          % [m] - ring height


% Mass
specCubesat.flywheel.mass = 0.10;           % [kg] - Flywheel mass

% ---------------- Coupling ---------------- %

% Mass
specCubesat.coupling.mass = 0.100;          % [kg] - Coupling mass


% ---------------- Electronics ---------------- %

% Mass
specCubesat.eletronics.mass = 0.500;


% ---------------- Cubesat ---------------- %

% Mass
% specCubesat.mass = 4.0;                       % [kg] - total mass
specCubesat.mass = 1.330;                     % [kg] - total mass


% Dynamic

% Max Pot + Max rpm ()


% Max Pot + Min rpm (Tmax)
specCubesat.Tmax = 0.000625; % [Nm] - Maximum Torque

% Min Pot + Max rpm (Tmin)
specCubesat.Tmin = 0.000100; % [Nm] - Maximum Torque

% Min Pot + Min rpm (Tstandby)
specCubesat.Tstandby = 0.000100; % [Nm] - Maximum Torque

%% Specification Laboratório de Simulações

% ---------------- Structure ---------------- %

% Mass
specLabsim.structure.mass = 2.0;   % [kg] - mass

% ---------------- Motor ---------------- %

% Motor Data

% Dynamics

% Mass
specLabsim.motor.mass = 0.50;               % [kg] - Weight of motor

% Dynamical Requirements
specLabsim.L = 2.0;               % [N.m.s] - The angular momentum of the wheel at maximum operational speed (nominal) should be at least 12 Nms with a tolerance of 1%
specLabsim.theta = 0.1;           % [deg] - The direction of rotation axis of the wheel shall be perpendicular to the mounting surface with a tolerance lower than or equal to 0.1 deg.
specLabsim.imbst = 0.4;           % [g.cm] - Residual static imbalance of the rotating parts shall be lower than 1.1 g.cm, and residual dynamic imbalance shall be lower than 10 g.cm2.
specLabsim.imbdy = 1.0;           % [g.cm^2] - Residual dynamic imbalance shall be lower than 1 g.cm2.
specLabsim.Tmax = 0.025;          % [N.m] - maximum motor torque
specLabsim.Tlmax = 0.005;         % [N.m] - maximum loss torque (friction torque)
specLabsim.wmax = ((10400*2*pi())/60);  % [rad/s] - Nominal speed (RW-MOTOR-SPEC)
% specLabsim.wmax = ((4000*2*pi())/60);  % [rad/s] - Nominal speed (RW-MOTOR-SPEC)

% Electrical Requirements
specLabsim.Pstandby = 2;          % [W] - at standby (RWA powered on and with null angular momentum)
specLabsim.Pmax = 25;             % [W] - at maximum operational speed and full torque
% specLabsim.Pmax = 2;             % [W] - at maximum operational speed and full torque

% ---------------- Flywheel ---------------- %

% Dimensions %
% Proj_R01
specLabsim.flywheel.diameter = 0.1501;       % [m] - maximum diameter
specLabsim.flywheel.height = 0.100;         % [m] - maximum height
specLabsim.flywheel.thickness = 0.005;      % [m] - thickness of the external layer 
% 
% Class I
% specLabsim.flywheel.diameter = 0.110;       % [m] - maximum diameter
% specLabsim.flywheel.height = 0.100;         % [m] - maximum height
% specLabsim.flywheel.thickness = 0.00;      % [m] - thickness of the external layer 
% 
% Class II
% specLabsim.flywheel.diameter = 0.150;       % [m] - maximum diameter
% specLabsim.flywheel.height = 0.100;         % [m] - maximum height
% specLabsim.flywheel.thickness = 0.00;      % [m] - thickness of the external layer 
% 
% Class III
% specLabsim.flywheel.diameter = 0.210;       % [m] - maximum diameter
% specLabsim.flywheel.height = 0.100;         % [m] - maximum height
% specLabsim.flywheel.thickness = 0.00;      % [m] - thickness of the external layer 

% ---------------- Coupling ---------------- %

% ---------------- Electronics ---------------- %

% ---------------- Labsim ---------------- %

% Mass %
specLabsim.mass = 2.5;            % [kg] - total mass
% 
% Class I
% specLabsim.mass = 3.0;            % [kg] - total mass
% 
% Class II
% specLabsim.mass = 4.0;            % [kg] - total mass
% 
% Class III
% specLabsim.mass = 6.0;            % [kg] - total mass

%% Specification Multi-Mission Plataform
specMmp.L = 12;               % [N.m.s] - The angular momentum of the wheel at maximum operational speed (nominal) should be at least 12 Nms with a tolerance of 1%
specMmp.theta = 0.1;          % [deg] - The direction of rotation axis of the wheel shall be perpendicular to the mounting surface with a tolerance lower than or equal to 0.1 deg.
specMmp.imbst = 1.1;          % [g.cm] - Residual static imbalance of the rotating parts shall be lower than 1.1 g.cm, and residual dynamic imbalance shall be lower than 10 g.cm2.
specMmp.imbdy = 10;           % [g.cm^2]
specMmp.Tmax = 0.075;         % [N.m] - maximum motor torque
specMmp.Tlmax = 0.025;        % [N.m] - maximum loss torque (friction torque)

% Dimensions %
specMmp.diameter = 0.25;      % [m] - maximum diameter
specMmp.height = 0.09;        % [mm] - maximum height

% Mass %

specMmp.mass = 5;           % [kg] - total mass

