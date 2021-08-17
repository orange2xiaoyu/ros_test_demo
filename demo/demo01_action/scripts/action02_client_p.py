#! /usr/bin/env python
#-*-coding=utf8-*-
import rospy
import actionlib
from demo01_action.msg import *

"""
    流程：
        1.导包
        2.初始化ROS节点
        3.创建action客户端对象（等待服务启动）
        4.发送请求
            a.激活处理     --- 回调函数 
            b.连续反馈处理 --- 回调函数 
            c.响应结果处理 --- 回调函数 
        5.spin()函数

"""

#最终结果回调
def done_cb(status, result):
    if status == actionlib.GoalStatus.SUCCEEDED:
        rospy.loginfo("最终响应结果：%d",result.result)
    else:
        rospy.loginfo("响应失败")

# 连接被激活时回调
def active_cb():
    rospy.loginfo("连接建立")

#处理连续反馈的回调
def feedback_cb(feedback):
    rospy.loginfo("当前进度：%.2f",feedback.progress_bar)

if __name__ == "__main__":
    rospy.init_node("action_client_p")
    client = actionlib.SimpleActionClient("addInts", AddIntsAction)
    client.wait_for_server()
    # send_goal(goal, done_cb=None, active_cb=None, feedback_cb=None)
    goal_obj = AddIntsGoal()
    goal_obj.num = 100
    client.send_goal(goal_obj, done_cb, active_cb, feedback_cb)
    rospy.spin()