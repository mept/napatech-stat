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
 * This is the header file of the STREAMTYPE_INFO interface.
 */
#ifndef __STREAM_INFO_H__
#define __STREAM_INFO_H__

#if !defined(__NT_H__)
  #error: My interface file is 'nt.h'. Please include that via #include "nt.h" directly.
#endif

/** @addtogroup InfoStream
 * @{
 *
 * Info streams are used to access system information. The info
 * stream is read only.
 *
 * To open an info stream call @ref NT_InfoOpen. Once the info stream
 * is open, the info read command needs to be set in the @ref NtInfo_t
 * structure and depending on the info command an adapter number, port
 * number or similar also needs to be set. Once the @ref NtInfo_t
 * structure query is filled out, a call to @ref NT_InfoRead makes the
 * system read out the requested data. When done, call @ref
 * NT_InfoClose to close the stream.
 *
 * The info stream read commands currently supported are:
 * @li <tt>System info</tt> - this includes the number of ports, adapters and sensors
 * @li <tt>Adapter info</tt> - this includes the number of sensors, ports, PCI ID and bus ID
 * @li <tt>Port info</tt> - this includes the port state, speed and duplex
 * @li <tt>Sensor info</tt> - this includes the sensor type, name and value
 * @li <tt>Host buffer info</tt> - this includes the NUMA node, size and feed
 * @li <tt>Time sync info</tt> - this includes the time sync connector and time sync data
 * @li <tt>Time sync external info</tt> - this includes the time sync information from a connected device
 * @li <tt>Stream ID info</tt> - this includes the Stream ID.
 * @li <tt>Product info</tt> - this includes the Product type, Product ID, Serial Number, PBA ID, AVR version, CPLD version and FPGA versions
 * @li <tt>PTP info</tt> - this includes the PTP related information
 *
 * For an example of using the info stream see @ref info/info_example.c "info/info_example.c"
 *
 *  @note The info stream is not thread-safe. If the same stream handle is to be used by multiple threads,
 *  it must be mutex protected in the application.
 *
 */

/**
 * Possible info stream read commands
 */
enum NtInfoCmd_e {
  NT_INFO_CMD_READ_UNKNOWN=0,     //!< Unknown stream read command
  NT_INFO_CMD_READ_SYSTEM,        //!< System info - the number of ports, adapters and sensors
  NT_INFO_CMD_READ_COMPAT_0,      //!< Command for backward compatibility - defined in stream_info_compat.h
  NT_INFO_CMD_READ_COMPAT_1,      //!< Command for backward compatibility - defined in stream_info_compat.h
  NT_INFO_CMD_READ_SENSOR,        //!< Sensor info - the sensor type, name and value
  NT_INFO_CMD_READ_COMPAT_3,      //!< Command for backward compatibility - defined in stream_info_compat.h
  NT_INFO_CMD_READ_STREAM,        //!< Info about active streams in the system
  NT_INFO_CMD_READ_COMPAT_2,      //!< Command for backward compatibility - defined in stream_info_compat.h
  NT_INFO_CMD_READ_COMPAT_5,      //!< Command for backward compatibility - defined in stream_info_compat.h
  NT_INFO_CMD_READ_COMPAT_4,      //!< Command for backward compatibility - defined in stream_info_compat.h
  NT_INFO_CMD_READ_COMPAT_6,      //!< Command for backward compatibility - defined in stream_info_compat.h
  NT_INFO_CMD_READ_HOSTBUFFER_V1, //!< Host buffer info - the NUMA node, size and feed
  NT_INFO_CMD_READ_COMPAT_9,      //!< Command for backward compatibility - defined in stream_info_compat.h
  NT_INFO_CMD_READ_STREAMID,      //!< Info about a stream ID
  NT_INFO_CMD_READ_COMPAT_10,     //!< Command for backward compatibility - defined in stream_info_compat.h
  NT_INFO_CMD_READ_TIMESYNC_STATUS_EXT, //!< Time sync external status info - the time sync external status data
  NT_INFO_CMD_READ_COMPAT_7,      //!< Adapter info version 2 - the number of sensors, ports, PCI ID and bus ID
  NT_INFO_CMD_READ_COMPAT_8,      //!< Port info - the port state, speed and duplex
  NT_INFO_CMD_READ_COMPAT_19,     //!< Product information version 0 request command
  NT_INFO_CMD_READ_COMPAT_11,     //!< Adapter info version 3 - the number of sensors, ports, PCI ID and bus ID
  NT_INFO_CMD_READ_COMPAT_12,     //!< Port info version 3 - the port state, speed and duplex
  NT_INFO_CMD_READ_COMPAT_15,     //!< PTP info v1 PTP port status, PTP clock datasets and PTP configuration
  NT_INFO_CMD_READ_COMPAT_23,     //!< Filter usage info. Read filter usage information
  NT_INFO_CMD_READ_COMPAT_21,     //!< Time sync info version 3 - the time sync connector and time sync data
  NT_INFO_CMD_READ_PATH_DELAY,    //!< Port path delay
  NT_INFO_CMD_READ_COMPAT_13,     //!< Adapter info version 4 - the number of sensors, ports, PCI ID and bus ID
  NT_INFO_CMD_READ_COMPAT_14,     //!< Port info version 4 - the port state, speed and duplex
  NT_INFO_CMD_READ_COMPAT_17,     //!< Adapter info version 5 - the number of sensors, ports, PCI ID and bus ID
  NT_INFO_CMD_READ_COMPAT_16,     //!< Port info version 5 - the port state, speed and duplex
  NT_INFO_CMD_READ_TIMESYNC_STAT, //!< Time sync statistics
  NT_INFO_CMD_READ_PTP_V2,        //!< PTP info v2 PTP port status, PTP clock data sets and PTP configuration
  NT_INFO_CMD_READ_COMPAT_18,     //!< Port info version 6 - the port state, speed and duplex

  NT_INFO_CMD_READ_ADAPTER_V6,    //!< Adapter info version 6 - the number of sensors, ports, PCI ID and bus ID
  NT_INFO_CMD_READ_COMPAT_20,     //!< Port info version 7 - the port state, speed and duplex
  NT_INFO_CMD_READ_COMPAT_22,     //!< Product information version 1 request command
  NT_INFO_CMD_READ_COMPAT_24,     //!< Port info version 8 - the port state, speed and duplex
  NT_INFO_CMD_READ_TIMESYNC_V4,   //!< Time sync info version 4 - the time sync connector and time sync data
  NT_INFO_CMD_READ_PRODUCT_INFO_V2, //!< Product information version 2 request command
  NT_INFO_CMD_READ_FILTERUSAGE_V1,   //!< Filter usage info. Read filter usage information
  NT_INFO_CMD_READ_PROPERTY,      //!< Property information request
  NT_INFO_CMD_READ_PORT_V9,       //!< Port info version 9 - the port state, speed and duplex
};

/**
 * This structure will return the system-wide information
 */
struct NtInfoSystem_s {
  uint8_t numNumaNodes;  //!< The number of online NUMA nodes in the system
  uint8_t Reserved1[3];
  uint8_t numAdapters;   //!< The number of adapters in the system
  uint8_t Reserved2[3];
  uint8_t numPorts;      //!< The number of ports in the system
  uint8_t Reserved3[3];
  /**
   * Version info
   */
  struct {
    int32_t major;  //!< The major release number
    int32_t minor;  //!< The minor release number
    int32_t patch;  //!< The major/minor patch release
    int32_t tag;    //!< The release tag number
  } version;
};

enum {
  NT_AVR_NOT_VALID = 0,             //!< No valid AVR data
  NT_AVR_VALID_2   = 1,             //!< Valid AVR data for mainboard and front board has been filled in the structure (Both index 0 and 1 has been filled with valid data)
  NT_AVR_VALID_1   = 2,             //!< Valid AVR data has been filled in the structure (Only index 0 has been filled with valid data)
};

struct NtversionAvr_s {
  uint8_t valid;                      //!< Does this structure contain valid data (not all adapters use this structure)
  struct {
    uint8_t version_major;            //!< The major version
    uint8_t version_minor;            //!< The minor version
    uint8_t version_build;            //!< The build number
  } avr[2];
};

