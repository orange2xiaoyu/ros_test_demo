#include "ros/ros.h"
#include "std_msgs/String.h"

/*
    需求：演示不同类型的话题名称设置
        设置话题名称与命名空间

*/


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "hello");
    // ros::NodeHandle nh;
    //设置不同类型的话题
    //1.全局------话题名称需要以 / 开头（也可以设置自己的命名空间），这种情况下和节点（命名空间以及名称）没有关系
    // ros::Publisher pub = nh.advertise<std_msgs::String>("/chat", 1000);                   //话题名称：/chat
    // ros::Publisher pub = nh.advertise<std_msgs::String>("/yyy/chat", 1000);               //话题名称：/yyy/chat

    //2.相对------话题名称以非 / 开头
    // ros::Publisher pub = nh.advertise<std_msgs::String>("chatter", 1000);                 //话题名称：/xxx/chatter
    // ros::Publisher pub = nh.advertise<std_msgs::String>("yyy/chatter", 1000);             //话题名称：/xxx/yyy/chatter

    //3.私有-------需要创建指定的NodeHandle
    ros::NodeHandle nh("~");
    // ros::Publisher pub = nh.advertise<std_msgs::String>("chatter", 1000);                    //话题名称：/xxx/hello/chatter
    ros::Publisher pub = nh.advertise<std_msgs::String>("yyy/chatter", 1000);                //话题名称：/xxx/hello/yyy/chatter
    
    //注意：如果私有的nodehandle创建的话题以 / 开头，生成的话题是全局的
    //全局话题优先级更高
    // ros::Publisher pub = nh.advertise<std_msgs::String>("/yyy/chatter", 1000);                //话题名称：/yyy/chatter(全局)



    while (ros::ok)
    {


    }
    return 0;
}
