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
 * This is the header file of the statistics stream interface containing
 * included for backward compatibility structures.
 *
 */

#ifndef __STREAM_STATISTICS_COMPAT_H__
#define __STREAM_STATISTICS_COMPAT_H__

#if !defined(_NT_NTAPI_NO_COMPAT)

/********************************************************************************/
/*       Statistics data defines for NT_STATISTICS_READ_CMD_QUERY               */
/********************************************************************************/
#define NT_STATISTICS_READ_CMD_QUERY  NT_STATISTICS_READ_CMD_COMPAT_0

/**
  * Extended drop counters - these counters will count the packets
  * dropped for various reasons
 */
struct NtExtendedDropCounters_s {
  uint64_t pktsMacBandwidth;  //!< Number of packets dropped by the MAC because of bandwidth issues and number of packets < 17 octets. This counter is also available in @ref NtRMON1Counters_s::dropEvents.

  uint64_t pktsOverflow;      //!< Number of packets dropped because the port buffer is full
  uint64_t octetsOverflow;    //!< Number of octets dropped because the port buffer is full

  uint64_t pktsDedup;         //!< Number of packets dropped because of deduplication
  uint64_t octetsDedup;       //!< Number of octets dropped because of deduplication

  uint64_t pktsNoFilter;      //!< Number of packets dropped because they do not match a filter
  uint64_t octetsNoFilter;    //!< Number of octets dropped because they do not match a filter
};

/**
 * Extended RMON - these counters are used to categorize packets not handled by RMON1
 */
struct NtExtendedRMONCounters_s {
  uint64_t pkts1519to2047Octets;   //!< Number of packets in the range 1519 to 2047 octets
  uint64_t pkts2048to4095Octets;   //!< Number of packets in the range 2048 to 4095 octets
  uint64_t pkts4096to8191Octets;   //!< Number of packets in the range 4096 to 8191 octets
  uint64_t pkts8192toMaxOctets;    //!< Number of packets in the range 8192 to MAX octets
  uint64_t pktsHardSlice;          //!< Number of packets in the range 10001 to 16383 octets
  uint64_t pktsHardSliceJabber;    //!< Number of bad packets in the range 10001 to 16383 octets and packets > 16383 octets
  uint64_t unicastPkts;            //!< Number of Unicast packets including MAC control packets
  // The following counters are also counted as a sum in @ref NtRMON1Counters_s::crcAlignErrors.
  uint64_t pktsCrc;               //!< Number of packets with CRC errors
  uint64_t pktsAlignment;         //!< Number of packets with alignment errors
  uint64_t pktsCodeViolation;     //!< Number of packets with code violation errors
};

/**
 * Packet decoding counters - these counters are available on adapters with a packet decoder
 */
struct NtDecodeCounters_s {
  uint64_t pktsGiantUndersize;    //!< Number of packets > 63 bytes including tags and =< 63 excluding tags
  uint64_t pktsBabyGiant;         //!< Number of packets > MAX including tags and =< MAX excluding tags
  uint64_t pktsNotIslVlanMpls;    //!< Number of packets without ISL, VLAN and MPLS
  uint64_t pktsIsl;               //!< Number of packets with ISL
  uint64_t pktsVlan;              //!< Number of packets with VLAN
  uint64_t pktsIslVlan;           //!< Number of packets with ISL and VLAN
  uint64_t pktsMpls;              //!< Number of packets with MPLS
  uint64_t pktsIslMpls;           //!< Number of packets with ISL and MPLS
  uint64_t pktsVlanMpls;          //!< Number of packets with VLAN and MPLS
  uint64_t pktsIslVlanMpls;       //!< Number of packets with ISL, VLAN and MPLS
};

/**
 * Statistics for each port
 */
struct NtPortStatistics_s {
  /**
   * Valid indicators. These indicate which counters are supported by the port.
   */
  struct NtPortStatisticsValid_s {
    int RMON1;   //!< Is set if RMON1 counters are supported
    int extRMON; //!< Is set if extended RMON counters are supported
    int chksum;  //!< Is set if IP/TCP/UDP checksum counters are supported
    int decode;  //!< Is set if packet decode counters are supported
    int extDrop; //!< Is set if extended drop counters are supported
  } valid;

  struct NtRMON1Counters_s RMON1;          //!< RMON1 counters
  struct NtExtendedRMONCounters_s extRMON; //!< Extended RMON counters
  struct NtCheckSumCounters_s chksum;      //!< Checksum error counters
  struct NtDecodeCounters_s decode;        //!< Packets decoded by onboard packet decoder
  struct NtExtendedDropCounters_s extDrop; //!< Extended drop counters
};

/**
 * Statistics info group for port statistics
 */
struct NtStatGroupPort_s {
  struct NtPortStatistics_s rx;   //!< Counters based on RX ports
  struct NtPortStatistics_s tx;   //!< Counters based on TX ports
  uint64_t linkDownCounter;       //!< Counts number of link downs

  uint64_t ts;                    //!< Port counter sample time stamp
  enum NtTimestampType_e tsType;  //!< Time stamp type
};

