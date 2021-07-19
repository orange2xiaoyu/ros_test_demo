#include "ros/ros.h"

/*
    需求：演示时间相关的操作（获取当前时刻+设置指定时刻）
    实现：
        1.准备操作(头文件、ROS节点初始化、NodeHandle创建、、、)
        2.获取当前时刻
        3.设置指定时刻

*/
void callback(const ros::TimerEvent &event)
{
    ROS_INFO("---------------------");
}


int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc, argv, "hello_time");
    ros::NodeHandle nh;       //注意：必须。NodeHandle会初始化时间操作
    //当前时刻：now 被调用执行的那一刻（）
    //参考系：1970年01月01日 00:00:00
    ros::Time right_now = ros::Time::now();      //now函数会将当前时刻封装被返回
    ROS_INFO("当前时刻：%.2f",right_now.toSec());
    ROS_INFO("当前时刻：%d",right_now.sec);

    //设置指定时刻
    ros::Time t1(20, 312345678);           //t1(sec,nsec)
    ros::Time t2(100.35);
    ROS_INFO("t1 = %.2f",t1.toSec());
    ROS_INFO("t2 = %.2f",t2.toSec());

    /*
        定时器
        ros::timer createTimer(ros::Duration period,       //时间间隔---------1s
                 const ros::TimerCallback &callback,       //回调函数---------封装业务
                 bool oneshot = false,                     //是否是一次性
                 bool autostart = true)                    //自动启动
    */

    ros::Timer timer = nh.createTimer(ros::Duration(1), callback);
    
    ros::spin();
    return 0;
}

