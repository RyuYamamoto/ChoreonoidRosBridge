#include "../include/JointTrajectoryRosBridge/JointTrajectoryRosBridge.h"

static const char* JointTrajectoryRosBridge_spec[] =
{
	"implementation_id", "JointTrajectoryRosBridge",
	"type_name",         "JointTrajectoryRosBridge",
	"description",       "Ros Choreonoid Bridge for Range Sensor Node",
	"version",           "1.0.0",
	"vendor",            "CIT",
	"category",          "tes",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",
	""
};

JointTrajectoryRosBridge::JointTrajectoryRosBridge(RTC::Manager* manager)
	: RTC::DataFlowComponentBase(manager)
{
}

JointTrajectoryRosBridge::~JointTrajectoryRosBridge()
{
}

void JointTrajectoryRosBridge::joint_trajectory_callback(const trajectory_msgs::JointTrajectory::ConstPtr& msg)
{
	size_t joint_size = msg->joint_names.size();

	joint_name_.resize(joint_size);
	for(size_t i=0;i<joint_size;i++){
		joint_name_[i] = msg->joint_names[i];
		cout << joint_name_ [i] << " " << msg->points[i] << endl;
	}
	cout << "\n" ;
}

RTC::ReturnCode_t JointTrajectoryRosBridge::onInitialize()
{
	joint_trajectory_sub = node.subscribe("/JVRC_1/torque_control/set_joint_trajectory", 1000, &JointTrajectoryRosBridge::joint_trajectory_callback, this);

	return RTC::RTC_OK;
}

RTC::ReturnCode_t JointTrajectoryRosBridge::onActivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}

RTC::ReturnCode_t JointTrajectoryRosBridge::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}

RTC::ReturnCode_t JointTrajectoryRosBridge::onExecute(RTC::UniqueId ec_id)
{
	ros::spinOnce();

	return RTC::RTC_OK;
}

extern "C"
{

	void JointTrajectoryRosBridgeInit(RTC::Manager* manager)
	{
		coil::Properties profile(JointTrajectoryRosBridge_spec);
		manager->registerFactory(profile,
				RTC::Create<JointTrajectoryRosBridge>,
				RTC::Delete<JointTrajectoryRosBridge>);
	}

};


