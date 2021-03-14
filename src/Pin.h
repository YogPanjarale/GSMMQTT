#ifndef PIN_H
#define PIN_H
class Pin
{
public:
    int no;
    char *topic;
    int status;
    Pin(int num, String topic_) {}
    void init() {}
    void init(int mode) {}
    void on() {}
    void off() {}
    void toggle() {}
};
#endif