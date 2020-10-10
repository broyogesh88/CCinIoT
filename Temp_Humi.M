readChannelID = 1173739;
TemperatureFieldID = 1;
HumidityFieldID = 2;
readAPIKey = 'LQRCZR5S9P7EWQJ6';


data = thingSpeakRead(readChannelID,'Fields',[TemperatureFieldID HumidityFieldID],'NumPoints',200,'ReadKey',readAPIKey); 
% Read Temperature Data
temperatureData = data(:,1);

% Read Humidity Data
humidityData = data(:,2);

% Visualize the data
scatter(temperatureData,humidityData);
xlabel('Temperature');
ylabel('Humidity');
