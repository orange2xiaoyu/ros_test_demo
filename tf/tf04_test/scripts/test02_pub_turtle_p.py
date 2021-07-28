#! /usr/bin/env python
#-*-coding=utf8-*-

import rospy
from turtlesim.msg import Pose
from geometry_msgs.msg import TransformStamped
import tf2_ros 
import sys
import tf_conversions

# 接收乌龟名称的变量
turtle_name = ""

def doPose(pose):
    pub = tf2_ros.TransformBroadcaster()
    tfs = TransformStamped()
    tfs.header.frame_id = "world"
    tfs.header.stamp = rospy.Time.now()
    tfs.child_frame_id = turtle_name
    tfs.transform.translation.x = pose.x
    tfs.transform.translation.y = pose.y
    tfs.transform.translation.z = 0

    qtn = tf_conversions.transformations.quaternion_from_euler(0, 0, pose.theta)
    tfs.transform.rotation.x = qtn[0]
    tfs.transform.rotation.y = qtn[1]
    tfs.transform.rotation.z = qtn[2]
    tfs.transform.rotation.w = qtn[3]
    pub.sendTransform(tfs)


if __name__ == "__main__":
    rospy.init_node("pub_turtle")
    # 解析传入的参数(现在传入的参数：文件全路径+传入的参数+节点名称+日志文件名称)
    if len(sys.argv) != 4:
        rospy.loginfo("传入的参数不对")
        sys.exit()
    else:
        turtle_name = sys.argv[1]

    rospy.Subscriber(turtle_name + "/pose", Pose, doPose, queue_size=100)
    rospy.spin()