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

#include "scenegraph/sc_node.h"
#include "scenegraph/scene.h"
#include "sc_node_phys.h"
#include "scene_phys.h"

#include "phys_rigidbody_mod.h"

void ngine_phys_rigidbody_mod_init() {
  reg_struct_mod(ngine_sc_node, phys);
  reg_struct_mod(ngine_scene, phys);
}
