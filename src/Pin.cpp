#include <Arduino.h>
class Pin
{
public:
    int no;
    String topic;
    int status = LOW;
    Pin(int num, String topic_) {
        no=num;
        topic=String(topic_);
    }
    //set The pinmode to
    void init()
    {
        pinMode(no, OUTPUT);
    }
    void init(int mode)
    {
        pinMode(no,mode);
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