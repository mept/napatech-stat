/*
 *
 * Copyright (C) 2021 Napatech A/S.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Napatech A/S nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NAPATECH A/S BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *

 */

/**
 * @file
 *
 * This header file is the STREAMTYPE_CONFIG interface
 *
 */
#ifndef __STREAM_CONFIG_H__
#define __STREAM_CONFIG_H__

#if !defined(__NT_H__)
  #error: My interface file is 'nt.h'. Please include that via #include "nt.h" directly.
#endif

/** @addtogroup ConfigStream
 * @{
 *
 * Configuration streams are used to read and write configuration data
 * and to set the filter configuration using NTPL commands. This
 * includes everything that can be changed on the fly. All static
 * configuration is done in the <tt>ntservice.ini</tt> file.
 *
 * All configuration parameters are organized in a parameter tree
 * structure @ref NtConfig_t where some parameters are read only (static
 * configuration parameters) and some parameters are read and write
 * (dynamic configuration parameters).
 *
 * To open a configuration stream call @ref NT_ConfigOpen. Once the
 * configuration stream is open use @ref NT_ConfigRead and @ref
 * NT_ConfigWrite with the @ref NtConfig_t structure to retrieve and
 * change the configuration. When done, call @ref NT_ConfigClose to close
 * the stream.
 *
 * @note Changing a configuration setting will trigger an @ref
 * NtEventSource_e::NT_EVENT_SOURCE_CONFIG
 * "NT_EVENT_SOURCE_CONFIG" when the changes have been made.
 *
 * The configuration parameter types currently supported are:
 * @li <tt>Port settings</tt> - retrieves or changes link speed, IFG, MDI mode
 * @li <tt>Time stamp type</tt> Retrieves or changes time stamp configuration
 * @li <tt>Time synchronization</tt> Retrieves or changes time synchronization configuration
 * @li <tt>Sensor min/max alarm settings</tt> Retrieves or changes sensor min/max alarm limits configuration
 * @li <tt>Coordinated time synchronized transmit</tt> Sets the coordinated time synchronized transmit configuration
 *
 * To set up or change filter configuration using NTPL commands use
 * the @ref NT_NTPL function call on an open configuration stream. For
 * a complete description of the NTPL syntax see @ref
 * NtplOverview "NTPL Overview".
 *
 * For an example of using the configuration stream see @ref
 * config/config_example.c "config/config_example.c".
 *
 *  @note The config stream is not thread-safe. If the same stream handle is to be used by multiple threads,
 *  it must be mutex protected in the application.
 *
 */
#include "/mnt/1/1/include/napatech/ntapi/commontypes.h"

/**
 * Configuration parameters
 */
