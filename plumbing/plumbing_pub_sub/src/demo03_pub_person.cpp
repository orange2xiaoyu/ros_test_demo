#include "ros/ros.h"
#include "plumbing_pub_sub/Person.h"

/*
    发布者实现：发布人的消息
        1.包含头文件
        2.初始化ros节点
        3.创建节点句柄
        4.创建发布者对象；
        5.编写发布逻辑，发布数据


*/


int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ROS_INFO("消息的发布方：");
    ros::init(argc, argv, "node_name_person");
    ros::NodeHandle nh;
    ros::Publisher pub_person = nh.advertise<plumbing_pub_sub::Person>("topic_name_person",10);
    
    //1.被发布的数据
    plumbing_pub_sub::Person person;
    person.name = "张三";
    person.age = 1;
    person.height = 1.73;
    //2.设置发布频率
    ros::Rate rate(1);

    //3.循环发布数据
    while (ros::ok())
    {
        //修改数据
        person.age += 1;
        pub_person.publish(person);
        ROS_INFO("发布的消息：%s,%d,%2f",person.name.c_str(),person.age,person.height);
        rate.sleep();
        ros::spinOnce();
    }
    
    
    return 0;
}