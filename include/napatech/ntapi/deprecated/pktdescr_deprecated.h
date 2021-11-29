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
 * This source file contains legacy macros. Bug corrections should not be performed
 * in this file; instead, help users to use newer API functions.\n
 * It is <b>not</b> to be used directly but via the @ref PacketMacros.
 */

#ifndef DOXYGEN_INTERNAL_ONLY

#ifndef __PKT_DESCR_DEPRECATED_H__
#define __PKT_DESCR_DEPRECATED_H__

#include "napatech/ntapi/pktdescr.h"

//
// Internal macros to create compiler messages and warnings
//
#if defined( __clang__ )
#define _NT_DO_PRAGMA(S)            _Pragma(#S)
#define _NT_GET_COMPILE_MESSAGE(S)  _NT_DO_PRAGMA(message S)
#define _NT_GET_COMPILE_WARNING(S)  _NT_DO_PRAGMA(warning S)
#define _NT_SET_COMPILE_MESSAGE(S)  _NT_DO_PRAGMA(message S)
#define _NT_SET_COMPILE_WARNING(S)  _NT_DO_PRAGMA(warning S)
#elif defined( __GNUC__ )
#define _NT_DO_PRAGMA(S)            _Pragma(#S)
#define _NT_GET_COMPILE_MESSAGE(S)  // No gcc support :(
#define _NT_GET_COMPILE_WARNING(S)  _NT_DO_PRAGMA(GCC warning S)
#define _NT_SET_COMPILE_MESSAGE(S)  _NT_DO_PRAGMA(message S)
#define _NT_SET_COMPILE_WARNING(S)  _NT_DO_PRAGMA(GCC warning S)
#elif defined( _MSC_VER )
#define _NT_DO_PRAGMA(S)            __pragma(S)
#define _NT_GET_COMPILE_MESSAGE(S)  _NT_DO_PRAGMA(message S)
#define _NT_GET_COMPILE_WARNING(S)  _NT_DO_PRAGMA(warning S)
#define _NT_SET_COMPILE_MESSAGE(S)  _NT_DO_PRAGMA(message S)
#define _NT_SET_COMPILE_WARNING(S)  _NT_DO_PRAGMA(warning S)
#else
#endif

#ifdef NT_DISABLE_LEGACY_MACRO_MESSAGES
#define _NT_LEGACY_GET_MACRO_MESSAGE(...)
#define _NT_LEGACY_SET_MACRO_MESSAGE(...)
#else
#define _NT_LEGACY_GET_MACRO_MESSAGE(OLD, NEW) \
  _NT_GET_COMPILE_MESSAGE("\n" #OLD " is a legacy macro.\nIt is recommended to use " #NEW " instead.\n" \
    "To simply disable this message, define NT_DISABLE_LEGACY_MACRO_MESSAGES before including nt.h")
#define _NT_LEGACY_SET_MACRO_MESSAGE(OLD, NEW) \
  _NT_SET_COMPILE_MESSAGE("\n" #OLD " is a legacy macro.\nIt is recommended to use " #NEW " instead.\n" \
    "To simply disable this message, define NT_DISABLE_LEGACY_MACRO_MESSAGES before including nt.h")
#endif


//
// Users are encouraged to use macros to get a pointer to the specific macros,
// rather than the union of all descriptors.
//

// Ensure that the following is packed.
#pragma pack(push, 1)

typedef union {
  NtStd0Descr_t std0; //!< Standard descriptor v0
  NtExt7Descr_t ext7; //!< Only valid for extended descriptor format 7
  NtExt8Descr_t ext8; //!< Only valid for extended descriptor format 8
  NtExt9Descr_t ext9; //!< Only valid for extended descriptor format 9
  NtDyn3Descr_t dyn3; //!< Only valid for dynamic descriptor format 3
} NtPktDescr_t;

// Disable 1-byte packing
#pragma pack(pop)


//
// Legacy general descriptor macros
//
#define NT_NET_GET_PKT_DESCRIPTOR_TYPE(_hNetBuf_) \
  NT_NET_GET_PKT_DESCR_TYPE(_hNetBuf_)

#define NT_NET_GET_PKT_DESCR_PTR(_hNetBuf_)             ((NtPktDescr_t*)(_hNetBuf_)->hHdr)

#define NT_DESCR_NT_LENGTH  (sizeof(NtStd0Descr_t))

#define NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)     NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)

