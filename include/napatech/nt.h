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
 * This header file contain everything presented by the NTAPI and is the only
 * header file that needs to be included in tools/applications.
 */
#ifndef __NT_H__
#define __NT_H__

#ifdef WIN32
#include <winsock2.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "napatech/ntapi/commontypes.h"
#include "napatech/ntapi/errorcodes.h"
#include "napatech/ntapi/pktdescr.h"
#include "napatech/ntapi/stream_statistics.h"
#include "napatech/ntapi/stream_config.h"
#include "napatech/ntapi/stream_event.h"
#include "napatech/ntapi/stream_net.h"
#include "napatech/ntapi/stream_info.h"
#include "napatech/ntapi/stream_flow.h"
#include "napatech/ntapi/version.h"
#include "napatech/ntapi/ntapi.h"

#include "napatech/ntapi/deprecated/pktdescr_deprecated.h"

#ifdef __cplusplus
}
#endif

#endif // __NT_H__