enum NtConfigParm_e {
  NT_CONFIG_PARM_UNKNOWN=0,                       //!< Unknown command
  NT_CONFIG_PARM_PORT_COMPAT_0 = 1,               //!< Port settings configuration parameter - defined in stream_config_compat.h
  NT_CONFIG_PARM_ADAPTER_TIMESTAMP,               //!< Time stamp configuration parameter - use @ref NtConfigTimestampRead_s or @ref NtConfigTimestampWrite_s
  NT_CONFIG_PARM_ADAPTER_TIMESYNC,                //!< Time synchronization configuration parameter - use @ref NtConfigTimesyncWrite_s
  NT_CONFIG_PARM_SENSOR,                          //!< Sensor configuration parameter - use @ref NtConfigSensor_s
  NT_CONFIG_PARM_RESERVED_0,                      //!< Reserved
  NT_CONFIG_PARM_BYPASS_ADAPTER,                  //!< Bypass adapter settings configuration parameter - use @ref NtConfigBypass_s
  NT_CONFIG_PARM_BYPASS_PORT,                     //!< Bypass port settings configuration parameter - use @ref NtConfigBypass_s
  NT_CONFIG_PARM_BYPASS_ADAPTER_WATCHDOG_TIMEOUT, //!< Bypass watchdog timeout setup configuration parameter - use @ref NtConfigBypassWatchdogTimeout_s
  NT_CONFIG_PARM_BYPASS_PORT_WATCHDOG_TIMEOUT,    //!< Bypass adapter port watchdog timeout setup configuration parameter - use @ref NtConfigBypassWatchdogTimeout_s
  NT_CONFIG_PARM_BYPASS_ADAPTER_WATCHDOG_TIMER,   //!< Bypass adapter watchdog settings configuration parameter - use @ref NtConfigBypassWatchdogTimer_s
  NT_CONFIG_PARM_BYPASS_PORT_WATCHDOG_TIMER,      //!< Bypass port watchdog settings configuration parameter - use @ref NtConfigBypassWatchdogTimer_s
  NT_CONFIG_PARM_ADAPTER_GLOBAL_SYNC,             //!< Enable/disable GlobalSync on the adapter - use @ref NtConfigGlobalSyncWrite_s
  NT_CONFIG_PARM_NIM_ACCESS,                      //!< NIM data access for a Port - use @ref NtConfigNimAccess_s
  NT_CONFIG_PARM_VPD,                             //!< VPD data access. - use @ref NtVpd_s
  NT_CONFIG_PARM_PTP_PORT,                        //!< PTP port on PTP adapter - defined in stream_config_compat.h
  NT_CONFIG_PARM_ADAPTER_TIMESYNC_RESET,          //!< Timesync hard reset and PTP stat reset - use @ref NtConfigTimesyncReset_s
  NT_CONFIG_PARM_ADAPTER_PTP_IMPL_CFG,            //!< PTP configuration settings - use @ref NtConfigPtpImpl_s
  NT_CONFIG_PARM_PORT_COMPAT_1,                   //!< Port settings configuration parameter - defined in stream_config_compat.h
  NT_CONFIG_PARM_ADAPTER_MONITOR,                 //!< AdapterMonitor configuration parameter - use @ref NtConfigAdapterMonitor_s
  NT_CONFIG_PARM_PORT_TRANSMIT_ON_TIMESTAMP,      //!< Port TX time delta - use @ref NtConfigTransmitOnTimestamp_s
  NT_CONFIG_PARM_PORT_SETTINGS_V2,                //!< Port settings configuration parameter - use @ref NtConfigPort_v2_s
//

};

/**
 * Configuration stream handle
 */
typedef struct NtConfigStream_s* NtConfigStream_t;

/**
 * Array of manual port setting parameters
 */
struct NtPortSettingsManual_s {
  NtLinkSpeed_t speed;   //!< The interface speed - this is in effect if @ref NtLinkAutoNeg_e "autoNegotiation" = @ref NT_LINK_AUTONEG_MANUAL
  NtLinkDuplex_t duplex; //!< The duplex mode - this is in effect if @ref NtLinkAutoNeg_e "autoNegotiation" = @ref NT_LINK_AUTONEG_MANUAL
};

/**
 * Array of parameters to be advertised when autonegotiation is enabled
 */
struct NtPortSettingsAdvertise_s {
  uint32_t halfDuplexMask; //!< Available half duplex (uses @ref NtLinkSpeed_e as bitmask)
  uint32_t fullDuplexMask; //!< Available full duplex (uses @ref NtLinkSpeed_e as bitmask)
};


/**
 * The settings reflect how the interface should be configured.
 * The advertise section tells what should be advertised when
 * autonegotiation is enabled.
 * halfDuplexMask=0.
 * fullDuplexMask=NT_LINK_SPEED_100M.
 *
 * When a parameter does not apply on a particular adapter, then this parameter is ignored.
 *
 * @internal
 * Note: This is part of the NTDS structure. Changing this requires the service to be recompiled.
 */
struct NtPortSettings_v2_s {
  int enable;           //!< 0 = Disable interface, 1 = Enable interface. If disabled, the port will still be visible, but has status link down.
#ifndef DOXYGEN_IGNORE
  // Not supported
  int flow;             //!< 0 = No flow control, 1 = Flow control
#endif
  enum NtLinkMDI_e mdi; //!< MDI mode
  /**
   * NOTE: Cannot be set on optical NIM interfaces
   */
  enum NtLinkAutoNeg_e autoNegotiation;  //!< Link speed negotiation mode (manual or auto).
  /**
   * NOTE: Cannot be set on optical NIM interfaces
   */
  struct NtPortSettingsManual_s manual; //!< Array of manual port setting parameters
  /**
   * NOTE: Cannot be set on optical NIM interfaces
   */
  struct NtPortSettingsAdvertise_s advertise; //!< Array of parameters to be advertised when autonegotiation is enabled