#define NT_NET_SET_PKT_CLEAR_DESCR_NT(_hNetBuf_)       NT_NET_SET_PKT_CLEAR_DESCR_STD(_hNetBuf_)
#define NT_NET_SET_PKT_DESCR_TYPE_NT(_hNetBuf_)        NT_NET_SET_PKT_DESCR_TYPE_STD(_hNetBuf_)

//
// Checking NT_NET_DESCR_PTR_DYN
//
#define NT_NET_DESCR_PTR_DYN1(_hNetBuf_) \
  ((_NT_NET_GET_PKT_DESCR_PTR_DYN1(_hNetBuf_)->descrFormat==1 ? \
  (NtDyn1Descr_t*)(_hNetBuf_->hHdr) : (NtDyn1Descr_t*)_NT_NET_DESCR_CAST_ASSERT(NULL)))

#define NT_NET_DESCR_PTR_DYN2(_hNetBuf_) \
  ((_NT_NET_GET_PKT_DESCR_PTR_DYN2(_hNetBuf_)->descrFormat==2 ? \
  (NtDyn2Descr_t*)(_hNetBuf_->hHdr) : (NtDyn2Descr_t*)_NT_NET_DESCR_CAST_ASSERT(NULL)))

#define NT_NET_DESCR_PTR_DYN3(_hNetBuf_) \
  ((_NT_NET_GET_PKT_DESCR_PTR_DYN3(_hNetBuf_)->descrFormat==3 ? \
  (NtDyn3Descr_t*)(_hNetBuf_->hHdr) : (NtDyn3Descr_t*)_NT_NET_DESCR_CAST_ASSERT(NULL)))

#define NT_NET_DESCR_PTR_DYN4(_hNetBuf_) \
  ((_NT_NET_GET_PKT_DESCR_PTR_DYN4(_hNetBuf_)->descrFormat==4 ? \
  (NtDyn4Descr_t*)(_hNetBuf_->hHdr) : (NtDyn4Descr_t*)_NT_NET_DESCR_CAST_ASSERT(NULL)))


//
// _NT_NTAPI_NO_COMPAT macros
//
#if !defined(_NT_NTAPI_NO_COMPAT)
#define NT_NET_GET_PKT_DESCR(_hNetBuf_) \
  NT_NET_GET_PKT_DESCR_PTR(_hNetBuf_)
#endif

#if !defined(_NT_NTAPI_NO_COMPAT)
#define NT_NET_GET_PKT_CALC_L2_CRC(_hNetBuf_) \
  NT_NET_GET_PKT_RECALC_L2_CRC(_hNetBuf_)
#endif

#if !defined(_NT_NTAPI_NO_COMPAT)
#define NT_NET_GET_PKT_PROT_SMALL(_hNetBuf_) \
  NT_NET_GET_PKT_DECODE_ERROR(_hNetBuf_)
#endif

#if !defined(_NT_NTAPI_NO_COMPAT)
#define NT_NET_SET_PKT_CALC_L2_CRC(_hNetBuf_, _bval_) \
  NT_NET_SET_PKT_RECALC_L2_CRC(_hNetBuf_, _bval_)
#endif

#if !defined(_NT_NTAPI_NO_COMPAT)
#define NT_NET_SET_PKT_L3_OFFSET(_hNetBuf_, _offset_)  _NT_SET_COMPILE_WARNING("NT_NET_SET_PKT_L3_OFFSET is not supported.")
#define NT_NET_SET_PKT_L4_OFFSET(_hNetBuf_, _offset_)  _NT_SET_COMPILE_WARNING("NT_NET_SET_PKT_L4_OFFSET is not supported.")
#endif


//
// Wire length
//
#define NT_NET_GET_PKT_WIRE_LENGTH(_hNetBuf_)                                  \
  ((uint16_t)(_NT_NET_GET_PKT_DYN_DESCR(_hNetBuf_) == 1 ?                      \
                _NT_NET_GET_PKT_WIRE_LENGTH_DYN(_hNetBuf_) :                   \
                _NT_NET_GET_PKT_WIRE_LENGTH_NT(_hNetBuf_)))

#define _NT_NET_GET_PKT_WIRE_LENGTH_DYN(_hNetBuf_) \
  (uint16_t)(_NT_NET_GET_PKT_CAP_LENGTH_DYN(_hNetBuf_) -\
    _NT_NET_GET_PKT_DESCR_LENGTH_DYN(_hNetBuf_))


