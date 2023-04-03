#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "librobot/motor.h"

enum state
{
    STOP,
    FORWARD,
    RIGHT,
    BACKWARD,
    LEFT
};

typedef struct robot
{
    motor *motor_left;
    motor *motor_right;
    state state = STOP;
} robot;

void init_robot(robot *robot, motor *motor_left, motor *motor_right);

void forward_robot(robot *robot, int speed);

void backward_robot(robot *robot, int speed);

void left_robot(robot *robot, int speed);

void right_robot(robot *robot, int speed);

void brake_robot(robot *robot);

#endif