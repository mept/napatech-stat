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
 * This source file contains the packet macros available.\n
 * See the @ref PacketMacros for details.
 */

#ifndef __PKT_DESCR_H__
#define __PKT_DESCR_H__

#ifndef DOXYGEN_INTERNAL_ONLY

/* In debug mode add assert to all general RX macros */
#ifdef NDEBUG
#define _NT_NET_ASSERT(x) (x)
#define _NT_NET_DESCR_CAST_ASSERT(x) (x)
#else
#define _NT_NET_ASSERT(x) (assert(0 && "macro argument: unsupported descriptor type"), x)
#define _NT_NET_DESCR_CAST_ASSERT(x) (assert(0 && "descriptor cast error."), x)
#endif

#include "pktdescr_impl.h"
#include "pktdescr_std0.h"
#include "pktdescr_ext7.h"
#include "pktdescr_ext8.h"
#include "pktdescr_ext9.h"
#include "pktdescr_dyn.h"
#include "pktdescr_dyn1.h"
#include "pktdescr_dyn2.h"
#include "pktdescr_dyn3.h"
#include "pktdescr_dyn4.h"

#endif // DOXYGEN_INTERNAL_ONLY

/** @addtogroup DataMacros
 * @{
 */

/** @defgroup PacketMacros Packet macros
 * @{
 * The following is only possible on packet-based streams.
 *
 * Unless specified otherwise, the NT_NET_GET_PKT_XYZ macros will return
 * integer type values.
 *
 * In debug mode some packet macros contain an assert which asserts
 * that the descriptor is supported for a given macro. Define the macro
 * NDEBUG to remove the assert or use the build option -DNDEBUG. When
 * the assert is removed the unsupported descriptors cause macros to return -1.
 *
 * The descriptor support for the various macros is as follows:
 *
 * <table border="1">
 *     <tr>
 *         <th>Macro group</th>
 *         <th>NT</th><th>Ext7</th><th>Ext8</th><th>Ext9</th><th>Dyn</th>
 *     </tr>
 *     <tr><td>Basic descriptor macros</td>
 *         <td> X </td><td> X </td><td> X </td><td> X </td><td> X </td></tr>
 *     <tr><td>NT descriptor macros</td>
 *         <td> X </td><td> X </td><td> X </td><td> X </td><td>   </td></tr>
 *     <tr><td>Extended NT descriptor macros</td>
 *         <td>   </td><td> X </td><td> X </td><td> X </td><td>   </td></tr>
 *     <tr><td>Extended NT descriptor IPF macros</td>
 *         <td>   </td><td>   </td><td> X </td><td> X </td><td>   </td></tr>
 *     <tr><td>Extended NT descriptor Tunneling macros</td>
 *         <td>   </td><td>   </td><td>   </td><td> X </td><td>   </td></tr>
 *     <tr><td>TX macros</td>
 *         <td> X </td><td> X </td><td> X </td><td> X </td><td>   </td></tr>
 * </table>
 *
 * Note that some macros may exist in different variants for each descriptor
 * type. In that case, the supported descriptor is part of the macro name.
 *
 */

/** @defgroup BasicDescriptorMacros Basic descriptor macros
 * @{
 * The following macros are always available.
 */

/** @def NT_DESCR_STD_LENGTH
 *  @brief Constant integer with length of the NT standard descriptor
 *  @hideinitializer
 */
#define NT_DESCR_STD_LENGTH                             (sizeof(NtStd0Descr_t))

/** @def NT_DESCR_EXT7_LENGTH
 *  @brief Length of the NT Extended 7 descriptor
 *  @brief Constant integer with length of the NT Extended 7 descriptor
 *  @hideinitializer
 */
#define NT_DESCR_EXT7_LENGTH                            (sizeof(NtExt7Descr_t))

/** @def NT_DESCR_EXT8_LENGTH
 *  @brief Constant integer with length of the NT Extended 8 descriptor
 *  @hideinitializer
 */
#define NT_DESCR_EXT8_LENGTH                            (sizeof(NtExt8Descr_t))

/** @def NT_DESCR_EXT9_LENGTH
 *  @brief Constant integer with length of the NT Extended 9 descriptor
 *  @hideinitializer
 */
#define NT_DESCR_EXT9_LENGTH                            (sizeof(NtExt9Descr_t))

/** @def NT_DESCR_DYN1_LENGTH
 *  @brief Constant integer with length of the NT Dynamic 1 descriptor
 *  @hideinitializer
 */
#define NT_DESCR_DYN1_LENGTH                            (sizeof(NtDyn1Descr_t))

/** @def NT_DESCR_DYN2_LENGTH
 *  @brief Constant integer with length of the NT Dynamic 2 descriptor
 *  @hideinitializer
 */
#define NT_DESCR_DYN2_LENGTH                            (sizeof(NtDyn2Descr_t))

/** @def NT_DESCR_DYN3_LENGTH
 *  @brief Constant integer with length of the NT Dynamic 3 descriptor
 *  @hideinitializer
 */
#define NT_DESCR_DYN3_LENGTH                            (sizeof(NtDyn3Descr_t))

/** @def NT_DESCR_DYN4_LENGTH
 *  @brief Constant integer with length of the NT Dynamic 4 descriptor
 *  @hideinitializer
 */
#define NT_DESCR_DYN4_LENGTH                            (sizeof(NtDyn4Descr_t))

