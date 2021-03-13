#ifndef PIN_H
#define PIN_H
class Pin
{
public:
    int no;
    char* topic;
    int status;
    Pin(int num,char topic_[]) {}
    void init(){}
    void on(){}
    void off(){}
    void toggle(){}
};
#endif