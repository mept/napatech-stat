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
 * This is header file of the network stream interface
 */
#ifndef __STREAM_NET_H__
#define __STREAM_NET_H__

#if !defined(__NT_H__)
  #error: My interface file is 'nt.h'. Please include that via #include "nt.h" directly.
#endif

/** @addtogroup NetworkStream
 *
 * Network streams are used to receive and transmit data packets to
 * and from the adapters. They are an extension build on top of the
 * hardware-based host buffers.
 * Three types of network streams exist:
 * @li @ref StreamRx is used to receive data
 * @li @ref StreamTx is used to transmit data
 * @li @ref StreamFile is used to receive data to a file
 *
 * @note The streams are not thread safe so using the network stream API
 * must be performed without concurrent access to the stream.
 */

/** @addtogroup StreamRx
 * The RX network stream is used for both capture and in-line
 * scenarios. The capture scenarios can deliver packets either
 * packet-by-packet or as segments. The segment delivery is used for
 * store to disk scenarios followed by offline analysis via the
 * file-based network stream.
 *
 * @section PacketInterface Packet Interface
 *
 * The main interface is the packet interface. The packet interface is
 * an interface for applications to do packet-by-packet
 * processing. Please note that this approach will move some CPU load
 * from the application to the driver compared to the segment
 * interface. To open an RX network stream using the packet interface,
 * call the @ref NT_NetRxOpen function with the interface type set to
 * @ref NtNetInterface_e::NT_NET_INTERFACE_PACKET
 * "NT_NET_INTERFACE_PACKET". To receive a packet, call @ref NT_NetRxGet
 * and use the @ref PacketMacros "packet macros" to access the
 * data. When finished with the packet, call @ref NT_NetRxRelease to release
 * it again. When finished with the stream, call @ref NT_NetRxClose to close
 * it.
 *
 * For an example on how to use the packet interface see @ref
 * net/analysis/analysis_example.c "net/analysis/analysis_example.c".
 *
 * @section SegmentInterface Segment Interface
 *
 * The segment interface is only intended to be used for writing data
 * to the disc and to do this the application will have to add a file
 * header, provided by the system, to the beginning of the file. To read
 * back data from the file, the application will have to use the
 * @ref StreamFile to open the file and process the saved data packet
 * by packet. To open an RX network stream using the segment interface,
 * call the @ref NT_NetRxOpen function with the interface type set to
 * @ref NtNetInterface_e::NT_NET_INTERFACE_SEGMENT
 * "NT_NET_INTERFACE_SEGMENT". To receive a segment, call @ref NT_NetRxGet
 * and use the @ref SegmentMacros "segment macros" to access the
 * data. When finished with the segment, call @ref NT_NetRxRelease to release
 * it again. When finished with the stream, call @ref NT_NetRxClose to
 * close it.
 *
 * For an example on how to use the segment interface see @ref
 * net/capture/capture_example.c "net/capture/capture_example.c".
 *
 * @section DataSharing Data Sharing
 *
 * Data sharing is a feature that will allow multiple applications to
 * access the same shared host buffer.
 *
 * Data sharing is supported at the host buffer level. This allows
 * multiple applications to access the same host buffer, at the
 * same time, and individually decide if they want to use the packet
 * interface or the segment interface. Data sharing is zero copy but
 * will take up some extra CPU power to handle the synchronization of
 * the host buffers. The service daemon is responsible for handling the
 * host buffer exchange with the hardware and the data sharing is
 * transparent to the application.
 *
 * In-line network streams cannot be shared and any attempt to open an
 * existing in-line stream fails with an error return value.
 *
 * @note Be aware that the slowest application sets the speed. This
 * means that a packet/segment will not be returned to the hardware
 * before all applications that share the host buffer have
 * processed it. To avoid this use @ref MainDocMainFeaturesTraffic_ReceiveHb_HostBufferAllowance
 *
 * @section DataMerging Data Merging
 *
 * Data merging is used for merging data packets received from
 * multiple host buffers into one stream. This feature is used to merge
 * data from multiple ports on multiple adapters, or multiple host buffers from one
 * in-line adapter. The Napatech Software Suite supports
 * merging of data from up to 42 host buffers, making it possible to
 * merge data from 42 NT adapters. See the @ref NtplOverview "NTPL" for a
 * description on how to configure data merging.
 *
 * @note Data merging is only possible for packet streams.
 * @par
 * @note Timesynchronisation is required when merging from different adapters (see @ref MainDocMainFeaturesVirtPort_AdapterMerge).
 */

/** @addtogroup StreamTx
 * The TX network stream is used for transmitting data. Packets sent
 * via this stream will be interleaved with traffic from in-line
 * streams or other transmit streams.
 *
 * To open a TX network stream, call the @ref NT_NetTxOpen function. To
 * get an empty packet, call the @ref NT_NetTxGet function with the
 * desired length of the packet. The length includes the 4 bytes for
 * the Ethernet CRC. Now fill data into the buffer and use the
 * @ref TxMacros "TX Macros" for setting the desired time stamp, force CRC
 * generation, etc. When finished with the packet, call @ref NT_NetTxRelease
 * to release and transmit it. When finished with the stream, call @ref
 * NT_NetTxClose to close it.
 *
 * For an example on how to use the packet interface, see @ref
 * net/transmit_packet/transmit_packet_example.c "net/transmit/transmit_example.c".
 *
 * With NT3GA FPGAs Tx mode selection is an adapter global configuration - controlled by the actual FPGA image functionality and the profile ini-option.\n
 * With NT4GA FPGAs the configuration granularity has changed - Tx mode selection can be set up/configured dynamically on individual streams.\n
 * To facilitate this change - new options have been introduced into NTAPI (NT_NetTxOpen).
 *
 * Tx streams are normally "per port Tx mode" - meaning that one host buffer is allocated per (Tx) port set in the (Tx) portMask specfied to NT_NetTxOpen.
 * Each allocated host buffer will be paired to a specific Tx port and the txPort field in the standard packet descriptor will have no meaning/effect.
 *
 * Adapter-based multi-port transmit buffer mode (named after its option/flag) will allocate one host buffer per adapter that has (Tx) ports set in the (Tx) portMask specified to NetTxOpen.
 * Each host buffer allocated will be paired to a specific adapter - and that host buffer will be able to transmit on all the ports mentioned in the portMask on the adapter it is paired with.
 * The Tx port will be selected by the txPort field in each packet descriptor.
 *
 * Adapter-based multi-port transmit buffer mode is selected by a new option (called flags) that is introduced to the attributes used by NTAPI function NT_NetTxOpen_Attr().
 * The new NT_NETTX_OPEN_FLAGS_ADAPTER_MULTI_PORT_BUFFER flag/attribute is set up using NT_NetTxOpenAttrSetFlags().
 *
 * With NT4GA Test & Measurement FPGAs the following can be controlled per transmitted packet: timestamp injection, FCS calculation, Layer 3 checksum calculation and  Layer 4 checksum calculation.
 * See @ref test_and_measurement_4ga_introduction "4GA Test and Measurement features" for a detailed description.
 */

/** @addtogroup StreamFile
 * The File network stream is used for packet-by-packet offline
 * analysis of the packets captured with the segment RX interface. See
 * @ref SegmentInterface "Segment interface" for a description of how
 * to accomplish this.
 *
 * To open a file network stream, call the @ref NT_NetFileOpen with the
 * name of the captured file as argument. To get the next packet from
 * the file network stream, call the @ref NT_NetFileGet. Use the
 * @ref PacketMacros "packet macros" to access the packet data. When
 * finished with the packet, call @ref NT_NetFileRelease to release it
 * again. When finished with the stream, call @ref NT_NetFileClose to close
 * it.
 *
 * Supported files are native NT captured files, pcap and pcap-ng files.
 * When using pcap or pcap-ng files, the received port information is always
 * set to 0.
 *
 * For an example on how to use the file network stream interface, see
 * @ref net/replay/replay_example.c "net/replay/replay_example.c".
 *
 */

/**
 * The network interface types.
 * Used to select PACKET or NETWORK interface.
 */
enum NtNetInterface_e {
  NT_NET_INTERFACE_UNKNOWN=0, //!< Unknown interface
  NT_NET_INTERFACE_PACKET,    //!< Packet interface
  NT_NET_INTERFACE_SEGMENT    //!< Segment interface
};


#ifndef DOXYGEN_INTERNAL_ONLY
/**
 * Internal structures used in @ref NtNetBuf_s
 */
typedef struct NtNetBufData_s*         NtNetBufData_t;       //!< Confidential data
typedef struct NtNetBufPkt_s*          NtNetBufPkt_t;        //!< Packet data
typedef struct NtNetBufHdr_s*          NtNetBufHdr_t;        //!< Header data
#endif


/**
 * This structure is used by the @ref NetworkStream Get/Release functions and provides a handle to the returned data.
 * The layout of the structure is confidential and must only be accessed via @ref DataMacros.
 * The layout of the structure might change between major releases of NTAPI.
 */
typedef struct NtNetBuf_s {
#ifndef DOXYGEN_INTERNAL_ONLY
  int version;                     //!< The version of the NetworkData header
  NtNetBufData_t hData;            //!< A handle to confidential data
  NtNetBufPkt_t hPkt;              //!< A handle to packet data
  NtNetBufHdr_t hHdr;              //!< A handle to header data
  uint64_t length;                 //!< Data field length
  enum NtNetInterface_e netIf;     //!< The network interface
  enum NtTimestampType_e tsType;   //!< The time stamp type
#endif
  uint8_t portOffset;              //!< The port offset - used to identify logical ports
#ifndef DOXYGEN_INTERNAL_ONLY
  uint8_t Reserved1[3];
  uint8_t adapterNo;               //!< The adapter from which the data originated
  uint8_t Reserved2[3];
  int8_t egressPort;              //!< The destination port (in-line)
  uint8_t Reserved3[3];
  uint8_t* colorMap;               //!< The filter color map table
#define _FEED2STREAM_SHL_ 4
  int* streamInfo;            //!< A pointer to indexed stream IDs - used by macros
  uint32_t pkts;
#endif
  uintptr_t arg0;                  //!< User specific meta data container 0
  uintptr_t arg1;                  //!< User specific meta data container 1
  uintptr_t arg2;                  //!< User specific meta data container 2
} *NtNetBuf_t;

/** @addtogroup StreamRx
 *@{
 */

/**
 * Possible NetRx stream commands
 */
enum NtNetRxCmd_e {
  NT_NETRX_READ_CMD_UNKNOWN=0,           //!< Unknown read command
  NT_NETRX_READ_CMD_GET_FILE_HEADER,     //!< Gets the file header for the stream
  NT_NETRX_READ_CMD_STREAM_DROP,         //!< Returns the drop counters for each stream - the counters increment when packets are dropped because of the host buffer allowance (hysteresis) being activated
  NT_NETRX_READ_CMD_STREAM_TIME,         //!< Returns the current stream time
  NT_NETRX_READ_CMD_PCAP_FCS,            //!< Returns whether packets with pcap descriptors include ethernet FCS
  NT_NETRX_READ_CMD_GET_RING_CONTROL,    //!< Return control of the host buffer ring of a stream Dangerous!! (Napatech internal use only - may change without further notice)
  NT_NETRX_READ_CMD_GET_HB_INFO          //!< Gets the info on the host buffers used by the stream
};