/** @def NT_NET_SET_PKT_CLEAR_DESCR_STD
 *  @brief Clears the STD descriptor
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CLEAR_DESCR_STD(_hNetBuf_)      do{ memset((_hNetBuf_)->hHdr, 0, sizeof(NtStd0Descr_t)); } while(0)

/** @def NT_NET_SET_PKT_CLEAR_DESCR_EXT7
 *  @brief Clears the EXT7 descriptor
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CLEAR_DESCR_EXT7(_hNetBuf_)     do{ memset((_hNetBuf_)->hHdr, 0, sizeof(NtExt7Descr_t)); } while(0)

/** @def NT_NET_SET_PKT_CLEAR_DESCR_EXT8
 *  @brief Clears the EXT8 descriptor
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CLEAR_DESCR_EXT8(_hNetBuf_)     do{ memset((_hNetBuf_)->hHdr, 0, sizeof(NtExt8Descr_t)); } while(0)

/** @def NT_NET_SET_PKT_CLEAR_DESCR_EXT9
 *  @brief Clears the EXT9 descriptor
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CLEAR_DESCR_EXT9(_hNetBuf_)     do{ memset((_hNetBuf_)->hHdr, 0, sizeof(NtExt9Descr_t)); } while(0)

/** @def NT_NET_SET_PKT_CLEAR_DESCR_DYN1
 *  @brief Clears the DYN1 descriptor
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CLEAR_DESCR_DYN1(_hNetBuf_)     do{ memset((_hNetBuf_)->hHdr, 0, sizeof(NtDyn1Descr_t)); } while(0)

/** @def NT_NET_SET_PKT_CLEAR_DESCR_DYN2
 *  @brief Clears the DYN2 descriptor
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CLEAR_DESCR_DYN2(_hNetBuf_)     do{ memset((_hNetBuf_)->hHdr, 0, sizeof(NtDyn2Descr_t)); } while(0)

/** @def NT_NET_SET_PKT_CLEAR_DESCR_DYN3
 *  @brief Clears the DYN3 descriptor
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CLEAR_DESCR_DYN3(_hNetBuf_)     do{ memset((_hNetBuf_)->hHdr, 0, sizeof(NtDyn3Descr_t)); } while(0)

/** @def NT_NET_SET_PKT_CLEAR_DESCR_DYN4
 *  @brief Clears the DYN4 descriptor
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CLEAR_DESCR_DYN4(_hNetBuf_)     do{ memset((_hNetBuf_)->hHdr, 0, sizeof(NtDyn4Descr_t)); } while(0)

/** @def NT_NET_GET_PKT_DESCR_TYPE
 *  @brief Get the packet descriptor type.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the packet descriptor type. See @ref NtPacketDescriptorType_e for values.
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_TYPE(_hNetBuf_)            _NT_NET_GET_PKT_DESCR_TYPE(_hNetBuf_)

/** @def NT_NET_SET_PKT_DESCR_TYPE_STD
 *  @brief Sets the packet descriptor type to NT
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_DESCR_TYPE_STD(_hNetBuf_)        do{ _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->descriptorType = 1; } while(0)

/** @def NT_NET_SET_PKT_DESCR_TYPE_EXT7
 *  @brief Sets the packet descriptor type to EXT7
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#ifndef DOXYGEN_INTERNAL_ONLY
#define NT_EXTENDED_DESCRIPTOR_07_LENGTH 2
#define NT_EXTENDED_DESCRIPTOR_07_TYPE   7
#endif // DOXYGEN_INTERNAL_ONLY
#define NT_NET_SET_PKT_DESCR_TYPE_EXT7(_hNetBuf_) \
  do{ _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->descriptorType = 1;    \
    _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionFormat = NT_EXTENDED_DESCRIPTOR_07_TYPE; \
    _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionLength = NT_EXTENDED_DESCRIPTOR_07_LENGTH; } while(0)

/** @def NT_NET_SET_PKT_DESCR_TYPE_EXT8
 *  @brief Sets the packet descriptor type to EXT8
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#ifndef DOXYGEN_INTERNAL_ONLY
#define NT_EXTENDED_DESCRIPTOR_08_LENGTH 2
#define NT_EXTENDED_DESCRIPTOR_08_TYPE   8
#endif // DOXYGEN_INTERNAL_ONLY
#define NT_NET_SET_PKT_DESCR_TYPE_EXT8(_hNetBuf_) \
  do{ _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->descriptorType = 1;    \
    _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionFormat = NT_EXTENDED_DESCRIPTOR_08_TYPE; \
    _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionLength = NT_EXTENDED_DESCRIPTOR_08_LENGTH; } while(0)

/** @def NT_NET_SET_PKT_DESCR_TYPE_EXT9
 *  @brief Sets the packet descriptor type to EXT9
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#ifndef DOXYGEN_INTERNAL_ONLY
#define NT_EXTENDED_DESCRIPTOR_09_LENGTH 3
#define NT_EXTENDED_DESCRIPTOR_09_TYPE   9
#endif // DOXYGEN_INTERNAL_ONLY
#define NT_NET_SET_PKT_DESCR_TYPE_EXT9(_hNetBuf_) \
  do{ _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->descriptorType = 1;    \
    _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionFormat = NT_EXTENDED_DESCRIPTOR_09_TYPE; \
    _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionLength = NT_EXTENDED_DESCRIPTOR_09_LENGTH; } while(0)

/** @def NT_NET_SET_PKT_DESCR_TYPE_DYN1
 *  @brief Sets the packet descriptor type to DYN1
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#ifndef DOXYGEN_INTERNAL_ONLY
#define NT_DYNAMIC_DESCRIPTOR_01_FORMAT 1
#define NT_DYNAMIC_DESCRIPTOR_01_LENGTH 18
#endif // DOXYGEN_INTERNAL_ONLY
#define NT_NET_SET_PKT_DESCR_TYPE_DYN1(_hNetBuf_) \
  do{ _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->ntDynDescr = 1;    \
    _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrFormat = NT_DYNAMIC_DESCRIPTOR_01_FORMAT; \
    _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrLength = NT_DYNAMIC_DESCRIPTOR_01_LENGTH; } while(0)

/** @def NT_NET_SET_PKT_DESCR_TYPE_DYN2
 *  @brief Sets the packet descriptor type to DYN2
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#ifndef DOXYGEN_INTERNAL_ONLY
#define NT_DYNAMIC_DESCRIPTOR_02_FORMAT 2
#define NT_DYNAMIC_DESCRIPTOR_02_LENGTH 22
#endif // DOXYGEN_INTERNAL_ONLY
#define NT_NET_SET_PKT_DESCR_TYPE_DYN2(_hNetBuf_) \
  do{ _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->ntDynDescr = 1;    \
    _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrFormat = NT_DYNAMIC_DESCRIPTOR_02_FORMAT; \
    _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrLength = NT_DYNAMIC_DESCRIPTOR_02_LENGTH; } while(0)

/** @def NT_NET_SET_PKT_DESCR_TYPE_DYN3
 *  @brief Sets the packet descriptor type to DYN3
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#ifndef DOXYGEN_INTERNAL_ONLY
#define NT_DYNAMIC_DESCRIPTOR_03_FORMAT 3
#define NT_DYNAMIC_DESCRIPTOR_03_LENGTH 22
#endif // DOXYGEN_INTERNAL_ONLY
#define NT_NET_SET_PKT_DESCR_TYPE_DYN3(_hNetBuf_) \
  do{ _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->ntDynDescr = 1;    \
    _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrFormat = NT_DYNAMIC_DESCRIPTOR_03_FORMAT; \
    _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrLength = NT_DYNAMIC_DESCRIPTOR_03_LENGTH; } while(0)

/** @def NT_NET_SET_PKT_DESCR_TYPE_DYN4
 *  @brief Sets the packet descriptor type to DYN4
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#ifndef DOXYGEN_INTERNAL_ONLY
#define NT_DYNAMIC_DESCRIPTOR_04_FORMAT 4
#define NT_DYNAMIC_DESCRIPTOR_04_LENGTH 24
#endif // DOXYGEN_INTERNAL_ONLY
#define NT_NET_SET_PKT_DESCR_TYPE_DYN4(_hNetBuf_) \
  do{ _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->ntDynDescr = 1;    \
    _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrFormat = NT_DYNAMIC_DESCRIPTOR_04_FORMAT; \
    _NT_NET_GET_PKT_DESCR_PTR_DYN(_hNetBuf_)->descrLength = NT_DYNAMIC_DESCRIPTOR_04_LENGTH; } while(0)

/** @def NT_NET_GET_PKT_DESCR_PTR_STD
 *  @brief Get standard packet descriptor pointer
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns a pointer to the packet descriptor
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_PTR_STD(_hNetBuf_)        _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)

/** @def NT_NET_GET_PKT_DESCR_PTR_EXT7
 *  @brief Get extended packet descriptor 7 pointer
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns a pointer to the packet descriptor
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)        _NT_NET_GET_PKT_DESCR_PTR_EXT7(_hNetBuf_)

/** @def NT_NET_GET_PKT_DESCR_PTR_EXT8
 *  @brief Get extended packet descriptor 8 pointer
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns a pointer to the packet descriptor
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_PTR_EXT8(_hNetBuf_)        _NT_NET_GET_PKT_DESCR_PTR_EXT8(_hNetBuf_)

/** @def NT_NET_GET_PKT_DESCR_PTR_EXT9
 *  @brief Get extended packet descriptor 9 pointer
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns a pointer to the packet descriptor
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_PTR_EXT9(_hNetBuf_)        _NT_NET_GET_PKT_DESCR_PTR_EXT9(_hNetBuf_)

/** @def NT_NET_GET_PKT_DESCR_PTR_DYN1
 *  @brief Get dynamic packet descriptor 1 pointer
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns a pointer to the packet descriptor
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_PTR_DYN1(_hNetBuf_)        _NT_NET_GET_PKT_DESCR_PTR_DYN1(_hNetBuf_)

/** @def NT_NET_GET_PKT_DESCR_PTR_DYN2
 *  @brief Get dynamic packet descriptor 2 pointer
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns a pointer to the packet descriptor
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_PTR_DYN2(_hNetBuf_)        _NT_NET_GET_PKT_DESCR_PTR_DYN2(_hNetBuf_)

/** @def NT_NET_GET_PKT_DESCR_PTR_DYN3
 *  @brief Get dynamic packet descriptor 3 pointer
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns a pointer to the packet descriptor
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_PTR_DYN3(_hNetBuf_)        _NT_NET_GET_PKT_DESCR_PTR_DYN3(_hNetBuf_)

/** @def NT_NET_GET_PKT_DESCR_PTR_DYN4
 *  @brief Get dynamic packet descriptor 4 pointer
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns a pointer to the packet descriptor
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_PTR_DYN4(_hNetBuf_)        _NT_NET_GET_PKT_DESCR_PTR_DYN4(_hNetBuf_)

/** @def NT_NET_GET_PKT_L2_PTR
 *  @brief A pointer to the L2 packet data. If an ISL header is present it will point to the ISL header.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns a void pointer to L2 packet data.
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L2_PTR(_hNetBuf_)                _NT_NET_GET_PKT_L2_PTR(_hNetBuf_)

/** @def NT_NET_UPDATE_PKT_L2_PTR
 *  @brief When creating packets within a segment it is required to update the L2 pointer using this macro after applying the descriptor info
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @hideinitializer
 */
