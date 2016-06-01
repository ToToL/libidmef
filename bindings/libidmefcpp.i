/*****
*
* Copyright (C) 2005-2016 CS-SI. All Rights Reserved.
* Author: Yoann Vandoorselaere <yoannv@libidmef-ids.com>
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

#if defined(SWIGPYTHON) || defined(SWIGLUA)
%module idmef
#else
%module Idmef
#endif

%warnfilter(509);
%feature("nothread", "1");

%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

%{
#pragma GCC diagnostic ignored "-Wunused-variable"

#include <list>
#include <sstream>

#include "libidmef.hxx"
#include "libidmef-error.hxx"
#include "idmef-criteria.hxx"
#include "idmef-value.hxx"
#include "idmef-path.hxx"
#include "idmef-time.hxx"
#include "idmef.hxx"

using namespace Idmef;
%}


typedef char int8_t;
typedef unsigned char uint8_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef int int32_t;
typedef unsigned int uint32_t;

typedef long long int64_t;
typedef unsigned long long uint64_t;

%ignore libidmef_error_t;
typedef signed int libidmef_error_t;

%ignore idmef_class_id_t;
typedef int idmef_class_id_t;

typedef long long time_t;


%exception {
        try {
                $action
        } catch(Idmef::LibIdmefError &e) {
                SWIG_exception(SWIG_RuntimeError, e.what());
                SWIG_fail;
        }
}


#ifdef SWIGPERL
%include perl/libidmefcpp-perl.i
#endif

#ifdef SWIGPYTHON
%include python/libidmefcpp-python.i
#endif

#ifdef SWIGRUBY
%include ruby/libidmefcpp-ruby.i
#endif

#ifdef SWIGLUA
%include lua/libidmefcpp-lua.i
#endif


%ignore operator <<(std::ostream &os, const Idmef::IDMEF &idmef);
%ignore operator >>(std::istream &is, const Idmef::IDMEF &idmef);


%template() std::vector<std::string>;
%template() std::vector<Idmef::IDMEF>;
%template() std::vector<Idmef::IDMEFValue>;
%template() std::vector<Idmef::Connection>;

#ifdef SWIG_COMPILE_LIBIDMEF
%extend Idmef::IDMEF {
        Idmef::IDMEFValue get(const char *path) {
                Idmef::IDMEFValue value;
                Idmef::IDMEFPath ipath = Idmef::IDMEFPath(*self, path);

                value = ipath.get(*self);
                if ( value.isNull() && ipath.isAmbiguous() ) {
                        std::vector<Idmef::IDMEFValue> v;
                        return Idmef::IDMEFValue(v);
                }

                return value;
        }
}

%extend Idmef::IDMEFPath {
        Idmef::IDMEFValue get(Idmef::IDMEF &message) {
                Idmef::IDMEFValue value;

                value = self->get(message);
                if ( value.isNull() && self->isAmbiguous() ) {
                        std::vector<Idmef::IDMEFValue> v;
                        return Idmef::IDMEFValue(v);
                }

                return value;
        }
}
#endif

%ignore Idmef::IDMEF::get;
%ignore Idmef::IDMEFPath::get;


%fragment("SWIG_FromBytePtrAndSize", "header", fragment="SWIG_FromCharPtrAndSize") %{
#ifndef SWIG_FromBytePtrAndSize
# define SWIG_FromBytePtrAndSize(arg, len) SWIG_FromCharPtrAndSize(arg, len)
#endif
%}


%fragment("IDMEFValue_to_SWIG", "header", fragment="SWIG_From_double",
                                          fragment="SWIG_From_float",
                                          fragment="SWIG_From_int", fragment="SWIG_From_unsigned_SS_int",
                                          fragment="SWIG_From_long_SS_long", fragment="SWIG_From_unsigned_SS_long_SS_long",
                                          fragment="SWIG_FromCharPtr", fragment="SWIG_FromCharPtrAndSize", fragment="SWIG_FromBytePtrAndSize",
                                          fragment="IDMEFValueList_to_SWIG") {

int IDMEFValue_to_SWIG(TARGET_LANGUAGE_SELF self, const Idmef::IDMEFValue &result, void *extra, TARGET_LANGUAGE_OUTPUT_TYPE ret)
{
        idmef_value_t *value = result;
        Idmef::IDMEFValue::IDMEFValueTypeEnum type = result.getType();

        if ( type == Idmef::IDMEFValue::TYPE_STRING ) {
                libidmef_string_t *str = idmef_value_get_string(value);
                *ret = SWIG_FromCharPtrAndSize(libidmef_string_get_string(str), libidmef_string_get_len(str));
        }

        else if ( type == Idmef::IDMEFValue::TYPE_INT8 )
                *ret = SWIG_From_int(idmef_value_get_int8(value));

        else if ( type == Idmef::IDMEFValue::TYPE_UINT8 )
                *ret = SWIG_From_unsigned_SS_int(idmef_value_get_uint8(value));

        else if ( type == Idmef::IDMEFValue::TYPE_INT16 )
                *ret = SWIG_From_int(idmef_value_get_int16(value));

        else if ( type == Idmef::IDMEFValue::TYPE_UINT16 )
                *ret = SWIG_From_unsigned_SS_int(idmef_value_get_uint16(value));

        else if ( type == Idmef::IDMEFValue::TYPE_INT32 )
                *ret = SWIG_From_int(idmef_value_get_int32(value));

        else if ( type == Idmef::IDMEFValue::TYPE_UINT32 )
                *ret = SWIG_From_unsigned_SS_int(idmef_value_get_uint32(value));

        else if ( type == Idmef::IDMEFValue::TYPE_INT64 )
                *ret = SWIG_From_long_SS_long(idmef_value_get_int64(value));

        else if ( type == Idmef::IDMEFValue::TYPE_UINT64 )
                *ret = SWIG_From_unsigned_SS_long_SS_long(idmef_value_get_uint64(value));

        else if ( type == Idmef::IDMEFValue::TYPE_FLOAT )
                *ret = SWIG_From_float(idmef_value_get_float(value));

        else if ( type == Idmef::IDMEFValue::TYPE_DOUBLE )
                *ret = SWIG_From_double(idmef_value_get_double(value));

        else if ( type == Idmef::IDMEFValue::TYPE_ENUM ) {
                const char *s = idmef_class_enum_to_string(idmef_value_get_class(value), idmef_value_get_enum(value));
                *ret = SWIG_FromCharPtr(s);
        }

        else if ( type == Idmef::IDMEFValue::TYPE_TIME ) {
                Idmef::IDMEFTime t = result;
                *ret = SWIG_NewPointerObj(new Idmef::IDMEFTime(t), $descriptor(Idmef::IDMEFTime *), 1);
        }

        else if ( type == Idmef::IDMEFValue::TYPE_LIST )
                *ret = IDMEFValueList_to_SWIG(self, result, extra);

        else if ( type == Idmef::IDMEFValue::TYPE_DATA ) {
                idmef_data_t *d = idmef_value_get_data(value);
                idmef_data_type_t t = idmef_data_get_type(d);

                if ( t == IDMEF_DATA_TYPE_BYTE || t == IDMEF_DATA_TYPE_BYTE_STRING )
                        *ret = SWIG_FromBytePtrAndSize((const char *)idmef_data_get_data(d), idmef_data_get_len(d));

                else if ( t == IDMEF_DATA_TYPE_CHAR )
                        *ret = SWIG_FromCharPtrAndSize((const char *)idmef_data_get_data(d), idmef_data_get_len(d));

                else if ( t == IDMEF_DATA_TYPE_CHAR_STRING )
                        *ret = SWIG_FromCharPtrAndSize((const char *)idmef_data_get_data(d), idmef_data_get_len(d) - 1);

                else if ( t == IDMEF_DATA_TYPE_FLOAT )
                        *ret = SWIG_From_float(idmef_data_get_float(d));

                else if ( t == IDMEF_DATA_TYPE_UINT32 || IDMEF_DATA_TYPE_INT )
                        *ret = SWIG_From_unsigned_SS_long_SS_long(idmef_data_get_int(d));
        }

        else if ( type == Idmef::IDMEFValue::TYPE_CLASS ) {
                idmef_object_t *obj = (idmef_object_t *) idmef_value_get_object(value);
                *ret = SWIG_NewPointerObj(new Idmef::IDMEF(idmef_object_ref(obj)), $descriptor(Idmef::IDMEF *), 1);
        }

        else return -1;

        return 1;
}
}

%ignore Idmef::IDMEFValue::operator const char*() const;
%ignore Idmef::IDMEFValue::operator std::vector<IDMEFValue>() const;
%ignore Idmef::IDMEFValue::operator Idmef::IDMEFTime() const;
%ignore Idmef::IDMEFValue::operator int8_t() const;
%ignore Idmef::IDMEFValue::operator uint8_t() const;
%ignore Idmef::IDMEFValue::operator int16_t() const;
%ignore Idmef::IDMEFValue::operator uint16_t() const;
%ignore Idmef::IDMEFValue::operator int32_t() const;
%ignore Idmef::IDMEFValue::operator uint32_t() const;
%ignore Idmef::IDMEFValue::operator int64_t() const;
%ignore Idmef::IDMEFValue::operator uint64_t() const;
%ignore Idmef::IDMEFValue::operator float() const;
%ignore Idmef::IDMEFValue::operator double() const;

/*
 * Force SWIG to use the IDMEFValue * version of the Set() function,
 * so that the user might provide NULL IDMEFValue. Force usage of the
 * std::string value, for binary data.
 */
