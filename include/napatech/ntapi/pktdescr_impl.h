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
 * This source file contains the implementation of the generic packet descriptor macros.\n
 * It is <b>not</b> to be used directly but via the @ref PacketMacros.
 */

#ifndef DOXYGEN_INTERNAL_ONLY

#ifndef __PKT_DESCR_IMPL_H__
#define __PKT_DESCR_IMPL_H__

//
// Determine which, if any, macro optimizations should be used
//
#ifdef _NTAPI_EXTDESCR_7_
#  define NTAPI_OPTIMIZE_FOR_EXT7
#endif

#ifdef _NTAPI_EXTDESCR_8_
#  define NTAPI_OPTIMIZE_FOR_EXT8
#endif

#ifdef _NTAPI_EXTDESCR_9_
#  define NTAPI_OPTIMIZE_FOR_EXT9
#endif

#if defined(NTAPI_OPTIMIZE_FOR_EXT7) || defined(NTAPI_OPTIMIZE_FOR_EXT8) || defined(NTAPI_OPTIMIZE_FOR_EXT9)
#  ifndef NTAPI_OPTIMIZE_FOR_EXT
#    define NTAPI_OPTIMIZE_FOR_EXT
#  endif
#endif

#if defined(NTAPI_OPTIMIZE_FOR_EXT)
#  ifndef NTAPI_OPTIMIZE_FOR_NT
#    define NTAPI_OPTIMIZE_FOR_NT
#  endif
#endif

#if defined(NTAPI_OPTIMIZE_FOR_DYN1) || defined(NTAPI_OPTIMIZE_FOR_DYN2) || defined(NTAPI_OPTIMIZE_FOR_DYN3) || defined(NTAPI_OPTIMIZE_FOR_DYN4)
#  ifndef NTAPI_OPTIMIZE_FOR_DYN
#    define NTAPI_OPTIMIZE_FOR_DYN
#  endif
#endif

#ifdef NTAPI_OPTIMIZE_FOR_EXT7
#  ifdef _NTAPI_SANITY_CHECK_NT_
#    error Cannot optimize for multiple descriptors
#  else
#    define _NTAPI_SANITY_CHECK_NT_
#  endif
#endif

#ifdef NTAPI_OPTIMIZE_FOR_EXT8
#  ifdef _NTAPI_SANITY_CHECK_NT_
#    error Cannot optimize for multiple descriptors
#  else
#    define _NTAPI_SANITY_CHECK_NT_
#  endif
#endif

#ifdef NTAPI_OPTIMIZE_FOR_EXT9
#  ifdef _NTAPI_SANITY_CHECK_NT_
#    error Cannot optimize for multiple descriptors
#  else
#    define _NTAPI_SANITY_CHECK_NT_
#  endif
#endif

#ifdef NTAPI_OPTIMIZE_FOR_DYN1
#  ifdef _NTAPI_SANITY_CHECK_DYN_
#    error Cannot optimize for multiple descriptors
#  else
#    define _NTAPI_SANITY_CHECK_DYN_
#  endif
#endif

#ifdef NTAPI_OPTIMIZE_FOR_DYN2
#  ifdef _NTAPI_SANITY_CHECK_DYN_
#    error Cannot optimize for multiple descriptors
#  else
#    define _NTAPI_SANITY_CHECK_DYN_
#  endif
#endif

#ifdef NTAPI_OPTIMIZE_FOR_DYN3
#  ifdef _NTAPI_SANITY_CHECK_DYN_
#    error Cannot optimize for multiple descriptors
#  else
#    define _NTAPI_SANITY_CHECK_DYN_
#  endif
#endif

#ifdef NTAPI_OPTIMIZE_FOR_DYN4
#  ifdef _NTAPI_SANITY_CHECK_DYN_
#    error Cannot optimize for multiple descriptors
#  else
#    define _NTAPI_SANITY_CHECK_DYN_
#  endif
#endif

#if defined(_NTAPI_SANITY_CHECK_NT_) && defined(_NTAPI_SANITY_CHECK_DYN_)
#  error Cannot optimize for multiple descriptors
#endif


//
//
//
#define _NT_NET_GET_PKT_DYN_DESCR(_hNetBuf_) \
  _NT_NET_GET_PKT_DYN_DESCR_DYN(_hNetBuf_)


//
// Packet pointer
//
#define _NT_NET_GET_PKT_L2_PTR(_hNetBuf_) \
  ((void*)(_hNetBuf_)->hPkt)

