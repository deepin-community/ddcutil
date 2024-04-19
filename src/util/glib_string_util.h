/** @file glib_string_util.h
 *
 *  Functions that depend on both glib_util.c and string_util.c
 *
 *  glib_string_util.c/h exist to avoid circular dependencies.
 */

// Copyright (C) 2014-2023 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later


/** \cond */
#include <glib-2.0/glib.h>
/** \endcond */

#ifndef GLIB_STRING_UTIL_H_
#define GLIB_STRING_UTIL_H_

char * join_string_g_ptr_array(GPtrArray* strings, char * sepstr);
char * join_string_g_ptr_array_t(GPtrArray* strings, char * sepstr);
char * join_string_g_ptr_array2(GPtrArray* strings, char * sepstr, bool sort);
char * join_string_g_ptr_array2_t(GPtrArray* strings, char * sepstr, bool sort);

int         gaux_string_ptr_array_find(GPtrArray * haystack, const char * needle);
bool        gaux_unique_string_ptr_arrays_equal(GPtrArray *first, GPtrArray* second);
GPtrArray * gaux_unique_string_ptr_arrays_minus(GPtrArray *first, GPtrArray* second);
void        gaux_unique_string_ptr_array_include(GPtrArray * arry, char * new_value);

#endif /* GLIB_STRING_UTIL_H_ */
