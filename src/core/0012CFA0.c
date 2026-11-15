#include "common.h"
#include "structs.h"

extern void mpeg_skip_bits(void *, int);

extern int mpeg_read_bits(void *, int);

extern void mpeg_skip_extra_info_bits(void *);

/* rac1-decomp src/core/00125630.c: func_00129180 */
/* Skips extra information bytes, each one marked by a leading 1 bit. */
void mpeg_skip_extra_info_bits(void *decoderPtr) {
    while (mpeg_read_bits(decoderPtr, 1) != 0) {
        mpeg_skip_bits(decoderPtr, 8);
    }
}
