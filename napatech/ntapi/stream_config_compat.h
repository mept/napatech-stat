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
 * This is the header file of the STREAMTYPE_CONFIG interface containing
 * included for backward compatibility structures.
 *
 */
#ifndef __STREAM_CONFIG_COMPAT_H__
#define __STREAM_CONFIG_COMPAT_H__

#if !defined(_NT_NTAPI_NO_COMPAT)

/***********************************************************************************************/
/*                               Port settings version 0                                       */
/***********************************************************************************************/
#define NT_CONFIG_PARM_PORT_SETTINGS NT_CONFIG_PARM_PORT_COMPAT_0 //!< Port settings - version 0

struct NtPortSettings_s {
  int enable;           //!< 0 = Disable interface, 1 = Enable interface. If disabled, the port will still be visible, but has status link down.
#ifndef DOXYGEN_IGNORE
  // Not supported
  int flow;             //!< 0 = No flow control, 1 = Flow control
#endif
  enum NtLinkMDI_e mdi; //!< MDI mode
  enum NtLinkAutoNeg_e autoNegotiation;  //!< Manual speed, Auto (ignored on optical NIM interfaces)
  /**
   * Array of manual port setting parameters
   */
  struct NtPortSettingsManual_s manual; //!< Ignored on optical NIM interfaces
  /**
   * Array of parameters to be advertised when autonegotiation is enabled
   */
  struct NtPortSettingsAdvertise_s advertise; //!< Ignored on optical NIM interfaces

  uint32_t minIFG; //!< The minimum inter-frame gap in steps of 10 ns. A specified value will be rounded up or down to the nearest HW-supported value, which depends on the link speed. The default minimum gap is 0 ns.
  uint32_t maxIFG; //!< The maximum inter-frame gap in steps of 10 ns. A specified value will be rounded up or down to the nearest HW-supported value, which depends on the link speed. The default maximum gap is the maximum HW-supported value. Setting the maximum interframe gap to 0 ns, corresponds to disabling the check for maximum IFG.

  enum NtTxPower_e TxPower; //!< TX power state on read and command on write. Controls laser power on/off on fiber SFP, XFP, SFP+ and QSFP+ modules. Note that not all modules support enable/disable of the laser. An error code is returned if not supported.
  int hostLoopback;  //!< Host loopback position.\n
  //!< Applying host loopback has the effect that data sent from the host is looped
  //!< back to the host on the same port regardless of, if a NIM (Network Interface
  //!< Module) has been plugged in, and if a physical loopback has been applied.
  //!< The link will therefore be reported as up despite that no NIM is present
  //!< or that no physical link is present.\n
  //!< In general simultaneous host and line loopback is not allowed.\n
  //!< The available loopback positions are adapter dependent and applying a loopback
  //!< position that is not supported will result in a returned error code by the API
  //!< function. In general only the following values @ref NtHostLoopback_e should be
  //!< used.\n
  //!< Applying loopback along with settings that require PHY setup changes or
  //!< applying these settings when already in loopback mode represents a conflict
  //!< and will not be carried out. A returned error code will indicate this. In order
  //!< to avoid conflicts, it is in general recommended to enable loopback separately.\n
  //!< When applying loopback special settings are used and for trispeed modules
  //!< this means that the link speed is changed to maximum. The original settings
  //!< are restored when loopback is removed.
};

/***********************************************************************
 * Config read and write port settings - NT_CONFIG_PARM_PORT_SETTINGS *
 ***********************************************************************/
struct NtConfigPort_s {
  uint8_t portNo;                 //!< Port number to read from
  uint8_t Reserved1[3];
  struct NtPortSettings_s data;   //!< Port settings
};

#define NtConfigReadPort_s NtConfigPort_s

/***********************************************************************************************/
/*                               Port settings version 1                                       */
/***********************************************************************************************/
#define NT_CONFIG_PARM_PORT_SETTINGS_V1 NT_CONFIG_PARM_PORT_COMPAT_1 //!< Port settings - version 1

struct NtPortSettings_v1_s {
  int enable;           //!< 0 = Disable interface, 1 = Enable interface. If disabled, the port will still be visible, but has status link down.
#ifndef DOXYGEN_IGNORE
  // Not supported
  int flow;             //!< 0 = No flow control, 1 = Flow control
#endif
  enum NtLinkMDI_e mdi; //!< MDI mode
  enum NtLinkAutoNeg_e autoNegotiation;  //!< Manual speed, Auto (ignored on optical NIM interfaces)
  /**
   * Array of manual port setting parameters
   */
  struct NtPortSettingsManual_s manual; //!< Ignored on optical NIM interfaces
  /**
   * Array of parameters to be advertised when autonegotiation is enabled
   */
  struct NtPortSettingsAdvertise_s advertise; //!< Ignored on optical NIM interfaces

