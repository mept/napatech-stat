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
 * This file contains the Common types that can be used by any interface
 */

#ifndef __COMMONTYPES_H__
#define __COMMONTYPES_H__

#include <limits.h>
#include <stdint.h>

#ifndef _MSC_VER
#include <stdbool.h>
#else

#ifndef __cplusplus

/*
 * In Visual C++ 5.0 and later, bool is implemented as a built-in type with a
 * size of 1 byte hence the C version should have same size. Use unsigned char
 * as MSVC does not provide _Bool.
 */
typedef unsigned char bool;
#define true    1
#define false   0

#endif

#define __bool_true_false_are_defined 1

#endif // _MSC_VER

/**
 * Define cross-platform NT_INLINE keyword for static inline functions
 */
#ifndef NT_INLINE
#ifdef _MSC_VER
#define NT_INLINE __forceinline
#else
#define NT_INLINE inline
#endif
#endif

#define NT_MAX_NUM_ADAPTERS 16

/**
 * Timestamp type.
 */
enum NtTimestampType_e {
  NT_TIMESTAMP_TYPE_NATIVE = 0,    //!< 64-bit 10 ns resolution timer from a base of 0
  NT_TIMESTAMP_TYPE_NATIVE_NDIS,   //!< 64-bit 10 ns resolution timer from a base of January 1, 1601
  NT_TIMESTAMP_TYPE_NATIVE_UNIX,   //!< 64-bit 10 ns resolution timer from a base of January 1, 1970
#ifndef DOXYGEN_INTERNAL_ONLY
  NT_TIMESTAMP_TYPE_NDIS,          //!< Deprecated
#endif
  /**
   * PCAP only supported for Rx, thus no in-line adapter support for these time stamps.
   */
  NT_TIMESTAMP_TYPE_PCAP,          //!< 32-bit seconds and 32-bit usecs from a base of January 1, 1970
  NT_TIMESTAMP_TYPE_PCAP_NANOTIME, //!< 32-bit seconds and 32-bit nsecs from a base of January 1, 1970
  NT_TIMESTAMP_TYPE_UNIX_NANOTIME, //!< 64-bit 1 ns resolution timer from a base of January 1, 1970
};


/**
 * Time stamp method
 */
enum NtTimestampMethod_e {
  NT_TIMESTAMP_METHOD_UNKNOWN = 0, //!< Time stamp method unknown
  NT_TIMESTAMP_METHOD_SOF,         //!< Time stamp at start of frame
  NT_TIMESTAMP_METHOD_EOF          //!< Time stamp at end of frame
};

/**
 * Time stamp inject offset
 */
enum NtTimestampInjectOffsetMode_e {
  NT_TIMESTAMP_INJECT_OFFSET_UNKNOWN = 0, //!< Time stamp inject offset mode unknown
  NT_TIMESTAMP_INJECT_OFFSET_UNSUPPORTED, //!< Time stamp inject offset mode is unsupported
  NT_TIMESTAMP_INJECT_OFFSET_SOF,         //!< Time stamp inject offset calculated from start of frame
  NT_TIMESTAMP_INJECT_OFFSET_EOF          //!< Time stamp inject offset calculated from end of frame
};

/**
 * Time stamp inject dynamic offset
 */
enum NtTimestampInjectDynamicOffset_e {
  NT_TIMESTAMP_INJECT_DYNAMIC_OFFSET_UNKNOWN = 0, //!< Time stamp inject offset mode unknown
  NT_TIMESTAMP_INJECT_DYNAMIC_OFFSET_UNSUPPORTED, //!< Time stamp inject offset mode is unsupported
  NT_TIMESTAMP_INJECT_DYNAMIC_OFFSET_SOF,         //!< Time stamp inject dynamice offset - start of frame
  NT_TIMESTAMP_INJECT_DYNAMIC_OFFSET_EOF,         //!< Time stamp inject dynamice offset - end of frame
  NT_TIMESTAMP_INJECT_DYNAMIC_OFFSET_L3,          //!< Time stamp inject dynamice offset - start of layer 3
  NT_TIMESTAMP_INJECT_DYNAMIC_OFFSET_L4           //!< Time stamp inject dynamice offset - start of layer 4
};

/**
 * Relative TX timing method
 */
enum NtTxTimingMethod_e {
  NT_TX_TIMING_UNSUPPORTED = 0, //!< Changing TX timing is unsupported
  NT_TX_TIMING_ABSOLUTE,        //!< TX is made absolute (time stamp based)
  NT_TX_TIMING_RELATIVE,        //!< TX is made relative (IFG based)
};

/**
 * WIS Mode bit mask
 */
enum NtWISMode_e {
  NT_WIS_MODE_DISABLED      = 0x00, //!< OC-192 WIS mode HW Support but disabled
  NT_WIS_MODE_ENABLED       = 0x01, //!< OC-192 WIS mode enabled
};

enum NtHighFrequencySampling_e {
  NT_HIGH_FREQUENCY_SAMPLING_DISABLE = 0, //!< High frequency sampling not used
  NT_HIGH_FREQUENCY_SAMPLING_ENABLE,      //!< High frequency sampling activated
};

enum NtOsTimeSyncFailover_e {
  NT_OS_TIMESYNC_FAILOVER_DISABLE = 0, //!< OS Timesync failover disabled
  NT_OS_TIMESYNC_FAILOVER_ENABLE,      //!< OS Timesync failover enabled
};

/**
 * Host buffer types.
 * Used to select between RX or TX host buffers.
 */
enum NtNetHostBufferType_e {
  NT_NET_HOSTBUFFER_TYPE_UNKNOWN=0, //!< Host buffer type is unknown
  NT_NET_HOSTBUFFER_TYPE_RX,        //!< Host buffer type is RX (ntservice.ini file tag: HostBufferRx)
  NT_NET_HOSTBUFFER_TYPE_TX,        //!< Host buffer type is TX (ntservice.ini file tag: HostBufferTx)
};

/**
 * Host buffer layout
 * Defined how the host buffer layout is defined
 */
enum NtNetHostBufferLayout_e {
  NT_NET_HOSTBUFFER_LAYOUT_UNKNOWN=0,   //!< Unknown host buffer layout
  NT_NET_HOSTBUFFER_LAYOUT_SLABS,       //!< The host buffer is slab based. Packets are in this mode not allowed to spread across slabs and the slab is therefore terminated if the next packet doesn't fit into the current slab. A slab is 1MB.
  NT_NET_HOSTBUFFER_LAYOUT_CIRCULAR,    //!< The host buffer consist of one circular buffer there packets can start at the tail and continue at the head.
};

/**
 * The stream types supported.
 */
enum NtMsgEndpoint_e {
  NT_MSG_ENDPOINT_UNKNOWN=0,      //!< Unknown stream type
  NT_MSG_ENDPOINT_NET_STREAM,     //!< Network stream
  NT_MSG_ENDPOINT_CONFIG_STREAM,  //!< Configuration stream
  NT_MSG_ENDPOINT_STAT_STREAM,    //!< Statistics stream
  NT_MSG_ENDPOINT_EVENT_STREAM,   //!< Event stream
  NT_MSG_ENDPOINT_INFO_STREAM,    //!< Info stream
  NT_MSG_ENDPOINT_SYSTEM_STREAM,  //!< System-wide stream. @note This is vital and is automatically created in NT_Init() and must
                                  //!< only be created once per process. The reason is that when it closes we expect the process is
                                  //!< terminated and will perform system-wide cleanup for all resourced linked to that process.
  NT_MSG_ENDPOINT_NET_CMD,        //!< Network stream related command endpoint
  NT_MSG_ENDPOINT_FLOW_STREAM     //!< Flow stream
};

/**
 * Adapter types
 */
enum NtAdapterType_e {
  NT_ADAPTER_TYPE_UNKNOWN=0,     //!< Unknown adapter type
  NT_ADAPTER_TYPE_NT4E,          //!< NT4E network adapter
  NT_ADAPTER_TYPE_NT20E,         //!< NT20E network adapter
  NT_ADAPTER_TYPE_NT4E_STD,      //!< NT4E-STD network adapter
  NT_ADAPTER_TYPE_NT4E_PORT,     //!< NTPORT4E expansion adapter
  NT_ADAPTER_TYPE_NTBPE,         //!< NTBPE bypass adapter
  NT_ADAPTER_TYPE_NT20E2,        //!< NT20E2 network adapter
  NT_ADAPTER_TYPE_RESERVED1,     //!< Reserved
  NT_ADAPTER_TYPE_RESERVED2,     //!< Reserved
  NT_ADAPTER_TYPE_NT40E2_1,      //!< NT40E2-1 network adapter
  NT_ADAPTER_TYPE_NT40E2_4,      //!< NT40E2-4 network adapter
  NT_ADAPTER_TYPE_NT4E2_4T_BP,   //!< NT4E2-4T-BP bypass network adapter
  NT_ADAPTER_TYPE_NT4E2_4_PTP,   //!< NT4E2-4 PTP network adapter with IEEE1588
  NT_ADAPTER_TYPE_NT20E2_PTP,    //!< NT20E2 PTP network adapter with IEEE1588
  NT_ADAPTER_TYPE_NT40E3_4_PTP,  //!< NT40E3 network adapter with IEEE1588
  NT_ADAPTER_TYPE_NT100E3_1_PTP, //!< NT100E3 network adapter with IEEE1588
  NT_ADAPTER_TYPE_NT20E3_2_PTP,  //!< NT20E3 network adapter with IEEE1588
  NT_ADAPTER_TYPE_NT80E3_2_PTP,  //!< NT80E3 network adapter with IEEE1588
  NT_ADAPTER_TYPE_NT200E3_2,     //!< NT200E3 network adapter
  NT_ADAPTER_TYPE_NT200A01,      //!< NT200A01 network adapter
  NT_ADAPTER_TYPE_NT200A01_2X100 = NT_ADAPTER_TYPE_NT200A01, //!< NT200A01 2 x 100 Gbps network adapter
  NT_ADAPTER_TYPE_NT40A01_4X1,   //!< NT40A01_4X1 network adapter with IEEE1588
  NT_ADAPTER_TYPE_NT200A01_2X40, //!< NT200A01 2 x 40 Gbps network adapter
  NT_ADAPTER_TYPE_NT80E3_2_PTP_8X10,  //!< NT80E3 8 x 10 Gbps network adapter with IEEE1588
  //
  NT_ADAPTER_TYPE_INTEL_A10_4X10, //!<Intel PAC A10 GX 4 x 10 Gbps network adapter
  NT_ADAPTER_TYPE_INTEL_A10_1X40, //!<Intel PAC A10 GX 1 x 40 Gbps network adapter
  //
  NT_ADAPTER_TYPE_NT200A01_8X10,  //!< NT200A01 8 x 10 Gbps network adapter
  NT_ADAPTER_TYPE_NT200A02_2X100, //!< NT200A02 2 x 100 Gbps network adapter
  NT_ADAPTER_TYPE_NT200A02_2X40,  //!< NT200A02 2 x 40 Gbps network adapter
  NT_ADAPTER_TYPE_NT200A01_2X25,  //!< Deprecated
  NT_ADAPTER_TYPE_NT200A01_2X10_25 = NT_ADAPTER_TYPE_NT200A01_2X25, //!< NT200A01 2 x 10/25 Gbps network adapter
  NT_ADAPTER_TYPE_NT200A02_2X25,  //!< Deprecated
  NT_ADAPTER_TYPE_NT200A02_2X10_25 = NT_ADAPTER_TYPE_NT200A02_2X25, //!< NT200A02 2 x 10/25 Gbps network adapter
  NT_ADAPTER_TYPE_NT200A02_4X25,  //!< Deprecated
  NT_ADAPTER_TYPE_NT200A02_4X10_25 = NT_ADAPTER_TYPE_NT200A02_4X25, //!< NT200A02 4 x 10/25 Gbps network adapter
  NT_ADAPTER_TYPE_NT200A02_8X10,  //!< NT200A02 8 x 10 Gbps network adapter
  NT_ADAPTER_TYPE_NT50B01_2X25,   //!< Deprecated
  NT_ADAPTER_TYPE_NT50B01_2X10_25 = NT_ADAPTER_TYPE_NT50B01_2X25, //!< NT50B01 2 x 10/25 Gbps network adapter
  NT_ADAPTER_TYPE_NT200A02_2X1_10,   //!< NT200A02 2 x 1/10 Gbps network adapter
  NT_ADAPTER_TYPE_NT100A01_4X1_10,   //!< NT100A01 4 x 1/10 Gbps network adapter
  NT_ADAPTER_TYPE_NT100A01_4X10_25,  //!< NT100A01 4 x 10/25 Gbps network adapter
  NT_ADAPTER_TYPE_NT50B01_2X1_10,   //!< NT50B01 2 x 1/10 Gbps network adapter
  //NT_ADAPTER_TYPE_NT200A02_2X1_10_25,   //!< NT200A02 2 x 1/10/25 Gbps network adapter. OBS In the future

