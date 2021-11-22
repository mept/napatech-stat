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
 * This source file contains the Ext7 packet descriptor.\n
 * It is <b>not</b> to be used directly but via the @ref PacketMacros.
 */

#ifndef DOXYGEN_INTERNAL_ONLY

#ifndef __PKT_DESCR_EXT7_H__
#define __PKT_DESCR_EXT7_H__

// Ensure that the following is packed.
#pragma pack(push, 1)

// Extended descriptor 7 RX
#define _NT_DESCR_EXT7_RX_FIELDS                                                          \
  /* 32bit Word0. */                                                                      \
  uint32_t hash:24;              /* 23:00 - Hash value */                                 \
  uint32_t hashType:5;           /* 28:24 - Hash type */                                  \
  uint32_t Reserved0:2;          /* 30:29 - Reserved */                                   \
  uint32_t hashValid:1;          /*    31 - Hash valid */                                 \
  /* 32bit Word1. */                                                                      \
  uint32_t jumbo:1;              /*    00 - Jumbo frame */                                \
  uint32_t broadcastDest:1;      /*    01 - Destination MAC address is broadcast */       \
  uint32_t l4PortType:4;         /* 05:02 - Layer4 port type */                           \
  uint32_t l4FrameType:4;        /* 09:06 - Layer4 frame type */                          \
  uint32_t l3FrameType:3;        /* 12:10 - Layer3 type */                                \
  uint32_t l2FrameType:2;        /* 14:13 - Layer2 type */                                \
  uint32_t l4Size:4;             /* 18:15 - Layer4 header length (in units of 32 bits) */ \
  uint32_t l3Size:7;             /* 25:19 - Layer3 header length (in units of 32 bits) */ \
  uint32_t mplsCount:3;          /* 28:26 - Number of MPLS shim labels present */         \
  uint32_t vlanCount:2;          /* 30:29 - Number of VLANs present */                    \
  uint32_t islPresent:1;         /*    31 - ISL encapsulation present */                  \
  /* 32bit Word2. */                                                                      \
  uint32_t Reserved1:14;         /* 13:00 - Reserved */                                   \
  uint32_t Reserved2:3;          /* 16:14 - Reserved */                                   \
  uint32_t decodeError:1;        /*    17 - Decode error in Frame. Was "prot. small" */   \
  uint32_t frameLarge:1;         /*    18 - Large frame */                                \
  uint32_t frameSmall:1;         /*    19 - Small frame */                                \
  uint32_t ipv6FragmentHeader:1; /*    20 - IPv6 fragment header present */               \
  uint32_t ipv6RoutingHeader:1;  /*    21 - IPv6 routing header present */                \
  uint32_t l4ProtocolNumber:8;   /* 29:22 - Layer 4 protocol number */                    \
  uint32_t l3Fragmented:1;       /*    30 - L3 fragmented frame */                        \
  uint32_t l3FirstFragment:1;    /*    31 - L3 First fragment */                          \
  /* 32bit Word3. */                                                                      \
  uint32_t color:6;              /* 05:00 - Color */                                      \
  uint32_t Reserved3:1;          /*    06 - Reserved */                                   \
  uint32_t l5Offset:9;           /* 15:07 - Offset to layer 5 */                          \
  uint32_t l4Offset:9;           /* 24:16 - Offset to layer 4 */                          \
  uint32_t l3Offset:7;           /* 31:25 - Offset to layer 3 */

/* Extended descriptor 7 TX */
#define _NT_DESCR_EXT7_TX_FIELDS                                                          \
  /* 32bit Word0. */                                                                      \
  uint32_t Unused0:32;           /* 31:00 - Unused */                                     \
  /* 32bit Word1. */                                                                      \
  uint32_t Unused1:6;            /* 05:00 - Unused */                                     \
  uint32_t l4FrameType:4;        /* 09:06 - Layer4 frame type */                          \
  uint32_t l3FrameType:3;        /* 12:10 - Layer3 type */                                \
  uint32_t l2FrameType:2;        /* 14:13 - Layer2 type */                                \
  uint32_t l4Size:4;             /* 18:15 - Layer4 header length (in units of 32 bits) */ \
  uint32_t l3Size:7;             /* 25:19 - Layer3 header length (in units of 32 bits) */ \
  uint32_t mplsCount:3;          /* 28:26 - Number of MPLS shim labels present */         \
  uint32_t vlanCount:2;          /* 30:29 - Number of VLANs present */                    \
  uint32_t islPresent:1;         /*    31 - ISL encapsulation present */                  \
  /* 32bit Word2. */                                                                      \
  uint32_t Unused2:14;           /* 13:00 - Unused */                                     \
  uint32_t txTsInject:1;         /*    14 - Inject TX time stamp */                       \
  uint32_t calcUDPTCPChecksum:1; /*    15 - Recalculate the UDP/TCP checksum */           \
  uint32_t calcIPChecksum:1;     /*    16 - Recalculate the IP checksum */                \
  uint32_t Unused3:15;           /* 31:17 - Unused */                                     \
  /* 32bit Word3. */                                                                      \
  uint32_t Unused4:7;            /* 06:00 - Unused */                                     \
  uint32_t txTsInjectOffset:9;   /* 15:07 - 15:07 - TX time stamp inject offset */        \
  uint32_t Unused5:16;           /* 31:16 - Unused */

typedef struct NtExt7DescrRx_s {
  _NT_DESCR_STD0_FIELDS
  _NT_DESCR_EXT7_RX_FIELDS
} NtExt7DescrRx_t; // descrLength = 32 /*256 bits*/

typedef struct NtExt7DescrTx_s {
  _NT_DESCR_STD0_FIELDS
  _NT_DESCR_EXT7_TX_FIELDS
} NtExt7DescrTx_t; // descrLength = 32 /*256 bits*/

