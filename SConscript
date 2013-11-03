#!/usr/bin/env python
#
# ***** BEGIN GPL LICENSE BLOCK *****
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# The Original Code is Copyright (C) 2006, Blender Foundation
# All rights reserved.
#
# The Original Code is: all of this file.
#
# Contributor(s): Nathan Letwory.
#
# ***** END GPL LICENSE BLOCK *****

Import ('env')

sources = env.Glob('*.cpp')

incs = '. #intern/string #intern/moto/include'
incs += ' #source/gameengine/Ketsji #intern/container'
incs += ' #source/gameengine/GameLogic #source/gameengine/Expressions'
incs += ' #source/gameengine/Network #source/gameengine/SceneGraph'

defs = []

if env['WITH_BF_PYTHON']:
    incs += ' ' + env['BF_PYTHON_INC']
    defs.append('WITH_PYTHON')

env.BlenderLib ( 'bf_network', Split(sources), Split(incs), defines=defs,libtype=['core','player'], priority=[400,125], cxx_compileflags=env['BGE_CXXFLAGS'])