union Ntpciid_u {
  /**
   * PCI ID can be read as:
   *   32-bit value,
   *   2 x 16-bit values defining
   *      device ID and
   *      vendor ID
   */
  struct Ntpciid_s {
    uint16_t device; //!< The device ID, for example, NT20E in-line 0x64
    uint16_t vendor; //!< The vendor ID, for example, Napatech 0x18F4
  }s;
  uint32_t value;    //!< The PCI ID, for example, 0x18540064
};

union Ntfpgaid_u {
  struct {
    uint32_t rev:8;      //!< The FPGA revision
    uint32_t ver:8;      //!< The FPGA version
    uint32_t product:16; //!< The FPGA product code
    uint32_t item:12;    //!< The FPGA item type (200 is FPGA, 201 is CPLD)
    uint32_t build:10;   //!< The build number - non-zero for R&D builds
    uint32_t reserved:10;
  }s;
  uint64_t value;      //!< The raw 64-bit FPGA ID
};

/**
 * Structure to hold information about WIS mode
 */
struct NtInfoWis_v1_s {
  int  supported;               //!< Is WIS mode supported by the adapter - 1 supported, 0: not supported
  enum NtWISMode_e mode;        //!< Is WIS mode enabled
  uint32_t mask;                //!< Wismode port enable mask ->  bit 0 = port0, bit 1 = port 1 etc.
};

/**
 * Structure to hold information about global sync
 */
struct NtInfoGlobalSync_s {
  int supported;                           //!< Is global sync supported.
  uint32_t portEnableMask;                 //!< Enables coordinated time synchronized transmit on port bit mask
  uint64_t timeSynchronizedTxOffset;       //!< Time offset between time stamp in first frame and adapter time
};

/**
 * Structure to read SDRAM information
 */
struct NtInfoSDRAMInfo_s {
  int present;                          //!< Is the SDRAM present
  enum NtSdramSize_e size;              //!< The physical SDRAM chip size
};

/**
 * Structure to read PCIe information
 */
struct NtInfoPCIeInfo_s {
  int pciGen;                             //!< PCI generation
  int numLanes;                           //!< Number of PCI lanes
  int numLanesSupported;                  //!< The number of lanes supported by the adapter
  int maxPayloadSupported;                //!< The maximum supported payload by the adapter
  int maxPayload;                         //!< The negotiated maximum payload
  uint32_t measuredRxThroughput;          //!< RX PCI throughput
  uint32_t measuredTxThroughput;          //!< TX PCI throughput
  uint32_t measuredCombinedRxThroughput;  //!< Combined RX throughput
  uint32_t measuredCombinedTxThroughput;  //!< Combined RX throughput
};

/**
  * Adapter bonding information
  */
typedef struct {
  uint32_t bonded;            //!< Has this adapter been bonded with another
  uint8_t remoteAdapter;     //!< The adapter this adapter is bonded with.
  enum NtBondingType_e type;  //!< Is the adapter master or slave
} NtInfoBondingInfo_t;



/**
 * This structure will return the adapter specific info version 6.
 * Must be a mirror of NtInfoAdapter_v5_s with version 6 variables added
 * to the bottom.
 */
struct NtInfoAdapter_v6_s {
  uint8_t numSensors;                      //!< The number of sensors on this adapter
  uint8_t Reserved1[3];
  uint8_t numLevel1Sensors;                //!< The number of level 1 sensors on this adapter
  uint8_t Reserved2[3];
  uint8_t portOffset;                      //!< The port numbers of this adapter start at this port offset
  uint8_t Reserved3[3];
  uint8_t numPorts;                        //!< The number of ports on this adapter
  uint8_t Reserved4[3];
  uint8_t numPhysicalAdapters;             //!< The number of physical adapters grouped in this logical adapter
  uint8_t Reserved5[3];
  uint32_t numHostBuffersRx;               //!< The number of RX host buffers on this adapter
  uint32_t numHostBuffersTx;               //!< The number of TX host buffers on this adapter
  uint32_t numTsConnectors;                //!< The number of time sync connectors on this adapter
  enum NtAdapterType_e adapterType;        //!< The adapter type
  enum NtProductType_e productType;        //!< The product line type
  enum NtProfileType_e profile;            //!< The profile the adapter is using
  uint32_t supportedProfilesBitmask;       //!< The profiles supported by the adapter - the value is represented as a bitmask of @ref NtProfileType_e values
  uint32_t adapterFeatures;                //!< The features supported by the adapter - the value is represented as a bitmask of @ref NtFeatureType_e values
  enum NtProductFamily_e productFamily;    //!< The product family
  char name[128];                          //!< The adapter name
  char serialNo[50];                       //!< The adapter serial number
  /**
   * AVR version for Gen2 adapters:
   *   avr[0] = Main board AVR,
   *   avr[1] = Front board AVR
   */
  struct NtversionAvr_s avr;

  /**
   * The bus ID of the device
   */
  union Ntbusid_v6_u {
    struct Ntbusid_v6_s {
      uint32_t function:3; //!< The PCI function number
      uint32_t device:5;   //!< The PCI device number
      uint32_t bus:8;      //!< The PCI bus number
      uint32_t domain:16;  //!< The PCI domain number
    }s;
    uint32_t value;        //!< The domain, bus, device and function as a 32-bit value
  } busid;
  /**
   * PCI  ID is read as:
   *   32-bit value,
   *   2 x 16-bit values defining
   *      device ID and
   *      vendor ID
   */
  union Ntpciid_u pciid;
  struct NtInfoPCIeInfo_s pciInfo;              //!< Information about the PCI bus.
  /**
   * The FPGA ID of the image currently running on the adapter.
   * The format is: item-product-version-revision-build.
   * For example, 200-9114-40-01-1023.
   */
  union Ntfpgaid_u fpgaid;
  struct NtInfoSDRAMInfo_s sdramInfo;           //!< The SDRAM information
  uint32_t extendedDescriptor; //!< The extended descriptor in use by RX - if 0 then no extended is used
  uint32_t supportedExtendedDescriptorsBitmask; //!< Bitmask of supported extended descriptors, for example, if bit 7 is set then extended descriptor 7 is supported, and if bit 8 it set then extended descriptor 8 is supported
  enum NtPacketDescriptorType_e descriptorType; //!< The descriptor type used
  enum NtTimestampType_e timestampType;         //!< The time stamp type used by the adapter
  enum NtTimestampMethod_e timestampMethod;     //!< The time stamp method (SOF/EOF) used by the adapter
  enum NtTxTimingMethod_e txTiming;             //!< The TX timing
  struct NtInfoWis_v1_s wisMode;                //!< Wis mode status
  enum NtTimestampInjectOffsetMode_e tsInjectModeOffset; //!< Time stamp injection offset mode
  struct NtInfoGlobalSync_s globalSync;         //!< Global sync status
  NtInfoBondingInfo_t bondingInfo;              //!< Adapter Bonding status
  enum NtFeatureLevel_e featureLevel;           //!< Adapter/FPGA feature level
  uint16_t customId;                            //!< Custom identification number
};

enum NtPortFeatureMask_e {
  NT_PORT_FEATURE_DMA_TRANSMIT=1LL<<0,              //!< The port is able to perform DMA transmit. Ports that do not have this bit set will only be able to transmit at a limited rate
  NT_PORT_FEATURE_HARDSLICE_AT_MAXFRAMESIZE=1LL<<1, //!< The port will hard slice packets when they exceed the maximum frame size
  NT_PORT_FEATURE_IPV4_TX_CHECKSUM_CALC=1LL<<2,     //!< The port can calculate the IPv4 checksum on transmit
  NT_PORT_FEATURE_UDP_TX_CHECKSUM_CALC=1LL<<3,      //!< The port can calculate the UDP checksum on transmit
  NT_PORT_FEATURE_TCP_TX_CHECKSUM_CALC=1LL<<4,      //!< The port can calculate the TCP checksum on transmit
  NT_PORT_FEATURE_INJECT_TX_TS=1LL<<5,              //!< The port can inject a time stamp when transmitting packets
  NT_PORT_FEATURE_TIMED_TX=1LL<<6,                  //!< The port can transmit timed using the time stamps in each packet
  NT_PORT_FEATURE_BYPASS=1LL<<7,                    //!< The port has bypass functionality
  NT_PORT_FEATURE_DISABLE=1LL<<8,                   //!< The port can be disabled
  NT_PORT_FEATURE_64BIT_TIMESTAMP=1LL<<9,           //!< The port has 64-bit time stamp support
  NT_PORT_FEATURE_RX_ONLY=1LL<<10,                  //!< The port can only be used to receive data. No transmit capabilities.
  NT_PORT_FEATURE_TX_REPLICATE=1LL<<11,             //!< The port can replicate the TX traffic of another port
  NT_PORT_FEATURE_FCS_TX_CHECKSUM_CALC=1LL<<12      //!< The port can calculate the FCS checksum on transmit
};