#define _NT_NET_UPDATE_PKT_L2_PTR(_hNetBuf_) \
  (((_hNetBuf_)->hPkt)=(NtNetBufPkt_t)((uint8_t*)((_hNetBuf_)->hHdr)+_NT_NET_GET_PKT_DESCR_LENGTH(_hNetBuf_)))


//
// Type
//
// The only branching macro that is not optimized by define NTAPI_OPTIMIZE_FOR_XXXX
//
#define _NT_NET_GET_PKT_DESCR_TYPE(_hNetBuf_) \
  (_NT_NET_GET_PKT_DYN_DESCR(_hNetBuf_) == 1 ? \
    NT_PACKET_DESCRIPTOR_TYPE_DYNAMIC : \
    _NT_NET_GET_PKT_NT_DESCR_TYPE_NT(_hNetBuf_))

#define _NT_NET_GET_PKT_NT_DESCR_TYPE_NT(_hNetBuf_) \
  ((_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->descriptorType == 0) ? \
    NT_PACKET_DESCRIPTOR_TYPE_PCAP : \
    ((_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionFormat == 0 ? \
      NT_PACKET_DESCRIPTOR_TYPE_NT : \
      NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED)))


//
// Time-stamp
//
#define _NT_NET_GET_PKT_TIMESTAMP_TYPE(_hNetBuf_) \
  ((_hNetBuf_)->tsType)

#if defined(NTAPI_OPTIMIZE_FOR_NT)

#define _NT_NET_GET_PKT_TIMESTAMP(_hNetBuf_) \
  (_NT_NET_GET_PKT_TIMESTAMP_NT(_hNetBuf_))

#define _NT_NET_SET_PKT_TIMESTAMP(_hNetBuf_, _val_) \
  do{ _NT_NET_SET_PKT_TIMESTAMP_NT(_hNetBuf_,_val_); } while(0)

#elif defined(NTAPI_OPTIMIZE_FOR_DYN)

#define _NT_NET_GET_PKT_TIMESTAMP(_hNetBuf_) \
  (_NT_NET_GET_PKT_TIMESTAMP_DYN(_hNetBuf_))

#define _NT_NET_SET_PKT_TIMESTAMP(_hNetBuf_, _val_) \
  do{ _NT_NET_SET_PKT_TIMESTAMP_DYN(_hNetBuf_,_val_); } while(0)

#else

#define _NT_NET_GET_PKT_TIMESTAMP(_hNetBuf_) \
  (_NT_NET_GET_PKT_DYN_DESCR(_hNetBuf_) == 1 ? \
    _NT_NET_GET_PKT_TIMESTAMP_DYN(_hNetBuf_) : \
    _NT_NET_GET_PKT_TIMESTAMP_NT(_hNetBuf_))

#define _NT_NET_SET_PKT_TIMESTAMP(_hNetBuf_, _val_) \
  do{ if(_NT_NET_GET_PKT_DYN_DESCR(_hNetBuf_) == 1) \
    _NT_NET_SET_PKT_TIMESTAMP_DYN(_hNetBuf_,_val_); \
    else _NT_NET_SET_PKT_TIMESTAMP_NT(_hNetBuf_,_val_); } while(0)

#endif


//
// Format
//
#if defined(NTAPI_OPTIMIZE_FOR_NT)

#define _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_) \
  (_NT_NET_GET_PKT_DESCR_FORMAT_NT(_hNetBuf_))

#elif defined(NTAPI_OPTIMIZE_FOR_DYN)

#define _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_) \
  (_NT_NET_GET_PKT_DESCR_FORMAT_DYN(_hNetBuf_))

#else

#define _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_) \
  (_NT_NET_GET_PKT_DYN_DESCR(_hNetBuf_) == 1 ? \
    _NT_NET_GET_PKT_DESCR_FORMAT_DYN(_hNetBuf_) : \
    _NT_NET_GET_PKT_DESCR_FORMAT_NT(_hNetBuf_))

#endif


//
// Length
//
#if defined(NTAPI_OPTIMIZE_FOR_NT)

#define _NT_NET_GET_PKT_DESCR_LENGTH(_hNetBuf_) \
  (_NT_NET_GET_PKT_DESCR_LENGTH_NT(_hNetBuf_))

#elif defined(NTAPI_OPTIMIZE_FOR_DYN)

#define _NT_NET_GET_PKT_DESCR_LENGTH(_hNetBuf_) \
  (_NT_NET_GET_PKT_DESCR_LENGTH_DYN(_hNetBuf_))

#else