  uint32_t minIFG; //!< Depending on the IfgMode parameter in ntservice.ini the minimum interframe-gap is either interpreted as 10 ns steps or bytes. If IfgMode is set to NS the value will be rounded up or down to the nearest HW-supported value, which depends on the link speed. The default minimum gap is 0 ns. If the IfgMode is set to BYTE the value is written directly to the HW.
  uint32_t maxIFG; //!< Depending on the IfgMode parameter in ntservice.ini the maximum interframe-gap is either interpreted as 10 ns steps or bytes. If the IfgMode is set to NS the value will be rounded up or down to the nearest HW-supported value, which depends on the link speed. The default maximum gap is the maximum HW-supported value. If the IfgMode is set to BYTE the value will be  written directly to the HW. Setting the maximum interframe gap to 0, corresponds to disabling the check for maximum IFG.

  enum NtTxPower_e TxPower; //!< TX power state on read and command on write. Controls laser power on/off on fiber SFP, XFP, SFP+ and QSFP+ modules. Note that not all modules support enable/disable of the laser. An error code is returned if not supported.
  int hostLoopback;  //!< Host loopback position.\n
  //!< Applying host loopback has the effect that data sent from the host is looped
  //!< back to the host on the same port regardless of, if a NIM (Network Interface
  //!< Module) has been plugged in, and if a physical loopback has been applied.
  //!< The link will therefore be reported as up despite that no NIM is present
  //!< or that no physical link is present.\n
  //!< In general simultaneous host and line loopback is not allowed.\n
  //!< The available loopback positions are adapter dependent and applying a loopback
  //!< position that is not supported will result in a returned error code by the API
  //!< function. In general only the following values @ref NtHostLoopback_e should be
  //!< used.\n
  //!< Applying loopback along with settings that require PHY setup changes or
  //!< applying these settings when already in loopback mode represents a conflict
  //!< and will not be carried out. A returned error code will indicate this. In order
  //!< to avoid conflicts, it is in general recommended to enable loopback separately.\n
  //!< When applying loopback special settings are used and for trispeed modules
  //!< this means that the link speed is changed to maximum. The original settings
  //!< are restored when loopback is removed.

  int lineLoopback;  //!< Line loopback position.\n
  //!< Applying line loopback has the effect that data sent from the line is looped
  //!< back to the line on the same port. This requires that a NIM (Network Interface
  //!< Module) has been plugged in.
  //!< The link will in general be reported as up and traffic can be received by
  //!< the host but any traffic transmitted by the host will be replaced by the
  //!< traffic looped back.
  //!< In general simultaneous host and line loopback is NOT allowed.\n
  //!< The available loopback positions are adapter dependent and applying a loopback
  //!< position that is not supported will result in a returned error code by the API
  //!< function. In general only the following values @ref NtLineLoopback_e should be
  //!< used.\n
  //!< Applying loopback along with settings that require PHY setup changes or
  //!< applying these settings when already in loopback mode represents a conflict
  //!< and will not be carried out. A returned error code will indicate this. In order
  //!< to avoid conflicts, it is in general recommended to enable loopback separately.\n
  //!< When applying loopback special settings are used and for trispeed modules
  //!< this means that the link speed is changed to maximum. The original settings
  //!< are restored when loopback is removed.
  enum NtPortId_e PortId; //!< Port identification state.
  //!< Turns the port identification feature on/off. An error code is returned if
  //!< not supported.
  //!< When enabled the port led will start to blink regardless if the link is up
  //!< or the port receives data or not.
  int wisModeEnable; //!< 0 = Wismode disabled on port, 1 = Enable Wismode enabled on port.
  int txReplicatePort; //!< Set TX port replication.\n
  //!< An error code is returned if not supported or the configuration
  //!< is invalid.
  //!< When set to a different port it will replicate all TX traffic from that port. It will
  //!< not be possible to transmit on this port when replication is activated. It is not
  //!< possible to change the replication configuration while TX traffic is active on this port
  //!< or the port it is replicating from.
  uint64_t txPortRateLimit; //!< Set Tx port rate limit in bits per second.\n
  //!< A value of zero disables the Tx port rate limit.
  //!< The resulting ports speed will be an aproximated value close to the specified value.
  //!< An error code is returned if not supported or the configuration is invalid.
  //!< Special case: a value in the range of 1 to 100 specifies a limit as percentage of the link speed.
};

/***********************************************************************
 * Config read and write port settings - NT_CONFIG_PARM_PORT_SETTINGS_V2 *
 ***********************************************************************/
struct NtConfigPort_v2_s {
  uint8_t portNo;                 //!< Port number to read from
  uint8_t Reserved1[3];
  struct NtPortSettings_v2_s data;   //!< Port settings
};

