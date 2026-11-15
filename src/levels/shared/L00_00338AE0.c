/* func_L00_00338AE0 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections). */
#include "common.h"

typedef int V4 __attribute__((mode(TI)));

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
    V4 v10;
    V4 v20;
    f32 f30;
    f32 f34;
    s32 i38;
} Obj_L00_00338AE0;

/* Known payload fields beginning with the second full vector. */
typedef struct { V4 vector; f32 random, rate; s32 id; } EffectPayload;

extern void *func_002B9030(s32 kind);
extern s32 func_002A77E0(s32 limit);
extern s32 func_00283CF0(f32 value);
extern f32 func_002A7878(f32 a, f32 b);
extern unsigned char *ref_L00_00338AE0_00;

Obj_L00_00338AE0 *func_L00_00338AE0(char *src1, char *src2, s32 a2, f32 value, f32 value2)
{
    Obj_L00_00338AE0 *o = (Obj_L00_00338AE0 *)func_002B9030(0x2E);
    f32 r;
    u8 tag;
    EffectPayload *payload;

    if (o != 0) {
        qcopy(&o->v10, src1);
        payload = (EffectPayload *)&o->v20;
        o->w4 = ((func_002A77E0(10) + 0x26) << 24) | 0x00808080;
        o->b9 = FloatToInt(1.0f) + 0x20;
        o->b3 = 0x48;
        o->b1 = 1;
        tag = *ref_L00_00338AE0_00;
        o->s_a = 5;
        o->b2 = tag;
        o->f_c = value * 210000.0f;
        qcopy(&payload->vector, src2);
        r = func_002A7878(0.0f, 256.0f);
        payload->random = r;
        o->b8 = FloatToInt(r);
        payload->rate = value2;
        payload->id = a2;
    }
    return o;
}