/**
 * TX stream descriptor modes.
 * Used for configuring required variables for TX.
 */
enum NtNetTxDescriptorMode_e {
  NT_NETTX_DESCRIPTOR_MODE_STD,   //!< TX with standard descriptors
  NT_NETTX_DESCRIPTOR_MODE_DYN1,  //!< TX with DYN1 descriptors
  NT_NETTX_DESCRIPTOR_MODE_DYN2,  //!< TX with DYN2 descriptors
  NT_NETTX_DESCRIPTOR_MODE_DYN3,  //!< TX with DYN3 descriptors
  NT_NETTX_DESCRIPTOR_MODE_DYN4,  //!< TX with DYN4 descriptors
};

/**
 *  File header return structure.
 *  Note: This header can only be read when all NTPL assignments have completed.
 */
struct NtNetRxFileHeader_s {
  uint8_t data[128]; //!< The actual file header
  int32_t size;      //!< The size of the file header
};

/**
 * Stream drop counter return structure
 */
struct NtNetRxStreamDrop_s {
  uint64_t pktsDropped;   //!< Packets dropped because the application is affected by the host buffer allowance (hysteresis)
  uint64_t octetsDropped; //!< Bytes dropped because the application is affected by the host buffer allowance (hysteresis)
};

/**
 * Stream time
 */
struct NtNetRxStreamTime_s {
  uint64_t ts;   //!< Current stream time. Can be used when NT_NetRxGet() returns timeout to get the time of the stream.
};

/**
 * PCAP information
 */
struct NtNetRxPcapInfo_s {
  uint32_t fcs;   //!< Returns non-zero if FCS is included in packets with PCAP descriptors.
};

/**
 * Expose buffer info to the user (Napatech internal use only - may change without further notice)
 */
struct NtNetRxHbRing_s {
  volatile uint64_t* pRead;
  volatile uint64_t* pWrite;
  uint8_t* ring;
  uint64_t size;
  uint64_t mask;
};

/**
 *  RX Host buffer info
 */
struct NtNetRxHbInfo_s {
  uint32_t numAddedHostBuffers;    //!< The number of host buffers added by the driver
  uint32_t numAssignedHostBuffers; //!< The number of host buffers assigned and also the depth of the array
  struct NtNetRxHb_s {
    uint64_t timestamp;   //!< The current host buffer time
    size_t size;          //!< The size of the host buffer (4GA only)
    size_t available;     //!< Amount of the host buffer available to the adapter (4GA only)
    size_t dequeued;      //!< Reserved for future use
    size_t pending;       //!< Amount of the host buffer pending for the application to read (4GA only)
    size_t inlinePending; //!< Reserved for future use
    enum NtNetHostBufferLayout_e layout; //!< The host buffer layout
    int index;          //!< The host buffer index. Unique throughout the system
  } aHostBuffer[128];
};

/**
 * NetRx structure. Network RX data is read via this structure via @ref NT_NetRxRead().
 */
typedef struct NtNetRx_s {
  enum NtNetRxCmd_e cmd; //!< The read command - specified what to read from NetRx
  /**
   *  Union of all possible return structures from NetRxRead()
  */
  union NtNetRx_u {
    struct NtNetRxFileHeader_s fileheader;  //!< The structure to use for @ref NtNetRx_s::cmd==NT_NETRX_READ_CMD_GET_FILE_HEADER
    struct NtNetRxStreamDrop_s streamDrop;  //!< The structure to use for @ref NtNetRx_s::cmd==NT_NETRX_READ_CMD_STREAM_DROP
    struct NtNetRxStreamTime_s streamTime;  //!< The structure to use for @ref NtNetRx_s::cmd==NT_NETRX_READ_CMD_STREAM_TIME
    struct NtNetRxPcapInfo_s   pcap;        //!< The structure to use for @ref NtNetRx_s::cmd==NT_NETRX_READ_CMD_PCAP_INFO
    struct NtNetRxHbRing_s ringControl;     //!< The structure to use for @ref NtNetRx_s::cmd==NT_NETRX_READ_CMD_GET_RING_CONTROL
    struct NtNetRxHbInfo_s hbInfo;          //!< The structure to use for @ref NtNetRx_s::cmd==NT_NETRX_READ_CMD_GET_HB_INFO
  } u ;
} NtNetRx_t;

/**
 * Possible NetTx stream commands
 */
enum NtNetTxCmd_e {
  NT_NETTX_READ_CMD_UNKNOWN=0,           //!< Unknown read command
  NT_NETTX_READ_CMD_GET_HB_INFO,         //!< Gets the info on the host buffers used by the stream
  NT_NETTX_READ_CMD_GET_RING_CONTROL,    //!< Get the control of the host buffer ring. Dangerous!! (Napatech internal use only - may change without further notice)
};

/**
 *  TX Host buffer info
 */
struct NtNetTxHbInfo_s {
  unsigned int numHostBuffers; //!< The number of host buffers used by the stream and also the depth of the array
  struct NtNetTxHb_s {
    size_t size;         //!< The size of the host buffer
    size_t available;    //!< Amount of the host buffer available to the application
    size_t dequeued;     //!< Amount of the host buffer dequeued by the application
    size_t released;     //!< Amount of the host buffer released waiting to be transmitted
    enum NtNetHostBufferLayout_e layout; //!< The host buffer layout
    int    index;        //!< The host buffer index. Unique throughout the system.
    uint64_t portMask;   //!< The port-mask the host buffer can utilize
  } aHostBuffer[128];
};

/**
 * Expose host buffer info (Napatech internal use only - may change without further notice)
 */
struct NtNetTxHbRing_s {
  volatile uint64_t* pRead;
  volatile uint64_t* pWrite;
  uint8_t* ring;
  uint64_t size;
  uint16_t minTxPktSize;         //!< The min transmit packet size of this port
  uint16_t maxTxPktSize;         //!< The max transmit packet size of this port
  uint8_t port;                  //!< The port this ring is attached to
  //TODO: Maybe expose what descriptors can be used?
};

/**
 * NetTx structure. Network TX data is read via this structure via @ref NT_NetTxRead().
 */
typedef struct NtNetTx_s {
  enum NtNetTxCmd_e cmd; //!< The read command - specified what to read from NetTx
  /**
   *  Union of all possible return structures from NetTxRead()
  */
  union NtNetTx_u {
      struct NtNetTxHbInfo_s hbInfo; //!< Information about the host buffers used
      struct NtNetTxHbRing_s ringControl; //!< Control of the host buffer ring (Napatech internal use only - may change without further notice)
  } u ;
} NtNetTx_t;


/**
 *  NtNetTxFragment structure. A TX packet may be scattered in a list of fragments,
 *  which is put together and added to the TX hostbuffer via @ref NT_NetTxAddPacket().
 */
typedef struct NtNetTxFragment_s
{
  uint8_t* data;
  uint16_t size;
} NtNetTxFragment_t;

/**
 * Possible NetFileRead commands
 */
enum NtNetFileReadCmd_e {
  NT_NETFILE_READ_INFO_UNKNOWN_CMD=0,       //!< Unknown read command
  NT_NETFILE_READ_COMPAT_0,                 //!< Read information about the NetFile stream
  NT_NETFILE_READ_FILETYPE_CMD,             //!< Read information about the opened file type
  NT_NETFILE_READ_DESCRIPTOR_CMD,           //!< Read information about the descriptor and timestamp format used
  NT_NETFILE_READ_INFO_CMD_V1,              //!< Read information about the NetFile stream
};

/**
 *  NetFile stream Info return structure
 */

typedef struct NtNetFileReadInfo_v1_s {
  uint64_t lastTimestamp;   //!< The time stamp in the last packet in last segment read using the function @ref NT_NetFileGet
  uint64_t numberOfOctets;  //!< Number of octets read from Netfile so far
  uint32_t numberOfPackets; //!< Number of packets read from Netfile so far
  uint64_t firstTimestamp;  //!< The time stamp in the first packet in first segment read using the function @ref NT_NetFileGet
} NtNetFileInfo_v1_t;

typedef enum {
  NT_NETFILE_TYPE_UNKNOWN,  //!< The opened file is a unknown
  NT_NETFILE_TYPE_NT,       //!< The opened file is a Napatech capture file
  NT_NETFILE_TYPE_PCAP,     //!< The opened file is a PCAP capture file
  NT_NETFILE_TYPE_PCAP_NG,  //!< The opened file is a PCAP NG capture file
} NtNetFileType_e;

typedef struct NtNetFileReadDesc_s
{
  enum NtTimestampType_e tsType;       //!< Timestamp format used in packet data
  enum NtPacketDescriptorType_e desc;  //!< Descriptor used in packet data
} NtNetFileReadDesc_t;

/* Include commands for backward compatibility */
#if !defined(_NT_NTAPI_NO_COMPAT)
#include "stream_net_compat.h"
#endif

/**
 * NetFileRead stream structure - network File data is read via this structure via @ref NT_NetFileRead()
 */
typedef struct NtNetFileRead_s {
  enum NtNetFileReadCmd_e cmd; //!< The read command - specified what to read from NetFile
  /**
   *  Union of all possible return structures from NT_NetFileRead()
  */
  union NtNetFileRead_u {
    struct NtNetFileReadInfo_v1_s info_v1; //!< Information about the NetFile. Used by NT_NETFILE_READ_INFO_CMD
    struct NtNetFileReadDesc_s desc;       //!< Information about the descriptor and timestamp format used. Used by NT_NETFILE_READ_DESCRIPTOR_CMD
    NtNetFileType_e fileType;              //!< Information about the type of the opened file
#if !defined(_NT_NTAPI_NO_COMPAT)
    /* Commands for backward compatibility */
    struct NtNetFileReadInfo_s info; //!< Information about the NetFile. Used by NT_NETFILE_READ_INFO_CMD
#endif
  } u ;
} NtNetFileRead_t;

/**
 * The Network RX stream handle - used for both in-line and capture streams
 */
typedef struct NtNetStreamRx_s* NtNetStreamRx_t;

/**
 * Parameter structure for NT_NetRxOpen_Attr/NT_NetRxOpen_v3/NT_NetRxOpenMulti_v3.
 * Use NT_NetRxOpenAttrInit() and NT_NetRxOpenAttrSet*() functions to define content.
 */
#define __SIZEOF_NT_NETRX_ATTR (128)
union __nt_netrx_attr {
  char __size[__SIZEOF_NT_NETRX_ATTR];
  long int __align;
};
typedef union __nt_netrx_attr NtNetRxAttr_t;

