#include <Arduino.h>
#include <SoftwareSerial.h>
//select your modem:
#define TINY_GSM_MODEM_SIM900 // first define this then include tinygsm ans other libs
#include <TinyGsmClient.h>
#include <StreamDebugger.h>
#include <PubSubClient.h>

//set serial for debug console (to serial Monitor)
#define SerialMon Serial
//Software Sreial on Uno, Nano
SoftwareSerial SerialAT(2, 3); //RX,TX
//Set Serial for AT commands (to the module)
// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon

// Range to attempt to autobaud
#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 115200

// Define how you're planning to connect to the internet
#define TINY_GSM_USE_GPRS true
// set GSM PIN, if any
#define GSM_PIN ""

#define DUMP_AT_COMMANDS
#ifdef DUMP_AT_COMMANDS
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif
TinyGsmClient client(modem);
PubSubClient mqtt(client);
