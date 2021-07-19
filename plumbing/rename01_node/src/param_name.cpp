#include "ros/ros.h"


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "hello");
    ros::NodeHandle nh;
    /*
        使用ros::param设置参数
    */
    //1.全局
    // ros::param::set("/radiusA", 100);                     //参数：/radiusA

    // //2.相对
    // ros::param::set("radiusB", 10);                       //参数：/xxx/radiusB

    // //3.私有
    // ros::param::set("~radiusC", 500);                     //参数：/xxx/hello/radiusC

    //1.全局
    nh.setParam("/radiusA", 1000);                          //参数：/radiusA
    //2.相对
    nh.setParam("radiusB", 10);                            //参数：/xxx/radiusB
    //3.私有
    ros::NodeHandle nh_private("~");
    nh_private.setParam("radiusC", 10);                   //参数：/xxx/hello/radiusC


    
    
    while (ros::ok)
    {


    }
    return 0;
}
