/*****
*
* Copyright (C) 2004-2016 CS-SI. All Rights Reserved.
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

#ifndef _LIBIDMEF_LIBIDMEF_STRING_H
#define _LIBIDMEF_LIBIDMEF_STRING_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdarg.h>

#include "libidmef-list.h"
#include "libidmef-macros.h"
#include "libidmef-inttypes.h"
#include "libidmef-linked-object.h"

#ifdef __cplusplus
 extern "C" {
#endif


typedef struct libidmef_string libidmef_string_t;


int libidmef_string_new(libidmef_string_t **string);

int libidmef_string_new_nodup(libidmef_string_t **string, char *str);

int libidmef_string_new_ref(libidmef_string_t **string, const char *str);

int libidmef_string_new_dup(libidmef_string_t **string, const char *str);

int libidmef_string_new_dup_fast(libidmef_string_t **string, const char *str, size_t len);

void libidmef_string_destroy(libidmef_string_t *string);

void libidmef_string_destroy_internal(libidmef_string_t *string);

int libidmef_string_new_nodup_fast(libidmef_string_t **string, char *str, size_t len);

int libidmef_string_new_ref_fast(libidmef_string_t **string, const char *str, size_t len);

int libidmef_string_set_dup_fast(libidmef_string_t *string, const char *buf, size_t len);

int libidmef_string_set_dup(libidmef_string_t *string, const char *buf);

int libidmef_string_set_nodup_fast(libidmef_string_t *string, char *buf, size_t len);

int libidmef_string_set_nodup(libidmef_string_t *string, char *buf);

int libidmef_string_set_ref_fast(libidmef_string_t *string, const char *buf, size_t len);

int libidmef_string_set_ref(libidmef_string_t *string, const char *buf);

int libidmef_string_copy_ref(const libidmef_string_t *src, libidmef_string_t *dst);

int libidmef_string_copy_dup(const libidmef_string_t *src, libidmef_string_t *dst);

libidmef_string_t *libidmef_string_ref(libidmef_string_t *string);

int libidmef_string_clone(const libidmef_string_t *src, libidmef_string_t **dst);

size_t libidmef_string_get_len(const libidmef_string_t *string);

const char *libidmef_string_get_string_or_default(const libidmef_string_t *string, const char *def);

const char *libidmef_string_get_string(const libidmef_string_t *string);

int libidmef_string_get_string_released(libidmef_string_t *string, char **outptr);

libidmef_bool_t libidmef_string_is_empty(const libidmef_string_t *string);

int libidmef_string_truncate(libidmef_string_t *string, size_t len);

void libidmef_string_clear(libidmef_string_t *string);

/*
 * string operation
 */
int libidmef_string_cat(libidmef_string_t *dst, const char *str);
int libidmef_string_ncat(libidmef_string_t *dst, const char *str, size_t len);

int libidmef_string_sprintf(libidmef_string_t *string, const char *fmt, ...)
                           LIBIDMEF_FMT_PRINTF(2, 3);

int libidmef_string_vprintf(libidmef_string_t *string, const char *fmt, va_list ap)
                           LIBIDMEF_FMT_PRINTF(2, 0);

int libidmef_string_compare(const libidmef_string_t *str1, const libidmef_string_t *str2);

#define libidmef_string_set_constant(string, str)                         \
        libidmef_string_set_ref_fast((string), (str), strlen((str)))

#define libidmef_string_new_constant(string, str)                         \
        libidmef_string_new_ref_fast((string), (str), strlen((str)))

#ifdef __cplusplus
 }
#endif

#endif /* _LIBIDMEF_LIBIDMEF_STRING_H */