/************************************************************
 * Config read timestamp - NT_CONFIG_PARM_ADAPTER_TIMESTAMP *
 ************************************************************/
struct NtConfigTimestampRead_s {
  uint8_t adapter;                  //!< Adapter number to read from
  uint8_t Reserved1[3];
  struct NtConfigTimestampReadData_s {
    uint64_t ts;                    //!< The time stamp
    uint64_t nativeUnixTs;          //!< Value converted to native Unix (read only)
    enum NtTimestampType_e tsType;  //!< The time stamp type used by the adapter
  } data;
};

/*************************************************************
 * Config write timestamp - NT_CONFIG_PARM_ADAPTER_TIMESTAMP *
 *************************************************************/
struct NtConfigTimestampWrite_s {
  uint8_t adapter;                //!< Adapter number to write to
  uint8_t Reserved1[3];
  struct NtConfigTimestampWriteData_s {
    uint64_t ts;                  //!< The time stamp
    uint32_t bCurrent;            //!< Uses current OS time
  } data;
};

/****************************************************************
 * Config write timesync data - NT_CONFIG_PARM_ADAPTER_TIMESYNC *
 ****************************************************************/
struct NtConfigTimesyncWrite_s {
  uint8_t adapter;                //!< Adapter number to write to
  uint8_t Reserved1[3];
  struct NtConfigTimesyncWriteData_s {
    uint32_t action;              //!< 0 = Reference time, 1 = Enable PPS, 2 = Disable PPS
    uint64_t refTime;             //!< PPS reference time
  } data;
};



/**
 * TimeSync Reset commands
 */
enum NtTimeSyncReset_e {
  NT_TIMESYNC_RESET_INVALID = 0,
  NT_TIMESYNC_RESET_COMPAT_0,               //!< Command for backward compatibility - defined in stream_config_compat.h
  NT_TIMESYNC_RESET_PTP_PORT_STAT,          //!< Reset PTP port statistics
  NT_TIMESYNC_RESET_HARD_RESET_TIME_TO_REF, //!< Hard reset Time to reference clock (temporary time jumps allowed)
  NT_TIMESYNC_RESET_TS_STATISTICS           //!< Reset global time sync statistics
};

/*****************************************************************
 * Config timesync reset - NT_CONFIG_PARM_ADAPTER_TIMESYNC_RESET *
 *****************************************************************/
struct NtConfigTimesyncReset_s {
  uint8_t adapter;                   //!< Adapter number to write to
  uint8_t Reserved1[3];
  enum NtTimeSyncReset_e resetCmd;   //!< Timesync reset command
};




/*****************************************************************
 * PTP configuration - NT_CONFIG_PARM_ADAPTER_PTP_IMPL_CFG       *
 *****************************************************************/
typedef struct NtConfigPtpImplData_s {
  int32_t PTPDelayAsymmetry;       //!< The PTP delay asymmetry compensation to set
} NtConfigPtpImplData_t;

struct NtConfigPtpImpl_s {
  uint8_t adapter;                   //!< Adapter number to write to
  uint8_t Reserved1[3];
  NtConfigPtpImplData_t data;
};



/************************************************************
 * Config read or write sensor data - NT_CONFIG_PARM_SENSOR *
 ************************************************************/
struct NtConfigSensor_s {
  enum NtSensorSource_e source; //!< The source of the sensor - either a port or an adapter sensor
  uint32_t sourceIndex;         //!< The source index - either adapter number or port number on which the sensor resides
  uint32_t sensorIndex;         //!< The sensor index within the sensor group, see @ref MainDocMainFeaturesInfo_Sensors
  struct NtConfigSensorData_s {
    int32_t limitLow;           //!< The minimum sensor value before an alarm is triggered
    int32_t limitHigh;          //!< The maximum sensor value before an alarm is triggered
  } data;
};


/**************************************************************
 * Config globalsync - NT_CONFIG_PARM_ADAPTER_GLOBAL_SYNC     *
 **************************************************************/

struct NtConfigGlobalSyncWrite_s {
  uint8_t adapterNo;                         //!< Adapter number to write to
  uint8_t Reserved1[3];
  struct NtConfigWriteGlobalSyncData_s {
    uint32_t portEnableMask;                 //!< Enable coordinated time synchronized transmit on port bit mask
    uint64_t timeSynchronizedTxOffset;       //!< Time offset between time stamp in first frame and adapter time
    int timeSynchronizedTxOffsetUpdate;      //!< Set to 1 to update the offset value
  } data;
};

