/* func_L00_0033E220 in its own unit: its 16-byte copies are lq/sq pairs (-frac2-qcopy -frac2-qcopy-barrier). */
#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef float f32;

typedef int V4_L00_0033E220 __attribute__((mode(TI)));

typedef struct {
    u32 w0;
    u32 w4;
    f32 f8;
    u16 sc;
    u16 se;
} Sub_L00_0033E220;

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
    V4_L00_0033E220 v10;
    Sub_L00_0033E220 sub;
    V4_L00_0033E220 v30;
} Obj_L00_0033E220;

extern void *part_alloc(s32 kind);
extern s32 FloatToInt(f32 value);
/* The vector add takes the record's 0x30 vector as its third argument: retail keeps
   that address in $a2 from the copy above. */
extern void FastVecAdd(void *out, void *a, void *b);
extern s32 math_random_int_below(s32 range);

extern int *ref_L00_0033E220_00;

/* Creates an effect that can follow an object. It sets the position, size and brightness from the object or from the given point. */
Obj_L00_0033E220 *part_spawn_object_following_effect(V4_L00_0033E220 *vec, u8 *obj, u32 flags, s32 a3, s32 index, s32 idx2, s32 sc, s32 range, f32 f12, f32 f13)
{
    Obj_L00_0033E220 *o = (Obj_L00_0033E220 *)part_alloc(0x59);

    if (o != 0) {
        f32 four = 4.0f;
        o->w4 = flags;
        o->b9 = FloatToInt(four) + 0x40;
        o->f_c = f12;
        o->b1 = 0;
        o->b3 = 0x48;
        o->b8 = math_random_int_below(0xFF);
        o->b2 = *((u8 *)ref_L00_0033E220_00 + index);
        o->s_a = idx2;
        o->sub.w0 = (u32)obj;
        {
        Sub_L00_0033E220 *q = &o->sub;
        q->w4 = a3;
        q->f8 = f13;
        q->sc = sc;
        o->v30 = *vec;
        if (index == 0) {
            q->se = 1;
        }
        }
        if (obj != 0) {
            o->v10 = *(V4_L00_0033E220 *)(obj + 0x10);
            FastVecAdd(&o->v10, &o->v10, &o->v30);
            if (range > 0) {
                o->b9 = ((range >> 5) << 4) + FloatToInt(four);
            } else {
                o->b9 = (((s16)*(u16 *)(obj + 0x32) >> 5) << 4) + FloatToInt(four);
            }
        } else {
            o->v10 = *vec;
        }
    }
    return o;
}
