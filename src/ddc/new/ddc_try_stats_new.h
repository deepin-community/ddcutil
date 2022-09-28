/** @file ddc_try_stats_new.h
 *
 *  Maintains statistics on DDC retries.
 */

// Copyright (C) 2014-2020 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef TRY_STATS_NEW_H_
#define TRY_STATS_NEW_H_

#include "ddc_retry_mgt.h"


// OLD #define MAX_STAT_NAME_LENGTH  31

// Returns an opaque pointer to a Try_Data data structure
// OLD: void * try_data_create(char * stat_name, int max_tries);

// OLD: int  try_data_get_total_attempts(void * stats_rec);



//old: int  try_data_get_max_tries(void * stats_rec);
//old void try_data_set_max_tries(void* stats_rec,int new_max_tries);
void set_default_max_tries(DDCA_Retry_Type type_id, uint16_t new_max_tries);
void set_cur_thread_max_tries(DDCA_Retry_Type type_id, uint16_t new_max_tries);
uint16_t get_cur_thread_max_tries(DDCA_Retry_Type type_id);

// OLD: void try_data_reset(void * stats_rec);
void reset_cur_thread_tries();
void reset_all_threads_tries();


void record_cur_thread_successful_tries(DDCA_Retry_Type type_id, int tryct);
void record_cur_thread_failed_max_tries(DDCA_Retry_Type type_id);
void record_cur_thread_failed_fatally(DDCA_Retry_Type type_id);

// OLD: void try_data_record_tries(void * stats_rec, int rc, int tryct);
void record_cur_thread_tries(DDCA_Retry_Type type_id, int rc, int tryct);

// OLD: void try_data_report(void * stats_rec, int depth);
void all_threads_type_data_report(int depth);

#endif /* TRY_STATS_NEW_H_ */
