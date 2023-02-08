#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H

#define ANALOG_TO_CM  0.012837
#define MAX_RAW  4095

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