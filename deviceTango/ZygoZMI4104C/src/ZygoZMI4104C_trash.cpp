/*----- PROTECTED REGION ID(ZygoZMI4104C.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        ZygoZMI4104C.cpp
//
// description : C++ source for the ZygoZMI4104C class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               ZygoZMI4104C are implemented in this file.
//
// project :     ZygoZMI4104C
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// $HeadURL:  $
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#include <ZygoZMI4104C.h>
#include <ZygoZMI4104CClass.h>
#include <yat4tango/InnerAppender.h>
#include "eca_soleil_zmi4104c.h"

/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C.cpp

/**
 *  ZygoZMI4104C class description:
 *    
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name                    |  Method name
//================================================================
//  State                           |  Inherited (no method)
//  Status                          |  Inherited (no method)
//  ResetMeasurementAxis            |  reset_measurement_axis
//  StartContinuousAcquisition      |  start_continuous_acquisition
//  StopContinnuousAcquisition      |  stop_continnuous_acquisition
//  EnableCyclicErrorCompensation   |  enable_cyclic_error_compensation
//  DisableCyclicErrorCompensation  |  disable_cyclic_error_compensation
//  ResetTheMeasurementSystem       |  reset_the_measurement_system
//  PlotGraphs                      |  plot_graphs
//================================================================

//================================================================
//  Attributes managed are:
//================================================================
//  samplingFrequency             |  Tango::DevDouble	Scalar
//  positionValueOnAxis1          |  Tango::DevDouble	Scalar
//  positionValueOnAxis2          |  Tango::DevDouble	Scalar
//  positionValueOnAxis3          |  Tango::DevDouble	Scalar
//  positionValueOnAxis4          |  Tango::DevDouble	Scalar
//  ledStateOnAxis1               |  Tango::DevUChar	Scalar
//  ledStateOnAxis2               |  Tango::DevDouble	Scalar
//  ledStateOnAxis3               |  Tango::DevDouble	Scalar
//  ledStateOnAxis4               |  Tango::DevDouble	Scalar
//  opticalPowerValueOnAxis3      |  Tango::DevDouble	Scalar
//  opticalPowerValueOnAxis4      |  Tango::DevDouble	Scalar
//  opticalPowerValueOnAxis1      |  Tango::DevDouble	Scalar
//  opticalPowerValueOnAxis2      |  Tango::DevDouble	Scalar
//  currentPrecision              |  Tango::DevUChar	Scalar
//  cyclicErrorCompensationState  |  Tango::DevUChar	Scalar
//  ledStateOnReferenceAxis       |  Tango::DevDouble	Scalar
//================================================================

namespace ZygoZMI4104C_ns
{
/*----- PROTECTED REGION ID(ZygoZMI4104C::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : ZygoZMI4104C::ZygoZMI4104C()
 *	Description : Constructors for a Tango device
 *                implementing the classZygoZMI4104C
 */
