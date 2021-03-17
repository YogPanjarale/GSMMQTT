#ifndef BATTERYSYSTEM_V
#define BATTERYSYSTEM_V
#include <Pin.h>
class Battery
{
private:
    float denominator;

public:
    uint8_t pin;
    float Vout; //in middle of R1 and R2 ( +ve )R1----Vout----R2( -ve )
    float Vin;// real voltage connected to +ve terminal 
    float R1; // resistance of R1 (100K) connected to +
    float R2; // resistance of R2 (10K) connected to -
    float recommendedVoltage;
    void setRecommendedVoltage(){}
    Battery(){}
    Battery(uint8_t pin, float R1_, float R2_) {}
    void init(uint8_t pin, float R1_, float R2_) {}
    float voltage();
};

#endif
/*Voltage meter refrence
int analogInput = 1;
float Vout = 0.00;
float Vin = 0.00;
float R1 = 100000.00; // resistance of R1 (100K) 
float R2 = 10000.00; // resistance of R2 (10K) 
int val = 0;
void setup(){
   pinMode(analogInput, INPUT); //assigning the input port
   Serial.begin(9600); //BaudRate
}
void loop(){
   
   val = analogRead(analogInput);//reads the analog input
   Vout = (val * 5.00) / 1024.00; // formula for calculating voltage out i.e. V+, here 5.00
   Vin = Vout / (R2/(R1+R2)); // formula for calculating voltage in i.e. GND
   if (Vin<0.09)//condition 
   {
     Vin=0.00;//statement to quash undesired reading !
  } 
Serial.print("\t Voltage of the given source = ");
Serial.print(Vin);
delay(1000); //for maintaining the speed of the output in serial moniter
}
*/