#include <Arduino.h>
#include "../include/robot.h"

Robot::Robot()
: ustart(MICRO_START_SIGNAL_PIN),
  front_sensor(FRONT_SENSOR_PIN),
  full_left_sensor(FULL_LEFT_SENSOR_PIN),
  full_right_sensor(FULL_RIGHT_SENSOR_PIN),
  left_sensor(LEFT_SENSOR_PIN),
  right_sensor(RIGHT_SENSOR_PIN),
  left_motor(LEFT_MOTOR_PWM_PIN, LEFT_MOTOR_IN1_PIN, LEFT_MOTOR_IN2_PIN, LEFT_MOTOR_SPEED_CONST),
  right_motor(RIGHT_MOTOR_PWM_PIN, RIGHT_MOTOR_IN1_PIN, RIGHT_MOTOR_IN2_PIN, RIGHT_MOTOR_SPEED_CONST),
  vision(),
  auto_strategy()
{
    this->robot_state = RobotState::AWAITING_START;
}

void Robot::readSensors()
{
    this->front_sensor.readSensor();
    this->full_left_sensor.readSensor();
    this->full_right_sensor.readSensor();
    this->left_sensor.readSensor();
    this->right_sensor.readSensor();
}

void Robot::update()
{
    this->ustart.update();
    this->readSensors();
    this->vision.updateEnemyPosition(this->front_sensor, this->full_left_sensor, this->full_right_sensor, this->left_sensor, this->right_sensor);

    if(this->ustart.state == uStartState::START)
        this->auto_strategy.updateMotors(this->vision, this->left_motor, this->right_motor);
}


