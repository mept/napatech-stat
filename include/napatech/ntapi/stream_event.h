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
 * This header file contains the STREAMTYPE_EVENT interface
 */
#ifndef __STREAM_EVENT_H__
#define __STREAM_EVENT_H__

#if !defined(__NT_H__)
  #error: My interface file is 'nt.h'. Please include that via #include "nt.h" directly.
#endif

/** @addtogroup EventStream
 * @{
 *
 * Event streams are used to get various events from the system. The
 * event stream is a read only stream.
 *
 * To open an event stream call @ref NT_EventOpen. Once the event
 * stream is open it will receive all system events. An application
 * that requires certain events will open an event stream and
 * read the events one by one. The application can then react on the
 * events that it wants to react on and ignore the rest. Once done,
 * call @ref NT_EventClose to close the stream.
 *
 * The events types currently supported are:
 * @li <tt>Port events</tt> These events are link up and link down events.
 * @li <tt>Sensor events</tt> These events are sensor alarm state changes.
 * @li <tt>Config events</tt> These events are sent when a configuration change has been made.
 * @li <tt>Time sync events</tt> These events are time synchronization state changes.
 *
 * For an example on how to use the event stream see @ref
 * event/event_example.c "event/event_example.c".
 *
 *  @note The event stream is not thread-safe. If the same stream handle is to be used by multiple threads,
 *  it must be mutex protected in the application.
 *
 */
#include "/mnt/1/1/include/napatech/ntapi/commontypes.h"
#include "/mnt/1/1/include/napatech/ntapi/stream_config.h"
/**
 * The event types supported
 * Note: MUST be bitmasks
 */
enum NtEventSource_e {
  NT_EVENT_SOURCE_NONE             = 0,
  NT_EVENT_SOURCE_PORT             = (1 << 0),    //!< Bit for port event - Data placed in @ref NtEventPort_s
  NT_EVENT_SOURCE_SENSOR           = (1 << 1),    //!< Bit for sensor change event - Data placed in @ref NtEventSensor_s
  NT_EVENT_SOURCE_CONFIG           = (1 << 2),    //!< Bit for config change made events - Data placed in @ref NtConfig_s
  NT_EVENT_SOURCE_TIMESYNC         = (1 << 3),    //!< Bit for time sync events - Data placed in @ref NtEventTimeSync_s
  NT_EVENT_SOURCE_SDRAM_FILL_LEVEL = (1 << 4),    //!< Bit for host buffer fill level warning - Data placed in @ref NtSDRAMFillLevel_s
  NT_EVENT_SOURCE_PTP_PORT         = (1 << 5),    //!< Bit for PTP port events - Data placed in @ref NtEventPtpPort_s
  NT_EVENT_SOURCE_TIMESYNC_STATE_MACHINE = (1 << 6),//!< Bit for time sync state machine - Data placed in @ref NtEventTimeSyncStateMachine_s
  NT_EVENT_SOURCE_ALL              = (NT_EVENT_SOURCE_PORT |
                                      NT_EVENT_SOURCE_SENSOR |
                                      NT_EVENT_SOURCE_CONFIG |
                                      NT_EVENT_SOURCE_TIMESYNC |
                                      NT_EVENT_SOURCE_SDRAM_FILL_LEVEL |
                                      NT_EVENT_SOURCE_PTP_PORT |
                                      NT_EVENT_SOURCE_TIMESYNC_STATE_MACHINE),   //!< Bits for all events


  NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER0 = (1 << 23),  //!< Listen for command event(s). Event raised on write
  NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER1 = (1 << 24),
  NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER2 = (1 << 25),
  NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER3 = (1 << 26),
  NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER4 = (1 << 27),
  NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER5 = (1 << 28),
  NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER6 = (1 << 29),
  NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER7 = (1 << 30),

  NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ALL = (NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER0 |
                                          NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER1 |
                                          NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER2 |
                                          NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER3 |
                                          NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER4 |
                                          NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER5 |
                                          NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER6 |
                                          NT_EVENT_LISTEN_TIMESTAMP_SAMPLE_ADAPTER7),
//

};

