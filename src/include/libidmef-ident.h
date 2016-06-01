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

#ifndef _LIBIDMEF_LIBIDMEF_IDENT_H
#define _LIBIDMEF_LIBIDMEF_IDENT_H

#include "libidmef-inttypes.h"
#include "libidmef-string.h"

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct libidmef_ident libidmef_ident_t;

int libidmef_ident_generate(libidmef_ident_t *ident, libidmef_string_t *out);

uint64_t libidmef_ident_inc(libidmef_ident_t *ident);

void libidmef_ident_destroy(libidmef_ident_t *ident);

int libidmef_ident_new(libidmef_ident_t **ret);

#ifdef __cplusplus
 }
#endif

#endif /* _LIBIDMEF_LIBIDMEF_IDENT_H */
