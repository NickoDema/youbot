/*
 *  Created on: 12.05.2016
 *       Email: Nicko_Dema@protonmail.com
 *              ITMO University
 *              Robotics Engineering Department
 */

#ifndef NAV_STEP_
#define NAV_STEP_

#include <unordered_map>
#include <sys/stat.h>
#include <fstream>
#include <cstdlib>
#include <regex>

#include <boost/filesystem.hpp>

#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <std_srvs/Empty.h>
#include <ros/callback_queue.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PointStamped.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/server/simple_action_server.h>

#include <youbot_navigation/DestAction.h>
#include <youbot_navigation/SetOrientation.h>
#include <youbot_navigation/BasePoint.h>
#include <youbot_navigation/PointData.h>
#include <youbot_navigation/Manual.h>
#include <youbot_navigation/Twist.h>
#include <youbot_navigation/Dict.h>

class Navi
{
    public:
        Navi(std::string);
        ~Navi();
        void spin();

    protected:
        ros::NodeHandle nh_;

        unsigned char mode;
        enum modes
        {
            move_to_point  = 0x01,
            twisting       = 0x02,
            manual         = 0x04,
            ld_pnts        = 0x08,      //This flag means the dictionary had been loaded
            res_dict       = 0x10       //This flag is set when the reserve dict is used
            // ++++
        };

        std::unordered_map<std::string, std::pair<double, double>> points;
        std::string pnt_extr_regex;
        std::string dfile_path;
        std::fstream dict_fs;

        // ACTIONLIB used to communicate with CONTROL_NODE
        actionlib::SimpleActionServer<youbot_navigation::DestAction> dest_as;
        void execute_cb(const youbot_navigation::DestGoalConstPtr&);        // &goal??
        std::string dest_as_name;

        //ACTIONLIB client for move_base
        actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> move_base_ac;

        ros::ServiceServer stop_srv;
        ros::ServiceServer manual_srv;
        //ros::ServiceServer set_twist_srv;
        ros::ServiceServer set_orientation_srv;
        ros::ServiceServer dict_srv;
        ros::ServiceServer mode_srv;

        ros::ServiceClient point_catcher_cli;
        ros::ServiceClient costmap_clearer_cli;
        ros::ServiceServer point_catcher_srv;
        ros::ServiceServer point_catcher_base_srv;

        bool stop_cb (std_srvs::Empty::Request&, std_srvs::Empty::Response&);
        bool mode_cb (std_srvs::Empty::Request&, std_srvs::Empty::Response&);
        bool set_orientation_cb (youbot_navigation::SetOrientation::Request&, youbot_navigation::SetOrientation::Response&);
        //bool set_twist_cb (youbot_navigation::Twist::Request&, youbot_navigation::Twist::Response&);
        bool manual_cb (youbot_navigation::Manual::Request&, youbot_navigation::Manual::Response&);
        bool dict_cb (youbot_navigation::Dict::Request&, youbot_navigation::Dict::Response&);
        bool point_catcher_cb (std_srvs::Empty::Request&, std_srvs::Empty::Response&);
        bool point_catcher_base_cb (youbot_navigation::BasePoint::Request&, youbot_navigation::BasePoint::Response&);

        ros::Publisher twist_pub;
        geometry_msgs::Twist twist_msg;

        bool load_points();
        bool init_dict_load();

};

#endif  /*NAV_STEP_*/
