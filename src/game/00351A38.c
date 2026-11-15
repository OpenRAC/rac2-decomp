#include "include_asm.h"
#include "names.h"

extern int mpeg_dec_get_queued_bytes(unsigned char *);
extern int mpeg_has_no_pictures_decoded(void *);
int func_00351A38(void *a0) { int result = 0; if (!mpeg_dec_get_queued_bytes(a0)) result = mpeg_has_no_pictures_decoded(a0) != 0; return result; }
