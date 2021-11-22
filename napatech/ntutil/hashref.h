/*
 *
 * Copyright 2021 Napatech A/S. All Rights Reserved.
 *
 * 1. Copying, modification, and distribution of this file, or executable
 * versions of this file, is governed by the terms of the Napatech Software
 * license agreement under which this file was made available. If you do not
 * agree to the terms of the license do not install, copy, access or
 * otherwise use this file.
 *
 * 2. Under the Napatech Software license agreement you are granted a
 * limited, non-exclusive, non-assignable, copyright license to copy, modify
 * and distribute this file in conjunction with Napatech SmartNIC's and
 * similar hardware manufactured or supplied by Napatech A/S.
 *
 * 3. The full Napatech Software license agreement is included in this
 * distribution, please see "NP-0405 Napatech Software license
 * agreement.pdf"
 *
 * 4. Redistributions of source code must retain this copyright notice,
 * list of conditions and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTIES, EXPRESS OR
 * IMPLIED, AND NAPATECH DISCLAIMS ALL IMPLIED WARRANTIES INCLUDING ANY
 * IMPLIED WARRANTY OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, OR OF
 * FITNESS FOR A PARTICULAR PURPOSE. TO THE EXTENT NOT PROHIBITED BY
 * APPLICABLE LAW, IN NO EVENT SHALL NAPATECH BE LIABLE FOR PERSONAL INJURY,
 * OR ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF PROFITS, CORRUPTION OR
 * LOSS OF DATA, FAILURE TO TRANSMIT OR RECEIVE ANY DATA OR INFORMATION,
 * BUSINESS INTERRUPTION OR ANY OTHER COMMERCIAL DAMAGES OR LOSSES, ARISING
 * OUT OF OR RELATED TO YOUR USE OR INABILITY TO USE NAPATECH SOFTWARE OR
 * SERVICES OR ANY THIRD PARTY SOFTWARE OR APPLICATIONS IN CONJUNCTION WITH
 * THE NAPATECH SOFTWARE OR SERVICES, HOWEVER CAUSED, REGARDLESS OF THE THEORY
 * OF LIABILITY (CONTRACT, TORT OR OTHERWISE) AND EVEN IF NAPATECH HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. SOME JURISDICTIONS DO NOT ALLOW
 * THE EXCLUSION OR LIMITATION OF LIABILITY FOR PERSONAL INJURY, OR OF
 * INCIDENTAL OR CONSEQUENTIAL DAMAGES, SO THIS LIMITATION MAY NOT APPLY TO YOU.
 *
 *

 */

/**
 * @file
 *
 * This header file contains the interface to the hash reference library.
 *
 */
#ifndef __HASHREF_H__
#define __HASHREF_H__

#include "nt.h"

/**
 * Available hash modes
 */
