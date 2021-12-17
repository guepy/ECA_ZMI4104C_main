/*----- PROTECTED REGION ID(ZygoZMI.h) ENABLED START -----*/
//=============================================================================
//
// file :        ZygoZMI.h
//
// description : Include file for the ZygoZMI class
//
// project :     zygoZMI4104c
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
//
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#ifndef ZygoZMI_H
#define ZygoZMI_H

#include <tango.h>
#include "eca_soleil_zmi4104c.h"
#include "zVME_const.h"
#include "wingetopt.h" 
#include "sis3100_vme_calls.h"
#include "sis1100w.h"
#include "sis3302.h"
#include "sis3100.h"
#include "vmeInterruptConst.h"

/*----- PROTECTED REGION END -----*/	//	ZygoZMI.h

/**
 *  ZygoZMI class description:
 *    Zygo interferometer tango device`s which use a zmi4104c measurement board with a SIS VME/PCIe gateway.
 */

namespace ZygoZMI_ns
{
enum _axis1StateEnum {
	_NOSIGNAL,
	_ERROR,
	_OK,
} ;
typedef _axis1StateEnum axis1StateEnum;
BIAS_MODE bias_mode;
/*----- PROTECTED REGION ID(ZygoZMI::Additional Class Declarations) ENABLED START -----*/

//	Additional Class Declarations

/*----- PROTECTED REGION END -----*/	//	ZygoZMI::Additional Class Declarations

class ZygoZMI : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(ZygoZMI::Data Members) ENABLED START -----*/

//	Add your own data members

/*----- PROTECTED REGION END -----*/	//	ZygoZMI::Data Members
	double *postion;

//	Attribute data members
public:
	Tango::DevDouble	*attr_axis1Position_read;
	axis1StateEnum	*attr_axis1State_read;
	Tango::DevString	*attr_boardVersion_read;
	Tango::DevString	*attr_boardFirmwareVersion_read;
	Tango::DevString	*attr_gatewayBoardVersion_read;
	Tango::DevString	*attr_gatewayFirmwareVersion_read;
	Tango::DevUChar	*attr_flyscanAxisNbr_read;
	Tango::DevDouble	*attr_flyscanFreq_read;
	Tango::DevDouble	*attr_flyscanTime_read;

//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	ZygoZMI(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	ZygoZMI(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	ZygoZMI(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~ZygoZMI() {delete_device();};


//	Miscellaneous methods
public:
	/*
	 *	will be called at device destruction or at init command.
	 */
	void delete_device();
	/*
	 *	Initialize the device
	 */
	virtual void init_device();
	/*
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();


//	Attribute methods
public:
	//--------------------------------------------------------
	/*
	 *	Method      : ZygoZMI::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);
	//--------------------------------------------------------
	/*
	 *	Method      : ZygoZMI::write_attr_hardware()
	 *	Description : Hardware writing for attributes.
	 */
	//--------------------------------------------------------
	virtual void write_attr_hardware(vector<long> &attr_list);

/**
 *	Attribute axis1Position related methods
 *	Description: measured position on axis 1
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_axis1Position(Tango::Attribute &attr);
	virtual bool is_axis1Position_allowed(Tango::AttReqType type);
/**
 *	Attribute axis1State related methods
 *	Description: 
 *
 *	Data type:	Tango::DevEnum
 *	Attr type:	Scalar
 */
	virtual void read_axis1State(Tango::Attribute &attr);
	virtual bool is_axis1State_allowed(Tango::AttReqType type);
/**
 *	Attribute boardVersion related methods
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_boardVersion(Tango::Attribute &attr);
	virtual bool is_boardVersion_allowed(Tango::AttReqType type);
/**
 *	Attribute boardFirmwareVersion related methods
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_boardFirmwareVersion(Tango::Attribute &attr);
	virtual bool is_boardFirmwareVersion_allowed(Tango::AttReqType type);
/**
 *	Attribute gatewayBoardVersion related methods
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_gatewayBoardVersion(Tango::Attribute &attr);
	virtual bool is_gatewayBoardVersion_allowed(Tango::AttReqType type);
/**
 *	Attribute gatewayFirmwareVersion related methods
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_gatewayFirmwareVersion(Tango::Attribute &attr);
	virtual bool is_gatewayFirmwareVersion_allowed(Tango::AttReqType type);
/**
 *	Attribute flyscanAxisNbr related methods
 *	Description: 
 *
 *	Data type:	Tango::DevUChar
 *	Attr type:	Scalar
 */
	virtual void read_flyscanAxisNbr(Tango::Attribute &attr);
	virtual void write_flyscanAxisNbr(Tango::WAttribute &attr);
	virtual bool is_flyscanAxisNbr_allowed(Tango::AttReqType type);
/**
 *	Attribute flyscanFreq related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_flyscanFreq(Tango::Attribute &attr);
	virtual void write_flyscanFreq(Tango::WAttribute &attr);
	virtual bool is_flyscanFreq_allowed(Tango::AttReqType type);
/**
 *	Attribute flyscanTime related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_flyscanTime(Tango::Attribute &attr);
	virtual void write_flyscanTime(Tango::WAttribute &attr);
	virtual bool is_flyscanTime_allowed(Tango::AttReqType type);


	//--------------------------------------------------------
	/**
	 *	Method      : ZygoZMI::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:
	/**
	 *	Command Start related method
	 *	Description: Start the measurment system
	 *
	 */
	virtual void start();
	virtual bool is_Start_allowed(const CORBA::Any &any);
	/**
	 *	Command Stop related method
	 *	Description: Stop tha continuous acquisition
	 *
	 */
	virtual void stop();
	virtual bool is_Stop_allowed(const CORBA::Any &any);
	/**
	 *	Command updatePosition related method
	 *	Description: refresh the position on the given axis
	 *
	 *	@param argin 
	 */
	virtual void update_position(Tango::DevUShort argin);
	virtual bool is_updatePosition_allowed(const CORBA::Any &any);
	/**
	 *	Command startContinuousAcquisition related method
	 *	Description: Starts the continuous acquisition using values store in attributes flyscanAxisNbr, flyscanFreq and flyscanTime
	 *
	 */
	virtual void start_continuous_acquisition();
	virtual bool is_startContinuousAcquisition_allowed(const CORBA::Any &any);
	/**
	 *	Command reset related method
	 *	Description: reset all the VME system(including gateway boards)
	 *
	 */
	virtual void reset();
	virtual bool is_reset_allowed(const CORBA::Any &any);


	//--------------------------------------------------------
	/**
	 *	Method      : ZygoZMI::add_dynamic_commands()
	 *	Description : Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(ZygoZMI::Additional Method prototypes) ENABLED START -----*/

//	Additional Method prototypes

/*----- PROTECTED REGION END -----*/	//	ZygoZMI::Additional Method prototypes
};

/*----- PROTECTED REGION ID(ZygoZMI::Additional Classes Definitions) ENABLED START -----*/

//	Additional Classes Definitions

/*----- PROTECTED REGION END -----*/	//	ZygoZMI::Additional Classes Definitions

}	//	End of namespace

#endif   //	ZygoZMI_H