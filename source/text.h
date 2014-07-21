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

#ifndef TEXT_H
#define TEXT_H

struct ngine_text {
  char* str;
};

void 			ngine_text_create(struct ngine_text* _self);
void 			ngine_text_destroy(struct ngine_text* _self);
void 			ngine_text_update(struct ngine_text* _self);
struct ngine_texture* 	ngine_text_texture(struct ngine_text* _self);

#endif // TEXT_H