struct NtStatisticsQuery_s {
  int poll; //!< Gets the current statistical information or waits for a new update
  int clear; //!< Clears the statistical information after it has been read. All statistics counters for the current stream will be cleared. Other statistics streams will remain untouched.
  /**
   * Data section holding the statistic counters
   */
  struct NtStatisticsQueryResult_s {
    /**
     * Port specific statistics
     */
    struct NtStatisticsQueryPortResult_s {
      uint8_t numPorts;                     //!< Number of ports in @ref aPorts
      uint8_t Reserved1[3];
      struct NtStatGroupPort_s aPorts[64];  //!< Array of port statistic structures in the system
    } port;
    /**
     * Adapter specific statistics
     */
    struct NtStatisticsQueryAdapterResult_s {
      uint8_t numAdapters;                        //!< Number of adapters in @ref aAdapters
      uint8_t Reserved1[3];
      struct NtStatGroupAdapter_s aAdapters[10];  //!< Array of adapter statistic structures
    } adapter;
  } data;                               //!< Structure for statistic results
};

/********************************************************************************/
/*       Statistics data defines for NT_STATISTICS_READ_CMD_QUERY_V1            */
/********************************************************************************/
#define NT_STATISTICS_READ_CMD_QUERY_V1 NT_STATISTICS_READ_CMD_COMPAT_1

/**
 * Statistics for each port
 */
struct NtPortStatistics_v1_s {
  /**
   * Valid indicators - these indicate which counters are supported by the port
   */
  struct NtPortStatisticsValid_v1_s {
    int RMON1;   //!< Is set if RMON1 counters are supported
    int extRMON; //!< Is set if extended RMON counters are supported
    int chksum;  //!< Is set if IP/TCP/UDP checksum counters are supported
    int decode;  //!< Is set if packet decode counters are supported
    int extDrop; //!< Is set if extended drop counters are supported
    int ipf;     //!< Is set if IP fragment table counters are supported
  } valid;

  struct NtRMON1Counters_s RMON1;          //!< RMON1 counters
  struct NtExtendedRMONCounters_s extRMON; //!< Extended RMON counters
  struct NtCheckSumCounters_s chksum;      //!< Checksum error counters
  struct NtDecodeCounters_s decode;        //!< Packets decoded by onboard packet decoder
  struct NtExtendedDropCounters_s extDrop; //!< Extended drop counters
  struct NtIpFragTableCounters_s  ipf;     //!< IP fragment table counters (when using IPFMode)
};

/**
 * Statistics info group for port statistics
 */
struct NtStatGroupport_v1_s {
  struct NtPortStatistics_v1_s rx;   //!< Counters based on RX ports
  struct NtPortStatistics_v1_s tx;   //!< Counters based on TX ports
  uint64_t linkDownCounter;          //!< Counts number of link downs
  uint64_t ts;                       //!< Port counter sample time stamp. The format of the timestamp is specified by @ref tsType.
  enum NtTimestampType_e tsType;     //!< Time stamp type - For a description of the time stamp type see "DN-0384 3GD Time-Stamping and Time Synchronization User Guide"
};


struct NtStatisticsQuery_v1_s {
  int poll; //!< Gets the current statistical information or waits for a new update
  int clear; //!< Clears the statistical information after it has been read. All statistics counters for the current stream will be cleared. Other statistics streams will remain untouched.
  /**
   * Data section holding the statistic counters
   */
  struct NtStatisticsQueryResult_v1_s {
    /**
     * Port specific statistics
     */
    struct NtStatisticsQueryPortResult_v1_s {
      uint8_t numPorts;                    //!< Number of ports in @ref aPorts
      uint8_t Reserved1[3];
      struct NtStatGroupport_v1_s aPorts[64];  //!< Array of port statistic structures in the system
    } port;
    /**
     * Adapter specific statistics
     */
    struct NtStatisticsQueryAdapterResult_v1_s {
      uint8_t numAdapters;                       //!< Number of adapters in @ref aAdapters
      uint8_t Reserved1[3];
      struct NtStatGroupAdapter_s aAdapters[10];  //!< Array of adapter statistic structures
    } adapter;
  } data;                               //!< Structure for statistic results
};


/********************************************************************************/
/*       Statistics data defines for NT_STATISTICS_READ_CMD_QUERY_V2            */
/********************************************************************************/
#define NT_STATISTICS_READ_CMD_QUERY_V2 NT_STATISTICS_READ_CMD_COMPAT_2

struct NtStatisticsQuery_v2_s {
  int poll; //!< Gets the current statistical information or waits for a new update
  int clear; //!< Clears the statistical information after it has been read. All statistics counters for the current stream will be cleared. Other statistics streams will remain untouched.
  /**
   * Data section holding the statistic counters
   */
  struct NtStatisticsQueryResult_v2_s {
    /**
     * Port specific statistics
     */
    struct NtStatisticsQueryPortResult_v2_s {
      uint8_t numPorts;                    //!< Number of ports in @ref aPorts
      uint8_t Reserved1[3];
//

      struct NtStatGroupport_v1_s aPorts[64];  //!< Array of port statistic structures in the system
//

    } port;
    /**
     * Adapter specific statistics
     */
    struct NtStatisticsQueryAdapterResult_v2_s {
      uint8_t numAdapters;                       //!< Number of adapters in @ref aAdapters
      uint8_t Reserved1[3];
      struct NtStatGroupAdapter_s aAdapters[10];  //!< Array of adapter statistic structures
    } adapter;
    /**
     * Stream specific statistics
     */
    struct NtStatGroupStream_s stream;
  } data;                                         //!< Structure for statistic results
};

#endif /* _NT_NTAPI_NO_COMPAT */
#endif /* __STREAM_STATISTICS_COMPAT_H__ */
