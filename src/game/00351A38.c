#include "include_asm.h"
#include "names.h"

extern int func_00351938(unsigned char *);
extern int func_0012F9B8(void *);
int func_00351A38(void *a0) { int result = 0; if (!VideoDecGetQueuedBytes(a0)) result = HasMpegNoPicturesDecoded(a0) != 0; return result; }