/**
 * Parameter structure for NT_NetTxOpen_Attr/NT_NetTxOpen_v3/NT_NetTxOpenMulti_v3.
 * Use NT_NetTxOpenAttrInit() and NT_NetTxOpenAttrSet*() functions to define content.
 */
#define __SIZEOF_NT_NETTX_ATTR (128)
union __nt_nettx_attr {
  char __size[__SIZEOF_NT_NETTX_ATTR];
  long int __align;
};
typedef union __nt_nettx_attr NtNetTxAttr_t;

/**
 * Parameter structure for NT_NetFileOpen_Attr.
 * Use NT_NetFileOpenAttrInit() and NT_NetFileOpenAttrSet*()
 * functions to define content.
 */
#define __SIZEOF_NT_NETFILE_ATTR (128)
union __nt_netfile_attr {
  char __size[__SIZEOF_NT_NETFILE_ATTR];
  long int __align;
};
typedef union __nt_netfile_attr NtNetFileAttr_t;

/**
 * Flags for NT_NetRxOpen_v2+/NT_NetRxOpenMulti_v2+
 *
 * Obsolete: please use enum NtNetRxOpenFlags_e below
 */
#define NT_NETRX_NONE (0)
#define NT_NETRX_READONLY_STREAM (1LL<<0)

/**
 *
 */
enum NtNetRxOpenFlags_e {
  NT_NETRX_OPEN_FLAGS_NONE=0,
  NT_NETRX_OPEN_FLAGS_READONLY_STREAM=1LL<<0,
};

/**
 * @brief Opens in-line or capture host buffer(s) and returns a NtNetStreamRx_t handle
 *
 * This function is called to retrieve a handle to an in-line or capture network stream.
 *
 * In-line network streams cannot be shared and any attempt to open an existing in-line stream fails with an error return value.
 *
 * @note It is important to start calling NT_NetRxGet() and NT_NetRxRelease() soon
 * after this call to avoid packet drop. Host buffers are assigned/released to the streamid within
 * NT_NetRxGet() and NT_NetRxRelease().
 *
 * @param[out] hStream                    Reference to a NtNetStreamRx_t stream pointer
 * @param[in]  name                       Stream friendly name - used in, for example, logging statements
 * @param[in]  netIntf                    Interface type - segment or packet
 * @param[in]  streamId                   The network stream ID to open - can be opened a number of times which will cause sharing of the host buffers in the streamId
 * @param[in]  hostBufferAllowance        Drop level for the host buffer allowance (hysteresis), -1 means disabled
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetRxOpen(NtNetStreamRx_t* hStream, const char* name, enum NtNetInterface_e netIntf, uint32_t streamId, int hostBufferAllowance);

/**
 * @brief Opens in-line or capture host buffer(s) and returns a NtNetStreamRx_t handle
 *
 * This function is called to retrieve a handle to an in-line or capture network stream with flags.
 *
 * In-line network streams cannot be shared and any attempt to open an existing in-line stream fails with an error return value.
 *
 * @note It is important to start calling NT_NetRxGet() and NT_NetRxRelease() soon
 * after this call to avoid packet drop. Host buffers are assigned/released to the streamid within
 * NT_NetRxGet() and NT_NetRxRelease().
 *
 * The flags shall be either NT_NETRX_OPEN_FLAGS_NONE or the bitwise-inclusive OR of one or more of the other
 * flags in the following table:
 *
 * Flag                                | Description
 * ------------------------------------|-------------
 * NT_NETRX_OPEN_FLAGS_NONE            | No flags set, equivalent to passing '0' as flag.
 * NT_NETRX_OPEN_FLAGS_READONLY_STREAM | Using this option will cause a write to data returned by NT_NetRxGet to fail with a segmentation fault.
 *
 * @param[out] hStream                    Reference to a NtNetStreamRx_t stream pointer
 * @param[in]  name                       Stream friendly name - used in, for example, logging statements
 * @param[in]  netIntf                    Interface type - segment or packet
 * @param[in]  streamId                   The network stream ID to open - can be opened a number of times which will cause sharing of the host buffers in the streamId
 * @param[in]  hostBufferAllowance        Drop level for the host buffer allowance (hysteresis), -1 means disabled
 * @param[in]  flags                      Flags for the stream OR'd together, or zero for no flags.
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetRxOpen_v2(NtNetStreamRx_t* hStream, const char* name, enum NtNetInterface_e netIntf, uint32_t streamId, int hostBufferAllowance, int flags);

/**
 * @brief Initialize RX stream attributes
 *
 * The attributes are initialized to the following default values: \n
 *    name                = NULL \n
 *    netIntf             = NT_NET_INTERFACE_UNKNOWN \n
 *    hostBufferAllowance = -1 \n
 *    flags               = NT_NETRX_OPEN_FLAGS_NONE \n
 *
 * @param[out] attr                       Pointer to the attributes structure
 */
void NT_NetRxOpenAttrInit(NtNetRxAttr_t* attr);

/**
 * @brief Sets the stream name attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] name                        Stream friendly name - used in, for example, logging statements
 */
void NT_NetRxOpenAttrSetName(NtNetRxAttr_t* attr, const char* name);

/**
 * @brief Returns the name attribute
 * @return The name attribute
 */
const char* NT_NetRxOpenAttrGetName(const NtNetRxAttr_t* attr);

/**
 * @brief Sets the interface type attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] netIntf                     Interface type - segment or packet
 */
void NT_NetRxOpenAttrSetNetIntf(NtNetRxAttr_t* attr, enum NtNetInterface_e netIntf);

/**
 * @brief Returns the interface type attribute
 * @return The interface type attribute
 */
enum NtNetInterface_e NT_NetRxOpenAttrGetNetIntf(const NtNetRxAttr_t* attr);

/**
 * @brief Sets the host buffer allowance attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] hostBufferAllowance         Drop level for the host buffer allowance (hysteresis), -1 means disabled
 */
void NT_NetRxOpenAttrSetHostBufferAllowance(NtNetRxAttr_t* attr, int hostBufferAllowance);

/**
 * @brief Returns the buffer allowance attribute
 * @return The buffer allowance attribute
 */
int NT_NetRxOpenAttrGetHostBufferAllowance(const NtNetRxAttr_t* attr);

/**
 * @brief Sets the flags attribute
 *
 * The flags shall be either NT_NETRX_NONE or the bitwise-inclusive OR of one or more of the other
 * flags in the following table - see enum ::NtNetRxOpenFlags_e
 *
 * Flag                     | Description
 * -------------------------|-------------
 * NT_NETRX_NONE            | No flags set, equivalent to passing '0' as flag.
 * NT_NETRX_READONLY_STREAM | Using this option will cause a write to data returned by NT_NetRxGet to fail with a segmentation fault.
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] flags                       Drop level for the host buffer allowance (hysteresis), -1 means disabled
 */
void NT_NetRxOpenAttrSetFlags(NtNetRxAttr_t* attr, int flags);

/**
 * @brief Returns the flags attribute
 * @return The flags attribute - see enum ::NtNetRxOpenFlags_e
 */
int NT_NetRxOpenAttrGetFlags(const NtNetRxAttr_t* attr);

/**
 * @brief Opens in-line or capture host buffer(s) and returns a NtNetStreamRx_t handle
 *
 * This function is called to retrieve a handle to an in-line or capture network stream with flags.
 * @note It is important to start calling NT_NetRxGet() and NT_NetRxRelease() soon
 * after this call to avoid packet drop. Host buffers are assigned/released to the streamid within
 * NT_NetRxGet() and NT_NetRxRelease().
 *
 * @param[out] hStream                    Reference to a NtNetStreamRx_t stream pointer
 * @param[in]  streamId                   The network stream ID to open - can be opened a number of times which will cause sharing of the host buffers in the streamId
 * @param[in]  attr                       Attributes of the stream
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetRxOpen_Attr(NtNetStreamRx_t* hStream, uint32_t streamId, const NtNetRxAttr_t* attr);

/**
 * @brief Opens in-line or capture host buffer(s) and returns a NtNetStreamRx_t handle
 *
 * This function is called to retrieve a handle to an in-line or capture network streams. If
 * multiple stream-ids are opened the data from them will be time stamp merged. Note multiple
 * stream-ids can only be used with the packet interface.
 * @note It is important to start calling NT_NetRxGet() and NT_NetRxRelease() soon
 * after this call to avoid packet drop. Host buffers are assigned/released to the streamid within
 * NT_NetRxGet() and NT_NetRxRelease().
 *
 * @param[out] hStream                    Reference to a NtNetStreamRx_t stream pointer
 * @param[in]  name                       Stream friendly name - used in, for example, logging statements
 * @param[in]  netIntf                    Interface type - Can only be packet if multiple are opened
 * @param[in]  paStreamId                 Array containing the network stream IDs to open. A maximum of 8 streams can be specified.
 * @param[in]  numStreamIds               The number of stream-ids in the paStreamId array
 * @param[in]  hostBufferAllowance        Drop level for the host buffer allowance (hysteresis), -1 means disabled
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetRxOpenMulti(NtNetStreamRx_t* hStream, const char* name, enum NtNetInterface_e netIntf, uint32_t* paStreamId, unsigned int numStreamIds, int hostBufferAllowance);

/**
 * @brief Opens in-line or capture host buffer(s) and returns a NtNetStreamRx_t handle
 *
 * This function is called to retrieve a handle to an in-line or capture network streams with flags.
 * If multiple stream-ids are opened the data from them will be time stamp merged. Note multiple
 * stream-ids can only be used with the packet interface.
 * @note It is important to start calling NT_NetRxGet() and NT_NetRxRelease() soon
 * after this call to avoid packet drop. Host buffers are assigned/released to the streamid within
 * NT_NetRxGet() and NT_NetRxRelease().
 *
 * The flags shall be either NT_NETRX_NONE or the bitwise-inclusive OR of one or more of the other
 * flags in the following table (see enum ::NtNetRxOpenFlags_e):
 *
 * Flag                     | Description
 * -------------------------|-------------
 * NT_NETRX_NONE            | No flags set, equivalent to passing '0' as flag.
 * NT_NETRX_READONLY_STREAM | Using this option will cause a write to data returned by NT_NetRxGet to fail with a segmentation fault.
 *
 * @param[out] hStream                    Reference to a NtNetStreamRx_t stream pointer
 * @param[in]  name                       Stream friendly name - used in, for example, logging statements
 * @param[in]  netIntf                    Interface type - Can only be packet if multiple are opened
 * @param[in]  paStreamId                 Array containing the network stream IDs to open. A maximum of 8 streams can be specified.
 * @param[in]  numStreamIds               The number of stream-ids in the paStreamId array
 * @param[in]  hostBufferAllowance        Drop level for the host buffer allowancei (hysteresis), -1 means disabled
 * @param[in]  flags                      Flags for the stream OR'd together, or zero for no flags.
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetRxOpenMulti_v2(NtNetStreamRx_t* hStream, const char* name, enum NtNetInterface_e netIntf, uint32_t* paStreamId, unsigned int numStreamIds, int hostBufferAllowance, int flags);

/**
 * @brief Opens in-line or capture host buffer(s) and returns a NtNetStreamRx_t handle
 *
 * This function is called to retrieve a handle to an in-line or capture network streams with flags.
 * If multiple stream-ids are opened the data from them will be time stamp merged. Note multiple
 * stream-ids can only be used with the packet interface.
 * @note It is important to start calling NT_NetRxGet() and NT_NetRxRelease() soon
 * after this call to avoid packet drop. Host buffers are assigned/released to the streamid within
 * NT_NetRxGet() and NT_NetRxRelease().
 *
 * @param[out] hStream                    Reference to a NtNetStreamRx_t stream pointer
 * @param[in]  paStreamId                 Array containing the network stream IDs to open. A maximum of 8 streams can be specified.
 * @param[in]  numStreamIds               The number of stream-ids in the paStreamId array
 * @param[in]  attr                       Attributes of the stream(s)
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetRxOpenMulti_Attr(NtNetStreamRx_t* hStream, uint32_t* paStreamId, unsigned int numStreamIds, const NtNetRxAttr_t* attr);

/**
 * @brief Gets data from an in-line or capture stream
 *
 * This function is called to retrieve packets/segments from a in-line or capture stream.
 *
 * The calling process is suspended when no data is immediately available.
 * The suspension is done in one of two ways, depending on the system clock resolution:

 *   1) If the system clock resolution is <= 1 uSec, sleep calls are used. The timeout value
 *      is divided into sleep intervals (with intervals approximating the segment timeout on the adapter).
 *      It then periodically polls for data.

 *   2) using events. If the system cannot do uSec sleeps, then the suspension mechanism used is event
 *      based. It puts the calling process to sleep waiting for an event. On data receival an event is sent
 *      and the process is woken up.
 *
 * @param[in]    hStream     Network RX stream handle
 * @param[out]   netBuf      Segment/packet container reference, is set to NULL if return value is not NT_SUCCESS
 * @param[in]    timeout     The timeout in milliseconds. The call will return when any data is available, or when the timeout is reached.
 *                           A timeout of -1 will wait indefinitely if using the packet mode. In segment mode the waiting is always capped
 *                           to the next HostBufferPollInterval (ntservice.ini), which is 100 usecs by default, at which point an empty
 *                           segment is returned, if no data arrived. So in segment mode, any timeout larger than HostBufferPollInterval
 *                           (including -1) has no effect.
 *
 * @note This function has no mutex protection, therefore the same hStream cannot be used by multiple threads
 * @note When the segment interface is used this function can return empty segments only containing a time stamp update, hence if NT_NET_GET_SEGMENT_LENGTH() return 0 only NT_NET_GET_SEGMENT_TIMESTAMP() can be used.
 * The time stamp update will make it possible for users to merge packets in segments from different stream ids.
 *
 * @retval  NT_SUCCESS          Data has been returned and must be released again via NT_NetRxRelease()
 * @retval  NT_STATUS_TIMEOUT   No data has been returned and a timeout has occured
 * @retval  NT_STATUS_TRYAGAIN  The resource is temporarily unavailable because of reconfiguration - call NT_NetRxGet() again
 * @retval  Error               Use @ref NT_ExplainError for an error description
 */
