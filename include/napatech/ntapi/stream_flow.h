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
 * This is header file of the flow stream interface
 */
#ifndef __STREAM_FLOW_H__
#define __STREAM_FLOW_H__

#if !defined(__NT_H__)
  #error: My interface file is 'nt.h'. Please include that via #include "nt.h" directly.
#endif

/** @addtogroup FlowStream
 * @{
 * Flow streams are used to program and delete flows as well as receiving flow status
 * and information records on adapters that support stateful flow tracking.
 *
 * A flow stream must be opened before flows can be programmed. This is accomplished
 * with the @ref NT_FlowOpen_Attr functions which takes a NtFlowAttr_t attribute
 * structure and returns a handle to the flow stream.
 *
 * Three types of records can be present in a flow stream:
 *
 * @ref NtFlow_t records for flow programming using @ref NT_FlowWrite
 *
 * @ref NtFlowInfo_t records with flow information read using @ref NT_FlowRead. These
 * records are only generated if flow programming sets the gfi bit.
 *
 * @ref NtFlowStatus_t records with async flow programming result read using @ref NT_FlowStatusRead.
 * Generation of these records depends on ntservice.ini settings.
 *
 * To ensure optimal performance an application that both wishes to read and write flows
 * should alternate between @ref NT_FlowWrite, @ref NT_FlowRead and @ref NT_FlowStatusRead.
 */


/**
 * Flow stream handle
 */
typedef struct NtFlowStream_s* NtFlowStream_t;

/** \cond */
#define __SIZEOF_NT_FLOW_ATTR 128
union __nt_flow_attr {
  char __size[__SIZEOF_NT_FLOW_ATTR];
  long int __align;
};
typedef union __nt_flow_attr NtFlowAttr_t;
/** \endcond */

/**
 * @brief Flow programming structure
 *
 * This structure is used when programming flows with the @ref NT_FlowWrite
 * function.
 */
typedef struct NtFlow_s {
  uint8_t keyData[40];     /*!< Raw key data array as defined by the NTPL KeyDef command */
  uint64_t id;             /*!< 64-bit user defined ID */
  uint32_t color;          /*!< 32-bit flow color */
  uint8_t overwrite:1;     /*!< Enable overwrite filter action */
  uint8_t streamId:7;      /*!< Marks the stream id if overwrite filter action is enabled.
                               Unused if overwrite is not enabled */
  uint8_t ipProtocolField; /*!< Next-protocol field from the IP header. Can be extracted from
                               outer or inner IP header or not at all
                               (see @ref NtplKeyType "KeyType NTPL Command") */
  uint8_t keyId;           /*!< Key ID as used in the @ref NtplKeyType "KeyType NTPL Command" */
  uint8_t keySetId;        /*!< Ket Set id as used in the NTPL filter */
  uint8_t op:4;            /*!< Flow programming operation (1: learn, 0: un-learn) */
  uint8_t gfi:1;           /*!< Generate flow info record (1: generate, 0: do not generate) */
  uint8_t tau:1;           /*!< TCP auto unlearn (1: auto unlearn enable, 0: auto unlearn disable) */
} NtFlow_t;

/**
 * @brief Flow information structure
 *
 * This structure contains state for a particular flow. If flow programming
 * had the gfi bit set, the flow information structure is
 * returned on the flow stream when the flow is terminated or timed out.
 */
typedef struct NtFlowInfo_s {
  uint64_t packetsA;         /*!< Packet counter for set A */
  uint64_t octetsA;          /*!< Byte/octet counter for set A */
  uint64_t packetsB;         /*!< Packet counter for set B */
  uint64_t octetsB;          /*!< Byte/octet counter for set B */
  uint64_t ts;               /*!< Time stamp in UNIX_NS format of last seen packet */
  uint64_t id;               /*!< The 64-bit user defined ID from the flow programming operation */
  uint16_t flagsA;           /*!< Bitwise OR of TCP flags for packets in set A */
  uint16_t flagsB;           /*!< Bitwise OR of TCP flags for packets in set B */
  uint8_t cause;             /*!< Unlearn cause (0: Software, 1: Timeout, 2: TCP flow termination */
} NtFlowInfo_t;


#define NT_FLOW_STAT_LDS 0x1  /*< Learn done status flag */
#define NT_FLOW_STAT_LFS 0x2  /*< Learn fail status flag */
#define NT_FLOW_STAT_LIS 0x4  /*< Learn ignore status flag */
#define NT_FLOW_STAT_UDS 0x8  /*< Un-learn done status flag */
#define NT_FLOW_STAT_UIS 0x10 /*< Un-learn ignore status flag */

/**
 * @brief Flow status structure
 *
 * This structure contains the status for a particular flow (Un-)learning
 * operation. A series of flags indicates whether the operation was successful
 * or not.
 */
typedef struct NtFlowStatus_s {
  uint64_t id;    /*< 64-bit user defined flow id */
  uint32_t flags; /*< Flags indicating the status of the operation */
} NtFlowStatus_t;

/**
 * @brief Initialize flow stream attributes
 *
 * See NT_FlowOpen_Attr for further description
 *
 * @param attr  Pointer to the attributes structure
 */
void NT_FlowOpenAttrInit(NtFlowAttr_t *attr);

