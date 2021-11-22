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
 * This source file contains the NT_DYN dynamic packet descriptor base.\n
 * It is <b>not</b> to be used directly but via the @ref PacketMacros.
 */

/** @addtogroup PacketDescriptor
 *
 * This is a new class of descriptors that offer more flexibility and less overhead
 * than the legacy NT and extended descriptors.
 * The descriptors provide several offset fields that can be programmed via. NTPL as
 * well as an extended color field that allow for more color and hash bits.
 *
 * Unlike the legacy descriptors, dynamic descriptor fields are accessed directly
 * through the c-struct by obtaining a pointer to it from @ref NtNetBuf_s and the
 * NT_NET_DESCR_PTR_DYN\<X\> macros.
 *
 * <b>NOTE:</b> The <i>rxPort</i> field indicates the adapter relative port the packet
 * was received on. To get the absolute port number, @ref NtNetBuf_s.portOffset should
 * be manually added.
 *
 * <b>NOTE:</b> The format of the "timestamp" field in the dynamic descriptors is dependent
 * upon what is configured in the ini-file setting "TimestampFormat". For a description
 * of the possible formats see @ref NtTimestampType_e
 */

#ifndef DOXYGEN_INTERNAL_ONLY

#ifndef __PKT_DESCR_DYN_H__
#define __PKT_DESCR_DYN_H__

// Ensure that the following is packed.
#pragma pack(push, 1)

typedef struct NtDynDescr_s {
  uint64_t capLength:14;    /*  0: The length of the packet incl. descriptor.                */
  uint64_t unused0:34;      /* 14: To be used for acceleration fields.                       */
  uint64_t descrFormat:8;   /* 48: The variable descriptor format.                           */
  uint64_t descrLength:6;   /* 56: The length of the descriptor in bytes.                    */
  uint64_t unused1:1;       /* 62: To be used for acceleration fields.                       */
  uint64_t ntDynDescr:1;    /* 63: Set to 1 to identify this descriptor as a dynamic         */
} NtDynDescr_t;

// Disable 1-byte packing
#pragma pack(pop)


#define _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)                ((NtDynDescr_t*)(_hNetBuf_)->hHdr)

//
// Getters
//
#define _NT_NET_GET_PKT_CAP_LENGTH_DYN(_hNetBuf_)               (_NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->capLength)
#define _NT_NET_GET_PKT_DESCR_FORMAT_DYN(_hNetBuf_)             (_NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrFormat)
// descrLength == 0 means descriptor length is 64
#define _NT_NET_GET_PKT_DESCR_LENGTH_DYN(_hNetBuf_)             ((64&(_NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrLength-1)) + _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrLength)
#define _NT_NET_GET_PKT_DYN_DESCR_DYN(_hNetBuf_)                (_NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->ntDynDescr)
// The timestamp is stored in the same bits for each of the current 4 dynamic descriptors
#define _NT_NET_GET_PKT_TIMESTAMP_DYN(_hNetBuf_)                (_NT_NET_GET_PKT_DESCR_PTR_DYN1(_hNetBuf_)->timestamp)

//
// Setters
//
#define _NT_NET_SET_PKT_CAP_LENGTH_NOALIGN_DYN(_hNetBuf_,_val_) do{_NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->capLength=\
                                                                (uint16_t)((_NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrLength+(_val_))&0x3FFF);}while(0)
#define _NT_NET_SET_PKT_DESCR_FORMAT_DYN(_hNetBuf_, _val_)      do{_NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrFormat=(_val_);}while(0)
// descrLength == 0 means descriptor length is 64
#define _NT_NET_SET_PKT_DESCR_LENGTH_DYN(_hNetBuf_, _val_)      do{_NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrLength=(_val_);}while(0)
#define _NT_NET_SET_PKT_DYN_DESCR_DYN(_hNetBuf_, _val_)         do{_NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->ntDynDescr=(_val_);}while(0)
// The timestamp is stored in the same bits for each of the current 4 dynamic descriptors
#define _NT_NET_SET_PKT_TIMESTAMP_DYN(_hNetBuf_, _val_)         do{_NT_NET_GET_PKT_DESCR_PTR_DYN1(_hNetBuf_)->timestamp=(_val_);}while(0)

#endif // __PKT_DESCR_VAR_H__
#endif // DOXYGEN_INTERNAL_ONLY