enum NtNimIdentifier_e {
  NT_NIM_UNKNOWN      = 0x00, //!< Nim type is unknown
  NT_NIM_GBIC         = 0x01, //!< Nim type = GBIC
  NT_NIM_FIXED        = 0x02, //!< Nim type = FIXED
  NT_NIM_SFP_SFP_PLUS = 0x03, //!< Nim type = SFP/SFP+
  NT_NIM_300_PIN_XBI  = 0x04, //!< Nim type = 300 pin XBI
  NT_NIM_XEN_PAK      = 0x05, //!< Nim type = XEN-PAK
  NT_NIM_XFP          = 0x06, //!< Nim type = XFP
  NT_NIM_XFF          = 0x07, //!< Nim type = XFF
  NT_NIM_XFP_E        = 0x08, //!< Nim type = XFP-E
  NT_NIM_XPAK         = 0x09, //!< Nim type = XPAK
  NT_NIM_X2           = 0x0A, //!< Nim type = X2
  NT_NIM_DWDM         = 0x0B, //!< Nim type = DWDM
  NT_NIM_QSFP         = 0x0C, //!< Nim type = QSFP
  NT_NIM_QSFP_PLUS    = 0x0D, //!< Nim type = QSFP+
  NT_NIM_QSFP28       = 0x11, //!< Nim type = QSFP28
  NT_NIM_CFP4         = 0x12, //!< Nim type = CFP4
};

enum NtPortStatusMask_e {
  NT_PORT_IFG_BYTE_MODE=1LL<<0,           //!< The port is configured to run in IFG BYTE mode
};

struct NtLinkCapabilities_s {
    uint32_t halfDuplexMask;              //!< The available half duplex (use @ref NtLinkSpeed_e as the bitmask)
    uint32_t fullDuplexMask;              //!< The available full duplex (use @ref NtLinkSpeed_e as the bitmask)
    uint32_t speed;                       //!< The available speed (use @ref NtLinkSpeed_e as the bitmask)
    uint32_t mdi;                         //!< The available MDI mode (use @ref NtLinkMDI_e as the bitmask)
    uint32_t AutoNeg;                     //!< The available link mode (use @ref NtLinkAutoNeg_e as the bitmask)
    uint32_t duplex;
    uint16_t minTxPktSize;                //!< The minimum transmit packet size, see also @ref NtRMON1Counters_s::undersizePkts
    uint16_t maxTxPktSize;                //!< The maximum transmit packet size
    uint32_t featureMask;                 //!< The feature mask of the port
};

struct NtNIMLinkLength_s {
    uint16_t sm;                  //!< NIM link length (in meters) supported SM (9um). A value of 0xFFFF indicates that the length is >= 65535 m
    uint16_t ebw;                 //!< NIM link length (in meters) supported EBW (50um)
    uint16_t mm50;                //!< NIM link length (in meters) supported MM (50um)
    uint16_t mm62;                //!< NIM link length (in meters) supported MM (62.5um)
    uint16_t copper;              //!< NIM link length (in meters) supported copper
};

/*
 * Bypass port information
 */
struct NtBypassPortInfo_s {                                 //!< Read-only information about bypass port states
  uint8_t bypassPortsetNo;                                   //!< Portset (portpair) membership - within an adapter
  uint8_t Reserved1[3];
  enum NtBypassTrigger_e bypassTriggerModes;                 //!< Bypass triggers that affect this port state using @ref NtBypassTrigger_e
  enum NtBypassPortState_e currentBypassPortState;           //!< Current (live) bypass port state using @ref NtBypassPortState_e
  enum NtBypassPortState_e onInitBypassPortState;            //!< onInit bypass port state using @ref NtBypassPortState_e
  enum NtBypassPortState_e onPowerFailBypassPortState;       //!< onPowerFail bypass port state using @ref NtBypassPortState_e
  enum NtBypassPortState_e onWatchdogFailBypassPortState;    //!< onWatchdogFail bypass port state using @ref NtBypassPortState_e
  uint32_t bypassPortWatchdogTimeout;                        //!< Watchdog timeout (msec)
  uint32_t bypassPortWatchdogTimeRemaining;                  //!< Watchdog remaining time before timeout (msec)
};



/**
 * This structure will return the port specific information version 7.
 * Must be a mirror of NtInfoPort_v8_s with version 9 variables added
 * to the bottom.
 */
struct NtInfoPort_v9_s {
  enum NtPortType_e type;     //!< The interface type
  enum NtLinkState_e state;   //!< The port up or down
  enum NtLinkSpeed_e speed;   //!< The interface speed
  enum NtLinkDuplex_e duplex; //!< The duplex mode
  int32_t flow;               //!< 0 = no flow control, 1 = flow control
  enum NtLinkMDI_e mdi;       //!< 1 = auto, 2 = MDI, 4 = MDIX
  uint8_t macAddress[6];      //!< The MAC address of the interface
  uint16_t maxFrameSize;      //!< The current maximum frame size
  /**
   * Capabilities reflect what the port is capable of, that is, what speed/duplex is possible. For example,
   * if only 100 M full duplex is available, the capabilities would
   * show:
   * halfDuplexMask=0.
   * fullDuplexMask=NT_LINK_SPEED_100M.
   * Other capabilities are min/max transmit sizes.
   */
  struct NtLinkCapabilities_s capabilities; //!< The link capabilities
  uint8_t adapterNo;             //!< The adapter that has the port
  uint8_t Reserved1[3];
  uint8_t numSensors;            //!< The number of sensors on this port
  uint8_t Reserved2[3];
  uint8_t numLevel1Sensors;      //!< Number of level 1 sensors on this port
  uint8_t Reserved3[3];
  uint8_t numLevel2Sensors;      //!< Number of level 2 sensors on this port
  uint8_t Reserved4[3];

  /**
   *  NIM model information
   */
  enum NtNimIdentifier_e nim_id; //!< NIM identifier
  uint8_t vendor_name[17];       //!< NIM Vendor name
  uint8_t product_no[17];        //!< NIM product number
  uint8_t serial_no[17];         //!< NIM serial number
  uint8_t date[9];               //!< NIM vendors manufacturing date
  uint8_t revision[5];           //!< NIM vendor revision
  uint8_t power_level_req;       //!< NIM required power level
  uint8_t power_level_curr;      //!< NIM current power level
  struct NtNIMLinkLength_s link_length;
  /**
   *  Adapter information
   */
  struct NtInfoAdapter_v6_s adapterInfo; // Adapter information
  /**
   * Bypass port information
   */
  struct NtBypassPortInfo_s bypass;   // Bypass port information
  uint32_t statusMask; //!< Adapter status mask holds information on how the port is configured at startup
  NtPortFec_t fecState;          //!< The state of Forward Error Correction if applicable
  uint64_t nextPktNs;            //!< Time till next package will be transmitted in ns.
  uint64_t maxPktDelayedNs;      //!< Max time pkts were late in being transmitted
};






