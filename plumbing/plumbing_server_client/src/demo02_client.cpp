#include "ros/ros.h"
#include "plumbing_server_client/AddInts.h"

/*
    客户端：提交两个整数，并处理响应结果。
        1.包含头文件
        2.初始化ROS节点
        3.创建句柄
        4.创建客户端对象
        5.提交请求并处理响应

    实现参数的动态提交：
        1.格式： rosrun 包名 节点名称 12 34
        2.节点执行时，需要获取命令中的参数，并组织进request

    问题：
        如果想启动客户端，那么会请求异常
    需求：
        如果先启动客户端，不要直接抛出异常，而是挂起，等服务器启动后，再正常请求
    解决：
        在ros中内置了相关函数，这些函数可以让客户端启动后挂起，等待服务器启动
        client.waitForExistence()；
        ros::service::waitForService("addints");
*/

int main(int argc, char * argv[])
{
    
    setlocale(LC_ALL,"");
    //优化实现，获取命令中的参数
    if (argc !=3)
    {
        ROS_INFO("提交的参数个数不对");
        return 1;
    }
    
    ros::init(argc, argv, "client_name");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<plumbing_server_client::AddInts>("addints");
    //组织请求
    plumbing_server_client::AddInts ai;
    ai.request.num1 = atoi(argv[1]);
    ai.request.num2 = atoi(argv[2]);
    //处理响应
    //调用判断服务器状态的函数
    //函数一
    // client.waitForExistence();
    //函数二
    ros::service::waitForService("addints");      //需要传参，传入需要等待的话题名称
    
    bool flag = client.call(ai);
    if (flag)
    {
        ROS_INFO("响应成功");
        ROS_INFO("响应结果 = %d", ai.response.sum);
    }else
    {
        ROS_INFO("处理失败");
    }
    return 0;
}