int NT_NetRxGet(NtNetStreamRx_t hStream, NtNetBuf_t* netBuf, int timeout);

/**
 * @brief Gets data from an in-line or capture stream
 *
 * This function is called to retrieve packets from a in-line or capture stream. The function will
 * automatically release the previous packet when called, hence it is not possible to keep packets and if necessary
 * the packets must be copied to a safe buffer before calling the function to get the next packet.
 *
 * @param[in]    hStream     Network RX stream handle
 * @param[out]   netBuf      Segment/packet container reference, is set to NULL if return value is not NT_SUCCESS
 * @param[in]    timeout     The timeout in milliseconds. The call will return when this timeout is reached unless data is available. A timeout of -1 will wait indefinitely for a new buffer.
 *
 * @note This function has no mutex protection, therefore the same hStream cannot be used by multiple threads
 *
 * @retval  NT_SUCCESS          Data has been returned and will be valid until the next @ref NT_NetRxGetNextPacket() call
 * @retval  NT_STATUS_TIMEOUT   No data has been returned and a timeout has occured
 * @retval  NT_STATUS_TRYAGAIN  The resource is temporarily unavailable because of reconfiguration - call NT_NetRxGetNextPacket() again
 * @retval  Error               Use @ref NT_ExplainError for an error description
 */
int NT_NetRxGetNextPacket(NtNetStreamRx_t hStream, NtNetBuf_t* netBuf, int timeout);

/**
 * @brief Reads data from the stream
 *
 * This function will read on-line generated data from the stream, for example, a file header
 *
 * @param[in] hStream  NetRx stream handle
 * @param[in] cmd      NetRx read structure
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetRxRead(NtNetStreamRx_t hStream, NtNetRx_t* cmd);


/**
 * @brief Releases network buffer
 *
 * This function will release the netBuf data obtained via NT_NetRxGet(). The data within
 * netBuf will on an in-line profile be sent to the adapter upon release even in the case where
 * the NTPL assignment has been terminated.
 *
 * @note This function has no mutex protection, therefore the same hStream cannot be used by multiple threads
 *
 * @param[in] hStream NetRx stream handle
 * @param[in] netBuf  Net buffer received via NT_NetRxGet()
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetRxRelease(NtNetStreamRx_t hStream, NtNetBuf_t netBuf);

/**
 * @brief Closes an in-line or capture stream
 *
 * This function is called to close an in-line or capture stream
 *
 * @param[in] hStream  In-line or capture stream handle to close
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetRxClose(NtNetStreamRx_t hStream);

/** @} */


/** @addtogroup StreamTx
 *@{
 */
/**
 * Network TX stream handle - used for TX streams
 */
typedef struct NtNetStreamTx_s* NtNetStreamTx_t;

/**
 * Network TX packet options
 */
enum NtNetTxPacketOption_e {
  NT_NETTX_PACKET_OPTION_UNKNOWN=0,                         //!< Unknown option
  NT_NETTX_PACKET_OPTION_DEFAULT,                           //!< Gets a TX buffer with a pre-configured packet descriptor. Use this option to transmit L2 data. This option uses packetSize as wire length.
  NT_NETTX_PACKET_OPTION_L2=NT_NETTX_PACKET_OPTION_DEFAULT, //!< Same as default
  NT_NETTX_PACKET_OPTION_RAW,                               //!< Gets a raw TX packet buffer without packet descriptor. Care needs to be taken when using this option. Use this option in replay scenarios where packets already have a correct descriptor, e.g. data recorded using @ref StreamFile. Uses packetSize as the stored length. With this option packetSize must be a multiple of 8 (NT3GA only).
  NT_NETTX_SEGMENT_OPTION_RAW,                              //!< Gets a raw TX segment buffer. Care needs to be taken when using this option. Use this option in replay scenarios where the segment length is known prior to calling @ref NT_NetTxGet. Use packetSize as the segment length. The port parameter in @ref NT_NetTxGet is used to control that the segment returned belongs to the adapter on which the port resides. It is required that the txPort in the packet descriptors within the segment are set before releasing the segment. If the host buffer layout is NT_NET_HOSTBUFFER_LAYOUT_SLABS, the slabs are automatically terminated when this option is used.
  NT_NETTX_PACKET_OPTION_DYN,                               //!< Gets a TX buffer with a pre-configured dynamic packet descriptor. Use this option to transmit L2 data. This option uses packetSize as wire length. Set DescriptorMode before using this option.
};

/**
 * Network TX NUMA HB options for NUMA-parameter in NT_NetTxOpen()
 */
enum NtNetTxOpenNumaOption_e {
  NT_NETTX_NUMA_ANY_HB=0xFFFFFFFE,                          //!< (=-2) Allocate TX host buffer from any TX host buffer pool
  NT_NETTX_NUMA_ADAPTER_HB=0xFFFFFFFF,                      //!< (=-1) Allocate TX host buffer from TX-host buffer pool on that NUMA node where the adapter of the TX-port is located
};

/**
 * Flags for NT_NetTxOpen_Attr()
 */
enum NtNetTxOpenFlags_e {
  NT_NETTX_OPEN_NONE=0,                                    //!< No NtNetTxOpen flags (Obsolete)
  NT_NETTX_OPEN_FLAGS_NONE=0,                              //!< No NtNetTxOpen flags
  NT_NETTX_OPEN_FLAGS_ADAPTER_MULTI_PORT_BUFFER=(1LL<<0),  //!< Allocate one TX host buffer per adapter that has ports set in NT_NetTXOpen portmask - if unset allocate one TX host buffer per port that is set in NT_NetTXOpen portmask
};

