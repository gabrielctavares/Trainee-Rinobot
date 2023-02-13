#include <Arduino.h>
#include "../include/robot.h"

Robot::Robot()
: ustart(MICRO_START_SIGNAL_PIN),
  front_sensor(FRONT_SENSOR_PIN),
  full_left_sensor(FULL_LEFT_SENSOR_PIN),
  full_right_sensor(FULL_RIGHT_SENSOR_PIN),
  left_sensor(LEFT_SENSOR_PIN),
  right_sensor(RIGHT_SENSOR_PIN),
  left_motor(LEFT_MOTOR_PWM_PIN, LEFT_MOTOR_IN1_PIN, LEFT_MOTOR_IN2_PIN, LEFT_MOTOR_SPEED_CONST, LEFT_MOTOR_CHANNEL),
  right_motor(RIGHT_MOTOR_PWM_PIN, RIGHT_MOTOR_IN1_PIN, RIGHT_MOTOR_IN2_PIN, RIGHT_MOTOR_SPEED_CONST, RIGHT_MOTOR_CHANNEL),
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

    if(this->ustart.state == uStartState::START){
        switch(this->robot_state){
            case RobotState::AWAITING_START: {
                this->initial_strategy = get_selected_strategy(STRATEGY_PIN_A, STRATEGY_PIN_B, STRATEGY_PIN_C);
                this->robot_state == RobotState::INITIAL_STRATEGY;
                break;
            }
            case RobotState::INITIAL_STRATEGY: {
                this->initial_strategy->update(this->left_motor, this->right_motor);
            
                if(this->initial_strategy->strategy_finished)
                    this->robot_state == RobotState::AUTO_STRATEGY;
                break;
            }
            case RobotState::AUTO_STRATEGY: {
                this->auto_strategy.updateMotors(this->vision, this->left_motor, this->right_motor);
                break;
            }
        }                
    }
    else{
        this->robot_state == RobotState::STOPPED;
        this->left_motor.setPower(0);
        this->right_motor.setPower(0);
    }        
}


