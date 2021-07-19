#! /usr/bin/env python
#-*- coding:utf-8 -*-
import os
import rospy
from std_msgs.msg import String    #发布消息的类型


"""
    使用python实现消息发布：
        1.导包
        2.初始化ros节点
        3.创建发布者对象；
        4.编写发布逻辑并发布数据
"""

if __name__ == "__main__":
    rospy.init_node("talker_py")        #传入节点名称
    path = os.path.abspath(".")
    rospy.loginfo("执行的时候，路径是：%s", path)
    
    #创建发布者对象
    pub = rospy.Publisher("topic_name_py", String, queue_size=10)     #参数一，话题名；参数二，发布消息类型；参数三，缓存大小
    #编写发布逻辑并发布
    msg = String()
    #休眠1s，在正式发布数据之前，为了完成数据注册
    rospy.sleep(1)
    #指定发布频率
    rate = rospy.Rate(1)
    #设置计数器
    count = 0
    while not rospy.is_shutdown:
        count += 1
        msg.data = "hello py" + str(count)
        pub.publish(msg)
        rospy.loginfo("发布的数据是：%s",msg.data)
        rate.sleep()