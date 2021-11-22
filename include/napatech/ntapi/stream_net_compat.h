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
 * This is the header file of the STREAMTYPE_NET interface containing
 * included for backward compatibility structures.
 *
 */
#ifndef __STREAM_NET_COMPAT_H__
#define __STREAM_NET_COMPAT_H__

#if !defined(_NT_NTAPI_NO_COMPAT)

/***********************************************************************************************/
/*                               Net file read version 0                                       */
/***********************************************************************************************/

#define NT_NETFILE_READ_INFO_CMD NT_NETFILE_READ_COMPAT_0

/**
 *  NetFile stream Info return structure
 */

typedef struct NtNetFileReadInfo_s {
  uint64_t lastTimestamp;   //!< The time stamp in the last packet in last the segment read using the function @ref NT_NetFileGet
  uint64_t numberOfOctets;  //!< Number of octets read from Netfile so far
  uint32_t numberOfPackets; //!< Number of packets read from Netfile so far
} NtNetFileInfo_t;

#endif // _NT_NTAPI_NO_COMPAT
#endif // __STREAM_NET_COMPAT_H__
