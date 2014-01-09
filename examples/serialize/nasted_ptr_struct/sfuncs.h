#include "serialize.h"
#include "structs.h"

#ifndef __sfuncs_H__
#define __sfuncs_H__

sfunc(b,)
  sint32(f)
  sint32(s)
funcs

dsfunc(b,)
  dsint32(f)
  dsint32(s)
funcds

sfunc(a,)
  sint32(f)
  sint32(s)
  sstruct_ptr(t, b,)
funcs

dsfunc(a,)
  dsint32(f)
  dsint32(s)
  dsstruct_ptr(t, b,)
funcds

#endif
