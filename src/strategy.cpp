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
    if(this->start_time_ms == 0) {
        this->started = true;
        this->start_time_ms = millis();
    }
    
    if((millis() - this->start_time_ms) >= this->time_ms){
        left_motor.setPower(0);
        right_motor.setPower(0);    
        this->finished = true;    
        return true;
    }

    left_motor.setPower(this->left_motor_power);
    right_motor.setPower(this->right_motor_power);
    return false;
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

InitialStrategy::InitialStrategy(std::list<Move> moves): current_move(moves.front())
{  
    this->moves = moves;
    this->strategy_finished = false;
}
bool InitialStrategy::update(MotorControl &left_motor, MotorControl &right_motor){
    this->current_move.update(left_motor, right_motor);
    
    if(this->current_move.finished){
        this->moves.pop_front();

        if(!this->moves.empty())
            this->current_move = this->moves.front();
    }

    this->strategy_finished = this->moves.empty();
}

InitialStrategy* get_selected_strategy(int pinA, int pinB, int pinC){
    int estrategia = (4 * pinA) + (2 * pinB) + pinC;
    std::list<Move> moves;

    switch(estrategia){
        case 0:{
            //Direita - Frente - Esquerda
            moves.push_back(Move(80, 20, 1000));
            moves.push_back(Move(80, 80, 1000));
            moves.push_back(Move(20, 80, 1000));
            break;  
        }
        case 1:{
            //Esquerda - Frente - Direita
            moves.push_back(Move(20, 80, 1000));
            moves.push_back(Move(80, 80, 1000));
            moves.push_back(Move(80, 20, 1000));
            break;  
        }
        case 2:{
            //Frente - Direita - Frente
            moves.push_back(Move(100, 100, 1000));
            moves.push_back(Move(80, 20, 1000));
            moves.push_back(Move(100, 100, 1000));
            break;  
        }
        case 3:{
            //Frente - Esquerda - Frente
            moves.push_back(Move(100, 100, 1000));
            moves.push_back(Move(20, 80, 1000));
            moves.push_back(Move(100, 100, 1000));
            break;  
        }
        case 4:{
            //Direita - Frente - Esquerda - FrenteFull
            moves.push_back(Move(80, 20, 1000));
            moves.push_back(Move(80, 80, 1000));
            moves.push_back(Move(20, 80, 1000));
            moves.push_back(Move(100, 100, 1000));
            break;  
        }
        case 5:{
            //Esquerda - Frente - Direita - FrenteFull
            moves.push_back(Move(20, 80, 1000));
            moves.push_back(Move(80, 80, 1000));
            moves.push_back(Move(80, 20, 1000));
            moves.push_back(Move(100, 100, 1000));
            break;  
        }
        case 6:{
            //Lesminha - direita - frente - esquerda
            moves.push_back(Move(50, 10, 1500));
            moves.push_back(Move(50, 50, 1500));
            moves.push_back(Move(10, 50, 1500));
            break;  
        }
        case 7:{
            // Ao Infinito e além
            moves.push_back(Move(100, 100, 4000));
            break;  
        }
    }

    return new InitialStrategy(moves); // TODO
}