  //
  //
//

};

typedef enum NtAdapterType_e NtAdapterType_t;

/**
 * Adapter PCI generation
 */

enum NtAdapterPciGeneration_e {
  NT_ADAPTER_PCI_GENERATION_UNKNOWN=0,
  NT_ADAPTER_PCI_GENERATION_1,
  NT_ADAPTER_PCI_GENERATION_2,
  NT_ADAPTER_PCI_GENERATION_3
};

typedef enum NtAdapterPciGeneration_e NtAdapterPciGeneration_t;

/**
 * Adapter hardware generation
 *
 * NOTE: This is *NOT* equal to PCIe generation
 */

enum NtAdapterHwGeneration_e {
  NT_ADAPTER_HW_GENERATION_UNKNOWN=0,
  NT_ADAPTER_HW_GENERATION_1GA,
  NT_ADAPTER_HW_GENERATION_2GA,
  NT_ADAPTER_HW_GENERATION_3GA,
  NT_ADAPTER_HW_GENERATION_4GA,
};

typedef enum NtAdapterHwGeneration_e NtAdapterHwGeneration_t;

/**
 * Adapter FPGA Architecture Generation
 *
 * NOTE: may differ from Adapter (hardware) generation
 */

enum NtAdapterFpgaArchGeneration_e {
  NT_ADAPTER_FPGA_ARCH_GENERATION_UNKNOWN=0,
  NT_ADAPTER_FPGA_ARCH_GENERATION_1,
  NT_ADAPTER_FPGA_ARCH_GENERATION_2,
  NT_ADAPTER_FPGA_ARCH_GENERATION_3,
  NT_ADAPTER_FPGA_ARCH_GENERATION_4,
};

typedef enum NtAdapterFpgaArchGeneration_e  NtAdapterFpgaArchGeneration_t;

/**
 * Packet descriptor type
 */
enum NtPacketDescriptorType_e {
  NT_PACKET_DESCRIPTOR_TYPE_UNKNOWN,               //!< Unknown descriptor type
  NT_PACKET_DESCRIPTOR_TYPE_PCAP,                  //!< Descriptor type is PCAP
  NT_PACKET_DESCRIPTOR_TYPE_NT,                    //!< Descriptor type is NT
  NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED,           //!< Descriptor type is NT extended
  NT_PACKET_DESCRIPTOR_TYPE_DYNAMIC,               //!< Descriptor type is Dynamic (fields can be programmed via NTPL)
};

/*
 * Napatech Dynamic Descriptor formats.
 */
enum NtDynamicDescriptorFormat_e {
  NT_DYNAMIC_DESCRIPTOR_FORMAT_1 = 1, //!< Dynamic descriptor with 3 dynamic offsets and a dynamic IPProcotol selector.
  NT_DYNAMIC_DESCRIPTOR_FORMAT_2 = 2, //!< Dynamic descriptor with 2 dynamic offsets and a dynamic IPProcotol selector.
  NT_DYNAMIC_DESCRIPTOR_FORMAT_3 = 3, //!< Dynamic descriptor 3 is suited for various TX inline scenarios
  NT_DYNAMIC_DESCRIPTOR_FORMAT_4 = 4, //!< Dynamic descriptor 4 is suited for various correlation scenarios
};

/**
 * Product types
 */
enum NtProductType_e {
  NT_PRODUCT_TYPE_UNKNOWN=0,      //!< Unknown product type
  NT_PRODUCT_TYPE_CAPTURE,        //!< Capture product type
  NT_PRODUCT_TYPE_INLINE,         //!< In-line product type
  NT_PRODUCT_TYPE_CAPTURE_REPLAY, //!< Capture-replay product type
  NT_PRODUCT_TYPE_TRAFFIC_GEN,    //!< Traffic generator product type
  NT_PRODUCT_TYPE_BYPASS,         //!< Bypass product type
};

typedef enum NtProductType_e NtProductType_t;

/**
 * Profile types
 */
enum NtProfileType_e {
  NT_PROFILE_TYPE_UNKNOWN=0,           //!< Unknown profile type
  NT_PROFILE_TYPE_CAPTURE=1<<0,        //!< Capture profile type
  NT_PROFILE_TYPE_INLINE=1<<1,         //!< In-line profile type
  NT_PROFILE_TYPE_CAPTURE_REPLAY=1<<2, //!< Capture-replay profile type
  NT_PROFILE_TYPE_TRAFFIC_GEN=1<<3,    //!< Traffic generator profile type
};

/**
 * Product family
 */
enum NtProductFamily_e {
  NT_PRODUCT_FAMILY_UNKNOWN=0, //!< Unknown product family
  NT_PRODUCT_FAMILY_NT,        //!< NT adapter family
  NT_PRODUCT_FAMILY_NIC,       //!< Standard NIC product family
};

typedef enum NtProductFamily_e NtProductFamily_t;

enum NtFeatureType_e {
  NT_FEATURE_TYPE_BYPASS=1<<0,   //!< The adapter has support for bypass.
  NT_FEATURE_TYPE_NEBS=1<<1,     //!< The adapter is a NEBS adapter.
  NT_FEATURE_TYPE_FAN=1<<2,      //!< The adapter has an alternative FAN.
  NT_FEATURE_TYPE_FEC_SUPP=1<<3, //!< The adapter has support for FEC.
  NT_FEATURE_TYPE_SOF_SUPP=1<<4, //!< The adapter has support for SOF.
};

/**
 * SDRAM module sizes
 */
enum NtSdramSize_e {
  NT_SDRAM_SIZE_UNKNOWN=0,      //!< Unknown RAM size
  NT_SDRAM_SIZE_0G = (-1),      //!< RAM size 0 gigabytes
  NT_SDRAM_SIZE_512M = 0x1,     //!< RAM size 512 megabytes
  NT_SDRAM_SIZE_1G = 0x2,       //!< RAM size 1 gigabyte
  NT_SDRAM_SIZE_2G = 0x4,       //!< RAM size 2 gigabytes
  NT_SDRAM_SIZE_4G = 0x8,       //!< RAM size 4 gigabytes
  NT_SDRAM_SIZE_5G = 0xA,       //!< RAM size 5 gigabytes
  NT_SDRAM_SIZE_8G = 0x10,      //!< RAM size 8 gigabytes
  NT_SDRAM_SIZE_10G = 0x14,     //!< RAM size 10 gigabytes
  NT_SDRAM_SIZE_12G = 0x18,     //!< RAM size 12 gigabytes
};

/**
 * SDRAM module type
 */
enum NtSdramType_e {
  NT_SDRAM_TYPE_UNKNOWN=0,       //!< Unknown RAM type
  NT_SDRAM_TYPE_DDR2 = 0x1,      //!< RAM is DDR2
  NT_SDRAM_TYPE_DDR3 = 0x2,      //!< RAM is DDR3
  NT_SDRAM_TYPE_DDR4 = 0x3,      //!< RAM is DDR4
};

/**
 * SDRAM OnboardMemorySplit
 */
enum NtSdramOnboardMemorySplit_e {
  NT_SDRAM_ONBOARD_MEMORY_SPLIT_UNKNOWN = 0,
  NT_SDRAM_ONBOARD_MEMORY_SPLIT_DYNAMIC = 1,
  NT_SDRAM_ONBOARD_MEMORY_SPLIT_EVEN = 2,
  NT_SDRAM_ONBOARD_MEMORY_SPLIT_PROPORTIONAL = 3,
  NT_SDRAM_ONBOARD_MEMORY_SPLIT_DEFAULT = NT_SDRAM_ONBOARD_MEMORY_SPLIT_EVEN
};

/**
 * Port types
 * The use of all non-generic XX_NOT_PRESENT is deprecated - use
 * NT_PORT_TYPE_NIM_NOT_PRESENT instead
 */
enum NtPortType_e {
  NT_PORT_TYPE_NOT_AVAILABLE = 0,      //!< The NIM/port type is not available (unknown)
  NT_PORT_TYPE_NOT_RECOGNISED,         //!< The NIM/port type not recognized
  NT_PORT_TYPE_RJ45,                   //!< RJ45 type
  NT_PORT_TYPE_SFP_NOT_PRESENT,        //!< SFP type but slot is empty
  NT_PORT_TYPE_SFP_SX,                 //!< SFP SX
  NT_PORT_TYPE_SFP_SX_DD,              //!< SFP SX digital diagnostic
  NT_PORT_TYPE_SFP_LX,                 //!< SFP LX
  NT_PORT_TYPE_SFP_LX_DD,              //!< SFP LX digital diagnostic
  NT_PORT_TYPE_SFP_ZX,                 //!< SFP ZX
  NT_PORT_TYPE_SFP_ZX_DD,              //!< SFP ZX digital diagnostic
  NT_PORT_TYPE_SFP_CU,                 //!< SFP copper
  NT_PORT_TYPE_SFP_CU_DD,              //!< SFP copper digital diagnostic
  NT_PORT_TYPE_SFP_NOT_RECOGNISED,     //!< SFP unknown
  NT_PORT_TYPE_XFP,                    //!< XFP
  NT_PORT_TYPE_XPAK,                   //!< XPAK
  NT_PORT_TYPE_SFP_CU_TRI_SPEED,       //!< SFP copper tri-speed
  NT_PORT_TYPE_SFP_CU_TRI_SPEED_DD,    //!< SFP copper tri-speed digital diagnostic
  NT_PORT_TYPE_SFP_PLUS,               //!< SFP+ type
  NT_PORT_TYPE_SFP_PLUS_NOT_PRESENT,   //!< SFP+ type but slot is empty
  NT_PORT_TYPE_XFP_NOT_PRESENT,        //!< XFP type but slot is empty
  NT_PORT_TYPE_QSFP_PLUS_NOT_PRESENT,  //!< QSFP type but slot is empty
  NT_PORT_TYPE_QSFP_PLUS,              //!< QSFP type
  NT_PORT_TYPE_SFP_PLUS_PASSIVE_DAC,   //!< SFP+ Passive DAC
  NT_PORT_TYPE_SFP_PLUS_ACTIVE_DAC,    //!< SFP+ Active DAC
  NT_PORT_TYPE_CFP4,                   //!< CFP4 type
  NT_PORT_TYPE_CFP4_LR4 = NT_PORT_TYPE_CFP4,  //!< CFP4 100G, LR4 type
  NT_PORT_TYPE_CFP4_NOT_PRESENT,       //!< CFP4 type but slot is empty
  NT_PORT_TYPE_INITIALIZE,             //!< The port type is not fully established yet
  NT_PORT_TYPE_NIM_NOT_PRESENT,        //!< Generic "Not present"
  NT_PORT_TYPE_HCB,                    //!< Test mode: Host Compliance Board
  NT_PORT_TYPE_NOT_SUPPORTED,          //!< The NIM type is not supported in this context
  NT_PORT_TYPE_SFP_PLUS_DUAL_RATE,     //!< SFP+ supports 1G/10G
  NT_PORT_TYPE_CFP4_SR4,               //!< CFP4 100G, SR4 type
  NT_PORT_TYPE_QSFP28_NOT_PRESENT,     //!< QSFP28 type but slot is empty
  NT_PORT_TYPE_QSFP28,                 //!< QSFP28 type
  NT_PORT_TYPE_QSFP28_SR4,             //!< QSFP28-SR4 type
  NT_PORT_TYPE_QSFP28_LR4,             //!< QSFP28-LR4 type
  NT_PORT_TYPE_QSFP_PLUS_4X10,         //!< Deprecated. The port type should not mention speed eg 4x10 or 1x40
  NT_PORT_TYPE_QSFP_PASSIVE_DAC_4X10,  //!< Deprecated. The port type should not mention speed eg 4x10 or 1x40
  NT_PORT_TYPE_QSFP_PASSIVE_DAC = NT_PORT_TYPE_QSFP_PASSIVE_DAC_4X10, //!< QSFP passive DAC type
  NT_PORT_TYPE_QSFP_ACTIVE_DAC_4X10,   //!< Deprecated. The port type should not mention speed eg 4x10 or 1x40
  NT_PORT_TYPE_QSFP_ACTIVE_DAC = NT_PORT_TYPE_QSFP_ACTIVE_DAC_4X10, //!< QSFP active DAC type
  NT_PORT_TYPE_SFP_28,                 //!< SFP28 type
  NT_PORT_TYPE_SFP_28_SR,              //!< SFP28-SR type
  NT_PORT_TYPE_SFP_28_LR,              //!< SFP28-LR type
  NT_PORT_TYPE_SFP_28_CR_CA_L,         //!< SFP28-CR-CA-L type
  NT_PORT_TYPE_SFP_28_CR_CA_S,         //!< SFP28-CR-CA-S type
  NT_PORT_TYPE_SFP_28_CR_CA_N,         //!< SFP28-CR-CA-N type
  NT_PORT_TYPE_QSFP28_CR_CA_L,         //!< QSFP28-CR-CA-L type
  NT_PORT_TYPE_QSFP28_CR_CA_S,         //!< QSFP28-CR-CA-S type
  NT_PORT_TYPE_QSFP28_CR_CA_N,         //!< QSFP28-CR-CA-N type
  NT_PORT_TYPE_SFP_28_SR_DR,           //!< SFP28-SR-DR type
  NT_PORT_TYPE_SFP_28_LR_DR,           //!< SFP28-LR-DR type
  NT_PORT_TYPE_SFP_FX,                 //!< SFP FX
  NT_PORT_TYPE_SFP_PLUS_CU,            //!< SFP+ CU type
};

