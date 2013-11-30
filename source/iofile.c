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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "iofile.h"

char* file_rdbuf(FILE* _file) {
  size_t newLen;
  char* buf;
  if(_file != NULL) {
    /* Go to the end of the file. */
    if(fseek(_file, 0L, SEEK_END) == 0) {
      /* Get the size of the file. */
      long bufsize = ftell(_file);
      if(bufsize == -1) {
        /* Error */
	printf("error\n");
      }

      /* Allocate our buffer to that size. */
      buf = malloc(sizeof(char) * (bufsize + 1));

      /* Go back to the start of the file. */
      if(fseek(_file, 0L, SEEK_SET) != 0) {
        /* Error */
	printf("error\n");
      }

      /* Read the entire file into memory. */
      newLen = fread(buf, sizeof(char), bufsize, _file);
      if(newLen == 0) {
        fputs("Error reading file", stderr);
      }
      else {
        buf[++newLen] = '\0'; /* Just to be safe. */
      }
    }
  }
  
  return buf;
}

char* file_rdbufp(char* _path) {
  FILE* f;
  char* buf;
  f = fopen(_path, "r");
  if(f != 0) {
    buf = file_rdbuf(f);
//     fclose(f);
  } else {
    //error();
    printf("file read error: %s\n     %i", _path, errno);
  }

  return buf;
}