enum NtEventRaise_e {
  NT_EVENT_SAMPLE_TIMESTAMP  = 1,
};

/**
 * Port events<br>
 * NT_EVENT_PORT_NIM_INSERTED and NT_EVENT_PORT_NIM_REMOVED will also be issued
 * during the load of ntservice if a NIM is present/not present at this time.
 * These events are not issued for fixed ports like RJ45.

   If the link goes up or down, then NT_EVENT_PORT_LINK_UP and
   NT_EVENT_PORT_LINK_DOWN are issued.
   A special case is relevant if the link goes down and then shortly afterwards
   comes up again, and at the same time sampling is used to detect link changes
   (in contrast to interrupt). In this case this link-down glitch might go
   undetected by the sampling itself.
   For most adapters, however, a sticky bit is set when the link goes down and
   remains in this state until cleared. If, therefore, the link is up at the
   current sampling, and it was also up at the last sampling, but the sticky bit
   indicates that the link has been down, then an NT_EVENT_PORT_LINK_DOWN event
   followed immediately by an NT_EVENT_PORT_LINK_UP event are issued.
   In this case the log will also indicate that a link down glitch has occurred.
   It should be noted that the link might go up and down several times during a
   sampling period but this only counts as ONE link down glitch.
   Whether sampling or interrupt is used to detect link changes is adapter
   dependent.

   The following figure illustrates a link-down glitch:

   @image html pictures/LinkDownGlitch1.png "Link-down Glitch"

   <br>
 */
enum NtEventPort_e {
  NT_EVENT_PORT_LINK_UP,            //!< Port link up event
  NT_EVENT_PORT_LINK_DOWN,          //!< Port link down event
  NT_EVENT_RXAUI_LINK_ERROR,        //!< Port RXAUI link error
  NT_EVENT_PORT_BYPASS_ACTIVATED,   //!< Port bypass activated event
  NT_EVENT_PORT_BYPASS_DEACTIVATED, //!< Port bypass deactivated event
  NT_EVENT_PORT_NIM_INSERTED,       //!< Port NIM inserted/found event
  NT_EVENT_PORT_NIM_REMOVED,        //!< Port NIM removed/not-found event
};

/**
 * Sensor events
 */
enum NtEventSensor_e {
  NT_EVENT_SENSOR_ALARM_STATE_ENTRY, //!< Sensor enters alarm state
  NT_EVENT_SENSOR_ALARM_STATE_EXIT,  //!< Sensor exits alarm state
};

/**
 * Event time sync information
 */
enum NtEventTimeSync_e {
  NT_EVENT_TIMESYNC_PPS_REQUEST_TIME,   //!< Request for PPS reference time
};

/**
 * Event time sync state machine information
 */
enum NtEventTimeSyncStateMachine_e {
  NT_EVENT_TIMESYNC_TIME_REFERENCE_LOST,              //!< Time reference is lost
  NT_EVENT_TIMESYNC_TIME_REFERENCE_SELECT,            //!< Select time reference
  NT_EVENT_TIMESYNC_TIME_REFERENCE_SELECT_FAIL,       //!< Fail to select time reference
  NT_EVENT_TIMESYNC_TIME_IN_SYNC,                     //!< TS clock changed from out-of-sync to in-sync with master clock based on configured threshold value. Note: no timestamp value supplied.
  NT_EVENT_TIMESYNC_TIME_OUT_OF_SYNC,                 //!< TS clock changed from in-sync to out-of-sync with master clock based on configured threshold value. note: no timestamp value supplied.
  NT_EVENT_TIMESYNC_PTP_STATE_CHANGE,                 //!< Change of PTP state
  NT_EVENT_TIMESYNC_TIME_STAMP_CLOCK_SET,             //!< Absolute value assigned to time stamp clock
  NT_EVENT_TIMESYNC_EXTERNAL_DEVICE_LOST_SYNC_SIGNAL, //!< External device lost synchronization signal
  NT_EVENT_TIMESYNC_EXTERNAL_DEVICE_OUT_OF_SYNC,      //!< External device is out of synchronization
  NT_EVENT_TIMESYNC_EXTERNAL_DEVICE_LOST_TIME_OF_DAY, //!< External device lost time of day information
};