//--------------------------------------------------------
ZygoZMI4104C::ZygoZMI4104C(Tango::DeviceClass *cl, string &s)
 : Tango::Device_4Impl(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(ZygoZMI4104C::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::constructor_1
}
//--------------------------------------------------------
ZygoZMI4104C::ZygoZMI4104C(Tango::DeviceClass *cl, const char *s)
 : Tango::Device_4Impl(cl, s)
{
	/*----- PROTECTED REGION ID(ZygoZMI4104C::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::constructor_2
}
//--------------------------------------------------------
ZygoZMI4104C::ZygoZMI4104C(Tango::DeviceClass *cl, const char *s, const char *d)
 : Tango::Device_4Impl(cl, s, d)
{
	/*----- PROTECTED REGION ID(ZygoZMI4104C::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : ZygoZMI4104C::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void ZygoZMI4104C::delete_device()
{
	DEBUG_STREAM << "ZygoZMI4104C::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::delete_device) ENABLED START -----*/
	
	//	Delete device allocated objects
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::delete_device
	delete[] attr_samplingFrequency_read;
	delete[] attr_positionValueOnAxis1_read;
	delete[] attr_positionValueOnAxis2_read;
	delete[] attr_positionValueOnAxis3_read;
	delete[] attr_positionValueOnAxis4_read;
	delete[] attr_ledStateOnAxis1_read;
	delete[] attr_ledStateOnAxis2_read;
	delete[] attr_ledStateOnAxis3_read;
	delete[] attr_ledStateOnAxis4_read;
	delete[] attr_opticalPowerValueOnAxis3_read;
	delete[] attr_opticalPowerValueOnAxis4_read;
	delete[] attr_opticalPowerValueOnAxis1_read;
	delete[] attr_opticalPowerValueOnAxis2_read;
	delete[] attr_currentPrecision_read;
	delete[] attr_cyclicErrorCompensationState_read;
	delete[] attr_ledStateOnReferenceAxis_read;
}

//--------------------------------------------------------
/**
 *	Method      : ZygoZMI4104C::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void ZygoZMI4104C::init_device()
{
	DEBUG_STREAM << "ZygoZMI4104C::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::init_device_before) ENABLED START -----*/
	
	DEBUG_STREAM << "ZygoZMI4104C::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::init_device_before) ENABLED START -----*/
	
	//	Initialization before get_device_property() call
	
	//bias_mode = BIAS_CONSTANT_VOLT_MODE;
	//	Initialization before get_device_property() call
	m_is_device_initialized = false;
	//	Initialization before get_device_property() call
    set_state(Tango::INIT);
	//- initialize the inner appender (first thing to do)
	try
	{
		INFO_STREAM << "Create the InnerAppender in order to manage logs." << endl;
		yat4tango::InnerAppender::initialize(this);
		INFO_STREAM << "Create the DeviceInfo in order to manage info on versions." << endl;
		yat4tango::DeviceInfo::initialize( this, YAT_XSTR(PROJECT_NAME), YAT_XSTR(PROJECT_VERSION) );
	}
	catch( Tango::DevFailed& df )
	{
		ERROR_STREAM << df << std::endl;
		m_status_message << "Initialization failed - could not instanciate the InnerAppender!";
		return;
	}

	//	Get the device properties from database
	try
	{
		get_device_property();
	}
	catch (Tango::DevFailed& df)
	{
		ERROR_STREAM << df << std::endl;
		m_status_message << "Initialization Failed.\n" << endl;
		m_status_message << "Origin\t: " << df.errors[0].origin << endl;
		m_status_message << "Desc\t: " << df.errors[0].desc << endl;
		return;
	}
	catch (...)
	{
		ERROR_STREAM << "Initialization failed - unknown <get_device_property> error" << std::endl;
		m_status_message << "Initialization failed [unknown <get_device_property> error]";
		return;
	}
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::init_device_before
	
	
	attr_samplingFrequency_read = new Tango::DevDouble[1];
	attr_positionValueOnAxis1_read = new Tango::DevDouble[1];
	attr_positionValueOnAxis2_read = new Tango::DevDouble[1];
	attr_positionValueOnAxis3_read = new Tango::DevDouble[1];
	attr_positionValueOnAxis4_read = new Tango::DevDouble[1];
	attr_ledStateOnAxis1_read = new Tango::DevUChar[1];
	attr_ledStateOnAxis2_read = new Tango::DevDouble[1];
	attr_ledStateOnAxis3_read = new Tango::DevDouble[1];
	attr_ledStateOnAxis4_read = new Tango::DevDouble[1];
	attr_opticalPowerValueOnAxis3_read = new Tango::DevDouble[1];
	attr_opticalPowerValueOnAxis4_read = new Tango::DevDouble[1];
	attr_opticalPowerValueOnAxis1_read = new Tango::DevDouble[1];
	attr_opticalPowerValueOnAxis2_read = new Tango::DevDouble[1];
	attr_currentPrecision_read = new Tango::DevUChar[1];
	attr_cyclicErrorCompensationState_read = new Tango::DevUChar[1];
	attr_ledStateOnReferenceAxis_read = new Tango::DevDouble[1];

	/*----- PROTECTED REGION ID(ZygoZMI4104C::init_device) ENABLED START -----*/
	
	//	Initialize device
	
#if 1
	
		DEBUG_STREAM << "ZygoZMI4104C::vme_system_reset() Start" << endl;
		vme_system_reset();
		DEBUG_STREAM << "ZygoZMI4104C::vme_system_reset() Stop" << endl;
	
		ERROR_STREAM << "Initialization failed - in vme_system_reset() function" << std::endl;

	
	
#else
	try {
		if (initSISboards() != RET_SUCCESS) {
			
		FATAL("Failed to initialize SIS boards\n");	}
	}
	catch (...) {
		ERROR_STREAM << "Initialization failed - in initSISboards() function" << std::endl;
		return;

	}
#endif
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::init_device
}