/********************************************************
 * Structure for bypass related port settings
 *
 * cmd parm: NT_CONFIG_PARM_BYPASS_PORT
 *           NT_CONFIG_PARM_BYPASS_ADAPTER
 ********************************************************/
typedef struct NtConfigBypassData_s {
  enum NtBypassTrigger_e bypassTriggerModes;                  //!< Bypass triggers that affect bypass states using @ref NtBypassTrigger_e
  enum NtBypassPortState_e currentBypassPortState;            //!< Current (live) bypass state using @ref NtBypassPortState_e
  enum NtBypassPortState_e onInitBypassPortState;             //!< onInit bypass state using @ref NtBypassPortState_e
  enum NtBypassPortState_e onPowerFailBypassPortState;        //!< onPowerFail bypass state using @ref NtBypassPortState_e
  enum NtBypassPortState_e onWatchdogFailBypassPortState;     //!< onWatchdogFail bypass state using @ref NtBypassPortState_e
  uint32_t onPowerFailBypassSwitchDelay;                       //!< onPowerFail bypass switch delay (msec)
} NtConfigBypassData_t;

struct NtConfigBypass_s {
  union NtConfigBypassParam_u {                               //!< Input key parameter union
    uint8_t adapterNo;                                         //!< Adapter number to read from or write to
    uint8_t portNo;                                            //!< port number to read from or write to
    uint32_t Reserved;
  } u;
  NtConfigBypassData_t data;
};


/********************************************************
 * Structure for bypass watchdog timer pings "heartbeat"
 *
 * cmd parm: NT_CONFIG_PARM_BYPASS_PORT_WATCHDOG_TIMER
 *           NT_CONFIG_PARM_BYPASS_ADAPTER_WATCHDOG_TIMER
 ********************************************************/
typedef struct NtConfigBypassWatchdogTimerData_s {
  //
  uint32_t bypassWatchdogTimeout;               //!< Bypass watchdog timeout in msec.
  uint32_t bypassWatchdogTimeRemaining;         //!< Bypass watchdog remaining time before timeout (msec)
} NtConfigBypassWatchdogTimerData_t;

struct NtConfigBypassWatchdogTimer_s {
  union NtConfigBypassWatchdogTimerParam_u {     //!< Input key parameter union
    uint8_t adapterNo;                           //!< Adapter number to read from or write to
    uint8_t portNo;                              //!< port number to read from or write to
    uint32_t Reserved;
  } u;
  NtConfigBypassWatchdogTimerData_t data;
};

/********************************************************
 * Structure for bypass port watchdog timer setup
 *
 * cmd parm: NT_CONFIG_PARM_BYPASS_PORT_WATCHDOG_TIMEOUT
 *           NT_CONFIG_PARM_BYPASS_ADAPTER_WATCHDOG_TIMEOUT
 ********************************************************/
typedef struct NtConfigBypassWatchdogTimeoutData_s {
  uint32_t bypassWatchdogTimeout;              //!< Bypass watchdog timeout (msec)
} NtConfigBypassWatchdogTimeoutData_t;

struct NtConfigBypassWatchdogTimeout_s {
  union NtConfigBypassWatchdogTimeoutParam_u {  //!< Input key parameter union
    uint8_t adapterNo;                          //!< Adapter number to read from or write to
    uint8_t portNo;                             //!< port number to read from or write to
    uint32_t Reserved;
  } u;
  NtConfigBypassWatchdogTimeoutData_t data;
};

struct NtConfigAdapterMonitor_s {
  uint8_t  adapter;                             //!< Adapter number to write to
  unsigned portCtrlInterval;                    //!< Number of milliseconds between each scan
  bool     run;                                 //!< Indicate if the thread should run
};

/********************************************************
 * Structure to configure transmit on timestamp
 *
 * cmd parm: NT_CONFIG_PARM_PORT_TRANSMIT_ON_TIMESTAMP
 *
 ********************************************************/
struct NtConfigTransmitOnTimestamp_s {
  uint8_t portNo;                               //!< Port to configure transmit on timestamp for
  uint8_t Reserved[3];
  struct NtConfigTransmitOnTimestampData_s {
    uint64_t timeDelta;                         //!< Delta in nanoseconds to add to packet time before comparing to adapter time
    bool enable;                                //!< Enable transmit on timestamp
    bool forceTxOnTs;                           //!< Force transmit on timestamp
    uint64_t timeDeltaAdjust;                   //!< Delta in nanoseconds added by adapter to timeDelta whenever a TXSETCLOCK packet is encountered
  } data;
};

