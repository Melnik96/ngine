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

#include "blenloader/BLO_readfile.h"
#include "blenkernel/BKE_main.h"
#include "makesdna/DNA_scene_types.h"
#include "makesdna/DNA_listBase.h"
#include "makesdna/DNA_node_types.h"
#include "makesdna/DNA_object_types.h"

#include "sc_obj.h"

#include "blen_scene.h"

struct scene* blen_scene_import() {
  struct sc_obj* cur_obj = malloc(sizeof(struct sc_obj));
  BlendFileData* blen = BLO_read_from_file("path", NULL);
  struct Object* b_cur_obj = (struct Object*)(blen->main->object.first);
  
  cur_obj->pos.x = b_cur_obj->loc[0];
  cur_obj->pos.y = b_cur_obj->loc[1];
  cur_obj->pos.z = b_cur_obj->loc[2];
  
  cur_obj->orient.w = b_cur_obj->quat[0];
  cur_obj->orient.x = b_cur_obj->quat[1];
  cur_obj->orient.y = b_cur_obj->quat[2];
  cur_obj->orient.z = b_cur_obj->quat[3];
  
  b_cur_obj;// тут я поняв, що я поєхавший і вирішив створити Vilka OS
}
