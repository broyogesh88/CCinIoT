#include <SoftwareSerial.h>       //Software Serial library
#define DEBUG true
#define RX 3
#define TX 4

//String HOST = "api.thingspeak.com";
String HOST = "184.106.153.149";
String PORT = "80";
String AP = "your access point name";
String PASS = "password of your access point";

String API = "your write key";
String field = "your field";

int countTrueCommand;
int countTimeCommand;
boolean found = false;

void setup()
{

}

void loop()
{

}

