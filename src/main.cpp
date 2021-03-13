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
  SerialMon.println("Initializing pins...");
  //setting pins
  p1.init();p2.init();p3.init();p4.init();


}

void loop()
{
  // put your main code here, to run repeatedly:
}