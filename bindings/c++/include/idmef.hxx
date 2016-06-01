/*****
*
* Copyright (C) 2009-2016 CS-SI. All Rights Reserved.
* Author: Yoann Vandoorselaere <yoannv@gmail.com>
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

#ifndef _LIBIDMEF_IDMEF_HXX
#define _LIBIDMEF_IDMEF_HXX

#include <string>
#include <iostream>
#include "idmef-value.hxx"
#include "idmef-time.hxx"

namespace Idmef
{
        class IDMEF;
}

namespace Idmef {
        class IDMEF {
            protected:
                idmef_object_t *_object;

            public:
                ~IDMEF();
                IDMEF();
                IDMEF(const char *json);
                IDMEF(const IDMEF &idmef);
                IDMEF(idmef_object_t *message);

                void set(const char *path, const std::vector<Idmef::IDMEF> &value);
                void set(const char *path, Idmef::IDMEF *value);
                void set(const char *path, const std::vector<Idmef::IDMEFValue> &value);
                void set(const char *path, const std::string &value);
                void set(const char *path, Idmef::IDMEFValue *value);
                void set(const char *path, Idmef::IDMEFValue &value);
                void set(const char *path, Idmef::IDMEFTime &value);
                void set(const char *path, const char *value);
                void set(const char *path, int32_t value);
                void set(const char *path, int64_t value);
                void set(const char *path, uint64_t value);
                void set(const char *path, float value);
                void set(const char *path, double value);
                Idmef::IDMEFValue get(const char *path);


                IDMEF clone();
                idmef_class_id_t getId() const;
                const std::string toString() const;
                const std::string toJSON() const;
                const std::string toBinary() const;

                operator const std::string() const;
                operator idmef_object_t *() const;
                IDMEF &operator = (const IDMEF &idmef);
                int operator == (const IDMEF *idmef);
        };
};

#endif /* __LIBIDMEF_IDMEF_HXX */