typedef union {
  NtExt7DescrRx_t rx;
  NtExt7DescrTx_t tx;
} NtExt7Descr_t;

// Disable 1-byte packing
#pragma pack(pop)

#define _NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)       ((NtExt7Descr_t*)(_hNetBuf_)->hHdr)

// RX
#define _NT_NET_GET_PKT_HASH_EXT7(_hNetBuf_)             (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.hash)
#define _NT_NET_GET_PKT_HASH_TYPE_EXT7(_hNetBuf_)        (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.hashType)
#define _NT_NET_GET_PKT_HASH_VALID_EXT7(_hNetBuf_)       (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.hashValid)
#define _NT_NET_GET_PKT_JUMBO_EXT7(_hNetBuf_)            (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.jumbo)
#define _NT_NET_GET_PKT_BROADCAST_EXT7(_hNetBuf_)        (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.broadcastDest)
#define _NT_NET_GET_PKT_L4_PORT_TYPE_EXT7(_hNetBuf_)     (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.l4PortType)
#define _NT_NET_GET_PKT_L4_FRAME_TYPE_EXT7(_hNetBuf_)    (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.l4FrameType)
#define _NT_NET_GET_PKT_L3_FRAME_TYPE_EXT7(_hNetBuf_)    (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.l3FrameType)
#define _NT_NET_GET_PKT_L2_FRAME_TYPE_EXT7(_hNetBuf_)    (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.l2FrameType)
#define _NT_NET_GET_PKT_L4_LENGTH_EXT7(_hNetBuf_)        (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.l4Size)
#define _NT_NET_GET_PKT_L3_LENGTH_EXT7(_hNetBuf_)        (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.l3Size)
#define _NT_NET_GET_PKT_MPLS_COUNT_EXT7(_hNetBuf_)       (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.mplsCount)
#define _NT_NET_GET_PKT_VLAN_COUNT_EXT7(_hNetBuf_)       (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.vlanCount)
#define _NT_NET_GET_PKT_ISL_EXT7(_hNetBuf_)              (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.islPresent)
#define _NT_NET_GET_PKT_DECODE_ERROR_EXT7(_hNetBuf_)     (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.decodeError)
#define _NT_NET_GET_PKT_FRAME_LARGE_EXT7(_hNetBuf_)      (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.frameLarge)
#define _NT_NET_GET_PKT_FRAME_SMALL_EXT7(_hNetBuf_)      (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.frameSmall)
#define _NT_NET_GET_PKT_IPV6_FR_HEADER_EXT7(_hNetBuf_)   (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.ipv6FragmentHeader)
#define _NT_NET_GET_PKT_IPV6_RT_HEADER_EXT7(_hNetBuf_)   (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.ipv6RoutingHeader)
#define _NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT7(_hNetBuf_)  (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.l4ProtocolNumber)
#define _NT_NET_GET_PKT_L3_FRAGMENTED_EXT7(_hNetBuf_)    (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.l3Fragmented)
#define _NT_NET_GET_PKT_L3_FIRST_FRAG_EXT7(_hNetBuf_)    (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.l3FirstFragment)
#define _NT_NET_GET_PKT_COLOR_EXT7(_hNetBuf_)            ((_hNetBuf_)->colorMap[_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.color])
#define _NT_NET_GET_PKT_L5_OFFSET_EXT7(_hNetBuf_)        (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.l5Offset)
#define _NT_NET_GET_PKT_L4_OFFSET_EXT7(_hNetBuf_)        (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.l4Offset)
#define _NT_NET_GET_PKT_L3_OFFSET_EXT7(_hNetBuf_)        (_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->rx.l3Offset)

// TX
#define _NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT7(_hNetBuf_, _offset_) do{_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->tx.txTsInject=1; \
    _NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->tx.txTsInjectOffset=(_offset_);}while(0)
#define _NT_NET_SET_PKT_ISL_EXT7(_hNetBuf_, _bval_)                do{_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->tx.islPresent=(_bval_);}while(0)
#define _NT_NET_SET_PKT_VLAN_COUNT_EXT7(_hNetBuf_, _count_)        do{_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->tx.vlanCount=(_count_);}while(0)
#define _NT_NET_SET_PKT_MPLS_COUNT_EXT7(_hNetBuf_, _count_)        do{_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->tx.mplsCount=(_count_);}while(0)
#define _NT_NET_SET_PKT_L2_FRAME_TYPE_EXT7(_hNetBuf_, _type_)      do{_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->tx.l2FrameType=(_type_);}while(0)
#define _NT_NET_SET_PKT_L3_FRAME_TYPE_EXT7(_hNetBuf_, _type_)      do{_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->tx.l3FrameType=(_type_);}while(0)
#define _NT_NET_SET_PKT_L4_FRAME_TYPE_EXT7(_hNetBuf_, _type_)      do{_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->tx.l4FrameType=(_type_);}while(0)
#define _NT_NET_SET_PKT_L3_LENGTH_EXT7(_hNetBuf_, _u32len_)        do{_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->tx.l3Size=(_u32len_);}while(0)
#define _NT_NET_SET_PKT_L4_LENGTH_EXT7(_hNetBuf_, _u32len_)        do{_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->tx.l4Size=(_u32len_);}while(0)
#define _NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT7(_hNetBuf_, _bval_)   do{_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->tx.calcIPChecksum=(_bval_);}while(0)
#define _NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT7(_hNetBuf_, _bval_)   do{_NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)->tx.calcUDPTCPChecksum=(_bval_);}while(0)

#endif /* __PKT_DESCR_EXT7_H__ */

#endif // DOXYGEN_INTERNAL_ONLY
