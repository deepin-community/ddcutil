/* adl_errors.c
 *
 *  Interpret ADL error codes
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
 * ADL Error Number Services
 */

/** \cond */
#include <stdio.h>    // for NULL
#include <adl_defines.h>
/** \endcond */

#include "util/string_util.h"

#include "base/adl_errors.h"
#include "base/status_code_mgt.h"


#define EDENTRY(id,desc) {id, #id, desc}
static Status_Code_Info adl_status_desc[] = {
      EDENTRY(ADL_OK_WAIT,                       "All ok, but need to wait"),         //  4
      EDENTRY(ADL_OK_RESTART,                    "All ok, but need restart"),         //  3
      EDENTRY(ADL_OK_MODE_CHANGE,                "All OK, but need mode change" ),    //  2
      EDENTRY(ADL_OK_WARNING,                    "All OK, but with warning" ),        //  1
      EDENTRY(ADL_OK,                            "Function completed successfully" ), //  0
      EDENTRY(ADL_ERR,                           "Generic error (see adl_defines.h)" ), // -11
      EDENTRY(ADL_ERR_NOT_INIT,                  "ADL not initialized" ),
      EDENTRY(ADL_ERR_INVALID_PARAM,             "Invalid parameter" ),
      EDENTRY(ADL_ERR_INVALID_PARAM_SIZE,        "A parameter size is invalid" ),
      EDENTRY(ADL_ERR_INVALID_ADL_IDX ,          "Invalid ADL index"           ),
      EDENTRY(ADL_ERR_INVALID_CONTROLLER_IDX ,   "Invalid controller index" ),
      // n. ADL_ERR_INVALID_DIPLAY_IDX is actual value in adl_defines.h
      EDENTRY(ADL_ERR_INVALID_DIPLAY_IDX,        "Invalid display index" ),
      EDENTRY(ADL_ERR_NOT_SUPPORTED,             "Function not supported by the driver"),
      EDENTRY(ADL_ERR_NULL_POINTER,              "Null Pointer error"),                       //  -9
      EDENTRY(ADL_ERR_DISABLED_ADAPTER,          "Can't be made due to disabled adapter"),    // -10
      EDENTRY(ADL_ERR_INVALID_CALLBACK,          "Invalid callback"),                         // -11
      EDENTRY(ADL_ERR_RESOURCE_CONFLICT,         "Display resource conflict"),                // -12
      EDENTRY(ADL_ERR_SET_INCOMPLETE,            "Failed to update some values. (see adl_definess.h)"), // -20
      EDENTRY(ADL_ERR_NO_XDISPLAY,               "There's no XDisplay in Linux console environment"), // -21
    };
#undef EDENTRY
static const int adl_status_desc_ct = sizeof(adl_status_desc)/sizeof(Status_Code_Info);

#define WORKBUF_SIZE 100
static char workbuf[WORKBUF_SIZE];
static Status_Code_Info dummy_adl_status_desc;
static char buf2[20];

/** Given an unmodulated ADL status code, return its
 *  Status_Code_Info struct.
 *
 *  @param errnum   unmodulated ADL status code
 *  @return pointer to #Status_Code_Info struct describing the code.
 *                  NULL if code not found
 */
Status_Code_Info * find_adl_status_description(Base_Status_ADL errnum) {
   Status_Code_Info * result = NULL;

   int ndx;
   for (ndx=0; ndx < adl_status_desc_ct; ndx++) {
       if (errnum == adl_status_desc[ndx].code) {
          result = &adl_status_desc[ndx];
          break;
       }
   }
   return result;
}


/** Given an unmodulated ADL status code, return its
 *  Status_Code_Info struct.
 *
 *  If the error code is unrecognized, a dummy struct is initializaed and
 *  returmed.  The contents of this struct are valid until the next call
 *  to this function.
 *
 *  @param errnum   unmodulated ADL status code
 *  @return pointer to #Status_Code_Info struct describing the code
 */
Status_Code_Info * get_adl_status_description(Base_Status_ADL errnum) {
   Status_Code_Info * result = NULL;

   result = find_adl_status_description(errnum);

   if (!result) {
      result = &dummy_adl_status_desc;
      result->code = errnum;
      char * s  = "Unknown ADL status code";
      result->description = s;
      snprintf(buf2,20, "%d",errnum);
      result->name = buf2;
      snprintf(workbuf, WORKBUF_SIZE, "(%d) %s\n",
               errnum, result->description);
   }

   return result;
}


// n. called from main before command line parsed, trace control not yet set up
void init_adl_errors() {
#ifdef OLD
   register_retcode_desc_finder(RR_ADL,
                                get_adl_status_description,
                                false);                     // finder_arg_is_modulated
#endif
}


/** Gets the (unmodulated) ADL error number for a symbolic name.
 *
 *  @param  adl_error_name    symbolic name, e.g. ADL_ERR_NOT_SUPPORTED
 *  @param  p_adl_error_number where to return error number
 *  @return true if symbolic name found, false if not
 */
bool adl_error_name_to_number(
        const char *      adl_error_name,
        Base_Status_ADL * p_adl_error_number)
{
   int result = 0;
   bool found = false;
   for (int ndx = 0; ndx < adl_status_desc_ct; ndx++) {
       if ( streq(adl_status_desc[ndx].name, adl_error_name) ) {
          result = adl_status_desc[ndx].code;
          found = true;
          break;
       }
   }
   *p_adl_error_number = result;
   return found;
}


/** Gets the (modulated) ADL error number for a symbolic name.
 *
 *  @param  adl_error_name   symbolic name, e.g. ADL_ERR_NOT_SUPPORTED
 *  @param  p_adl_error_number   where to return error number
 *  @return true if symbolic name found, false if not
 */
bool adl_error_name_to_modulated_number(
        const char *            adl_error_name,
        Modulated_Status_ADL *  p_adl_error_number)
{
   int result = 0;
   bool found = adl_error_name_to_number(adl_error_name, &result);
   if (found) {
      result = modulate_rc(result, RR_ADL);
   }
   *p_adl_error_number = result;
   return found;
}
