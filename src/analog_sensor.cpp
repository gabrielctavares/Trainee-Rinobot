#include <Arduino.h>
#include "../include/analog_sensor.h"


AnalogSensor::AnalogSensor(int pin)
{
    this->pin = pin;
};

int AnalogSensor::filterSensor()
{       
    return this->raw_reading;
}

int AnalogSensor::readSensor()
{
    this->raw_reading = analogRead(this->pin);
    this->filtered_reading = filterSensor();
    this->distance_cm = ((int)(this->filtered_reading * ANALOG_TO_CM));
    return this->distance_cm;
}