#define _NT_NET_GET_PKT_DESCR_LENGTH(_hNetBuf_) \
  (_NT_NET_GET_PKT_DYN_DESCR(_hNetBuf_) == 1 ? \
    _NT_NET_GET_PKT_DESCR_LENGTH_DYN(_hNetBuf_) : \
    _NT_NET_GET_PKT_DESCR_LENGTH_NT(_hNetBuf_))

#endif


//
// Capture length
//
#if defined(NTAPI_OPTIMIZE_FOR_NT)

#define _NT_NET_GET_PKT_CAP_LENGTH(_hNetBuf_) \
  (_NT_NET_GET_PKT_CAP_LENGTH_NT(_hNetBuf_))

#define _NT_NET_SET_PKT_CAP_LENGTH_NOALIGN(_hNetBuf_,_Length_) \
  do{ _NT_NET_SET_PKT_CAP_LENGTH_NOALIGN_NT(_hNetBuf_,_Length_); } while(0)

#elif defined(NTAPI_OPTIMIZE_FOR_DYN)

#define _NT_NET_GET_PKT_CAP_LENGTH(_hNetBuf_) \
  (_NT_NET_GET_PKT_CAP_LENGTH_DYN(_hNetBuf_))

#define _NT_NET_SET_PKT_CAP_LENGTH_NOALIGN(_hNetBuf_,_Length_) \
  do{ _NT_NET_SET_PKT_CAP_LENGTH_NOALIGN_DYN(_hNetBuf_,_Length_); } while(0)

#else

#define _NT_NET_GET_PKT_CAP_LENGTH(_hNetBuf_) \
  (_NT_NET_GET_PKT_DYN_DESCR(_hNetBuf_) == 1 ? \
    _NT_NET_GET_PKT_CAP_LENGTH_DYN(_hNetBuf_) : \
    _NT_NET_GET_PKT_CAP_LENGTH_NT(_hNetBuf_))

#define _NT_NET_SET_PKT_CAP_LENGTH_NOALIGN(_hNetBuf_,_Length_) \
  do{ if(_NT_NET_GET_PKT_DYN_DESCR(_hNetBuf_) == 1) \
    _NT_NET_SET_PKT_CAP_LENGTH_NOALIGN_DYN(_hNetBuf_,_Length_); \
    else _NT_NET_SET_PKT_CAP_LENGTH_NOALIGN_NT(_hNetBuf_,_Length_); } while(0)

#endif


//
// EXT macros
//
#if defined(NTAPI_OPTIMIZE_FOR_EXT7)

#define _NT_NET_GET_PKT_HASH_EXT(_hNetBuf_)             _NT_NET_GET_PKT_HASH_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_HASH_TYPE_EXT(_hNetBuf_)        _NT_NET_GET_PKT_HASH_TYPE_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_HASH_VALID_EXT(_hNetBuf_)       _NT_NET_GET_PKT_HASH_VALID_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_JUMBO_EXT(_hNetBuf_)            _NT_NET_GET_PKT_JUMBO_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_BROADCAST_EXT(_hNetBuf_)        _NT_NET_GET_PKT_BROADCAST_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_PORT_TYPE_EXT(_hNetBuf_)     _NT_NET_GET_PKT_L4_PORT_TYPE_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_)    _NT_NET_GET_PKT_L4_FRAME_TYPE_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_)    _NT_NET_GET_PKT_L3_FRAME_TYPE_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_)    _NT_NET_GET_PKT_L2_FRAME_TYPE_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_LENGTH_EXT(_hNetBuf_)        _NT_NET_GET_PKT_L4_LENGTH_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_LENGTH_EXT(_hNetBuf_)        _NT_NET_GET_PKT_L3_LENGTH_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_MPLS_COUNT_EXT(_hNetBuf_)       _NT_NET_GET_PKT_MPLS_COUNT_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_VLAN_COUNT_EXT(_hNetBuf_)       _NT_NET_GET_PKT_VLAN_COUNT_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_ISL_EXT(_hNetBuf_)              _NT_NET_GET_PKT_ISL_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_DECODE_ERROR_EXT(_hNetBuf_)     _NT_NET_GET_PKT_DECODE_ERROR_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_PROT_SMAL_EXTL(_hNetBuf_)       _NT_NET_GET_PKT_DECODE_ERROR_EXT7(_hNetBuf_) // Deprecated - use NT_NET_GET_PKT_DECODE_ERROR
#define _NT_NET_GET_PKT_FRAME_LARGE_EXT(_hNetBuf_)      _NT_NET_GET_PKT_FRAME_LARGE_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_FRAME_SMALL_EXT(_hNetBuf_)      _NT_NET_GET_PKT_FRAME_SMALL_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_IPV6_FR_HEADER_EXT(_hNetBuf_)   _NT_NET_GET_PKT_IPV6_FR_HEADER_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_IPV6_RT_HEADER_EXT(_hNetBuf_)   _NT_NET_GET_PKT_IPV6_RT_HEADER_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT(_hNetBuf_)  _NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_FRAGMENTED_EXT(_hNetBuf_)    _NT_NET_GET_PKT_L3_FRAGMENTED_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_FIRST_FRAG_EXT(_hNetBuf_)    _NT_NET_GET_PKT_L3_FIRST_FRAG_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_COLOR_EXT(_hNetBuf_)            _NT_NET_GET_PKT_COLOR_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_L5_OFFSET_EXT(_hNetBuf_)        _NT_NET_GET_PKT_L5_OFFSET_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_OFFSET_EXT(_hNetBuf_)        _NT_NET_GET_PKT_L4_OFFSET_EXT7(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_OFFSET_EXT(_hNetBuf_)        _NT_NET_GET_PKT_L3_OFFSET_EXT7(_hNetBuf_)