/**
 * Event link up/down information
 */
struct NtEventPort_s {
  enum NtEventPort_e action;  //!< Port action
  uint8_t portNo;             //!< Port generating the event
  uint8_t Reserved1[3];
};

/**
 * PTP port link up/down event information
 */
struct NtEventPtpPort_s {
  enum NtEventPort_e action;  //!< Port action
  uint8_t adapterNo;          //!< Adapter that generates the event
  uint8_t portNo;             //!< Port that generates the event
  uint8_t Reserved1[2];
};

/**
 * Event SDRAM fill level information
 */
#define MAX_SDRAM_FILL_LEVEL_STREAMS 256
struct NtSDRAMFillLevel_s {
  uint8_t adapterNo;   //!< The adapter owning the host buffer
  uint8_t Reserved1[3];
  uint32_t streamsId;  //!< Stream ID using the host buffer
  uint32_t numStreams; //!< Number of streams using the host buffers. Also indicating the use depth of @ref aStreams.
  uint64_t used;       //!< SDRAM used. This shows the amount of adapter memory used. One must pay attention to this value.
                       //!< When the value is close to used, it means that the adapter has used all the buffer memory.
                       //!< This happens if the adapter is not able to transfer the received data to the host buffers on the PC
                       //!< and is mainly caused by a slow application not being able to release the data fast enough.
                       //!< Packet loss will probably occur.
  uint64_t size;       //!< The amount of SDRAM reserved for this host buffer
  /**
   * This structure tells where the host buffer is currently used.
   */
  struct NtHostBuffer_s {
    uint64_t deQueued;          //!< Bytes available or in use by the streams.
                                //!< If all data is placed here it means that the application is too slow to handle the data.
                                //!< The application is not able to release the packets (host buffer) fast enough so the data is
                                //!< ready for the driver and adapter to fill with new data. The result is that the adapter runs
                                //!< out of data space and a packet loss occurs.
    uint64_t enQueued;          //!< Bytes available to the host buffer handler.
                                //!< If all data is placed here it means that the driver is too slow to handle the data.
                                //!< This is a driver error and should never happen.
    uint64_t enQueuedAdapter;   //!< Bytes currently in the adapter.
                                //!< Most of the time the data should be placed here.
    uint64_t size;              //!< Host buffer size
  } hb;
  /**
   * the array of streams using the host buffer
   */
  struct NtStream_s {
    int streamIndex;        //!< The index for the stream attached to the host buffer
    uint64_t enQueued;      //!< The data currently enqueued to the stream. The stream with the largest enqueued amount is the slowest stream and probably the one that causes the packet loss.
    uint64_t processID;     //!< The process owning the stream
  } aStreams[MAX_SDRAM_FILL_LEVEL_STREAMS];
};

/**
 * Event sensor change information
 */
struct NtEventSensor_s {
  enum NtSensorSource_e source;      //!< The source of the sensor (the port or adapter on which the sensor resides)
  uint32_t sourceIndex;                   //!< The source index - the adapter number or port number where the sensor resides
  uint32_t sensorIndex;                   //!< The sensor index - the index of the sensor within the group of sensors. Each adapter or port has a different number and sensor type.
                                     //!< - NT20E2 adapter sensor group - @ref NtSensorsAdapterNT20E2_e
                                     //!< - NT20E2 port sensor group - @ref NtSensorsPortNT20E2_e
                                     //!< - NT20E adapter sensor group - @ref NtSensorsAdapterNT20E_e
                                     //!< - NT20E port sensor group - @ref NtSensorsPortNT20E_e
                                     //!< - NT4E adapter sensor group - @ref NtSensorsAdapterNT4E_e
                                     //!< - NT4E port sensor group - @ref NtSensorsPortNT4E_e
  enum NtEventSensor_e action;       //!< Whether the alarm is entered or exited
  int value;                         //!< The value that triggered the event
  enum NtAdapterType_e adapterType;  //!< The adapter type triggering the event
};

/**
 * Time sync information
 */