enum NtHashRefHashMode_e {
  NT_HASHREF_HASHMODE_UNDEFINED = 0,
  NT_HASHREF_HASHMODE_LAST_MPLS_LABEL,         //!< Hash Key Type 2: Last MPLS Label
  NT_HASHREF_HASHMODE_ALL_MPLS_LABELS,         //!< Hash Key Type 3: All MPLS Labels
  NT_HASHREF_HASHMODE_2_TUPLE,                 //!< Hash Key Type 4: 2-Tuple
  NT_HASHREF_HASHMODE_2_TUPLE_SORTED,          //!< Hash Key Type 5: 2-Tuple Sorted
  NT_HASHREF_HASHMODE_LAST_VLAN_ID,            //!< Hash Key Type 6: Last VLAN ID
  NT_HASHREF_HASHMODE_ALL_VLAN_IDS,            //!< Hash Key Type 7: All VLAN IDs
  NT_HASHREF_HASHMODE_5_TUPLE,                 //!< Hash Key Type 8: 5-Tuple
  NT_HASHREF_HASHMODE_5_TUPLE_SORTED,          //!< Hash Key Type 9: 5-Tuple Sorted
  NT_HASHREF_HASHMODE_3_TUPLE_GRE_V0,          //!< Hash Key Type 10: 3-Tuple GREv0
  NT_HASHREF_HASHMODE_3_TUPLE_GRE_V0_SORTED,   //!< Hash Key Type 11: 3-Tuple GREv0 Sorted
  NT_HASHREF_HASHMODE_5_TUPLE_SCTP,            //!< Hash Key Type 12: 5-Tuple SCTP
  NT_HASHREF_HASHMODE_5_TUPLE_SCTP_SORTED,     //!< Hash Key Type 13: 5-Tuple SCTP Sorted
  NT_HASHREF_HASHMODE_INNER_2_TUPLE,           //!< Hash Key Type 14 for PCIe Gen2 Adapters: Inner 2-Tuple
  NT_HASHREF_HASHMODE_3_TUPLE_GTP_V0,          //!< Hash Key Type 14 for PCIe Gen1 Adapters: 3-Tuple GTPv0
  NT_HASHREF_HASHMODE_INNER_2_TUPLE_SORTED,    //!< Hash Key Type 15 for PCIe Gen2 Adapters: Inner 2-Tuple Sorted
  NT_HASHREF_HASHMODE_3_TUPLE_GTP_V0_SORTED,   //!< Hash Key Type 15 for PCIe Gen1 Adapters: 3-Tuple GTPv0 Sorted
  NT_HASHREF_HASHMODE_INNER_5_TUPLE,           //!< Hash Key Type 16 for PCIe Gen2 Adapters: Inner 5-Tuple
  NT_HASHREF_HASHMODE_3_TUPLE_GTP_V1V2,        //!< Hash Key Type 16 for PCIe Gen1 Adapters: 3-Tuple GTPv1/GTPv2
  NT_HASHREF_HASHMODE_INNER_5_TUPLE_SORTED,    //!< Hash Key Type 17 for PCIe Gen2 Adapters: Inner 5-Tuple Sorted
  NT_HASHREF_HASHMODE_3_TUPLE_GTP_V1V2_SORTED, //!< Hash Key Type 17 for PCIe Gen1 Adapters: 3-Tuple GTPv1/GTPv2 Sorted
  NT_HASHREF_HASHMODE_IP_FRAGMENT_TUPLE,       //!< Hash Key Type 30 for PCIe Gen2 Adapters: IP Fragment Tuple
  NT_HASHREF_HASHMODE_LAST
};

/**
 * Hash reference configuration
 */
typedef struct NtHashRefConfig_v0_s {
  enum NtAdapterType_e adapterType; //!< The adapter type
  union Ntfpgaid_u fpgaid;          //!< The FPGA ID of the adapter to emulate in the hash value calculation
  enum NtHashRefHashMode_e hashmode;//!< The hash mode to use, see @ref ::NtHashRefHashMode_e for available hash modes
  uint32_t hashmask[10];            //!< Hash mask - default in NTPL is 0xFFFFFFFF for all hash words.
  uint32_t streams;                 //!< Number of streams to distribute to
  uint32_t seed;                    //!< Hash seed as defined in ntservice.ini. Default is 0xFFFFFFFF
} NtHashRefConfig_v0_t;

/**
 * Hash reference configuration versions
 */
enum NtHashRefConfig_e {
  NT_HASHREF_CONFIG_UNDEFINED = 0,
  NT_HASHREF_CONFIG_V0,             //!< Use hash reference configuration @ref ::NtHashRefConfig_v0_t
  NT_HASHREF_CONFIG_LAST
};

/**
 * Hash reference configuration
 */
typedef struct NtHashRefConfig_s {
  enum NtHashRefConfig_e config;    //!< Configuration version to use
  union NtHashRefConfig_u {
    NtHashRefConfig_v0_t config_v0; //!< Hash reference configuration version 0
  } u;
} NtHashRefConfig_t;


