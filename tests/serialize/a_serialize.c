#include "a_serialize.h"

// serialize
sfunc_begin(a,)
sattr(f, int32)
sattr(s, int8)
sattrstruct(t, b,)
sfunc_end

sfunc_begin(b,)
sattr(f, int32)
sattr(s, int64)
sfunc_end

// deserialize
dsfunc_begin(a,)
dsattr(f, int32)
dsattr(s, int8)
dsattrstruct(t, b,)
dsfunc_end

dsfunc_begin(b,)
dsattr(f, int32)
dsattr(s, int64)
dsfunc_end
