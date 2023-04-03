#include <stdio.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/int32.h>
#include <geometry_msgs/msg/twist.h>

#include <rmw_microros/rmw_microros.h>

#include "pico/stdlib.h"
#include "pico_wifi_transport.h"
#include "librobot/motor.h"

motor motor_left;
motor motor_right;
bool forward = false;

rcl_subscription_t subscriber;
rcl_publisher_t publisher;
std_msgs__msg__Int32 msg;
// geometry_msgs__msg__Twist msg_pub;
geometry_msgs__msg__Twist msg_sub;
// std_msgs__msg__Int32 msg_sub;
void timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    // rcl_publish(&publisher, &msg_pub, NULL);
    rcl_publish(&publisher, &msg, NULL);
    msg.data++;
    if (forward)
    {
        forward_motor(&motor_left, 250);
        forward_motor(&motor_right, 250);
    }
    else
    {
        brake_motor(&motor_left);
        brake_motor(&motor_right);
        //stop_motor(&motor_left);
        //stop_motor(&motor_right);
    }
}

void subscription_callback(const void *msgin)
{
    // printf("Hi");
    const geometry_msgs__msg__Twist *msg = (const geometry_msgs__msg__Twist *)msgin;
    printf("Received %lf\n", msg->linear.x);

    forward = !forward;

    // const std_msgs__msg__Int32 *msg = (const std_msgs__msg__Int32 *)msgin;
    // printf("STD MSG %d", msg->data);
}

int main()
{
    init_motor(&motor_left, 18, 17, 16);
    init_motor(&motor_right, 19, 20, 22);
    // set_microros_wifi_transports("BassAdict", "$lap2023", "192.168.137.115", 4444);
    // set_microros_wifi_transports("NETGEAR13", "purplefire019", "10.0.0.8", 4444);
    // set_microros_wifi_transports("DLINK204-1", "eabux63999", "172.16.204.234", 4444);
    set_microros_wifi_transports("allan-VivoBook", "f5CgQFMa", "10.42.0.1", 4444);

    rcl_timer_t timer;
    rcl_node_t node;
    rcl_allocator_t allocator;
    rclc_support_t support;
    rclc_executor_t executor;

    allocator = rcl_get_default_allocator();

    // Wait for agent successful ping for 2 minutes.
    const int timeout_ms = 1000;
    const uint8_t attempts = 120;

    rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);

    if (ret != RCL_RET_OK)
    {
        // Unreachable agent, exiting program.
        printf("Agent unreachable. Exiting...");
        return ret;
    }

    rclc_support_init(&support, 0, NULL, &allocator);

    rclc_node_init_default(&node, "pico_node", "", &support);

    rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
        // ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "cmd_vel");
    /*
        rclc_publisher_init_default(
            &publisher,
            &node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
            // ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
            "cmd_vel");
            */

    rclc_publisher_init_default(
        &publisher,
        &node,
        // ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "topic");

    rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(1000),
        timer_callback);

    rclc_executor_init(&executor, &support.context, 3, &allocator);
    rclc_executor_add_timer(&executor, &timer);
    rclc_executor_add_subscription(&executor, &subscriber, &msg_sub, &subscription_callback, ON_NEW_DATA);

    // msg_pub.linear.x = 1;
    msg.data = 1;
    while (ret == RCL_RET_OK)
    {
        rcl_ret_t ret = rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        sleep_ms(10);
    }
    printf("GOODBYE");
    return 0;
}