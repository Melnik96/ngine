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

#include "physics_mgr.h"

/*
 * forward definitions
 */
G_DEFINE_TYPE(physics_mgr, physics_mgr, G_TYPE_OBJECT);
/*
/* forward declarations of default virtual methods
 */

static void
physics_mgr_dispose(GObject* gobject) {
  physics_mgr* self = PHYSICS_MGR(gobject);

  /*
   * In dispose, you are supposed to free all types referenced from this
   * object which might themselves hold a reference to self. Generally,
   * the most simple solution is to unref all members on which you own a
   * reference.
   */

  /* Chain up to the parent class */
  G_OBJECT_CLASS(physics_mgr_parent_class)->dispose(gobject);
}

static void
physics_mgr_finalize(GObject* gobject) {
  physics_mgr* self = PHYSICS_MGR(gobject);

  /* Chain up to the parent class */
  G_OBJECT_CLASS(physics_mgr_parent_class)->finalize(gobject);
}

static void
physics_mgr_init(physics_mgr* self) {
  /* initialize all public and private members to reasonable default values. */

  /* Default implementations for virtual methods
   * For pure-virtual functions, set these to NULL
   */
}
