/*
 * Author: Kazuya Suzuki
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


#include <assert.h>
#include "checks.h"
#include "packet_info.h"
#include "wrapper.h"
#include "trema.h"


/**
 * Releases the memory allocated to structure of type packet_header_info.
 *
 * @param buf Pointer to buffer type structure
 * @return None
 */
void
free_packet_info( buffer *buf ) {
  die_if_NULL( buf );
  die_if_NULL( buf->user_data );

  xfree( buf->user_data );
  buf->user_data = NULL;
  buf->user_data_free_function = NULL;
}


/**
 * Allocates memory to structure of type packet_header_info.
 *
 * @param buf Pointer to buffer type structure
 * @return None
 */
void
calloc_packet_info( buffer *buf ) {
  die_if_NULL( buf );

  void *user_data = xcalloc( 1, sizeof( packet_info ) );
  assert( user_data != NULL );

  memset( user_data, 0, sizeof( packet_info ) );

  buf->user_data = user_data;
  buf->user_data_free_function = free_packet_info;
}


/**
 * This function is deprecated.
 *
 * Releases the memory allocated to structure of type buffer.
 * @param buf Pointer to buffer type structure
 * @return packet_info TODO
 */
packet_info
get_packet_info( const buffer *frame ) {
  die_if_NULL( frame );

  packet_info info;
  
  if ( frame->user_data != NULL ) {
    info = *( packet_info * ) frame->user_data;
  } 
  else {
    memset( &info, 0, sizeof( info ) );
  }
  
  return info;
}


static bool
if_packet_type( const buffer *frame, const uint32_t type ) {
  die_if_NULL( frame );
  packet_info packet_info = get_packet_info( frame );
  return ( ( packet_info.format & type ) == type );
}


bool
packet_type_eth_dix( const buffer *frame ) {
  die_if_NULL( frame );
  return if_packet_type( frame, ETH_DIX );
}


bool
packet_type_eth_vtag( const buffer *frame ) {
  die_if_NULL( frame );
  return if_packet_type( frame, ETH_8021Q );
}


bool
packet_type_eth_raw( const buffer *frame ) {
  die_if_NULL( frame );
  return if_packet_type( frame, ETH_8023_RAW );
}


bool
packet_type_eth_llc( const buffer *frame ) {
  die_if_NULL( frame );
  return if_packet_type( frame, ETH_8023_LLC );
}


bool
packet_type_ether( const buffer *frame ) {
  die_if_NULL( frame );
  return ( if_packet_type( frame, ETH_DIX ) |
           if_packet_type( frame, ETH_8023_RAW ) |
           if_packet_type( frame, ETH_8023_LLC ) |
           if_packet_type( frame, ETH_8023_SNAP ) );
}


bool
packet_type_eth_snap( const buffer *frame ) {
  die_if_NULL( frame );
  return if_packet_type( frame, ETH_8023_SNAP );
}


bool
packet_type_arp( const buffer *frame ) {
  die_if_NULL( frame );
  return if_packet_type( frame, NW_ARP );
}


bool
packet_type_ipv4( const buffer *frame ) {
  die_if_NULL( frame );
  return if_packet_type( frame, NW_IPV4 );
}


bool
packet_type_icmpv4( const buffer *frame ) {
  die_if_NULL( frame );
  return if_packet_type( frame, NW_ICMPV4 );
}


bool
packet_type_ipv4_tcp( const buffer *frame ) {
  die_if_NULL( frame );
  return if_packet_type( frame, NW_IPV4 | TP_TCP );
}


bool
packet_type_ipv4_udp( const buffer *frame ) {
  die_if_NULL( frame );
  return if_packet_type( frame, NW_IPV4 | TP_UDP );
}



/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */
