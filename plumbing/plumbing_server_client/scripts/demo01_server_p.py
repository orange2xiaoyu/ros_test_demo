#! /usr/bin/env python
#-*- coding=utf8 -*-
import rospy
from plumbing_server_client.srv import *
from rospy.client import spin

"""
    服务端：解析客户端请求，产生响应
        1.导包
        2.初始化ROS节点
        3.创建服务端对象
        4.处理请求并产生响应(回调函数)
        5.spin()

"""

#参数:封装了请求数据，返回值：响应数据
def doNum(request):
    #解析提交的请求数据
    num1 = request.num1
    num2 = request.num2

    #求和
    sum = num1 + num2
    #将结果封装进响应
    respose = AddIntsResponse()
    respose.sum = sum
    rospy.loginfo("服务器解析的数据：num1=%d, num2=%d, sum =%d", num1, num2, sum)
    return respose


if __name__ == "__main__":
    rospy.init_node("server_node_py")
    server = rospy.Service("addints_py", AddInts, doNum)     #参数1：话题名，参数2：数据载体类型，参数3：回调函数
    rospy.loginfo("服务器已经启动。")
    rospy.spin()
