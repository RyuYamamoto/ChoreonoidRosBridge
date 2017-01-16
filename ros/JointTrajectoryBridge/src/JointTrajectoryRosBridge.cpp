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
	: RTC::DataFlowComponentBase(manager),
	m_rangeIn("range", m_range),
	counter(0)
{
}

JointTrajectoryRosBridge::~JointTrajectoryRosBridge()
{
}

RTC::ReturnCode_t JointTrajectoryRosBridge::onInitialize()
{
	addInPort("range", m_rangeIn);

	range_pub = node.advertise<sensor_msgs::LaserScan>("laser_scan", 10);

	ros::param::param<std::string>("~frame_id", _frame_id, "laser_scan");
	//std::cout << "[name]:"<<_frame_id.c_str() <<std::endl;

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
	if(m_rangeIn.isNew()){
		m_rangeIn.read();
		
		laser_msg.header.stamp = ros::Time::now();	
		laser_msg.header.frame_id = _frame_id;
		laser_msg.header.seq = counter; counter++;
		laser_msg.angle_min = m_range.config.minAngle;
		laser_msg.angle_max = m_range.config.maxAngle;
		laser_msg.angle_increment = m_range.config.angularRes;
		laser_msg.time_increment = 0;
		laser_msg.scan_time = 1. / m_range.config.frequency;
		laser_msg.range_min = m_range.config.minRange;
		laser_msg.range_max = m_range.config.maxRange;

		//.laser_msg.intensities.resize(m_range.ranges.length());
		laser_msg.ranges.resize(m_range.ranges.length());
		for(size_t i=0;i<laser_msg.ranges.size();i++){
			laser_msg.ranges[i] = m_range.ranges[i];
		}

		range_pub.publish(laser_msg);
	}else{
		ROS_WARN_STREAM("laser scan data not set.");
	}
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


