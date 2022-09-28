// dynamic_features_yanl.h

// Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef DYNAMIC_FEATURES_YAML_H_
#define DYNAMIC_FEATURES_YAML_H_

#include "util/error_info.h"
#include "base/dynamic_features.h"

Error_Info *
create_monitor_dynamic_features_yaml(
      const char *            mfg_id,
      const char *            model_name,
      uint16_t                product_code,
      const char *            filename,
      Dynamic_Features_Rec ** dynamic_features_loc);

#endif /* DYNAMIC_FEATURES_YAML_H_ */
