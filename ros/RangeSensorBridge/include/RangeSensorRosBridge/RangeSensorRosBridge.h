#ifndef RANGESENSORROSBRIDGE_H
#define RANGESENSORROSBRIDGE_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

using namespace RTC;

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <string>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

class RangeSensorRosBridge
: public RTC::DataFlowComponentBase
{
	public:
		RangeSensorRosBridge(RTC::Manager* manager);
		~RangeSensorRosBridge();

		virtual RTC::ReturnCode_t onInitialize();
		virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
		virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
		virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

	protected:
		RTC::RangeData m_range;
		RTC::InPort<RTC::RangeData> m_rangeIn;

		ros::Publisher range_pub;
		sensor_msgs::LaserScan laser_msg;

	private:
		int counter;
		std::string _frame_id;
		ros::NodeHandle node;
};


extern "C"
{
	DLL_EXPORT void RangeSensorRosBridgeInit(RTC::Manager* manager);
};

#endif // RANGESENSORROSBRIDGE_H
