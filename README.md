## Sensors setup

### Multiple Hokuyo sensors case

From workspace */src* directory:

    git clone https://github.com/ros-drivers/driver_common.git
    git clone https://github.com/ros-drivers/hokuyo_node.git
    catkin build  # or catkin_make

If [catkin_tools](https://catkin-tools.readthedocs.io/en/latest/index.html) is used *youbot* package must be in the same workspace as the previous ones.
From root directory of the *youbot* package:

    sudo ./sensors_setup/lidar/udev_hokuyo_configuration.sh

This script creates a udev rule which will make links in */dev/sensors/* directory for each hokuyo by its *serial numbers*. Plug your hokuyo scanners one by one and check the corresponding *serial numbers* in */dev/sensors/* directory. Set this serial numbers in *sensor_setup/launch/hokuyo.launch*.

## Usage

Simple navigation on pre-builded map:

    roslaunch youbot_navigation navigation.launch

Mapping:

    roslaunch youbot_navigation gmapping.launch


## Demo

[![](https://img.youtube.com/vi/zKAOW9xSVBE/1.jpg)](https://www.youtube.com/watch?v=zKAOW9xSVBE "")
