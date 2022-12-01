#include <Arduino.h>
#include "micro_start.h"


uStart::uStart(int signal_pin)
{
    this->signal_pin = signal_pin;
    this->state =  uStartState::STOP;
};

void uStart::update()
{
    // Arduino::HIGH existe?
    this->state = (digitalRead(this->signal_pin) == 1 ) ? uStartState::START : uStartState::STOP;
}