//--------------------------------------------------------
/**
 *	Method      : ZygoZMI4104C::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void ZygoZMI4104C::get_device_property()
{
	/*----- PROTECTED REGION ID(ZygoZMI4104C::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::get_device_property_before


	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("baseAddress"));
	dev_prop.push_back(Tango::DbDatum("biasMode"));
	dev_prop.push_back(Tango::DbDatum("interferometerType"));
	dev_prop.push_back(Tango::DbDatum("presetPositionValueOnAxis1"));
	dev_prop.push_back(Tango::DbDatum("presetPositionValueOnAxis2"));
	dev_prop.push_back(Tango::DbDatum("presetPositionValueOnAxis3"));
	dev_prop.push_back(Tango::DbDatum("presetPositionValueOnAxis4"));
	dev_prop.push_back(Tango::DbDatum("offsetPostionValueOnAxis1"));
	dev_prop.push_back(Tango::DbDatum("offsetPostionValueOnAxis2"));
	dev_prop.push_back(Tango::DbDatum("offsetPostionValueOnAxis3"));
	dev_prop.push_back(Tango::DbDatum("offsetPostionValueOnAxis4"));
	dev_prop.push_back(Tango::DbDatum("continuousSamplingSize"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on ZygoZMI4104CClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		ZygoZMI4104CClass	*ds_class =
			(static_cast<ZygoZMI4104CClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize baseAddress from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  baseAddress;
		else {
			//	Try to initialize baseAddress from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  baseAddress;
		}
		//	And try to extract baseAddress value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  baseAddress;

		//	Try to initialize biasMode from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  biasMode;
		else {
			//	Try to initialize biasMode from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  biasMode;
		}
		//	And try to extract biasMode value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  biasMode;

		//	Try to initialize interferometerType from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  interferometerType;
		else {
			//	Try to initialize interferometerType from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  interferometerType;
		}
		//	And try to extract interferometerType value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  interferometerType;

		//	Try to initialize presetPositionValueOnAxis1 from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  presetPositionValueOnAxis1;
		else {
			//	Try to initialize presetPositionValueOnAxis1 from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  presetPositionValueOnAxis1;
		}
		//	And try to extract presetPositionValueOnAxis1 value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  presetPositionValueOnAxis1;

		//	Try to initialize presetPositionValueOnAxis2 from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  presetPositionValueOnAxis2;
		else {
			//	Try to initialize presetPositionValueOnAxis2 from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  presetPositionValueOnAxis2;
		}
		//	And try to extract presetPositionValueOnAxis2 value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  presetPositionValueOnAxis2;

		//	Try to initialize presetPositionValueOnAxis3 from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  presetPositionValueOnAxis3;
		else {
			//	Try to initialize presetPositionValueOnAxis3 from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  presetPositionValueOnAxis3;
		}
		//	And try to extract presetPositionValueOnAxis3 value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  presetPositionValueOnAxis3;

		//	Try to initialize presetPositionValueOnAxis4 from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  presetPositionValueOnAxis4;
		else {
			//	Try to initialize presetPositionValueOnAxis4 from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  presetPositionValueOnAxis4;
		}
		//	And try to extract presetPositionValueOnAxis4 value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  presetPositionValueOnAxis4;

		//	Try to initialize offsetPostionValueOnAxis1 from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  offsetPostionValueOnAxis1;
		else {
			//	Try to initialize offsetPostionValueOnAxis1 from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  offsetPostionValueOnAxis1;
		}
		//	And try to extract offsetPostionValueOnAxis1 value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  offsetPostionValueOnAxis1;

		//	Try to initialize offsetPostionValueOnAxis2 from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  offsetPostionValueOnAxis2;
		else {
			//	Try to initialize offsetPostionValueOnAxis2 from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  offsetPostionValueOnAxis2;
		}
		//	And try to extract offsetPostionValueOnAxis2 value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  offsetPostionValueOnAxis2;

		//	Try to initialize offsetPostionValueOnAxis3 from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  offsetPostionValueOnAxis3;
		else {
			//	Try to initialize offsetPostionValueOnAxis3 from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  offsetPostionValueOnAxis3;
		}
		//	And try to extract offsetPostionValueOnAxis3 value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  offsetPostionValueOnAxis3;

		//	Try to initialize offsetPostionValueOnAxis4 from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  offsetPostionValueOnAxis4;
		else {
			//	Try to initialize offsetPostionValueOnAxis4 from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  offsetPostionValueOnAxis4;
		}
		//	And try to extract offsetPostionValueOnAxis4 value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  offsetPostionValueOnAxis4;

		//	Try to initialize continuousSamplingSize from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  continuousSamplingSize;
		else {
			//	Try to initialize continuousSamplingSize from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  continuousSamplingSize;
		}
		//	And try to extract continuousSamplingSize value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  continuousSamplingSize;

	}

	/*----- PROTECTED REGION ID(ZygoZMI4104C::get_device_property_after) ENABLED START -----*/
	
	DEBUG_STREAM << "ZygoZMI4104C::get_device_property() END" << endl;
	//	Check device property data members init
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::get_device_property_after
}

