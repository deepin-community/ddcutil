/** @file base_init.c
 * Master base services initialization
 */

// Copyright (C) 2014-2020 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "util/error_info.h"

#include "core.h"
#include "ddc_packets.h"
#include "displays.h"
#include "execution_stats.h"
#include "linux_errno.h"
#include "per_thread_data.h"
#include "sleep.h"

#include "base_init.h"


/** Master initialization function for files in subdirectory base
 */
void init_base_services() {
   init_msg_control();
   errinfo_init(psc_name, psc_desc);
   init_sleep_stats();
   init_execution_stats();
   init_status_code_mgt();
   // init_linux_errno();
   init_thread_data_module();
   init_displays();
}
