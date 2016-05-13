/*****
*
* Copyright (C) 2009-2016 CS-SI. All Rights Reserved.
* Author: Yoann Vandoorselaere <yoannv@gmail.com>
*
* This file is part of the Prelude library.
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

#include <iostream>

#include <string.h>
#include <idmef.h>
#include <idmef-path.h>
#include <idmef-message-print.h>
#include <idmef-object-prv.h>

#include "prelude-error.hxx"
#include "idmef-path.hxx"
#include "idmef.hxx"

using namespace Idmef;


IDMEF::IDMEF() : _object(NULL)
{
        int ret;

        ret = idmef_message_new((idmef_message_t **) &_object);
        if ( ret < 0 )
                throw PreludeError(ret);
}


IDMEF::IDMEF(const char *json) : _object(NULL)
{
        int ret;

        ret = idmef_object_new_from_json(&_object, json);
        if ( ret < 0 )
                throw PreludeError(ret);
}


IDMEF::IDMEF(const IDMEF &idmef)
{
        _object = (idmef._object) ? idmef_object_ref(idmef._object) : NULL;
}


IDMEF::IDMEF(idmef_object_t *object)
{
        _object = object;
}


IDMEF::~IDMEF()
{
        if ( _object )
                idmef_object_destroy(_object);
}

void IDMEF::set(const char *path, const std::vector<IDMEF> &value)
{
        IDMEFPath(*this, path).set(*this, value);
}


void IDMEF::set(const char *path, IDMEF *value)
{
        IDMEFPath(*this, path).set(*this, value);
}


void IDMEF::set(const char *path, const std::vector<IDMEFValue> &value)
{
        IDMEFPath(*this, path).set(*this, value);
}


void IDMEF::set(const char *path, IDMEFValue *value)
{
        IDMEFPath(*this, path).set(*this, value);
}


void IDMEF::set(const char *path, IDMEFValue &value)
{
        IDMEFPath(*this, path).set(*this, &value);
}


void IDMEF::set(const char *path, const std::string &value)
{
        IDMEFPath(*this, path).set(*this, value);
}


void IDMEF::set(const char *path, const char *value)
{
        IDMEFPath(*this, path).set(*this, value);
}


void IDMEF::set(const char *path, int32_t value)
{
        IDMEFPath(*this, path).set(*this, value);
}


void IDMEF::set(const char *path, int64_t value)
{
        IDMEFPath(*this, path).set(*this, value);
}


void IDMEF::set(const char *path, uint64_t value)
{
        IDMEFPath(*this, path).set(*this, value);
}


void IDMEF::set(const char *path, float value)
{
        IDMEFPath(*this, path).set(*this, value);
}


void IDMEF::set(const char *path, double value)
{
        IDMEFPath(*this, path).set(*this, value);
}


void IDMEF::set(const char *path, IDMEFTime &value)
{
        IDMEFPath(*this, path).set(*this, value);
}


IDMEFValue IDMEF::get(const char *path)
{
        return IDMEFPath(*this, path).get(*this);
}


int IDMEF::operator == (const IDMEF *idmef)
{
        if ( ! idmef )
                return 0;

        if ( _object == idmef->_object )
                return 1;

        return idmef_object_compare(_object, idmef->_object) == 0 ? 1 : 0;
}


IDMEF IDMEF::clone()
{
        int ret;
        idmef_object_t *clone;

        ret = idmef_object_clone(_object, &clone);
        if ( ret < 0 )
                throw PreludeError(ret);

        return IDMEF(clone);
}


idmef_class_id_t IDMEF::getId() const
{
        return _object->_idmef_object_id;
}


const std::string IDMEF::toString() const
{
        int ret;
        std::string str;
        prelude_io_t *fd;

        ret = prelude_io_new(&fd);
        if ( ret < 0 )
                throw PreludeError(ret);

        prelude_io_set_buffer_io(fd);
        idmef_object_print(_object, fd);

        str.assign((const char *) prelude_io_get_fdptr(fd), prelude_io_pending(fd));

        prelude_io_close(fd);
        prelude_io_destroy(fd);

        return str;
}


const std::string IDMEF::toJSON() const
{
        int ret;
        std::string str;
        prelude_io_t *fd;

        ret = prelude_io_new(&fd);
        if ( ret < 0 )
                throw PreludeError(ret);

        prelude_io_set_buffer_io(fd);
        idmef_object_print_json(_object, fd);

        str.assign((const char *) prelude_io_get_fdptr(fd), prelude_io_pending(fd));

        prelude_io_close(fd);
        prelude_io_destroy(fd);

        return str;
}

const std::string IDMEF::toBinary() const
{
        int ret;
        std::string str;
        prelude_io_t *fd;

        ret = prelude_io_new(&fd);
        if ( ret < 0 )
                throw PreludeError(ret);

        prelude_io_set_buffer_io(fd);
        idmef_object_print_binary(_object, fd);

        str.assign((const char *) prelude_io_get_fdptr(fd), prelude_io_pending(fd));

        prelude_io_close(fd);
        prelude_io_destroy(fd);

        return str;
}


IDMEF::operator const std::string() const
{
        return toString();
}


IDMEF::operator idmef_object_t *() const
{
        return (idmef_object_t *) _object;
}


IDMEF &IDMEF::operator = (const IDMEF &idmef)
{
        if ( this != &idmef && _object != idmef._object ) {
                if ( _object )
                        idmef_object_destroy(_object);

                _object = (idmef._object) ? idmef_object_ref(idmef._object) : NULL;
        }

        return *this;
}