#define NT_NET_UPDATE_PKT_L2_PTR(_hNetBuf_)             _NT_NET_UPDATE_PKT_L2_PTR(_hNetBuf_)


/** @def NT_NET_GET_PKT_DESCR_LENGTH
 *  @brief Get the length of the packet descriptor
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Return the length of the packet descriptor in bytes
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_LENGTH(_hNetBuf_)          _NT_NET_GET_PKT_DESCR_LENGTH(_hNetBuf_)

/** @def NT_NET_GET_PKT_DESCR_FORMAT
 *  @brief Indicates if extended packet descriptor 7, 8, or 9 is used, if the
 *  standard packet descriptor is used, or what dynamic packet descriptor type is used.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the packet descriptor format used
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)          _NT_NET_GET_PKT_DESCR_FORMAT(_hNetBuf_)

/** @def NT_NET_GET_PKT_TIMESTAMP
 *  @brief Get the packet timestamp
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the time when the packet was captured as an 64bit unsigned value
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TIMESTAMP(_hNetBuf_)             _NT_NET_GET_PKT_TIMESTAMP(_hNetBuf_)

/** @def NT_NET_SET_PKT_TIMESTAMP
 *  @brief Sets the packet time stamp - useful when controlling the traffic rate
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_ts_" The timestamp value in 10ns resolution NATIVE format
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_TIMESTAMP(_hNetBuf_, _ts_)      _NT_NET_SET_PKT_TIMESTAMP(_hNetBuf_, _ts_)

/** @def NT_NET_GET_PKT_TIMESTAMP_TYPE
 *  @brief Get the packet time stamp type. See @ref NtTimestampType_e
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the packet time stamp type. See @ref NtTimestampType_e for values
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TIMESTAMP_TYPE(_hNetBuf_)        _NT_NET_GET_PKT_TIMESTAMP_TYPE(_hNetBuf_)

/** @def NT_NET_GET_PKT_CAP_LENGTH
 *  @brief Returns the total stored length of the received frame including
 *  packet descriptors, in bytes, after any slicing.  The value is a multiple
 *  of eight for frames received on 3GA adapters, or if the capture length
 *  was set with the ALIGN macro.
 *  The value is also rounded up for unsliced frames with wire lengths
 *  that are not a multiple of eight (bytes).
 *  NT_NET_GET_PKT_CAP_LENGTH returns a value of type uint16_t.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns an uint16_t value that is the total stored length of the received frame
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_CAP_LENGTH(_hNetBuf_) ((uint16_t)(_NT_NET_GET_PKT_CAP_LENGTH(_hNetBuf_)))

/** @def NT_NET_SET_PKT_CAP_LENGTH_NOALIGN
 *  @brief Calculates and sets the packet capture length. Input is wire length. Capture length is calculated from the value - no alignment is applied
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_Length_" The length value
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CAP_LENGTH_NOALIGN(_hNetBuf_, _Length_)   _NT_NET_SET_PKT_CAP_LENGTH_NOALIGN(_hNetBuf_, _Length_)

/** @} */

