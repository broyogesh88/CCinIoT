
#include <DHT.h> //DHT Library contains necessary files to read temperature and humidity using DHT11 Sensor
#include <SPI.h>
#include <Ethernet.h> // Ethernet Library to Connect your Arduino Uno with Ethernet Shield
#include <ThingSpeak.h> // Thingspeak Library inclusion


#define WRITE_DELAY_FOR_THINGSPEAK 15000 // Delay should be atleast 15 Seconds to update data in Thingspeak
#define DHTPIN 5   // Pin No. 5 is use to get the data from DHT11 Sensor
#define DHTTYPE DHT11  // Defining Type of DHT Sensor (DHT11 sensor gives temperature with +-2 degree accuracy and +-5 % humidity accuracy
DHT dht(DHTPIN, DHTTYPE); //creating a object of type dht

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE,0xED}; // Assigning default MAC Address to my Ethernet Shield
IPAddress ip(192,168,1,150); // Deafault Router IP
EthernetClient client;

unsigned long channelNumber = 1173739;
unsigned long commandNumber = 1182645;
const char * key = "IXM5CQRP2OGQPORP";
const char * readKey = "1B5MBHB1QBKG3QQM";


long lastWriteTime = 0;
long lastReadTime = 0;
float responseValue = 0;

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  ThingSpeak.begin(client);
  dht.begin();
  pinMode(7,OUTPUT);
  Serial.println("Setup completed");
  delay(1000);
}


void loop()
{
  if (millis() - lastWriteTime > 20000)
  {
      Serial.println("Reading Sensors' Values...");
      float temp = dht.readTemperature();
      float humi = dht.readHumidity();

      // Code to Write Data read from DHT11 Sensor in Thingspeak
      if (isnan(temp) || isnan(humi))
      {
        Serial.println("Failed to read data from DHT");
      }
      else
      {
          Serial.println("Temperature = " + String(temp)+" °C");
          Serial.println("Humidity = "+ String(humi)+" %");
          ThingSpeak.setField(1,temp); // Field 1 is Temperature
          ThingSpeak.setField(2,humi); // Field 2 is Humidity
          ThingSpeak.setField(3, responseValue); // Field 3 is Current LED State
          ThingSpeak.writeFields(channelNumber, key); // Writing Data in Things Speak Cloud
          lastWriteTime = millis();
      }
  }

    // Code to Switch Off LED Light using ViVirtuino Mobile App
   if (millis() - lastReadTime > 15000)
   {
      float value = ThingSpeak.readFloatField(commandNumber, 1, readKey);
      Serial.println("Read thingSpeak channel commands field 1 last value = "+ String(value));

      if (value == 0)
        digitalWrite(7,LOW); // Turning Led Off
      else
        digitalWrite(7,HIGH); // Turning Led On

      responseValue = value;
      lastReadTime = millis();
   }
} 
