#! /usr/bin/env python
#-*- coding:utf-8 -*-
import rospy
from std_msgs.msg import String    #发布消息的类型


"""
    订阅实现流程
        1.导包
        2.初始化ros节点
        3.创建订阅者对象
        4.编写回调函数处理数据
        5.spin()
"""

def do_msg(msg):
    rospy.loginfo("订阅的数据：%s",msg.data)



if __name__ =="__main__":
    rospy.init_node("listener_py")
    sub = rospy.Subscriber("topic_name", String, do_msg, queue_size=10)
    #采用回调函数必须使用spin函数
    rospy.spin()