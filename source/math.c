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

#include "math.h"

const mat4 identitymatrix = {
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

int mat4_mul(mat4* _mat, mat4* _f, mat4* _s) {
  _mat->m[0][0] = _f->m[0][0] * _s->m[0][0] + _f->m[0][1] * _s->m[1][0] + _f->m[0][2] * _s->m[2][0] + _f->m[0][3] * _s->m[3][0];
  _mat->m[0][1] = _f->m[0][0] * _s->m[0][1] + _f->m[0][1] * _s->m[1][1] + _f->m[0][2] * _s->m[2][1] + _f->m[0][3] * _s->m[3][1];
  _mat->m[0][2] = _f->m[0][0] * _s->m[0][2] + _f->m[0][1] * _s->m[1][2] + _f->m[0][2] * _s->m[2][2] + _f->m[0][3] * _s->m[3][2];
  _mat->m[0][3] = _f->m[0][0] * _s->m[0][3] + _f->m[0][1] * _s->m[1][3] + _f->m[0][2] * _s->m[2][3] + _f->m[0][3] * _s->m[3][3];

  _mat->m[1][0] = _f->m[1][0] * _s->m[0][0] + _f->m[1][1] * _s->m[1][0] + _f->m[1][2] * _s->m[2][0] + _f->m[1][3] * _s->m[3][0];
  _mat->m[1][1] = _f->m[1][0] * _s->m[0][1] + _f->m[1][1] * _s->m[1][1] + _f->m[1][2] * _s->m[2][1] + _f->m[1][3] * _s->m[3][1];
  _mat->m[1][2] = _f->m[1][0] * _s->m[0][2] + _f->m[1][1] * _s->m[1][2] + _f->m[1][2] * _s->m[2][2] + _f->m[1][3] * _s->m[3][2];
  _mat->m[1][3] = _f->m[1][0] * _s->m[0][3] + _f->m[1][1] * _s->m[1][3] + _f->m[1][2] * _s->m[2][3] + _f->m[1][3] * _s->m[3][3];

  _mat->m[2][0] = _f->m[2][0] * _s->m[0][0] + _f->m[2][1] * _s->m[1][0] + _f->m[2][2] * _s->m[2][0] + _f->m[2][3] * _s->m[3][0];
  _mat->m[2][1] = _f->m[2][0] * _s->m[0][1] + _f->m[2][1] * _s->m[1][1] + _f->m[2][2] * _s->m[2][1] + _f->m[2][3] * _s->m[3][1];
  _mat->m[2][2] = _f->m[2][0] * _s->m[0][2] + _f->m[2][1] * _s->m[1][2] + _f->m[2][2] * _s->m[2][2] + _f->m[2][3] * _s->m[3][2];
  _mat->m[2][3] = _f->m[2][0] * _s->m[0][3] + _f->m[2][1] * _s->m[1][3] + _f->m[2][2] * _s->m[2][3] + _f->m[2][3] * _s->m[3][3];

  _mat->m[3][0] = _f->m[3][0] * _s->m[0][0] + _f->m[3][1] * _s->m[1][0] + _f->m[3][2] * _s->m[2][0] + _f->m[3][3] * _s->m[3][0];
  _mat->m[3][1] = _f->m[3][0] * _s->m[0][1] + _f->m[3][1] * _s->m[1][1] + _f->m[3][2] * _s->m[2][1] + _f->m[3][3] * _s->m[3][1];
  _mat->m[3][2] = _f->m[3][0] * _s->m[0][2] + _f->m[3][1] * _s->m[1][2] + _f->m[3][2] * _s->m[2][2] + _f->m[3][3] * _s->m[3][2];
  _mat->m[3][3] = _f->m[3][0] * _s->m[0][3] + _f->m[3][1] * _s->m[1][3] + _f->m[3][2] * _s->m[2][3] + _f->m[3][3] * _s->m[3][3];
}
