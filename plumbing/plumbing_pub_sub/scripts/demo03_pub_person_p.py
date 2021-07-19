#! /usr/bin/env python
#-*- coding:utf-8 -*-

import rospy
from plumbing_pub_sub.msg import Person

"""
    发布者实现：
        1.导包
        2.初始化ROS节点
        3.创建发布者对象
        4.编写发布逻辑并发布数据

"""


if __name__ == "__main__":
    rospy.init_node("talk_name_person")
    pub_person = rospy.Publisher("topic_name_py_person",Person,queue_size=10)

    p1 = Person()
    p1.age = 8
    p1.name = "aoteman"
    p1.height = 1.8

    rate = rospy.Rate(1)
    while not rospy.is_shutdown():

        pub_person.publish(p1)
        p1.age += 1
        rospy.loginfo("发布者的消息：%s,%d,%.2f",p1.name,p1.age,p1.height)
        rate.sleep()

