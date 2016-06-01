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

#ifndef _LIBIDMEF_LIBIDMEF_LINKED_OBJECT_H
#define _LIBIDMEF_LIBIDMEF_LINKED_OBJECT_H


#include "libidmef-list.h"


#define LIBIDMEF_LINKED_OBJECT    \
        unsigned int _object_id; \
        libidmef_list_t _list


typedef struct {
        LIBIDMEF_LINKED_OBJECT;
} libidmef_linked_object_t;



static inline void libidmef_linked_object_del(libidmef_linked_object_t *obj) 
{
        libidmef_list_del(&obj->_list);
}



static inline void libidmef_linked_object_del_init(libidmef_linked_object_t *obj) 
{
        libidmef_list_del(&obj->_list);
        libidmef_list_init(&obj->_list);
}



static inline void libidmef_linked_object_add(libidmef_list_t *head, libidmef_linked_object_t *obj) 
{
        libidmef_list_add(head, &obj->_list);
}



static inline void libidmef_linked_object_add_tail(libidmef_list_t *head, libidmef_linked_object_t *obj) 
{
        libidmef_list_add_tail(head, &obj->_list);
}


static inline void libidmef_linked_object_set_id(libidmef_linked_object_t *obj, unsigned int id)
{
        obj->_object_id = id;
}


static inline unsigned int libidmef_linked_object_get_id(libidmef_linked_object_t *obj)
{
        return obj->_object_id;
}



#define libidmef_linked_object_get_object(object)  \
        (void *) libidmef_list_entry(object, libidmef_linked_object_t, _list)


#endif /* _LIBIDMEF_LIBIDMEF_LINKED_OBJECT_H */