#define _NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT(_hNetBuf_, _offset_) _NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT7(_hNetBuf_, _offset_)
#define _NT_NET_SET_PKT_ISL_EXT(_hNetBuf_, _bval_)                _NT_NET_SET_PKT_ISL_EXT7(_hNetBuf_, _bval_)
#define _NT_NET_SET_PKT_VLAN_COUNT_EXT(_hNetBuf_, _count_)        _NT_NET_SET_PKT_VLAN_COUNT_EXT7(_hNetBuf_, _count_)
#define _NT_NET_SET_PKT_MPLS_COUNT_EXT(_hNetBuf_, _count_)        _NT_NET_SET_PKT_MPLS_COUNT_EXT7(_hNetBuf_, _count_)
#define _NT_NET_SET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_, _type_)      _NT_NET_SET_PKT_L2_FRAME_TYPE_EXT7(_hNetBuf_, _type_)
#define _NT_NET_SET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_, _type_)      _NT_NET_SET_PKT_L3_FRAME_TYPE_EXT7(_hNetBuf_, _type_)
#define _NT_NET_SET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_, _type_)      _NT_NET_SET_PKT_L4_FRAME_TYPE_EXT7(_hNetBuf_, _type_)
#define _NT_NET_SET_PKT_L3_LENGTH_EXT(_hNetBuf_, _u32len_)        _NT_NET_SET_PKT_L3_LENGTH_EXT7(_hNetBuf_, _u32len_)
#define _NT_NET_SET_PKT_L4_LENGTH_EXT(_hNetBuf_, _u32len_)        _NT_NET_SET_PKT_L4_LENGTH_EXT7(_hNetBuf_, _u32len_)
#define _NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT(_hNetBuf_, _bval_)   _NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT7(_hNetBuf_, _bval_)
#define _NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT(_hNetBuf_, _bval_)   _NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT7(_hNetBuf_, _bval_)

#elif defined(NTAPI_OPTIMIZE_FOR_EXT8)