typedef enum NtPortType_e NtPortType_t, *NtPortType_p;

/**
 * Link state.\n
 * Just after start of ntservice the link state might be unknown since the
 * monitoring routine is busy reading NIM state and NIM data. This might also
 * be the case after a NIM is plugged into an interface.
 * The error state indicates a HW reading error.
 */
enum NtLinkState_e {
  NT_LINK_STATE_UNKNOWN = 0, //!< The link state has not been read yet
  NT_LINK_STATE_DOWN    = 1, //!< The link state is DOWN
  NT_LINK_STATE_UP      = 2, //!< The link state is UP
  NT_LINK_STATE_ERROR   = 3  //!< The link state could not be read
};

typedef enum NtLinkState_e NtLinkState_t, *NtLinkState_p;

/**
 * Link speed.
 * Note this is a bitmask.
 */
enum NtLinkSpeed_e {
  NT_LINK_SPEED_UNKNOWN = 0,
  NT_LINK_SPEED_10M  = 0x01, //!< 10 Mbps
  NT_LINK_SPEED_100M = 0x02, //!< 100 Mbps
  NT_LINK_SPEED_1G   = 0x04, //!< 1 Gbps  (Autoneg only)
  NT_LINK_SPEED_10G  = 0x08, //!< 10 Gbps (Autoneg only)
  NT_LINK_SPEED_40G  = 0x10, //!< 40 Gbps (Autoneg only)
  NT_LINK_SPEED_100G = 0x20, //!< 100 Gbps (Autoneg only)
  NT_LINK_SPEED_50G  = 0x40, //!< 50 Gbps (Autoneg only)
  NT_LINK_SPEED_25G  = 0x80, //!< 25 Gbps (Autoneg only)
  NT_LINK_SPEED_END //!< always keep this entry as the last in enum
};

typedef enum NtLinkSpeed_e NtLinkSpeed_t;

/**
 * Link duplex mode
 */
enum NtLinkDuplex_e {
  NT_LINK_DUPLEX_UNKNOWN=0,
  NT_LINK_DUPLEX_HALF = 0x01, //!< Half duplex
  NT_LINK_DUPLEX_FULL = 0x02, //!< Full duplex
};

typedef enum NtLinkDuplex_e NtLinkDuplex_t;

/**
 * Link MDI mode
 */
enum NtLinkMDI_e {
  NT_LINK_MDI_NA = 0,
  NT_LINK_MDI_AUTO = 0x01,  //!< MDI auto
  NT_LINK_MDI_MDI  = 0x02,  //!< MDI mode
  NT_LINK_MDI_MDIX = 0x04,  //!< MDIX mode
};

typedef enum NtLinkMDI_e NtLinkMDI_t;

/**
 * Link Auto/Manual mode
 */
enum NtLinkAutoNeg_e {
  NT_LINK_AUTONEG_NA     = 0,
  NT_LINK_AUTONEG_MANUAL = 0x01,
  NT_LINK_AUTONEG_OFF    = NT_LINK_AUTONEG_MANUAL, //!< Auto negotiation OFF
  NT_LINK_AUTONEG_AUTO   = 0x02,
  NT_LINK_AUTONEG_ON     = NT_LINK_AUTONEG_AUTO,   //!< Auto negotiation ON
};

typedef enum NtLinkAutoNeg_e NtLinkAutoNeg_t;


/**
 * ForceTxLink mode
 */
enum NtForceTxLink_e {
  NT_FORCE_TX_LINK_UNKNOWN = 0,
  NT_FORCE_TX_LINK_DISABLE = 0x01,
  NT_FORCE_TX_LINK_ENABLE  = 0x02
};

typedef enum NtForceTxLink_e NtForceTxLink_t;


/**
 * TX laser power mode
 */
enum NtTxPower_e {
  NT_TX_POWER_UNKNOWN=0, //!< Illegal value - should newer be read or written
  NT_TX_POWER_NA,        //!< Reading: Changing TX Power is not supported.\n Writing: Not valid for writing.
  NT_TX_POWER_ON,        //!< Reading: TX power is on.\n Writing: Turns on the TX power
  NT_TX_POWER_OFF        //!< Reading: TX power is off.\n Writing: Turns off the TX power
};

typedef enum NtTxPower_e NtTxPower_t;

/**
 * Port ID mode
 */
typedef enum NtPortId_e {
  NT_PORT_ID_UNKNOWN=0, //!< Illegal value - should newer be read or written
  NT_PORT_ID_NA,        //!< Reading: Port Identification is not supported.\n Writing: Not valid for writing.
  NT_PORT_ID_ON,        //!< Reading: Port Identification is on.\n Writing: Turns on the port ID
  NT_PORT_ID_OFF        //!< Reading: Port Identification is off.\n Writing: Turns off the port ID
} NtPortId_t;


/**
 * Port FEC (Forward Error Correction) mode
 */
typedef enum NtPortFec_e {
  NT_PORT_FEC_NA =   0,  //!< FEC is not available/unsupported
  NT_PORT_FEC_ON,        //!< FEC is active
  NT_PORT_FEC_OFF        //!< FEC is inactive
} NtPortFec_t;


/**
 * Ifg unit
 */
enum NtIfgMode_e {
  NT_IFG_NS    = 0, //!< Ifg unit is in 10 ns ticks
  NT_IFG_BYTE  = 1, //!< Ifg unit is in bytes
};


/**
 *
 */
enum NtBypassTrigger_e {
  NT_BYPASS_TRIGGER_NONE = 0x00,        //!< TODO:
  NT_BYPASS_TRIGGER_PWRFAIL = 0x01,     //!< TODO:
};

/**
 *
 */
enum NtBypassPortState_e {
  NT_BYPASS_PORT_STATE_UNKNOWN=0,  //!< NT_BYPASS_PORT_STATE_UNKNOWN should be used when reading
  NT_BYPASS_PORT_STATE_IGNORE=0,   //!< NT_BYPASS_PORT_STATE_IGNORE should be used when writing
  NT_BYPASS_PORT_STATE_NORMAL=1,   //!< TODO:
  NT_BYPASS_PORT_STATE_BYPASS=2,   //!< TODO:
};

/**
 *
 */
enum NtOperationReadWrite_e {
  NT_OPERATION_UNKNOWN = 0,        //!< TODO:
  NT_OPERATION_READ = 1,           //!< TODO:
  NT_OPERATION_WRITE = 2,          //!< TODO:
};



/**
 * Time sync protocol
 */
enum NtTimeSyncProtocol_e {
  NT_TIMESYNC_PROTOCOL_NT=0,      //!< Time sync set to NT time sync
  NT_TIMESYNC_PROTOCOL_OS,        //!< Time sync set to OS time sync
  NT_TIMESYNC_PROTOCOL_PPS_REL,   //!< Time sync set to PPS time sync with no external time source
  NT_TIMESYNC_PROTOCOL_PPS_ABS,   //!< Time sync set to PPS time sync with external time source
  NT_TIMESYNC_PROTOCOL_FREE,      //!< Time sync set to free running
};

/**
 * Time sync PPS actions
 */
enum NtTimeSyncPpsAction_e {
  NT_TIMESYNC_PPS_ACTION_REFERENCE_TIME=0,  //!< Send reference TOD to driver
  NT_TIMESYNC_PPS_ACTION_ENABLE,            //!< Enable PPS clock synchronization
  NT_TIMESYNC_PPS_ACTION_DISABLE,           //!< Disable PPS clock synchronization
};

/**
 * Time sync connectors
 */
enum NtTimeSyncConnector_e {
  NT_TIMESYNC_CONNECTOR_NONE = 0,      //!< Time sync connector unused
  NT_TIMESYNC_CONNECTOR_EXT  = 0x01,   //!< Bit mask for external time sync connnector
  NT_TIMESYNC_CONNECTOR_INT1 = 0x02,   //!< Bit mask for internal 1 time sync connnector
  NT_TIMESYNC_CONNECTOR_INT2 = 0x04,   //!< Bit mask for internal 2 time sync connnector
};


/**
 * Time sync PPS current clock synchonization mode
 */
enum NtTimeSyncPpsSyncMode_e {
  NT_TIMESYNC_PPS_MODE_NOT_SYNCING = 0,  //!< Currently not using PPS synchronization
  NT_TIMESYNC_PPS_MODE_PHASE_SYNCING,    //!< Currently using phase synchronization method
  NT_TIMESYNC_PPS_MODE_TIME_SYNCING      //!< Currently using time synchronization
};


/**
 * Time sync connector settings
 */
enum NtTimeSyncConnectorSetting_e {
  NT_TIMESYNC_CONNECTOR_SETTING_NONE = 0,          //!< Connector set to None. Connector not used
  NT_TIMESYNC_CONNECTOR_SETTING_NTTS_IN = 1,       //!< Connector set to NttsIn (NT-TS input)
  NT_TIMESYNC_CONNECTOR_SETTING_PPS_IN = 2,        //!< Connector set to PpsIn (PPS input)
  NT_TIMESYNC_CONNECTOR_SETTING_10MPPS_IN = 3,     //!< 10MPPS - Frequency reference input (not yet supported)
  NT_TIMESYNC_CONNECTOR_SETTING_NTTS_OUT = 4,      //!< Connector set to NttsOut (NT-TS output)
  NT_TIMESYNC_CONNECTOR_SETTING_PPS_OUT = 5,       //!< Connector set to PpsOut (PPS output)
  NT_TIMESYNC_CONNECTOR_SETTING_10MPPS_OUT = 6,    //!< 10MPPS - Frequency output  (not yet supported)
  NT_TIMESYNC_CONNECTOR_SETTING_REPEAT_INT1 = 7,   //!< Connector set to repeat connector Int1
  NT_TIMESYNC_CONNECTOR_SETTING_REPEAT_INT2 = 8,   //!< Connector set to repeat connector Int2
  NT_TIMESYNC_CONNECTOR_SETTING_REPEAT_EXT1 = 9,   //!< Connector set to repeat connector Ext1
};

