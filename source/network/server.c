/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <memory.h>
#include <malloc.h>
#include <pthread.h>

#include "core/log.h"
#include "network/socket.h"

#include "server.h"

typedef struct accept_handler_args {
  struct ngine_server* _self;
  struct ngine_socket* _accept_sock;
} accept_handler_args_t;
void* ngine_server_accept_handler(accept_handler_args_t* args);

struct ngine_server* ngine_server_create(struct ngine_socket* _sock) {
  struct ngine_server* new_server = calloc(1, sizeof(struct ngine_server));
  
  new_server->base_sock = _sock;
  
  return new_server;
}

void ngine_server_delete(struct ngine_server* _self) {
//   ngine_socket_delete(_self->base_sock);
  free(_self->events);
  free(_self);
}

void ngine_server_start(struct ngine_server* _self) {
  struct ngine_socket* accept_sock = 0;
  while(!_self->stop) {
    accept_sock = ngine_socket_accept(_self->base_sock);
    
    pthread_t new_thr;
    pthread_create(&new_thr, 0, ngine_server_accept_handler, &(accept_handler_args_t){_self, accept_sock});
  }
}

void ngine_server_stop(struct ngine_server* _self) {
  _self->stop = 1;
}

void ngine_server_add_handler(struct ngine_server* _self, uint32_t _id, event_handler_t _event_handler, void* _args) {
  _self->events = realloc(_self->events, (_self->num_events+1)*sizeof(struct ngine_server_event));
  _self->events[_self->num_events].id = _id;
  _self->events[_self->num_events].handler = _event_handler;
  _self->events[_self->num_events].args = _args;
  
  _self->num_events += 1;
}

void ngine_server_remove_handler(struct ngine_server* _self, uint32_t _id) {
  for(uint32_t i = 0; i != _self->num_events; ++i) {
    if(_self->events[i].id == _id) {/* drink & write */}
  }
}

void* ngine_server_accept_handler(accept_handler_args_t* args) {
  debug("server accept client");
  void* buf = malloc(sizeof(uint32_t));
  
  uint32_t 	event_id;
  char 		event_defined = 0;
  char 		close_connection = 0;
  
  while(1/*!close_connection*/) {
    ngine_socket_recv(args->_accept_sock, buf, sizeof(uint32_t));
    event_id = *(uint32_t*)buf;
    
    for(uint32_t i = 0; i != args->_self->num_events; ++i) {
//       printf("event id: %x %x", event_id, args->_self->events[i].id);
      if(args->_self->events[i].id == event_id) {
	event_defined = 1;
	if(args->_self->events[i].handler(args->_accept_sock, args->_self->events[i].args) == 1) {/*close_connection = 1;*/break; };
	break;
      }
    }
    if(!event_defined) {
      debug("received an undefined event");
    }
  }
  
  free(buf);
  
  ngine_socket_delete(args->_accept_sock);
}