//*****************************************************************************
//Structures and enums for accessing NIM via the config stream.
//*****************************************************************************
enum NtNimAccessType_e {
  NT_NIM_READ_DATA_LIN,       //!< Read NIM data using linear address convention
//

};

struct NtNimRawData_s {
  uint16_t linAddr;
  uint16_t length;
  uint8_t  data[512];
};

struct NtConfigNimAccess_s {
  enum NtNimAccessType_e accessType;
  uint8_t               portNo;
  uint8_t Reserved1[3];

  union NtNimAccess_u {
    struct NtNimRawData_s rawData;
  } u;
};

typedef struct NtConfigNimAccess_s* NtConfigNimAccess_p;


struct NtConfigPtpPortData_s {
  /** @brief PTP active flag.

On read: 0 = PTP is not active, 1 = PTP is active.
On Write: Value is ignored. */
  int enable;
  /** @brief PTP port enable flag.

On read: 0 = PTP port is not enabled, 1 = PTP port is enabled.
On Write: 0 = disable PTP port, 1 = enable PTP port.

      A PTP port must be enabled to achieve link up. */
  int port_enable;
  /** @brief Manual or auto negotiation of link speed and duplex mode.

      This field specifies whether link speed and duplex mode of the
PTP port is set manually or auto negotiated. */
  enum NtLinkAutoNeg_e autoNegotiation;
  /** @brief Bit mask of manual port setting parameters.

This field specifies the manually configured link speed and
duplex mode of the PTP port. These values are ignored when
auto negotiation is enabled.*/
  struct NtPortSettingsManual_s manual;
  /** @brief The speeds to advertise during auto negotiation.

This field is a bit mask of the speeds that are advertised
during auto negotiation. These values are ignored when auto
negotiation is disabled. */
  struct NtPortSettingsAdvertise_s advertise;
};
typedef struct NtConfigPtpPortData_s NtConfigPtpPortData_t;


/*************************************************************************
 * Config read or write PTP port configuration - NT_CONFIG_PARM_PTP_PORT *
 *************************************************************************/
struct NtConfigPtpPort_s {
  uint8_t adapterNo;    //!< Number of adapter with PTP functionality.
  /** @brief PTP port number.

      On Read: Always 0 (zero), currently.
      On Write: Must be 0 (zero), currently. */
  uint8_t portNo;
  uint8_t reserved[2];  //!< Reserved for future use.
  NtConfigPtpPortData_t data;
};
typedef struct NtConfigPtpPort_s NtConfigPtpPort_t;


/****************************************************************/
/* NTPL Info data structures                                    */
/****************************************************************/
/**
 * NTPL command execution mode
 */
enum NtNTPLCommands_e {
  NT_NTPL_PARSER_VALIDATE_NORMAL,     //!< NTPL expression is validated and executed
  NT_NTPL_PARSER_VALIDATE_PARSE_ONLY, //!< NTPL expression is only validated and has no effect
};

/**
 * NTPL parser error description and error code
 */
struct NtNtplParserErrorData_s {
#define NT_MAX_NTPL_BUFFER_SIZE (4*1024)            //!< NTPL maximum buffer size
  char     errBuffer[3][NT_MAX_NTPL_BUFFER_SIZE];   //!< NTPL error description
  int32_t  errCode;                                 //!< NTPL error code
};

#ifndef DOXYGEN_INTERNAL_ONLY
/**
 * NTPL filter counters. Deprecated. Use info stream instead.
 */
struct NtNtplFilterCounters_s {
  uint8_t sizeCount;        //!< Number of frame length filters used
  uint8_t protocolCount;    //!< Number of protocol filters used
  uint8_t errorCount;       //!< Number of error filters used
  uint8_t patternCount;     //!< Number of data filters used
  uint8_t dynOffsetCount;   //!< Number of dynamic offsets used
  uint8_t group4PlusCount;  //!< Number of group filters used combining 4 patterns with 4 different dynamic offsets
  uint8_t group8Count;      //!< Number of group filters used combining 8 patterns with 2 different dynamic offsets
};
#endif

/**
 * NTPL return values
 */