typedef enum NtTimeSyncConnectorSetting_e NtTimeSyncConnectorSetting_t;

/**
 * Time sync connector status
 */
enum NtTimeSyncConStatus_e {
  NT_TIMESYNC_CONNECTOR_STATUS_NONE = 0,         //!< Time sync status not applicable (current TS ref is not a connector)
  NT_TIMESYNC_CONNECTOR_STATUS_SIGNAL_LOST,      //!< Time sync signal lost (NT and PPS)
  NT_TIMESYNC_CONNECTOR_STATUS_SIGNAL_PRESENT,   //!< Time sync signal present (NT and PPS)
};

/**
 * Time sync in-sync status
 *
 * This is set according to the configured parameters
 * TimeSyncOSInSyncLimit, TimeSyncPTPInSyncLimit,
 * TimeSyncPPSInSyncLimit and TimeSyncNTTSInSyncLimit
 */
enum NtTimeSyncInSyncStatus_e {
  NT_TIMESYNC_INSYNC_STATUS_NONE = 0,     //!< Time sync in-sync status not applicable. Have recently lost the reference signal and no new measurements done yet or reference is FreeRun.
  NT_TIMESYNC_INSYNC_STATUS_IN_SYNC,      //!< Time sync in-sync status is in-sync.
  NT_TIMESYNC_INSYNC_STATUS_NOT_IN_SYNC   //!< Time sync in-sync status is not in-sync.
};

/**
 * Time sync PPS status
 */
enum NtTimeSyncPpsStatus_e {
  NT_TIMESYNC_PPS_STATUS_NONE = 0,        //!< PPS clock synchronization status invalid
  NT_TIMESYNC_PPS_STATUS_ENABLED = 0x01,  //!< PPS clock synchronization status enabled by app
  NT_TIMESYNC_PPS_STATUS_DISABLED = 0x02, //!< //!< PPS clock synchronization status disabled
};

/**
 * Time sync reference priority
 */
enum NtTimeSyncReference_e {
  NT_TIMESYNC_REFERENCE_INVALID      = 0,  //!< Time Sync reference undetermined. Set initially or when in a transition state from one reference to another.
  NT_TIMESYNC_REFERENCE_FREE_RUN     = 1,  //!< Time Sync reference id for free running
  NT_TIMESYNC_REFERENCE_PTP          = 2,  //!< Time Sync reference id for PTP
  NT_TIMESYNC_REFERENCE_INT1         = 3,  //!< Time Sync reference id for connector internal 1
  NT_TIMESYNC_REFERENCE_INT2         = 4,  //!< Time Sync reference id for connector internal 2
  NT_TIMESYNC_REFERENCE_EXT1         = 5,  //!< Time Sync reference id for connector external 1
  NT_TIMESYNC_REFERENCE_OSTIME       = 6,  //!< Time Sync reference id for OS Time
};

typedef enum NtTimeSyncReference_e NtTimeSyncReference_t;

/**
 * Time sync frequency reference priority
 */
enum NtTimeSyncFreqReference_e {
  NT_TIMESYNC_FREQ_REFERENCE_INVALID   = 0,  //!< Time Sync frequency reference id invalid
  NT_TIMESYNC_FREQ_REFERENCE_FREE_RUN  = 1,  //!< Time Sync frequency reference id for free running oscillator
  NT_TIMESYNC_FREQ_REFERENCE_SYNC_E    = 2,  //!< Time Sync frequency reference id for PTP port Rx recovered clock (SyncE)
};

/**
 * Time sync sampling source identifier
 */
enum NtTimeSyncSamplingSrc_e {
  NT_TIMESYNC_SAMPLING_EXT1 = 0,    //!< Sampling source is External1 connector
  NT_TIMESYNC_SAMPLING_INT1 = 1,    //!< Sampling source is Internal1 connector
  NT_TIMESYNC_SAMPLING_INT2 = 2,    //!< Sampling source is Internal2 connector
  /* 3,4,5 - for future use */
  NT_TIMESYNC_SAMPLING_PTP  = 6,    //!< Sampling source is PTP clock PPS output.
  NT_TIMESYNC_SAMPLING_APP  = 7,
  NT_TIMESYNC_SAMPLING_CNT
};

/**
 * Time sync sampling source status
 */
enum NtTimeSyncSamplingSrcStatus_e {
  NT_TIMESYNC_SAMPLING_STATUS_INVALID     = 0,   //!< Time sync sampling source status unused
  NT_TIMESYNC_SAMPLING_STATUS_NOT_PRESENT = 1,   //!< Time sync sampling source status not present (no signal/undefined)
  NT_TIMESYNC_SAMPLING_STATUS_PRESENT     = 2    //!< Time sync sampling source status present
};



/**
 * IEEE 1588 PTP port state identifier
 */
enum NtPTPPortState_e {
  NT_PTP_PORT_STATE_NA           = 0,   //!< Invalid
  NT_PTP_PORT_STATE_INIT         = 1,   //!< Initializing
  NT_PTP_PORT_STATE_FAULTY       = 2,   //!< Faulty
  NT_PTP_PORT_STATE_DISABLED     = 3,   //!< Disabled
  NT_PTP_PORT_STATE_LISTENING    = 4,   //!< Listening
  NT_PTP_PORT_STATE_PRE_MASTER   = 5,   //!< Pre Master
  NT_PTP_PORT_STATE_MASTER       = 6,   //!< Master
  NT_PTP_PORT_STATE_PASSIVE      = 7,   //!< Passive
  NT_PTP_PORT_STATE_UNCALIBRATED = 8,   //!< Uncalibrated
  NT_PTP_PORT_STATE_SLAVE        = 9,   //!< Slave
  NT_PTP_PORT_STATE_INACTIVE     = 127, //!< PTP protocol engine inactive
};


/**
 * Sensor types
 */
enum NtSensorType_e {
  NT_SENSOR_TYPE_UNKNOWN      = 0,
  NT_SENSOR_TYPE_TEMPERATURE  = 1, //!< Unit: 0.1 degree Celsius
  NT_SENSOR_TYPE_VOLTAGE      = 2, //!< Unit: 1 mV
  NT_SENSOR_TYPE_CURRENT      = 3, //!< Unit: 1 uA
  NT_SENSOR_TYPE_POWER        = 4, //!< Unit: 0.1 uW
  NT_SENSOR_TYPE_FAN          = 5, //!< Unit: 1 RPM (Revolutions Per Minute)
  NT_SENSOR_TYPE_HIGH_POWER   = 6, //!< Unit: 1 mW
  NT_SENSOR_TYPE_NUMBER       = 7,
};

typedef enum NtSensorType_e NtSensorType_t;

/**
 * Sensor subtypes
 */
enum NtSensorSubType_e {
  NT_SENSOR_SUBTYPE_NA = 0,
  NT_SENSOR_SUBTYPE_POWER_OMA,     //!< Subtype for NT_SENSOR_TYPE_POWER type on optical modules (optical modulation amplitude measured)
  NT_SENSOR_SUBTYPE_POWER_AVERAGE, //!< Subtype for NT_SENSOR_TYPE_POWER type on optical modules (average power measured)
  NT_SENSOR_SUBTYPE_POWER_TOTAL    //!< Subtype for NT_SENSOR_TYPE_HIGH_POWER type on adapters (total power consumption)
};

typedef enum NtSensorSubType_e NtSensorSubType_t;

/**
 * Sensor source
 */
enum NtSensorSource_e {
  NT_SENSOR_SOURCE_UNKNOWN        = 0x00,  //!< Unknown source
  NT_SENSOR_SOURCE_PORT           = 0x01,  //!< Sensors located in a port. These are primary sensors - usually NIM temperature. Presence depends on adapter and NIM type.
  NT_SENSOR_SOURCE_LEVEL1_PORT    = 0x02,  //!< Level 1 sensors located in a port. These are secondary sensors - usually NIM supply voltage, Tx bias and Rx/Tx optical power. Presence depends on adapter and NIM type.
#ifndef DOXYGEN_INTERNAL_ONLY
  NT_SENSOR_SOURCE_LEVEL2_PORT    = 0x04,  //!< Level 2 sensors located in a port
#endif
  NT_SENSOR_SOURCE_ADAPTER        = 0x08,  //!< Sensors mounted on the adapter
  NT_SENSOR_SOURCE_LEVEL1_ADAPTER = 0x10,  //!< Level 1 sensors mounted on the adapter
#ifndef DOXYGEN_INTERNAL_ONLY
  NT_SENSOR_SOURCE_LEVEL2_ADAPTER = 0x20,  //!< Level 2 sensors mounted on the adapter
#endif
};

/**
 * Sensor state
 */
enum NtSensorState_e {
  NT_SENSOR_STATE_UNKNOWN      = 0, //!< Unknown state
  NT_SENSOR_STATE_INITIALIZING = 1, //!< The sensor is initializing
  NT_SENSOR_STATE_NORMAL       = 2, //!< Sensor values are within range
  NT_SENSOR_STATE_ALARM        = 3, //!< Sensor values are out of range
  NT_SENSOR_STATE_NOT_PRESENT  = 4  //!< The sensor is not present, for example, SFP without diagnostics
};

typedef enum NtSensorState_e NtSensorState_t;

/**
 * Sensor value
 */
#define NT_SENSOR_NAN (int)0x80000000 //!< Indicates that sensor value or sensor limit is not valid (Not a Number)

/**
 * Master/Slave
 */
enum NtBondingType_e {
  NT_BONDING_UNKNOWN,       //!< Unknown bonding type
  NT_BONDING_MASTER,        //!< Adapter is master in the bonding
  NT_BONDING_SLAVE,         //!< Adapter is slave in the bonding
  NT_BONDING_PEER           //!< Adapter is bonded, but relationship is symmetric
};

/**
 * Maximum name length for streams
 */
#define NT_MAX_STREAM_NAME_LENGTH 20


/**
 * NT20E2 Adapter sensors
 *
 * When reading sensors using the @ref InfoStream @ref NtInfoSensor_t
 * the source must be @ref NtSensorSource_e::NT_SENSOR_SOURCE_ADAPTER to
 * read the public sensors or @ref NtSensorSource_e::NT_SENSOR_SOURCE_LEVEL1_ADAPTER
 * to read the Diagnostic sensors.
 */
enum NtSensorsAdapterNT20E2_e {
  // Public sensors
  NT_SENSOR_NT20E2_FPGA,              //!< FPGA temperature sensor
  NT_SENSOR_NT20E2_FAN,               //!< FAN speed sensor
  NT_SENSOR_NT20E2_MAIN_EXAR1_TEMP,   //!< Mainboard power supply 1 temperature sensor
  NT_SENSOR_NT20E2_MAIN_EXAR2_TEMP,   //!< Mainboard power supply 2 temperature sensor
  NT_SENSOR_NT20E2_FRONT_EXAR_TEMP,   //!< Front board power supply temperature sensor
  NT_SENSOR_NT20E2_FRONT_TEMP_PBA,    //!< Front board PBA temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT20E2_NT20E2_POWER,      //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E2_FPGA_POWER,        //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E2_DDR3_POWER,        //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E2_PHY_POWER,         //!< PHY power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E2_SFP_0_POWER,       //!< SFP 0 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E2_SFP_1_POWER,       //!< SFP 1 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E2_ADAPTER_MAX,       //!< Number of NT20E2 adapter sensors
};

/**
 * Generic SFP/SFP+/SFP28 sensors
 *
 * These sensors should be used instead of all adapter specific SFP sensors
 * that have been deprecated..
 */
enum NtSensors_SFP {
  NT_SENSOR_SFP_TEMP,
  NT_SENSOR_SFP_SUPPLY,
  NT_SENSOR_SFP_TX_BIAS,
  NT_SENSOR_SFP_TX_POWER,
  NT_SENSOR_SFP_RX_POWER,
};

/**
 * Generic QSFP/QSFP+/QSFP28 sensors
 *
 * These sensors should be used instead of all adapter specific QSFP sensors
 * that have been deprecated..
 */