/** @defgroup NtDescriptorMacros NT descriptor macros
 * @{

 * The following is only available if "PacketDescriptor = NT or Ext7 or Ext8 or Ext9" has been selected in the ntservice.ini file
 * and if @ref NT_NET_GET_PKT_DESCRIPTOR_TYPE returns @ref NT_PACKET_DESCRIPTOR_TYPE_NT || @ref NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED.
 * The following macros constitute the collection extracting data from the "NT" descriptor.
 */

/** @def NT_NET_SET_PKT_CAP_LENGTH_ALIGN_NT
 *  @brief Calculates and sets the packet capture length. Input is wire length. Capture length is calculated from the value.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_Length_" The length value
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CAP_LENGTH_ALIGN_NT(_hNetBuf_, _Length_)   _NT_NET_SET_PKT_CAP_LENGTH_ALIGN_NT(_hNetBuf_, _Length_)

/** @def NT_NET_GET_PKT_WIRE_LENGTH_NT
 *  @brief Returns the wire length of the received frame, in bytes, with the
 *  value saturated at 16,383 for longer frames.
 *  NT_NET_GET_PKT_WIRE_LENGTH_NT returns a value of type uint16_t.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns an uint16_t value that is the packet wire length
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_WIRE_LENGTH_NT(_hNetBuf_) ((uint16_t)_NT_NET_GET_PKT_WIRE_LENGTH_NT(_hNetBuf_))

/** @def NT_NET_SET_PKT_WIRE_LENGTH_NT
 *  @brief Sets the packet wire length
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_Length_" The length value
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_WIRE_LENGTH_NT(_hNetBuf_, _Length_)    _NT_NET_SET_PKT_WIRE_LENGTH_NT(_hNetBuf_, _Length_)

/** @def NT_NET_GET_PKT_CRC_ERROR_NT
 *  @brief Indicates if the received frame has a layer 2 CRC error.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has a L2 CRC error - If no L2 CRC error this is 0.
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_CRC_ERROR_NT(_hNetBuf_)             _NT_NET_GET_PKT_CRC_ERROR_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_CRC_ERROR_NT
 *  @brief Sets if the packet has a CRC error
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 if packet has a CRC error, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CRC_ERROR_NT(_hNetBuf_, _bval_)    _NT_NET_SET_PKT_CRC_ERROR_NT(_hNetBuf_, _bval_)

/** @def NT_NET_GET_PKT_TCP_CSUM_OK_NT
 *  @brief Indicates if the received TCP checksum is correct
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has a valid TCP checksum - if not a TCP packet this is 0
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TCP_CSUM_OK_NT(_hNetBuf_)           _NT_NET_GET_PKT_TCP_CSUM_OK_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_TCP_CSUM_OK_NT
 *  @brief Sets if the packet has an OK TCP checksum
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 if packet packet has an OK TCP checksum, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_TCP_CSUM_OK_NT(_hNetBuf_, _bval_)  _NT_NET_SET_PKT_TCP_CSUM_OK_NT(_hNetBuf_, _bval_)

/** @def NT_NET_GET_PKT_UDP_CSUM_OK_NT
 *  @brief Indicates if the received UDP checksum is correct
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has a valid UDP checksum - if not a UDP packet this is 0
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_UDP_CSUM_OK_NT(_hNetBuf_)           _NT_NET_GET_PKT_UDP_CSUM_OK_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_UDP_CSUM_OK_NT
 *  @brief Sets if the packet has an OK UDP checksum
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 if packet packet has an OK UDP checksum, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_UDP_CSUM_OK_NT(_hNetBuf_, _bval_)  _NT_NET_SET_PKT_UDP_CSUM_OK_NT(_hNetBuf_, _bval_)

/** @def NT_NET_GET_PKT_IP_CSUM_OK_NT
 *  @brief Indicates if the received IP checksum is correct
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has a valid IP checksum - if not an IP packet this is 0
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IP_CSUM_OK_NT(_hNetBuf_)            _NT_NET_GET_PKT_IP_CSUM_OK_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_IP_CSUM_OK_NT
 *  @brief Sets if the packet has an OK IP checksum
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 if packet packet has an OK IP checksum, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_IP_CSUM_OK_NT(_hNetBuf_, _bval_)   _NT_NET_SET_PKT_IP_CSUM_OK_NT(_hNetBuf_, _bval_)

/** @def NT_NET_GET_PKT_CV_ERROR_NT
 *  @brief Indicates if the frame has any coding violations errors.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has coding violations - If no coding violations this is 0.
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_CV_ERROR_NT(_hNetBuf_)              _NT_NET_GET_PKT_CV_ERROR_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_CV_ERROR_NT
 *  @brief Sets if the frame has any coding violations errors.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 if packet packet has coding violations errors, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CV_ERROR_NT(_hNetBuf_, _bval_)              _NT_NET_SET_PKT_CV_ERROR_NT(_hNetBuf_, _bval_)

/** @def NT_NET_GET_PKT_SLICED_NT
 *  @brief Indicates if the frame has been sliced
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has been sliced - If no slicing has occured this is 0
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_SLICED_NT(_hNetBuf_)                _NT_NET_GET_PKT_SLICED_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_SLICED_NT
 *  @brief Sets if the frame has been sliced
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 if packet packet has been sliced, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_SLICED_NT(_hNetBuf_, _bval_)                _NT_NET_SET_PKT_SLICED_NT(_hNetBuf_, _bval_)

/** @def NT_NET_GET_PKT_HARD_SLICED_NT
 *  @brief Indicates if the frame has been hard sliced.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has been hard sliced - If no hard slicing has occured this is 0
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_HARD_SLICED_NT(_hNetBuf_)           _NT_NET_GET_PKT_HARD_SLICED_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_HARD_SLICED_NT
 *  @brief Sets if the frame has been hard sliced.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 if packet packet has been hard sliced, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_HARD_SLICED_NT(_hNetBuf_, _bval_)           _NT_NET_SET_PKT_HARD_SLICED_NT(_hNetBuf_, _bval_)

/** @def NT_NET_GET_PKT_RXPORT_NT
 *  @brief Specifies the port number where the frame was received.
 *  NT_NET_GET_PKT_RXPORT_NT returns a value of type uint8_t.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns an uint8_t value that is the port that received this packet
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_RXPORT_NT(_hNetBuf_)                _NT_NET_GET_PKT_RXPORT_NT(_hNetBuf_)

/** @def NT_NET_GET_PKT_IS_TCP_NT
 *  @brief Indicates if the received frame is a TCP frame.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has a TCP header - returns 0 if the packet does not have a TCP header
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IS_TCP_NT(_hNetBuf_)                _NT_NET_GET_PKT_TCP_FRAME_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_IS_TCP_NT
 *  @brief Sets if the packet is TCP
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 if TCP packet, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_IS_TCP_NT(_hNetBuf_, _bval_)       _NT_NET_SET_PKT_IS_TCP_NT(_hNetBuf_, _bval_)

/** @def NT_NET_GET_PKT_IS_UDP_NT
 *  @brief Indicates if the received frame is a UDP frame.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has an UDP header - returns 0 if the packet does not have an UDP header
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IS_UDP_NT(_hNetBuf_)                _NT_NET_GET_PKT_UDP_FRAME_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_IS_UDP_NT
 *  @brief Sets if the packet is UDP
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 if UDP packet, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_IS_UDP_NT(_hNetBuf_, _bval_)       _NT_NET_SET_PKT_IS_UDP_NT(_hNetBuf_, _bval_)

/** @def NT_NET_GET_PKT_IS_IP_NT
 *  @brief Indicates if the received frame is an IP frame
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has an IP header - returns 0 if the packet does not have an IP header
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IS_IP_NT(_hNetBuf_)                 _NT_NET_GET_PKT_IP_FRAME_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_IS_IP_NT
 *  @brief Sets if the packet is IP
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 if IP packet, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_IS_IP_NT(_hNetBuf_, _bval_)        _NT_NET_SET_PKT_IS_IP_NT(_hNetBuf_, _bval_)

/** @def NT_NET_GET_PKT_TXPORT_NT
 *  @brief Get TX port
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the port number where the frame is to be transmitted.
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TXPORT_NT(_hNetBuf_)                _NT_NET_GET_PKT_TXPORT_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_TXPORT_NT
 *  @brief Sets the packet port where the packets should be transmitted @note This feature only works on the CaptureReplay profile and the TX port can only be within the range of one adapter
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_Port_" Port number
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_TXPORT_NT(_hNetBuf_, _Port_)        _NT_NET_SET_PKT_TXPORT_NT(_hNetBuf_, _Port_)

/** @def NT_NET_GET_PKT_RECALC_L2_CRC_NT
 *  @brief Indicates if the original CRC in the received frame will be recalculated and overwritten in the transmitted frame.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has L2 CRC recalc/override set - Returns 0 if L2 CRC recalc/override is not set
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_RECALC_L2_CRC_NT(_hNetBuf_)         _NT_NET_GET_PKT_RECALC_L2_CRC_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_RECALC_L2_CRC_NT
 *  @brief Asks the adapter to re-generate the CRC
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 if CRC should be re-generated, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_RECALC_L2_CRC_NT(_hNetBuf_, _bval_)  _NT_NET_SET_PKT_RECALC_L2_CRC_NT(_hNetBuf_, _bval_)

/** @def NT_NET_GET_PKT_TXNOW_NT
 *  @brief Indicates if the frame is to be transmitted according to time stamp or as fast as possible.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has TxNow set - Returns 0 if TxNow is not set
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TXNOW_NT(_hNetBuf_)                 _NT_NET_GET_PKT_TXNOW_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_TXNOW_NT
 *  @brief If set the IPG is ignored - this will result in line rate TX
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 if line rate, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_TXNOW_NT(_hNetBuf_, _bval_)        _NT_NET_SET_PKT_TXNOW_NT(_hNetBuf_, _bval_)

/** @def NT_NET_GET_PKT_TXIGNORE_NT
 *  @brief Indicates if the frame is to be transmitted or not.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has TxIgnore set - Returns 0 if TxIgnore is not set
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TXIGNORE_NT(_hNetBuf_)              _NT_NET_GET_PKT_TXIGNORE_NT(_hNetBuf_)

/** @def NT_NET_SET_PKT_TXIGNORE_NT
 *  @brief Marks the packet not to be sent - useful in in-line scenarios where some packets should not be retransmitted
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 to not transmit the packet, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_TXIGNORE_NT(_hNetBuf_, _bval_)     _NT_NET_SET_PKT_TXIGNORE_NT(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_TXSETCLOCK_NT
 *  @brief Cause the adapter transmission delta to by incremented by the configured delta adjustment before transmitting the packet
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 to increment delta before transmitting this packet, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_TXSETCLOCK_NT(_hNetBuf_, _bval_)   _NT_NET_SET_PKT_TXSETCLOCK_NT(_hNetBuf_, _bval_)

/** @} */

