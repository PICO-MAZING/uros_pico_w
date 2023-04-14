#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "librobot/motor.h"
#include "librobot/sensor.h"

typedef enum
{
    STOP,
    FORWARD,
    RIGHT,
    BACKWARD,
    LEFT
} state;

typedef struct robot
{
    state state;
    motor motor_left;
    motor motor_right;
    sensor wall;
    sensor ground;
} robot;

void forward_robot(robot *robot, int speed);

void backward_robot(robot *robot, int speed);

void left_robot(robot *robot, int speed);

void right_robot(robot *robot, int speed);

void brake_robot(robot *robot);

uint8_t read_sensors(sensor *wall, sensor *ground);

#endif