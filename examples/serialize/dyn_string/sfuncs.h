#include "serialize.h"
#include "dynstr.h"

// struct string
sfunc(string,)
  svoid_ptr(str, s->len)
  sint32(len)
funcs

dsfunc(string,)
  dschar_ptr(str)
  dsint32(len)
  dsdata->alloc = dsdata->len;
funcds