/**
 * @brief Opens a TX host buffer and returns a NtNetStreamTx_t handle
 *
 * This function, which is superseded by NT_NetTxOpen_v3(), is called
 * to retrieve a TX stream handle.
 *
 * Note that the TX stream on capture-only adapters (NT4E Capture, NT4E_STD Capture and NT20E Capture)
 * will have very limited transmit capabilities. They will not be able to transmit at line rate
 * and their transmit sizes and statistics will also be limited. Packets larger than 2000 bytes
 * will sliced to the size of 2000 bytes.
 *
 * @param[out] hStream    Reference to a NtNetStreamTx_t stream pointer
 * @param[in]  name       Stream friendly name - used in, for example, logging statements
 * @param[in]  portMask   Bitmask for ports this stream will use for transmitting
 * @param[in]  NUMA       NUMA node on which the host buffer is be located (NOTE: Special options in NtNetTxOpenNumaOption_e)
 * @param[in] minHostBufferSize Minimum size of host buffer needed in <em>MBytes</em>. The
 *                              smallest host buffer found that is larger or equal to minHostBufferSize
 *                              is used and the size of the host buffer is set to minHostBufferSize. If
 *                              set to 0, the first host buffer found is used regardsless of the size.
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpen(NtNetStreamTx_t* hStream, const char* name, uint64_t portMask, uint32_t NUMA, uint32_t minHostBufferSize);

/**
 * @brief Opens a TX host buffer and returns a NtNetStreamTx_t handle (extended version)
 *
 * This function, which is superseded by NT_NetTxOpen_v3(), is similar
 * to the NT_NetTxOpen() function. The main difference is that it has
 * two additional parameters, the descriptor type and the timestamp
 * format.
 *
 * This function will only work with 4GA adapters.
 *
 * @param[out] hStream    Reference to a NtNetStreamTx_t stream pointer
 * @param[in]  name       Stream friendly name - used in, for example, logging statements
 * @param[in]  portMask   Bitmask for ports this stream will use for transmitting
 * @param[in]  NUMA       NUMA node on which the host buffer is be located (NOTE: Special options in NtNetTxOpenNumaOption_e)
 * @param[in] minHostBufferSize Minimum size of host buffer needed in <em>MBytes</em>. The smallest host
 *                              buffer found that is larger or equal to minHostBufferSize is used and the
 *                              size of the host buffer is set to minHostBufferSize. If set to 0, the
 *                              first host buffer found is used regardsless of the size.
 * @param[in]  descriptor Descriptor type to use when transmitting.
 * @param[in]  ts         Timestamp format to use when transmitting.
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpen_v2(NtNetStreamTx_t* hStream, const char* name, uint64_t portMask, uint32_t NUMA, uint32_t minHostBufferSize, enum NtPacketDescriptorType_e descriptor, enum NtTimestampType_e ts);

/**
 * @brief Opens a TX host buffer and returns a NtNetStreamTx_t handle (extended version)
 *
 * This function is similar to the NT_NetTxOpen_v2() function. The
 * main difference is that the minimum hostbuffer size is specified in
 * bytes to support a hostbuffer size less than one megabyte.
 *
 * This function will only work with 4GA adapters.
 *
 * @param[out] hStream    Reference to a NtNetStreamTx_t stream pointer
 * @param[in]  name       Stream friendly name - used in, for example, logging statements
 * @param[in]  portMask   Bitmask for ports this stream will use for transmitting
 * @param[in]  NUMA       NUMA node on which the host buffer is be located (NOTE: Special options in NtNetTxOpenNumaOption_e)
 * @param[in] minHostBufferSize Minimum size of host buffer needed in <em>bytes</em>. The smallest host
 *                              buffer found that is larger or equal to minHostBufferSize is used and the
 *                              size of the host buffer is set to minHostBufferSize. If set to 0, the
 *                              first host buffer found is used regardsless of the size.
 * @param[in]  descriptor Descriptor type to use when transmitting.
 * @param[in]  ts         Timestamp format to use when transmitting.
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 *
 * NOTE:
 * When using NT_NetTxOpen() >= 3: ntservice ini-option System.NtapiNetTxSegmentRawAlignMode can be used to control NT_NetTxGet()/NT_NetTxRelease() behaviour for NT_NETTX_SEGMENT_OPTION_RAW  mode.
 * System.NtapiNetTxSegmentRawAlignMode = 1 will retain previous NTAPI default behaviour where RAW segment mode always operates on a whole (aligned) underlying slab (segment) typically (1,2,4 MB - dictated by FPGA)
 * System.NtapiNetTxSegmentRawAlignMode = 0 will enable NT4GA to operate on arbitrary raw segment sizes that will be placed back to back
 * System.NtapiNetTxSegmentRawAlignMode = -1 will apply the decided default value for the current driver release. This default value (applied with -1) can change across driver releases.
 */
int NT_NetTxOpen_v3(NtNetStreamTx_t* hStream, const char* name, uint64_t portMask, uint32_t NUMA, uint64_t minHostBufferSize, enum NtPacketDescriptorType_e descriptor, enum NtTimestampType_e ts);

/**
 * @brief Initialize TX stream attributes
 *
 * The attributes are initialized to the following default values: \n
 *    name              = NULL \n
 *    portMask          = 0 \n
 *    NUMA              = NT_NETTX_NUMA_ADAPTER_HB \n
 *    minHostBufferSize = 0 \n
 *    descriptor        = NT_PACKET_DESCRIPTOR_TYPE_NT \n
 *    timestampType     = NT_TIMESTAMP_TYPE_NATIVE_UNIX \n
 *
 * @param[out] attr                       Pointer to the attributes structure
 */
void NT_NetTxOpenAttrInit(NtNetTxAttr_t* attr);

/**
 * @brief Sets the stream name attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] name                        Stream friendly name - used in, for example, logging statements
 */
void NT_NetTxOpenAttrSetName(NtNetTxAttr_t* attr, const char* name);

/**
 * @brief Returns the name attribute
 * @return The name attribute
 */
const char* NT_NetTxOpenAttrGetName(const NtNetTxAttr_t* attr);

/**
 * @brief Sets the descriptor mode attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] portMask                    Descriptor mode
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpenAttrSetDescriptorMode(NtNetTxAttr_t* attr, enum NtNetTxDescriptorMode_e descriptorMode);

/**
 * @brief Returns the descriptor mode attribute
 * @return The descriptor mode attribute
 */
enum NtNetTxDescriptorMode_e NT_NetTxOpenAttrGetDescriptorMode(const NtNetTxAttr_t* attr);

/**
 * @brief Sets the port mask attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] portMask                    Bitmask for ports this stream will use for transmitting
 */
void NT_NetTxOpenAttrSetPortMask(NtNetTxAttr_t* attr, uint64_t portMask);

/**
 * @brief Returns the port mask attribute
 * @return The port mask attribute
 */
uint64_t NT_NetTxOpenAttrGetPortMask(NtNetTxAttr_t* attr);

/**
 * @brief Sets the numa attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] NUMA                        NUMA node on which the host buffer is be located (NOTE: Special options in enum ::NtNetTxOpenNumaOption_e)
 */
void NT_NetTxOpenAttrSetNUMA(NtNetTxAttr_t* attr, uint32_t NUMA);

/**
 * @brief Returns the numa attribute
 * @return The numa attribute
 */
uint32_t NT_NetTxOpenAttrGetNUMA(NtNetTxAttr_t* attr);

/**
 * @brief Sets the flags attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] flags                       Flags - see enum ::NtNetTxOpenFlags_e
 *
 * flags shall be either NT_NETTX_OPEN_FLAGS_NONE (0) or the bitwise-inclusive OR of one or more of the other flags in enum ::NtNetTxOpenFlags_e
 */
void NT_NetTxOpenAttrSetFlags(NtNetTxAttr_t* attr, uint32_t flags);

/**
 * @brief Returns the flags attribute
 * @return The flags attribute - see enum ::NtNetTxOpenFlags_e
 */
uint32_t NT_NetTxOpenAttrGetFlags(NtNetTxAttr_t* attr);

/**
 * @brief Sets the minimum host buffer size attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] minHostBufferSize           Minimum size of host buffer needed in bytes. The smallest host buffer found that is larger or equal to minHostBufferSize is used and the size of the host buffer is set to minHostBufferSize. If set to 0, the first host buffer found is used regardsless of the size.
 */
void NT_NetTxOpenAttrSetMinHostbufferSize(NtNetTxAttr_t* attr, uint64_t minHostBufferSize);

/**
 * @brief Returns the minimum host buffer size attribute
 * @return The minimum host buffer size attribute
 */
uint64_t NT_NetTxOpenAttrGetMinHostbufferSize(NtNetTxAttr_t* attr);

/**
 * @brief Sets the descriptor type attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] descriptor                  Descriptor type to use when transmitting.
 */
void NT_NetTxOpenAttrSetDescriptor(NtNetTxAttr_t* attr, enum NtPacketDescriptorType_e descriptor);

/**
 * @brief Returns the descriptor type attribute
 * @return The descriptor type attribute
 */
enum NtPacketDescriptorType_e NT_NetTxOpenAttrGetDescriptor(NtNetTxAttr_t* attr);

/**
 * @brief Sets bit position in packet descriptor for the Timestamp Inject command bit
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] enable                      Enable/disable use of bits in packet descriptor.
 * @param[in] pos                         Position of bit. Maximum value is 191.

 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpenAttrSetTxtDescriptorPosTimestampInject(NtNetTxAttr_t* attr, bool enable, uint32_t pos);

/**
 * @brief Gets bit position in packet descriptor for the Timestamp Inject command bit
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] enable                      Output pointer to enable/disable use of bit in packet descriptor.
 * @param[in] pos                         Output pointer to position of bits. Value will not be set if disabled.
 */
void NT_NetTxOpenAttrGetTxtDescriptorPosTimestampInject(NtNetTxAttr_t* attr, bool* enable, uint32_t* pos);

//-----------
/**
 * @brief Sets bit position in packet descriptor for the FCS control command bit
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] enable                      Enable/disable use of bits in packet descriptor.
 *                                        When disabled all FCS is recalculated for packets.
 *                                        When enabled FCS recalculation is controlled by
 *                                        the packet descriptor bit in position pos.
 * @param[in] pos                         Position of bit. Maximum value is 191.

 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpenAttrSetTxtDescriptorPosFcs(NtNetTxAttr_t* attr, bool enable, uint32_t pos);

/**
 * @brief Gets bit position in packet descriptor for the FCS control command bit
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] enable                      Output pointer to enable/disable use of bit in packet descriptor.
 * @param[in] pos                         Output pointer to position of bits. Value will not be set if disabled.
 */
void NT_NetTxOpenAttrGetTxtDescriptorPosFcs(NtNetTxAttr_t* attr, bool* enable, uint32_t* pos);

//-----------
/**
 * @brief Sets the timestamp type attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] timestampType               Timestamp format to use when transmitting.
 */
void NT_NetTxOpenAttrSetTimestampType(NtNetTxAttr_t* attr, enum NtTimestampType_e timestampType);

/**
 * @brief Returns the timestamp type attribute
 * @return The timestamp type attribute
 */
enum NtTimestampType_e NT_NetTxOpenAttrGetTimestampType(NtNetTxAttr_t* attr);

/**
 * @brief Set bit position in packet descriptor for layer 3 offset bits.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Enable/disable use of bits in packet descriptor.
 * @param[in] pos         Position of bits. Maximum value is 191.
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpenAttrSetDescriptorPosLayer3Offset(NtNetTxAttr_t* attr, bool enable, uint32_t pos);

/**
 * @brief Get bit position in packet descriptor for layer 3 offset bits.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Output pointer to enable/disable use of bits in packet descriptor.
 * @param[in] pos         Output pointer to position of bits. Value will not be set if disabled.
 */
void NT_NetTxOpenAttrGetDescriptorPosLayer3Offset(const NtNetTxAttr_t* attr, bool* enable, uint32_t* pos);

/**
 * @brief Set bit position in packet descriptor for layer 4 offset bits.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Enable/disable use of bits in packet descriptor.
 * @param[in] pos         Position of bits. Maximum value is 191.
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpenAttrSetDescriptorPosLayer4Offset(NtNetTxAttr_t* attr, bool enable, uint32_t pos);

/**
 * @brief Get bit position in packet descriptor for layer 4 offset bits.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Output pointer to enable/disable use of bits in packet descriptor.
 * @param[in] pos         Output pointer to position of bits. Value will not be set if disabled.
 */
void NT_NetTxOpenAttrGetDescriptorPosLayer4Offset(const NtNetTxAttr_t* attr, bool* enable, uint32_t* pos);

/**
 * @brief Set bit position in packet descriptor for frame type bits.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Enable/disable use of bits in packet descriptor.
 * @param[in] pos         Position of bits. Maximum value is 191.
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpenAttrSetDescriptorPosFrameType(NtNetTxAttr_t* attr, bool enable, uint32_t pos);

/**
 * @brief Get bit position in packet descriptor for frame type bits.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Output pointer to enable/disable use of bits in packet descriptor.
 * @param[in] pos         Output pointer to position of bits. Value will not be set if disabled.
 */
