#! /usr/bin/env python
#-*-coding=utf8-*-

import rospy
from geometry_msgs.msg import Twist
import math
import tf2_ros 
from tf2_geometry_msgs import tf2_geometry_msgs



if __name__ =="__main__":
    rospy.init_node("control_turtle2")
    buffer = tf2_ros.Buffer()
    sub = tf2_ros.TransformListener(buffer)
    # 创建速度消息发布对象
    pub = rospy.Publisher("/turtle2/cmd_vel", Twist, queue_size=100)
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        try:
            ts = buffer.lookup_transform("turtle2", "turtle1", rospy.Time(0))
            # 组织消息，发布消息
            twist = Twist()
            twist.linear.x = 0.5*math.sqrt(math.pow(ts.transform.translation.x, 2) + math.pow(ts.transform.translation.y, 2))
            twist.angular.z = 4* math.atan2(ts.transform.translation.y, ts.transform.translation.x)
            pub.publish(twist)


        except Exception as e:
            rospy.loginfo("请求异常")
        
        rate.sleep()