/** @defgroup ExtendedNtDescriptorMacros Extended NT descriptor macros
 * @{
 * The following is only available if "PacketDescriptor = Ext7, Ext8 or Ext9" has been set in the ntservice.ini
 * file and if @ref NT_NET_GET_PKT_DESCRIPTOR_TYPE returns @ref NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED
 */

/** @def NT_NET_GET_PKT_HASH_EXT
 *  @brief Get the packet hash value
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the packet hash value. If the hash calculation is invalid, the value is 0x00.
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_HASH_EXT(_hNetBuf_)             _NT_NET_GET_PKT_HASH_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_HASH_TYPE_EXT
 *  @brief Get the number of the used hash key type
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the number of the used hash key type.
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_HASH_TYPE_EXT(_hNetBuf_)        _NT_NET_GET_PKT_HASH_TYPE_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_HASH_VALID_EXT
 *  @brief Indicates if the hash calculation is valid.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the hash value/type is valid - Returns 0 if the hash value/type is invalid
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_HASH_VALID_EXT(_hNetBuf_)       _NT_NET_GET_PKT_HASH_VALID_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_JUMBO_EXT
 *  @brief Indicates if the frame is a jumbo frame.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the packet has a jumbo frame - Returns 0 if the packet does not have a jumbo frame
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_JUMBO_EXT(_hNetBuf_)            _NT_NET_GET_PKT_JUMBO_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_BROADCAST_EXT
 *  @brief Indicates if the destination MAC address is broadcast.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the destination MAC is a broadcast address - Returns 0 if the destination MAC is not a broadcast address
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_BROADCAST_EXT(_hNetBuf_)        _NT_NET_GET_PKT_BROADCAST_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_L4_PORT_TYPE_EXT
 *  @brief Get the layer 4 port type
 *  When using extended descriptor 9 it is advised to use @ref NT_NET_GET_PKT_TUNNEL_TYPE instead.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Return the layer 4 port type - see @ref NtL4PortType_e for values
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L4_PORT_TYPE_EXT(_hNetBuf_)     _NT_NET_GET_PKT_L4_PORT_TYPE_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_L4_FRAME_TYPE_EXT
 *  @brief Get layer 4 frame type
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns layer 4 frame type - see @ref NtL4FrameType_e for values
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_)    _NT_NET_GET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_L3_FRAME_TYPE_EXT
 *  @brief Get layer 3 frame type
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns layer 3 frame type - see @ref NtL3FrameType_e for values
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_)    _NT_NET_GET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_L2_FRAME_TYPE_EXT
 *  @brief Get layer 2 frame type
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns layer 2 frame type - see @ref NtL2FrameType_e for values
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_)    _NT_NET_GET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_L4_LENGTH_EXT
 *  @brief Get layer 4 header length (valid for L4 = UDP/TCP only)
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns layer 4 header length in units of 32 bits
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L4_LENGTH_EXT(_hNetBuf_)        _NT_NET_GET_PKT_L4_LENGTH_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_L3_LENGTH_EXT
 *  @brief Get layer 3 header length (valid for L3 = IPv4/IPv6 only)
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns layer 3 header length in units of 32 bits
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L3_LENGTH_EXT(_hNetBuf_)        _NT_NET_GET_PKT_L3_LENGTH_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_MPLS_COUNT_EXT
 *  @brief Get the number of MPLS shim labels present
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the number of MPLS shim labels present
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_MPLS_COUNT_EXT(_hNetBuf_)       _NT_NET_GET_PKT_MPLS_COUNT_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_VLAN_COUNT_EXT
 *  @brief Get the number of VLANs present
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the number of VLANs present
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_VLAN_COUNT_EXT(_hNetBuf_)       _NT_NET_GET_PKT_VLAN_COUNT_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_ISL_EXT
 *  @brief Indicates if ISL encapsulation is present.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if ISL encapsulation is present - Returns 0 if ISL encapsulation is not present
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_ISL_EXT(_hNetBuf_)              _NT_NET_GET_PKT_ISL_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_DECODE_ERROR_EXT
 *  @brief Indicates if a frame decoding error is present.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the frame could not be decoded correctly - Returns 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DECODE_ERROR_EXT(_hNetBuf_)     _NT_NET_GET_PKT_DECODE_ERROR_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_FRAME_LARGE_EXT
 *  @brief Indicates if the frame is a large frame.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return - Returns 1 when FrameSize > MaxFrameSize. MaxFrameSize is set in ntservice.ini. Returns 0 when FrameSize <= MaxFrameSize
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_FRAME_LARGE_EXT(_hNetBuf_)      _NT_NET_GET_PKT_FRAME_LARGE_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_FRAME_SMALL_EXT
 *  @brief Indicates if the frame is a small frame.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 when PktSz < 64 (+ISL and/or VLAN) - Returns 0 when PktSz >= 64
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_FRAME_SMALL_EXT(_hNetBuf_)      _NT_NET_GET_PKT_FRAME_SMALL_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_IPV6_FR_HEADER_EXT
 *  @brief Indicates if an IPv6 fragment header is present.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if IPv6 fragment header is present - Returns 0 if no IPv6 fragment header is present
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IPV6_FR_HEADER_EXT(_hNetBuf_)   _NT_NET_GET_PKT_IPV6_FR_HEADER_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_IPV6_RT_HEADER_EXT
 *  @brief Indicates if an IPv6 routing header is present.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if IPv6 routing header is present - Returns 0 if no IPv6 routing header is present
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IPV6_RT_HEADER_EXT(_hNetBuf_)   _NT_NET_GET_PKT_IPV6_RT_HEADER_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT
 *  @brief Get layer 4 protocol number (TCP, UDP, SCTP etc.) - if not an IP packet this is 0
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the layer 4 protocol number / next header.
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT(_hNetBuf_)  _NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_L3_FRAGMENTED_EXT
 *  @brief Indicates if the packet is part of a layer 3 fragmented datagram. Only valid for IPv4 if more fragments bit = 1 or fragment offset not equal to 0
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if fragmented layer 3 - Returns 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L3_FRAGMENTED_EXT(_hNetBuf_)    _NT_NET_GET_PKT_L3_FRAGMENTED_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_L3_FIRST_FRAG_EXT
 *  @brief Layer 3 First fragment (offset = 0) Note: Only valid for IPv4 - always set on IPv6 so use IPV6_FR_HEADER instead
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if first fragment or not fragmented - Returns 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L3_FIRST_FRAG_EXT(_hNetBuf_)    _NT_NET_GET_PKT_L3_FIRST_FRAG_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_COLOR_EXT
 *  @brief Returns the packet color of the frame, if the frame matches a
 *  filter. The color is automatically assigned as a 6bit color ID when the
 *  filter is defined. If the frame matches more than one filter, the packet
 *  color of the frame is the one from the filter with the highest priority.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the color of the packet as an integer value
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_COLOR_EXT(_hNetBuf_)            _NT_NET_GET_PKT_COLOR_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_L5_OFFSET_EXT
 *  @brief Returns the offset in bytes (0x00 - 0x1FF) from the start of the
 *  frame to the start of layer 5. The value 0x00 indicates an invalid offset.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns layer 5 offset as an integer value
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L5_OFFSET_EXT(_hNetBuf_)        _NT_NET_GET_PKT_L5_OFFSET_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_L4_OFFSET_EXT
 *  @brief Returns the offset in bytes (0x00 - 0x1FF) from the start of the
 *  frame to the start of layer 4. The value 0x00 indicates an invalid offset.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns layer 4 offset as an integer value
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L4_OFFSET_EXT(_hNetBuf_)        _NT_NET_GET_PKT_L4_OFFSET_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_L3_OFFSET_EXT
 *  @brief Returns the offset in bytes (0x00 - 0x1FF) from the start of the
 *  frame to the start of layer 3. The value 0x00 indicates an invalid offset.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns layer 3 offset as an integer value
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L3_OFFSET_EXT(_hNetBuf_)        _NT_NET_GET_PKT_L3_OFFSET_EXT(_hNetBuf_)

/** @} */