/**
This structure will return the sensor specific information

The units used for the fields: value, valueLowest, valueHighest, limitLow and
limitHigh depend on the type field. See @ref NtSensorType_e.

For the limitLow and limitHigh fields the following applies:\n
If the sensor is located in a NIM (Network Interface Module), the limits are read
from the NIM module via the DMI (Diagnostic Monitoring Interface) from the alarm
and warning threshholds section, and the units are changed to internal representation.
Only the alarm threshholds are used and are read only once during initialization.
The limits cannot be changed.

The value field is updated internally on a regular basis and is also based on a
value read from the NIM which is also changed to internal representation.

Not all NIM types support DMI data, and its presence must be determined by reading an
option flag. In general, a NIM can read out: temperature, supply voltage,
TX bias, TX optical power and RX optical power but not all NIM types support all
5 values.

If external calibration is used (most NIM use internal calibration), both the
current value and the threshold values are subjected to the specified calibration
along with the change to internal calibration.
*/
typedef struct NtInfoSensor_s {
  enum NtSensorSource_e source;     //!< The source of the sensor (port or adapter on which the sensor resides)
  uint32_t sourceIndex;             //!< The source index - the adapter number for adapter sensors and port number for port sensors
  uint32_t sensorIndex;             //!< The sensor index within the source index (sensor number on the adapter or sensor number on the port)
  enum NtSensorType_e type;         //!< The sensor type
  enum NtSensorSubType_e subType;   //!< The sensor subtype (if applicable)
  enum NtSensorState_e state;       //!< The current state (normal or alarm)
  int32_t value;                    //!< The current value
  int32_t valueLowest;              //!< The lowest value registered
  int32_t valueHighest;             //!< The highest value registered
  int32_t limitLow;                 //!< The minimum sensor value before an alarm is triggered
  int32_t limitHigh;                //!< The maximum sensor value before an alarm is triggered
  char name[50];                    //!< The sensor name
  enum NtAdapterType_e adapterType; //!< The adapter type where the sensor resides
} NtInfoSensor_t, *NtInfoSensor_p;


/**
 * StreamID specific information
 */
struct NtInfoStreamId_s {
  int useCount;                     //!< Set to the number of streams using this stream ID
  int numHostBuffers;               //!< The amount of hostbuffers currently in use by this stream ID
  enum NtStreamIdState_e state;     //!< The current state of the stream ID
  uint64_t minHostBufferSize;       //!< The minimum hostbuffer size this stream ID requires
  uint8_t numaNode;                 //!< The NUMA node on which this stream ID resides
};

/**
 * Host buffer specific information
 */
struct NtInfoHostBuffer_v1_s {
  uint8_t numaNode;  //!< The NUMA node on which the host buffer resides
  uint8_t Reserved1[3];
  uint64_t size;     //!< The size of the host buffer in bytes
  uint32_t feed;     //!< The feed index per adapter and type
};


/**
 * Structure to hold information about currently active streams
 */
struct NtInfoStreams_s {
  int streamIDList[256];  //!< Holds all the stream IDs currently created in the system
  uint32_t count;         //!< The number of stream IDs from the stream ID list
//

};


/**
 * Structure to hold the sampled timestamps and status
 */
struct NtInfoTimeSyncSample_s {
  enum NtTimeSyncSamplingSrcStatus_e sampledStatus;  //!< Status of sampled timestamp (valid/invalid)
  uint64_t sampledTime;                              //!< The sampled adapter time in ns since 1/1 1970 (unix epoch). if NATIVE timestamp format is configured, the epoch is user defined)
  enum NtTimeSyncSamplingSrcStatus_e externalStatus; //!< Status of external reference timestamp (available/unavailable)
  uint64_t externalTime;                             //!< The sampled external time in ns since 1/1 1970 (unix epoch). if NATIVE timestamp format is configured, the epoch is user defined)
};


/**
 * Time syncronization specific info
 */
#define NT_TIME_SYNC_CLOCK_RATE_ADJ_UNKNOWN  1000000000    //!< Used for timeSyncClockRateAdjustment and timeSyncOSClockRateAdjustment parameters to indicate that no clock rate adjustment is retrievable

struct NtInfoTimeSync_v4_s {
  uint32_t timeSyncSupported;                              //!< Is time sync supported by this adapter
  uint32_t ptpSupported;                                   //!< Is PTP time sync available on this adapter

  NtTimeSyncConnectorSetting_t timeSyncConnectorExt1; //!< Timesync connector Ext1 setting
  NtTimeSyncConnectorSetting_t timeSyncConnectorInt1; //!< Timesync connector Int1 setting
  NtTimeSyncConnectorSetting_t timeSyncConnectorInt2; //!< Timesync connector Int2 setting
  enum NtTimeSyncReference_e tsRefPrio[4];                 //!< Timesync source reference priority list
  enum NtTimeSyncReference_e timeRef;                      //!< The current time reference
  enum NtTimeSyncFreqReference_e tsFreqRefPrio[4];         //!< Timesync frequency reference priority list
  enum NtTimeSyncFreqReference_e freqRef;                  //!< The current frequency reference
  uint32_t timeSyncNTTSInSyncLimit;                        //!< The configured NT-TS in-sync limit
  uint32_t timeSyncOSInSyncLimit;                          //!< The configured OS in-sync limit
  uint32_t timeSyncPPSInSyncLimit;                         //!< The configured PPS in-sync limit
  uint32_t timeSyncPTPInSyncLimit;                         //!< The configured PTP in-sync limit
  enum NtTimeSyncInSyncStatus_e timeSyncInSyncStatus;      //!< The timestamp clock time in-sync/out-of-sync status
  enum NtTimeSyncConStatus_e timeSyncCurrentConStatus;     //!< The current time sync connector status
  enum NtTimeSyncPpsStatus_e   timeSyncPpsEnable;          //!< The time sync PPS enable. Activated by an application
  enum NtTimeSyncPpsSyncMode_e timeSyncPpsSyncMode;        //!< When current timeref is PpsIn, this is the sync mode status
  uint32_t timeSyncClockAdjustmentMode;                    //!< The time sync timestamp clock adjustment mode
  /* timeSyncClockAdjustmentMode 2 only */
  uint32_t timeSyncHardReset;                              //!< If hard reset of clock is allowed (time jumps)
  /* timeSyncClockAdjustmentMode 1 only */
  uint32_t timeSyncTimeJumpThreshold;                      //!< The time sync time jump threshold in seconds

  uint32_t timeSyncTimeOffset;                             //!< The time sync offset in nanoseconds. Used for NT-TS and PPS caple delay compensation
  uint64_t timeSyncPpsSampled;                             //!< The sampled PPS time. In ns since 1/1 1970 (unix epoch). if NATIVE timestamp format is configured, the epoch is user defined). Note that timeSyncPpsEnable must be true for this parameter to become valid
  int64_t  timeSyncTimeSkew;                               //!< The time skew in ns (0 if not syncing to a time reference)
  uint32_t highFrequencySampling;                          //!< The high frequency sampling status
  struct NtInfoTimeSyncSample_s sample[NT_TIMESYNC_SAMPLING_CNT]; //!< Timestamp sample sets. @ref NtTimeSyncSamplingSrc_e
  uint64_t timeSyncCpuTsc[2];                              //!< When TS sampling is app initiated through an event write, these values are cpu tsc values before and after the ts sampling

  int64_t  timeSyncClockRateAdjustment;                    //!< The current clock rate adjustment imposed on the TS clock to synchronize to the referenced clock in nanoseconds per second. This is only supported on newer Gen2 adapters (FPGA version must be 46 or above)

  /* Server OS clock synchronization to TS clock */
  uint32_t timeSyncAdapterToOSSyncEnabled;                 //!< Non-zero if this adapter is configured to synchronize the server OS clock
  int64_t  timeSyncOSClockOffset;                          //!< The latest read OS clock offset to the adapter TS clock
  int64_t  timeSyncOSClockRateAdjustment;                  //!< The current clock rate adjustment imposed on the server OS clock to synchronize to the adapter TS clock.
};

/**
 * Time synchronization NT-TS remote info
 */
struct NtInfoTimeSyncStatusExt_s {
  uint32_t infoValid;                         //!< The information is valid if infoValid != 0
  uint32_t extDevSyncSignalOk;                //!< The status of the external synchronization signal (1 if ok, otherwise 0) (Only used if the external device is a NT-TSU)
  uint32_t extDevInSync;                      //!< The external device is in sync (1 if in sync, otherwise 0) (Only used if the external device is a NT-TSU or a NT-TSE)
  uint32_t extDevTimeOfDayOk;                 //!< The external device delivers valid Time Of Day information (1 if valid, otherwise 0)  (Only used if the external device is a NT-TSU or a NT-TSE) For the NT-TSU this indicates if the serial time stream is available. For the NT-TSE this field indicates if the Ethernet connection is up.
  uint32_t extDevOsModeSyncEnabled;           //!< The external device is synching to the OS time (1 if synching, otherwise 0) Only used if the external device is an adapter.
  uint32_t extDevOsModeInSync;                //!< The external device is in synchronization to the OS time (1 if in sync, otherwise 0) Only used if the external device is an adapter.
  uint32_t extDevIsMaster;                    //!< The External device is master (1 if the external device is a NTTSU or NTTSE, otherwise 0)
  uint32_t extAdapterIsMaster;                //!< An external Adapter is master (1 if the external device is an adapter, otherwise 0)
  uint32_t extDevMasterID;                    //!< Master ID of the external device
};



