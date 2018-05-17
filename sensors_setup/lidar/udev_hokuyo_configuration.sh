# current workspace setup path
cd ../..
ws_setup=$PWD'/devel/setup.sh'

# bash script to get hokuyo serial
. /opt/ros/kinetic/setup.sh
cd /etc/ros/
echo '#!/bin/sh' > ros_run.sh
echo '. /opt/ros/'$ROS_DISTRO'/setup.sh' >> ros_run.sh
echo '. '$ws_setup >> ros_run.sh
echo 'rosrun $@' >> ros_run.sh
chmod 755 ros_run.sh

# udev rule
cd /etc/udev/rules.d/
echo 'SUBSYSTEMS=="usb", KERNEL=="ttyACM[0-9]*", ATTRS{manufacturer}=="Hokuyo Data Flex for USB", ATTRS{product}=="URG-Series USB Driver", MODE="0666", GROUP="dialout", PROGRAM=="/etc/ros/ros_run.sh hokuyo_node getID %N q", SYMLINK+="sensors/hokuyo_%c"' > 99-hokuyo.rules