/** @defgroup ExtendedNtDescriptorIPFMacros Extended NT descriptor IPF macros
 * @{
 * The following are used to help collect IP fragmented data. With theses
 * macros it is possible to de-fragment IP fragmented data in a
 * multi-processing application using 5-tuple hashing. It is only available if
 * "PacketDescriptor" in the ntservice.ini file has been set to "Ext8" or
 * "Ext9" and if @ref NT_NET_GET_PKT_DESCRIPTOR_TYPE returns @ref
 * NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED @note: These macros do not return
 * valid values if the IPF engine is not turned on see @ref NtplIPFMode
 */

/** @def NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID_EXT
 *  @brief Stream ID where unmatched fragments are stored
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the stream ID where unmatched fragments are stored
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID_EXT(_hNetBuf_)      _NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_IPF_UNMATCHED_FLAG_EXT
 *  @brief Indicates if no entry corresponding to the packet was allocated or
 *  found in the datagram lookup table.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if unmatched - Returns 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IPF_UNMATCHED_FLAG_EXT(_hNetBuf_)          _NT_NET_GET_PKT_IPF_UNMATCHED_FLAG_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_IPF_LAST_FRAGMENT_EXT
 *  @brief Indicates if the packet is the last fragment of a layer 3
 *  fragmented datagram. (More fragment bit = 0 && offset != 0)
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if last fragment - Returns 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IPF_LAST_FRAGMENT_EXT(_hNetBuf_)           _NT_NET_GET_PKT_IPF_LAST_FRAGMENT_EXT(_hNetBuf_)

/** @} */

