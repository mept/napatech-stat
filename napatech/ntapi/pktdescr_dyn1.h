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
 * This source file contains the NT_DYN1 variable packet descriptor.\n
 */

#ifndef __PKT_DESCR_DYN1_H__
#define __PKT_DESCR_DYN1_H__

/** @addtogroup PacketDescriptorDyn1
 * @{
 *
 * This descriptor offers 3 dynamic offsets, IP protocol field and a 6-bit color field.
 * The packet descriptor is suited for applications doing NetFlow and IDS. <br/>
 * Note: The wireLength field has been sacrificed so in case of slicing the
 * original packet length is unknown.
 */

// Ensure that the following is packed.
#pragma pack(push, 1)

/**
 *  @brief NT Variable descriptor 1
 */
typedef struct NtDyn1Descr_s {
  uint64_t capLength:14;    /**< The length of the packet incl. descriptor.                         */ /*  0*/
  uint64_t offset0:10;      /**< Programmable offset into the packet. Default is outer L3.          */ /* 14*/
  uint64_t offset1:10;      /**< Programmable offset into the packet. Default is outer L4.          */ /* 24*/
  uint64_t ipProtocol:8;    /**< Select-able IP protocol. Default is outer IP Protocol field.       */ /* 34*/
  uint64_t rxPort:6;        /**< The port that received the frame.                                  */ /* 42*/
  uint64_t descrFormat:8;   /**< The descriptor type.                                               */ /* 48*/
  uint64_t descrLength:6;   /**< The length of the descriptor in bytes.                             */ /* 56*/
  uint64_t tsColor:1;       /**< Timestamp color. Reserved for future use.                          */ /* 62*/
  uint64_t ntDynDescr:1;    /**< Set to 1 to identify this descriptor as a dynamic descriptor.      */ /* 63*/
  uint64_t timestamp;       /**< The time of arrival of the packet.                                 */ /* 64*/
  uint16_t offset2:10;      /**< Programmable offset into the packet. Default is outer L4 payload.  */ /*128*/
  uint16_t color:6;         /**< Programmable packet color.                                         */ /*138*/
} NtDyn1Descr_t; // descrFormat = 1, descrLength = 18  /*144 bits*/

// Disable 1-byte packing
#pragma pack(pop)

#ifndef DOXYGEN_INTERNAL_ONLY


#define _NT_NET_GET_PKT_DESCR_PTR_DYN1(_hNetBuf_)       ((NtDyn1Descr_t*)(_hNetBuf_)->hHdr)


#ifdef DEBUG
//Guards against misconfigurations
#ifdef _MSC_VER
static void __nt_dyn1_check__(void);
#else
static void __nt_dyn1_check__(void) __attribute__ ((unused));
#endif
static void __nt_dyn1_check__(void) {
  //Compile-time check to avoid sizeof(NtDyn1Descr_t) != 18
  switch (0) { case 0: case sizeof (NtDyn1Descr_t) == 18: ; }
}
#endif // DEBUG

#endif // DOXYGEN_INTERNAL_ONLY

/** @} */

#endif // __PKT_DESCR_DYN1_H__
