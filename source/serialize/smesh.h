#include "serialize.h"
#include "mesh.h"

sfunc(mesh,)
  sint16(num_indices)
  sint32(num_vertices)
funcs

dsfunc(mesh,)
  dschar_ptr(str)
  dsint32(len)
  dsdata->alloc = dsdata->len;
funcds
