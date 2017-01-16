#ifndef JointTrajectoryROSBRIDGE_H
#define JointTrajectoryROSBRIDGE_H

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
#include <trajectory_msgs::JointTrajectory.h>

class JointTrajectoryRosBridge
: public RTC::DataFlowComponentBase
{
	public:
		JointTrajectoryRosBridge(RTC::Manager* manager);
		~JointTrajectoryRosBridge();

		void joint_trajectory_callback(const trajectory_msgs::JointTrajectory::ConstPtr &msg);

		virtual RTC::ReturnCode_t onInitialize();
		virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
		virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
		virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

	protected:
		ros::Subscriber joint_trajectory_sub;

	private:
		ros::NodeHandle node;
};


extern "C"
{
	DLL_EXPORT void JointTrajectoryRosBridgeInit(RTC::Manager* manager);
};

#endif // JointTrajectoryROSBRIDGE_H
