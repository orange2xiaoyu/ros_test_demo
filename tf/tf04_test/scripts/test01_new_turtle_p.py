#! /usr/bin/env python
#-*-coding=utf8-*-

import rospy
from turtlesim.srv import Spawn, SpawnRequest, SpawnResponse

if __name__ == "__main__":
    rospy.init_node("new_turtle")
    client = rospy.ServiceProxy("/spawn", Spawn)
    request = SpawnRequest()
    request.x = 4.5
    request.y = 2.0
    request.theta = -3
    request.name = "turtle2"

    client.wait_for_service()
    try:
        response = client.call(request)
        rospy.loginfo("生成的乌龟的名称是：%s", response.name)
    except Exception as e:
        rospy.loginfo("请求处理异常")