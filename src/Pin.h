#ifndef PIN_H
#define PIN_H
#include <Arduino.h>
class Pin
{
public:
    uint8_t no;
    char tchar;
    String topic;
    int topicInt;
    int status;
    Pin(uint8_t num){}
    Pin(uint8_t num, String topic_){}
    Pin(uint8_t num, String topic_,String base){}
    void init(){}
    void init(int mode){}
    void on(){}
    void off(){}
    void toggle(){}
    void set(int status_){}
};
#endif