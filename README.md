## Sensors setup

### Multiple Hokuyo sensors case

From workspace */src* directory:

    git clone https://github.com/ros-drivers/driver_common.git
    git clone https://github.com/ros-drivers/hokuyo_node.git
    catkin build  # or catkin_make 

If [catkin_tools](https://catkin-tools.readthedocs.io/en/latest/index.html) is used *youbot* package must be in the same workspace as the previous ones. 
From root directory of the *youbot* package:

    sudo ./sensors_setup/lidar/udev_hokuyo_configuration.sh

