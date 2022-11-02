#ifndef DIGITAL_SENSOR_H
#define DIGITAL_SENSOR_H

class DigitalSensor
{
public:
    int raw_reading;
    int filtered_reading;
    bool enemy_close;
    int pin;
    int readSensor();
    int filterSensor();
    DigitalSensor(int pin);
};

#endif