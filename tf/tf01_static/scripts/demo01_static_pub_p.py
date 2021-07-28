#! /usr/bin/env python
#-*-ufcoding=utf8-*-

import rospy
import tf2_ros 
from geometry_msgs.msg import TransformStamped
import tf

"""
    发布方在:发布两个坐标系的相对关系（车辆底盘----base_link和雷达-----laser）
    流程：
        1.导包
        2.初始化节点
        3.创建发布对象
        4.组织发布对象
        5.发布数据
        6.spin()
"""

if __name__ == "__main__":
    # 初始化节点
    rospy.init_node("static_pub_p")
    # 创建发布对象
    pub = tf2_ros.StaticTransformBroadcaster
    ts = TransformStamped()
    # 设置header
    ts.header.stamp = rospy.Time.now()
    ts.header.frame_id = "base_link"
    #设置child_frame
    ts.child_frame_id = "laser"
    # 相对关系(偏移和四元数)
    ts.transform.translation.x = 2.0
    ts.transform.translation.y = 0.0
    ts.transform.translation.z = 0.5
    
    
    # 从欧拉角转成四元数

    qtn = tf.transformation.quaterion_from_euler(0, 0, 0)
    ts.transform.rotation.x = qtn[0]
    ts.transform.rotation.y = qtn[1]
    ts.transform.rotation.z = qtn[2]
    ts.transform.rotation.w = qtn[3]

    pub.sendTransform(ts)
    rospy.spin()