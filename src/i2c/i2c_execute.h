/** @file i2c_execute.h
 *
 *  Low level functions for writing to and reading from the I2C bus,
 *  using various mechanisms.
 */
// Copyright (C) 2014-2020 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef I2C_EXECUTE_H_
#define I2C_EXECUTE_H_

#include "util/coredefs.h"
#include "base/status_code_mgt.h"

void set_i2c_fileio_use_timeout(bool yesno);
bool get_i2c_fileio_use_timeout();

/** Function template for I2C write function */
typedef Status_Errno_DDC (*I2C_Writer)(
      int    fd,
      Byte   slave_address,
      int    bytect,
      Byte * bytes_to_write);

/** Function template for I2C read function */
typedef Status_Errno_DDC (*I2C_Reader)(
      int fd,
      Byte   slave_addr,
      bool   read_bytewise,
      int    bytect,
      Byte * readbuf);

Status_Errno_DDC fileio_writer(
      int    fd,
      Byte   slave_address,
      int    bytect,
      Byte * pbytes);

Status_Errno_DDC fileio_reader (
      int    fd,
      Byte   slave_address,
      bool   read_bytewise,
      int    bytect,
      Byte * readbuf);

Status_Errno_DDC ioctl_writer(
      int    fd,
      Byte   slave_address,
      int    bytect,
      Byte * pbytes);

Status_Errno_DDC ioctl_reader(
      int    fd,
      Byte   slave_address,
      bool   read_bytewise,
      int    bytect,
      Byte * readbuf);

#endif /* I2C_EXECUTE_H_ */