enum NtNTPLReturnType_e {
  NT_NTPL_PARSER_NORMAL,               //!< No error data returned
  NT_NTPL_PARSER_ERROR_DATA,           //!< Error data returned - errorData is filled
#ifndef DOXYGEN_INTERNAL_ONLY
  NT_NTPL_PARSER_FILTERINFO,           //!< Filter info data returned, see @ref NtNtplFilterCounters_s
//

#endif
};

/**
 * NTPL Info
 */
typedef struct NtNtplInfo_s {
  enum NtNTPLReturnType_e eType;          //!< Returned status
  uint32_t                ntplId;         //!< ID of the NTPL command
  int                     streamId;       //!< The selected stream ID
  uint64_t                ts;             //!< Time when the NTPL command is in effect
  enum NtTimestampType_e  timestampType;  //!< The time stamp type of NtNtplInfo_t::ts
  /**
   * NTPL return data.
   * Error or filter information.
   */
#ifndef DOXYGEN_INTERNAL_ONLY
  uint32_t reserved[50];
#endif
  union NtplReturnData_u {
    struct NtNtplParserErrorData_s   errorData;          //!< Error code and error text
#ifndef DOXYGEN_INTERNAL_ONLY
    struct NtNtplFilterCounters_s    aFilterInfo[NT_MAX_NUM_ADAPTERS];    // Deprecated. Use info stream instead
//

#endif
  } u;
} NtNtplInfo_t;


/* Include commands for backward compatibility */
#if !defined(_NT_NTAPI_NO_COMPAT)
#include "stream_config_compat.h"
#endif

/********************************************************
 * Structure for vpd access
 ********************************************************/
#define VPD_USER_SIZE 400

/**
 * VPD commands
 */
enum NtVpdCommands_e {
  NT_VPD_USER_DATA
};

typedef struct NtVpd_s {
  uint8_t adapterNo;                         //!< Adapter number to write to
  uint16_t length;                           //!< Length of data
  enum NtVpdCommands_e vpdCommand;           //!< VPD command using command @ref NtVpdCommands_e.
  union data_u {
  uint8_t userData[VPD_USER_SIZE];           //!< Userdata section of VPD
  } u;
} NtVpd_t;


//


//





//




/**************************************************************
 * Config change information
 **************************************************************/
typedef struct NtConfig_s {
  enum NtConfigParm_e parm;  //!<Configuration parameter
  union NtConfig_u {
    struct NtConfigPort_v2_s portSettings_v2;          //!< Port setting struct is used when reading or writing using command @ref NT_CONFIG_PARM_PORT_SETTINGS_V2
#if !defined(_NT_NTAPI_NO_COMPAT)
    struct NtConfigPort_v1_s portSettings_v1;          //!< Port setting struct is used when reading or writing using command @ref NT_CONFIG_PARM_PORT_SETTINGS_V1
#endif
    struct NtConfigTimestampRead_s timestampRead;      //!< Time stamp read struct is used when reading using command @ref NT_CONFIG_PARM_ADAPTER_TIMESTAMP
    struct NtConfigTimestampWrite_s timestampWrite;    //!< Time stamp write struct is used when writing using command @ref NT_CONFIG_PARM_ADAPTER_TIMESTAMP
    struct NtConfigTimesyncWrite_s  timesyncWrite;     //!< Time sync write struct is used when writing using command @ref NT_CONFIG_PARM_ADAPTER_TIMESYNC
    struct NtConfigSensor_s sensor;                    //!< Sensor read and write struct is used to read or write sensor alarm limits using command @ref NT_CONFIG_PARM_SENSOR
    struct NtConfigGlobalSyncWrite_s globalSyncWrite;  //!< Stream write struct is used when writing using command @ref NT_CONFIG_PARM_ADAPTER_GLOBAL_SYNC
    struct NtConfigBypass_s bypassConfig;              //!< Bypass adapter and port setting struct is used when reading or writing using commands @ref NT_CONFIG_PARM_BYPASS_PORT @ref NT_CONFIG_PARM_BYPASS_ADAPTER
    struct NtConfigBypassWatchdogTimer_s bypassWatchdogTimer;     //!< Bypass watchdog reading or writing using commands @ref NT_CONFIG_PARM_BYPASS_PORT_WATCHDOG_TIMER @ref NT_CONFIG_PARM_BYPASS_ADAPTER_WATCHDOG_TIMER
    struct NtConfigBypassWatchdogTimeout_s bypassWatchdogTimeout; //!< Bypass watchdog reading or writing using commands @ref NT_CONFIG_PARM_BYPASS_PORT_WATCHDOG_TIMEOUT @ref NT_CONFIG_PARM_BYPASS_ADAPTER_WATCHDOG_TIMEOUT
    struct NtConfigNimAccess_s nimAccess;              //!< NIM data access using command @ref NT_CONFIG_PARM_NIM_ACCESS
#if !defined(_NT_NTAPI_NO_COMPAT)
    struct NtConfigSensor_s  sensorWrite;              //!< Sensor write struct is used when writing using command @ref NT_CONFIG_PARM_SENSOR
#endif
    struct NtVpd_s vpdData;                            //!< VPD write structure @ref  NT_CONFIG_PARM_VPD
    struct NtConfigPtpPort_s ptpPort;                  //!< PTP port configuation @ref NT_CONFIG_PARM_PTP_PORT
    struct NtConfigTimesyncReset_s timesyncReset;      //!< Time sync hard reset time command
    struct NtConfigPtpImpl_s ptpImplCfg;               //!< PTP configuration settings
#if !defined(_NT_NTAPI_NO_COMPAT)
    struct NtConfigPort_s portSettings;                //!< Port setting struct defined in stream_config_compat.h
#endif
    struct NtConfigAdapterMonitor_s adapterMonitorSettings;  //!< Adapter Monitor settings
    struct NtConfigTransmitOnTimestamp_s transmitOnTimestamp; //!< Port transmit on timestamp settings
//

  } u;
} NtConfig_t;

