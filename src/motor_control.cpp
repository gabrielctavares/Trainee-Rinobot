#include <Arduino.h>
#include "../include/motor_control.h"

MotorConfig::MotorConfig(int pwm_pin, int in1_pin, int in2_pin, float speed_const, int channel)
{
    this->pwm_pin = pwm_pin;
    this->in1_pin = in1_pin;
    this->in2_pin = in2_pin;
    this->speed_const = speed_const;
    this->channel = channel;
}

MotorControl::MotorControl(int pwm_pin, int in1_pin, int in2_pin, float speed_const, int channel): config(pwm_pin, in1_pin, in2_pin, speed_const, channel)
{
    
    
}

void MotorControl::setPower(int power)
{    
    this->power = abs(power);
    
    if(this->power > abs(this->max_power))
        this->power = abs(this->max_power);
        
    digitalWrite(this->config.in1_pin, power >= 0);
    digitalWrite(this->config.in2_pin, power < 0);
    ledcWrite(this->config.channel, map(this->power, 0, 100, 0, 255));
}