//--------------------------------------------------------
/**
 *	Method      : ZygoZMI4104C::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void ZygoZMI4104C::always_executed_hook()
{
	INFO_STREAM << "ZygoZMI4104C::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : ZygoZMI4104C::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "ZygoZMI4104C::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_attr_hardware
}

//--------------------------------------------------------
/**
 *	Read attribute samplingFrequency related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_samplingFrequency(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_samplingFrequency(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_samplingFrequency) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_samplingFrequency_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_samplingFrequency
}
//--------------------------------------------------------
/**
 *	Write attribute samplingFrequency related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::write_samplingFrequency(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::write_samplingFrequency(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(ZygoZMI4104C::write_samplingFrequency) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::write_samplingFrequency
}
//--------------------------------------------------------
/**
 *	Read attribute positionValueOnAxis1 related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_positionValueOnAxis1(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_positionValueOnAxis1(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_positionValueOnAxis1) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_positionValueOnAxis1_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_positionValueOnAxis1
}
//--------------------------------------------------------
/**
 *	Read attribute positionValueOnAxis2 related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_positionValueOnAxis2(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_positionValueOnAxis2(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_positionValueOnAxis2) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_positionValueOnAxis2_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_positionValueOnAxis2
}
//--------------------------------------------------------
/**
 *	Read attribute positionValueOnAxis3 related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_positionValueOnAxis3(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_positionValueOnAxis3(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_positionValueOnAxis3) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_positionValueOnAxis3_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_positionValueOnAxis3
}
//--------------------------------------------------------
/**
 *	Read attribute positionValueOnAxis4 related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_positionValueOnAxis4(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_positionValueOnAxis4(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_positionValueOnAxis4) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_positionValueOnAxis4_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_positionValueOnAxis4
}
//--------------------------------------------------------
/**
 *	Read attribute ledStateOnAxis1 related method
 *	Description: 
 *
 *	Data type:	Tango::DevUChar
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_ledStateOnAxis1(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_ledStateOnAxis1(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_ledStateOnAxis1) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_ledStateOnAxis1_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_ledStateOnAxis1
}
//--------------------------------------------------------
/**
 *	Read attribute ledStateOnAxis2 related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_ledStateOnAxis2(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_ledStateOnAxis2(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_ledStateOnAxis2) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_ledStateOnAxis2_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_ledStateOnAxis2
}
//--------------------------------------------------------
/**
 *	Read attribute ledStateOnAxis3 related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_ledStateOnAxis3(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_ledStateOnAxis3(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_ledStateOnAxis3) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_ledStateOnAxis3_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_ledStateOnAxis3
}
//--------------------------------------------------------
/**
 *	Read attribute ledStateOnAxis4 related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_ledStateOnAxis4(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_ledStateOnAxis4(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_ledStateOnAxis4) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_ledStateOnAxis4_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_ledStateOnAxis4
}
//--------------------------------------------------------
/**
 *	Read attribute opticalPowerValueOnAxis3 related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_opticalPowerValueOnAxis3(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_opticalPowerValueOnAxis3(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_opticalPowerValueOnAxis3) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_opticalPowerValueOnAxis3_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_opticalPowerValueOnAxis3
}
//--------------------------------------------------------
/**
 *	Read attribute opticalPowerValueOnAxis4 related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_opticalPowerValueOnAxis4(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_opticalPowerValueOnAxis4(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_opticalPowerValueOnAxis4) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_opticalPowerValueOnAxis4_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_opticalPowerValueOnAxis4
}
//--------------------------------------------------------
/**
 *	Read attribute opticalPowerValueOnAxis1 related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_opticalPowerValueOnAxis1(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_opticalPowerValueOnAxis1(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_opticalPowerValueOnAxis1) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_opticalPowerValueOnAxis1_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_opticalPowerValueOnAxis1
}
//--------------------------------------------------------
/**
 *	Read attribute opticalPowerValueOnAxis2 related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_opticalPowerValueOnAxis2(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_opticalPowerValueOnAxis2(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_opticalPowerValueOnAxis2) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_opticalPowerValueOnAxis2_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_opticalPowerValueOnAxis2
}
//--------------------------------------------------------
/**
 *	Read attribute currentPrecision related method
 *	Description: 
 *
 *	Data type:	Tango::DevUChar
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_currentPrecision(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_currentPrecision(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_currentPrecision) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_currentPrecision_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_currentPrecision
}
//--------------------------------------------------------
/**
 *	Write attribute currentPrecision related method
 *	Description: 
 *
 *	Data type:	Tango::DevUChar
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::write_currentPrecision(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::write_currentPrecision(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevUChar	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(ZygoZMI4104C::write_currentPrecision) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::write_currentPrecision
}
//--------------------------------------------------------
/**
 *	Read attribute cyclicErrorCompensationState related method
 *	Description: 
 *
 *	Data type:	Tango::DevUChar
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_cyclicErrorCompensationState(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_cyclicErrorCompensationState(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_cyclicErrorCompensationState) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_cyclicErrorCompensationState_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_cyclicErrorCompensationState
}
//--------------------------------------------------------
/**
 *	Read attribute ledStateOnReferenceAxis related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void ZygoZMI4104C::read_ledStateOnReferenceAxis(Tango::Attribute &attr)
{
	DEBUG_STREAM << "ZygoZMI4104C::read_ledStateOnReferenceAxis(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::read_ledStateOnReferenceAxis) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_ledStateOnReferenceAxis_read);
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::read_ledStateOnReferenceAxis
}

//--------------------------------------------------------
/**
 *	Method      : ZygoZMI4104C::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void ZygoZMI4104C::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(ZygoZMI4104C::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command ResetMeasurementAxis related method
 *	Description: reset all the measurement axis on the board
 *
 */
