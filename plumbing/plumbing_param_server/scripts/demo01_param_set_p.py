#! /usr/bin/env python
#-*-ucoding=utf8-*-
import rospy

"""
    演示参数的新增和修改
    需求：在参数服务器中设置机器人的属性，型号和半径
    实现：
        rospy.set_param()
"""


if __name__ == "__main__":
    rospy.init_node("set_param_py")
    #新增参数
    rospy.set_param("radius", 0.22223)
    rospy.set_param("type_py","xiaolan")

    #修改参数
    rospy.set_param("radius",100.9)