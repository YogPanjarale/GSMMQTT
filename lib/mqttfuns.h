#ifndef MQTTFUNCS
#define MQTTFUNCS
void mqttCallback(char* topic, byte* payload, unsigned int len);
boolean mqttConnect();
#endif