/** @defgroup ExtendedNtDescriptorTunnelMacros Extended NT descriptor Tunneling macros
 * @{
 *
 * The following are used to help accessing GTPv1 and IP-in-IP tunneled
 * data. With theses macros it is possible to determine the tunnel type,
 * retrieve the frame types and get direct offsets to the layers 3, 4 and 5
 * inside the tunnel. Only the first tunnel is decoded, hence a tunnel inside
 * a tunnel is not decoded. The following macros are only available if
 * "PacketDescriptor" in the ntservice.ini file has been set to "Ext9" or if
 * "Ext9" is configured as the descriptor type in the NTPL "assign" statement
 * matching the received packet.
 */

/** @def NT_NET_GET_PKT_INNER_L3_OFFSET_EXT9
 *  @brief Returns the offset in bytes (0x00 - 0x1FF) from the start of the
 *  frame to the start of inner layer 3. The value 0x00 indicates an invalid
 *  offset.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns inner layer 3 offset as an integer value
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_L3_OFFSET_EXT9(_hNetBuf_)             _NT_NET_GET_PKT_INNER_L3_OFFSET_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_INNER_L4_OFFSET_EXT9
 *  @brief Returns the offset in bytes (0x00 - 0x1FF) from the start of the
 *  frame to the start of inner layer 4. The value 0x00 indicates an invalid
 *  offset.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns inner layer 4 offset as an integer value
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_L4_OFFSET_EXT9(_hNetBuf_)             _NT_NET_GET_PKT_INNER_L4_OFFSET_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_INNER_L5_OFFSET_EXT9
 *  @brief Returns the offset in bytes (0x00 - 0x1FF) from the start of the
 *  frame to the start of inner layer 5. The value 0x00 indicates an invalid
 *  offset.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns inner layer 5 offset as an integer value
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_L5_OFFSET_EXT9(_hNetBuf_)             _NT_NET_GET_PKT_INNER_L5_OFFSET_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_INNER_L3_FRAME_TYPE_EXT9
 *  @brief Get the inner tunnel layer 3 frame type
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the inner tunnel layer 3 frame type - see @ref NtL3FrameType_e for values
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_L3_FRAME_TYPE_EXT9(_hNetBuf_)         _NT_NET_GET_PKT_INNER_L3_FRAME_TYPE_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_INNER_L4_FRAME_TYPE_EXT9
 *  @brief Get the inner tunnel layer 4 frame type
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the inner tunnel layer 4 frame type - see @ref NtL4FrameType_e for values
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_L4_FRAME_TYPE_EXT9(_hNetBuf_)         _NT_NET_GET_PKT_INNER_L4_FRAME_TYPE_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_INNER_L3_FRAGMENT_TYPE_EXT9
 *  @brief Get inner layer 3 fragment type
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns inner layer 3 fragment type - see @ref NtL3FragmentType_e for values
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_L3_FRAGMENT_TYPE_EXT9(_hNetBuf_)      _NT_NET_GET_PKT_INNER_L3_FRAGMENT_TYPE_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_TUNNEL_TYPE_EXT9
 *  @brief Get the tunnel type
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the tunnel type - see @ref NtTunnelType_e for values
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TUNNEL_TYPE_EXT9(_hNetBuf_)                 _NT_NET_GET_PKT_TUNNEL_TYPE_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_TUNNEL_HDR_LENGTH_EXT9
 *  @brief Get the tunnel header length
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the tunnel header length in units of 32 bits
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TUNNEL_HDR_LENGTH_EXT9(_hNetBuf_)           _NT_NET_GET_PKT_TUNNEL_HDR_LENGTH_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_INNER_DECODE_ERROR_EXT9
 *  @brief Indicates if a inner tunnel frame decoding error is present.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns 1 if the inner tunnel frame could not be decoded correctly - Returns 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_DECODE_ERROR_EXT9(_hNetBuf_)          _NT_NET_GET_PKT_INNER_DECODE_ERROR_EXT(_hNetBuf_)

/** @def NT_NET_GET_PKT_DEDUPLICATION_CRC_EXT9
 *  @brief The packet deduplication CRC value. Only available on extended descriptor 9.
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @return Returns the 24bit packet deduplication CRC value.
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DEDUPLICATION_CRC_EXT9(_hNetBuf_)           _NT_NET_GET_PKT_DEDUPLICATION_CRC_EXT(_hNetBuf_)

/** @} */

