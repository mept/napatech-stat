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
 * Error codes and error strings.
 */

#ifndef __ERRORCODES_H__
#define __ERRORCODES_H__

/** @def NT_ERRBUF_SIZE
 *  @brief Maximum error message size.
 *
 *  Use this define when creating an error buffer to be sure that there is
 *  room for the largest error message.
 */
#define NT_ERRBUF_SIZE 128

//! @cond Doxygen_Suppress

#ifdef _WIN32
#ifdef LIBNTOS_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#else
#define DLL_API
#endif

#define NT_NTERROR_ERRORS          0x10000000 // Identifies an nterror code
#define NT_INTERNAL_ERRORS         0x20000000 // Marking an error internal in windows
#define NT_SYSTEM_ERRORS           0x40000000 // Marking an error as a system error in windows

/* Error code groups */
#define NT_FIRST_GENERAL_ERROR  (NT_INTERNAL_ERRORS + 0x0000)
#define NT_FIRST_FILTER_ERROR   (NT_INTERNAL_ERRORS + 0x1000)
#define NT_FIRST_PARSER_ERROR   (NT_INTERNAL_ERRORS + 0x2000)
#define NT_FIRST_NIM_ERROR      (NT_INTERNAL_ERRORS + 0x3000)
#define NT_FIRST_AVR_ERROR      (NT_INTERNAL_ERRORS + 0x4000)
#define NT_FIRST_AFU_ERROR      (NT_INTERNAL_ERRORS + 0x5000)

/**
 * Error codes and error strings
 *
 * Format: param1: Error code enum
 *         param2: Error string
 *         param3: Error log string. Used when parameters are
 *                 needed in the error string for logging
 *
 * The Enum is named:
 *  NT_ERROR_"error description"
 *
 * The error string will be named:
 *  NT_ERROR_"error description"_STRING (_STRING is added)
 *
 * The log error string will be named:
 *  NT_ERROR_"error description"_LOG_STRING (_LOG_STRING is
 *  added)
 *
 *  When entering a new error code:
 *  Use macro NT_MAKE_ERR_SET to add a new error group with enum
 *  snd string.
 *  Use macro NT_MAKE_ERROR2 to add a new error code with enum and
 *  string
 *  Use macro NT_MAKE_ERROR3 to add a new error code with enum,
 *  string and log string
 *
 */

/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE
 *
 * Due to the binary compatibility old and unused error codes must not be deleted.
 * unless the API level is increased.
 *
 * New error codes must be added in the bottom of a set!
 *
 * NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE */
#undef NT_SUCCESS

typedef int NtError_t;

