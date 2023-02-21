#include <ros/ros.h>
#include <ros/network.h>
#include <geometry_msgs/Twist.h>

/**
 * This tutorial demonstrates how to send a velocity command to a p2os robot
 */
const double TWIST_LINEAR_MAX= 0.5; //.5 m/s forward
const double TWIST_ANGULAR_MAX = 0.31; //0 rad/s 
double run_time =0.0;
double delta_time = 0.05;
double w_time_ang = 0.5;
double w_time_lin = 1.0;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "simple_move_publisher");
    ros::NodeHandle n; 
    ros::Publisher cmd_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 100);  
    ros::Rate loop_rate(10);
    
    while (ros::ok())
    {
        run_time += delta_time;

        geometry_msgs::Twist cmd_msg;
        cmd_msg.linear.x = TWIST_LINEAR_MAX * sin(run_time*w_time_lin);
        cmd_msg.angular.z = TWIST_ANGULAR_MAX * sin(run_time*w_time_ang);
        
        
        cmd_pub.publish(cmd_msg);
        
        ros::spinOnce();
        
        loop_rate.sleep();
    }
    
    
    return 0;
}