#define _NT_NET_GET_PKT_HASH_EXT(_hNetBuf_)                   _NT_NET_GET_PKT_HASH_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_HASH_TYPE_EXT(_hNetBuf_)              _NT_NET_GET_PKT_HASH_TYPE_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_HASH_VALID_EXT(_hNetBuf_)             _NT_NET_GET_PKT_HASH_VALID_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_JUMBO_EXT(_hNetBuf_)                  _NT_NET_GET_PKT_JUMBO_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_BROADCAST_EXT(_hNetBuf_)              _NT_NET_GET_PKT_BROADCAST_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_PORT_TYPE_EXT(_hNetBuf_)           _NT_NET_GET_PKT_L4_PORT_TYPE_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_)          _NT_NET_GET_PKT_L4_FRAME_TYPE_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_)          _NT_NET_GET_PKT_L3_FRAME_TYPE_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_)          _NT_NET_GET_PKT_L2_FRAME_TYPE_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_LENGTH_EXT(_hNetBuf_)              _NT_NET_GET_PKT_L4_LENGTH_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_LENGTH_EXT(_hNetBuf_)              _NT_NET_GET_PKT_L3_LENGTH_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_MPLS_COUNT_EXT(_hNetBuf_)             _NT_NET_GET_PKT_MPLS_COUNT_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_VLAN_COUNT_EXT(_hNetBuf_)             _NT_NET_GET_PKT_VLAN_COUNT_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_ISL_EXT(_hNetBuf_)                    _NT_NET_GET_PKT_ISL_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_DECODE_ERROR_EXT(_hNetBuf_)           _NT_NET_GET_PKT_DECODE_ERROR_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_PROT_SMALL_EXT(_hNetBuf_)             _NT_NET_GET_PKT_DECODE_ERROR_EXT8(_hNetBuf_) // Deprecated - use NT_NET_GET_PKT_DECODE_ERROR
#define _NT_NET_GET_PKT_FRAME_LARGE_EXT(_hNetBuf_)            _NT_NET_GET_PKT_FRAME_LARGE_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_FRAME_SMALL_EXT(_hNetBuf_)            _NT_NET_GET_PKT_FRAME_SMALL_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_IPV6_FR_HEADER_EXT(_hNetBuf_)         _NT_NET_GET_PKT_IPV6_FR_HEADER_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_IPV6_RT_HEADER_EXT(_hNetBuf_)         _NT_NET_GET_PKT_IPV6_RT_HEADER_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT(_hNetBuf_)        _NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_FRAGMENTED_EXT(_hNetBuf_)          _NT_NET_GET_PKT_L3_FRAGMENTED_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_FIRST_FRAG_EXT(_hNetBuf_)          _NT_NET_GET_PKT_L3_FIRST_FRAG_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_COLOR_EXT(_hNetBuf_)                  _NT_NET_GET_PKT_COLOR_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_L5_OFFSET_EXT(_hNetBuf_)              _NT_NET_GET_PKT_L5_OFFSET_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_OFFSET_EXT(_hNetBuf_)              _NT_NET_GET_PKT_L4_OFFSET_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_OFFSET_EXT(_hNetBuf_)              _NT_NET_GET_PKT_L3_OFFSET_EXT8(_hNetBuf_)

#define _NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID_EXT(_hNetBuf_) _NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_IPF_UNMATCHED_FLAG_EXT(_hNetBuf_)     _NT_NET_GET_PKT_IPF_UNMATCHED_FLAG_EXT8(_hNetBuf_)
#define _NT_NET_GET_PKT_IPF_LAST_FRAGMENT_EXT(_hNetBuf_)      _NT_NET_GET_PKT_IPF_LAST_FRAGMENT_EXT8(_hNetBuf_)

#define _NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT(_hNetBuf_, _offset_) _NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT8(_hNetBuf_, _offset_)
#define _NT_NET_SET_PKT_ISL_EXT(_hNetBuf_, _bval_)                _NT_NET_SET_PKT_ISL_EXT8(_hNetBuf_, _bval_)
#define _NT_NET_SET_PKT_VLAN_COUNT_EXT(_hNetBuf_, _count_)        _NT_NET_SET_PKT_VLAN_COUNT_EXT8(_hNetBuf_, _count_)
#define _NT_NET_SET_PKT_MPLS_COUNT_EXT(_hNetBuf_, _count_)        _NT_NET_SET_PKT_MPLS_COUNT_EXT8(_hNetBuf_, _count_)
#define _NT_NET_SET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_, _type_)      _NT_NET_SET_PKT_L2_FRAME_TYPE_EXT8(_hNetBuf_, _type_)
#define _NT_NET_SET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_, _type_)      _NT_NET_SET_PKT_L3_FRAME_TYPE_EXT8(_hNetBuf_, _type_)
#define _NT_NET_SET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_, _type_)      _NT_NET_SET_PKT_L4_FRAME_TYPE_EXT8(_hNetBuf_, _type_)
#define _NT_NET_SET_PKT_L3_LENGTH_EXT(_hNetBuf_, _u32len_)        _NT_NET_SET_PKT_L3_LENGTH_EXT8(_hNetBuf_, _u32len_)
#define _NT_NET_SET_PKT_L4_LENGTH_EXT(_hNetBuf_, _u32len_)        _NT_NET_SET_PKT_L4_LENGTH_EXT8(_hNetBuf_, _u32len_)
#define _NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT(_hNetBuf_, _bval_)   _NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT8(_hNetBuf_, _bval_)
#define _NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT(_hNetBuf_, _bval_)   _NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT8(_hNetBuf_, _bval_)

#elif defined(NTAPI_OPTIMIZE_FOR_EXT9)