struct NtEventTimeSync_s {
  enum NtEventTimeSync_e action;  //!< What happened
  uint8_t adapter;                //!< Which adapter generated the event
  uint8_t Reserved1[3];
};

/**
 * Time sync state machine event information
 */
struct NtEventTimeSyncStateMachine_s {
  enum NtEventTimeSyncStateMachine_e action; //!< What happened
  uint8_t adapter; //!< Which adapter generated the event
  enum NtTimeSyncReference_e timeReference; //!< Time reference affected by the event
  union {
    enum NtPTPPortState_e ptpState[2]; //!< ptpState[0] = old state; ptpState[1] = new state
    uint64_t timeStampClock; //!< Time in nanoseconds set on adapter
  };
  uint8_t reserved[3]; //!< Reserved for future use
};

/**
 * Event information
 */
typedef struct NtEvent_s {
  enum NtEventSource_e type;    //!< Event type
  /**
   * Union holding event information
  */
  union NtEvent_u {
    struct NtEventPort_s   portEvent;                         //!< Port events - @ref NT_EVENT_SOURCE_PORT
    struct NtEventSensor_s sensorEvent;                       //!< Sensor events - @ref NT_EVENT_SOURCE_SENSOR
    struct NtConfig_s configEvent;                            //!< Config events - @ref NT_EVENT_SOURCE_CONFIG
    struct NtEventTimeSync_s timeSyncEvent;                   //!< Time sync events - @ref NT_EVENT_SOURCE_TIMESYNC
    struct NtSDRAMFillLevel_s sdramFillLevelEvent;            //!< Host buffer usage event - @ref NT_EVENT_SOURCE_SDRAM_FILL_LEVEL
    struct NtEventPtpPort_s ptpPortEvent;                     //!< PTP port event - @ref NT_EVENT_SOURCE_PTP_PORT
    struct NtEventTimeSyncStateMachine_s timeSyncStateMachineEvent; //!< Time sync change state event - @ref NT_EVENT_SOURCE_TIMESYNC_STATE_MACHINE
  } u;
} NtEvent_t;

/**
 * Event stream handle
 */
typedef struct NtEventStream_s* NtEventStream_t;

/**
 * @brief Opens an event stream and initializes event queues, etc.
 *
 * This function must be called before using the events. The necessary
 * stream, lists, mutexes and semaphores are initialized and
 * created.
 *
 * The source of event is selected by the eventMask. This could be either a
 * single event source or all event sources. See @ref NtEventSource_e for
 * the different event sources.
 *
 * @param[in,out] hStream   Pointer to the stream handle
 * @param[in]     name      A friendly name of the stream
 * @param[in]     eventMask @ref NtEventSource_e - A bitmask defining the sources of events to receive
 *
 * @retval  == NT_SUCCESS: Success
 * @retval  != NT_SUCCESS: Error
 */
int NT_EventOpen(NtEventStream_t *hStream, const char *name, uint32_t eventMask);

/**
 * @brief Reads an event from an event queue
 *
 * This function is called by the user to read an event.
 * The event is copied from the event queue to the
 * stream handle for the user to read using the HAL functions.
 * The event is marked as read for deletion and cannot be
 * read by the user again.
 *
 *
 * @param[in] hStream       Stream to store the current event
 * @param[out] event        Event structure - the event information is returned in this structure
 * @param[in] timeout       Time in milliseconds to wait for an event
 *
 * @retval  == NT_SUCCESS: Success
 * @retval  != NT_SUCCESS: Error
 */
int NT_EventRead(NtEventStream_t hStream, NtEvent_t *event, uint32_t timeout);





int NT_EventWrite(NtEventStream_t hStream, enum NtEventRaise_e eventId);





/**
 * @brief Releases the stream and clears event queues, etc.
 *
 * This function must be called after using the events in order
 * to release the stream and clear the allocated lists, mutexes
 * and semaphores.
 *
 * @param[in] hStream Pointer to the stream handle
 *
 * @retval  == NT_SUCCESS: Success
 * @retval  != NT_SUCCESS: Error
 */
int NT_EventClose(NtEventStream_t hStream);

/** @} */

#endif /* __STREAM_EVENT_H__ */