//--------------------------------------------------------
void ZygoZMI4104C::reset_measurement_axis()
{
	DEBUG_STREAM << "ZygoZMI4104C::ResetMeasurementAxis()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::reset_measurement_axis) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::reset_measurement_axis
}
//--------------------------------------------------------
/**
 *	Command StartContinuousAcquisition related method
 *	Description: Start the continuous acquisition based on sampling frequency and continuousScanSize board properties. 
 *               In the Auto mode, the user should provide sampling frequency as well as the number of sample to acquire (samplingFrequency and samplingSize). The acquisition time will be determined by the board.
 *               In the manual mode, the user only provide the frequency. the size and the integration time will depend on the time at which the user press the  StopAcquisition button.
 *
 *	@param argin The input is the continuous acquisitio mode: false for Automatic and true for Manual
 */
//--------------------------------------------------------
void ZygoZMI4104C::start_continuous_acquisition(Tango::DevBoolean argin)
{
	DEBUG_STREAM << "ZygoZMI4104C::StartContinuousAcquisition()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::start_continuous_acquisition) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::start_continuous_acquisition
}
//--------------------------------------------------------
/**
 *	Command StopContinnuousAcquisition related method
 *	Description: stop the current continuous acquisition in manual mode
 *
 */
//--------------------------------------------------------
void ZygoZMI4104C::stop_continnuous_acquisition()
{
	DEBUG_STREAM << "ZygoZMI4104C::StopContinnuousAcquisition()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::stop_continnuous_acquisition) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::stop_continnuous_acquisition
}
//--------------------------------------------------------
/**
 *	Command EnableCyclicErrorCompensation related method
 *	Description: This command calculates and subtracts the cyclic errors 0 and N. The calculation is performed while motion occurs, and the
 *               coefficients are stored and used to correct for the cyclic errors when motion is at a velocity below
 *               a predefined threshold.
 *
 *	@param argin the axis number on which to enable compensation
 */
