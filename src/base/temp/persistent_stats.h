/** \f persistent_stats.h */

// Copyright (C) 2023 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef PERSISTENT_STATS_H_
#define PERSISTENT_STATS_H_

#include "private/ddcutil_types_private.h"
#include "util/error_info.h"

bool   enable_stats_cache(bool onoff);
char * get_stats_cache_file_name();
char * get_persistent_stats(DDCA_Monitor_Model_Key* mmk);
void   set_persistent_stats(DDCA_Monitor_Model_Key* mmk, const char * stats);
void   dbgrpt_stats_hash(int depth, const char * msg);
void   init_persistent_stats();

#endif /* PERSISTENT_STATS_H_ */
