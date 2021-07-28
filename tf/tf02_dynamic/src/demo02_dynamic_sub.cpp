#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

/*
    订阅方实现：订阅发布的坐标系关系，传入一个坐标点，调用tf实现转换
    流程：
        1.包含头文件；
        2.编码、初始化、nodehandle(必须)；
        3.创建订阅对象；------->订阅坐标系相对关系
        4.组织一个坐标点数据；
        5.转换算法，需要调用tf内置实现
        6.输出。
*/


int main(int argc, char *argv[])
{
    // 2.编码、初始化、nodehandle(必须)；
    setlocale(LC_ALL,"");
    ros::init(argc, argv, "static_sub");
    ros::NodeHandle nh;
    // 3.创建订阅对象；------->订阅坐标系相对关系
    //3.1 创建一个buffer
    tf2_ros::Buffer buffer;
    //3.2 创建一个订阅对象（可以将订阅数据传入buffer）
    tf2_ros::TransformListener listener(buffer);
    // 4.组织一个坐标点数据；
    geometry_msgs::PointStamped ps;
    //参考的坐标系 turtle1
    ps.header.frame_id = "turtle1";           
    //时间戳
    ps.header.stamp = ros::Time(0.0);
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;
    //添加休眠
    // ros::Duration(2).sleep();
    // 5.转换算法，需要调用tf内置实现
    ros::Rate rate(10);
    while (ros::ok())
    {
        //将ps转换成相对于base_link的坐标点，
        geometry_msgs::PointStamped ps_out;
        /*
            调用了buffer的转换函数transform
            参数1：被转换的坐标点数据，
            参数2：目的坐标系，
            返回值：输出的坐标点
            
            注意1：调用时包含头文件 tf2_geometry_msgs/tf2_geometry_msgs.h
            注意2：运行时存在的问题：抛出异常 base_link 不存在
                    原因：订阅数据是一个耗时操作，可能在调用transform转换函数时，
                        坐标系的相对关系还没有订阅到，因此出现异常。
                    解决：
                        方案1：在调用转换函数前，执行休眠
                        方案2：进行异常处理
        */
        try
        {
            ps_out = buffer.transform(ps, "world");       
        
            // 6.输出
            ROS_INFO("转换后的坐标值：（%.2f, %.2f,%.2f）,参考的坐标系：%s",ps_out.point.x,
                                                                    ps_out.point.y,
                                                                    ps_out.point.z,
                                                                    ps_out.header.frame_id.c_str());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            ROS_INFO("异常消息：%s",e.what());
        }
        
        
        rate.sleep();
        ros::spinOnce();
    }
    
    return 0;
}