//
// Capture length
//
#define NT_NET_SET_PKT_CAP_LENGTH(_hNetBuf_, _Length_) \
  _NT_NET_SET_PKT_CAP_LENGTH_ALIGN(_hNetBuf_, _Length_)

#define _NT_NET_SET_PKT_CAP_LENGTH_ALIGN(_hNetBuf_,_Length_) \
  do{ if(_NT_NET_GET_PKT_DYN_DESCR(_hNetBuf_) == 1) \
    _NT_NET_SET_PKT_CAP_LENGTH_NOALIGN_DYN(_hNetBuf_,_Length_); \
    else _NT_NET_SET_PKT_CAP_LENGTH_ALIGN_NT(_hNetBuf_,_Length_); } while(0)


//
// NT macros
//
#define NT_NET_GET_PKT_CRC_ERROR(_hNetBuf_)              NT_NET_GET_PKT_CRC_ERROR_NT(_hNetBuf_)
#define NT_NET_GET_PKT_TCP_CSUM_OK(_hNetBuf_)            NT_NET_GET_PKT_TCP_CSUM_OK_NT(_hNetBuf_)
#define NT_NET_GET_PKT_UDP_CSUM_OK(_hNetBuf_)            NT_NET_GET_PKT_UDP_CSUM_OK_NT(_hNetBuf_)
#define NT_NET_GET_PKT_IP_CSUM_OK(_hNetBuf_)             NT_NET_GET_PKT_IP_CSUM_OK_NT(_hNetBuf_)
#define NT_NET_GET_PKT_CV_ERROR(_hNetBuf_)               NT_NET_GET_PKT_CV_ERROR_NT(_hNetBuf_)
#define NT_NET_GET_PKT_SLICED(_hNetBuf_)                 NT_NET_GET_PKT_SLICED_NT(_hNetBuf_)
#define NT_NET_GET_PKT_HARD_SLICED(_hNetBuf_)            NT_NET_GET_PKT_HARD_SLICED_NT(_hNetBuf_)
#define NT_NET_GET_PKT_RXPORT(_hNetBuf_)                 NT_NET_GET_PKT_RXPORT_NT(_hNetBuf_)
#define NT_NET_GET_PKT_IS_TCP(_hNetBuf_)                 NT_NET_GET_PKT_IS_TCP_NT(_hNetBuf_)
#define NT_NET_GET_PKT_IS_UDP(_hNetBuf_)                 NT_NET_GET_PKT_IS_UDP_NT(_hNetBuf_)
#define NT_NET_GET_PKT_IS_IP(_hNetBuf_)                  NT_NET_GET_PKT_IS_IP_NT(_hNetBuf_)
#define NT_NET_GET_PKT_TXPORT(_hNetBuf_)                 NT_NET_GET_PKT_TXPORT_NT(_hNetBuf_)
#define NT_NET_GET_PKT_RECALC_L2_CRC(_hNetBuf_)          NT_NET_GET_PKT_RECALC_L2_CRC_NT(_hNetBuf_)
#define NT_NET_GET_PKT_TXNOW(_hNetBuf_)                  NT_NET_GET_PKT_TXNOW_NT(_hNetBuf_)
#define NT_NET_GET_PKT_TXIGNORE(_hNetBuf_)               NT_NET_GET_PKT_TXIGNORE_NT(_hNetBuf_)

