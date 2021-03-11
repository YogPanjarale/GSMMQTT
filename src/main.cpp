#include <Arduino.h>
#include <TinyGsmClient.h>
#include <SoftwareSerial.h>
#include <StreamDebugger.h>

//select your modem:
#define TINY_GSM_MODEM_SIM800

//set serial for debug console (to serial Monitor)
#define SerialMon Serial
//Software Sreial on Uno, Nano
SoftwareSerial SerialAT(2, 3); //RX,TX
//Set Serial for AT commands (to the module)
// #define SerialAT Serial1

// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon

// Range to attempt to autobaud
#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 115200

// Define how you're planning to connect to the internet
#define TINY_GSM_USE_GPRS true
// set GSM PIN, if any
#define GSM_PIN ""
// Your GPRS credentials, if any
const char apn[] = "www";
const char gprsUser[] = "";
const char gprsPass[] = "";

// MQTT details
const char *broker = "broker.hivemq.com";

#define DUMP_AT_COMMANDS
#ifdef DUMP_AT_COMMANDS
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif
TinyGsmClient client(modem);
PubSubClient mqtt(client);


void setup()
{
  SerialMon.begin(115200);
  delay(10);
  //settings pins
  pinMode()
}

void loop()
{
  // put your main code here, to run repeatedly:
}