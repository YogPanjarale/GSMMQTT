#include <Pin.h>
class Battery
{
private:
    float denominator;

public:
    uint8_t pin;
    float Vout; //in middle of R1 and R2 ( +ve )R1----Vout----R2( -ve )
    float Vin;  // real voltage connected to +ve terminal
    float R1;   // resistance of R1 (100K) connected to +
    float R2;   // resistance of R2 (10K) connected to -
    float recommendedVoltageMin;
    float recommendedVoltageMax;
    void setRecommendedVoltage(float min, float max)
    {
        recommendedVoltageMin = min;
        recommendedVoltageMax = max;
    }
    /*in middle of R1 and R2 ( +ve )R1----Vout----R2( -ve )
    real voltage connected to +ve terminal
    resistance of R1 (100K) connected to +
    resistance of R2 (10K) connected to -*/
    Battery() {}
    Battery(int pin_, float R1_, float R2_)
    {
        pin = pin_;
        R1 = R1_;
        R2 = R2_;
    }
    void init(int pin_, float R1_, float R2_)
    {
        pin = pin_;
        R1 = R1_;
        R2 = R2_;
    }
    float voltage()
    {
        int val = analogRead(pin);
        // Vout = (val * 5.00) / 1024.00; // formula for calculating voltage out i.e. V+, here 5.00
        //Internal reference is set to 1.1 with analogReference(INTERNAL)
        Vout = (val * 1.1) / 1024.00; // formula for calculating voltage out i.e. V+, here 5.00 //
        Vin = Vout / (R2 / (R1 + R2)); // formula for calculating voltage in i.e. GND
        if (Vin < 0.09)                //condition
        {
            Vin = 0.00; //statement to quash undesired reading !
        }
        Serial.print("Battery Voltage: ");
        Serial.print(Vin);
        Serial.println();
        // // read normal Arduino value
        // int in0 = analogRead(A0);
        // float val0 = in0 * 5.0 / 1024.0;

        // // read correct supply voltage

        // float supply = readVcc() / 1000.0;
        // float val0Corrected = supply / 5 * val0;
        return Vin;
    }
};

long readVcc()
{
    long result;
    // Read 1.1V reference against AVcc
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
#else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif
    delay(2);            // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Convert
    while (bit_is_set(ADCSRA, ADSC))
        ;
    result = ADCL;
    result |= ADCH << 8;
    result = 1126400L / result; // Calculate Vcc (in mV); 1126400 = 1.1*1024*1000
    return result;
}
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