#define NT_NET_SET_PKT_WIRE_LENGTH(_hNetBuf_, _Length_)  NT_NET_SET_PKT_WIRE_LENGTH_NT(_hNetBuf_, _Length_)
#define NT_NET_SET_PKT_CRC_ERROR(_hNetBuf_, _bval_)      NT_NET_SET_PKT_CRC_ERROR_NT(_hNetBuf_, _bval_)
#define NT_NET_SET_PKT_TCP_CSUM_OK(_hNetBuf_, _bval_)    NT_NET_SET_PKT_TCP_CSUM_OK_NT(_hNetBuf_, _bval_)
#define NT_NET_SET_PKT_UDP_CSUM_OK(_hNetBuf_, _bval_)    NT_NET_SET_PKT_UDP_CSUM_OK_NT(_hNetBuf_, _bval_)
#define NT_NET_SET_PKT_IP_CSUM_OK(_hNetBuf_, _bval_)     NT_NET_SET_PKT_IP_CSUM_OK_NT(_hNetBuf_, _bval_)
#define NT_NET_SET_PKT_IS_TCP(_hNetBuf_, _bval_)         NT_NET_SET_PKT_IS_TCP_NT(_hNetBuf_, _bval_)
#define NT_NET_SET_PKT_IS_UDP(_hNetBuf_, _bval_)         NT_NET_SET_PKT_IS_UDP_NT(_hNetBuf_, _bval_)
#define NT_NET_SET_PKT_IS_IP(_hNetBuf_, _bval_)          NT_NET_SET_PKT_IS_IP_NT(_hNetBuf_, _bval_)
#define NT_NET_SET_PKT_TXPORT(_hNetBuf_, _Port_)         NT_NET_SET_PKT_TXPORT_NT(_hNetBuf_, _Port_)
#define NT_NET_SET_PKT_RECALC_L2_CRC(_hNetBuf_, _bval_)  NT_NET_SET_PKT_RECALC_L2_CRC_NT(_hNetBuf_, _bval_)
#define NT_NET_SET_PKT_TXNOW(_hNetBuf_, _bval_)          NT_NET_SET_PKT_TXNOW_NT(_hNetBuf_, _bval_)
#define NT_NET_SET_PKT_TXIGNORE(_hNetBuf_, _bval_)       NT_NET_SET_PKT_TXIGNORE_NT(_hNetBuf_, _bval_)
#define NT_NET_SET_PKT_TXSETCLOCK(_hNetBuf_, _bval_)     NT_NET_SET_PKT_TXSETCLOCK_NT(_hNetBuf_, _bval_)


//
// EXT macros
//
#define NT_NET_GET_PKT_HASH(_hNetBuf_)             NT_NET_GET_PKT_HASH_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_HASH_TYPE(_hNetBuf_)        NT_NET_GET_PKT_HASH_TYPE_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_HASH_VALID(_hNetBuf_)       NT_NET_GET_PKT_HASH_VALID_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_JUMBO(_hNetBuf_)            NT_NET_GET_PKT_JUMBO_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_BROADCAST(_hNetBuf_)        NT_NET_GET_PKT_BROADCAST_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_L4_PORT_TYPE(_hNetBuf_)     NT_NET_GET_PKT_L4_PORT_TYPE_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_L4_FRAME_TYPE(_hNetBuf_)    NT_NET_GET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_L3_FRAME_TYPE(_hNetBuf_)    NT_NET_GET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_L2_FRAME_TYPE(_hNetBuf_)    NT_NET_GET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_L4_LENGTH(_hNetBuf_)        NT_NET_GET_PKT_L4_LENGTH_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_L3_LENGTH(_hNetBuf_)        NT_NET_GET_PKT_L3_LENGTH_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_MPLS_COUNT(_hNetBuf_)       NT_NET_GET_PKT_MPLS_COUNT_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_VLAN_COUNT(_hNetBuf_)       NT_NET_GET_PKT_VLAN_COUNT_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_ISL(_hNetBuf_)              NT_NET_GET_PKT_ISL_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_DECODE_ERROR(_hNetBuf_)     NT_NET_GET_PKT_DECODE_ERROR_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_FRAME_LARGE(_hNetBuf_)      NT_NET_GET_PKT_FRAME_LARGE_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_FRAME_SMALL(_hNetBuf_)      NT_NET_GET_PKT_FRAME_SMALL_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_IPV6_FR_HEADER(_hNetBuf_)   NT_NET_GET_PKT_IPV6_FR_HEADER_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_IPV6_RT_HEADER(_hNetBuf_)   NT_NET_GET_PKT_IPV6_RT_HEADER_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_L4_PROTOCOL_NUM(_hNetBuf_)  NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_L3_FRAGMENTED(_hNetBuf_)    NT_NET_GET_PKT_L3_FRAGMENTED_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_L3_FIRST_FRAG(_hNetBuf_)    NT_NET_GET_PKT_L3_FIRST_FRAG_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_COLOR(_hNetBuf_)            NT_NET_GET_PKT_COLOR_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_L5_OFFSET(_hNetBuf_)        NT_NET_GET_PKT_L5_OFFSET_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_L4_OFFSET(_hNetBuf_)        NT_NET_GET_PKT_L4_OFFSET_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_L3_OFFSET(_hNetBuf_)        NT_NET_GET_PKT_L3_OFFSET_EXT(_hNetBuf_)

