#include "ros/ros.h"

/*
    需要实现参数的新增和修改
    需求：
        首先设置机器人的共享参数，类型，半径（0.15m）
        再修改半径（0.2m）
    实现：
        ros::NodeHandle nh;
            nh.setParam(key,value)
        ros::param::set(key,value)

*/



int main(int argc, char * argv[])
{
    ros::init(argc, argv, "set_param_c");
    ros::NodeHandle nh;
    //实现参数的增
    //方案1：nh
    nh.setParam("type","xiaohuang");
    nh.setParam("radius",0.15);

    //方案2：ros::param
    ros::param::set("type_param","xiaobai");
    ros::param::set("radius_param",0.15);

    //实现参数的改
    nh.setParam("type", "xiaohong");
    ros::param::set("type_param","xiaohei");
    
    return 0;
}