#define NT_ALL_ERROR_CODES \
NT_MAKE_ERR_SET(NT_SUCCESS,                                 "Success",                                   0) \
/* Non errors */ \
NT_MAKE_ERR_SET(NT_STATUS_TIMEOUT,                          "Timeout",                                  NT_FIRST_GENERAL_ERROR) \
NT_MAKE_ERROR2(NT_STATUS_TRYAGAIN,                          "Resource temporarily busy, try again") \
NT_MAKE_ERROR2(NT_STATUS_NO_DATA,                           "No data") \
NT_MAKE_ERROR2(NT_STATUS_NO_MORE_DATA,                      "No more data available") \
NT_MAKE_ERROR2(NT_STATUS_END_OF_FILE,                       "EOF indicator") \
/* Warnings */ \
/* General errors */ \
NT_MAKE_ERROR2(NT_ERROR_UNKNOWN_ERROR,                      "Unknown error") \
NT_MAKE_ERROR2(NT_ERROR_INTERNAL_ERROR,                     "Internal error") \
NT_MAKE_ERROR2(NT_ERROR_MEMORY_ALLOCATION_FAILED,           "Memory allocation failed") \
NT_MAKE_ERROR3(NT_ERROR_PORT_OUT_OF_RANGE,                  "Port out of range",                        "Port %d out of range. Range is [0..%d].\n") \
NT_MAKE_ERROR3(NT_ERROR_IPPROTOCOL_OUT_OF_RANGE,            "IpProtocol out of range",                  "Protocol %d out of range. Range is [0..%d].\n") \
NT_MAKE_ERROR3(NT_ERROR_ADAPTER_OUT_OF_RANGE,               "Adapter out of range",                     "Adapter%d out of range. Range is [0..%d].\n") \
NT_MAKE_ERROR2(NT_ERROR_HOSTBUFFER_RX_OUT_OF_RANGE,         "RX host buffer out of range")\
NT_MAKE_ERROR2(NT_ERROR_HOSTBUFFER_TX_OUT_OF_RANGE,         "TX host buffer out of range")\
NT_MAKE_ERROR2(NT_ERROR_HOSTBUFFER_INVALID_TYPE,            "Invalid host buffer type")\
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_COMMAND,                "Command is not supported for this adapter") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_SEQUENCE,               "The sequence, in which the commands are issued, is illegal on this adapter") \
NT_MAKE_ERROR2(NT_ERROR_UNKNOWN_COMMAND,                    "Unknown command") \
NT_MAKE_ERROR2(NT_ERROR_FAILED_GETTING_FASTLOCK,            "Failed to get fastlock") \
NT_MAKE_ERROR2(NT_ERROR_FAILED_RELEASING_FASTLOCK,          "Failed to release fastlock") \
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_NOT_STARTED,             "NT Service is not started") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_STREAM_POINTER,             "Stream pointer invalid") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_STREAM_HANDLE,              "Stream handle invalid") \
NT_MAKE_ERROR2(NT_ERROR_WRONG_STREAM_TYPE,                  "Wrong stream type") \
NT_MAKE_ERROR2(NT_ERROR_ILLEGAL_TIMESTAMP_TYPE,             "Illegal time stamp type") \
NT_MAKE_ERROR2(NT_ERROR_TIMESTAMP_VS_HDR_MISMATCH,          "Detected a time stamp type setting and packet descriptor type setting mismatch") \
NT_MAKE_ERROR2(NT_ERROR_FAILED_SETTING_TIMESTAMP_TYPE,      "Failed to set time stamp type") \
NT_MAKE_ERROR2(NT_ERROR_FAILED_TO_START_LOGGING,            "Failed to start logging") \
NT_MAKE_ERROR2(NT_ERROR_FAILED_TO_READ_DRIVER_LOG,          "Failed to read driver log") \
NT_MAKE_ERROR2(NT_ERROR_FAILED_TO_CLEAR_DRIVER_LOG,         "Failed to clear driver log") \
NT_MAKE_ERROR2(NT_ERROR_DRIVER_ERROR,                       "Driver error") \
NT_MAKE_ERROR2(NT_ERROR_OS_IPC_RMID,                        "Unable to mark IPC area as destroyed") \
NT_MAKE_ERROR2(NT_ERROR_OS_NULL_SHM,                        "NULL pointer passed as shared memory") \
NT_MAKE_ERROR2(NT_ERROR_OS_CREATE_DMA,                      "Failed to create DMA buffer") \
NT_MAKE_ERROR2(NT_ERROR_OS_REQUEST_DMA,                     "Failed to request DMA buffer") \
NT_MAKE_ERROR2(NT_ERROR_OS_RELEASE_DMA,                     "Failed to release DMA buffer") \
NT_MAKE_ERROR2(NT_ERROR_OS_DMA_STILL_MAPPED,                "Failed to release DMA buffer - need to unmap before releasing") \
NT_MAKE_ERROR2(NT_ERROR_OS_INVALID_ADAPTER,                 "OS Function called with invalid adapter number") \
NT_MAKE_ERROR2(NT_ERROR_OS_IOCTL_INVALID_PARAM,             "Ioctl called with invalid parameter") \
NT_MAKE_ERROR2(NT_ERROR_OS_DMA_MAP,                         "Failed to map DMA memory") \
NT_MAKE_ERROR2(NT_ERROR_OS_COMM_CREATE_INVALID_TYPE,        "CommCreate: invalid eType") \
NT_MAKE_ERROR2(NT_ERROR_OS_ACCEPT_CLIENT_TYPE,              "CommAccept: invalid eType") \
NT_MAKE_ERROR2(NT_ERROR_OS_RECV_MSG_SIZE,                   "CommRecv: Message is too big") \
NT_MAKE_ERROR2(NT_ERROR_OS_RECV_MSG_CONN_LOST,              "CommRecv: Connection lost while receiving") \
NT_MAKE_ERROR2(NT_ERROR_OS_FLOCK_OVERFLOW,                  "Too many locks in set") \
NT_MAKE_ERROR2(NT_ERROR_OS_FLOCKEND_INVALID_PARAM,          "FastLockEnd called with invalid parameter") \
NT_MAKE_ERROR2(NT_ERROR_OS_FLOCK_AQUIRE,                    "Failed to acquire FastLock") \
NT_MAKE_ERROR2(NT_ERROR_OS_FLOCK_RELEASE,                   "Failed to release FastLock - CRITICAL ERROR!!") \
NT_MAKE_ERROR2(NT_ERROR_OS_IRQ_EVENT_WAIT_PARAM,            "IRQEventWait called with invalid parameter") \
NT_MAKE_ERROR2(NT_ERROR_OS_NAMED_EVENT_INVALID_PARAM,       "NamedEvenCreate called, but named events not yet created") \
NT_MAKE_ERROR2(NT_ERROR_OS_NAMED_EVENT_MAXED_OUT,           "NamedEvenCreate called, but no more events available") \
NT_MAKE_ERROR2(NT_ERROR_CONFIG_NOT_SUPPORTED,               "Configuration not supported")\
NT_MAKE_ERROR2(NT_ERROR_CONFIG_CONFLICT,                    "Configuration conflict")\
NT_MAKE_ERROR2(NT_ERROR_LOOPBACK_NOT_IMPLEMENTED,           "Loopback not implemented")\
NT_MAKE_ERROR2(NT_ERROR_LOOPBACK_ARG_ILLEGAL,               "Loopback argument illegal")\
NT_MAKE_ERROR2(NT_ERROR_LOOPBACK_CONFLICT,                  "Loopback configuration conflict")\
NT_MAKE_ERROR2(NT_ERROR_IFG_CONFIG_ERROR,                   "IFG min or max configuration error")\
NT_MAKE_ERROR2(NT_ERROR_ILLEGAL_TIMESTAMP_VALUE,            "Illegal time stamp value") \
NT_MAKE_ERROR2(NT_ERROR_OPERATION_TIMEOUT,                  "An operation timed out") \
NT_MAKE_ERROR2(NT_ERROR_OPERATION_FAILED,                   "An operation failed") \
NT_MAKE_ERROR2(NT_ERROR_32_64_BIT_MISMATCH,                 "A 32bit/64bit mismatch between ntservice and NTAPI") \
NT_MAKE_ERROR2(NT_ERROR_LOOPBACK_NOT_AVAILABLE,             "Loopback not available")\
NT_MAKE_ERROR2(NT_ERROR_NTHW_MODULE_NOT_SUPPORTED,          "Nthw module register not in FPGA") \
NT_MAKE_ERROR3(NT_ERROR_NUMANODE_IS_OFFLINE,                "NUMANode is offline",                      "NUMANode %u is offline") \
NT_MAKE_ERROR2(NT_ERROR_BONDING_SLAVE_TS_NO_CONFIG,         "Bonding Slave misses timesync configuration") \
NT_MAKE_ERROR2(NT_ERROR_BONDING_MASTER_NO_TS_SYNC,          "Bonding Master failed initial time synchronization") \
NT_MAKE_ERROR2(NT_ERROR_BONDING_SLAVE_NO_TS_SYNC,           "Bonding Slave failed initial time synchronization") \
NT_MAKE_ERROR2(NT_ERROR_PERMISSION_DENIED,                  "Permission denied") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_EVENT,                      "Invalid of unknown event type specified") \
NT_MAKE_ERROR2(NT_ERROR_EVENT_RAISE_NOT_ACTIVE,             "Raising events not activated. Specify a listen event on open") \
NT_MAKE_ERROR2(NT_ERROR_TX_RINGBUFFER_NOT_SUPPORTED,        "Tx ring buffer is not supported") \
NT_MAKE_ERROR2(NT_ERROR_TX_RINGBUFFER_PKT_SEND_FAILED,      "Tx ring buffer packet send failed") \
NT_MAKE_ERROR2(NT_ERROR_VALUE_OUT_OF_RANGE,                 "A value was out of range") \
NT_MAKE_ERROR2(NT_ERROR_MALFORMED_ITEM,                     "Malformed item") \
NT_MAKE_ERROR3(NT_ERROR_GROUP_OUT_OF_RANGE,                 "GroupId out of range",                        "GroupId %d out of range. Range is [0..%d].\n") \
NT_MAKE_ERROR2(NT_ERROR_DESCR_BIT_POSITION_OUT_OF_RANGE,    "The descriptor bit position is out of range") \
NT_MAKE_ERROR2(NT_ERROR_TX_DESCR_MODE_UNKNOWN,              "The chosen TX descriptor is unknown or unsupported") \
NT_MAKE_ERROR2(NT_ERROR_FILE_OPEN,                          "A file open operation failed") \
NT_MAKE_ERROR2(NT_ERROR_FILE_READ,                          "A file read operation failed") \
NT_MAKE_ERROR2(NT_ERROR_FILE_WRITE,                         "A file write operation failed") \
NT_MAKE_ERROR2(NT_ERROR_THREAD_START,                       "Failed starting a thread") \
NT_MAKE_ERROR2(NT_ERROR_DRIVER_AND_NTAPI_VERSION_MISMATCH,  "Mismatch of driver and NTAPI libraries") \
/* Filter error codes */ \
NT_MAKE_ERR_SET(NT_ERROR_SPLIT,                             "Split",                                    NT_FIRST_FILTER_ERROR) \
NT_MAKE_ERROR2(NT_ERROR_FILTER_TOO_BIG,                     "The filter is too big") \
NT_MAKE_ERROR2(NT_ERROR_IMPLICIT_EMPTY_FILTER,              "Implicit empty filter") \
NT_MAKE_ERROR2(NT_ERROR_RETRY,                              "Retry") \
NT_MAKE_ERROR2(NT_ERROR_CONFLICTING_FILTER,                 "Conflicting filter") \
NT_MAKE_ERROR2(NT_ERROR_IMPLICIT_ALL_FILTER,                "Implicit all filter") \
NT_MAKE_ERROR2(NT_ERROR_NOT_MERGED,                         "Not merged") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_NTPLID,                     "Invalid NtplId") \
NT_MAKE_ERROR2(NT_ERROR_NTPLID_ALREADY_USED,                "NtplId is already used") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_PORT,                       "Invalid port") \
NT_MAKE_ERROR2(NT_ERROR_PORTS_NOT_ON_SAME_ADAPTER,          "Ports not on same adapter") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_HASHMODE,                   "Invalid HashMode option for selected HashMode") \
NT_MAKE_ERROR2(NT_ERROR_SLICEOFFSET_ZERO,                   "SliceOffset cannot be 0 without a SliceAddHeader option") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_HASHMODE,               "Unsupported hash mode") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_HASHMODE_OPTION,        "Unsupported hash option") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_HASHMASK,               "Unsupported hash mask") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_ERROR_FILTER,           "Unsupported error filter") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_PROTOCOL_FILTER,        "Unsupported protocol filter") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_IPMATCH_FILTER,         "Unsupported IP match filter") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_KEYMATCH_FILTER,        "Unsupported keymatch filter") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_KEY_FILTER,             "Unsupported key filter") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_IPMATCHLIST_FILTER,     "Unsupported IP match list filter") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_PATTERN_FILTER,         "Unsupported pattern filter") \
NT_MAKE_ERROR2(NT_ERROR_WISMODE_ENABLED_ON_DESTINATION_PORT,"Wismode is enabled on destination port") \
NT_MAKE_ERROR2(NT_ERROR_IPMATCHLIST_LISTTYPE_CONFLICT,      "IPMatchList ListType conflict") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_IPFMODE_OPTION,         "Unsupported IPFMode option") \
NT_MAKE_ERROR2(NT_ERROR_UNKNOWN_DATATYPE,                   "KeySet value has unknown datatype") \
NT_MAKE_ERROR2(NT_ERROR_RESOURCE_IN_USE,                    "Resource is in use and cannot be released/re-configured") \
/* Parser error codes */ \
NT_MAKE_ERR_SET(NT_ERROR_SYNTAX_ERROR,                      "Syntax error",                             NT_FIRST_PARSER_ERROR) \
NT_MAKE_ERROR2(NT_ERROR_BUFFER_TOO_LONG,                    "Buffer too long") \
NT_MAKE_ERROR3(NT_ERROR_DUPLICATE_COMMAND,                  "Duplicate command",                        "Duplicate command \"%s\"") \
NT_MAKE_ERROR2(NT_ERROR_PORT_RANGE_OUT_OF_RANGE,            "Port option must include all ports on the adapter") \
NT_MAKE_ERROR3(NT_ERROR_HOSTBUFFER_OUT_OF_RANGE,            "Host buffer number out of range",          "Host buffer number out of range: %d. Must be between %d and %d") \
NT_MAKE_ERROR3(NT_ERROR_INVALID_NUMANODE_RANGE,             "Invalid NUMANode range",                   "Invalid NUMANode range: (%d..%d)") \
NT_MAKE_ERROR3(NT_ERROR_NUMANODE_OUT_OF_RANGE,              "NUMANode out of range",                    "NUMANode out of range %d. Max NUMANode is %d") \
NT_MAKE_ERROR3(NT_ERROR_TOO_MANY_VALUES,                    "Too many values",                          "Too many values: Max %d values allowed") \
NT_MAKE_ERROR3(NT_ERROR_SWAPPED_RANGE,                      "Illegal range",                            "Illegal range (%d..%d). Must be swapped") \
NT_MAKE_ERROR3(NT_ERROR_STREAMID_OUT_OF_RANGE,              "Stream ID out of range",                   "Stream ID out of range %d. Max Stream ID is %d") \
NT_MAKE_ERROR3(NT_ERROR_MISSING_STREAMID,                   "Missing stream ID",                        "Missing stream ID") \
NT_MAKE_ERROR3(NT_ERROR_SOURCE_PORT_OUT_OF_RANGE,           "Source port number out of range",          "Source port number out of range: %d. Max port number is %d") \
NT_MAKE_ERROR3(NT_ERROR_DESTINATION_PORT_OUT_OF_RANGE,      "Destination port number out of range",     "Destination port number out of range: %d. Max port number is %d") \
NT_MAKE_ERROR3(NT_ERROR_PRIORITY_OUT_OF_RANGE,              "Priority out of range",                    "Priority out of range: %d") \
NT_MAKE_ERROR3(NT_ERROR_TIMEOUT_OUT_OF_RANGE,               "Timeout out of range",                     "Timeout out of range: %d. Must be between %d and %d") \
NT_MAKE_ERROR3(NT_ERROR_OFFSET_OUT_OF_RANGE,                "Offset out of range",                      "Offset out of range: %d. The maximum allowed value is %d") \
NT_MAKE_ERROR3(NT_ERROR_ILLEGAL_COMPERATOR,                 "Illegal comparator used",                  "Illegal comparator used in \"%s\"") \
NT_MAKE_ERROR3(NT_ERROR_MISSING_CHAR_IN_MACRO,              "Missing character in macro name",          "Missing '%c' in macro name") \
NT_MAKE_ERROR3(NT_ERROR_ILLEGAL_CHARACTERS_IN_MACRO_NAME,   "Illegal characters in macro name",         "Illegal characters in macro name '%c'") \
NT_MAKE_ERROR3(NT_ERROR_MACRO_NAME_TOO_LONG,                "Macro name is too long",                   "Macro name is too long: %d chars. Max length is %d chars") \
NT_MAKE_ERROR3(NT_ERROR_ILLEGAL_CHARACTERS_IN_MACRO_DEF,    "Illegal characters in macro definition",   "Illegal characters in macro definition '%c'") \
NT_MAKE_ERROR3(NT_ERROR_MACRO_DEF_TOO_LONG,                 "Macro definition is too long",             "Macro definition is too long. Max length is %d") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_ARGS_IN_MACRO_DEF,          "Invalid args in macro definition") \
NT_MAKE_ERROR3(NT_ERROR_POWER_SWITCH_DELAY_TOO_LARGE,       "Power switch delay too large",             "Power switch delay too large %d. Max delay is %d") \
NT_MAKE_ERROR2(NT_ERROR_RESERVEDDMAPOOLSIZE_MULTIPLE_OF_4,  "ReservedDMAPoolSize must be a multiple of 4") \
NT_MAKE_ERROR3(NT_ERROR_NUMSEGMENTS_TOO_LARGE,              "NumSegments out of range",                 "NumSegments must be between %d and %d") \
NT_MAKE_ERROR3(NT_ERROR_INVALID_SEGMENT_SIZE,               "Invalid segment size",                     "Invalid segment size. Valid values are %u, %u and %u") \
NT_MAKE_ERROR3(NT_ERROR_INVALID_MAX_LATENCY,                "Invalid max latency",                      "Invalid max latency. Must be between %d and %d") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_MAX_LATENCY2,               "Invalid max latency - must be a multiple of 100") \
NT_MAKE_ERROR3(NT_ERROR_EXT_DESC_LENGTH_LARGE,              "Extended descriptor length too large",     "Extended descriptor length too large. Must be less than %d") \
NT_MAKE_ERROR3(NT_ERROR_TIME_SYNC_OFFSET_LARGE,             "Time sync offset too large",               "Time sync offset too large - must be less than %d") \
NT_MAKE_ERROR3(NT_ERROR_IFG_TOO_LARGE,                      "IFG too large",                            "IFG too large. Must be less than %d") \
NT_MAKE_ERROR3(NT_ERROR_COLOR_OUT_OF_RANGE,                 "Color out of range",                       "Color out of range: %d. Max color is %d") \
NT_MAKE_ERROR3(NT_ERROR_SLICEOFFSET_OUT_OF_RANGE,           "Slice offset out of range",                "Slice offset out of range: %d. Max frame length is %d") \
NT_MAKE_ERROR3(NT_ERROR_SET_DESC_PORT_OUT_OF_RANGE,         "Set descriptor port out of range",         "Set descriptor port out of range: %d. Max port number is: %d") \
NT_MAKE_ERROR3(NT_ERROR_FILENAME_TOO_LONG,                  "File name too long",                       "File name too long: %d. Max length is %d") \
NT_MAKE_ERROR3(NT_ERROR_HASHVALUE_OUT_OF_RANGE,             "Hash value out of range",                  "Hash value out of range: {0x%02X:0x%02X}. Max value is 0x%02X") \
NT_MAKE_ERROR3(NT_ERROR_HASHSPLIT_PART_OUT_OF_RANGE,        "Hash split part out of range",             "Hash split part %d out of range: Must be between %d and %d") \
NT_MAKE_ERROR3(NT_ERROR_HASHSPLIT_VALUE_OUT_OF_RANGE,       "Hash split value out of range",            "Hash split value %d out of range: Must be less than %d") \
NT_MAKE_ERROR3(NT_ERROR_HASHSPLIT_VALUE_RANGE_ERROR,        "Hash split value range is illegal",        "Hash split value range (%d..%d) is illegal: Value must be less than %d and in right order") \
NT_MAKE_ERROR3(NT_ERROR_HASHSPLIT_VALUE_LIST_ERROR,         "Hash split value illegal",                 "Hash split value illegal - only one value allowed") \
NT_MAKE_ERROR3(NT_ERROR_NUMBER_RANGE_TOO_LARGE256,          "Number too large",                         "Number too large (%d..%d): Must be less than %d") \
NT_MAKE_ERROR3(NT_ERROR_NUMBER_TOO_LARGE256,                "Number too large",                         "Number too large %d: Must be less than %d") \
NT_MAKE_ERROR3(NT_ERROR_TOO_MANY_EVENTS,                    "Too many events",                          "Too many events: Max %d events allowed") \
NT_MAKE_ERROR3(NT_ERROR_LENGTH_TOO_LARGE,                   "Length too large",                         "Length too large %d. Must be less than %d") \
NT_MAKE_ERROR3(NT_ERROR_DATAMASK_OUT_OF_RANGE,              "Data mask out of range",                   "Data mask out of range [%d:%d]. Must be less or equal to %d") \
NT_MAKE_ERROR3(NT_ERROR_BITMASK_ILLEGAL,                    "Bitmask illegal",                          "Bitmask illegal: Second value must be less than first value [%d..%d]") \
NT_MAKE_ERROR3(NT_ERROR_BITMASK_ILLEGAL31,                  "Bitmask illegal",                          "Bitmask illegal: First value must be less than 31 [%d..%d]") \
NT_MAKE_ERROR2(NT_ERROR_MISMATCH_DATATYPE_DATAVALUE,        "Mismatch between DataType and DataValue") \
NT_MAKE_ERROR3(NT_ERROR_DATA_OUT_OF_RANGE,                  "Data out of range",                        "Data out of range %d. Must be less or equal to %d") \
NT_MAKE_ERROR3(NT_ERROR_DATA_OUT_OF_RANGE_HEX,              "Data out of range",                        "Data out of range %X. Must be less or equal to %X") \
NT_MAKE_ERROR3(NT_ERROR_INVALID_DATA_RANGE,                 "Invalid data range",                       "Invalid data range (%d..%d). %d must be less than %d") \
NT_MAKE_ERROR3(NT_ERROR_DATA_RANGE_OUT_OF_RANGE,            "Data out of range",                        "Data out of range (%d..%d). Must be less or equal to %d") \
NT_MAKE_ERROR2(NT_ERROR_DATATYPE_MUST_BE_DEFINED,           "Data type must be defined") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_BYTE_STRING_0X,             "Invalid byte string. Missing \"0x\"") \
NT_MAKE_ERROR2(NT_ERROR_FEW_CHARACTERS_BYTE_STRING,         "Too few characters in byte string") \
NT_MAKE_ERROR2(NT_ERROR_MANY_CHARACTERS_BYTE_STRING,        "Too many characters in byte string") \
NT_MAKE_ERROR3(NT_ERROR_ILLEGAL_STRING_MUST_BE,             "Illegal string",                          "Illegal string - must be %d characters long") \
NT_MAKE_ERROR2(NT_ERROR_MISSING_OR_ILLEGAL_DATATYPE,        "Missing or illegal DataType") \
NT_MAKE_ERROR2(NT_ERROR_IP_ADDRESS_OUT_OF_RANGE,            "IP address out of range") \
NT_MAKE_ERROR2(NT_ERROR_MAC_ADDRESS_OUT_OF_RANGE,           "MAC address out of range") \
NT_MAKE_ERROR2(NT_ERROR_MISSING_FILTER_EXPRESSIONS,         "Missing filter expressions") \
NT_MAKE_ERROR2(NT_ERROR_MISSING_STREAM_ID,                  "Missing stream ID") \
NT_MAKE_ERROR2(NT_ERROR_MISSING_EVENTS,                     "Missing events") \
NT_MAKE_ERROR2(NT_ERROR_DUPLICATE_MACRO,                    "Duplicate macro") \
NT_MAKE_ERROR2(NT_ERROR_MACRO_NOT_FOUND,                    "Error deleting macro - macro not found") \
NT_MAKE_ERROR2(NT_ERROR_MACRO_NO_ARGUMENT,                  "Cannot find argument in data") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_NO_OF_ARGS_IN_MACRO_DEF,    "Invalid number of arguments in macro definition") \
NT_MAKE_ERROR2(NT_ERROR_MISSING_PAREN_IN_MACRO_DEF,         "Missing brackets '(' or ')' in macro argument") \
NT_MAKE_ERROR2(NT_ERROR_MISSING_COMMA_IN_MACRO_DEF,         "Missing comma ',' in macro argument") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_STREAM,                     "Invalid stream") \
NT_MAKE_ERROR2(NT_ERROR_NOT_NT_CAPFILE,                     "File doesn't contain correct file header") \
NT_MAKE_ERROR2(NT_ERROR_INSUFFICIENT_DATA,                  "Insufficient data") \
NT_MAKE_ERROR2(NT_ERROR_NO_BONDING_MASTER,                  "No bonding master detected") \
NT_MAKE_ERROR2(NT_ERROR_BONDING_PLACEMENT,                  "Master and slave adapters have not been configured together") \
NT_MAKE_ERROR2(NT_ERROR_HOSTBUFFER_MERGE,                   "Host buffer time stamp merge error") \
NT_MAKE_ERROR2(NT_ERROR_NO_ADAPTERS,                        "No adapters located in the system") \
NT_MAKE_ERROR2(NT_ERROR_SENSOR_NOT_FOUND,                   "The sensor cannot be located") \
NT_MAKE_ERROR2(NT_ERROR_IMAGE_CORRUPT,                      "Image is corrupt") \
NT_MAKE_ERROR2(NT_ERROR_IMAGE_NOT_COMPATIBLE,               "Image is not compatible") \
NT_MAKE_ERROR2(NT_ERROR_NO_SAFEMODE,                        "There is no safe mode support") \
NT_MAKE_ERROR2(NT_ERROR_IMAGE_VERIFY_FAILED,                "Image verification failed") \
NT_MAKE_ERROR2(NT_ERROR_IMAGE_UPDATE_IN_PROGRESS,           "Image update already in progress") \
NT_MAKE_ERROR2(NT_ERROR_PROCESS_DOES_NOT_EXIST,             "Process does not exist") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_EXTENDED_DESCRIPTOR,    "The extended descriptor is not supported") \
NT_MAKE_ERROR2(NT_ERROR_LIBRARY_NOT_COMPATIBLE,             "The library is not compatible") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_PARAMETER,                  "The parameter is not valid") \
NT_MAKE_ERROR2(NT_ERROR_SHARED_MEM_CORRUPTED,               "Shared memory corrupted") \
NT_MAKE_ERROR2(NT_ERROR_SHARED_MEM_ILLEGAL_VERSION,         "Illegal version of shared memory") \
NT_MAKE_ERROR2(NT_ERROR_SERVICE_ERROR,                      "Not able to start the service - see the log") \
NT_MAKE_ERROR2(NT_ERROR_SERVER_CANNOT_CONNECT,              "Server cannot connect") \
NT_MAKE_ERROR2(NT_ERROR_NT_INIT_ALREADY_CALLED,             "NT_Init has already been called") \
NT_MAKE_ERROR2(NT_ERROR_HOSTBUFFER_MIX,                     "host buffers from in-line and capture adapters cannot be merged in a streamid") \
NT_MAKE_ERROR2(NT_ERROR_FEATURE_NOT_SUPPORTED,              "Feature not supported") \
NT_MAKE_ERROR2(NT_ERROR_HASHMASK_ALREADY_SET,               "Hash mask already set for the specified hash mode") \
NT_MAKE_ERROR2(NT_ERROR_SEGMENT_MERGE_CONFLICT,             "Segment interface cannot merge traffic") \
NT_MAKE_ERROR2(NT_ERROR_TXPORT_MISSING,                     "TxPort option required for in-line adapters") \
NT_MAKE_ERROR2(NT_ERROR_NO_AVAILABLE_HOSTBUFFER,            "No available host buffer found matching the command") \
NT_MAKE_ERROR2(NT_ERROR_MERGE_NOT_POSSIBLE,                 "Merging is not possible") \
NT_MAKE_ERROR2(NT_ERROR_INLINE_SEGMENT_CONFLICT,            "The segment interface cannot be used with in-line adapters") \
NT_MAKE_ERROR2(NT_ERROR_MISSING_SOURCEPORT,                 "Missing source port") \
NT_MAKE_ERROR2(NT_ERROR_MISSING_DESTINATIONPORT,            "Missing destination port") \
NT_MAKE_ERROR2(NT_ERROR_MISSING_HASHMASKS,                  "Missing hash masks") \
NT_MAKE_ERROR2(NT_ERROR_HASHMODE_ALREADY_SET,               "Hash mode is already set") \
NT_MAKE_ERROR2(NT_ERROR_MISSING_SETUP_OPTION,               "Missing setup option") \
NT_MAKE_ERROR2(NT_ERROR_TIMESTAMPTYPE_MIX,                  "Time stamp types cannot be mixed in a stream ID") \
NT_MAKE_ERROR2(NT_ERROR_STREAM_LOCK_LIST,                   "Failed to acquire the stream list lock") \
NT_MAKE_ERROR2(NT_ERROR_INVALID_PACKET,                     "Invalid packet")  \
NT_MAKE_ERROR2(NT_ERROR_INVALID_PACKET_SIZE,                "Invalid packet size - length must be 8 bytes aligned") \
NT_MAKE_ERROR2(NT_ERROR_RESOURCE_UNAVAILABLE,               "Resource unavailable") \
NT_MAKE_ERROR2(NT_ERROR_LOG_FILE_ERROR,                     "Unable to open log file") \
NT_MAKE_ERROR2(NT_ERROR_INI_FILE_ERROR,                     "Illegal value found in the ini-file") \
NT_MAKE_ERROR2(NT_ERROR_INI_FILE_INTERNAL,                  "Internal error reading the ini-file") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_VERSION_MISMATCH,             "NT_Init called with version mismatch") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_INFO_CLIENT_NOT_INIT,         "NT_InfoOpen client not initialized") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_INFO_CLIENT_NULL_STREAM,      "NT_Info stream is NULL") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_INFO_INVALID_HANDLE,          "NT_Info invalid handle used") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_INFO_INVALID_CMD,             "NT_Info invalid command") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_NET_PORT_NO_TX_SUPPORT,       "Port does not support TX") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_NET_NO_TX_BUFFERS,            "No TX buffers allocated on adapter") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_NET_TX_PORTS_INVALID,         "Some TX ports specified in TX mask are invalid") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_NET_TX_PORT_INVALID,          "TX ports specified is not in TX mask") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_NET_TX_PKT_SIZE_INVALID,      "TX packet size is not supported") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_NET_TX_GET_OPTION_INVALID,    "TX get option invalid") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_NET_TX_TSI_NOT_SUPPORTED ,    "Timestamp inject configured but not supported") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_NET_TX_L3_L4_CS_NOT_SUPPORTED , "Calculation of L3 and L4 checksum configured but not supported") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_NET_FCS_NOT_SUPPORTED ,       "Calculation of FCS checksum configured but not supported") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_STAT_GET_FAILED,              "Could not receive updated statistics in a reasonable time") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_STAT_GET_INVALID_CMD,         "NT_StatRead called with unknown command") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_SYSTEM_NULL_STREAM,           "NT_System stream is NULL - call NT_Open to create a stream") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_SYSTEM_INVALID_STREAM,        "NT_System stream is invalid") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_SYSTEM_READ_INVALID_CMD,      "NT_SystemRead called with unknown command") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_SYSTEM_READ_NO_VPD_SUPPORT,   "NT_SystemRead VPD requested, but not supported") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_NET_RELEASE_INVALID_BUF,      "Tried to release an invalid buffer - timed out NetxxGet call must not be released") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_CLOSE_WITH_INUSE_BUFFERS,     "NT_NetRxClose called with pending in-use buffers") \
NT_MAKE_ERROR2(NT_ERROR_NT_NOT_INITIALIZED,                 "NT not initialized")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_LIMITED_MODE,            "NT service running in limited mode due to initialization errors - command not permitted")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_STARTUP_FAILED_VPD,      "NT service startup failed - VPD initialization failed")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_INI_FILE_BUSID_CLASH,    "The ini-file contains adapters with same bus ID")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_INI_FILE_ADAPTER_MISSING,"The ini-file contains adapters not present")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_INI_FILE_ADPTERX_MISSING,"The ini-file [Adapter(x)] not found")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_HBH_TX_FAILED,           "Transmit failed")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_HBH_UNSUPPORTED_SDRAM,   "SDRAM not supported")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_HBM_NOT_RUNNING,         "HBM is not running")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_HBM_NO_EMPTY_SLOT,       "HBM reports no empty slot found (internal error)")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_HBM_NO_TX_HOSTBUFFER,    "HBM reports no free TX host buffers found")\
NT_MAKE_ERROR3(NT_ERROR_NT_SERVICE_HBM_NO_TX_HOSTBUFFER_NUMA,"HBM reports no free TX host buffers found", "HBM reports no free TX host buffers found on NUMA %d (requested numa %d)")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_HBM_HOSTBUF_IDX_ERROR,   "HBM failed to find host buffer index (internal error)")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_HBM_STREAMMAP_ERROR,     "HBM reports no free stream maps found (internal error)")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_HBM_EGRESS_ERROR,        "HBM host buffer already mapped to egress port")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_HBM_EGRESS_MAP_ERROR,    "HBM error - only RX host buffers may be mapped to an egress port")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_HBM_INIT_TOO_MANY_HB,    "HBMInit: too many host buffers specified")\
NT_MAKE_ERROR2(NT_ERROR_NT_SERVICE_HBM_INIT_NO_NUMA,        "HBMInit: no NUMA nodes specified")\
NT_MAKE_ERROR2(NT_ERROR_CPLD_INVALID_REG,                   "Invalid CPLD register to read/write")\
NT_MAKE_ERROR2(NT_ERROR_ADAPTER_BONDING_READ_DAUGHTER_FAILED,"Adapter bonding: daughter board read failed")\
NT_MAKE_ERROR2(NT_ERROR_ADAPTER_BONDING_INLINE_ADAPTER,     "Adapter bonding: In-line adapters cannot be bonded with expansion cards")\
NT_MAKE_ERROR2(NT_ERROR_ADAPTER_BONDING_TRAINING,           "Adapter bonding: Expansion bus training failed")\
NT_MAKE_ERROR2(NT_ERROR_ADAPTER_BONDING_SLAVE_ALREADY_BONDED,"Adapter bonding: Slave already bonded")\
NT_MAKE_ERROR2(NT_ERROR_ADAPTER_BONDING_SLAVE_NOT_FOUND,    "Adapter bonding: Failed to find bonded slave")\
NT_MAKE_ERROR2(NT_ERROR_ADAPTER_BONDING_TOO_MANY_BUFFERS,   "Adapter bonding: Too many host buffers defined (Total max 32)..")\
NT_MAKE_ERROR2(NT_ERROR_SDRAM_INIT_FAILED,                  "SDRAM DDR: Initialize controller failed (internal error)")\
NT_MAKE_ERROR2(NT_ERROR_SDRAM_CALIB_FAILED,                 "SDRAM DDR: Calibration failed (internal error)")\
NT_MAKE_ERROR2(NT_ERROR_SDRAM_SELFTEST_FAILED,              "SDRAM DDR: Self test failed (internal error)")\
NT_MAKE_ERROR2(NT_ERROR_SDRAM_START_FAILED,                 "SDRAM DDR: Start failed (internal error)")\
NT_MAKE_ERROR2(NT_ERROR_SDRAM_CONFIGURE_FEEDS_FAILED,       "SDRAM DDR: Configure feeds failed (internal error)")\
NT_MAKE_ERROR2(NT_ERROR_SENSOR_ADD_FAILED,                  "Add sensor failed (internal error)")\
NT_MAKE_ERROR2(NT_ERROR_VPD_FAILED,                         "No VPD info")\
NT_MAKE_ERROR2(NT_ERROR_VPD_INIT_FLASH_READ_FAILED,         "VPD init: Flash read failed")\
NT_MAKE_ERROR2(NT_ERROR_VPD_INIT_DEFRAG_FAILED,             "VPD init: Failed defragmenting sectors (internal error)")\
NT_MAKE_ERROR2(NT_ERROR_VPD_SUPPLIED_MEM_TOO_SMALL,         "Not enough memory in buffer for VPD info")\
NT_MAKE_ERROR2(NT_ERROR_RESERVED1,                          "Reserved")\
NT_MAKE_ERROR2(NT_ERROR_RESERVED2,                          "Reserved")\
NT_MAKE_ERROR2(NT_ERROR_RESERVED3,                          "Reserved")\
NT_MAKE_ERROR2(NT_ERROR_NTPL_FILTER_UNSUPP_FPGA,            "NTPL: Unsupported FPGA")\
NT_MAKE_ERROR2(NT_ERROR_NT_TERMINATING,                     "NT library is terminating")\
NT_MAKE_ERROR2(NT_ERROR_NT_READING_FLASH_FAILED,            "Reading flash failed")\
NT_MAKE_ERROR2(NT_ERROR_NT_WRITING_FLASH_FAILED,            "Writing flash failed")\
NT_MAKE_ERROR2(NT_ERROR_NT_INIT_SPI_FAILED,                 "Initialising SPI failed")\
NT_MAKE_ERROR2(NT_ERROR_NT_INIT_I2C_FAILED,                 "Initialising I2C failed")\
NT_MAKE_ERROR2(NT_ERROR_RXAUI_LINK_ERROR,                   "RXAUI link error")\
NT_MAKE_ERROR2(NT_ERROR_NIM_NOT_PRESENT,                    "NIM not present")\
NT_MAKE_ERROR2(NT_ERROR_PROFILE_NOT_ALLOWED,                "The adapter cannot use the requested profile")\
NT_MAKE_ERROR2(NT_ERROR_LOG_NOT_READY,                      "The log is not ready")\
NT_MAKE_ERROR2(NT_ERROR_MERGE_NOT_ALLOWED,                  "Merge between different adapter types is not allowed")\
NT_MAKE_ERROR2(NT_ERROR_IPF_MERGE_NOT_ALLOWED,              "IPF unmatched stream merge on in-line adapter not allowed")\
NT_MAKE_ERROR2(NT_ERROR_TX_LASER_DISABLE_NOT_SUPPORTED,     "TX laser software disable is not supported")\
NT_MAKE_ERROR2(NT_ERROR_TX_LASER_DISABLE_FAILED,            "TX laser disable failed")\
NT_MAKE_ERROR2(NT_ERROR_ADAPTER_NOT_SUPPORTED,              "Adapter is not supported")\
NT_MAKE_ERROR2(NT_ERROR_PACKET_IF_NOT_SUPP,                 "When running PCAP header, the packet interface is not supported")\
NT_MAKE_ERROR2(NT_ERROR_MULTI_DATA_MASK,                    "Only one data mask definition allowed")\
NT_MAKE_ERROR2(NT_ERROR_HOSTBUFFER_TOO_SMALL,               "The host buffer is too small")\
NT_MAKE_ERROR2(NT_ERROR_TXPORT_SAME_ADAPTER_MISMATCH,       "A TX port is specified, receiving data from a capture adapter. The TX port must be on the same adapter as the receiving port(s)")\
NT_MAKE_ERROR2(NT_ERROR_TXPORT_INLINE_MISMATCH,             "The TX port does not match an in-line adapter")\
NT_MAKE_ERROR2(NT_ERROR_TXPORT_PRODUCTFAMILY_MISMATCH,      "The TX port does not match an adapter of same product family")\
NT_MAKE_ERROR2(NT_ERROR_STREAM_PROFILE_MISMATCH,            "The stream cannot merge from adapters with different profiles")\
NT_MAKE_ERROR2(NT_ERROR_STREAM_PRODUCTFAMILY_MISMATCH,      "The stream cannot merge from adapters of different product families") \
NT_MAKE_ERROR3(NT_ERROR_INVALID_NUMBER,                     "Syntax error - invalid number",             "Syntax error - invalid number \"%s\"") \
NT_MAKE_ERROR3(NT_ERROR_HOSTBUFFERSIZE_OUT_OF_RANGE,        "Host buffer size out of range",             "Host buffer size %d MByte out of range - must be between %d MByte and %d MByte") \
NT_MAKE_ERROR2(NT_ERROR_RETRANSMIT_PORT_FILTER_NOT_ALLOWED, "Port filter is not allowed in retransmit") \
NT_MAKE_ERROR2(NT_ERROR_SLICE_RETX_WITHOUT_RETRANSMIT,      "Cannot setup retransmit slicer without a retransmit destination port") \
NT_MAKE_ERROR2(NT_ERROR_PCI_BANDWIDTH_MEASUREMENT_FAILED,   "The measurement of PCI bandwidth failed - please check the log") \
NT_MAKE_ERROR3(NT_ERROR_SENSOR_SOURCE_NOT_SUPPORTED,        "Sensor source not supported",              "Sensor source %d not supported") \
NT_MAKE_ERROR3(NT_ERROR_SENSOR_SOURCEINDEX_OUT_OF_RANGE,    "Sensor source index out of range",         "Sensor source index %d out of range - range is [0..%d]\n") \
NT_MAKE_ERROR3(NT_ERROR_SENSOR_INDEX_OUT_OF_RANGE,          "Sensor index out of range",                "Sensor index %d out of range - range is [0..%d]\n") \
NT_MAKE_ERROR2(NT_ERROR_SENSOR_LIMITS_OUT_OF_RANGE,         "Sensor limits out of range")\
NT_MAKE_ERROR2(NT_ERROR_FILEHEADER_ONLY_ON_SEGMENTS,        "The file header can only be retrieved when using the segment interface") \
NT_MAKE_ERROR2(NT_ERROR_STREAMID_TXPORT_MISMATCH,           "The number of stream IDs and TX ports do not match") \
NT_MAKE_ERROR3(NT_ERROR_INVALID_VALUE,                      "Invalid value used",                      "Invalid value %d used\n") \
NT_MAKE_ERROR2(NT_ERROR_UNSUPPORTED_FPGA_MODULE,            "The FPGA is not supported by the adapter") \
NT_MAKE_ERROR2(NT_ERROR_GLOBALSYNC_MODE_NOT_SUPPORTED,      "Global sync mode not supported by inline adapters") \
NT_MAKE_ERROR2(NT_ERROR_I2C_OPERATION_FAILED,               "I2C operation failed")\
NT_MAKE_ERROR2(NT_ERROR_WATCHDOG_TIMEOUT_OUT_OF_RANGE,      "Watchdog timeout out of range") \
NT_MAKE_ERROR2(NT_ERROR_DELAY_OUT_OF_RANGE,                 "Delay out of range") \
NT_MAKE_ERROR2(NT_ERROR_ABSOLUTE_TX_TIMING,                 "Adapter does not support absolute TX timing") \
NT_MAKE_ERROR2(NT_ERROR_PORT_DISABLE,                       "Adapter does not support disabling of the ports") \
NT_MAKE_ERROR2(NT_ERROR_TIMESTAMP_INJECT_OFFSET,            "Adapter does not support timestamp injection offset other than start of frame") \
NT_MAKE_ERROR2(NT_ERROR_GLOBAL_SYNC_INVALID,                "IFG cannot be changed while in Global Sync mode") \
NT_MAKE_ERROR2(NT_ERROR_NT_SPI_RX_BUFFER_TOO_SMALL,         "SPI RX buffer too small")\
NT_MAKE_ERROR2(NT_ERROR_TX_TIMING_NOT_SUPPORTED,            "TX timing cannot be changed for the adapter") \
NT_MAKE_ERROR2(NT_ERROR_TS_INJECT_OFF_MODE_NOT_SUPPORTED,   "Timestamp injection offset mode cannt be changed for the adapter") \
NT_MAKE_ERROR2(NT_ERROR_PTP_CFG_INVALID_PARAM,              "PTP parameter configuration error") \
NT_MAKE_ERROR2(NT_ERROR_DRIVER_VERSION_MISMATCH,            "The kernel driver version does not match the the user mode driver") \
NT_MAKE_ERROR3(NT_ERROR_MASKNO_OUT_OF_RANGE,                "Mask Number out of range",                "Mask number %d out of range. Must be between %d and %d") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_NT_INIT_NOT_CALLED,           "NTAPI is not initialized - NT_Init() has not been called") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_INITIALIZING,                 "NTAPI is initializing") \
NT_MAKE_ERROR2(NT_ERROR_NTAPI_TERMINATING,                  "NTAPI is terminating") \
NT_MAKE_ERROR2(NT_ERROR_OUT_OF_RESOURCES,                   "No more resources available") \
NT_MAKE_ERROR2(NT_IPC_STATUS_CONNECTION_CLOSED, "IPC connection closed")\
NT_MAKE_ERROR2(NT_ERROR_DMA_OUT_OF_RANGE,                   "DMA memory physical address out of range") \
NT_MAKE_ERROR2(NT_ERROR_HOST_BUFFER_MEM_TOO_BIG,            "Host buffer memory size exceeded")\
NT_MAKE_ERROR2(NT_ERROR_PTP_NOT_ENABLED_OR_NOT_AVAIL,       "PTP is not enabled or not available")\
NT_MAKE_ERROR2(NT_ERROR_PTP_DEL_ASYM_OUT_OF_RANGE,          "PTP delay asymmetry out of range")\
NT_MAKE_ERROR3(NT_ERROR_KEYLENGTH_OUT_OF_RANGE,             "Key length out of range",                      "Key length out of range: %d. Must be less than or equal to %d") \
NT_MAKE_ERROR2(NT_ERROR_LINK_ERROR,                         "Link error")\
NT_MAKE_ERROR3(NT_ERROR_TOO_MANY_DESTINATION_PORTS,         "Too many destination ports",                   "Too many destination ports: Max %d ports allowed") \
NT_MAKE_ERROR2(NT_ERROR_FILE_EMPTY,                         "Empty file")\
NT_MAKE_ERROR3(NT_ERROR_INVALID_IDENTIFIER,                 "Invalid identifier used",                      "Invalid identifier '%s' used\n") \
NT_MAKE_ERROR2(NT_ERROR_OPTIONS_MISSING,                    "At least one option must be specified")\
NT_MAKE_ERROR2(NT_ERROR_PCAP_NG_VERSION_NOT_SUPPORTED,      "Supplied PCAP-NG file version is not supported")\
NT_MAKE_ERROR2(NT_ERROR_PCAP_NG_INVALID_RESOLUTION,         "Invalid time stamp resolution found in PCAP-NG file")\
NT_MAKE_ERROR2(NT_ERROR_PCAP_NG_INVALID_PACKET_SIZE,        "Invalid packet size found in PCAP-NG file")\
NT_MAKE_ERROR2(NT_ERROR_CAP_FILE_NOT_RECOGNIZED,            "The supplied capture file format is not recognized")\
NT_MAKE_ERROR2(NT_ERROR_CAP_FILE_PACKET_TOO_LARGE,          "Too large packets found. Captured with LRO (Large Receive Offload) enabled?")\
NT_MAKE_ERROR2(NT_ERROR_CAP_FILE_STORED_LENGTH_INVALID,     "Packet with invalid stored length found")\
NT_MAKE_ERROR2(NT_ERROR_CAP_FILE_CREATION_ERROR,            "Could not open target file for file format conversion")\
NT_MAKE_ERROR2(NT_ERROR_CAP_FILE_CORRUPTED_ERROR,           "The capture file is corrupted")\
NT_MAKE_ERROR2(NT_ERROR_NSEB_NOT_ACTIVE,                    "NSEB interface not active")\
NT_MAKE_ERROR3(NT_ERROR_LENGTH_OUT_OF_RANGE,                "Length out of range", "Length out of range (%d..%d)")\
/* NIM error codes */ \
NT_MAKE_ERR_SET(NT_ERROR_NIM_ERROR,                         "NIM error",                             NT_FIRST_NIM_ERROR) \
NT_MAKE_ERROR2(NT_ERROR_NIM_ID_UNHANDLED,                   "NIM ID unhandled") \
NT_MAKE_ERROR2(NT_ERROR_NIM_FUNC_NOT_SUPP,                  "NIM function not supported") \
NT_MAKE_ERROR2(NT_ERROR_NIM_OPTION_NOT_SUPP,                "NIM option not supported") \
NT_MAKE_ERROR2(NT_ERROR_NIM_NUMBER_OUT_OF_RANGE,            "NIM number out of range") \
NT_MAKE_ERROR2(NT_ERROR_NIM_ADDRESS_OUT_OF_RANGE,           "NIM address out of range") \
NT_MAKE_ERROR2(NT_ERROR_NIM_INTERNAL_ERROR,                 "NIM internal error") \
NT_MAKE_ERROR2(NT_ERROR_NIM_FUNC_FAILED,                    "NIM function failed") \
NT_MAKE_ERROR2(NT_ERROR_NIM_INSUFF_ARRAY_SIZE,              "NIM insufficient array size") \
NT_MAKE_ERROR2(NT_ERROR_NIM_NOT_RECOGNISED,                 "NIM not recognised") \
NT_MAKE_ERROR2(NT_ERROR_NIM_PN_NOT_RECOGNISED,              "NIM product number not recognised") \
NT_MAKE_ERROR2(NT_ERROR_NIM_PWR_CLASS_NOT_SUPPORTED,        "NIM power class not supported") \
NT_MAKE_ERROR2(NT_ERROR_NIM_TYPE_NOT_SUPPORTED,             "NIM type is not supported") \
NT_MAKE_ERROR2(NT_ERROR_NIM_NOT_ACCESSIBLE,                 "NIM not accessible") \
/* AVR error codes */ \
NT_MAKE_ERR_SET(NT_ERROR_AVR_ERROR,                         "AVR error",                             NT_FIRST_AVR_ERROR) \
NT_MAKE_ERROR2(NT_ERROR_AVR_RX_BUFFER_TOO_SMALL,            "AVR RX buffer too small")\
NT_MAKE_ERROR2(NT_ERROR_AVR_OPCODE_RETURNED_ERROR,          "AVR Opcode did not succeed and returned an error")\
NT_MAKE_ERROR2(NT_ERROR_AVR_UNKNOWN_OPCODE_RETURNED,        "AVR did not know the opcode requested")\
NT_MAKE_ERROR2(NT_ERROR_AVR_RETURNED_DATA_COUNT_MISMATCH,   "AVR returned an unexpected number of data bytes")\
NT_MAKE_ERROR2(NT_ERROR_AVR_LOG_VERSION_UNHANDLED,          "AVR log version unhandled")\
NT_MAKE_ERROR2(NT_ERROR_AVR_LOG_INCONSISTENCY,              "AVR log inconsistency")\
NT_MAKE_ERROR2(NT_ERROR_AVR_SENSOR_DATA_NOT_UPDATED,        "AVR did not update sensor data")\
/* AFU error codes */ \
NT_MAKE_ERR_SET(NT_ERROR_AFU_ERROR,                         "AFU error",                             NT_FIRST_AFU_ERROR) \
NT_MAKE_ERROR2(NT_ERROR_AFU_FILE_HANDLING,                  "AFU File handling error")\
NT_MAKE_ERROR2(NT_ERROR_AFU_INVALID_PARAM,                  "AFU Invalid parameter supplied")\
NT_MAKE_ERROR2(NT_ERROR_AFU_BUSY,                           "AFU Resource is busy")\
NT_MAKE_ERROR2(NT_ERROR_AFU_EXCEPTION,                      "AFU An exception occurred")\
NT_MAKE_ERROR2(NT_ERROR_AFU_NOT_FOUND,                      "AFU A required resource was not found ")\
NT_MAKE_ERROR2(NT_ERROR_AFU_NOT_SUPPORTED,                  "AFU Requested operation is not supported")\
NT_MAKE_ERROR2(NT_ERROR_AFU_NO_DRIVER,                      "AFU Driver is not loaded")\
NT_MAKE_ERROR2(NT_ERROR_AFU_NO_DAEMON,                      "AFU FPGA Daemon (fpgad) is not running")\
NT_MAKE_ERROR2(NT_ERROR_AFU_NO_ACCESS,                      "AFU Insufficient privileges or permissions")\
NT_MAKE_ERROR2(NT_ERROR_AFU_RECONF_ERROR,                   "AFU Error while reconfiguring FPGA")\
// !!!Dont add non-AFU error code here