#define NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID(_hNetBuf_)      NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_IPF_UNMATCHED_FLAG(_hNetBuf_)          NT_NET_GET_PKT_IPF_UNMATCHED_FLAG_EXT(_hNetBuf_)
#define NT_NET_GET_PKT_IPF_LAST_FRAGMENT(_hNetBuf_)           NT_NET_GET_PKT_IPF_LAST_FRAGMENT_EXT(_hNetBuf_)
#define NT_NET_SET_PKT_INJECT_TIMESTAMP(_hNetBuf_, _offset_)  NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT(_hNetBuf_, _offset_)
#define NT_NET_SET_PKT_ISL(_hNetBuf_, _bval_)                 NT_NET_SET_PKT_ISL_EXT(_hNetBuf_, _bval_)
#define NT_NET_SET_PKT_VLAN_COUNT(_hNetBuf_, _count_)         NT_NET_SET_PKT_VLAN_COUNT_EXT(_hNetBuf_, _count_)
#define NT_NET_SET_PKT_MPLS_COUNT(_hNetBuf_, _count_)         NT_NET_SET_PKT_MPLS_COUNT_EXT(_hNetBuf_, _count_)
#define NT_NET_SET_PKT_L2_FRAME_TYPE(_hNetBuf_, _type_)       NT_NET_SET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_, _type_)
#define NT_NET_SET_PKT_L3_FRAME_TYPE(_hNetBuf_, _type_)       NT_NET_SET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_, _type_)
#define NT_NET_SET_PKT_L4_FRAME_TYPE(_hNetBuf_, _type_)       NT_NET_SET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_, _type_)
#define NT_NET_SET_PKT_L3_LENGTH(_hNetBuf_, _u32len_)         NT_NET_SET_PKT_L3_LENGTH_EXT(_hNetBuf_, _u32len_)
#define NT_NET_SET_PKT_L4_LENGTH(_hNetBuf_, _u32len_)         NT_NET_SET_PKT_L4_LENGTH_EXT(_hNetBuf_, _u32len_)
#define NT_NET_SET_PKT_CALC_L3_CHECKSUM(_hNetBuf_, _bval_)    NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT(_hNetBuf_, _bval_)
#define NT_NET_SET_PKT_CALC_L4_CHECKSUM(_hNetBuf_, _bval_)    NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT(_hNetBuf_, _bval_)
#define NT_NET_GET_PKT_INNER_L3_OFFSET(_hNetBuf_)             NT_NET_GET_PKT_INNER_L3_OFFSET_EXT9(_hNetBuf_)
#define NT_NET_GET_PKT_INNER_L4_OFFSET(_hNetBuf_)             NT_NET_GET_PKT_INNER_L4_OFFSET_EXT9(_hNetBuf_)
#define NT_NET_GET_PKT_INNER_L5_OFFSET(_hNetBuf_)             NT_NET_GET_PKT_INNER_L5_OFFSET_EXT9(_hNetBuf_)
#define NT_NET_GET_PKT_INNER_L3_FRAME_TYPE(_hNetBuf_)         NT_NET_GET_PKT_INNER_L3_FRAME_TYPE_EXT9(_hNetBuf_)
#define NT_NET_GET_PKT_INNER_L4_FRAME_TYPE(_hNetBuf_)         NT_NET_GET_PKT_INNER_L4_FRAME_TYPE_EXT9(_hNetBuf_)
#define NT_NET_GET_PKT_INNER_L3_FRAGMENT_TYPE(_hNetBuf_)      NT_NET_GET_PKT_INNER_L3_FRAGMENT_TYPE_EXT9(_hNetBuf_)
#define NT_NET_GET_PKT_TUNNEL_TYPE(_hNetBuf_)                 NT_NET_GET_PKT_TUNNEL_TYPE_EXT9(_hNetBuf_)
#define NT_NET_GET_PKT_TUNNEL_HDR_LENGTH(_hNetBuf_)           NT_NET_GET_PKT_TUNNEL_HDR_LENGTH_EXT9(_hNetBuf_)
#define NT_NET_GET_PKT_INNER_DECODE_ERROR(_hNetBuf_)          NT_NET_GET_PKT_INNER_DECODE_ERROR_EXT9(_hNetBuf_)
#define NT_NET_GET_PKT_DEDUPLICATION_CRC(_hNetBuf_)           NT_NET_GET_PKT_DEDUPLICATION_CRC_EXT9(_hNetBuf_)

#endif // __PKT_DESCR_DEPRECATED_H__

#endif // DOXYGEN_INTERNAL_ONLY
