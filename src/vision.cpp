#include <Arduino.h>
#include "../include/vision.h"



void Vision::updateEnemyPosition(DigitalSensor &front_sensor, DigitalSensor &full_left_sensor, DigitalSensor &full_right_sensor,  AnalogSensor &left_sensor,  AnalogSensor &right_sensor)
{
    //Primeiro salva onde ele tava depois tenta encontrar ele dnv.
    this->latest_enemy_position = this->enemy_position;

    if(front_sensor.enemy_close)
        this->enemy_position = EnemyPosition::FRONT;
    else if(full_left_sensor.enemy_close)
        this->enemy_position = EnemyPosition::FULL_LEFT;
    else if(full_right_sensor.enemy_close)
        this->enemy_position = EnemyPosition::FULL_RIGHT;
    else if(left_sensor.distance_cm <= 20)
        this->enemy_position = EnemyPosition::LEFT;
    else if(right_sensor.distance_cm <= 20)
        this->enemy_position = EnemyPosition::RIGHT;
}