#define _NT_NET_GET_PKT_HASH_EXT(_hNetBuf_)                   _NT_NET_GET_PKT_HASH_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_HASH_TYPE_EXT(_hNetBuf_)              _NT_NET_GET_PKT_HASH_TYPE_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_HASH_VALID_EXT(_hNetBuf_)             _NT_NET_GET_PKT_HASH_VALID_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_JUMBO_EXT(_hNetBuf_)                  _NT_NET_GET_PKT_JUMBO_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_BROADCAST_EXT(_hNetBuf_)              _NT_NET_GET_PKT_BROADCAST_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_PORT_TYPE_EXT(_hNetBuf_)           _NT_NET_GET_PKT_L4_PORT_TYPE_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_)          _NT_NET_GET_PKT_L4_FRAME_TYPE_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_)          _NT_NET_GET_PKT_L3_FRAME_TYPE_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_)          _NT_NET_GET_PKT_L2_FRAME_TYPE_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_LENGTH_EXT(_hNetBuf_)              _NT_NET_GET_PKT_L4_LENGTH_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_LENGTH_EXT(_hNetBuf_)              _NT_NET_GET_PKT_L3_LENGTH_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_MPLS_COUNT_EXT(_hNetBuf_)             _NT_NET_GET_PKT_MPLS_COUNT_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_VLAN_COUNT_EXT(_hNetBuf_)             _NT_NET_GET_PKT_VLAN_COUNT_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_ISL_EXT(_hNetBuf_)                    _NT_NET_GET_PKT_ISL_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_DECODE_ERROR_EXT(_hNetBuf_)           _NT_NET_GET_PKT_DECODE_ERROR_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_PROT_SMALL_EXT(_hNetBuf_)             _NT_NET_GET_PKT_DECODE_ERROR_EXT9(_hNetBuf_) // Deprecated - use NT_NET_GET_PKT_DECODE_ERROR
#define _NT_NET_GET_PKT_FRAME_LARGE_EXT(_hNetBuf_)            _NT_NET_GET_PKT_FRAME_LARGE_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_FRAME_SMALL_EXT(_hNetBuf_)            _NT_NET_GET_PKT_FRAME_SMALL_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_IPV6_FR_HEADER_EXT(_hNetBuf_)         _NT_NET_GET_PKT_IPV6_FR_HEADER_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_IPV6_RT_HEADER_EXT(_hNetBuf_)         _NT_NET_GET_PKT_IPV6_RT_HEADER_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT(_hNetBuf_)        _NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_FRAGMENTED_EXT(_hNetBuf_)          _NT_NET_GET_PKT_L3_FRAGMENTED_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_FIRST_FRAG_EXT(_hNetBuf_)          _NT_NET_GET_PKT_L3_FIRST_FRAG_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_COLOR_EXT(_hNetBuf_)                  _NT_NET_GET_PKT_COLOR_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_L5_OFFSET_EXT(_hNetBuf_)              _NT_NET_GET_PKT_L5_OFFSET_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_L4_OFFSET_EXT(_hNetBuf_)              _NT_NET_GET_PKT_L4_OFFSET_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_L3_OFFSET_EXT(_hNetBuf_)              _NT_NET_GET_PKT_L3_OFFSET_EXT9(_hNetBuf_)

#define _NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID_EXT(_hNetBuf_) _NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_IPF_UNMATCHED_FLAG_EXT(_hNetBuf_)     _NT_NET_GET_PKT_IPF_UNMATCHED_FLAG_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_IPF_LAST_FRAGMENT_EXT(_hNetBuf_)      _NT_NET_GET_PKT_IPF_LAST_FRAGMENT_EXT9(_hNetBuf_)

#define _NT_NET_GET_PKT_INNER_L3_OFFSET_EXT(_hNetBuf_)        _NT_NET_GET_PKT_INNER_L3_OFFSET_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_INNER_L4_OFFSET_EXT(_hNetBuf_)        _NT_NET_GET_PKT_INNER_L4_OFFSET_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_INNER_L5_OFFSET_EXT(_hNetBuf_)        _NT_NET_GET_PKT_INNER_L5_OFFSET_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_INNER_L3_FRAME_TYPE_EXT(_hNetBuf_)    _NT_NET_GET_PKT_INNER_L3_FRAME_TYPE_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_INNER_L4_FRAME_TYPE_EXT(_hNetBuf_)    _NT_NET_GET_PKT_INNER_L4_FRAME_TYPE_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_INNER_L3_FRAGMENT_TYPE_EXT(_hNetBuf_) _NT_NET_GET_PKT_INNER_L3_FRAGMENT_TYPE_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_TUNNEL_TYPE_EXT(_hNetBuf_)            _NT_NET_GET_PKT_TUNNEL_TYPE_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_TUNNEL_HDR_LENGTH_EXT(_hNetBuf_)      _NT_NET_GET_PKT_TUNNEL_HDR_LENGTH_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_INNER_DECODE_ERROR_EXT(_hNetBuf_)     _NT_NET_GET_PKT_INNER_DECODE_ERROR_EXT9(_hNetBuf_)
#define _NT_NET_GET_PKT_DEDUPLICATION_CRC_EXT(_hNetBuf_)      _NT_NET_GET_PKT_DEDUPLICATION_CRC_EXT9(_hNetBuf_)

