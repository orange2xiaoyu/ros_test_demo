#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"

//声明变量接收传递的参数
std::string turtle_name;

void doPose(const turtlesim::Pose::ConstPtr& pose)
{
    static tf2_ros::TransformBroadcaster pub;               
    geometry_msgs::TransformStamped ts;
    ts.header.frame_id = "world";
    ts.header.stamp = ros::Time::now();
    //关键点2：frame_id是动态传入的
    ts.child_frame_id = turtle_name;
    ts.transform.translation.x = pose->x;
    ts.transform.translation.y = pose->y;
    ts.transform.translation.z = 0;
    
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
    ros::init(argc, argv, "dynamic_pub");
    ros::NodeHandle nh;
    //关键点1：订阅的话题名称turtle1或者turtle2是动态传入的
    /*
            解析launch文件通过args传入的参数
    */
    if (argc != 2)
    {
        ROS_ERROR("请传入一个参数");
        return 1;
    }else
    {
        turtle_name = argv[1];
    }
    
    ROS_INFO("turtle_name: %s", turtle_name.c_str());
    ros::Subscriber sub = nh.subscribe(turtle_name + "/pose", 100, doPose);
    
    ros::spin();
    return 0;
}
