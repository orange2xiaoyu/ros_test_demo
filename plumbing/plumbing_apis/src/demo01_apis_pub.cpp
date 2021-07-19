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
    //初始化ROS节点
    /*
        作用：ros初始化函数
        参数：
            1.argc ---------封装实参个数（n+1）
            2.argv ---------封装参数的数组
            3.name ---------为节点命名（唯一性）
            4.options ------节点启动选项
            返回值：void
        使用：
            1.argc与argv的使用
                如果按照ros中的特定格式传入实参，那么ros可以加以使用，比如可以用来设置全局参数，给节点重命名等
            2.options的使用
                节点名称需要保证唯一性，会导致一个问题：同一个节点不能重复启动。
                结果：ros中有崇明的节点启动时，之前的节点会被关闭。
                需求：特地场景下，需要一个节点多次启动且能正常运行，怎么办？
                解决：设置启动项 ros::init_options::AnonymousName
                    当创建ROS节点时，会在用户自定义的节点名称后添加随机数，避免重名问题。

    */

    ros::init(argc,argv,"talker", ros::init_options::AnonymousName);   //节点名字具有唯一性
    ros::NodeHandle nh;
    //包括泛型，即被发布消息的类型，参数一表示发布的话题名字，参数二表示最大的保存的消息数
    ros::Publisher pub = nh.advertise<std_msgs::String>("topic_name",10, true);
    /*
        作用：创建发布者对象
        模板：被发布消息的类型
        参数：
            1.话题名称
            2.队列长度
            3.latch(可选) 如果设置为ture，会保存发布方的最后一条消息，并且新的订阅对象连接到发布方时，发布方会将这条消息发送给订阅方
        使用：
            latch设置为true的作用？
            以静态地图发布为例，方案一：可以使用固定频率发送地图数据，但是效率太低；
            方案二：可以将地图发布对象的latch设置为true，并且发布方只发布一次数据，每当订阅者连接时，就可以将地图数据发送给订阅者（只发布一次），提高了数据的发送效率。
    */


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
        if (count <= 10)
        {
            pub.publish(msgs);
            //添加日志
            ROS_INFO("发布的数据是： %s", ss.str().c_str());
        }
        
        
        rate.sleep();
        ros::spinOnce();    //官方建议，处理回调函数
    }
    return 0;
}