/**
 * @brief Opens a configuration stream
 *
 * This function is called to retrieve a handle to a configuration stream
 *
 * @param[out] hStream          Reference to an NtConfigStream_t stream pointer
 * @param[in]  name             Stream friendly name - used in, for example, logging statements
 *
 * @retval  0    Success
 * @retval !=0   Error
 */
int NT_ConfigOpen(NtConfigStream_t *hStream, const char *name);

/**
 * @brief Closes a configuration stream
 *
 * This function is called to close a configuration stream
 *
 * @param[in] hStream          Reference to a NtConfigStream_t stream pointer
 *
 * @retval  0    Success
 * @retval !=0   Error
 */
int NT_ConfigClose(NtConfigStream_t hStream);

/**
 * @brief Reads data from a configuration stream
 *
 * Returns configuration data
 *
 * @param[in]      hStream   NtSystemStream_t handle
 * @param[in,out]  data      NtConfig_t structure containing configuration query and serving as output buffer for data
 *
 * @retval  0    Success
 * @retval !=0   Error
 */
int NT_ConfigRead(NtConfigStream_t hStream, NtConfig_t *data);

/**
 * @brief Writes data to a configuration stream
 *
 * Writes configuration data
 *
 * @param[in]      hStream   NtSystemStream_t handle
 * @param[in,out]  data      NtConfig_t structure containing the configuration to write
 *
 * @retval  0    Success
 * @retval !=0   Error
 */
int NT_ConfigWrite(NtConfigStream_t hStream, NtConfig_t *data);

/**
 * @brief Sends an NTPL line buffer to the parser
 *
 * This function is used to send an NTPL line buffer to the
 * parser. The config stream is defined by the hStream stream
 * handle.
 *
 * When using validate mode no data is written to the adapter. The
 * different modes define how far down the parsing is done.
 *
 * Note: Return data is stored in the stream handle and must be
 * read by the HAL functions.
 *
 * @param[in]  hStream    Config stream for the NTPL
 * @param[in]  ntplBuffer NTPL line buffer containing NTPL code
 * @param[in]  info       NTPL Info
 * @param[in]  validate   Set parsing mode to validate. See @ref NtNTPLCommands_e
 *
 * @retval  NT_SUCCESS                       NTPL command has been succesfully executed
 * @retval  NT_ERROR_WRONG_STREAM_TYPE       The stream is not a config stream
 * @retval  NT_ERROR_NT_SERVICE_NOT_STARTED  NT service is not started
 * @retval  NT_ERROR_INVALID_STREAM_POINTER  Stream handle is a NULL pointer
 * @retval  NT_ERROR_INVALID_STREAM_HANDLE   Stream handle is not a valid handle
 * @retval  NT_STATUS_TRYAGAIN               Host buffers are temporarily unavailable - please try again
 */
int NT_NTPL(NtConfigStream_t hStream, const char *ntplBuffer, NtNtplInfo_t *info, uint32_t validate);

/** @} */

#endif // __STREAM_CONFIG_H__
