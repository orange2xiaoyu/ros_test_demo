## ros_test_demo

在学习ros过程中的一些demo代码，之后可以回顾或者复用。

#### 关于发布与订阅的代码示例

1. 话题的发布与订阅，比如控制乌龟的移动；

2. 服务的发布与响应，比如使用服务添加新的小乌龟；

3. 参数的增删查改，比如全局、相对和私人参数的设置。

#### 关于坐标转换的代码示例

1. 静态坐标系的变换；

2. 动态坐标系的变换；

3. 多坐标系的变换；

4. 实践：乌龟跟随案例

#### 使用无线手柄控制Autolabor底盘

当前Autolabor自带手柄在不连接上位机情况下，可以控制底盘移动。连接上上位机之后，可以使用键盘控制底盘运动，为了更方便控制小车的运动，我们添加了logitech_move的节点，在连接上位机时可以通过罗技手柄控制小车运动。

#### urdf模块
包括使用urdf构建机器人，使用xacro构建机器人，集成rviz和gazebo，并进行导航。

#### demo模块
ros进阶模块，包括action通信、动态参数、pluginlib以及nodelet。