enum NtSensors_QSFP {
  NT_SENSOR_QSFP_TEMP,
  NT_SENSOR_QSFP_SUPPLY,
  NT_SENSOR_QSFP_TX_BIAS1,
  NT_SENSOR_QSFP_TX_BIAS2,
  NT_SENSOR_QSFP_TX_BIAS3,
  NT_SENSOR_QSFP_TX_BIAS4,
  NT_SENSOR_QSFP_TX_POWER1,
  NT_SENSOR_QSFP_TX_POWER2,
  NT_SENSOR_QSFP_TX_POWER3,
  NT_SENSOR_QSFP_TX_POWER4,
  NT_SENSOR_QSFP_RX_POWER1,
  NT_SENSOR_QSFP_RX_POWER2,
  NT_SENSOR_QSFP_RX_POWER3,
  NT_SENSOR_QSFP_RX_POWER4,
};

//!< The following sensors are deprecated - generic types should be used instead
enum NtSensorsPortNT20E2_e {
  // Public sensors
  NT_SENSOR_NT20E2_NIM,               //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT20E2_SUPPLY,            //!< SFP supply voltage sensor - does not generate alarms
  NT_SENSOR_NT20E2_TX_BIAS,           //!< SFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT20E2_TX,                //!< SFP TX power sensor - does not generate alarms
  NT_SENSOR_NT20E2_RX,                //!< SFP RX power sensor - does not generate alarms
  NT_SENSOR_NT20E2_PORT_MAX,          //!< Number of NT20E2 port sensors
};

/**
 * NT40E2_4 Adapter sensors
 *
 * When reading sensors using the @ref InfoStream @ref NtInfoSensor_t
 * the source must be @ref NtSensorSource_e::NT_SENSOR_SOURCE_ADAPTER to
 * read the public sensors or @ref NtSensorSource_e::NT_SENSOR_SOURCE_LEVEL1_ADAPTER
 * to read the Diagnostic sensors.
 */
enum NtSensorsAdapterNT40E2_4_e {
  // Public sensors
  NT_SENSOR_NT40E2_4_FPGA = NT_SENSOR_NT20E2_FPGA,                         //!< FPGA temperature sensor
  NT_SENSOR_NT40E2_4_FAN = NT_SENSOR_NT20E2_FAN,                           //!< FAN speed sensor
  NT_SENSOR_NT40E2_4_MAIN_EXAR1_TEMP = NT_SENSOR_NT20E2_MAIN_EXAR1_TEMP,   //!< Mainboard power supply 1 temperature sensor
  NT_SENSOR_NT40E2_4_MAIN_EXAR2_TEMP = NT_SENSOR_NT20E2_MAIN_EXAR2_TEMP,   //!< Mainboard power supply 2 temperature sensor
  NT_SENSOR_NT40E2_4_FRONT_EXAR_TEMP = NT_SENSOR_NT20E2_FRONT_EXAR_TEMP,   //!< Front board power supply temperature sensor
  NT_SENSOR_NT40E2_4_FRONT_TEMP_PBA = NT_SENSOR_NT20E2_FRONT_TEMP_PBA,     //!< Front board PBA temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40E2_4_NT40E2_4_POWER = NT_SENSOR_NT20E2_NT20E2_POWER,       //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_4_FPGA_POWER = NT_SENSOR_NT20E2_FPGA_POWER,             //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_4_DDR3_POWER = NT_SENSOR_NT20E2_DDR3_POWER,             //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_4_PHY_POWER = NT_SENSOR_NT20E2_PHY_POWER,               //!< PHY power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_4_SFP_0_POWER = NT_SENSOR_NT20E2_SFP_0_POWER,           //!< SFP 0 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_4_SFP_1_POWER = NT_SENSOR_NT20E2_SFP_1_POWER,           //!< SFP 1 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_4_ADAPTER_MAX = NT_SENSOR_NT20E2_ADAPTER_MAX,           //!< Number of NT40E2_4 adapter sensors
};

//!< The following sensors are deprecated - generic types should be used instead
enum NtSensorsPortNT40E2_4_e {
  // Public sensors
  NT_SENSOR_NT40E2_4_NIM = NT_SENSOR_NT20E2_NIM,              //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40E2_4_SUPPLY = NT_SENSOR_NT20E2_SUPPLY,        //!< SFP supply voltage sensor - does not generate alarms
  NT_SENSOR_NT40E2_4_TX_BIAS = NT_SENSOR_NT20E2_TX_BIAS,      //!< SFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT40E2_4_TX = NT_SENSOR_NT20E2_TX,                //!< SFP TX power sensor - does not generate alarms
  NT_SENSOR_NT40E2_4_RX = NT_SENSOR_NT20E2_RX,                //!< SFP RX power sensor - does not generate alarms
  NT_SENSOR_NT40E2_4_PORT_MAX = NT_SENSOR_NT20E2_PORT_MAX,    //!< Number of NT20E2 port sensors
};

/**
 * NT40E2_1 Adapter sensors
 *
 * When reading sensors using the @ref InfoStream @ref NtInfoSensor_t
 * the source must be @ref NtSensorSource_e::NT_SENSOR_SOURCE_ADAPTER to
 * read the public sensors or @ref NtSensorSource_e::NT_SENSOR_SOURCE_LEVEL1_ADAPTER
 * to read the Diagnostic sensors.
 */
enum NtSensorsAdapterNT40E2_e {
  // Public sensors
  NT_SENSOR_NT40E2_FPGA,              //!< FPGA temperature sensor
  NT_SENSOR_NT40E2_FAN,               //!< FAN speed sensor
  NT_SENSOR_NT40E2_MAIN_EXAR1_TEMP,   //!< Mainboard power supply 1 temperature sensor
  NT_SENSOR_NT40E2_MAIN_EXAR2_TEMP,   //!< Mainboard power supply 2 temperature sensor
  NT_SENSOR_NT40E2_FRONT_EXAR_TEMP,   //!< Front board power supply temperature sensor
  NT_SENSOR_NT40E2_FRONT_TEMP_PBA,    //!< Front board PBA temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40E2_NT40E2_POWER,      //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_FPGA_POWER,        //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_DDR3_POWER,        //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_PHY_POWER,         //!< PHY power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_QSFP_POWER,        //!< QSFP power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_ADAPTER_MAX,       //!< Number of NT40E2 adapter sensors
};

//!< The following sensors are deprecated - generic types should be used instead
enum NtSensorsPortNT40E2_e {
  // Public sensors
  NT_SENSOR_NT40E2_NIM,               //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40E2_SUPPLY,            //!< QSFP+ supply voltage sensor
  NT_SENSOR_NT40E2_TX_BIAS1,          //!< QSFP+ TX bias line 0 current sensor
  NT_SENSOR_NT40E2_TX_BIAS2,          //!< QSFP+ TX bias line 1 current sensor
  NT_SENSOR_NT40E2_TX_BIAS3,          //!< QSFP+ TX bias line 2 current sensor
  NT_SENSOR_NT40E2_TX_BIAS4,          //!< QSFP+ TX bias line 3 current sensor
  NT_SENSOR_NT40E2_RX1,               //!< QSFP+ RX line 0 power sensor
  NT_SENSOR_NT40E2_RX2,               //!< QSFP+ RX line 1 power sensor
  NT_SENSOR_NT40E2_RX3,               //!< QSFP+ RX line 2 power sensor
  NT_SENSOR_NT40E2_RX4,               //!< QSFP+ RX line 3 power sensor
  NT_SENSOR_NT40E2_TX1,               //!< QSFP+ TX line 0 power sensor
  NT_SENSOR_NT40E2_TX2,               //!< QSFP+ TX line 1 power sensor
  NT_SENSOR_NT40E2_TX3,               //!< QSFP+ TX line 2 power sensor
  NT_SENSOR_NT40E2_TX4,               //!< QSFP+ TX line 3 power sensor
  NT_SENSOR_NT40E2_PORT_MAX,          //!< Number of NT40E2 port sensors
};

enum NtSensorsAdapterNT20E_e {
  // Public sensors
  NT_SENSOR_NT20E_FPGA,               //!< FPGA temperature sensor (junction temperature)
  NT_SENSOR_NT20E_PBA,                //!< PCB temperature sensor (PCB temperature)
  NT_SENSOR_NT20E_ADAPTER_MAX,        //!< Number of NT20E adapter sensors
};

enum NtSensorsPortNT20E_e {
  // Public sensors
  NT_SENSOR_NT20E_XFP,               //!< XFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT20E_TX_BIAS,           //!< XFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT20E_TX,                //!< XFP TX power sensor - does not generate alarms
  NT_SENSOR_NT20E_RX,                //!< XFP RX power sensor - does not generate alarms
  NT_SENSOR_NT20E_PORT_MAX,          //!< Number of NT20E port sensors
};

enum NtSensorsAdapterNT4E_e {
  // Public sensors
  NT_SENSOR_NT4E_FPGA,               //!< FPGA temperature sensor (junction temperature)
  NT_SENSOR_NT4E_PBA,                //!< PCB temperature sensor (PCB temperature)
  NT_SENSOR_NT4E_ADAPTER_MAX,        //!< Number of NT4E adapter sensors
};

//!< The following sensors are deprecated - generic types should be used instead
enum NtSensorsPortNT4E_e {
  // Public sensors
  NT_SENSOR_NT4E_SFP,                //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT4E_SUPPLY,             //!< SFP supply voltage sensor - does not generate alarms
  NT_SENSOR_NT4E_TX_BIAS,            //!< SFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT4E_TX,                 //!< SFP TX power sensor - does not generate alarms
  NT_SENSOR_NT4E_RX,                 //!< SFP RX power sensor - does not generate alarms
  NT_SENSOR_NT4E_PORT_MAX,           //!< Number NT4E of port sensors
};

enum NtSensorsAdapterNT4E2_e {
  // Public sensors
  NT_SENSOR_NT4E2_FPGA,              //!< FPGA temperature sensor
  NT_SENSOR_NT4E2_FAN,               //!< FAN speed sensor
  NT_SENSOR_NT4E2_MAIN_EXAR1_TEMP,   //!< Mainboard power supply 1 temperature sensor
  NT_SENSOR_NT4E2_MAIN_EXAR2_TEMP,   //!< Mainboard power supply 2 temperature sensor
  NT_SENSOR_NT4E2_FRONT_EXAR_TEMP,   //!< Front board power supply temperature sensor
  NT_SENSOR_NT4E2_FRONT_TEMP_PBA,    //!< Front board PBA temperature sensor
  NT_SENSOR_NT4E2_FRONT_TEMP_PHY,    //!< Front board PHY temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT4E2_NT4E2_POWER,       //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_FPGA_POWER,        //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_DDR3_POWER,        //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_FRONT_POWER,       //!< FRONT power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_ADAPTER_MAX,       //!< Number of NT4E2 adapter sensors
};

enum NtSensorsAdapterNT4E2_PTP_e {
  // Public sensors
  NT_SENSOR_NT4E2_PTP_FPGA,            //!< FPGA temperature sensor
  NT_SENSOR_NT4E2_PTP_FAN,             //!< FAN speed sensor
  NT_SENSOR_NT4E2_PTP_MAIN_EXAR1_TEMP, //!< Mainboard power supply 1 temperature sensor
  NT_SENSOR_NT4E2_PTP_MAIN_EXAR2_TEMP, //!< Mainboard power supply 2 temperature sensor
  NT_SENSOR_NT4E2_PTP_FRONT_EXAR_TEMP, //!< Front board power supply temperature sensor
  NT_SENSOR_NT4E2_PTP_FRONT_TEMP_PBA,  //!< Front board PBA temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT4E2_PTP_NT4E2_POWER,     //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_PTP_FPGA_POWER,      //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_PTP_DDR3_POWER,      //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_PTP_FRONT_POWER,     //!< FRONT power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_PTP_SFP_0_POWER,     //!< SFP 0 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_PTP_SFP_1_POWER,     //!< SFP 1 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_PTP_ADAPTER_MAX,     //!< Number of NT4E2 adapter sensors
};

