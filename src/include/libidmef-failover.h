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

#ifndef _LIBIDMEF_LIBIDMEF_FAILOVER_H
#define _LIBIDMEF_LIBIDMEF_FAILOVER_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct libidmef_failover libidmef_failover_t;

void libidmef_failover_destroy(libidmef_failover_t *failover);

int libidmef_failover_new(libidmef_failover_t **ret, const char *dirname);

void libidmef_failover_set_quota(libidmef_failover_t *failover, size_t limit);

int libidmef_failover_save_msg(libidmef_failover_t *failover, libidmef_msg_t *msg);

ssize_t libidmef_failover_get_saved_msg(libidmef_failover_t *failover, libidmef_msg_t **out);

unsigned long libidmef_failover_get_deleted_msg_count(libidmef_failover_t *failover);

unsigned long libidmef_failover_get_available_msg_count(libidmef_failover_t *failover);

void libidmef_failover_enable_transaction(libidmef_failover_t *failover);

void libidmef_failover_disable_transaction(libidmef_failover_t *failover);

int libidmef_failover_commit(libidmef_failover_t *failover, libidmef_msg_t *msg);

int libidmef_failover_rollback(libidmef_failover_t *failover, libidmef_msg_t *msg);

#ifdef __cplusplus
 }
#endif

#endif