void NT_NetTxOpenAttrGetDescriptorPosFrameType(const NtNetTxAttr_t* attr, bool* enable, uint32_t* pos);

/**
 * @brief Set bit position in packet descriptor for checksum command bits.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Enable/disable use of bits in packet descriptor.
 * @param[in] pos         Position of bits. Maximum value is 191.
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpenAttrSetDescriptorPosChecksumCmd(NtNetTxAttr_t* attr, bool enable, uint32_t pos);

/**
 * @brief Get bit position in packet descriptor for checksum command bits.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Output pointer to enable/disable use of bits in packet descriptor.
 * @param[in] pos         Output pointer to position of bits. Value will not be set if disabled.
 */
void NT_NetTxOpenAttrGetDescriptorPosChecksumCmd(const NtNetTxAttr_t* attr, bool* enable, uint32_t* pos);

/**
 * @brief Set bit position in packet descriptor for TX ignore bit.
 *
 * See Standard Descriptor for "TX ignore bit" description.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Enable/disable use of bit in packet descriptor.
 * @param[in] pos         Position of bits. Maximum value is 191.
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpenAttrSetDescriptorPosIgnoreBit(NtNetTxAttr_t* attr, bool enable, uint32_t pos);

/**
 * @brief Get bit position in packet descriptor for TX ignore bit.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Output pointer to enable/disable use of bits in packet descriptor.
 * @param[in] pos         Output pointer to position of bits. Value will not be set if disabled.
 */
void NT_NetTxOpenAttrGetDescriptorPosIgnoreBit(const NtNetTxAttr_t* attr, bool* enable, uint32_t* pos);

/**
 * @brief Set bit position in packet descriptor for TX now bit.
 *
 * See Standard Descriptor for "TX now bit" description.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Enable/disable use of bit in packet descriptor.
 * @param[in] pos         Position of bits. Maximum value is 191.
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpenAttrSetDescriptorPosTxNowBit(NtNetTxAttr_t* attr, bool enable, uint32_t pos);

/**
 * @brief Get bit position in packet descriptor for TX now bit.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Output pointer to enable/disable use of bits in packet descriptor.
 * @param[in] pos         Output pointer to position of bits. Value will not be set if disabled.
 */
void NT_NetTxOpenAttrGetDescriptorPosTxNowBit(const NtNetTxAttr_t* attr, bool* enable, uint32_t* pos);

/**
 * @brief Set bit position in packet descriptor for TX set clock bit.
 *
 * See Standard Descriptor for "TX set clock bit" description.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Enable/disable use of bit in packet descriptor.
 * @param[in] pos         Position of bits. Maximum value is 191.
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpenAttrSetDescriptorPosClockBit(NtNetTxAttr_t* attr, bool enable, uint32_t pos);

/**
 * @brief Get bit position in packet descriptor for TX set clock bit.
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Output pointer to enable/disable use of bits in packet descriptor.
 * @param[in] pos         Output pointer to position of bits. Value will not be set if disabled.
 */
void NT_NetTxOpenAttrGetDescriptorPosClockBit(const NtNetTxAttr_t* attr, bool* enable, uint32_t* pos);

/**
 * @brief Set mode for use of wire length in packet descriptor
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      flag to enable/disable use wire length in packet descriptor.
 */
int NT_NetTxOpenAttrSetDescriptorUseWireLength(NtNetTxAttr_t* attr, bool enable);

/**
 * @brief get mode for use of wire length in packet descriptor
 *
 * @param[in] attr        Pointer to the attributes structure.
 * @param[in] enable      Output pointer flag indicating use of wire length in packet descriptor.
 */
int NT_NetTxOpenAttrGetDescriptorUseWireLength(const NtNetTxAttr_t* attr, bool* enable);


/**
 * @brief Opens a TX host buffer and returns a NtNetStreamTx_t handle (extended version)
 *
 * This function is called to retrieve a TX stream handle.
 * This function will only work with 4GA adapters.
 *
 * @param[out] hStream    Reference to a NtNetStreamTx_t stream pointer
 * @param[in]  attr       Pointer to stream attributes
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxOpen_Attr(NtNetStreamTx_t* hStream, const NtNetTxAttr_t* attr);
/**
 * @brief Gets a TX port buffer
 *
 * This function is called to acquire a TX buffer
 *
 * @note This function has no mutex protection, therefore the same hStream cannot be used by multiple threads
 *
 * @param[in]    hStream      Network TX stream handle
 * @param[out]   netBuf       Segment/packet container reference
 * @param[in]    port         Port to receive a TX buffer from
 * @param[in]    packetSize   Size of the packet to transmit including 4-byte CRC.
 * @param[in]    packetOption Option to control the properties of the buffer, see @ref NtNetTxPacketOption_e for details
 * @param[in]    timeout      Time in milliseconds to wait for a new buffer - a timeout of -1 will wait indefinitely for a new buffer
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxGet(NtNetStreamTx_t hStream, NtNetBuf_t* netBuf, uint32_t port, size_t packetSize, enum NtNetTxPacketOption_e packetOption, int timeout);

/**
 * @brief Releases the network buffer
 *
 * This function releases the netBuf data obtained via NT_TxGet
 *
 * @note This function has no mutex protection and can therefore the same hStream cannot be used by multiple threads
 *
 * @param[in] hStream Network TX stream handle
 * @param[in] netBuf  Net buffer is received via NT_TxGet
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxRelease(NtNetStreamTx_t hStream, NtNetBuf_t netBuf);

/**
 * @brief Reads data from the stream
 *
 * This function will read Tx related info
 *
 * @param[in] hStream  NetTx stream handle
 * @param[in] cmd      NetTx read structure
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxRead(NtNetStreamTx_t hStream, NtNetTx_t* cmd);

/**
 * @brief Closes a TX stream
 *
 * This function is called to close a TX stream
 *
 * @param[in] hStream  The TX stream handle to close
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxClose(NtNetStreamTx_t hStream);

/**
 * @brief AddPacket to a TX stream
 *
 * This function is called to put together scattered fragments of a packet and add it to a TX stream
 *
 * @note This function has no mutex protection and cannot be used by multiple threads on the same stream, hStream.
 *
 * @param[in] hStream       Network TX stream handle
 * @param[in] port          Port to add packet into host buffer
 * @param[in] fragments     The scattered list of packet fragments
 * @param[in] fragmentCount The number of scattered fragments in the list
 * @param[in] timeout       Time in milliseconds to wait for a packet buffer - a timeout of -1 will wait indefinitely for a packet buffer
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetTxAddPacket(NtNetStreamTx_t hStream, uint32_t port, NtNetTxFragment_t* fragments, uint32_t fragmentCount, int timeout );

//


/** @page HwL3L4Checksum HW IP/UDP/TCP checksum
 * @{
 * The NT40E2-4, NT20E2, NT4E2 adapters and NT4E in-line adapters support IPv4, UDP and TCP
 * calculations in hardware on transmit.\n
 * In order to use the feature, the packet descriptor must be configured prior to calling
 * @ref NT_NetTxRelease().\n
 * <b>Note:</b> The feature only works on non-fragmented packets.\n\n
 * Here is an example on the configuration required before transmitting a packet.
 *
 @verbatim

 struct IPv4Header_s {
  uint16_t ip_hl: 4;
  uint16_t ip_v: 4;
  uint16_t ip_tos: 8;
  uint16_t ip_len;

  uint32_t ip_id:16;
  uint32_t ip_frag_off:16;
#define IP_DONT_FRAGMENT  0x4000
#define IP_MORE_FRAGMENTS 0x2000

  uint32_t ip_ttl:8;
  uint32_t ip_prot:8;
  uint32_t ip_crc:16;

  uint32_t ip_src;
  uint32_t ip_dest;
}; //20 bytes

struct UDPHeader_s {
  uint32_t udp_src:16;
  uint32_t udp_dest:16;

  uint32_t udp_len:16;
  uint32_t udp_crc:16;
}; // 8 bytes


          NT_NET_SET_PKT_IS_IP(hNetBuf, 1);
          NT_NET_SET_PKT_IS_UDP(hNetBuf, 1);
          NT_NET_SET_PKT_IP_CSUM_OK(hNetBuf, 1);
          NT_NET_SET_PKT_UDP_CSUM_OK(hNetBuf, 1);
          if(NT_NET_GET_PKT_DESCRIPTOR_TYPE(hNetBuf) == NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED) {
            NT_NET_SET_PKT_ISL(hNetBuf, 0);
            NT_NET_SET_PKT_VLAN_COUNT(hNetBuf, 0);
            NT_NET_SET_PKT_MPLS_COUNT(hNetBuf, 0);
            NT_NET_SET_PKT_L2_FRAME_TYPE(hNetBuf, NT_L2_FRAME_TYPE_ETHER_II);
            NT_NET_SET_PKT_L3_FRAME_TYPE(hNetBuf, NT_L3_FRAME_TYPE_IPv4);
            NT_NET_SET_PKT_L4_FRAME_TYPE(hNetBuf, NT_L4_FRAME_TYPE_UDP);
            NT_NET_SET_PKT_L3_LENGTH(hNetBuf, sizeof(struct IPv4Header_s)>>2);
            NT_NET_SET_PKT_L4_LENGTH(hNetBuf, sizeof(struct UDPHeader_s)>>2);
            NT_NET_SET_PKT_CALC_L3_CHECKSUM(hNetBuf, 1);
            NT_NET_SET_PKT_CALC_L4_CHECKSUM(hNetBuf, 1);
         }
 @endverbatim

 @} */

/** @page PacketBasedTransmit Packet based transmit
 * @{
 *
 * For packet based transmit see the example @ref transmit_packet_example.c "net/transmit/transmit_packet_example.c"
 @} */

/** @page SegmentBasedTransmit Segment based transmit
 * @{
 *
 * For segment based transmit see the example @ref transmit_segment_example.c "net/transmit_segment/transmit_segment_example.c"
 @} */

/** @} */


/** @addtogroup StreamFile
 *@{
 */
/**
 * Network file stream handle - used for file streams
 */
typedef struct NtNetStreamFile_s* NtNetStreamFile_t;

/**
 * @brief Opens a capture file
 *
 * This function is called to open a capture file, captured with a segment-based stream.
 * The capture file must have an NT, PCAP or PCAP-NG file header otherwise it will fail
 * when opening the capture file.
 *
 * @param[out] hStream       Reference to a NetFile_t stream pointer
 * @param[in]  name          A stream friendly name - used in, for example, logging statements
 * @param[in]  netIntf       Deliver packets or segments
 * @param[in]  file          The capture file to open
 *
 * @retval  NT_SUCCESS    Success
 * @retval  !=NT_SUCCESS  Error - use @ref NT_ExplainError for an error description
 */
int NT_NetFileOpen(NtNetStreamFile_t* hStream, const char* name, enum NtNetInterface_e netIntf, const char* file);

