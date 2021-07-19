#include "ros/ros.h"

/*
    演示参数删除
    实现：
        ros::nodeHandle
            deleteParam()
        ros::param
            del()

*/



int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc,argv,"del_param_c");
    ros::NodeHandle nh;

    //删除：nodehandle
    bool flag1 = nh.deleteParam("radius");
    if (flag1)
    {
        ROS_INFO("success!");
    }else
    {
        ROS_INFO("default");
    }

    //删除：param
    bool flag2 = ros::param::del("radius_param");
    if (flag2)
    {
        ROS_INFO("success!");
    }else
    {
        ROS_INFO("default");
    }

    return 0;

}