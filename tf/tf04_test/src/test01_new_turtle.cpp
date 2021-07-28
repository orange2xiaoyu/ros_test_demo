#include "ros/ros.h"
#include "turtlesim/Spawn.h"

/*
    需求：向服务端发送请求，生成一只新乌龟
        话题：/spawn
        消息：turtlesim/Spawn

    实现：
        1.包含头文件
        2.初始化ROS节点
        3.创建节点句柄
        4.创建客户端对象
        5.组织数据并发送
        6.处理响应
*/

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"service_call");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn spawn;
    //组织请求数据
    spawn.request.x = 4.5;
    spawn.request.y = 2.0;
    spawn.request.theta = -3;
    spawn.request.name = "turtle2";
    
    //发送请求
    //判断服务器状态
    client.waitForExistence();
    // ros::service::waitForService();
    bool flag = client.call(spawn);       //flag用来接收响应状态，响应结果成功会被设置进spawn对象
    //处理响应
    if (flag)
    {
        ROS_INFO("请求成功，新乌龟名字叫：%s",spawn.response.name.c_str());
    }else
    {
        ROS_INFO("请求失败");
    }
    
    return 0;
}