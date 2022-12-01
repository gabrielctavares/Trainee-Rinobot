#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H

#define ANALOG_TO_CM ((float)(20.0 / 2000.0))

class AnalogSensor
{
public:
    int raw_reading;
    int filtered_reading;
    int distance_cm;
    int pin;
    int readSensor();
    int filterSensor();
    AnalogSensor(int pin);
};

#endif