/**
* @brief Opens a capture file (extended version)
*
* This function is called to open a capture file, captured with a segment-based stream.
* The capture file must have an NT, PCAP or PCAP-NG file header otherwise it will fail
* when opening the capture file.
*
* @param[out] hStream       Reference to a NetFile_t stream pointer
* @param[in]  name          A stream friendly name - used in, for example, logging statements
* @param[in]  netIntf       Deliver packets or segments
* @param[in]  file          The capture file to open
* @param[in]  noConvert     Do not convert PCAP files (Native PCAP tx for 4GA)
*
* @retval  NT_SUCCESS    Success
* @retval  !=NT_SUCCESS  Error - use @ref NT_ExplainError for an error description
*/
int NT_NetFileOpen_v2(NtNetStreamFile_t* hStream, const char* name, enum NtNetInterface_e netIntf, const char* file, bool noConvert);

/**
 * @brief Gets packets/segments from a file stream
 *
 * This function is called to retrieve packets or segments from a capture file
 *
 * @note This function has no mutex protection, therefore the same hStream cannot be used by multiple threads
 *
 * @param[in]    hStream     NetFile stream handle
 * @param[out]   netBuf      Packet/segment container reference
 *
 * @retval  NT_SUCCESS (0)          Success
 * @retval  NT_STATUS_END_OF_FILE   EOF indicator - See note
 * @retval  otherwise               Error - use @ref NT_ExplainError for an error description
 * @note When NT_STATUS_END_OF_FILE is returned the internal file offset that been reset making it possible to
 * call NT_NetFileGet() again without having to close and open the file, which improves performance when
 * replaying a file continuously.
 */
int NT_NetFileGet(NtNetStreamFile_t hStream, NtNetBuf_t* netBuf);

/**
 * @brief Releases the network buffer
 *
 * This function will release the netBuf data obtained via NT_FileGet
 *
 * @note This function has no mutex protection, therefore the same hStream cannot be used by multiple threads
 *
 * @param[in] hStream  NetStreamFile stream handle
 * @param[in] netBuf   The network buffer is received via NT_FileGet
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetFileRelease(NtNetStreamFile_t hStream, NtNetBuf_t netBuf);

/**
 * @brief Closes a file stream
 *
 * This function is called to close a file stream
 *
 * @param[in] hStream The file stream handle to close
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetFileClose(NtNetStreamFile_t hStream);

/**
 * @brief Read information about a file stream
 *
 * This function is called to read information about a file stream
 *
 * @param[in]     hStream  The file stream handle
 * @param[in,out] data     Structure containing command and returned data
 *
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_NetFileRead(NtNetStreamFile_t hStream, NtNetFileRead_t* data);

/**
* @brief Opens a capture file
*
* This function is called to open a capture file, captured with a segment-based stream.
* The capture file must have an NT, PCAP or PCAP-NG file header otherwise it will fail
* when opening the capture file.
*
* @param[out] hStream       Reference to a NetFile_t stream pointer
* @param[in]  file          The capture file to open
* @param[in]  attr          Attributes of the stream
*
* @retval  NT_SUCCESS    Success
* @retval  !=NT_SUCCESS  Error - use @ref NT_ExplainError for an error description
*/
int NT_NetFileOpen_Attr(NtNetStreamFile_t* hStream, const char* file, const NtNetFileAttr_t* attr);

/**
 * @brief Initialize NetFile stream attributes
 *
 * The attributes are initialized to the following default values: \n
 *    name                = NULL \n
 *    netIntf             = NT_NET_INTERFACE_SEGMENT \n
 *    pcapToNtConversion  = True \n
 *    convertedTsType     = NT_TIMESTAMP_TYPE_NATIVE_UNIX \n
 *
 * @param[in] attr        Pointer to the attributes structure
 *
 */
void NT_NetFileOpenAttrInit(NtNetFileAttr_t* attr);

/**
 * @brief Sets the stream name attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] name                        Stream friendly name - used in, for example, logging statements
 */
void NT_NetFileOpenAttrSetName(NtNetFileAttr_t* attr, const char* name);

/**
 * @brief Returns the name attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 *
 * @return The name attribute
 */
const char* NT_NetFileOpenAttrGetName(const NtNetFileAttr_t* attr);

/**
 * @brief Sets the interface type attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 * @param[in] netIntf                     Interface type - segment or packet
 */
void NT_NetFileOpenAttrSetInterface(NtNetFileAttr_t* attr, enum NtNetInterface_e netIntf);

/**
 * @brief Returns the interface type attribute
 *
 * @param[in] attr                        Pointer to the attributes structure
 *
 * @return The interface type attribute
 */
enum NtNetInterface_e NT_NetTxOpenAttrGetInterface(NtNetTxAttr_t* attr);


/**
 * @brief Enable or disable automatic conversion from PCAP to NT format
 *
 * @param[in] attr          Pointer to the attributes structure
 * @param[in] enableFlag    True enables automatic conversion from PCAP to NT
 *                          format for 3GA.  Automatic conversion does not
 *                          apply to 4GA, which has native support for PCAP.
 */
void NT_NetFileOpenAttrSetEnablePcapToNtConversion(NtNetFileAttr_t *attr,
                                                   bool enableFlag);

/**
 * @brief Returns whether automatic conversion from PCAP to NT format is enabled
 *
 * @param[in] attr          Pointer to the attributes structure
 *
 * @return A boolean where True denotes that automatic conversion from
 *         PCAP to NT format is enabled (only applicable to 3GA).
 */
bool NT_NetFileOpenAttrGetEnablePcapToNtConversion(const NtNetTxAttr_t *attr);

/**
 * @brief Sets the converted timstamp type attribute
 *
 * This attribute is only used, when a PCAP file is converted to
 * an NT capture file.
 *
 * Valid values are:
 *   NT_TIMESTAMP_TYPE_NATIVE_UNIX
 *   NT_TIMESTAMP_TYPE_UNIX_NANOTIME
 *
 * @param[in] attr              Pointer to the attributes structure
 * @param[in] convertedTsType   Converted timestamp type
 */
int NT_NetFileOpenAttrSetConvertedTsType(NtNetFileAttr_t* attr, enum NtTimestampType_e convertedTsType);

/**
 * @brief Gets the converted timstamp type attribute
 *
 * @param[in] attr              Pointer to the attributes structure
 *
 * @return the converted Timestamp Type attribute
 */
enum NtTimestampType_e NT_NetFileOpenAttrGetConvertedTsType(NtNetTxAttr_t* attr);

/** @} */

/**
 * MACROs to access network data
 */

/**
 * Layer 2 types
 */
enum NtL2FrameType_e {
  NT_L2_FRAME_TYPE_ETHER_II=0, //!< Ether type II frame
  NT_L2_FRAME_TYPE_LLC,        //!< LLC frame
  NT_L2_FRAME_TYPE_SNAP,       //!< SNAP frame
  NT_L2_FRAME_TYPE_NOVELL_RAW  //!< Novell Raw frame
};

/**
 * Layer 3 types
 */
enum NtL3FrameType_e {
  NT_L3_FRAME_TYPE_IPv4=0, //!< IPv4 frame
  NT_L3_FRAME_TYPE_IPv6,   //!< IPV6 frame
  NT_L3_FRAME_TYPE_IPX,    //!< IPX frame
  NT_L3_FRAME_TYPE_OTHER,  //!< Other frame
};

/**
 * Layer 4 frame types
 */
enum NtL4FrameType_e {
  NT_L4_FRAME_TYPE_TCP=0, //!< TCP frame
  NT_L4_FRAME_TYPE_UDP,   //!< UDP frame
  NT_L4_FRAME_TYPE_ICMP,  //!< ICMP frame
  NT_L4_FRAME_TYPE_OTHER, //!< Other frame
  NT_L4_FRAME_TYPE_GRE,   //!< GRE frame
  NT_L4_FRAME_TYPE_SCTP,  //!< SCTP frame
  NT_L4_FRAME_TYPE_IPV4,  //!< IPV4 in IP frame
  NT_L4_FRAME_TYPE_IPV6,  //!< IPV6 in IP frame
};

/**
 * Layer 4 port types
 */
enum NtL4PortType_e {
  NT_L4_PORT_OTHER=0,    //!< Other port
  NT_L4_PORT_GTPV0_U,    //!< GTPV0_U port
  NT_L4_PORT_GTPV1V2_C,  //!< GTPV1V2_C port
  NT_L4_PORT_GTPV1_U     //!< GTPV1_U port
};

/**
 * Frame tunnel types
 */
enum NtTunnelType_e {
  NT_TUNNELTYPE_OTHER=0,        //!< Other data type
  NT_TUNNELTYPE_GTPV0_U,        //!< GTPV0_U data type
  NT_TUNNELTYPE_GTPV1V2_C,      //!< GTPV1V2_C data type
  NT_TUNNELTYPE_GTPV1_U_SIGNAL, //!< GTPV1_U_SIGNAL type
  NT_TUNNELTYPE_GTPV1_U_GPDU,   //!< GTPV1_U_GPDU data type
  NT_TUNNELTYPE_IPINIP,         //!< IPINIP data type
};

/**
 * L3 fragmentation
 */
enum NtL3FragmentType_e {
  NT_L3_FRAGMENT_TYPE_NONE,        //!< L3 not fragmented
  NT_L3_FRAGMENT_TYPE_FIRST,       //!< L3 first fragment
  NT_L3_FRAGMENT_TYPE_MIDDLE,      //!< L3 middle fragment
  NT_L3_FRAGMENT_TYPE_LAST,        //!< L3 last fragment
};

/** @addtogroup NetworkStream
 *@{
 */

/**
 * @defgroup MetaDataMacros User meta data container
 * @{
 * The following macros get and set user defined meta data.
 * Use these fields as house-keeping storage. No NTAPI function use these meta containers for anything.
 *
 */

/** @def NT_NET_GET_USER_META_ARG0
 *  @brief Returns the meta data arg0 uintptr_t value
 *  @param[in] "_hNetBuf_" NetBuf pointer
 *  @hideinitializer
 */
#define NT_NET_GET_USER_META_ARG0(_hNetBuf_) ((_hNetBuf_)->arg0)

/** @def NT_NET_GET_USER_META_ARG1
 *  @brief Returns the meta data arg1 uintptr_t value
 *  @param[in] "_hNetBuf_" NetBuf pointer
 *  @hideinitializer
 */
#define NT_NET_GET_USER_META_ARG1(_hNetBuf_) ((_hNetBuf_)->arg1)

/** @def NT_NET_GET_USER_META_ARG2
 *  @brief Returns the meta data arg2 uintptr_t value
 *  @param[in] "_hNetBuf_" NetBuf pointer
 *  @hideinitializer
 */
#define NT_NET_GET_USER_META_ARG2(_hNetBuf_) ((_hNetBuf_)->arg2)

/** @def NT_NET_SET_USER_META_ARG0
 *  @brief Set the meta data arg0 uintptr_t value
 *  @param[in] "_hNetBuf_" NetBuf pointer
 *  @param[in] value An uintptr_t sized value
 *  @hideinitializer
 */
