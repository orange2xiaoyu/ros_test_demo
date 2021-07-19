#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

/*
    发布方实现：
        1.包含头文件；
        2.初始化ROS节点；
        3.创建节点句柄；
        4.创建发布者对象；
        5.编写发布逻辑并发布数据。
*/


int main(int argc, char *argv[])
{
    //解决中文的乱码问题
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"talker");   //节点名字具有唯一性
    ros::NodeHandle nh;
    //包括泛型，即被发布消息的类型，参数一表示发布的话题名字，参数二表示最大的保存的消息数
    ros::Publisher pub = nh.advertise<std_msgs::String>("topic_name",10);
    //要求以10hz的频率发布数据，并且需要在文本后加编号
    ros::Rate rate(10);
    //设置编号
    int count = 0;
    //创建被发布的消息
    std_msgs::String msgs;
    //休眠3s，用于发布者注册，使得订阅者可以从头接收发布者的信息
    ros::Duration(3).sleep();
    while (ros::ok())
    {
        count++;
        //实现字符串的拼接
        std::stringstream ss;
        ss << "hello ---->" << count;
        msgs.data = ss.str();
        pub.publish(msgs);
        //添加日志
        ROS_INFO("发布的数据是： %s", ss.str().c_str());
        rate.sleep();
        ros::spinOnce();    //官方建议，处理回调函数
    }
    return 0;
}