#! /usr/bin/env python
#-*-coding=utf8-*-
import rospy
import actionlib
from demo01_action.msg import *

"""
    流程：
        1.导包
        2.初始化ROS节点
        3.单独封装一个类
        4.类中创建action服务端对象
        5.处理请求（a.解析目标值；b.发送连续反馈；c.响应最终结果） ---- 回调函数
        6.spin()函数

"""
# 类中创建action服务端对象
# 处理请求（a.解析目标值；b.发送连续反馈；c.响应最终结果） ---- 回调函数
class MyAction:

    def __init__(self):
        #SimpleActionServer(name, ActionSpec, execute_cb=None, auto_start=True)
        self.server = actionlib.SimpleActionServer("addInts", AddIntsAction, self.cb, False)
        self.server.start()
        rospy.loginfo("服务端启动...")

    #回调函数
    def cb(self, goal):
        # a.解析目标值；
        goal_num = goal.num
        rospy.loginfo("目标值：%d",goal_num)
        
        # b.发送连续反馈；
        rate = rospy.Rate(10)
        sum = 0    #接收求和变量的结果
        rospy.loginfo("请求处理中")
        for i in range(1, goal_num+1):
            sum = sum + i
            rate.sleep()
            fb_obj = AddIntsFeedback()
            fb_obj.progress_bar = round(i/goal_num, 2)
            self.server.publish_feedback(fb_obj)

        # c.响应最终结果
        rospy.loginfo("响应最终结果：%d",sum)
        result = AddIntsResult()
        result.result = sum
        self.server.set_succeeded(result)

if __name__ == "__main__":
    rospy.init_node("action_server_p")
    # 单独封装一个类
    myaction = MyAction()
    rospy.spin()