/**
 * Time synchronization statistics
 * support level
 */
enum NtTsStatSupport_e {
  NT_TIMESYNC_STATISTICS_NO_SUPPORT   = 0,      //!< Not supported
  NT_TIMESYNC_STATISTICS_PTP_ONLY     = 1,      //!< When using older FPGAs on PTP adapters, then PTP will be supported only
  NT_TIMESYNC_STATISTICS_FULL_SUPPORT = 2       //!< Full supported. All protocols and failover/fallback are supported
};

/**
 * Overall Time synchronization performance statistics
 * and time sync event counters
 */
struct NtInfoTimeSyncStatistics_s {
  enum NtTsStatSupport_e supported;      //!< Specifies the level of which this feature is supported by the adapter.
  uint64_t ts;                           //!< The adapter time when retrieved in ns since 1/1 1970 (unix epoch). if NATIVE timestamp format is configured, the epoch is user defined)
  uint64_t samples;                      //!< The number of skew samples this statistics report is based on
  int64_t  skew;                         //!< The last recorded clock skew used to adjust the clock
  int64_t  min;                          //!< The minimum clock skew measured
  int64_t  max;                          //!< The maximum clock skew measured
  int64_t  mean;                         //!< The calculate mean clock skew
  int64_t  jitter;                       //!< The peak to peak jitter measured
  uint64_t secSinceReset;                //!< Time elapsed since last reset in seconds (using the OS time)
  double   stdDevSqr;                    //!< The calculated standard deviation square
  /* Timesync event counters */
  uint64_t signalLostCnt;                //!< The number of signal lost events that has occured since last reset
  uint64_t syncLostCnt;                  //!< The number of out-of-sync events (or synchronization lost events) that has occured since last reset
  uint64_t hardResetCnt;                 //!< The number of clock hard reset events that has occured since last reset (including the application triggered)
};


/**
 * NT_INFO_CMD_READ_SYSTEM specific data
 */
struct NtInfoCmdSystem_s {
  struct NtInfoSystem_s data; //!< System data
};

/**
 * NT_INFO_CMD_READ_ADAPTER_V6 specific data.
 * The adapterNo must be initialized for the relevant adapter.
 */
struct NtInfoCmdAdapter_v6_s {
  uint8_t adapterNo;              //!< The adapter to query
  uint8_t Reserved1[3];
  struct NtInfoAdapter_v6_s data; //!< The adapter data
};

/**
 * NT_INFO_CMD_READ_PORT_V9 specific data.
 * The portNo must be initialized for the relevant port.
 */
struct NtInfoCmdPort_v9_s {
  uint8_t portNo;              //!< The port to query
  uint8_t Reserved1[3];
  struct NtInfoPort_v9_s data; //!< The port data
};


/**
 * NT_INFO_CMD_READ_SENSOR specific data.
 * The group, adapterNo/portNo and grpIndex must be initialized for the relevant sensor.
 * For example, to read sensor 2 from port 4, do the following:
 *   info.u.cmd = NT_INFO_CMD_READ_SENSOR;
 *   info.u.sensor.source = NT_SENSOR_SOURCE_PORT;
 *   info.u.sensor.sourceIndex= 4;
 *   info.u.sensor.sensorIndex = 2;
 *   NT_ReadInfo(h, &info);
 */
struct NtInfoCmdSensor_s {
  enum NtSensorSource_e source; //!< The source of the sensor - either a port or adapter sensor
  uint32_t sourceIndex;         //!< The source index - either adapter number or port number on which the sensor resides
  uint32_t sensorIndex;         //!< The sensor index within the source index, for example, 2 for sensor 2 on port 4
  struct NtInfoSensor_s data;   //!< The sensor data
};

/**
 * NT_INFO_CMD_READ_HOSTBUFFER_V1 specific data.
 * The adapterNo, hostBufferNo and hostBufferType must be initialized for the relevant adapter, host buffer number and host buffer type.
 */
struct NtInfoCmdHostBuffer_v1_s {
  uint8_t adapterNo;                         //!< The adapter to query
  uint8_t Reserved1[3];
  uint32_t hostBufferNo;                     //!< The host buffer to query
  enum NtNetHostBufferType_e hostBufferType; //!< The host buffer type, that is, CAPTURE or TX
  struct NtInfoHostBuffer_v1_s data;         //!< The host buffer data
};

/**
 * NT_INFO_CMD_READ_STREAM specific data.
 * Returning information about streams. Currently only the list of active streams is supported.
 */
struct NtInfoCmdStream_s {
//

  struct NtInfoStreams_s data;
};

/**
 * NT_INFO_CMD_READ_STREAMID specific data.
 * Returning information about a streamID.
 */
struct NtInfoCmdstreamID_s {
  int streamId;                             //!< The streamID to query
  struct NtInfoStreamId_s data;             //!< The streamID data
};

/**
 * NT_INFO_CMD_READ_TIMESYNC_V4 specific data.
 * The adapterNo must be initialized for the relevant adapter.
 */
struct NtInfoCmdTimeSync_v4_s {
  uint8_t adapterNo;               //!< The adapter to query
  uint8_t Reserved1[2];
  struct NtInfoTimeSync_v4_s data; //!< The time sync data
};

/**
 * NT_INFO_CMD_READ_TIMESYNC_STAT specific data.
 * The adapterNo must be initialized for the relevant adapter.
 */
struct NtInfoCmdTimeSyncStat_s {
  uint8_t adapterNo;               //!< The adapter to query
  uint8_t Reserved1[2];
  struct NtInfoTimeSyncStatistics_s data; //!< The time sync data
};


/**
 * NT_INFO_CMD_READ_TIMESYNC_EXT_STATUS specific data.
 * The adapterNo must be initialized for the relevant adapter.
 */
struct NtInfoCmdTimeSyncStatusExt_s {
  uint8_t adapterNo;               //!< The adapter to query
  uint8_t Reserved1[3];
  struct NtInfoTimeSyncStatusExt_s data; //!< The time sync data
};



/**
 *  IEEE 1588 PTP network protocol identifier
 */
enum NtPTPNetProt_e {
  NT_PTP_NETW_PROTOCOL_NA         = 0,  //!< invalid protocol ID
  NT_PTP_NETW_PROTOCOL_IPV4_UDP   = 1,  //!< IPv4/UDP protocol
  NT_PTP_NETW_PROTOCOL_IPV6_UDP   = 2,  //!< IPv6/UDP protocol
  NT_PTP_NETW_PROTOCOL_IEEE802_3  = 3,  //!< IEEE 802.3 or Layer 2 protocol
  NT_PTP_NETW_PROTOCOL_DEVICENET  = 4,  //!< DeviceNet
  NT_PTP_NETW_PROTOCOL_CONTROLNET = 5,  //!< ControlNet
  NT_PTP_NETW_PROTOCOL_PROFINET   = 6   //!< PROFINET
};

/**
 * IEEE 1588 PTP: Filter to be applied to calculated
 * offset values before feed to PI controller
 */
enum NtPTPFilter_e {
  NT_PTP_FILTER_NONE       = 0,  //!< No filter
  NT_PTP_FILTER_MIN        = 1,  //!< Minimum filter
  NT_PTP_FILTER_PDV        = 2   //!< PDV filter
};

/**
 * IEEE 1588 PTP time source identifier
 */
