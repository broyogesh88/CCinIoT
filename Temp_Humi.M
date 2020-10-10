readChannelID = % Channel Number;
TemperatureFieldID = 1;
HumidityFieldID = 2;
readAPIKey = 'Paste your read API Key';


data = thingSpeakRead(readChannelID,'Fields',[TemperatureFieldID HumidityFieldID],'NumPoints',200,'ReadKey',readAPIKey); 
% Read Temperature Data
temperatureData = data(:,1);

% Read Humidity Data
humidityData = data(:,2);

% Visualize the data
scatter(temperatureData,humidityData);
xlabel('Temperature');
ylabel('Humidity');
