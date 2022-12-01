#ifndef VISION_H
#define VISION_H

#include "analog_sensor.h"
#include "digital_sensor.h"

namespace EnemyPosition
{
    enum Pos
    {
        LEFT,
        RIGHT,
        FRONT,
        FULL_LEFT,
        FULL_RIGHT,
        SEARCH_LEFT,
        SEARCH_RIGHT
    };
}

class Vision
{
public:
    EnemyPosition::Pos enemy_position;
    EnemyPosition::Pos latest_enemy_position;
    void updateEnemyPosition(DigitalSensor &front_sensor,
    DigitalSensor &full_left_sensor,
    DigitalSensor &full_right_sensor, 
    AnalogSensor &left_sensor, 
    AnalogSensor &right_sensor);
};

#endif