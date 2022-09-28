/* error_detail.h
 *
 * <copyright>
 * Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
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

#ifndef ERROR_DETAIL_H_
#define ERROR_DETAIL_H_

#include "ddcutil_types.h"
#include "util/error_info.h"


#ifdef REF
/** Struct for reporting errors, designed for collecting retry failures */
typedef struct error_info {
   char               marker[4];    ///<  always EINF
   int                status_code;  ///<  status code
   char *             func;         ///<  name of function generating status code
   char *             detail;       ///<  explanation (may be NULL)
   int                max_causes;   ///<  max number entries in array currently pointed to by **causes**
   int                cause_ct;     ///<  number of causal errors
   struct error_info **  causes;    ///<  pointer to array of pointers to Error_Info

#ifdef ALT
   GPtrArray *        causes_alt;   // GPointerArray of Ddc_Error *
#endif
} Error_Info;


#define DDCA_ERROR_DETAIL_MARKER "EDTL"
typedef struct ddca_error_detail {
   char                       marker[4];
   DDCA_Status                status_code;
   char *                     detail;
   uint                       cause_ct;
   struct ddca_error_detail * causes[];
} DDCA_Error_Detail;

#endif


void free_error_detail(DDCA_Error_Detail * ddca_erec);



#endif /* ERROR_DETAIL_H_ */
