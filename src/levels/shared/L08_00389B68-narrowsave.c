#include "names.h"
/* func_L08_00389B68: variadic, built with -mastra-quad-saves and -frac2-narrow-saves-below.
   register_precision keeps $ra's save at 64 bits; the narrower save takes the lower slot.
   The packet pointer is reloaded at every store in retail: it is a struct member, and this
   cc1 lets a store through a pointer alias a global only when that global is not a plain
   scalar (alias.c, fixed_scalar_and_varying_struct_p), so no volatile is needed. */
#include "common.h"
typedef struct { u32 *cur; } PacketCursor;
extern PacketCursor ref_L08_00389B68_00 __attribute__((sda));
extern u32 *ref_L08_00389B68_01 MACRO_ADDR;
extern void mem_copy_aligned(void *, void *, int);
void gfx_append_vectors_to_packet(int count, ...) __attribute__((register_precision(ra, 64)));
/* Adds a block of vector values passed as arguments to the graphics packet and moves the packet write position on. */
void gfx_append_vectors_to_packet(int count, ...) {
    if (count) {
        ref_L08_00389B68_00.cur[0] = (count + 1) | 0x10000000;
        ref_L08_00389B68_00.cur[1] = 0;
        ref_L08_00389B68_00.cur[2] = 0;
        ref_L08_00389B68_00.cur[3] = (count + 1) | 0x50000000;
        ref_L08_00389B68_00.cur[4] = count + 0x8000;
        ref_L08_00389B68_00.cur[5] = 0x10000000;
        ref_L08_00389B68_00.cur[6] = 14;
        ref_L08_00389B68_00.cur[7] = 0;
        ref_L08_00389B68_01 = (u32 *)(ref_L08_00389B68_00.cur + 8);
        mem_copy_aligned(ref_L08_00389B68_01, (char *)__builtin_next_arg(count) - 0x38, count * 16);
        ref_L08_00389B68_00.cur = (u32 *)((char *)ref_L08_00389B68_00.cur + count * 16);
    }
}
