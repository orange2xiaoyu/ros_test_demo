#include "ros/ros.h"

/*
    需求：修改参数服务器中turtlesim的背景色相关的参数
        参数的键：/turtlesim/background_b
                /turtlesim/background_g
                /turtlesim/background_r

    实现：
        1.初始化ros节点
        2.不一定需要创建节点句柄（和后续API有关）
        3.修改参数

*/


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "change_bg_color");
    ros::param::set("/turtlesim/background_b",0);
    ros::param::set("/turtlesim/background_g",0);
    ros::param::set("/turtlesim/background_r",0);
    return 0;
}