%ignore Idmef::IDMEF::set(char const *, int8_t);
%ignore Idmef::IDMEF::set(char const *, uint8_t);
%ignore Idmef::IDMEF::set(char const *, int16_t);
%ignore Idmef::IDMEF::set(char const *, uint16_t);
%ignore Idmef::IDMEF::set(char const *, char const *);
%ignore Idmef::IDMEF::set(char const *, Idmef::IDMEFValue &value);
%ignore Idmef::IDMEFPath::set(Idmef::IDMEF &, int8_t) const;
%ignore Idmef::IDMEFPath::set(Idmef::IDMEF &, uint8_t) const;
%ignore Idmef::IDMEFPath::set(Idmef::IDMEF &, int16_t) const;
%ignore Idmef::IDMEFPath::set(Idmef::IDMEF &, uint16_t) const;
%ignore Idmef::IDMEFPath::set(Idmef::IDMEF &, char const *) const;
%ignore Idmef::IDMEFPath::set(Idmef::IDMEF &, Idmef::IDMEFValue &) const;
%ignore Idmef::IDMEFValue::IDMEFValue(char const *);

%ignore idmef_path_t;
%ignore idmef_object_t;
%ignore idmef_criteria_t;
%ignore operator idmef_path_t *() const;
%ignore operator idmef_criteria_t *() const;
%ignore operator idmef_object_t *() const;
%ignore operator idmef_message_t *() const;
%ignore operator idmef_time_t *() const;
%ignore operator idmef_value_t *() const;

