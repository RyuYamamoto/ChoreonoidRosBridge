#ifndef JVRC1PDControllerRTC_H
#define JVRC1PDControllerRTC_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <vector>

class JVRC1PDController : public RTC::DataFlowComponentBase
{
	public:
		JVRC1PDController(RTC::Manager* manager);
		~JVRC1PDController();
		void ReadGain(size_t numJoints,std::vector<double> &pgain,std::vector<double> &dgain);

		virtual RTC::ReturnCode_t onInitialize();
		virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
		virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
		virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

	protected:
		// DataInPort declaration
		RTC::TimedDoubleSeq m_angle;
		RTC::InPort<RTC::TimedDoubleSeq> m_angleIn;
		
		//RTC::TimedDoubleSeq m_qRef;
		//RTC::InPort<RTC::TimedDoubleSeq> m_qRefIn;

		// DataOutPort declaration
		RTC::TimedDoubleSeq m_torque;
		RTC::OutPort<RTC::TimedDoubleSeq> m_torqueOut;

	private:
		std::vector<double> pgain;
		std::vector<double> dgain;
		std::vector<double> angleRef;
		std::vector<double> q_old;
		std::vector<double> q_old_ref;
		double dq_old;
		double dt;
};

extern "C"
{
	DLL_EXPORT void RobotTorqueControllerRTCInit(RTC::Manager* manager);
};

#endif