/**
 * @brief Set adapter number attribute
 *
 * @param attr       Pointer to the attributes structure
 * @param adapterNo  Adapter number the stream should be associated to
 */
void NT_FlowOpenAttrSetAdapterNo(NtFlowAttr_t *attr, uint8_t adapterNo);

/**
 * @brief Return the adapter number attribute
 *
 * See NT_FlowOpen_Attr for further description
 *
 * @return The adapter number attribute
 */
uint8_t NT_FlowOpenAttrGetAdapterNo(NtFlowAttr_t *attr);

/**
 * @brief Set flow stream flags
 *
 * Currently no flags are defined so calls of this
 * function shall be avoided
 *
 * @param attr      Pointer to attriute structure
 * @param flags     Flow stream flags
 */
void NT_FlowOpenAttrSetFlags(NtFlowAttr_t *attr, uint32_t flags);

/**
 * @brief Get flow stream flags
 *
 * @param attr      Pointer to attriute structure
 * @return Flow stream flags
 */
uint32_t NT_FlowOpenAttrGetFlags(NtFlowAttr_t *attr);

/**
 * @brief Opens a flow programming stream and returns a stream handle
 *
 * This function opens a flow stream which is used for fast programming of the flow
 * matcher present on adapters that support the flow matching feature. A flow stream
 * should only be opened after all relevant NTPL statements configuring the flow matcher
 * has been executed.
 *
 * The default sequence for opening a flow stream is:
 *
 * NtFlowAttr_t attr;
 *
 * NT_FlowOpenAttrInit(&attr);
 *
 * NT_FlowOpenAttrSetAdapterNo(&attr, adapter_no);
 *
 * int status = NT_FlowOpen_Attr(&_stream, "name", &attr);
 *
 * @param[out] hStream     Reference to the NtFlowStream_t stream pointer
 * @param[in]  name        Name of the stream
 * @param[in]  attr        Pointer to the flow stream attributes
 */
int NT_FlowOpen_Attr(NtFlowStream_t* hStream, const char *name, NtFlowAttr_t* attr);

/**
 * @brief Closes a flow stream
 *
 * This function closes and frees resources belonging to a flow stream
 *
 * @param[in] hStream     Flow stream handle to be closed
 * @retval  NT_SUCCESS    Success
 * @retval !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_FlowClose(NtFlowStream_t hStream);

/**
 * @brief Programs a flow into an adapter
 *
 * This function is used to program flows into the adapter associated
 * with the stream handle. The flow data must be written into the @ref NtFlow_t
 * structure by the caller before calling this function.
 *
 * Returns NT_ERROR_INVALID_PARAMETER if NtFlow_t:
 *  - tau = 1 and gfi = 0
 *  - overwrite is set and any of 7 most significant bit in color is set
 *  - overwrite is not set but streamId is different from 0
 *
 * @param[in] hStream        The flow stream handle obtained in @ref NT_FlowOpen_Attr
 * @param[in] flow           Pointer to the flow data structure
 * @param[in] timeout        Timeout in ms before failing to program the flow (-1 = retry indefinitely)
 * @retval    NT_SUCCESS     The flow was successfully programmed
 * @retval    !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_FlowWrite(NtFlowStream_t hStream, NtFlow_t* flow, int timeout);

/**
 * @brief Read a flow information record
 *
 * This function will attempt to read a flow information record. If a record
 * is available in the stream it will be returned in the record pointed
 * to by "info".
 *
 * @param[in]  hStream   The flow stream handle obtained in @ref NT_FlowOpen_Attr
 * @param[out] info      Pointer to flow info structure the record is returned in
 * @param[in]  timeout   Timeout in ms before failing to program the flow (-1 = retry indefinitely)
 * @retval     NT_SUCCESS     A flow information record was successfully read
 * @retval     !=NT_SUCCESS   Error - use @ref NT_ExplainError for an error description
 */
int NT_FlowRead(NtFlowStream_t hStream, NtFlowInfo_t* info, int timeout);

/**
 * @brief Read a flow status record
 *
 * This function will attempt to read a flow status record. A status record
 * is an async result response for an NT_FlowWrite. If a record
 * is available in the stream it will be returned in the record pointed
 * to by "status".
 *
 * There are 5 types of status records:
 *
 * LearnDone which signals a succesful flow program operation
 *
 * LearnFail which signals an unsuccesful flow program operation
 *
 * LearnIgnore which signals an ignored flow program operation (flow already exists)
 *
 * UnlearnDone which signals a succesful flow unlearn operation
 *
 * UnlearnIgnore which signals an ignored flow unlearn operation (flow doesn't exists)
 *
 * Generation of status records can be enabled/disabled individually in ntservice.ini
 *
 *
 * @param[in]  hStream            The flow stream handle obtained in @ref NT_FlowOpen_Attr
 * @param[out] status             Pointer to flow status structure the record is returned in
 * @retval     NT_SUCCESS         A flow status record was successfully read
 * @retval     NT_STATUS_TRYAGAIN No flow status records available at this time
 * @retval     !=NT_SUCCESS       Error - use @ref NT_ExplainError for an error description
 */
int NT_FlowStatusRead(NtFlowStream_t hStream, NtFlowStatus_t* status);

/**
 * @}
 */

#endif
