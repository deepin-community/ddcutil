/* adl_intf.h
 *
 * <copyright>
 * Copyright (C) 2014-2017 Sanford Rockowitz <rockowitz@minsoft.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * </endcopyright>
 */

/** \file
 *
 */

#ifndef ADL_INTF_H_
#define ADL_INTF_H_

/** \cond */
#include <config.h>
#include <stdbool.h>
#include <stdlib.h>     // wchar_t, needed by adl_structures.h
/** \endcond */

#include "util/edid.h"

#include "base/core.h"
#include "base/displays.h"
#include "base/execution_stats.h"
#include "base/status_code_mgt.h"

#include "adl/adl_impl/adl_sdk_includes.h"

/** Describes an ADL display.
 *
 * Used only within ADL implementation code and tests
 */
typedef
struct {
   int                   iAdapterIndex;
   int                   iDisplayIndex;
   bool                  supports_ddc;
   ADLDisplayEDIDData *  pAdlEdidData;
   ADLDDCInfo2 *         pAdlDDCInfo2;
   char                  mfg_id[4];
   char                  model_name[14];
   char                  serial_ascii[14];
   char                  xrandr_name[16];     // what is correct maximum size?
   Parsed_Edid *         pEdid;

   // additional fields added 12/2015 for further exploration
   int                   iVendorID;                       // e.g. 4098
   // waste of space to reserve full ADL_MAX_PATH for each field
   char *                pstrAdapterName;
   char *                pstrDisplayName;
   // char                  strAdapterName[ADL_MAX_PATH];    // e.g. "AMD Radeon HD 6420"
   // char                  strDisplayName[ADL_MAX_PATH];    // e.g. :0.0
#ifdef UNUSED
   int                   iBusNumber;           // don't think this is I2C bus
   int                   iFunctionNumber;     // not useful
   int                   iDrvIndex;
#endif
} ADL_Display_Rec;


// Initialization

bool adl_is_available();
// must be called before any other function (except is_adl_available()):
bool adl_initialize();
void adl_release();


// Report on active displays

Parsed_Edid* adl_get_parsed_edid_by_adlno(int iAdapterIndex, int iDisplayIndex);

void adl_report_active_display(ADL_Display_Rec * pdisp, int depth);
void adl_report_active_display_by_index(int ndx, int depth);
void adl_report_active_display_by_adlno(int iAdapterIndex, int iDisplayIndex, int depth);
int  adl_report_active_displays();   // returns number of active displays

void report_adl_display_rec(ADL_Display_Rec * pRec, bool verbose, int depth);

Base_Status_ADL adl_get_video_card_info_by_adlno(
                      int               iAdapterIndex,
                      int               iDisplayIndex,
                      Video_Card_Info * card_info);


// Find and validate display

bool              adl_is_valid_adlno(int iAdapterIndex, int iDisplayIndex, bool emit_error_msg);
ADL_Display_Rec * adl_get_display_by_adlno(int iAdapterIndex, int iDisplayIndex, bool emit_error_msg);
ADL_Display_Rec * adl_find_display_by_mfg_model_sn(const char * mfg_id, const char * model, const char * sn);
ADL_Display_Rec * adl_find_display_by_edid(const Byte * pEdidBytes);

#ifdef OLd
Display_Info_List adl_get_valid_displays();
#endif

// new

int adl_get_active_display_ct();
ADL_Display_Rec * adl_get_active_display_rec(int ndx);



// Read from and write to the display

Base_Status_ADL adl_ddc_write_only(
      int     iAdapterIndex,
      int     iDisplayIndex,
      Byte *  pSendMsgBuf,
      int     sendMsgLen);

Base_Status_ADL adl_ddc_read_only(
      int     iAdapterIndex,
      int     iDisplayIndex,
      Byte *  pRcvMsgBuf,
      int *   pRcvBytect);

Base_Status_ADL adl_ddc_write_read(
      int     iAdapterIndex,
      int     iDisplayIndex,
      Byte *  pSendMsgBuf,
      int     sendMsgLen,
      Byte *  pRcvMsgBuf,
      int *   pRcvBytect);

Base_Status_ADL adl_ddc_write_read_onecall(
      int     iAdapterIndex,
      int     iDisplayIndex,
      Byte *  pSendMsgBuf,
      int     sendMsgLen,
      Byte *  pRcvMsgBuf,
      int *   pRcvBytect);

#endif /* ADL_INTF_H_ */
