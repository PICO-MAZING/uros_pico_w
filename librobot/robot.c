#include "robot.h"

void forward_robot(robot *robot, int speed)
{
    forward_motor(&robot->motor_left, speed);
    forward_motor(&robot->motor_right, speed);
}

void backward_robot(robot *robot, int speed)
{
    backward_motor(&robot->motor_left, speed);
    backward_motor(&robot->motor_right, speed);
}

void left_robot(robot *robot, int speed)
{
    backward_motor(&robot->motor_left, speed);
    forward_motor(&robot->motor_right, speed);
}

void right_robot(robot *robot, int speed)
{
    forward_motor(&robot->motor_left, speed);
    backward_motor(&robot->motor_right, speed);
}

void brake_robot(robot *robot)
{
    brake_motor(&robot->motor_left);
    brake_motor(&robot->motor_right);
}