#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"

/*
    发布方实现：订阅乌龟的位姿信息，将其转换成相对与窗体的坐标关系，并发布
    准备：
        乌龟位姿使用的话题： /turtle1/pose
        消息：turtlesim/Pose
    流程：
        1.包含头文件
        2.初始化
        3.创建订阅对象，订阅 /turtle1/pose
        4.回调函数处理订阅数据：将位姿信息转换成坐标相对关系并发布（关注）
        5.spin()
*/

// 4.回调函数处理订阅数据：将位姿信息转换成坐标相对关系并发布（关注）
void doPose(const turtlesim::Pose::ConstPtr& pose)
{
    //获取位姿信息，转换成坐标系相对关系
    //a.创建发布对象
    static tf2_ros::TransformBroadcaster pub;               //使用静态函数，每次调用回调函数都使用同一个pub
    //b.组织被发布的数据 
    geometry_msgs::TransformStamped ts;
    ts.header.frame_id = "world";
    ts.header.stamp = ros::Time::now();
    ts.child_frame_id = "turtle1";
    // 坐标系偏移量的设置
    ts.transform.translation.x = pose->x;
    ts.transform.translation.y = pose->x;
    ts.transform.translation.z = 0;
    // 坐标系四元数
    /*
        位姿信息中没有四元数，但有偏航角度，又已知乌龟是二维，没有翻滚和俯仰，所以可以得到乌龟的欧拉角度（0, 0，theta）
    */
    tf2::Quaternion qtn;
    qtn.setRPY(0,0,pose->theta);
    ts.transform.rotation.x = qtn.getX();
    ts.transform.rotation.y = qtn.getY();
    ts.transform.rotation.z = qtn.getZ();
    ts.transform.rotation.w = qtn.getW();
    //c.发布数据
    pub.sendTransform(ts);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    // 2.初始化
    ros::init(argc, argv, "dynamic_pub");
    ros::NodeHandle nh;
    // 3.创建订阅对象，订阅 /turtle1/pose
    ros::Subscriber sub = nh.subscribe("turtle1/pose", 100, doPose);
    
    // 5.spin()
    ros::spin();
    return 0;
}
