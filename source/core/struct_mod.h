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

#ifndef STRUCT_MOD_H
#define STRUCT_MOD_H

#define def_modable_struct(struct) \
  static int struct##_mods_num = 0;

#define def_struct_mod(struct, mod) \
  static int struct##_mod_##mod##_id = 0;

#define reg_struct_mod(struct, mod) \
  struct##_mod_##mod##_id = struct##_mods_num; \
  struct##_mods_num += 1;
  
#define struct_mod_id(struct, mod) struct##_mod_##mod##_id
  
#define obj_get_mod(obj_mod, obj_base, struct_, mod) \
  struct struct_##_mod_##mod* obj_mod = obj_base->mods[struct_mod_id(struct_, mod)]

#endif // STRUCT_MOD_H