#define _NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT(_hNetBuf_, _offset_) _NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT9(_hNetBuf_, _offset_)
#define _NT_NET_SET_PKT_ISL_EXT(_hNetBuf_, _bval_)                _NT_NET_SET_PKT_ISL_EXT9(_hNetBuf_, _bval_)
#define _NT_NET_SET_PKT_VLAN_COUNT_EXT(_hNetBuf_, _count_)        _NT_NET_SET_PKT_VLAN_COUNT_EXT9(_hNetBuf_, _count_)
#define _NT_NET_SET_PKT_MPLS_COUNT_EXT(_hNetBuf_, _count_)        _NT_NET_SET_PKT_MPLS_COUNT_EXT9(_hNetBuf_, _count_)
#define _NT_NET_SET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_, _type_)      _NT_NET_SET_PKT_L2_FRAME_TYPE_EXT9(_hNetBuf_, _type_)
#define _NT_NET_SET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_, _type_)      _NT_NET_SET_PKT_L3_FRAME_TYPE_EXT9(_hNetBuf_, _type_)
#define _NT_NET_SET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_, _type_)      _NT_NET_SET_PKT_L4_FRAME_TYPE_EXT9(_hNetBuf_, _type_)
#define _NT_NET_SET_PKT_L3_LENGTH_EXT(_hNetBuf_, _u32len_)        _NT_NET_SET_PKT_L3_LENGTH_EXT9(_hNetBuf_, _u32len_)
#define _NT_NET_SET_PKT_L4_LENGTH_EXT(_hNetBuf_, _u32len_)        _NT_NET_SET_PKT_L4_LENGTH_EXT9(_hNetBuf_, _u32len_)
#define _NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT(_hNetBuf_, _bval_)   _NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT9(_hNetBuf_, _bval_)
#define _NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT(_hNetBuf_, _bval_)   _NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT9(_hNetBuf_, _bval_)

#else

#define _NT_NET_GET_PKT_HASH_EXT(_hNetBuf_)                                  \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_HASH_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_HASH_TYPE_EXT(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_HASH_TYPE_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_HASH_VALID_EXT(_hNetBuf_)                            \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_HASH_VALID_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_JUMBO_EXT(_hNetBuf_)                                 \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_JUMBO_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_BROADCAST_EXT(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_BROADCAST_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_L4_PORT_TYPE_EXT(_hNetBuf_)                          \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8) ? _NT_NET_GET_PKT_L4_PORT_TYPE_EXT7(_hNetBuf_) : \
   ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ? _NT_NET_GET_PKT_L4_PORT_TYPE_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0U)))

#define _NT_NET_GET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_)                         \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L4_FRAME_TYPE_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_)                         \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L3_FRAME_TYPE_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_)                         \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L2_FRAME_TYPE_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_L4_LENGTH_EXT(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L4_LENGTH_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_L3_LENGTH_EXT(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L3_LENGTH_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_MPLS_COUNT_EXT(_hNetBuf_)                            \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_MPLS_COUNT_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_VLAN_COUNT_EXT(_hNetBuf_)                            \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_VLAN_COUNT_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_ISL_EXT(_hNetBuf_)                                   \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_ISL_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_DECODE_ERROR_EXT(_hNetBuf_)                          \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_DECODE_ERROR_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_FRAME_LARGE_EXT(_hNetBuf_)                           \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_FRAME_LARGE_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_FRAME_SMALL_EXT(_hNetBuf_)                           \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_FRAME_SMALL_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_IPV6_FR_HEADER_EXT(_hNetBuf_)                        \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_IPV6_FR_HEADER_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_IPV6_RT_HEADER_EXT(_hNetBuf_)                        \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_IPV6_RT_HEADER_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT(_hNetBuf_)                       \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_L3_FRAGMENTED_EXT(_hNetBuf_)                         \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L3_FRAGMENTED_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_L3_FIRST_FRAG_EXT(_hNetBuf_)                         \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L3_FIRST_FRAG_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_COLOR_EXT(_hNetBuf_)                                 \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_COLOR_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_L5_OFFSET_EXT(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L5_OFFSET_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_L4_OFFSET_EXT(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L4_OFFSET_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_L3_OFFSET_EXT(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L3_OFFSET_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID_EXT(_hNetBuf_)                \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID_EXT8(_hNetBuf_) : _NT_NET_ASSERT(~0))

