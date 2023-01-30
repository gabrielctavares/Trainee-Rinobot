#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H

#define COEFFICIENT_A -0,004884004884;
#define COEFFICIENT_B 40;

class AnalogSensor
{
public:
    int raw_reading;
    int filtered_reading;
    int distance_cm;
    int pin;
    int readSensor();
    int filterSensor();
    int convertToCM();
    AnalogSensor(int pin);
};

#endif