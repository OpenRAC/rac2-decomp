#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef float f32;

/* The record's two sixteen-byte blocks: the quadword copy profile (-frac2-qcopy)
   keeps both addresses in registers, as the retail does. */
typedef int V4_L00_00338D28 __attribute__((mode(TI)));

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
    V4_L00_00338D28 v10;
    V4_L00_00338D28 v20;
} Obj_L00_00338D28;

extern void *part_alloc(s32 kind);
extern s32 math_random_int_below(s32 limit);
extern s32 FloatToInt(f32 value);

/* The level's pointer to the byte the record carries in its second flag byte: its
   address differs per level, so it is a per-level symbol. */
extern unsigned char *ref_L00_00338D28_00;

/* Allocates the 0x2F record, copies the two sixteen-byte blocks into it, and fills
   its flag bytes, its tag word and its two level-derived fields. */
/* Creates a short-lived visual effect between two points, with a random start color and a random shade. */
Obj_L00_00338D28 *part_spawn_two_point_effect(char *src1, char *src2, f32 value)
{
    Obj_L00_00338D28 *o = (Obj_L00_00338D28 *)part_alloc(0x2F);

    if (o != 0) {
        o->v10 = *(V4_L00_00338D28 *)src1;
        o->w4 = ((math_random_int_below(8) + 0x28) << 24) | 0x00808080;
        o->b9 = FloatToInt(2.0f) + 0x20;
        o->b3 = 0x48;
        o->b1 = 0;
        o->b2 = *ref_L00_00338D28_00;
        o->f_c = value;
        o->v20 = *(V4_L00_00338D28 *)src2;
        o->b8 = math_random_int_below(0x100);
    }
    return o;
}
