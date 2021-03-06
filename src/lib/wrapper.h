/*
 * Wrappers that simplifies the handling of memory allocation errors.
 *
 * Author: Yasuhito Takamiya <yasuhito@gmail.com>
 *
 * Copyright (C) 2008-2011 NEC Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/**
 * @file
 *
 * @brief Wrapper definitons for basic library functions
 * @code
 * // Memory allocation using malloc
 * new_entry = xmalloc( sizeof( match_entry ) );
 * // Memory allocation using calloc
 * packet_header_info *header_info = xcalloc( 1, sizeof( packet_header_info ) );
 * // Free allocated memory
 * xfree( trema_name );
 * // Duplicate string in memory
 * trema_name = xstrdup( name );
 * @endcode
 */

#ifndef WRAPPER_H
#define WRAPPER_H


#include <stddef.h>
#include <string.h>
#include "utility.h"


// If this is being built for a unit test.
#ifdef UNIT_TESTING

// Redirect assert to mock_assert() so assertions can be caught by cmockery.
#ifdef assert
#undef assert
#endif // assert
#define assert( expression )                                                \
  mock_assert( ( int ) ( expression ), #expression, __FILE__, __LINE__ );
extern void mock_assert( const int result, const char *const expression, const char *const file, const int line );

#endif // UNIT_TESTING


// Undef Ruby's xmalloc()
#ifdef xmalloc
#undef xmalloc
#endif
void *xmalloc( size_t size );

// Undef Ruby's xcalloc()
#ifdef xcalloc
#undef xcalloc
#endif
void *xcalloc( size_t nmemb, size_t size );

// Undef Ruby's xfree()
#ifdef xfree
#undef xfree
#endif
void xfree( void *ptr );

char *xstrdup( const char *s );
char *xasprintf( const char *format, ... );


#endif // WRAPPER_H


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */
