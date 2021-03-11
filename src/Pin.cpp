#include <Arduino.h>
class Pin
{
public:
    int no;
    String topic;
    int status = LOW;
    Pin(int num, char* topic_) {
        no=num;
        topic=String(topic_);
    }
    void init()
    {
        pinMode(no, OUTPUT);
    }
    void on()
    {
        status = HIGH;
        digitalWrite(no, status);
    }
    void off()
    {
        status = LOW;
        digitalWrite(no, status);
    }
    void toggle()
    {
        status = !status;
        digitalWrite(no, status);
    }
};