enum NtHashRefInputType_e {
  NT_HASHREF_INPUT_TYPE_UNDEFINED = 0,
  NT_HASHREF_INPUT_TYPE_LAST_MPLS_LABEL,
  NT_HASHREF_INPUT_TYPE_ALL_MPLS_LABELS,
  NT_HASHREF_INPUT_TYPE_TUPLE_2_IP_V4,
  NT_HASHREF_INPUT_TYPE_TUPLE_2_IP_V6,
  NT_HASHREF_INPUT_TYPE_LAST_VLAN_ID,
  NT_HASHREF_INPUT_TYPE_ALL_VLAN_IDS,
  NT_HASHREF_INPUT_TYPE_TUPLE_5_IP_V4,
  NT_HASHREF_INPUT_TYPE_TUPLE_5_IP_V6,
  NT_HASHREF_INPUT_TYPE_TUPLE_3_GRE_V0_IP_V4,
  NT_HASHREF_INPUT_TYPE_TUPLE_3_GRE_V0_IP_V6,
  NT_HASHREF_INPUT_TYPE_TUPLE_5_SCTP_IP_V4,
  NT_HASHREF_INPUT_TYPE_TUPLE_5_SCTP_IP_V6,
  NT_HASHREF_INPUT_TYPE_IP_FRAGMENT_TUPLE_IP_V4,
  NT_HASHREF_INPUT_TYPE_IP_FRAGMENT_TUPLE_IP_V6,
  NT_HASHREF_INPUT_TYPE_TUPLE_3_GTP_V0_IP_V4,
  NT_HASHREF_INPUT_TYPE_TUPLE_3_GTP_V0_IP_V6,
  NT_HASHREF_INPUT_TYPE_TUPLE_3_GTP_V1_V2_IP_V4,
  NT_HASHREF_INPUT_TYPE_TUPLE_3_GTP_V1_V2_IP_V6,
  NT_HASHREF_INPUT_TYPE_LAST
};

/**
 * Hash calculation input
 */
typedef struct {
  /**
   * hashref input union
   */
  enum NtHashRefInputType_e inputType; /* Denotes the used structure */
  union NtHashRefInput_u {
    struct NtLastMplsLabel_s {
      uint32_t label;         //!< 20-bit MPLS label
    } lastMplsLabel;
    struct NtAllMplsLabels_s {
      uint32_t label[7];      //!< 20-bit MPLS label
    } allMplsLabels;
    struct NtTuple2IPv4_s {
      uint32_t srcIP;         //!< 32-bit IPv4 address in network order
      uint32_t dstIP;         //!< 32-bit IPv4 address in network order
    } tuple2IPv4;
    struct NtTuple2IPv6_s {
      uint8_t srcIP[16];      //!< 128-bit IPv6 address in network order
      uint8_t dstIP[16];      //!< 128-bit IPv6 address in network order
    } tuple2IPv6;
    struct NtLastVlanId_s {
      uint16_t vlanId;        //!< 12-bit VLAN Id in network order
    } lastVlanId;
    struct NtAllVlanIds_s {
      uint16_t vlanId[3];     //!< 12-bit VLAN Id in network order
    } allVlanIds;
    struct NtTuple5IPv4_s {
      uint32_t srcIP;         //!< 32-bit IPv4 address in network order
      uint32_t dstIP;         //!< 32-bit IPv4 address in network order
      uint16_t srcPort;       //!< 16-bit port number in network order
      uint16_t dstPort;       //!< 16-bit port number in network order
      uint8_t  protocol;      //!< 8-bit IP protocol number
    } tuple5IPv4;
    struct NtTuple5IPv6_s {
      uint8_t  srcIP[16];     //!< 128-bit IPv6 address in network order
      uint8_t  dstIP[16];     //!< 128-bit IPv6 address in network order
      uint16_t srcPort;       //!< 16-bit port number in network order
      uint16_t dstPort;       //!< 16-bit port number in network order
      uint8_t  protocol;      //!< 8-bit IP protocol number
    } tuple5IPv6;
    struct NtTuple3GREv0IPv4_s {
      uint32_t srcIP;         //!< 32-bit IPv4 address in network order
      uint32_t dstIP;         //!< 32-bit IPv4 address in network order
      uint32_t key;           //!< 32-bit GRE key in network order
    } tuple3GREv0IPv4;
    struct NtTuple3GREv0IPv6_s {
      uint8_t  srcIP[16];     //!< 128-bit IPv6 address in network order
      uint8_t  dstIP[16];     //!< 128-bit IPv6 address in network order
      uint32_t key;           //!< 32-bit GRE key in network order
    } tuple3GREv0IPv6;
    struct NtTuple5SCTPIPv4_s {
      uint32_t srcIP;         //!< 32-bit IPv4 address in network order
      uint32_t dstIP;         //!< 32-bit IPv4 address in network order
      uint16_t srcPort;       //!< 16-bit port number in network order
      uint16_t dstPort;       //!< 16-bit port number in network order
      uint32_t verificationTag;//!< 32-bit verification tag in network order
    } tuple5SCTPIPv4;
    struct NtTuple5SCTPIPv6_s{
      uint8_t  srcIP[16];     //!< 128-bit IPv6 address in network order
      uint8_t  dstIP[16];     //!< 128-bit IPv6 address in network order
      uint16_t srcPort;       //!< 16-bit port number in network order
      uint16_t dstPort;       //!< 16-bit port number in network order
      uint32_t verificationTag;//!< 32-bit verification tag in network order
    } tuple5SCTPIPv6;
    struct NtIpFragmentTupleIPv4_s {
      uint32_t srcIP;         //!< 32-bit IPv4 address in network order
      uint32_t dstIP;         //!< 32-bit IPv4 address in network order
      uint16_t ipId;          //!< 16-bit IP identifier in network order
      uint8_t  ipProt;        //!< 8-bit IP protocol number
    } ipFragmentTupleIPv4;
    struct NtIpFragmentTupleIPv6_s {
      uint8_t  srcIP[16];     //!< 128-bit IPv6 address in network order
      uint8_t  dstIP[16];     //!< 128-bit IPv6 address in network order
      uint32_t id;            //!< 32-bit fragment identifier
    } ipFragmentTupleIPv6;
    struct NtTuple3GTPv0IPv4_s {
      uint32_t srcIP;         //!< 32-bit IPv4 address in network order
      uint32_t dstIP;         //!< 32-bit IPv4 address in network order
      uint16_t flowLabel;     //!< 16-bit flow label in network order
    } tuple3GTPv0IPv4;
    struct NtTuple3GTPv0IPv6_s {
      uint8_t  srcIP[16];     //!< 128-bit IPv6 address in network order
      uint8_t  dstIP[16];     //!< 128-bit IPv6 address in network order
      uint16_t flowLabel;     //!< 16-bit flow label in network order
    } tuple3GTPv0IPv6;
    struct NtTuple3GTPv1v2IPv4_s {
      uint32_t srcIP;         //!< 32-bit IPv4 address in network order
      uint32_t dstIP;         //!< 32-bit IPv4 address in network order
      uint32_t teid;          //!< 32-bit tunnel identifier in network order
    } tuple3GTPv1v2IPv4;
    struct NtTuple3GTPv1v2IPv6_s {
      uint8_t  srcIP[16];     //!< 128-bit IPv6 address in network order
      uint8_t  dstIP[16];     //!< 128-bit IPv6 address in network order
      uint32_t teid;          //!< 32-bit tunnel identifier in network order
    } tuple3GTPv1v2IPv6;
  } u;
} NtHashRefInput_t;