//OBS!
//Before adding a new error code please consider if any of the groups already
//defined (using NT_MAKE_ERR_SET) can contain it which they can under most
//circumstances. If it is something completely new then consider defining a new group


/**
 * Make error table macro
 * a: Name of the error enum
 * b: Error string
 */
#define NT_MAKE_ERROR2(a, b)     a,
/**
 * Make error table macro
 * a: Name of the error enum
 * b: Error string
 * c: Error log string
 */
#define NT_MAKE_ERROR3(a, b, c)  a,
/**
 * Make error table macro
 * a: Name of the error enum
 * b: Error string
 * c: Enum start value of new error group
 */
#define NT_MAKE_ERR_SET(a, b, c) a = c,

/****************************************************************************/
/* Make error code enums                                                    */
/****************************************************************************/
enum NtErrorCodes_e {
  NT_ALL_ERROR_CODES
};

/****************************************************************************/
/* Make error external definition strings for matching to an error code     */
/****************************************************************************/
#undef NT_MAKE_ERROR2
#undef NT_MAKE_ERROR3
#undef NT_MAKE_ERR_SET
#define NT_MAKE_ERROR2(a, b)     DLL_API extern char a##_STRING[];
#define NT_MAKE_ERROR3(a, b, c)  DLL_API extern char a##_STRING[];
#define NT_MAKE_ERR_SET(a, b, c) DLL_API extern char a##_STRING[];

NT_ALL_ERROR_CODES

/****************************************************************************/
/* Make error external definition strings for logging (with parameters)     */
/****************************************************************************/
#undef NT_MAKE_ERROR2
#undef NT_MAKE_ERROR3
#undef NT_MAKE_ERR_SET
#define NT_MAKE_ERROR2(a, b)
#define NT_MAKE_ERROR3(a, b, c)  DLL_API extern char a##_LOG_STRING[];
#define NT_MAKE_ERR_SET(a, b, c)

NT_ALL_ERROR_CODES

/****************************************************************************/
/* Macros for getting error codes and error strings                         */
/****************************************************************************/

#define NT_GET_ERROR_STRING(a)     a##_STRING
#define NT_GET_LOG_ERROR_STRING(a) a##_LOG_STRING

/****************************************************************************/
/* Windows specific macros                                                  */
/****************************************************************************/
#ifdef _WIN32
#define NT_GET_SYSTEM_ERRORS (GetLastError() | NT_SYSTEM_ERRORS)
#define NT_GET_SOCKET_ERRORS (WSAGetLastError() | NT_SYSTEM_ERRORS)
#endif

//! @endcond

#endif /* __ERRORCODES_H__ */
