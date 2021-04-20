#include <Arduino.h>
#include <setup.h>
// Your GPRS credentials, if any
char *apn = (char *)"www";
const char gprsUser[] = "";
const char gprsPass[] = "";

#include <details.h>
//phone number to send report logs
const char logNumber[] = YOURLOGSPHONENUMBER;
// MQTT details
const char *broker = MYMQTTBROKER;
const char topicbase[] = "dev01/";
const char topicToSubscribe[] = "dev01/#";
const char clientName[] = "dev01";
const char logsPath[] = "dev01/log";
const char subPinPath[] = "/pin/";
#define isAuth IsAuth
const char mqttUserName[] = MYMQTTUSERNAME;
const char mqttUserpass[] = MYMQTTUSERPSSWORD;
#include <battery.h>
#include <Pin.h>
Pin p1(7, "00p1");
Pin p2(8, "00p2");
Pin p3(9, "00p3");
Pin p4(10, "00p4");
Pin batteryRelay(11);
int a0 = A0; //A0 pin number
Battery battery;
uint32_t lastReconnectAttempt = 0;

//Call back fuction for mqtt , gets called when a messgage arrives
void mqttCallback(char *topic, byte *payload, unsigned int len)
{
  SerialMon.print(F("Message arrived ["));
  SerialMon.print(topic);
  SerialMon.print("]: ");
  SerialMon.write(payload, len);
  SerialMon.println();
  String stopic = topic;
  int lengthRequired = sizeof(topicbase) + sizeof(subPinPath);
  //Check if message is valid and then turn on/off pins
  if (stopic.indexOf(subPinPath) >= 0 && len == (unsigned)lengthRequired && isdigit(stopic[-1]))
  {
    SerialMon.println("Valid Topic for Pin");
    String p = (char *)payload;
    int status = (p.charAt(0) == '0') ? LOW : HIGH;
    String msg = "Pin n turned " + status ? "HIGH" : "LOW";
    char a = 'n';
    switch (topic[-1])
    {
    case '1':
      p1.set(status);
      a = '1';
      break;
    case '2':
      p2.set(status);
      a = '2';
      break;
    case '3':
      p3.set(status);
      a = '3';
      break;
    case '4':
      p4.set(status);
      a = '4';
      break;
    default:
      SerialMon.println("NO PINS Matched");
      break;
    }
    msg.setCharAt(4, a);
    SerialMon.println(msg);
    char *msgc;
    msg.toCharArray(msgc, 20);
    mqtt.publish(logsPath, msgc);
  }
}

boolean mqttConnect()
{
  SerialMon.print("Connecting to ");
  SerialMon.print(broker);
  boolean status;
  // Connect to MQTT Broker
  if (isAuth)
  {
    status = mqtt.connect(clientName, mqttUserName, mqttUserpass);
  }
  else // Or, if you want to authenticate MQTT:
  {
    status = mqtt.connect(clientName);
  }
  if (status == false)
  {
    SerialMon.println(" fail");
    return false;
  }
  else{
  SerialMon.println(" Success");
  }
  char msg[50];
  snprintf(msg, 50, "%s Started", clientName);
  mqtt.publish(logsPath, msg);
  mqtt.subscribe(topicToSubscribe);
  return mqtt.connected();
}
String autoApn(String operatorName)
{
  SerialMon.println("==AUTO APN START==");
  String aapn = "";
  if (operatorName.indexOf("Airtel"))
  {
    aapn = "airtelgprs.com";
  }
  else if (operatorName.indexOf("BSNL"))
  {
    aapn = "bsnlnet";
  }
  else if (operatorName.indexOf("Idea"))
  {
    aapn = "internet";
  }
  else if (operatorName.indexOf("Vodafone"))
  {
    aapn = "www";
  }
  SerialMon.print("==APN:");
  SerialMon.print(aapn);
  SerialMon.println("==");
  return aapn;
}

void setup()
{
  // SerialMon.begin(115200);
  SerialMon.begin(9600);
  delay(10);
  SerialMon.println("Starting...");
  //setting pins
  p1.init(OUTPUT);
  p2.init(OUTPUT);
  p3.init(OUTPUT);
  p4.init(OUTPUT);
  batteryRelay.init(OUTPUT);
  analogReference(INTERNAL);
  battery.init(a0, 100000.00, 10000.00);
  battery.setRecommendedVoltage(10.5, 14);
  // apn = (char *)"www";
  SerialMon.println("Pins Initialized...");
  // Set GSM module baud rate
  int baud = TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
  SerialMon.println("GSM module baud rate Set...");
  SerialMon.println(baud);
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
  if (GSM_PIN && modem.getSimStatus() != 3)
  {
    modem.simUnlock(GSM_PIN);
  }

  String operatorName = modem.getOperator();
  String as = autoApn(operatorName); //apn String
  SerialMon.println(F("Auto Apn Configured \nOperator Name:"));
  SerialMon.print(operatorName);
  SerialMon.println("\nApn Name:");
  as.toCharArray(apn, 20);
  SerialMon.print(apn);
  SerialMon.println("Waiting for network...");
  if (!modem.waitForNetwork())
  {
    SerialMon.println(" fail");
    delay(10000);
    modem.sendSMS(logNumber, String("Unable to reach Network \n") + String(clientName));
    return;
  }
  SerialMon.println(" Success");

  if (modem.isNetworkConnected())
  {
    SerialMon.println(F("Network connected"));
  }
  // GPRS connection parameters are usually set after network registration
  SerialMon.print(F("Connecting to "));
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass))
  {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success");

  if (modem.isGprsConnected())
  {
    SerialMon.println("GPRS connected");
  }
  // MQTT Broker setup
  mqtt.setServer(broker, 1883);
  mqtt.setCallback(mqttCallback);
}
//TODO: push battery updates to mqtt
void checkBattery()
{
  float v = battery.voltage();
  if (v > battery.recommendedVoltageMax)
  {
    batteryRelay.off();
  }
  else if (v < battery.recommendedVoltageMin)
  {
    batteryRelay.on();
  }
}
void loop()
{
  if (!mqtt.connected())
  {
    SerialMon.println(F("=== MQTT NOT CONNECTED ==="));
    // Reconnect every 10 seconds
    uint32_t t = millis();
    if (t - lastReconnectAttempt > 10000L)
    {
      lastReconnectAttempt = t;
      if (mqttConnect())
      {
        lastReconnectAttempt = 0;
      }
    }
    delay(100);
    return;
  }
  checkBattery();
}