enum NtPTPTimeSource_e {
  NT_PTP_TIMESOURCE_NA         = 0,     //!< Invalid
  NT_PTP_TIMESOURCE_ATOMIC     = 0x10,  //!< Time source is an atomic clock
  NT_PTP_TIMESOURCE_GPS        = 0x20,  //!< Time source is GPS
  NT_PTP_TIMESOURCE_TER_RADIO  = 0x30,  //!< Time source is terrestrial radio
  NT_PTP_TIMESOURCE_PTP        = 0x40,  //!< Time source is PTP (external to the domain)
  NT_PTP_TIMESOURCE_NTP        = 0x50,  //!< Time source is NTP
  NT_PTP_TIMESOURCE_HAND_SET   = 0x60,  //!< Time source is hand set
  NT_PTP_TIMESOURCE_OTHER      = 0x90,  //!< Any other time source
  NT_PTP_TIMESOURCE_OSCILLATOR = 0xA0   //!< Time source is free running oscillator
};

/**
 * IEEE 1588 PTP propagation delay measurement mechanism identifier
 */
enum NtPTPDelayMech_e {
  NT_PTP_DELAY_MECHANISM_NA       = 0x00,  //!< Invalid
  NT_PTP_DELAY_MECHANISM_E2E      = 0x01,  //!< End-to-End or delay request-response mechanism
  NT_PTP_DELAY_MECHANISM_P2P      = 0x02,  //!< Peer-to-Peer or peer delay mechanism
  NT_PTP_DELAY_MECHANISM_DISABLED = 0xFE   //!< no propagation delay mechanism implemented
};


/**
 * Timestamp structure used for PTP information request
 * Number of seconds since configured Epoch (if PTP timescale, this is TAI time)
 */
struct NtPTPTimestamp_s  {
  uint32_t sec;             //!< Number of seconds and nano seconds since Epoch
  uint32_t nsec;
};

/**
 * Rx and Tx port statistics for the PTP ethernet port
 */
struct NtPTPPortStat_s {
  // Do not change the order
  uint32_t txGoodBytes;       //!< Number of Good bytes transmitted.
  uint32_t txGoodBroadcast;   //!< Number of Good Broadcast frames transmitted.
  uint32_t txGoodMulticast;   //!< Number of Good Multicast frames transmitted.
  uint32_t txGoodUnicast;     //!< Number of Good Unicast frames transmitted.
  uint32_t rxGoodBytes;       //!< Number of Good bytes received.
  uint32_t rxGoodBroadcast;   //!< Number of Good Broadcast frames received.
  uint32_t rxGoodMulticast;   //!< Number of Good Multicast frames received.
  uint32_t rxGoodUnicast;     //!< Number of Good Unicast frames received.
  uint32_t rxGoodLegalLength; //!< Number of Good legal length received with errors received.
  uint32_t rxFragmented;      //!< Number of Fragmented frames received.
  uint32_t rxJabber;          //!< Number of Jabber frames received.
  uint32_t rxBadBytes;        //!< Number of Bad bytes received.
  uint32_t rxDiscarded;       //!< Number of Discarded frames received.
};

/**
 * IEEE 1588 PTP clock type
 */
enum NtPTPClockType_e {
  NT_PTP_CLOCK_TYPE_ORDINARY = 0,         //!< Ordinary clock slave or master
  NT_PTP_CLOCK_TYPE_BOUNDARY = 1,         //!< Boundary clock
  NT_PTP_CLOCK_TYPE_P2P_TRANSPARENT = 2,  //!< Peer-to-Peer transparent clock
  NT_PTP_CLOCK_TYPE_E2E_TRANSPARENT = 3,  //!< End-to-End transparent clock
  NT_PTP_CLOCK_TYPE_MANAGEMENT = 4        //!< Management node
};

/**
 * Information structure for PTP port
 */
struct NtPTPPort_s {
  /* Clock description */
  enum NtPTPClockType_e clockType;                    //!< Ordinary, boundary or transparent clock
  uint8_t               physicalLayerProtocol[65];    //!< Ethernet IEEE 802.3
  int16_t               physicalAddressLen;           //!< Length of physical address
  uint8_t               physicalAdress[6];            //!< Physical address
  uint8_t               protocolAddress[33];          //!< ex. IPv4:10.10.10.50 or Layer2:00:0D:E9:33:22:11
  uint8_t               manufacturerId[3];            //!< Manufacturer identification
  uint8_t               productDescription[129];      //!< Product description
  uint8_t               revisionData[129];            //!< Product revision
  uint8_t               userDescr[129];               //!< User description
  uint8_t               profileId[6];                 //!< Configured PTP profile
  /* PTP ethernet port configuration/status */
  /* and filter config */
  enum NtLinkSpeed_e    linkSpeed;                    //!< Current link speed on PTP ethernet port
  enum NtPTPNetProt_e   ptpNetProt;                   //!< Configured PTP network protocol
  enum NtPTPFilter_e    ptpFilter;                    //!< Configured PTP filter
  enum NtPTPProfile_e   ptpProfile;                   //!< The PTP profile configured on this adapter
  uint32_t              ipAddress;                    //!< IP address
  uint32_t              ipSubmask;                    //!< IP subnet mask
  uint32_t              ipGateway;                    //!< IP gateway
  bool                  dhcp;                         //!< DHCP enabled
  uint16_t              vlanId;                       //!< Configured Vlan Id
  uint16_t              vlanPrio;                     //!< Configured Vlan priority
};



/**
 * IEEE 1588 PTP clock quality
 */
struct NtPTPclkQuality_s {
  uint8_t  clkClass;       //!< Clock class
  uint8_t  clkAccuracy;    //!< Clock accuracy
  uint16_t clkVariance;    //!< Clock variance
};

/**
 * IEEE 1588 PTP Default Data Set
 */
struct NtPTPdefaultDs_s {
  /* Const values */
  bool     twoStepFlag;                 //!< One or two step clock
  uint8_t  clockId[8];                  //!< Clock Id
  uint16_t NumPorts;                    //!< Number of ports
  struct NtPTPclkQuality_s clkQuality;  //!< Clock quality
  /* From configuration of clock */
  uint8_t priority1;                    //!< Master priority1 for BMC
  uint8_t priority2;                    //!< Master priority2 for BMC
  uint8_t domain;                       //!< PTP domain operating in
  bool    slaveOnly;                    //!< Slave-only identifier
};

/**
 * IEEE 1588 PTP Current Data Set
 */
struct NtPTPcurrentDs_s {
  uint16_t stepsRemoved;    //!< Steps removed information for BMC
  int64_t  offsFromMaster;  //!< Current offset from master
  int64_t  meanPathDelay;   //!< Current mean path delay
};

/**
 * IEEE 1588 PTP Parent Data Set
 */
struct NtPTPparentDs_s {
  uint8_t  parentPortId[8];                 //!< Parent port identifier
  bool     parentStat;                      //!< Is observed variance and observed phase change measured
  uint16_t observedOffsScaledLogVariance;   //!< Observed offset variance of the parent clock, measured by this clock
  int32_t  observedPhaseChangeRate;         //!< Observed phase change rate of the parent clock, measured by this clock
  struct NtPTPclkQuality_s gmQuality;       //!< Grand Master clock quality
  uint8_t  gmId[8];                         //!< Grand Master clock Id
  uint8_t gmPriority1;                      //!< Grand Master priority 1
  uint8_t gmPriority2;                      //!< Grand Master priority 2

  /* Proprietary extension */
  union {
    struct {
      uint8_t grandmasterId;                //!< Power profile Grand master ID
      uint32_t grandmasterTimeInaccuracy;   //!< Power profile grand master time inacuuracy
      uint32_t networkTimeInaccuracy;       //!< Power profile network time inaccuracy
      uint8_t  keyField;                    //!< Alternate time offset indicator tlv keyField
      uint32_t currentOffset;               //!< Alternate time offset indicator tlv currentOffset
      uint32_t jumpSeconds;                 //!< Alternate time offset indicator tlv jumpSeconds
      uint64_t timeOfNextJump;              //!< Alternate time offset indicator tlv timeOfNextJump
      char  displayName[10];                //!< Alternate time offset indicator tlv displayName
    } power;
    struct {
      uint32_t IPv4_Addr;                   //!< IP address of Unicast grand master
      uint8_t ssm_ql;                       //!< Telecom profile SSM quality level
      uint8_t priority;                     //!< The configured priority of current grand master
    } telecom;
  } profile;                                //!< information received on Announce depending on PTP profile used
};

/**
 * IEEE 1588 PTP Time Properties Data Set
 */
