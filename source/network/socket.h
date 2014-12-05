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

#ifndef SOCKET_H
#define SOCKET_H

#include <stdint.h>

struct ngine_socket {
  int sock_fd;
};

struct ngine_socket* 	ngine_socket_create();
void 			ngine_socket_delete(struct ngine_socket* _self);
void 			ngine_socket_connect(struct ngine_socket* _self, const char* _addr, int _port);
void 			ngine_socket_listen(struct ngine_socket* _self, int _port);
struct ngine_socket* 	ngine_socket_accept(struct ngine_socket* _self);
void 			ngine_socket_send(struct ngine_socket* _self, void* _data, uint32_t _size);
void 			ngine_socket_recv(struct ngine_socket* _self, void* _data, uint32_t _size);

#endif // SOCKET_H
