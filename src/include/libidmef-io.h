/*****
*
* Copyright (C) 2001-2016 CS-SI. All Rights Reserved.
* Author: Yoann Vandoorselaere <yoann.v@libidmef-ids.com>
*
* This file is part of the LibIdmef library.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
*****/

#ifndef _LIBIDMEF_LIBIDMEF_IO_H
#define _LIBIDMEF_LIBIDMEF_IO_H

#ifdef __cplusplus
  extern "C" {
#endif

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>
#include <unistd.h>
#include "libidmef-inttypes.h"


typedef struct libidmef_io libidmef_io_t;

/*
 * Object creation / destruction functions.
 */
int libidmef_io_new(libidmef_io_t **ret);

void libidmef_io_destroy(libidmef_io_t *pio);

void libidmef_io_set_file_io(libidmef_io_t *pio, FILE *fd);

void libidmef_io_set_tls_io(libidmef_io_t *pio, void *tls);

void libidmef_io_set_sys_io(libidmef_io_t *pio, int fd);

int libidmef_io_set_buffer_io(libidmef_io_t *pio);


/*
 *
 */
void libidmef_io_set_fdptr(libidmef_io_t *pio, void *ptr);
void libidmef_io_set_write_callback(libidmef_io_t *pio, ssize_t (*write)(libidmef_io_t *io, const void *buf, size_t count));
void libidmef_io_set_read_callback(libidmef_io_t *pio, ssize_t (*read)(libidmef_io_t *io, void *buf, size_t count));
void libidmef_io_set_pending_callback(libidmef_io_t *pio, ssize_t (*pending)(libidmef_io_t *io));


/*
 * IO operations.
 */
int libidmef_io_close(libidmef_io_t *pio);

ssize_t libidmef_io_read(libidmef_io_t *pio, void *buf, size_t count);

ssize_t libidmef_io_read_wait(libidmef_io_t *pio, void *buf, size_t count);

ssize_t libidmef_io_read_delimited(libidmef_io_t *pio, unsigned char **buf);


ssize_t libidmef_io_write(libidmef_io_t *pio, const void *buf, size_t count);

ssize_t libidmef_io_write_delimited(libidmef_io_t *pio, const void *buf, uint16_t count);


ssize_t libidmef_io_forward(libidmef_io_t *dst, libidmef_io_t *src, size_t count);

int libidmef_io_get_fd(libidmef_io_t *pio);

void *libidmef_io_get_fdptr(libidmef_io_t *pio);

ssize_t libidmef_io_pending(libidmef_io_t *pio);

libidmef_bool_t libidmef_io_is_error_fatal(libidmef_io_t *pio, int error);

#ifdef __cplusplus
  }
#endif

#endif /* _LIBIDMEF_LIBIDMEF_IO_H */
