#include <Arduino.h>
#include "../include/analog_sensor.h"


AnalogSensor::AnalogSensor(int pin)
{
    this->pin = pin;
};

int AnalogSensor::readSensor()
{
    this->raw_reading = analogRead(this->pin);
    this->distance_cm = (int)(this->raw_reading * ANALOG_TO_CM);
    return this->distance_cm;
}
