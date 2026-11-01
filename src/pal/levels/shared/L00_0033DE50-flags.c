#include "include_asm.h"

typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef float f32;
typedef int V4_L00_0033BA68 __attribute__((mode(TI)));
typedef struct {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    u32 w4;
    u8 b8;
    u8 b9;
    u16 s_a;
    f32 f_c;
    V4_L00_0033BA68 v10;
} Obj_L00_0033BA68;
extern void *func_002B9030(s32 kind);
extern s32 func_00283CF0(f32 value);
extern int *ref_L00_0033BA68_00;

/* Allocates the 0x46 record, copies the caller's sixteen-byte block into it and
   fills its flag bytes, its tag word and its two level-derived fields. */
Obj_L00_0033BA68 *func_PAL_L00_0033DE50(char *src1, int index, f32 value)
{
    Obj_L00_0033BA68 *o = (Obj_L00_0033BA68 *)func_002B9030(0x46);

    if (o != 0) {
        o->v10 = *(V4_L00_0033BA68 *)src1;
        o->w4 = 0x5A404040;
        o->b9 = func_00283CF0(1.0f) + 0x20;
        o->b3 = 0x44;
        o->b1 = 1;
        o->b2 = *((unsigned char *)ref_L00_0033BA68_00 + index);
        o->b8 = func_00283CF0(value * 40.7436637878418f) - 0x20;
        o->f_c = 105000.0f;
        o->s_a = 0x64;
    }
    return o;
}