//!< The following sensors are deprecated - generic types should be used instead
enum NtSensorsPortNT4E2_PTP_e {
  // Public sensors
  NT_SENSOR_NT4E2_PTP_SFP,             //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT4E2_PTP_SUPPLY,          //!< SFP supply voltage sensor - does not generate alarms
  NT_SENSOR_NT4E2_PTP_TX_BIAS,         //!< SFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT4E2_PTP_TX,              //!< SFP TX power sensor - does not generate alarms
  NT_SENSOR_NT4E2_PTP_RX,              //!< SFP RX power sensor - does not generate alarms
  NT_SENSOR_NT4E2_PTP_PORT_MAX,        //!< Number NT4E of port sensors
};

typedef enum NtSensorsAdapterNT40E3_4_e {
  // Public sensors (Level 0)
  NT_SENSOR_NT40E3_4_FPGA_TEMP,        //!< FPGA temperature sensor
  NT_SENSOR_NT40E3_4_FAN_SPEED,        //!< FAN speed sensor
  NT_SENSOR_NT40E3_4_MCU_TEMP,         //!< MCU (Micro Controller Unit) temperature sensor located inside enclosure below FAN
  NT_SENSOR_NT40E3_4_PSU0_TEMP,        //!< Power supply 0 temperature sensor
  NT_SENSOR_NT40E3_4_PSU1_TEMP,        //!< Power supply 1 temperature sensor
  NT_SENSOR_NT40E3_4_OSC_TEMP,         //!< Clock oscillator temperature sensor
  NT_SENSOR_NT40E3_4_EXT_TEMP,         //!< External temperature sensor located at board corner outside enclosure
  NT_SENSOR_NT40E3_4_PCB_TEMP,         //!< PCB temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40E3_4_NT40E3_4_POWER,   //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E3_4_FPGA_POWER,       //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E3_4_DDR3_POWER,       //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E3_4_NIM_POWER,        //!< NIM power consumption (calculated value) - does not generate alarms

  NT_SENSOR_NT40E3_4_L1_MAX,           //!< Number of NT40E3P4 level 0,1 board sensors
} NtSensorsAdapterNT40E3_4_t;

//!< The following sensors are deprecated - generic types should be used instead
typedef enum NtSensorsPortNT40E3_4_e {
  // Public sensors
  NT_SENSOR_NT40E3_4_NIM,               //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40E3_4_SUPPLY,            //!< SFP supply voltage sensor - does not generate alarms
  NT_SENSOR_NT40E3_4_TX_BIAS,           //!< SFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT40E3_4_TX,                //!< SFP TX power sensor - does not generate alarms
  NT_SENSOR_NT40E3_4_RX,                //!< SFP RX power sensor - does not generate alarms
  NT_SENSOR_NT40E3_4_PORT_MAX,          //!< Number of NT40E3P4 port sensors
} NtSensorsPortNT40E3_4_t;

typedef enum NtSensorsAdapterNT20E3_2_e {
  // Public sensors (Level 0)
  NT_SENSOR_NT20E3_2_FPGA_TEMP = NT_SENSOR_NT40E3_4_FPGA_TEMP,           //!< FPGA temperature sensor
  NT_SENSOR_NT20E3_2_FAN_SPEED = NT_SENSOR_NT40E3_4_FAN_SPEED,           //!< FAN speed sensor
  NT_SENSOR_NT20E3_2_MCU_TEMP  = NT_SENSOR_NT40E3_4_MCU_TEMP,            //!< MCU (Micro Controller Unit) temperature sensor located inside enclosure below FAN
  NT_SENSOR_NT20E3_2_PSU0_TEMP = NT_SENSOR_NT40E3_4_PSU0_TEMP,           //!< Power supply 0 temperature sensor
  NT_SENSOR_NT20E3_2_PSU1_TEMP = NT_SENSOR_NT40E3_4_PSU1_TEMP,           //!< Power supply 1 temperature sensor
  NT_SENSOR_NT20E3_2_OSC_TEMP  = NT_SENSOR_NT40E3_4_OSC_TEMP,            //!< Clock oscillator temperature sensor
  NT_SENSOR_NT20E3_2_EXT_TEMP  = NT_SENSOR_NT40E3_4_EXT_TEMP,            //!< External temperature sensor located at board corner outside enclosure
  NT_SENSOR_NT20E3_2_PCB_TEMP  = NT_SENSOR_NT40E3_4_PCB_TEMP,            //!< PCB temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT20E3_2_NT20E3_2_POWER = NT_SENSOR_NT40E3_4_NT40E3_4_POWER, //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E3_2_FPGA_POWER     = NT_SENSOR_NT40E3_4_FPGA_POWER,     //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E3_2_DDR3_POWER     = NT_SENSOR_NT40E3_4_DDR3_POWER,     //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E3_2_NIM_POWER      = NT_SENSOR_NT40E3_4_NIM_POWER,      //!< NIM power consumption (calculated value) - does not generate alarms

  NT_SENSOR_NT20E3_2_L1_MAX = NT_SENSOR_NT40E3_4_L1_MAX,                 //!< Number of NT40E3P4 level 0,1 board sensors
} NtSensorsAdapterNT20E3_2_t;

//!< The following sensors are deprecated - generic types should be used instead
typedef enum NtSensorsPortNT20E3_2_e {
  // Public sensors
  NT_SENSOR_NT20E3_2_NIM = NT_SENSOR_NT40E3_4_NIM,               //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT20E3_2_SUPPLY   = NT_SENSOR_NT40E3_4_SUPPLY,            //!< SFP supply voltage sensor - does not generate alarms
  NT_SENSOR_NT20E3_2_TX_BIAS  = NT_SENSOR_NT40E3_4_TX_BIAS,           //!< SFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT20E3_2_TX       = NT_SENSOR_NT40E3_4_TX,                //!< SFP TX power sensor - does not generate alarms
  NT_SENSOR_NT20E3_2_RX       = NT_SENSOR_NT40E3_4_RX,                //!< SFP RX power sensor - does not generate alarms
  NT_SENSOR_NT20E3_2_PORT_MAX = NT_SENSOR_NT40E3_4_PORT_MAX,          //!< Number of NT40E3P4 port sensors
} NtSensorsPortNT20E3_2_t;

typedef enum NtSensorsAdapterNT40A01_4X1_e {
  // Public sensors (Level 0)
  NT_SENSOR_NT40A01_4X1_FPGA_TEMP = NT_SENSOR_NT40E3_4_FPGA_TEMP,           //!< FPGA temperature sensor
  NT_SENSOR_NT40A01_4X1_FAN_SPEED = NT_SENSOR_NT40E3_4_FAN_SPEED,           //!< FAN speed sensor
  NT_SENSOR_NT40A01_4X1_MCU_TEMP  = NT_SENSOR_NT40E3_4_MCU_TEMP,            //!< MCU (Micro Controller Unit) temperature sensor located inside enclosure below FAN
  NT_SENSOR_NT40A01_4X1_PSU0_TEMP = NT_SENSOR_NT40E3_4_PSU0_TEMP,           //!< Power supply 0 temperature sensor
  NT_SENSOR_NT40A01_4X1_PSU1_TEMP = NT_SENSOR_NT40E3_4_PSU1_TEMP,           //!< Power supply 1 temperature sensor
  NT_SENSOR_NT40A01_4X1_OSC_TEMP  = NT_SENSOR_NT40E3_4_OSC_TEMP,            //!< Clock oscillator temperature sensor
  NT_SENSOR_NT40A01_4X1_EXT_TEMP  = NT_SENSOR_NT40E3_4_EXT_TEMP,            //!< External temperature sensor located at board corner outside enclosure
  NT_SENSOR_NT40A01_4X1_PCB_TEMP  = NT_SENSOR_NT40E3_4_PCB_TEMP,            //!< PCB temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40A01_4X1_NT40A01_4X1_POWER  = NT_SENSOR_NT40E3_4_NT40E3_4_POWER, //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40A01_4X1_FPGA_POWER     = NT_SENSOR_NT40E3_4_FPGA_POWER,     //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40A01_4X1_DDR3_POWER     = NT_SENSOR_NT40E3_4_DDR3_POWER,     //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40A01_4X1_NIM_POWER      = NT_SENSOR_NT40E3_4_NIM_POWER,      //!< NIM power consumption (calculated value) - does not generate alarms

  NT_SENSOR_NT40A01_4X1_L1_MAX = NT_SENSOR_NT40E3_4_L1_MAX,                 //!< Number of NT40E3P4 level 0,1 board sensors
} NtSensorsAdapterNT40A01_4X1_t;

//!< The following sensors are deprecated - generic types should be used instead
typedef enum NtSensorsPortNT40A01_4X1_e {
  // Public sensors
  NT_SENSOR_NT40A01_4X1_NIM = NT_SENSOR_NT40E3_4_NIM,               //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40A01_4X1_SUPPLY   = NT_SENSOR_NT40E3_4_SUPPLY,            //!< SFP supply voltage sensor - does not generate alarms
  NT_SENSOR_NT40A01_4X1_TX_BIAS  = NT_SENSOR_NT40E3_4_TX_BIAS,           //!< SFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT40A01_4X1_TX       = NT_SENSOR_NT40E3_4_TX,                //!< SFP TX power sensor - does not generate alarms
  NT_SENSOR_NT40A01_4X1_RX       = NT_SENSOR_NT40E3_4_RX,                //!< SFP RX power sensor - does not generate alarms
  NT_SENSOR_NT40A01_4X1_PORT_MAX = NT_SENSOR_NT40E3_4_PORT_MAX,          //!< Number of NT40E3P4 port sensors
} NtSensorsPortNT40A01_4X1_t;

// The NT50B01 adapter sensor id's
typedef enum NtSensorsAdapterNT50B01_e {
  // Public sensors (Level 0)
  NT_SENSOR_NT50B01_FPGA_TEMP,         //!< FPGA temperature sensor
  NT_SENSOR_NT50B01_FAN_SPEED,         //!< FAN speed sensor
  NT_SENSOR_NT50B01_MCU_TEMP,          //!< MCU (Micro Controller Unit) temperature sensor located inside enclosure below FAN
  NT_SENSOR_NT50B01_PSU1_TEMP,         //!< Power supply 1 temperature sensor
  NT_SENSOR_NT50B01_PSU3_TEMP,         //!< Power supply 3 temperature sensor
  NT_SENSOR_NT50B01_PSU4_TEMP,         //!< Power supply 4 temperature sensor
  NT_SENSOR_NT50B01_PCB_TEMP,          //!< PCB temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT50B01_NT50B01_POWER ,   //!< Total power consumption (calculated value) - does not generate alarms

  NT_SENSOR_NT50B01_L1_MAX,            //!< Number of NT50B01 level 0,1 board sensors
} NtSensorsAdapterNT50B01_t;

// The PSU2GA adapter sensor id's
typedef enum NtSensorsAdapterPSU2GA_e {
  // Public sensors (Level 0)
  NT_SENSOR_PSU2GA_FPGA_TEMP = 0U,    //!< FPGA temperature sensor
  NT_SENSOR_PSU2GA_FAN_SPEED,         //!< FAN speed sensor
  NT_SENSOR_PSU2GA_MCU_TEMP,          //!< MCU (Micro Controller Unit) temperature sensor located inside enclosure below FAN
  NT_SENSOR_PSU2GA_PSU1_TEMP,         //!< Power supply 1 temperature sensor
  NT_SENSOR_PSU2GA_PSU3_TEMP,         //!< Power supply 3 temperature sensor
  NT_SENSOR_PSU2GA_PSU4_TEMP,         //!< Power supply 4 temperature sensor
  NT_SENSOR_PSU2GA_PCB_TEMP,          //!< PCB temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_PSU2GA_PSU2GA_POWER ,   //!< Total power consumption (calculated value) - does not generate alarms

  NT_SENSOR_PSU2GA_L1_MAX,            //!< Number of PSU2GA level 0,1 board sensors
} NtSensorsAdapterPSU2GA_t;