//--------------------------------------------------------
void ZygoZMI4104C::enable_cyclic_error_compensation(Tango::DevShort argin)
{
	DEBUG_STREAM << "ZygoZMI4104C::EnableCyclicErrorCompensation()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::enable_cyclic_error_compensation) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::enable_cyclic_error_compensation
}
//--------------------------------------------------------
/**
 *	Command DisableCyclicErrorCompensation related method
 *	Description: This command disable cyclic error compensation on the specified axis
 *
 *	@param argin the axis number on which to disable compensation
 */
//--------------------------------------------------------
void ZygoZMI4104C::disable_cyclic_error_compensation(Tango::DevShort argin)
{
	DEBUG_STREAM << "ZygoZMI4104C::DisableCyclicErrorCompensation()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::disable_cyclic_error_compensation) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::disable_cyclic_error_compensation
}
//--------------------------------------------------------
/**
 *	Command ResetTheMeasurementSystem related method
 *	Description: This command reset all the measurement system including VME/PCIe gateway
 *
 */
//--------------------------------------------------------
void ZygoZMI4104C::reset_the_measurement_system()
{
	DEBUG_STREAM << "ZygoZMI4104C::ResetTheMeasurementSystem()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::reset_the_measurement_system) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::reset_the_measurement_system
}
//--------------------------------------------------------
/**
 *	Command PlotGraphs related method
 *	Description: This command open a windows in which graph are ploted
 *
 */
//--------------------------------------------------------
void ZygoZMI4104C::plot_graphs()
{
	DEBUG_STREAM << "ZygoZMI4104C::PlotGraphs()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ZygoZMI4104C::plot_graphs) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::plot_graphs
}

/*----- PROTECTED REGION ID(ZygoZMI4104C::namespace_ending) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::namespace_ending
} //	namespace


/*----- PROTECTED REGION ID(ZygoZMI4104C::Additional Classes Definitions) ENABLED START -----*/

void ZygoZMI4104C::vme_system_reset(){
    info("VME SYSTEM RESET!!!\n");
    if(initSisBoards( )!= RET_SUCCESS) fatal("Failed to initialize SIS boards\n");
    //Sleep(10);
    if(initZmiBoards( ) != RET_SUCCESS) fatal("Failed to initialize ZMI board\n");
    //ui->pushButton_11->setEnabled(false);
    if(initAxis(  bias_mode) != RET_SUCCESS) fatal("Failed to initialize axis\n");
    enableDoublePassInterferometer();
	DEBUG_STREAM << "vme systeme reset complete  - " << device_name << endl;

}
/*----- PROTECTED REGION END -----*/	//	ZygoZMI4104C::Additional Classes Definitions