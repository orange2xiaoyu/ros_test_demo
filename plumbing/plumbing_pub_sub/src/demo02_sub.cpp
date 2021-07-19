#include "ros/ros.h"
#include "std_msgs/String.h"

/*
    订阅方实现：
        1.包含头文件；
        2.初始化ROS节点；
        3.创建节点句柄；
        4.创建订阅者对象；
        5.处理订阅到的数据。
        6.声明一个spin函数
*/

//回调函数（自己写的，调用时机是由外界控制的）
void domsg(const std_msgs::String::ConstPtr &msg){
    //通过msg获取并操作订阅到的数据
    ROS_INFO("翠花订阅的数据：%s",msg->data.c_str());
}


int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc, argv,"listener");    //节点名字具有唯一性
    ros::NodeHandle nh;
    //参数一，话题名称；参数二，最大消息数；参数三，回调函数
    ros::Subscriber sub = nh.subscribe("topic_name",10,domsg);

    //循环读取接收数据，调用回调函数
    ros::spin();
    return 0;
}