struct NtPTPtimePropertiesDs_s {
  int16_t  currentUtcOffset;            //!< Current UTC offset used. This may be from GM or configured if currUtcOffsValid is false
  bool     currUtcOffsValid;            //!< Is current UTC offset specified by GM valid
  bool     leap59;                      //!< True if last minute of current UTC day is 59 sec
  bool     leap61;                      //!< True if last minute of current UTC day is 61 sec
  bool     timeTraceable;               //!< True if timescale and current UTC offset is traceable to a primary source
  bool     frequencyTraceable;          //!< True if the frequency determining the timescale is traceable to a primary source
  bool     ptpTimescale;                //!< True if GM timescale is PTP
  enum NtPTPTimeSource_e timeSource;    //!< Identifies the source used by the GM
};


/**
 * IEEE 1588 PTP Port Data Set
 */
struct NtPTPportDs_s {
  uint8_t  portId[8];                      //!< Port Identity
  enum NtPTPPortState_e state;             //!< Current PTP port state
  int64_t  peerMeanPathDelay;              //!< If using Peer-to-Peer delay mechanism this is the measured P2P propagation delay for this port
  uint8_t  versionNumber;                  //!< PTP version number of this port
  /* Configuration */
  int8_t   logMinDelReqInt;                //!< Current minimum delay request interval (when E2E used)
  int8_t   logAnnoInt;                     //!< Current mean announce interval
  uint8_t  announceReceiptTimeout;         //!< Configured announce receipt timeout multiplier
  int8_t   logSyncInt;                     //!< Configured sync interval used in master mode
  enum NtPTPDelayMech_e delayMechanism;    //!< Configured propagation delay mechanism
  int8_t   logMinPDelayReqInt;             //!< Configured minimum peer delay request interval (when P2P used)
};

/**
 * IEEE 1588 PTP all Data Sets
 */
struct NtPTPDataSets_s {
  struct NtPTPdefaultDs_s        defaultDs;  //!< Default Data Set
  struct NtPTPcurrentDs_s        currentDs;  //!< Current Data Set
  struct NtPTPparentDs_s         parentDs;   //!< Parent Data Set
  struct NtPTPtimePropertiesDs_s timePropDs; //!< Time Property Data Set
  struct NtPTPportDs_s           portDs;     //!< Port Data Set
};

struct NtPTPImplCfg_s {
  int32_t  PTPDelayAsymmetry;  //!< PTP Delay asymmetry compensation parameter in ns
};



/**
 * PTP information structure
 */
struct NtInfoPTP_v2_s {
  bool                    enabled;      //!< Is PTP stack configured to be used (slave, master or ptp pps sampling)
  struct NtPTPTimestamp_s ts;           //!< Timestamp at this info retrieval
  struct NtPTPPort_s      ptpPort;      //!< PTP port information structure
  struct NtPTPDataSets_s  ptpDataSets;  //!< PTP data sets (according to IEEE1588-2008 spec.)
  struct NtPTPPortStat_s  ptpPortStat;  //!< PTP ethernet port statistics
  struct NtPTPImplCfg_s   ptpImplCfg;   //!< PTP implementation configuration settings
};

/**
 * NT_INFO_CMD_READ_PTP_V2 specific data.
 */
struct NtInfoCmdPTP_v2_s {
  uint8_t adapterNo;               //!< The adapter to query
  uint8_t Reserved1[2];
  struct NtInfoPTP_v2_s data;      //!< Query PTP information structure
};




enum NtProductInfoType_e {
  NT_PRODUCT_INFO_TYPE_NONE=0,
  NT_PRODUCT_INFO_TYPE_GEN1,
  NT_PRODUCT_INFO_TYPE_GEN2,
  NT_PRODUCT_INFO_TYPE_NTBPE,
  NT_PRODUCT_INFO_TYPE_GEN3,
};

/**
 * Structure to read product information
 */
typedef struct NtInfoProductInfo_v2_s {
  enum NtProductInfoType_e infoType;  //!< Information from Gen 1, Gen 2, NTBPE or Gen 3 adapter
  char ProductId[32];                 //!< Product ID (P/N)
  char SerialNo[2][32];               //!< Serial number (only index 0 used on Gen 1 otherwise 0 = main, 1 = front)
  char PbaId[2][32];                  //!< PBA ID (only index 0 used on Gen 1 otherwise 0 = main, 1 = front)
  char AvrId[2][32];                  //!< AVR version (only on Gen 2)
  char CpldVersion[32];               //!< CPLD Version
  char fpgaId1[40];                   //!< FPGA Image #0 ID
  char fpgaId2[40];                   //!< FPGA Image #1 ID
  uint16_t customId;                  //!< Custom ID
  uint8_t userId[8];                  //!< User ID
} NtInfoProductInfo_v2_t;


/**
 * Product info
 */
struct NtInfoReadProductInfo_v2_s {
  uint8_t adapterNo;             //!< Adapter number to query for product information
  NtInfoProductInfo_v2_t data;      //!< Product Information returned
};


/**
 * Structure to read NTPL filter usage for gen. 3 adapters
 */
typedef struct NtInfoFilterUsage3ga_s {
  int32_t sizeCount;          //!< Number of frame length filters used
  int32_t protocolCount;      //!< Number of protocol filters used
  int32_t errorCount;         //!< Number of error filters used
  int32_t patternCount;       //!< Number of data filters used
  int32_t dynOffsetCount;     //!< Number of dynamic offsets used
  int32_t group4PlusCount;    //!< Number of group filters used combining 4 patterns with 4 different dynamic offsets
  int32_t group8Count;        //!< Number of group filters used combining 8 patterns with 2 different dynamic offsets
  int32_t ipmatchCount;       //!< Number of IP match filters used
  int32_t ipmatchListOuter;   //!< Number of IP match list outer resources used
  int32_t ipmatchListInner;   //!< Number of IP match list inner resources used
} NtInfoFilterUsage3ga_t;

/**
 * Structure to read NTPL filter usage for gen. 4 adapters
 */
typedef struct NtInfoFilterUsage4ga_s {
  uint32_t categorizerFunctionCount; //!< Number of categorizer functions used
  uint32_t sizeCount;                //!< Number of frame length comparators used
  uint32_t patternExtractorCount;    //!< Number of data extractors used
  uint32_t patternCompareCount;      //!< Number of data comparators used
  uint32_t keyMatchCAMUsage;         //!< CAM usage in percent
  uint32_t keyMatchTCAMUsage;        //!< TCAM usage in percent
} NtInfoFilterUsage4ga_t;

typedef struct NtInfoFilterUsage_v1_s {
  enum NtAdapterFpgaArchGeneration_e generation; //!< Adapter generation
  union {
    NtInfoFilterUsage3ga_t filterUsage3ga;
    NtInfoFilterUsage4ga_t filterUsage4ga;
  } u;
} NtInfoFilterUsage_v1_t;

/**
 * Filter usage command
 */
struct NtInfoCmdFilterUsage_v1_s {
  uint8_t adapterNo;             //!< Adapter number to query for filter usage
  uint8_t Reserved1[3];
  uint32_t ntplId;               //!< Ntpl ID to query. 0 will retrieve total usage
  NtInfoFilterUsage_v1_t data;   //!< Filter usage information returned
};

/**
 * Path delay status codes
 */
enum NtPathDelayStatus_e {
  NT_PATH_DELAY_SUCCESS = 0x0,       //!< Returned delay includes both
                                     //!< adapter and NIM contributions.
  NT_PATH_DELAY_NOT_SUPPORTED = 0x1, //!< The adapter or NIM is not supported;
                                     //!< the returned delay is set to zero.
  NT_PATH_DELAY_LINK_DOWN = 0x2,     //!< The link is down;
                                     //!< the returned delay is set to zero.
  NT_PATH_DELAY_UNKNOWN_NIM = 0x4,   //!< The NIM module is unknown; returned
                                     //!< delay pertains to the adapter/FPGA.
};

/**
 * Structure used for returning port path delay information
 */
typedef struct NtInfoPortPathDelay_s {
  enum NtPathDelayStatus_e status; //!< status code
  int32_t                  delay;  //!< The delay
} NtInfoPortPathDelayInfo_t;

/**
 * Port path delay command structure
 */
