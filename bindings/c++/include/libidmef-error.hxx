/*****
*
* Copyright (C) 2008-2016 CS-SI. All Rights Reserved.
* Author: Yoann Vandoorselaere <yoann@libidmef-ids.com>
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

#ifndef _LIBIDMEF_LIBIDMEF_ERROR_HXX
#define _LIBIDMEF_LIBIDMEF_ERROR_HXX

#include <string>
#include <exception>

#define libidmef_except_if_fail(cond) do {                                   \
        if ( ! (cond) )                                                     \
                throw LibIdmefError(libidmef_error(LIBIDMEF_ERROR_ASSERTION)); \
} while(0)


namespace Idmef {
        class LibIdmefError: public std::exception {
            protected:
                int _error;
                std::string _message;

            public:
                virtual ~LibIdmefError() throw() {};
                LibIdmefError(void) throw();
                LibIdmefError(int error) throw();
                LibIdmefError(const std::string &message) throw();

                int getCode(void) const;

                virtual const char *what() const throw();
                operator const char *() const;
                operator int () const;
        };
};

#endif
