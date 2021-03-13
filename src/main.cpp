#include <setup.h>
// Your GPRS credentials, if any
const char apn[] = "www";
const char gprsUser[] = "";
const char gprsPass[] = "";
// MQTT details
const char* broker = "broker.hivemq.com";
char topicbase[] ="dev";

#include <Pin.h>
Pin p1(7,"00p1");
Pin p2(8,"00p2");
Pin p3(9,"00p3");
Pin p4(10,"00p4");

uint32_t lastReconnectAttempt = 0;

void setup()
{
  SerialMon.begin(115200);
  delay(10);
  SerialMon.println("Starting...");
  //setting pins
  p1.init();p2.init();p3.init();p4.init();
  SerialMon.println("Pins Initialized...");
  // Set GSM module baud rate
  TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
  SerialMon.println("GSM module baud rate Set...");
  // SerialAT.begin(9600);
  delay(6000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();
  // modem.init();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);

  // Unlock your SIM card with a PIN if needed
  if ( GSM_PIN && modem.getSimStatus() != 3 ) {
    modem.simUnlock(GSM_PIN);
  }
  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success");

  if (modem.isNetworkConnected()) {
    SerialMon.println("Network connected");
  }
  // GPRS connection parameters are usually set after network registration
    SerialMon.print(F("Connecting to "));
    SerialMon.print(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      SerialMon.println(" fail");
      delay(10000);
      return;
    }
    SerialMon.println(" success");

  if (modem.isGprsConnected()) {
    SerialMon.println("GPRS connected");
  }
  // MQTT Broker setup
  mqtt.setServer(broker, 1883);
  mqtt.setCallback(mqttCallback);
}

void loop()
{
  // put your main code here, to run repeatedly:
}