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
 * This source file contains the NT_DYN3 variable packet descriptor.\n
 */

#ifndef __PKT_DESCR_DYN3_H__
#define __PKT_DESCR_DYN3_H__

/** @addtogroup PacketDescriptorDyn3
 * @{
 *
 * This descriptor is suited for TX and includes the wire length as well as color bits
 * in the first 8 bytes of the descriptor. This allows SW to reduce the frame size before
 * TX by modifying the wire length and it allows reduction of the descriptor length down
 * to only 8 bytes while retaining the possibility to encode TX flags such as txIgnore in
 * the color. The default values for the dynamic parts are:
 *
 *    offset0 = outer L3\n
 *    offset1 = outer L4
 *
 *    descrFormat = 3\n
 *    descrLength = 22
 *
 */

// Ensure that the following is packed.
#pragma pack(push, 1)

/**
 *  @brief NT Variable descriptor 3
 */
typedef struct NtDyn3Descr_s {
  uint64_t capLength:14;    /**< The length of the packet incl. descriptor.     */ /*  0*/
  uint64_t wireLength:14;   /**< The wire length of the packet.                 */ /* 14*/
  uint64_t color_lo:14;     /**< Programmable packet color[13:0].               */ /* 28*/
  uint64_t rxPort:6;        /**< The port that received the frame.              */ /* 42*/
  uint64_t descrFormat:8;   /**< The descriptor type.                           */ /* 48*/
  uint64_t descrLength:6;   /**< The length of the descriptor in bytes.         */ /* 56*/
  uint64_t tsColor:1;       /**< Timestamp color. Reserved for future use.      */ /* 62*/
  uint64_t ntDynDescr:1;    /**< Set to 1 to identify this descriptor as a      */ /* 63*/
                            /**< dynamic descriptor.                            */
  uint64_t timestamp;       /**< The time of arrival of the packet.             */ /* 64*/
  uint64_t color_hi:28;     /**< Programmable packet color[41:14].              */ /*128*/
  uint64_t offset0:10;      /**< Programmable offset into the packet.           */ /*156*/
  uint64_t offset1:10;      /**< Programmable offset into the packet.           */ /*166*/
} NtDyn3Descr_t; // descrFormat = 3, descrLength = 22 /*176 bits*/

// Disable 1-byte packing
#pragma pack(pop)

#ifndef DOXYGEN_INTERNAL_ONLY


#define _NT_NET_GET_PKT_DESCR_PTR_DYN3(_hNetBuf_)       ((NtDyn3Descr_t*)(_hNetBuf_)->hHdr)


#ifdef DEBUG
//Guards against misconfigurations
#ifdef _MSC_VER
static void __nt_dyn3_check__(void);
#else
static void __nt_dyn3_check__(void) __attribute__ ((unused));
#endif
static void __nt_dyn3_check__(void) {
  //Compile-time check to avoid sizeof(NtDyn3Descr_t) != 22
#ifndef WIN32
  switch (0) { case 0: case sizeof (NtDyn3Descr_t) == 22: ; }
#endif
}
#endif // DEBUG

#endif // DOXYGEN_INTERNAL_ONLY

/** @} */

#endif // __PKT_DESCR_DYN3_H__