/*
 * We need to unlock the interpreter lock before calling certain methods
 * because they might acquire internal libidmef mutex that may also be
 * acquired undirectly through the libidmef asynchronous stack.
 *
 * [Thread 2]: Liblibidmef async stack
 * -> Lock internal mutexX
 *    -> libidmef_log()
 *       -> SWIG/C log callback
 *          -> Wait on Interpreter lock [DEADLOCK]
 *             -> Python logging callback (never called)
 *
 * [Thread 1] ConnectionPool::Recv()
 *  -> Acquire Interpreter lock
 *      *** At this time, thread 2 lock internal mutexX
 *      -> Wait on internal mutexX [DEADLOCK]
 *
 * In this situation, [Thread 1] hold the Interpreter lock and is
 * waiting on mutexX, which itself cannot be released by [Thread 2]
 * until [Thread 1] unlock the Interpreter lock.
 *
 * One rule to prevent deadlock is to always acquire mutex in the same
 * order. We thus need to make sure the interpreter lock is released
 * before calling C++ method that are susceptible to lock a mutex that
 * is also triggered from the asynchronous interface.
 *
 * Note that we are not releasing the Interpreter lock in all C++ call,
 * because it come at a performance cost, so we only try to do it when
 * needed.
 */

#ifdef SWIG_COMPILE_LIBIDMEF
%feature("exceptionclass") Idmef::LibIdmefError;
%feature("kwargs") Idmef::IDMEFClass::getPath;
%feature("kwargs") Idmef::IDMEFPath::getClass;
%feature("kwargs") Idmef::IDMEFPath::getValueType;
%feature("kwargs") Idmef::IDMEFPath::setIndex;
%feature("kwargs") Idmef::IDMEFPath::getIndex;
%feature("kwargs") Idmef::IDMEFPath::undefineIndex;
%feature("kwargs") Idmef::IDMEFPath::compare;
%feature("kwargs") Idmef::IDMEFPath::getName;
%feature("kwargs") Idmef::IDMEFPath::isList;

%include libidmef.hxx
%include libidmef-error.hxx
%include idmef-criteria.hxx
%include idmef-value.hxx
%include idmef-path.hxx
%include idmef-time.hxx
%include idmef-class.hxx
%include idmef.hxx
#endif

