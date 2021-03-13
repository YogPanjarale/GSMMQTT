#include <Arduino.h>
void mqttCallback(char* topic, byte* payload, unsigned int len) {
  SerialMon.print("Message arrived [");
  SerialMon.print(topic);
  SerialMon.print("]: ");
  SerialMon.write(payload, len);
  SerialMon.println();

  // Only proceed if incoming message's topic matches
  if (String(topic) == topicLed) {
    ledStatus = !ledStatus;
    digitalWrite(LED_PIN, ledStatus);
    mqtt.publish(topicLedStatus, ledStatus ? "1" : "0");
  }
}

boolean mqttConnect() {
  SerialMon.print("Connecting to ");
  SerialMon.print(broker);

  // Connect to MQTT Broker
  boolean status = mqtt.connect("GsmClientTest");

  // Or, if you want to authenticate MQTT:
  //boolean status = mqtt.connect("GsmClientName", "mqtt_user", "mqtt_pass");

  if (status == false) {
    SerialMon.println(" fail");
    return false;
  }
  SerialMon.println(" success");
  mqtt.publish(topicInit, "GsmClientTest started");
  mqtt.subscribe(topicLed);
  return mqtt.connected();
}
