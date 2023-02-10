#include <Arduino.h>
#include "../include/motor_control.h"

MotorConfig::MotorConfig(int pwm_pin, int in1_pin, int in2_pin, float speed_const)
{
    this->pwm_pin = pwm_pin;
    this->in1_pin = in1_pin;
    this->in2_pin = in2_pin;
    this->speed_const = speed_const;
}

MotorControl::MotorControl(int pwm_pin, int in1_pin, int in2_pin, float speed_const): config(pwm_pin, in1_pin, in2_pin, speed_const)
{
    
    
}

void MotorControl::setPower(int power)
{    
    this->power = abs((abs(power) > abs(this->max_power)) ? this->max_power : power); 

    digitalWrite(this->config.in1_pin, power >= 0);
    digitalWrite(this->config.in2_pin, power < 0);
    ledcWrite(this->config.pwm_pin, map(this->power, 0, 100, 0, 255));
}