#define NT_NET_SET_USER_META_ARG0(_hNetBuf_, value) ((_hNetBuf_)->arg0 = (value))

/** @def NT_NET_SET_USER_META_ARG1
 *  @brief Set the meta data arg1 uintptr_t value
 *  @param[in] "_hNetBuf_" NetBuf pointer
 *  @param[in] value An uintptr_t sized value
 *  @hideinitializer
 */
#define NT_NET_SET_USER_META_ARG1(_hNetBuf_, value) ((_hNetBuf_)->arg1 = (value))

/** @def NT_NET_SET_USER_META_ARG2
 *  @brief Set the meta data arg2 uintptr_t value
 *  @param[in] "_hNetBuf_" NetBuf pointer
 *  @param[in] value An uintptr_t sized value
 *  @hideinitializer
 */
#define NT_NET_SET_USER_META_ARG2(_hNetBuf_, value) ((_hNetBuf_)->arg2 = (value))

/** @} */

/** @defgroup DataMacros Network macros
 * @{
 * The network stream delivers data to the application. In order to access data
 * content, such as packet length or packet receive time stamp, a set of macros is
 * provided. These macros are divided into 2 major groups:
 * - @ref SegmentMacros
 * - @ref PacketMacros
 *
 * The @ref SegmentMacros are used with the segment-based interface
 * The @ref PacketMacros are used with the packet-based interface
 */

/** @defgroup SegmentMacros Segment macros
 *  @{
 * The following is only possible on segment-based streams
 */

/** @def NT_NET_GET_SEGMENT_PTR
 *  @brief Returns the segment pointer
 *  @param[in] "_hNetBuf_" Segment container reference
 *  @hideinitializer
 */
#define NT_NET_GET_SEGMENT_PTR(_hNetBuf_)              ((_hNetBuf_)->hHdr)

/** @def NT_NET_GET_SEGMENT_LENGTH
 *  @brief Returns the segment length
 *  @param[in] "_hNetBuf_" Segment container reference
 *  @hideinitializer
 */
#define NT_NET_GET_SEGMENT_LENGTH(_hNetBuf_)           ((size_t)(_hNetBuf_)->length)

/** @def NT_NET_GET_SEGMENT_PKTS
 *  @brief Returns the number of packets in a segment
 *
 *  This macro is only supported on NT4GA adapters configured to static segment
 *  size emulation mode. On NT4GA adapters configured to dynamic segment size
 *  this macro will always return 0.
 *  @param[in] "_hNetBuf_" Segment container reference
 *  @hideinitializer
 */
#define NT_NET_GET_SEGMENT_PKTS(_hNetBuf_)           ((size_t)(_hNetBuf_)->pkts)

/** @def NT_NET_GET_SEGMENT_TIMESTAMP
 *  @brief The time stamp of the first packet in the segment
 *  @param[in] "_hNetBuf_" Segment container reference
 *  @hideinitializer
 */
#define NT_NET_GET_SEGMENT_TIMESTAMP(_hNetBuf_)        NT_NetGetSegmentTimestamp((_hNetBuf_)->hHdr)
uint64_t NT_NetGetSegmentTimestamp(void* pDescr);

/** @def NT_NET_GET_SEGMENT_TIMESTAMP_TYPE
 *  @brief The time stamp type
 *  @param[in] "_hNetBuf_" Segment container reference
 *  @hideinitializer
 */
#define NT_NET_GET_SEGMENT_TIMESTAMP_TYPE(_hNetBuf_)   ((_hNetBuf_)->tsType)

/** @def NT_NET_SET_SEGMENT_LENGTH
 *  @brief Sets the segment length
 *
 *  This is used when generating a TX segment and should be used with care.
 *  @param[in,out] "_hNetBuf_" Segment container reference
 *  @param[in] "_length_" Length of the segment
 *  @hideinitializer
 */
#define NT_NET_SET_SEGMENT_LENGTH(_hNetBuf_, _length_) do {(_hNetBuf_)->length=_length_;} while(0)


/** @defgroup SegmentFunctions Functions to handle segment data
 * @{
 * These inline C functions are only valid when "PacketDescriptor" in ntservice.ini file has been set to any value than PCAP
 * and @ref NT_NET_GET_PKT_DESCRIPTOR_TYPE returns @ref NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED or @ref NT_PACKET_DESCRIPTOR_TYPE_NT
 */
/**
 * @brief Inline C function to create a segment NtNetBuf_t
 *
 * This function is used when creating segments in application memory, e.g.
 * when constructing a transmit segment
 *
 * @param[in] size        Size of the memory provided by the "mem" pointer
 * @param[in] mem         Pointer to the segment memory allocated
 * @param[in] portOffset  Segments are per adapter and ports are relative to the port offset. The port offset can be found in @ref NtInfoAdapter_v6_s::portOffset. If 0 is provided then the possible values in @ref NT_NET_SET_PKT_TXPORT can only be from 0 to 3.
 * @param[out] segNetBuf Destination segment NtNetBuf_t structure
 *
 */
static NT_INLINE void _nt_net_create_segment_netbuf(uint64_t size, void* mem, uint8_t portOffset, struct NtNetBuf_s* segNetBuf)
{
  memset(segNetBuf, 0, sizeof(struct NtNetBuf_s));
  segNetBuf->length=size;
  segNetBuf->portOffset=portOffset;
  segNetBuf->hHdr=(NtNetBufHdr_t)(mem);
  segNetBuf->hPkt=(NtNetBufPkt_t)(mem);
  *((uint64_t*)mem+0)=0;
  *((uint64_t*)mem+1)=0;
  *((uint64_t*)mem+2)=0;
  *((uint64_t*)mem+3)=0;
}

/**
 * @brief Inline C function to use when traversing segments. The
 * function will update the NetBuf to the next packet
 * in the segment.
 *
 * @param[in] segNetBuf   Segment NtNetBuf_s * structure
 * @param[in] segLength   Length of the segment - used to know when there is no more data
 * @param[out] pktNetBuf  Packet NtNetBuf_s * structure
 *
 * @retval Returns the amount of data left in the segment
 */
static NT_INLINE uint64_t _nt_net_get_next_packet(struct NtNetBuf_s* segNetBuf, uint64_t segLength, struct NtNetBuf_s* pktNetBuf)
{
  if(segLength) {
    uint8_t* nextPacket = (uint8_t*)pktNetBuf->hHdr + NT_NET_GET_PKT_CAP_LENGTH(pktNetBuf);
    uint8_t* endSegm = (uint8_t*)segNetBuf->hHdr + segLength;
    // If this was the last packet then do not traverse any further
    if (nextPacket >= endSegm) {
      return 0;
    }
    pktNetBuf->hHdr=(NtNetBufHdr_t)nextPacket;
    pktNetBuf->hPkt=(NtNetBufPkt_t)(nextPacket + NT_NET_GET_PKT_DESCR_LENGTH(pktNetBuf));
    return (uint64_t)(endSegm - nextPacket);
  } else {
    return 0;
  }
}

/**
 * @brief Inline C function to build a packet based NtNetBuf_t
 * from a segment based NtNetBuf_t
 *
 * @param[in] segNetBuf Segment NtNetBuf_t structure
 * @param[out] pktNetBuf Destination packet NtNetBuf_t structure
 *
 */
static NT_INLINE void _nt_net_build_pkt_netbuf(struct NtNetBuf_s* segNetBuf, struct NtNetBuf_s* pktNetBuf)
{
  memcpy((void*)pktNetBuf, (void*)segNetBuf, sizeof(struct NtNetBuf_s));
  pktNetBuf->hHdr=(NtNetBufHdr_t)(segNetBuf->hHdr);
  pktNetBuf->hPkt=(NtNetBufPkt_t)((uint8_t*)segNetBuf->hHdr+NT_NET_GET_PKT_DESCR_LENGTH(segNetBuf));
}

/**
 * @brief Inline C function to initialize a segment NtNetBuf_t structure
 * using any received segment buffer.
 *
 * This function is used when a new NtNetBuf_t handle is needed for a provided segment
 * buffer, e.g. when copying segments
 *
 * @param[in] size        Size of the segment pointed to by the "segment" pointer
 * @param[in] segment     Pointer to the segment
 * @param[in] portOffset  Segments are per adapter and ports are relative to the port offset. The port offset of the adapter of which the segment originates from most be copied/stored in parallel, or known by some other means, and specified here. If 0 is used here local ports will be seen as logical ports.
 * @param[out] segNetBuf  Segment NtNetBuf_t structure to initialize
 *
 */
static NT_INLINE void _nt_net_initialize_segment_netbuf(uint64_t size, void* segment, uint8_t portOffset, struct NtNetBuf_s* segNetBuf)
{
  memset(segNetBuf, 0, sizeof(struct NtNetBuf_s));
  segNetBuf->length=size;
  segNetBuf->portOffset=portOffset;
  segNetBuf->hHdr=(NtNetBufHdr_t)(segment);
  segNetBuf->hPkt=(NtNetBufPkt_t)(segment);
}


/** @} */

/** @} */

/** @} */
/** @} */
/** @} */


#ifndef DOXYGEN_INTERNAL_ONLY
#define NT_MAKE_STRUCTURE_ID( __structureType, __structureName ) \
  ((uint32_t)((__structureType << 16) | sizeof(__structureName)))

/**
 * File header. This data must be placed in the beginning of a
 * file when storing data to disk.
 */
#define NT_FILE_HEADER0_COOKIE 0xDEADBEAF
// Ensure that the following is packed equally on 32 and 64bit
#pragma pack(push, 1)
typedef struct NtFileHeader0_s {
  /**
   * StructureID is used to identify the header structure type
   */
  uint32_t structid; //!< The segment descriptor version
  uint64_t align;    //!< Alignment to ensure the cookie is located at offset 12
  /**
   * Cookie to validate the header
   */
  uint32_t cookie;                //!< Cookie = 0xDEADBEAF. Must be located at offset 12 to be able to detect if the file starts with a packet. The cookie will be located where storedLength is found in a packet.
  /**
   * The time stamp type used to time stamp the segments - very useful in offline mode
   */
  uint8_t tsType;       //!< Timestamp type that is supplied with 'TimeValidAt'
  /**
   * Port offset. All packets in the segment have a per adapter specific port index
   * and by adding this portOffset, the system-wide port is retrieved.
   */
  uint8_t portOffset;  //!< Port offset - use to calculate the logical port number
  /**
   * Color lookup.
   * Contains the customer color ID mapping to HW IDs.
   */
  uint8_t colorMap[64]; //!< Filter color map table
  uint8_t reserved[46]; //!< Reserved. Total structure size must be 128 bytes.
} NtFileHeader0_t;

// Disable packing
#pragma pack(pop)
#define NT_STID_FILE_HEADER0 NT_MAKE_STRUCTURE_ID(1, NtFileHeader0_t)
#endif
#endif /* __STREAM_NET_H__ */

//
// EOF
//
