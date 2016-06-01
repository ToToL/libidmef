/*****
*
* Copyright (C) 2005-2016 CS-SI. All Rights Reserved.
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

#ifndef _LIBIDMEF_LIBIDMEF_LOG_H
#define _LIBIDMEF_LIBIDMEF_LOG_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "libidmef-macros.h"
#include <stdarg.h>

#ifdef __cplusplus
 extern "C" {
#endif

typedef enum {
        LIBIDMEF_LOG_CRIT  = -1,
        LIBIDMEF_LOG_ERR   =  0,
        LIBIDMEF_LOG_WARN  =  1,
        LIBIDMEF_LOG_INFO  =  2,
        LIBIDMEF_LOG_DEBUG  = 3
} libidmef_log_t;


typedef enum {
        LIBIDMEF_LOG_FLAGS_QUIET  = 0x01, /* Drop LIBIDMEF_LOG_PRIORITY_INFO */
        LIBIDMEF_LOG_FLAGS_SYSLOG = 0x02
} libidmef_log_flags_t;



void _libidmef_log_v(libidmef_log_t level, const char *file,
                    const char *function, int line, const char *fmt, va_list ap)
                    LIBIDMEF_FMT_PRINTF(5, 0);

void _libidmef_log(libidmef_log_t level, const char *file,
                  const char *function, int line, const char *fmt, ...)
                  LIBIDMEF_FMT_PRINTF(5, 6);


#ifdef HAVE_VARIADIC_MACROS

#define libidmef_log(level, ...) \
        _libidmef_log(level, __FILE__, __LIBIDMEF_FUNC__, __LINE__, __VA_ARGS__)

#define libidmef_log_debug(level, ...) \
        _libidmef_log(LIBIDMEF_LOG_DEBUG + level, __FILE__, __LIBIDMEF_FUNC__, __LINE__, __VA_ARGS__)
#else

void libidmef_log(libidmef_log_t level, const char *fmt, ...)
                 LIBIDMEF_FMT_PRINTF(2, 3);

void libidmef_log_debug(libidmef_log_t level, const char *fmt, ...)
                       LIBIDMEF_FMT_PRINTF(2, 3);

#endif


#define libidmef_log_v(level, fmt, ap) \
        _libidmef_log_v(level, __FILE__, __LIBIDMEF_FUNC__, __LINE__, fmt, ap)

#define libidmef_log_debug_v(level, fmt, ap) \
        _libidmef_log_v(LIBIDMEF_LOG_DEBUG + level, __FILE__, __LIBIDMEF_FUNC__, __LINE__, fmt, ap)


void libidmef_log_set_level(libidmef_log_t level);

void libidmef_log_set_debug_level(int level);

libidmef_log_flags_t libidmef_log_get_flags(void);

void libidmef_log_set_flags(libidmef_log_flags_t flags);

char *libidmef_log_get_prefix(void);

void libidmef_log_set_prefix(char *prefix);

void libidmef_log_set_callback(void log_cb(libidmef_log_t level, const char *str));

int libidmef_log_set_logfile(const char *filename);

void _libidmef_log_set_abort_level(libidmef_log_t level);

int _libidmef_log_set_abort_level_from_string(const char *level);

#ifdef __cplusplus
 }
#endif

#endif /* _LIBIDMEF_LIBIDMEF_LOG_H */