#define _NT_NET_GET_PKT_IPF_UNMATCHED_FLAG_EXT(_hNetBuf_)                    \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_IPF_UNMATCHED_FLAG_EXT8(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_IPF_LAST_FRAGMENT_EXT(_hNetBuf_)                     \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_IPF_LAST_FRAGMENT_EXT8(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_INNER_L3_OFFSET_EXT(_hNetBuf_)                       \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_L3_OFFSET_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_INNER_L4_OFFSET_EXT(_hNetBuf_)                       \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_L4_OFFSET_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_INNER_L5_OFFSET_EXT(_hNetBuf_)                       \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_L5_OFFSET_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_INNER_L3_FRAME_TYPE_EXT(_hNetBuf_)                   \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_L3_FRAME_TYPE_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_INNER_L4_FRAME_TYPE_EXT(_hNetBuf_)                   \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_L4_FRAME_TYPE_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_INNER_L3_FRAGMENT_TYPE_EXT(_hNetBuf_)                \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_L3_FRAGMENT_TYPE_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_TUNNEL_TYPE_EXT(_hNetBuf_)                           \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_TUNNEL_TYPE_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_TUNNEL_HDR_LENGTH_EXT(_hNetBuf_)                     \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_TUNNEL_HDR_LENGTH_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_INNER_DECODE_ERROR_EXT(_hNetBuf_)                    \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_DECODE_ERROR_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_GET_PKT_DEDUPLICATION_CRC_EXT(_hNetBuf_)                     \
  ((_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_DEDUPLICATION_CRC_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0U))

#define _NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT(_hNetBuf_, _offset_)            \
    do { if(_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||          \
            _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||          \
            _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9)            \
           _NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT7(_hNetBuf_, _offset_);  \
         else assert(0); } while(0)

#define _NT_NET_SET_PKT_ISL_EXT(_hNetBuf_, _bval_)                           \
    do { if(_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||          \
            _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||          \
            _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9)            \
           _NT_NET_SET_PKT_ISL_EXT7(_hNetBuf_, _bval_);                 \
         else assert(0); } while(0)

#define _NT_NET_SET_PKT_VLAN_COUNT_EXT(_hNetBuf_, _count_)                   \
  do { if(_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_VLAN_COUNT_EXT7(_hNetBuf_, _count_);           \
       else assert(0); } while(0)

#define _NT_NET_SET_PKT_MPLS_COUNT_EXT(_hNetBuf_, _count_)                   \
  do { if(_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_MPLS_COUNT_EXT7(_hNetBuf_, _count_);           \
       else assert(0); } while(0)

#define _NT_NET_SET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_, _type_)                 \
  do { if(_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_L2_FRAME_TYPE_EXT7(_hNetBuf_, _type_);         \
       else assert(0); } while(0)

#define _NT_NET_SET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_, _type_)                 \
  do { if(_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_L3_FRAME_TYPE_EXT7(_hNetBuf_, _type_);         \
       else assert(0); } while(0)

#define _NT_NET_SET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_, _type_)                 \
  do { if(_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_L4_FRAME_TYPE_EXT7(_hNetBuf_, _type_);         \
       else assert(0); } while(0)

#define _NT_NET_SET_PKT_L3_LENGTH_EXT(_hNetBuf_, _u32len_)                   \
  do { if(_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_L3_LENGTH_EXT7(_hNetBuf_, _u32len_);           \
       else assert(0); } while(0)

#define _NT_NET_SET_PKT_L4_LENGTH_EXT(_hNetBuf_, _u32len_)                   \
  do { if(_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_L4_LENGTH_EXT7(_hNetBuf_, _u32len_);           \
       else assert(0); } while(0)

#define _NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT(_hNetBuf_, _bval_)              \
  do { if(_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT7(_hNetBuf_, _bval_);      \
       else assert(0); } while(0)

#define _NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT(_hNetBuf_, _bval_)              \
  do { if(_NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT7(_hNetBuf_, _bval_);      \
       else assert(0); } while(0)

#endif

#endif /* __PKT_DESCR_IMPL_H__ */

#endif // DOXYGEN_INTERNAL_ONLY
