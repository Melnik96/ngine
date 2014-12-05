/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
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


#ifndef __ENTITY_H__
#define __ENTITY_H__

struct ngine_entity;

int 			ngine_entity_init(struct ngine_entity* _ent, char* _name, struct ngine_mesh* _mesh);
struct ngine_entity* 	ngine_entity_create(char* _name, struct ngine_mesh* _mesh);
void 			ngine_entity_delete(struct ngine_entity* _self);

void 			ngine_entity_set_name(struct ngine_entity* _self, const char* _name);
char* 			ngine_entity_get_name(struct ngine_entity* _self);

void 			ngine_entity_set_mesh(struct ngine_entity* _self, struct ngine_mesh* _mesh);
struct ngine_mesh* 	ngine_entity_get_mesh(struct ngine_entity* _self);

#endif /* __ENTITY_H__ */
