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
 * This header file contains NTAPI function prototypes
 */
#ifndef __NTAPI_H__
#define __NTAPI_H__

/**
 * @brief Initializes the NTAPI library
 *
 * This function <em>must</em> be called prior to any other
 * NTAPI function. It will initialize the NTAPI library and perform
 * compatibility checks based on the version applied.
 * The version is used to indicate to NTAPI what version of the API the
 * application supports and will enable NTAPI to act on this and adapt to that
 * version of the API if possible. This means that if the application is compiled
 * to e.g. version 1 of the API and the current API is version 9, NT_Init will
 * check if it is possible to enable backward compatibility to version 1 and
 * thereby allow the application to run on a version 9 library with version 1 API.
 *
 * @param[in] version  The version that the calling application supports
 *
 * @retval  NT_SUCCESS     Success
 * @retval  !=0            Error
 */
NtError_t NT_Init(uint32_t version);

/**
 * @brief Closes down the NTAPI library
 *
 * @retval  NT_SUCCESS     Success
 */
NtError_t NT_Done(void);

/**
 * @brief Explains an error code returned by NTAPI functions
 *
 * This function will convert the error code to text
 *
 * @param[in]     error  The error code to explain
 * @param[in,out] buf    Location of the explanation
 * @param[in]     buflen The buffer length to prevent buffer overrun. The define @ref NT_ERRBUF_SIZE "NT_ERRBUF_SIZE" should be used as buflen.
 *
 * @retval  A pointer to buf
 */
char *NT_ExplainError(NtError_t error, char *buf, uint32_t buflen);

#endif // __NTAPI_H__
