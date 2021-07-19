#! /usr/bin/env python
#-*- coding=utf8 -*-

import rospy
from plumbing_server_client.srv import AddInts, AddIntsRequest, AddIntsResponse
import sys


"""
    客户端：组织并提交请求，处理服务端响应
        1.导包
        2.初始化ROS节点
        3.创建客户端对象
        4.组织请求的数据，并发送请求
        5.处理响应
    优化实现：
        可以在执行节点时动态传入参数
    问题：
        客户端先于服务端启动，会抛出异常
    需要：
        客户端先于服务端启动，不抛出异常而是挂起，等待服务启动后，再次发送请求
    实现：
        ros中已经内置了相关函数，这些函数可以判断服务器的状态，如果服务器没启动，就让服务器挂起
        方案一：
        client.wait_for_service()
        方案二：
        rospy.wait_for_service("addints_py")          #参数是指定特定话题
"""


if __name__ == "__main__":
    #判断参数长度
    if len(sys.argv) !=3:
        rospy.loginfo("传入的参数个数不对")
        sys.exit(1)
    
    sys.argv
    rospy.init_node("client_name_py")
    client = rospy.ServiceProxy("addints_py", AddInts)      #参数1：话题名称，参数2：消息类型
    #解析传入的参数
    num1 = int(sys.argv[1])
    num2 = int(sys.argv[2])

    #等待服务启动
    #方式一：
    # client.wait_for_service()

    #方式二
    rospy.wait_for_service("addints_py")              #需要指定特定话题
    response = client.call(num1,num2)
    rospy.loginfo("响应的数据：%d",response.sum)
