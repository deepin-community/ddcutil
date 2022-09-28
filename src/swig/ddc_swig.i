/* ddc_swig.i
 *
 * <copyright>
 * Copyright (C) 2016-2017 Sanford Rockowitz <rockowitz@minsoft.com>
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

#ifndef PYTHON3
%module ddc_swig
#else
%module ddc_swig3
#endif

%header %{
// Start of copy block
#include "swig/ddc_swig.h"
//  void ddca_init(void);
// bool ddcs_built_with_adl(void);
const char * ddcutil_version(void);
// enum Retries{DDCT_WRITE_ONLY_TRIES3, DDCT_WRITE_READ_TRIES3, DDCT_MULTI_PART_TRIES3};
// end of copy block
%}

%wrapper %{

%}

%init %{
ddcs_init();
%}

//%rename("%(regex:/(.*)_swigconstant$/\\1/)s") "";

%module(docstring="ddcutil Python interface") ddc_swig;

%exception {
  clear_exception();     // redundant
  $action
//  char * emsg = check_exception(); 
//  if (emsg) {
//     PyErr_SetString( PyExc_RuntimeError, emsg);
//     return NULL;
//  }
   bool exception_thrown = check_exception2();
   if (exception_thrown) {
      puts("(ddc_swig.i:exception handler) throwing exception");
      return NULL;
   }
}


// Convert byte of bit flags to a Python set

%typemap(out) FlagsByte {
   printf("(typemap:FlagsByte) Starting. Value=0x%02x\n", $1);
   PyObject * pyset = PySet_New(NULL);
   for (int ndx = 0; ndx < 8; ndx++) {
      printf("(typemap:FlagsByte) testing bit %d, hexval 0x%02x\n", ndx, (1<<ndx) );
      if ($1 & (1<<ndx)) {
         PyObject * iobj = PyInt_FromLong( 1<<ndx);
         int rc = PySet_Add(pyset, iobj);
         printf("(typemap:FlagsByte) PySet_Add returned %d\n", rc);
      }
   }
   $result = pyset;
}


#ifndef PYTHON3
%typemap(in) FILE * {
   FILE * result = NULL;
   printf("(%s) input = %p\n", __func__, $input);
   int is_pyfile = PyFile_Check($input);
   printf("(%s) is_pyfile=%d\n", __func__, is_pyfile);
   if ( PyFile_Check($input) ) {
      result = PyFile_AsFile($input);
      save_current_python_fout( (PyFileObject *) $input);
   }
   else if ($input == Py_None) {
      result = NULL;
   }
   else {
      PyErr_SetString(PyExc_ValueError, "Not a Python file object");
      return NULL;
   }
   printf("(%s) Converted value: %p\n", __func__, result);
   $1 = result;
}
#endif
   
   
%apply(char * STRING, int LENGTH) { (char * byte_buffer, int bytect) };


//
// Library Build Information
//

const char * ddcs_ddcutil_version_string(void);

// which variant to keep?

// bool ddcs_built_with_adl(void);
// bool ddcs_built_with_usb(void);

%rename(DDCS_HAS_ADL)  DDCA_HAS_ADL;
%rename(DDCS_HAS_USB)  DDCA_HAS_USB;
%rename(DDCS_HAS_FAILSIM) DDCA_HAS_FAILSIM;

typedef enum {DDCA_HAS_ADL=DDCA_BUILT_WITH_ADL,
              DDCA_HAS_USB=DDCA_BUILT_WITH_USB,
              DDCA_HAS_FAILSIM=DDCA_BUILT_WITH_FAILSIM
             } DDCS_Build_Flags;
%feature("autodoc", "0");
FlagsByte ddcs_get_build_options();


//
// Initialization
//

// void ddca_init(void);


//
// Status Code Management
//

%rename(ddcs_status_code_name) ddca_rc_name;
%rename(ddcs_status_code_desc) ddca_rc_desc;
typedef int DDCA_Status;    // for now
// need to handle illegal status_code 
char * ddca_rc_name(DDCA_Status status_code);
char * ddca_rc_desc(DDCA_Status status_code);


 //
 // Global Settings
 //




// DDC Retry Control
%rename(DDCS_Retry_Type) DDCA_Retry_Type;
%rename(ddcs_get_max_tries) ddca_get_max_tries;
%rename(ddcs_set_max_tries) ddca_set_max_tries;
%rename(DDCS_WRITE_ONLY_TRIES)  DDCA_WRITE_ONLY_TRIES;
%rename(DDCS_WRITE_READ_TRIES)  DDCA_WRITE_READ_TRIES;
%rename(DDCS_MULTI_PART_TRIES)  DDCA_MULTI_PART_TRIES;
typedef enum{DDCA_WRITE_ONLY_TRIES, DDCA_WRITE_READ_TRIES, DDCA_MULTI_PART_TRIES} DDCA_Retry_Type;
int          ddca_get_max_tries(DDCA_Retry_Type retry_type);
DDCA_Status  ddca_set_max_tries(DDCA_Retry_Type retry_type, int max_tries);


//
// Message Control
//

%rename(DDCS_Output_Level)  DDCA_Output_Level;
%rename(DDCS_OL_TERSE)   DDCA_OL_TERSE;
%rename(DDCS_OL_NORMAL)  DDCA_OL_NORMAL;
%rename(DDCS_OL_VERBOSE) DDCA_OL_VERBOSE;
%rename(DDCS_Output_Level) DDCA_Output_Level;
%rename(ddcs_get_output_level) ddca_get_output_level;
%rename(ddcs_set_output_level) ddca_set_output_level;
%rename(ddcs_output_level_name) ddca_output_level_name;
typedef enum {
           DDCA_OL_TERSE  =0x04,
           DDCA_OL_NORMAL =0x08,
           DDCA_OL_VERBOSE=0x10
} DDCA_Output_Level;


DDCA_Output_Level ddca_get_output_level();
void              ddca_set_output_level(DDCA_Output_Level newval);
char *            ddca_output_level_name(DDCA_Output_Level val);

%rename(ddcs_enable_report_ddc_errors) ddca_enable_report_ddc_errors;
%rename(ddcs_is_report_ddc_errors_enabled) ddca_is_report_ddc_errors_enabled;
void ddca_enable_report_ddc_errors(bool onoff);
bool ddca_is_report_ddc_errors_enabled();

#ifndef PYTHON3
%feature("docstring", "Additional doc for ddcs_set_fout()") ddcs_set_fout;
void ddcs_set_fout(FILE * fout);
// void ddcs_set_fout(PyFileObject * fpy);
// void ddcs_set_fout(void * fpy);
#endif

//
// Display Identifiers
//

typedef void * DDCS_Display_Identifier;

%feature("autodoc", "0");
DDCS_Display_Identifier ddcs_create_dispno_display_identifier(
               int dispno);
               
%feature("autodoc", "1");
DDCS_Display_Identifier ddcs_create_adlno_display_identifier(
               int iAdapterIndex,
               int iDisplayIndex);
%feature("autodoc", "sample feature autodoc docstring");
DDCS_Display_Identifier ddcs_create_busno_display_identifier(
               int busno);
DDCS_Display_Identifier ddcs_create_mfg_model_sn_display_identifier(
               const char * mfg_id,
               const char * model,
               const char * sn);
DDCS_Display_Identifier ddcs_create_edid_display_identifier(
               const uint8_t * byte_buffer, 
               int bytect);
DDCS_Display_Identifier ddcs_create_usb_display_identifier(
               int bus,
               int device);
void ddcs_free_display_identifier(DDCS_Display_Identifier ddcs_did);
char * ddcs_repr_display_identifier(DDCS_Display_Identifier ddcs_did);


%feature("feature docstring");

//
// Display References
//
typedef void * DDCS_Display_Ref;
DDCS_Display_Ref ddcs_get_display_ref(   DDCS_Display_Identifier did);
void               ddcs_free_display_ref(  DDCS_Display_Ref dref);
char *             ddcs_repr_display_ref(  DDCS_Display_Ref dref);
void               ddcs_report_display_ref(DDCS_Display_Ref dref, int depth);


//
// Display Handles
//

typedef void * DDCS_Display_Handle;
DDCS_Display_Handle ddcs_open_display(DDCS_Display_Ref dref);
void                  ddcs_close_display(DDCS_Display_Handle dh);
char *                ddcs_repr_display_handle(DDCS_Display_Handle dh);


//
// Miscellaneous Display Specific Functions
//


// unsigned long ddcs_get_feature_info_by_display(
//                DDCS_Display_Handle  dh,
//                DDCS_VCP_Feature_Code  feature_code);



//
// Reports
//

int ddcs_report_active_displays(int depth);


//
// VCP Feature Code Information
//

typedef int DDCS_VCP_Feature_Code;

typedef struct {
   int    major;
   int    minor;
} DDCS_MCCS_Version_Spec;

char *      ddcs_get_feature_name(DDCS_VCP_Feature_Code feature_code);


// unsigned long ddcs_get_feature_info_by_vcp_version(
//                DDCS_VCP_Feature_Code    feature_code, 
//                DDCA_MCCS_Version_Id     version_id);


//
// Monitor Capabilities
//

char * ddcs_get_capabilities_string(DDCS_Display_Handle dh);


//
// Get and Set VCP Feature Values
//

typedef struct {
   uint8_t  mh;
   uint8_t  ml;
   uint8_t  sh;
   uint8_t  sl;
   int   max_value;
   int   cur_value;
} DDCS_Non_Table_Value_Response;


DDCS_Non_Table_Value_Response ddcs_get_nontable_vcp_value(
               DDCS_Display_Handle   dh,
               DDCS_VCP_Feature_Code   feature_code);

void ddcs_set_nontable_vcp_value(
               DDCS_Display_Handle   dh,
               DDCS_VCP_Feature_Code   feature_code,
               int                     new_value);

char * ddcs_get_profile_related_values(DDCS_Display_Handle dh);

void ddcs_set_profile_related_values(char * profile_values_string);

 