typedef struct NtHashRefResult_s {
  uint32_t hashvalue;       //!< 24-bit calculated hash value
  uint32_t stream;          //!< Destination stream - set if the streams value
                            //!< is non-zero in the hash reference configuration
} NtHashRefResult_t;

/**
 * Hash reference handle
 */
typedef struct NtHashRef_s *NtHashRef_t;
typedef const struct NtHashRef_s *const_NtHashRef_t;

/**
 * @brief Allocate and configure a hash reference handle
 *
 * @param[out] handle      Allocated hash reference handle
 * @param[in] config       Hash reference configuration
 *
 * @retval 0               Success
 * @retval !=0             Error
 */
int NT_HashRefOpen(NtHashRef_t *handle, const NtHashRefConfig_t *config);

/**
 * @brief Calculate hash value
 *
 * This function calculates the hash value based on the configuration
 * associated with the handle and the input given
 *
 * @param[in] handle       Hash reference handle
 * @param[in] input        Input for hash calculation. Must match the selected input type
 * @param[out] result      The result of the hash calculation
 *
 * @retval 0               Success
 * @retval !=0             Error
 */
int NT_HashRefCalc(NtHashRef_t handle, const NtHashRefInput_t *input,
                   NtHashRefResult_t *result);

/**
 * @brief Calculate 32-bit hash value
 *
 * This function calculates the hash value based on the configuration
 * associated with the handle and the input given
 *
 * @param[in] handle       Hash reference handle
 * @param[in] input        Input for hash calculation. Must match the selected input type
 * @param[out] result      The result of the 32-bit hash calculation
 *
 * @retval 0               Success
 * @retval !=0             Error
 */
int NT_HashRefCalcV2(NtHashRef_t handle, const NtHashRefInput_t *input,
                     NtHashRefResult_t *result);

/**
 * @brief Close the hash reference handle and free associated resources
 *
 * @retval 0               Success
 * @retval !=0             Error
 */
int NT_HashRefClose(NtHashRef_t handle);

#endif // __HASHREF_H__
