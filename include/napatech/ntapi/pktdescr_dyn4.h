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
 * This source file contains the NT_DYN4 variable packet descriptor.\n
 */

#ifndef __PKT_DESCR_DYN4_H__
#define __PKT_DESCR_DYN4_H__

/** @addtogroup PacketDescriptorDyn4
 * @{
 *
 * This descriptor provides the option to have the 64-bit correlation key in
 * the color1 field, alternatively (the default) 32-bits color and 32-bits
 * hash value can be provided in color1. The color0 field contains the lower 8
 * bits of the color when the color1 field is used for correlation key,
 * otherwise (the default) color0 contains the outer protocol number
 * The default values for the dynamic parts are:
 *
 *    offset0 = outer L3\n
 *    offset1 = outer L4\n
 *    color0 = outer Protocol / Next Header field\n
 *    color1[31:0] = color value\n
 *    color1[63:32] = hash value\n
 *    descrLength = 24\n
 *
 */

// Ensure that the following is packed.
#pragma pack(push, 1)

/**
 *  @brief NT Variable descriptor 4
 */
typedef struct NtDyn4Descr_s {

  uint64_t capLength:14;    /**< The length of the packet incl. descriptor.                     */ /*  0*/
  uint64_t offset0:10;      /**< Programmable offset into the packet. Default is outer L3.      */ /* 14*/
  uint64_t offset1:10;      /**< Programmable offset into the packet. Default is outer L4.      */ /* 24*/
  uint64_t color0:8;        /**< Programmable packet color[8:0].                                */ /* 34*/
  uint64_t rxPort:6;        /**< The port that received the frame.                              */ /* 42*/
  uint64_t descrFormat:8;   /**< The descriptor type.                                           */ /* 48*/
  uint64_t descrLength:6;   /**< The length of the descriptor in bytes.                         */ /* 56*/
  uint64_t tsColor:1;       /**< Timestamp color. Reserved for future use.                      */ /* 62*/
  uint64_t ntDynDescr:1;    /**< Set to 1 to identify this descriptor as a dynamic descriptor.  */ /* 63*/
  uint64_t timestamp;       /**< The time of arrival of the packet.                             */ /* 64*/
  uint64_t color1;          /**< Programmable packet color[31:0] and hash[63:32].               */ /*128*/

} NtDyn4Descr_t; // descrFormat = 4, default descrLength = 24 /*192 bits*/

// Disable 1-byte packing
#pragma pack(pop)

#ifndef DOXYGEN_INTERNAL_ONLY


#define _NT_NET_GET_PKT_DESCR_PTR_DYN4(_hNetBuf_)       ((NtDyn4Descr_t*)(_hNetBuf_)->hHdr)


#ifdef DEBUG
//Guards against misconfigurations
#ifdef _MSC_VER
static void __nt_dyn4_check__(void);
#else
static void __nt_dyn4_check__(void) __attribute__ ((unused));
#endif
static void __nt_dyn4_check__(void) {
  //Compile-time check to avoid sizeof(NtDyn4Descr_t) != 24
#ifndef WIN32
  switch (0) { case 0: case sizeof (NtDyn4Descr_t) == 24: ; }
#endif
}
#endif // DEBUG

#endif // DOXYGEN_INTERNAL_ONLY

/** @} */

#endif // __PKT_DESCR_DYN4_H__