//!< The following sensors are deprecated - generic types should be used instead
//The NIM temperature sensor must be the one with the lowest sensorIndex
//(enum value) in order to be shown by the monitoring tool in port mode
enum NtSensorsPortNT50B01_2X25G_e {
  // Public sensors
  NT_SENSOR_NT50B01_2X25G_NIM,         //!< SFP28 temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT50B01_2X25G_SUPPLY,      //!< SFP28 supply voltage sensor
  NT_SENSOR_NT50B01_2X25G_TX_BIAS,     //!< SFP28 TX bias line 0 current sensor
  NT_SENSOR_NT50B01_2X25G_RX,          //!< SFP28 RX line 0 power sensor
  NT_SENSOR_NT50B01_2X25G_TX,          //!< SFP28 TX line 0 power sensor
  NT_SENSOR_NT50B01_2X25G_PORT_MAX,    //!< Number of NT50B01_2X25G port sensors
};

typedef enum NtSensorsAdapterNT80E3_2_e {
  // Public sensors (Level 0)
  NT_SENSOR_NT80E3_FPGA_TEMP,        //!< FPGA temperature sensor
  NT_SENSOR_NT80E3_PCI_BRIDGE_TEMP,  //!< PCI bridge temperature sensor
  NT_SENSOR_NT80E3_FAN_SPEED,        //!< FAN speed sensor
  NT_SENSOR_NT80E3_MCU_TEMP,         //!< MCU (Micro Controller Unit) temperature sensor located inside enclosure below FAN
  NT_SENSOR_NT80E3_PSU0_TEMP,        //!< Power supply 0 temperature sensor
  NT_SENSOR_NT80E3_PSU1_TEMP,        //!< Power supply 1 temperature sensor
  NT_SENSOR_NT80E3_PSU2_0_TEMP,      //!< Power supply 2, IC0 junction temperature sensor
  NT_SENSOR_NT80E3_PSU2_1_TEMP,      //!< Power supply 2, IC1 junction temperature sensor
  NT_SENSOR_NT80E3_OSC_TEMP,         //!< Clock oscillator temperature sensor
  NT_SENSOR_NT80E3_EXT_TEMP,         //!< External temperature sensor located at board corner outside enclosure
  NT_SENSOR_NT80E3_PCB_TEMP,         //!< PCB temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT80E3_NT80E3_POWER,    //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT80E3_FPGA_POWER,       //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT80E3_DDR3_POWER,       //!< DDR3 RAM9 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT80E3_NIM_POWER,        //!< NIM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT80E3_PCI_BRIDGE_POWER, //!< PCI bridge power consumption (calculated value) - does not generate alarms

  NT_SENSOR_NT80E3_L1_MAX,           //!< Number of NT80E3 level 0,1 board sensors
} NtSensorsAdapterNT80E3_2_t;

//!< The following sensors are deprecated - generic types should be used instead
//The NIM temperature sensor must be the one with the lowest sensorIndex
//(enum value) in order to be shown by the monitoring tool in port mode
enum NtSensorsPortNT80E3_2_e {
  // Public sensors
  NT_SENSOR_NT80E3_NIM,               //!< QSFP+ temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT80E3_SUPPLY,            //!< QSFP+ supply voltage sensor
  NT_SENSOR_NT80E3_TX_BIAS1,          //!< QSFP+ TX bias line 0 current sensor
  NT_SENSOR_NT80E3_TX_BIAS2,          //!< QSFP+ TX bias line 1 current sensor
  NT_SENSOR_NT80E3_TX_BIAS3,          //!< QSFP+ TX bias line 2 current sensor
  NT_SENSOR_NT80E3_TX_BIAS4,          //!< QSFP+ TX bias line 3 current sensor
  NT_SENSOR_NT80E3_RX1,               //!< QSFP+ RX line 0 power sensor
  NT_SENSOR_NT80E3_RX2,               //!< QSFP+ RX line 1 power sensor
  NT_SENSOR_NT80E3_RX3,               //!< QSFP+ RX line 2 power sensor
  NT_SENSOR_NT80E3_RX4,               //!< QSFP+ RX line 3 power sensor
  NT_SENSOR_NT80E3_TX1,               //!< QSFP+ TX line 0 power sensor
  NT_SENSOR_NT80E3_TX2,               //!< QSFP+ TX line 1 power sensor
  NT_SENSOR_NT80E3_TX3,               //!< QSFP+ TX line 2 power sensor
  NT_SENSOR_NT80E3_TX4,               //!< QSFP+ TX line 3 power sensor
  NT_SENSOR_NT80E3_PORT_MAX,          //!< Number of NT80E3 port sensors
};

// The NT100E3 adapter sensor id's must match the corresponding id's for NT80E3
typedef enum NtSensorsAdapterNT100E3_e {
  // Public sensors (Level 0)
  NT_SENSOR_NT100E3_FPGA_TEMP = NT_SENSOR_NT80E3_FPGA_TEMP,               //!< FPGA temperature sensor
  NT_SENSOR_NT100E3_PCI_BRIDGE_TEMP = NT_SENSOR_NT80E3_PCI_BRIDGE_TEMP,   //!< PCI bridge temperature sensor
  NT_SENSOR_NT100E3_FAN_SPEED = NT_SENSOR_NT80E3_FAN_SPEED,               //!< FAN speed sensor
  NT_SENSOR_NT100E3_MCU_TEMP = NT_SENSOR_NT80E3_MCU_TEMP,                 //!< MCU (Micro Controller Unit) temperature sensor located inside enclosure below FAN
  NT_SENSOR_NT100E3_PSU0_TEMP = NT_SENSOR_NT80E3_PSU0_TEMP,               //!< Power supply 0 temperature sensor
  NT_SENSOR_NT100E3_PSU1_TEMP = NT_SENSOR_NT80E3_PSU1_TEMP,               //!< Power supply 1 temperature sensor
  NT_SENSOR_NT100E3_PSU2_0_TEMP = NT_SENSOR_NT80E3_PSU2_0_TEMP,           //!< Power supply 2, IC0 junction temperature sensor
  NT_SENSOR_NT100E3_PSU2_1_TEMP = NT_SENSOR_NT80E3_PSU2_1_TEMP,           //!< Power supply 2, IC1 junction temperature sensor
  NT_SENSOR_NT100E3_OSC_TEMP = NT_SENSOR_NT80E3_OSC_TEMP,                 //!< Clock oscillator temperature sensor
  NT_SENSOR_NT100E3_EXT_TEMP = NT_SENSOR_NT80E3_EXT_TEMP,                 //!< External temperature sensor located at board corner outside enclosure
  NT_SENSOR_NT100E3_PCB_TEMP = NT_SENSOR_NT80E3_PCB_TEMP,                 //!< PCB temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT100E3_NT100E3_POWER = NT_SENSOR_NT80E3_NT80E3_POWER,        //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT100E3_FPGA_POWER = NT_SENSOR_NT80E3_FPGA_POWER,             //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT100E3_DDR3_POWER = NT_SENSOR_NT80E3_DDR3_POWER,             //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT100E3_NIM_POWER = NT_SENSOR_NT80E3_NIM_POWER,               //!< NIM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT100E3_PCI_BRIDGE_POWER = NT_SENSOR_NT80E3_PCI_BRIDGE_POWER, //!< PCI bridge power consumption (calculated value) - does not generate alarms

  NT_SENSOR_NT100E3_L1_MAX,                                               //!< Number of NT100E3 level 0,1 board sensors
} NtSensorsAdapterNT100E3_t;

//The NIM temperature sensor must be the one with the lowest sensorIndex
//(enum value) in order to be shown by the monitoring tool in port mode
enum NtSensorsPortNT100E3_e {
  // Public sensors
  NT_SENSOR_NT100E3_NIM,             //!< CFP4 temperature sensor
  NT_SENSOR_NT100E3_GEARBOX_TEMP,    //!< Gearbox temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT100E3_SUPPLY,          //!< CFP4 supply voltage sensor - does not generate alarms
  NT_SENSOR_NT100E3_TX_BIAS1,        //!< CFP4 TX lane 0 bias current sensor
  NT_SENSOR_NT100E3_TX_BIAS2,        //!< CFP4 TX lane 1 bias current sensor
  NT_SENSOR_NT100E3_TX_BIAS3,        //!< CFP4 TX lane 2 bias current sensor
  NT_SENSOR_NT100E3_TX_BIAS4,        //!< CFP4 TX lane 3 bias current sensor
  NT_SENSOR_NT100E3_TX1,             //!< CFP4 TX lane 0 power sensor
  NT_SENSOR_NT100E3_TX2,             //!< CFP4 TX lane 1 power sensor
  NT_SENSOR_NT100E3_TX3,             //!< CFP4 TX lane 2 power sensor
  NT_SENSOR_NT100E3_TX4,             //!< CFP4 TX lane 3 power sensor
  NT_SENSOR_NT100E3_RX1,             //!< CFP4 RX lane 0 power sensor
  NT_SENSOR_NT100E3_RX2,             //!< CFP4 RX lane 1 power sensor
  NT_SENSOR_NT100E3_RX3,             //!< CFP4 RX lane 2 power sensor
  NT_SENSOR_NT100E3_RX4,             //!< CFP4 RX lane 3 power sensor

  NT_SENSOR_NT100E3_PORT_MAX,        //!< Number of NT100E3 port sensors
};

// The NT200E3 adapter sensor id's
typedef enum NtSensorsAdapterNT200E3_e {
  // Public sensors (Level 0)
  NT_SENSOR_NT200E3_FPGA_TEMP,         //!< FPGA temperature sensor
  NT_SENSOR_NT200E3_FAN_SPEED,         //!< FAN speed sensor
  NT_SENSOR_NT200E3_MCU_TEMP,          //!< MCU (Micro Controller Unit) temperature sensor located inside enclosure below FAN
  NT_SENSOR_NT200E3_PSU0_TEMP,         //!< Power supply 0 temperature sensor
  NT_SENSOR_NT200E3_PSU1_TEMP,         //!< Power supply 1 temperature sensor
  NT_SENSOR_NT200E3_PCB_TEMP,          //!< PCB temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT200E3_NT200E3_POWER ,    //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT200E3_FPGA_POWER ,       //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT200E3_DDR4_POWER ,       //!< DDR4 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT200E3_NIM_POWER ,        //!< NIM power consumption (calculated value) - does not generate alarms

  NT_SENSOR_NT200E3_L1_MAX,            //!< Number of NT200E3 level 0,1 board sensors
} NtSensorsAdapterNT200E3_t;

//!< The following sensors are deprecated - generic types should be used instead
//The NIM temperature sensor must be the one with the lowest sensorIndex
//(enum value) in order to be shown by the monitoring tool in port mode
enum NtSensorsPortNT200E3_2_e {
  // Public sensors
  NT_SENSOR_NT200E3_NIM,               //!< QSFP28 temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT200E3_SUPPLY,            //!< QSFP28 supply voltage sensor
  NT_SENSOR_NT200E3_TX_BIAS1,          //!< QSFP28 TX bias line 0 current sensor
  NT_SENSOR_NT200E3_TX_BIAS2,          //!< QSFP28 TX bias line 1 current sensor
  NT_SENSOR_NT200E3_TX_BIAS3,          //!< QSFP28 TX bias line 2 current sensor
  NT_SENSOR_NT200E3_TX_BIAS4,          //!< QSFP28 TX bias line 3 current sensor
  NT_SENSOR_NT200E3_RX1,               //!< QSFP28 RX line 0 power sensor
  NT_SENSOR_NT200E3_RX2,               //!< QSFP28 RX line 1 power sensor
  NT_SENSOR_NT200E3_RX3,               //!< QSFP28 RX line 2 power sensor
  NT_SENSOR_NT200E3_RX4,               //!< QSFP28 RX line 3 power sensor
  NT_SENSOR_NT200E3_TX1,               //!< QSFP28 TX line 0 power sensor
  NT_SENSOR_NT200E3_TX2,               //!< QSFP28 TX line 1 power sensor
  NT_SENSOR_NT200E3_TX3,               //!< QSFP28 TX line 2 power sensor
  NT_SENSOR_NT200E3_TX4,               //!< QSFP28 TX line 3 power sensor
  NT_SENSOR_NT200E3_PORT_MAX,          //!< Number of NT200E3 port sensors
};

