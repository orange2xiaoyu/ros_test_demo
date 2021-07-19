#include "ros/ros.h"
#include "plumbing_pub_sub/Person.h"


/*
    订阅方实现：发布人的消息
        1.包含头文件
        2.初始化ros节点
        3.创建节点句柄
        4.创建订阅者对象；
        5.编写回调函数，处理数据
        6.spin()函数


*/

void doPerson(const plumbing_pub_sub::Person::ConstPtr& person)
{
    ROS_INFO("订阅的人的信息：%s,%d,%2f",person->name.c_str(),person->age,person->height);

}



int main(int argc, char *argv[])
{   
    setlocale(LC_ALL,"");
    ROS_INFO("订阅方实现：");
    ros::init(argc, argv, "listen_node_person");
    ros::NodeHandle nh;
    ros::Subscriber sub_person = nh.subscribe("topic_name_person", 10, doPerson);
    
    ros::spin();
    return 0;
}