  uint32_t minIFG; //!< Depending on the IfgMode parameter in ntservice.ini the minimum interframe-gap is either interpreted as 10 ns steps or bytes. If IfgMode is set to NS the value will be rounded up or down to the nearest HW-supported value, which depends on the link speed. The default minimum gap is 0 ns. If the IfgMode is set to BYTE the value is written directly to the HW.
  uint32_t maxIFG; //!< Depending on the IfgMode parameter in ntservice.ini the maximum interframe-gap is either interpreted as 10 ns steps or bytes. If the IfgMode is set to NS the value will be rounded up or down to the nearest HW-supported value, which depends on the link speed. The default maximum gap is the maximum HW-supported value. If the IfgMode is set to BYTE the value will be  written directly to the HW. Setting the maximum interframe gap to 0, corresponds to disabling the check for maximum IFG.

  enum NtTxPower_e TxPower; //!< TX power state on read and command on write. Controls laser power on/off on fiber SFP, XFP, SFP+ and QSFP+ modules. Note that not all modules support enable/disable of the laser. An error code is returned if not supported.
  int hostLoopback;  //!< Host loopback position.\n
  //!< Applying host loopback has the effect that data sent from the host is looped
  //!< back to the host on the same port regardless of, if a NIM (Network Interface
  //!< Module) has been plugged in, and if a physical loopback has been applied.
  //!< The link will therefore be reported as up despite that no NIM is present
  //!< or that no physical link is present.\n
  //!< In general simultaneous host and line loopback is not allowed.\n
  //!< The available loopback positions are adapter dependent and applying a loopback
  //!< position that is not supported will result in a returned error code by the API
  //!< function. In general only the following values @ref NtHostLoopback_e should be
  //!< used.\n
  //!< Applying loopback along with settings that require PHY setup changes or
  //!< applying these settings when already in loopback mode represents a conflict
  //!< and will not be carried out. A returned error code will indicate this. In order
  //!< to avoid conflicts, it is in general recommended to enable loopback separately.\n
  //!< When applying loopback special settings are used and for trispeed modules
  //!< this means that the link speed is changed to maximum. The original settings
  //!< are restored when loopback is removed.

  int lineLoopback;  //!< Line loopback position.\n
  //!< Applying line loopback has the effect that data sent from the line is looped
  //!< back to the line on the same port. This requires that a NIM (Network Interface
  //!< Module) has been plugged in.
  //!< The link will in general be reported as up and traffic can be received by
  //!< the host but any traffic transmitted by the host will be replaced by the
  //!< traffic looped back.
  //!< In general simultaneous host and line loopback is NOT allowed.\n
  //!< The available loopback positions are adapter dependent and applying a loopback
  //!< position that is not supported will result in a returned error code by the API
  //!< function. In general only the following values @ref NtLineLoopback_e should be
  //!< used.\n
  //!< Applying loopback along with settings that require PHY setup changes or
  //!< applying these settings when already in loopback mode represents a conflict
  //!< and will not be carried out. A returned error code will indicate this. In order
  //!< to avoid conflicts, it is in general recommended to enable loopback separately.\n
  //!< When applying loopback special settings are used and for trispeed modules
  //!< this means that the link speed is changed to maximum. The original settings
  //!< are restored when loopback is removed.
  enum NtPortId_e PortId; //!< Port identification state.
  //!< Turns the port identification feature on/off. An error code is returned if
  //!< not supported.
  //!< When enabled the port led will start to blink regardless if the link is up
  //!< or the port receives data or not.
  int wisModeEnable; //!< 0 = Wismode disabled on port, 1 = Enable Wismode enabled on port.
};

/***********************************************************************
 * Config read and write port settings - NT_CONFIG_PARM_PORT_SETTINGS_V1 *
 ***********************************************************************/
struct NtConfigPort_v1_s {
  uint8_t portNo;                 //!< Port number to read from
  uint8_t Reserved1[3];
  struct NtPortSettings_v1_s data;   //!< Port settings
};

#define NT_TIMESYNC_RESET_PTP_SYNC_STAT NT_TIMESYNC_RESET_COMPAT_0 //!< Deprecated. Use NT_TIMESYNC_RESET_TS_STATISTICS instead

#endif /* _NT_NTAPI_NO_COMPAT */
#endif /* __STREAM_INFO_COMPAT_H__ */
