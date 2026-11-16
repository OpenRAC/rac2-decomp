#include "include_asm.h"

#include "common.h"
typedef int Quad_3fca40 __attribute__((mode(TI)));
extern void *CreateMoby(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
extern int g_large_spark_trail_lifetime __attribute__((sda));
extern void ref_L00_003FCA40_00(void *);
extern void ref_L00_003FCA40_01(void *, void *);
extern void ref_L00_003FCA40_02(void);

/* The allocator hands out a 0xD9C-byte object; the object is set up (flag halfword, three
   header bytes), the second argument's vector is copied into it, the object is normalised
   twice and added to the first argument, and the level's own copy of func_L00_003FD178 runs
   on it. */
char *large_spark_trail_create_pal(char *origin, char *direction, Quad_3fca40 *position, int owner)
{
    Quad_3fca40 offset;
    char *object;
    char *object_pos;
    int *vars;
    char *velocity;
    int lifetime;
    float lifetime_f;

    object = (char *)CreateMoby(0xD9C);
    if (object != 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        vars = *(int **)(object + 0x68);
        *(unsigned short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x31) = 1;
        *(unsigned short *)(object + 0x34) |= 0x41;
        *(unsigned char *)(object + 0x20) = 0;
        velocity = (char *)vars + 0x20;
        object_pos = object + 0x10;
        vec_scale_to_length(velocity, direction, 0.40000004f);
        *(Quad_3fca40 *)object_pos = *position;
        vec_scale_to_length(&offset, velocity, -0.25f);
        FastVecAdd((char *)vars + 0x50, origin, &offset);
        lifetime = (int)((s32)(g_large_spark_trail_lifetime) * 5 + 2) / 6;
        *(int *)((char *)vars + 0x38) = lifetime;
        lifetime_f = IntToFloat(lifetime);
        *(int *)((char *)vars + 0x34) = owner;
        *(float *)((char *)vars + 0x3C) = 1.0f / lifetime_f;
        ref_L00_003FCA40_00(object_pos);
        ref_L00_003FCA40_01(ref_L00_003FCA40_02, object);
    }
    return object;
}
