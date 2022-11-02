#include <Arduino.h>
#include "robot.h"



Robot::Robot()
{
    this->robot_state = RobotState::AWAITING_START;
    this->ustart = new uStart(MICRO_START_SIGNAL_PIN);
    this->front_sensor = new DigitalSensor(FRONT_SENSOR_PIN);
    this->full_left_sensor = new DigitalSensor(FULL_LEFT_SENSOR_PIN);
    this->full_right_sensor = new DigitalSensor(FULL_RIGHT_SENSOR_PIN);
    this->left_sensor = new AnalogSensor(LEFT_SENSOR_PIN);
    this->right_sensor = new AnalogSensor(RIGHT_SENSOR_PIN);
    this->left_motor = new MotorControl(LEFT_MOTOR_PWM_PIN, LEFT_MOTOR_IN1_PIN, LEFT_MOTOR_IN2_PIN, LEFT_MOTOR_SPEED_CONST);
    this->right_motor = new MotorControl(RIGHT_MOTOR_PWM_PIN, RIGHT_MOTOR_IN1_PIN, RIGHT_MOTOR_IN2_PIN, RIGHT_MOTOR_SPEED_CONST);
    this->vision = new Vision();
    this->auto_strategy = new AutoStrategy();
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
    this->vision.updateEnemyPosition(this->front_sensor, this->full_left_sensor, this->full_right_sensor, this->left_sensor, this->right_sensor);
    this->auto_strategy.updateMotors(this->vision, this->left_motor, this->right_motor);

}


