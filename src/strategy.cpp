#include <Arduino.h>
#include "../include/strategy.h"


Move::Move(int left_motor_power, int right_motor_power, int time_ms){
    this->left_motor_power = left_motor_power;
    this->right_motor_power = right_motor_power;
    this->time_ms = time_ms;
    this->start_time_ms = 0;
    this->started = false;
    this->finished = false;    
}

bool Move::update(MotorControl &left_motor, MotorControl &right_motor){
    this->started = true;
    left_motor.setPower(this->left_motor_power);
    right_motor.setPower(this->right_motor_power);
    delay(this->time_ms);
    left_motor.setPower(0);
    right_motor.setPower(0);    
    this->finished = true;
    return true;
}

void AutoStrategy::updateMotors(Vision &vision, MotorControl &left_motor, MotorControl &right_motor){
    int left_power = 0;
    int right_power = 0;

    switch(vision.enemy_position) {
        case EnemyPosition::LEFT:        
            left_power = 40;
            right_power = 80;
            break;
        case EnemyPosition::RIGHT:        
            left_power = 80;
            right_power = 40;
            break;
        case EnemyPosition::FRONT:
            left_power = 100;
            right_power = 100;
            break;
        case EnemyPosition::FULL_LEFT:        
            left_power = 10;
            right_power = 80;
            break;
        case EnemyPosition::FULL_RIGHT:        
            left_power = 80;
            right_power = 10;
            break;
    } 

    left_motor.setPower(left_power);
    right_motor.setPower(right_power);
}

InitialStrategy::InitialStrategy(std::list<Move> moves)
{  
    this->moves = moves;
    this->strategy_finished = false;
}
bool InitialStrategy::update(MotorControl &left_motor, MotorControl &right_motor){
    for(Move mov = this->moves.begin(); mov != this->moves.end(); ++mov){
        this->current_move = *mov;
        this->current_move->update(left_motor, right_motor);
    }
}
