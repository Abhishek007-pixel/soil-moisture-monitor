clc;
clear;

% Configure Serial Port (Change 'COM21' to your port)
serialPort = 'COM21'; 
baudRate = 9600; 

% Create Serial Port Object
s = serialport(serialPort, baudRate, 'Timeout', 2);

% Wait for Serial Connection
disp('Waiting for data from PSoC...');
pause(2); % Allow time for connection setup

% Create Figure for Real-Time Display
figure('Name', 'Soil Moisture & Voltage Data', 'NumberTitle', 'off');

% Text Display (Instead of Plot)
moistureText = uicontrol('Style', 'text', 'Position', [50, 150, 250, 40], ...
                         'FontSize', 14, 'FontWeight', 'bold', 'ForegroundColor', 'b');
voltageText = uicontrol('Style', 'text', 'Position', [50, 100, 250, 40], ...
                        'FontSize', 14, 'FontWeight', 'bold', 'ForegroundColor', 'r');

% Continuous Data Reading Loop
while true
    try
        % Check if Data is Available
        if s.NumBytesAvailable > 0
            % Read the Data Line
            rawData = readline(s);
            disp(['Raw Data: ', rawData]);

            % Standardized Data Parsing (More Robust)
            tokens = regexp(rawData, 'Moisture: ([a-zA-Z]+), Voltage: ([\d\.]+)V', 'tokens');

            if ~isempty(tokens)
                % Extract Soil Moisture State and Voltage
                moistureState = strtrim(tokens{1}{1}); % Remove extra spaces if any
                voltage = str2double(tokens{1}{2});

                % Update UI Text
                moistureText.String = sprintf('Moisture: %s', moistureState);
                voltageText.String = sprintf('Voltage: %.2f V', voltage);
                
                % Log Data to Console
                fprintf('Moisture: %s, Voltage: %.2f V\n', moistureState, voltage);
            else
                warning('Data format mismatch: %s', rawData);
            end
        end
    catch err
        warning('Error reading data: %s', errmessage);
    end
    pause(1); % Small delay to prevent CPU overload
end