// The NT200A01 adapter sensor id's
typedef enum NtSensorsAdapterNT200A01_e {
  // Public sensors (Level 0)
  NT_SENSOR_NT200A01_FPGA_TEMP,         //!< FPGA temperature sensor
  NT_SENSOR_NT200A01_FAN_SPEED,         //!< FAN speed sensor
  NT_SENSOR_NT200A01_MCU_TEMP,          //!< MCU (Micro Controller Unit) temperature sensor located inside enclosure below FAN
  NT_SENSOR_NT200A01_PSU0_TEMP,         //!< Power supply 0 temperature sensor
  NT_SENSOR_NT200A01_PCB_TEMP,          //!< PCB temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT200A01_NT200A01_POWER ,   //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT200A01_FPGA_POWER ,       //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT200A01_DDR4_POWER ,       //!< DDR4 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT200A01_NIM_POWER ,        //!< NIM power consumption (calculated value) - does not generate alarms

  NT_SENSOR_NT200A01_L1_MAX,            //!< Number of NT200A01 level 0,1 board sensors
} NtSensorsAdapterNT200A01_t;

//!< The following sensors are deprecated - generic types should be used instead
//The NIM temperature sensor must be the one with the lowest sensorIndex
//(enum value) in order to be shown by the monitoring tool in port mode
enum NtSensorsPortNT200A01_e {
  // Public sensors
  NT_SENSOR_NT200A01_NIM,               //!< QSFP28 temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT200A01_SUPPLY,            //!< QSFP28 supply voltage sensor
  NT_SENSOR_NT200A01_TX_BIAS1,          //!< QSFP28 TX bias line 0 current sensor
  NT_SENSOR_NT200A01_TX_BIAS2,          //!< QSFP28 TX bias line 1 current sensor
  NT_SENSOR_NT200A01_TX_BIAS3,          //!< QSFP28 TX bias line 2 current sensor
  NT_SENSOR_NT200A01_TX_BIAS4,          //!< QSFP28 TX bias line 3 current sensor
  NT_SENSOR_NT200A01_RX1,               //!< QSFP28 RX line 0 power sensor
  NT_SENSOR_NT200A01_RX2,               //!< QSFP28 RX line 1 power sensor
  NT_SENSOR_NT200A01_RX3,               //!< QSFP28 RX line 2 power sensor
  NT_SENSOR_NT200A01_RX4,               //!< QSFP28 RX line 3 power sensor
  NT_SENSOR_NT200A01_TX1,               //!< QSFP28 TX line 0 power sensor
  NT_SENSOR_NT200A01_TX2,               //!< QSFP28 TX line 1 power sensor
  NT_SENSOR_NT200A01_TX3,               //!< QSFP28 TX line 2 power sensor
  NT_SENSOR_NT200A01_TX4,               //!< QSFP28 TX line 3 power sensor
  NT_SENSOR_NT200A01_PORT_MAX,          //!< Number of NT200A01 port sensors
};

//!< The following sensors are deprecated - generic types should be used instead
enum NtSensorsPortNT200A01_2X25G_e {
  // Public sensors
  NT_SENSOR_NT200A01_2X25G_NIM,         //!< SFP28 temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT200A01_2X25G_SUPPLY,      //!< SFP28 supply voltage sensor
  NT_SENSOR_NT200A01_2X25G_TX_BIAS,     //!< SFP28 TX bias line 0 current sensor
  NT_SENSOR_NT200A01_2X25G_RX,          //!< SFP28 RX line 0 power sensor
  NT_SENSOR_NT200A01_2X25G_TX,          //!< SFP28 TX line 0 power sensor
  NT_SENSOR_NT200A01_2X25G_PORT_MAX,    //!< Number of NT200A01_2X25G port sensors
};



// The NT200A02 adapter sensor id's
typedef enum NtSensorsAdapterNT200A02_e {
  // Public sensors (Level 0)
  NT_SENSOR_NT200A02_FPGA_TEMP,         //!< FPGA temperature sensor
  NT_SENSOR_NT200A02_FAN_SPEED,         //!< FAN speed sensor
  NT_SENSOR_NT200A02_MCU_TEMP,          //!< MCU (Micro Controller Unit) temperature sensor located inside enclosure below FAN
  NT_SENSOR_NT200A02_PSU0_TEMP,         //!< Power supply 0 temperature sensor
  NT_SENSOR_NT200A02_PSU1_TEMP,         //!< Power supply 1 temperature sensor
  NT_SENSOR_NT200A02_PCB_TEMP,          //!< PCB temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT200A02_NT200A02_POWER ,   //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT200A02_FPGA_POWER ,       //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT200A02_DDR4_POWER ,       //!< DDR4 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT200A02_NIM_POWER ,        //!< NIM power consumption (calculated value) - does not generate alarms

  NT_SENSOR_NT200A02_L1_MAX,            //!< Number of NT200A01 level 0,1 board sensors
} NtSensorsAdapterNT200A02_t;

//!< The following sensors are deprecated - generic types should be used instead
//The NIM temperature sensor must be the one with the lowest sensorIndex
//(enum value) in order to be shown by the monitoring tool in port mode
enum NtSensorsPortNT200A02_e {
  // Public sensors
  NT_SENSOR_NT200A02_NIM,               //!< QSFP28 temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT200A02_SUPPLY,            //!< QSFP28 supply voltage sensor
  NT_SENSOR_NT200A02_TX_BIAS1,          //!< QSFP28 TX bias line 0 current sensor
  NT_SENSOR_NT200A02_TX_BIAS2,          //!< QSFP28 TX bias line 1 current sensor
  NT_SENSOR_NT200A02_TX_BIAS3,          //!< QSFP28 TX bias line 2 current sensor
  NT_SENSOR_NT200A02_TX_BIAS4,          //!< QSFP28 TX bias line 3 current sensor
  NT_SENSOR_NT200A02_RX1,               //!< QSFP28 RX line 0 power sensor
  NT_SENSOR_NT200A02_RX2,               //!< QSFP28 RX line 1 power sensor
  NT_SENSOR_NT200A02_RX3,               //!< QSFP28 RX line 2 power sensor
  NT_SENSOR_NT200A02_RX4,               //!< QSFP28 RX line 3 power sensor
  NT_SENSOR_NT200A02_TX1,               //!< QSFP28 TX line 0 power sensor
  NT_SENSOR_NT200A02_TX2,               //!< QSFP28 TX line 1 power sensor
  NT_SENSOR_NT200A02_TX3,               //!< QSFP28 TX line 2 power sensor
  NT_SENSOR_NT200A02_TX4,               //!< QSFP28 TX line 3 power sensor
  NT_SENSOR_NT200A02_PORT_MAX,          //!< Number of NT200A02 port sensors
};

// The NT40E3_AFU adapter sensor id's
typedef enum NtSensorsAdapterNT40E3_AFU_e {
  // Public sensors (Level 0)
  NT_SENSOR_NT40E3_AFU_FPGA_TEMP,      //!< FPGA temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40E3_AFU_POWER , //!< Total power consumption (calculated value) - does not generate alarms

  NT_SENSOR_NT40E3_AFU_L1_MAX,            //!< Number of NT200E3 level 0,1 board sensors
} NtSensorsAdapterNT40E3_AFU_t;

typedef enum NtPTPProfile_e {
  NT_PTP_PROFILE_DEFAULT = 0,          //!< PTP Default E2E Profile according to IEEE1588-2008
  NT_PTP_PROFILE_TELECOM,              //!< PTP Telecom Profile (ITU G.8265.1)
  NT_PTP_PROFILE_POWER,                //!< PTP Power Profile (IEEE C37.238)
  NT_PTP_PROFILE_ENTERPRISE,           //!< PTP Enterprise Profile
  NT_PTP_PROFILE_G8275_1,              //!< PTP (ITU G.8275.1)
  NT_PTP_PROFILE_COUNT
} NtPTPProfile_t;

/**
 * Host loopback position.\n
 * The available loopback positions are adapter dependent and undocumented but
 * for each adapter a default host loopback position has been defined.
 * Therefore only the following values should be used.
 */
typedef enum NtHostLoopback_e {
  NT_HOST_LOOPBACK_NONE = 0,           //!< No host loopback
  NT_HOST_LOOPBACK_DEFAULT = INT_MAX,  //!< Default host loopback.
} NtHostLoopback_t;

/**
 * Line loopback position.\n
 * The available loopback positions are adapter dependent and undocumented but
 * for each adapter a default line loopback position has been defined.
 * Therefore only the following values should be used.
 */
typedef enum NtLineLoopback_e {
  NT_LINE_LOOPBACK_NONE = 0,           //!< No line loopback
  NT_LINE_LOOPBACK_DEFAULT = INT_MAX,  //!< Default line loopback.
} NtLineLoopback_t;

/**
 * Stream-id state.
 * When a stream-id is in the active state traffic is forwarded to the stream-id by the adapter
 * When a stream-id is in the inactive state traffic is discarded by the adapter
 */
enum NtStreamIdState_e {
  NT_STREAM_ID_STATE_UNKNOWN,       //!< Unknown stream-id state
  NT_STREAM_ID_STATE_ACTIVE,        //!< Traffic is forwarded to the stream-id
  NT_STREAM_ID_STATE_INACTIVE,      //!< Traffic is dropped
};

/**
 * Feature level.
 * The feature level supported by the adapter/FPGA
 */
enum NtFeatureLevel_e {
    NT_FEATURE_LEVEL_UNKNOWN  = 0x0000, //!< Unknown feature level
    NT_FEATURE_LEVEL_S_CAP2   = 0x1002, //!< Capture level 2 for standard adapter
    NT_FEATURE_LEVEL_N_CAP12  = 0x000C, //!< Capture level 12
    NT_FEATURE_LEVEL_N_CAP12A = 0x200C, //!< Capture level 12A
    NT_FEATURE_LEVEL_N_CAP13  = 0x000D, //!< Capture level 13
    NT_FEATURE_LEVEL_N_CAP14  = 0x000E, //!< Capture level 14
    NT_FEATURE_LEVEL_N_CAP15  = 0x000F, //!< Capture level 15
    NT_FEATURE_LEVEL_N_CAP16  = 0x0010, //!< Capture level 16
    NT_FEATURE_LEVEL_S_INL2   = 0x9002, //!< In-line level 2 for standard adapter
    NT_FEATURE_LEVEL_N_INL4   = 0x8004, //!< In-line level 4
    NT_FEATURE_LEVEL_N_INL4A  = 0xA004, //!< In-line level 4A
    NT_FEATURE_LEVEL_N_INL5   = 0x8005, //!< In-line level 5
    NT_FEATURE_LEVEL_N_INL6   = 0x8006, //!< In-line level 6
    NT_FEATURE_LEVEL_N_INL7   = 0x8007, //!< In-line level 7
    NT_FEATURE_LEVEL_N_INL8   = 0x8008, //!< In-line level 8
    NT_FEATURE_LEVEL_N_ANL1   = 0x4001, //!< Analyser level 1
    NT_FEATURE_LEVEL_N_ANL2   = 0x4002, //!< Analyser level 2
    NT_FEATURE_LEVEL_N_ANL3   = 0x4003, //!< Analyser level 3
    NT_FEATURE_LEVEL_N_ANL3A  = 0xA003, //!< Analyser level 3A
    NT_FEATURE_LEVEL_N_ANL4   = 0x4004, //!< Analyser level 4
    NT_FEATURE_LEVEL_N_ANL5   = 0x4005, //!< Analyser level 5
    NT_FEATURE_LEVEL_N_ANL6   = 0x4006, //!< Analyser level 6
    NT_FEATURE_LEVEL_N_ANL7   = 0x4007, //!< Analyser level 7
    NT_FEATURE_LEVEL_N_ANL8   = 0x4008, //!< Analyser level 8
    NT_FEATURE_LEVEL_N_ANL9   = 0x4009, //!< Analyser level 9
    NT_FEATURE_LEVEL_N_ANL10  = 0x400A, //!< Analyser level 10
    NT_FEATURE_LEVEL_N_ANL11  = 0x400B, //!< Analyser level 11
    NT_FEATURE_LEVEL_N_ANL12  = 0x400C, //!< Analyser level 12
    NT_FEATURE_LEVEL_N_ANL13  = 0x400D, //!< Analyser level 13
};

#endif //__COMMONTYPES_H__