#define NT_PATH_DELAY_RX_DIR 0
#define NT_PATH_DELAY_TX_DIR 1
struct NtInfoCmdPortPathDelay_s {
  uint8_t portNo;       //!< logical port number on which to query path delay
  uint8_t direction;    //!< NT_PATH_DELAY_RX_DIR or NT_PATH_DELAY_TX_DIR.
  uint8_t Reserved1[2];
  NtInfoPortPathDelayInfo_t data; //!< Delay information (returned to caller)
};

enum NtPropertyType_e {
  NT_PROPERTY_TYPE_INT = 0,
  NT_PROPERTY_TYPE_UINT,
  NT_PROPERTY_TYPE_STRING
};

typedef struct NtInfoPropertyValue_s {
  enum NtPropertyType_e type;
  union {
    int i;
    uint64_t u;
    char s[120];
  } u;
} NtInfoPropertyValue_t;

/**
 * Property request command
 */
struct NtInfoProperty_s {
  char path[120];
  NtInfoPropertyValue_t data;
};


/* Include commands for backward compatibility */
#if !defined(_NT_NTAPI_NO_COMPAT)
#include "stream_info_compat.h"
#endif


/**
 * Read command structure. Query used for info via NT_InfoRead().
 */
typedef struct NtInfo_s {
  enum NtInfoCmd_e cmd;           //!< Info stream command
  /**
   * Union of data structures for each info stream command
  */
  union NtInfo_u {
    struct NtInfoCmdSystem_s system;                //!< NT_INFO_CMD_READ_SYSTEM specific data
    struct NtInfoCmdAdapter_v6_s adapter_v6;        //!< NT_INFO_CMD_READ_ADAPTER specific data version 5
    struct NtInfoCmdSensor_s sensor;                //!< NT_INFO_CMD_READ_SENSOR specific data
    struct NtInfoCmdHostBuffer_v1_s hostBuffer_v1;  //!< NT_INFO_CMD_READ_HOSTBUFFER specific data version 1
    struct NtInfoCmdStream_s stream;                //!< NT_INFO_CMD_READ_STREAM specific data
    struct NtInfoCmdTimeSync_v4_s timeSync_v4;      //!< NT_INFO_CMD_READ_TIMESYNC specific data version 4
    struct NtInfoCmdTimeSyncStatusExt_s timeSyncExt; //!< NT_INFO_CMD_READ_TIMESYNC_EXT_STATUS specific data
    struct NtInfoCmdPort_v9_s port_v9;              //!< NT_INFO_CMD_READ_PORT_V9 specific data
    struct NtInfoCmdstreamID_s streamID;            //!< NT_INFO_CMD_READ_STREAMID specific data
    struct NtInfoReadProductInfo_v2_s productInfo_v2;//!< NT_INFO_CMD_READ_PRODUCTINFO specific data version 2
    struct NtInfoCmdPTP_v2_s ptp_v2;                //!< NT_INFO_CMD_READ_PTP_V2 specific data
    struct NtInfoCmdFilterUsage_v1_s filterUsage_v1;//!< NT_INFO_CMD_READ_FILTERUSAGE_V1 specific data
    struct NtInfoCmdPortPathDelay_s pathDelay;      //!< NT_INFO_CMD_READ_PATH_DELAY specific data
    struct NtInfoCmdTimeSyncStat_s timeSyncStat;    //!< NT_INFO_CMD_READ_TIMESYNC_STAT specific data
    struct NtInfoProperty_s property;               //!< NT_INFO_CMD_READ_PROPERTY specific data
#if !defined(_NT_NTAPI_NO_COMPAT)
    /* Commands for backward compatibility */
    struct NtInfoCmdTimeSync_v1_s timeSync_v1; //!< NT_INFO_CMD_READ_TIMESYNC specific data version 1
    struct NtInfoCmdTimeSync_v2_s timeSync_v2; //!< NT_INFO_CMD_READ_TIMESYNC specific data version 2
    struct NtInfoCmdTimeSync_v3_s timeSync_v3; //!< NT_INFO_CMD_READ_TIMESYNC specific data version 3
    struct NtInfoCmdAdapter_s adapter;         //!< NT_INFO_CMD_READ_ADAPTER specific data
    struct NtInfoCmdAdapter_v1_s adapter_v1;   //!< NT_INFO_CMD_READ_ADAPTER specific data version 1
    struct NtInfoCmdPort_s port;               //!< NT_INFO_CMD_READ_PORT specific data
    struct NtInfoCmdPort_v1_s port_v1;         //!< NT_INFO_CMD_READ_PORT_V1 specific data
    struct NtInfoCmdTimeSync_s timeSync;       //!< NT_INFO_CMD_READ_TIMESYNC specific data
    struct NtInfoCmdHostBuffer_s  hostBuffer;  //!< NT_INFO_CMD_READ_HOSTBUFFER specific data
    struct NtInfoCmdAdapter_v2_s adapter_v2;   //!< NT_INFO_CMD_READ_ADAPTER specific data version 2
    struct NtInfoCmdPort_v2_s port_v2;         //!< NT_INFO_CMD_READ_PORT_V2 specific data
    struct NtInfoCmdPTP_s ptp;                 //!< NT_INFO_CMD_READ_PTP specific data
    struct NtInfoCmdAdapter_v3_s adapter_v3;   //!< NT_INFO_CMD_READ_ADAPTER specific data version 3
    struct NtInfoCmdPort_v3_s port_v3;         //!< NT_INFO_CMD_READ_PORT_V3 specific data
    struct NtInfoCmdAdapter_v4_s adapter_v4;   //!< NT_INFO_CMD_READ_ADAPTER_V4 specific data version 4
    struct NtInfoCmdPort_v4_s port_v4;         //!< NT_INFO_CMD_READ_PORT_V4 specific data
    struct NtInfoCmdPTP_v1_s ptp_v1;           //!< NT_INFO_CMD_READ_PTP_V1 specific data
    struct NtInfoCmdPort_v5_s port_v5;         //!< NT_INFO_CMD_READ_PORT_V5 specific data
    struct NtInfoCmdAdapter_v5_s adapter_v5;   //!< NT_INFO_CMD_READ_ADAPTER specific data version 5
    struct NtInfoCmdPort_v6_s port_v6;         //!< NT_INFO_CMD_READ_PORT_V6 specific data
    struct NtInfoReadProductInfo_s productInfo;//!< NT_INFO_CMD_READ_PRODUCTINFO specific data
    struct NtInfoCmdPort_v7_s port_v7;         //!< NT_INFO_CMD_READ_PORT_V6 specific data
    struct NtInfoReadProductInfo_v1_s productInfo_v1;//!< NT_INFO_CMD_READ_PRODUCTINFO specific data version 1
    struct NtInfoCmdFilterUsage_s filterUsage; //!< NT_INFO_CMD_READ_FILTERUSAGE specific data
    struct NtInfoCmdPort_v8_s port_v8;         //!< NT_INFO_CMD_READ_PORT_V8 specific data
#endif
  } u;
} NtInfo_t;

/**
 * Info stream handle
 */
typedef struct NtInfoStream_s* NtInfoStream_t;

/**
 * @brief Opens an info stream
 *
 * This function is called to retrieve a handle to an info stream
 *
 * @param[out] hStream          Reference to an NtInfoStream_t stream pointer
 * @param[in]  name             The stream friendly name - used in, for example, logging statements
 *
 * @retval  0    Success
 * @retval !=0   Error
 */
int NT_InfoOpen(NtInfoStream_t *hStream, const char *name);

/**
 * @brief Reads data from an info stream
 *
 * Returns system stream data
 *
 * @param[in]      hStream   NtSystemStream_t handle
 * @param[in,out]  info      The info structure containing query info, which serves as an output buffer for data
 *
 * @retval  0    Success
 * @retval !=0   Error
 */
int NT_InfoRead(NtInfoStream_t hStream, NtInfo_t *info);

/**
 * @brief Closes an info stream
 *
 * This function is called to close an info stream
 *
 * @param[in] hStream          Reference to an NtInfoStream_t stream pointer
 *
 * @retval  0    Success
 * @retval !=0   Error
 */
int NT_InfoClose(NtInfoStream_t hStream);

/** @} */

#endif // __STREAM_INFO_H__
