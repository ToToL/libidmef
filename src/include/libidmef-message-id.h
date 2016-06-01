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

#ifndef _LIBIDMEF_LIBIDMEF_MESSAGE_ID_H
#define _LIBIDMEF_LIBIDMEF_MESSAGE_ID_H

/*
 * Top level message tag (to be used with libidmef_msg_new()).
 */
#define LIBIDMEF_MSG_IDMEF          0
#define LIBIDMEF_MSG_ID             3
#define LIBIDMEF_MSG_AUTH           4
#define LIBIDMEF_MSG_CM             5 
#define LIBIDMEF_MSG_CONNECTION_CAPABILITY    6
#define LIBIDMEF_MSG_OPTION_REQUEST 7
#define LIBIDMEF_MSG_OPTION_REPLY   8

/*
 * LIBIDMEF_MSG_ID submessage
 */
#define LIBIDMEF_MSG_ID_DECLARE  0

/*
 * authentication msg
 */
#define LIBIDMEF_MSG_AUTH_SUCCEED   6
#define LIBIDMEF_MSG_AUTH_FAILED    7


/*
 * LIBIDMEF_MSG_CM submessages
 */
#define LIBIDMEF_MSG_CM_FIREWALL 0
#define LIBIDMEF_MSG_CM_THROTTLE 1
#define LIBIDMEF_MSG_CM_ISLAND   2
#define LIBIDMEF_MSG_CM_FEATURE  3

/*
 * LIBIDMEF_MSG_OPTION submessages
 */
#define LIBIDMEF_MSG_OPTION_TARGET_ID        0
#define LIBIDMEF_MSG_OPTION_LIST             2
#define LIBIDMEF_MSG_OPTION_VALUE            3
#define LIBIDMEF_MSG_OPTION_SET              4
#define LIBIDMEF_MSG_OPTION_GET              5
#define LIBIDMEF_MSG_OPTION_REQUEST_ID       6
#define LIBIDMEF_MSG_OPTION_ERROR            7
#define LIBIDMEF_MSG_OPTION_START            8
#define LIBIDMEF_MSG_OPTION_END              9
#define LIBIDMEF_MSG_OPTION_NAME            10
#define LIBIDMEF_MSG_OPTION_DESC            11
#define LIBIDMEF_MSG_OPTION_HAS_ARG         12
#define LIBIDMEF_MSG_OPTION_HELP            13
#define LIBIDMEF_MSG_OPTION_INPUT_VALIDATION 14
#define LIBIDMEF_MSG_OPTION_INPUT_TYPE       15
#define LIBIDMEF_MSG_OPTION_ARG              16
#define LIBIDMEF_MSG_OPTION_TYPE             17
#define LIBIDMEF_MSG_OPTION_DESTROY          18
#define LIBIDMEF_MSG_OPTION_COMMIT           19
#define LIBIDMEF_MSG_OPTION_HOP              20
#define LIBIDMEF_MSG_OPTION_TARGET_INSTANCE_ID 21

#endif /* _LIBIDMEF_LIBIDMEF_MESSAGE_ID_H */