/** @defgroup TxMacros TX macros
 * @{
 * The following can only be used on TX or in-line based streams
 *
 */

/** @defgroup ExtendedTxMacros Extended TX macros
 * @{
 * The following can only be used if the TX buffer has an extended NT descriptor
 */

/** @def NT_NET_SET_PKT_INJECT_TIMESTAMP
 *  @brief Injects a time stamp on TX
 *
 *  The time stamp is injected into the payload at the offset
 *  provided. Offset range: 0-512. See @ref TimeStampInject "Time
 *  Stamp Injection" for further information
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_offset_" Offset to inject timestamp at
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT(_hNetBuf_, _offset_)  _NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT(_hNetBuf_, _offset_)

/** @def NT_NET_SET_PKT_ISL
 *  @brief Sets if the frame is ISL encapsulated
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set 1 if ISL encapsulated, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_ISL_EXT(_hNetBuf_, _bval_)                 _NT_NET_SET_PKT_ISL_EXT(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_VLAN_COUNT
 *  @brief Sets the number of VLAN tags
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_count_" The VLAN tag count
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_VLAN_COUNT_EXT(_hNetBuf_, _count_)         _NT_NET_SET_PKT_VLAN_COUNT_EXT(_hNetBuf_, _count_)

/** @def NT_NET_SET_PKT_MPLS_COUNT
 *  @brief Sets the number of MPLS shim labels
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_count_" The MPLS shim labels count
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_MPLS_COUNT_EXT(_hNetBuf_, _count_)         _NT_NET_SET_PKT_MPLS_COUNT_EXT(_hNetBuf_, _count_)

/** @def NT_NET_SET_PKT_L2_FRAME_TYPE
 *  @brief Sets the L2 frame type, see @ref NtL2FrameType_e
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_type_" The L2 frame type
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_, _type_)       _NT_NET_SET_PKT_L2_FRAME_TYPE_EXT(_hNetBuf_, _type_)

/** @def NT_NET_SET_PKT_L3_FRAME_TYPE
 *  @brief Sets the L3 frame type, see @ref NtL3FrameType_e
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_type_" The L3 frame type
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_, _type_)       _NT_NET_SET_PKT_L3_FRAME_TYPE_EXT(_hNetBuf_, _type_)

/** @def NT_NET_SET_PKT_L4_FRAME_TYPE
 *  @brief Sets the L4 frame type, see @ref NtL4FrameType_e
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_type_" The L4 frame type
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_, _type_)       _NT_NET_SET_PKT_L4_FRAME_TYPE_EXT(_hNetBuf_, _type_)

/** @def NT_NET_SET_PKT_L3_LENGTH
 *  @brief L3 length in 32-bit units
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_u32len_" The L3 length in 32-bit units
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_L3_LENGTH_EXT(_hNetBuf_, _u32len_)         _NT_NET_SET_PKT_L3_LENGTH_EXT(_hNetBuf_, _u32len_)

/** @def NT_NET_SET_PKT_L4_LENGTH
 *  @brief L4 length in 32-bit units
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_u32len_" The L4 length in 32-bit units
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_L4_LENGTH_EXT(_hNetBuf_, _u32len_)         _NT_NET_SET_PKT_L4_LENGTH_EXT(_hNetBuf_, _u32len_)

/** @def NT_NET_SET_PKT_CALC_L3_CHECKSUM
 *  @brief If set, the adapter will calculate an IPv4 checksum on transmit
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 calculate an IPv4 checksum on transmit, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT(_hNetBuf_, _bval_)    _NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_CALC_L4_CHECKSUM
 *  @brief If set, the adapter will calculate an TCP/UDP checksum on transmit
 *  @param[in] "_hNetBuf_" Packet container reference
 *  @param[in] "_bval_" Set to 1 calculate an TCP/UDP checksum on transmit, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT(_hNetBuf_, _bval_)    _NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT(_hNetBuf_, _bval_)

/** @} */

/** @} */
/** @} */
/** @} */

#endif /* __PKT_DESCR_H__ */
