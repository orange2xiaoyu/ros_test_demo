#! /usr/bin/env python
#-*- coding:utf-8 -*-
import rospy
from plumbing_pub_sub.msg import Person

"""
    订阅者实现：
        1.导包
        2.初始化ROS节点
        3.创建订阅者对象
        4.编写回调函数并处理数据
        5.spin()函数


"""

def doPerson(p):
    rospy.loginfo("订阅到的数据：%s,%d,%.2f",p.name,p.age,p.height)

if __name__ == "__main__":
    rospy.init_node("listen_node_py")
    sub = rospy.Subscriber("topic_name_py_person", Person, doPerson, queue_size=10)

    rospy.spin()
