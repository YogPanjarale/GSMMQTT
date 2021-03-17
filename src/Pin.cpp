#include <Arduino.h>
class Pin
{
public:
    uint8_t no;
    char tchar;
    String topic;
    int status = LOW;
    int mode;
    Pin(uint8_t num)
    {
        no = num;
    }
    Pin(uint8_t num, String topic_)
    {
        no = num;
        topic = topic_;
        tchar = topic_.charAt(-1);
    }
    Pin(uint8_t num, String topic_, String base)
    {
        no = num;
        topic = topic_ + base;
        tchar = topic_.charAt(-1);
    }
    //set The pinmode to
    void init()
    {
        mode = OUTPUT;
        pinMode(no, OUTPUT);
    }
    void init(int mode_)
    {
        mode = mode_;
        pinMode(no, mode_);
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
    void set(int status_)
    {
        status = status_;
        digitalWrite(no, status_);
    }
    int analogReadp()
    {
        if (mode == INPUT)
        {
            return analogRead(no);
        }
        //TODO:remove this if it takes up memory
        Serial.println(F("Pin mode is not Input still Tried to use anologRead"));
        return 0;
    }
};