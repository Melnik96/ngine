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

#include <malloc.h>
#include <memory.h>

#include "array.h"

void array_init(struct array *array) {
    memset(array, 0, sizeof *array);
}

void array_release(struct array *array) {
    free(array->data);
}

void* array_add(struct array *array, size_t size) {
    int alloc;
    void *data, *p;

    if (array->alloc > 0)
        alloc = array->alloc;
    else
        alloc = 16;

    while (alloc < array->size + size)
        alloc *= 2;

    if (array->alloc < alloc) {
        if (array->alloc > 0)
            data = realloc(array->data, alloc);
        else
            data = malloc(alloc);

        if (data == NULL)
            return 0;
        array->data = data;
        array->alloc = alloc;
    }

    p = array->data + array->size;
    array->size += size;

    return p;
}//TODO mempool, ? ??????? ? OGRE nedmalloc

void array_copy(struct array *array, struct array *source) {
    array->size = 0;
    array_add(array, source->size);
    memcpy(array->data, source->data, source->size);
}
