/*
 * Queue implementation.
 *
 * Author: Yasunobu Chiba
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
 * @brief Function declarations of Packet parsing implementation
 *
 * File containing functions declarations for handling packets i.e, parsing a packet to find
 * its type (whether IPv4, or ARP) and calculating checksum if required.
 *
 * @code
 * // Calculates checksum
 * get_checksum( ( uint16_t * ) packet_info( buf )->l3_data.ipv4, ( uint32_t ) hdr_len )
 * ...
 *
 * // Validates packet header information
 * bool parse_ok = parse_packet( body );
 * if ( !parse_ok ) {
 * error( "Failed to parse a packet." );
 * ...
 *
 * @endcode
 */

#ifndef QUEUE_H
#define QUEUE_H


#include "trema.h"


typedef struct queue_element {
  buffer *data;
  struct queue_element *next;
} queue_element;

typedef struct queue {
  queue_element *head;
  queue_element *divider;
  queue_element *tail;
  int length;
} queue;


queue *create_queue( void );
bool delete_queue( queue *queue );
bool enqueue( queue *queue, buffer *data );
buffer *dequeue( queue *queue );
buffer *peek( queue *queue );
bool sort_queue( queue *queue, bool compare( const buffer *x, const buffer *y ) );


#endif // QUEUE_H


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */