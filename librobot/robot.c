#include "motor.h"

void init_robot(robot *robot, motor *motor_left, motor *motor_right)
{
    robot->motor_left = motor_left;
    robot->motor_right = motor_right;
}

void forward_robot(robot *robot, int speed)
{
    forward_motor(robot->motor_left, speed);
    forward_motor(robot->motor_right, speed);
}

void backward_robot(robot *robot, int speed)
{
    backward_motor(robot->motor_left, speed);
    backward_motor(robot->motor_right, speed);
}

void left_robot(robot *robot, int speed)
{
    backward_motor(robot->motor_left, speed);
    forward_motor(robot->motor_right, speed);
}

void right_robot(robot *robot, int speed)
{
    forward_motor(robot->motor_left, speed);
    backward_motor(robot->motor_right, speed);
}

void backward_robot(robot *robot, int speed)
{
    brake_motor(robot->motor_left);
    brake_motor(robot->motor_right);
}