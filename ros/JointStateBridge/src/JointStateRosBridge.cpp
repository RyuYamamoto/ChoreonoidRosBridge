// -*- C++ -*-
/*!
 * @file  JointStateRosBridge.cpp
 * @brief Ros Choreonoid Bridge for Joint State Node
 * @date $Date$
 *
 * $Id$
 */

#include "../include/RtmRosBridge/JointStateRosBridge.h"

#include <string>

#include <cnoid/ItemTreeView>
#include <cnoid/BodyItem>
#include <cnoid/JointPath>

using namespace cnoid;

static const std::string joint_name[] = {
	"R_HIP_P",
	"R_HIP_R",
	"R_HIP_Y",
	"R_KNEE",
	"R_ANKLE_R",
	"R_ANKLE_P",
	"L_HIP_P",
	"L_HIP_R",
	"L_HIP_Y",
	"L_KNEE",
	"L_ANKLE_R",
	"L_ANKLE_P",
	"WAIST_Y",
	"WAIST_P",
	"WAIST_R",
	"NECK_Y",
	"NECK_R",
	"NECK_P",
	"R_SHOULDER_P",
	"R_SHOULDER_R",
	"R_SHOULDER_Y",
	"R_ELBOW_P",
	"R_ELBOW_Y",
	"R_WRIST_R",
	"R_WRIST_Y",
	"R_UTHUMB",
	"R_LTHUMB",
	"R_UINDEX",
	"R_LINDEX",
	"R_ULITTLE",
	"R_LLITTLE",
	"L_SHOULDER_P",
	"L_SHOULDER_R",
	"L_SHOULDER_Y",
	"L_ELBOW_P",
	"L_ELBOW_Y",
	"L_WRIST_R",
	"L_WRIST_Y",
	"L_UTHUMB",
	"L_LTHUMB",
	"L_UINDEX",
	"L_LINDEX",
	"L_ULITTLE",
	"L_LLITTLE"
};

// Module specification
// <rtc-template block="module_spec">
static const char* jointstaterosbridge_spec[] =
{
	"implementation_id", "JointStateRosBridge",
	"type_name",         "JointStateRosBridge",
	"description",       "Ros Choreonoid Bridge for Joint State Node",
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
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
JointStateRosBridge::JointStateRosBridge(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager),
	m_angleIn("angle", m_angle)

	  // </rtc-template>
{
}

/*!
 * @brief destructor
 */
JointStateRosBridge::~JointStateRosBridge()
{
}



RTC::ReturnCode_t JointStateRosBridge::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers

	// Set OutPort buffer

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// </rtc-template>
	addInPort("angle", m_angleIn);

	jstate_pub = node.advertise<sensor_msgs::JointState>("joint_states", 10);

//	ItemList<BodyItem> bodyItems = ItemTreeView::mainInstance()->selectedItems<BodyItem>();
//	body = bodyItems[0]->body();

	//size_t n = body->numJoints();
	size_t n = 44;//sizeof(joint_name);
	js.name.resize(n);
	js.position.resize(n);
	for(size_t i=0;i<n;i++){
		js.name[i] = joint_name[i];//body->joint(i)->name();
		js.position[i] = 0.0;
	}

	return RTC::RTC_OK;
}

/*
   RTC::ReturnCode_t JointStateRosBridge::onFinalize()
   {
   return RTC::RTC_OK;
   }
   */

/*
   RTC::ReturnCode_t JointStateRosBridge::onStartup(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */

/*
   RTC::ReturnCode_t JointStateRosBridge::onShutdown(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */


RTC::ReturnCode_t JointStateRosBridge::onActivated(RTC::UniqueId ec_id)
{
	js.header.stamp = ros::Time::now();
	jstate_pub.publish(js);

	return RTC::RTC_OK;
}


RTC::ReturnCode_t JointStateRosBridge::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}


RTC::ReturnCode_t JointStateRosBridge::onExecute(RTC::UniqueId ec_id)
{
	ros::spinOnce();

	if(m_angleIn.isNew()){
		m_angleIn.read();

		for(size_t i=0;i<m_angle.data.length();i++){
			js.name[i] = joint_name[i];
			js.position[i] = m_angle.data[i];
		}
	}
	js.header.stamp = ros::Time::now();
	jstate_pub.publish(js);

	return RTC::RTC_OK;
}

/*
   RTC::ReturnCode_t JointStateRosBridge::onAborting(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */

/*
   RTC::ReturnCode_t JointStateRosBridge::onError(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */

/*
   RTC::ReturnCode_t JointStateRosBridge::onReset(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */

/*
   RTC::ReturnCode_t JointStateRosBridge::onStateUpdate(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */

/*
   RTC::ReturnCode_t JointStateRosBridge::onRateChanged(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */



extern "C"
{

	void JointStateRosBridgeInit(RTC::Manager* manager)
	{
		coil::Properties profile(jointstaterosbridge_spec);
		manager->registerFactory(profile,
				RTC::Create<JointStateRosBridge>,
				RTC::Delete<JointStateRosBridge>);
	}

};


