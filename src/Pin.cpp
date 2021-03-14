#include <Arduino.h>
class Pin
{
public:
    uint8_t no;
    String topic;
    int status = LOW;
    Pin(uint8_t num, String topic_) {
        no=num;
        topic=topic_;
    }
    Pin(uint8_t num, String topic_,String base) {
        no=num;
        topic=topic_+base;
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
    void set(int status_){
        status= status_;
        digitalWrite(no,status_);
    }
};