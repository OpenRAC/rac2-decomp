#include "common.h"

typedef int Quad_3fca40 __attribute__((mode(TI)));

/* The allocator, the two vector helpers and the int-to-float helper the retail calls;
   each sits at another address in the other levels, so the level's own copies are named
   here with the address they have in level 00. */
extern void *CreateMoby(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);

extern int D_L00_001B0BB4 __attribute__((sda));

/* The bodies the retail calls reach, at 0x3FD178, 0x2E6EF8 and 0x3FCDB0 in level 00. */
extern void ref_L00_003FCA40_00(void *);
extern void ref_L00_003FCA40_01(void *, void *);
extern void ref_L00_003FCA40_02(void);

/* The allocator hands out a 0xD9C-byte object; the object is set up (flag halfword, three
   header bytes), the second argument's vector is copied into it, the object is normalised
   twice and added to the first argument, and the level's own copy of func_L00_003FD178 runs
   on it. */
/* Creates a short-lived trail object from a start point, direction and position, and returns it. */
char *large_spark_trail_create(char *origin, char *direction, Quad_3fca40 *position, int owner)
{
    Quad_3fca40 local;
    char *object;
    char *position_ptr;
    int *vars;
    char *velocity;
    int lifetime;
    float lifetime_float;

    object = (char *)CreateMoby(0xD9C /* moby class 3484 */);
    if (object != 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        vars = *(int **)(object + 0x68);
        *(unsigned short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x31) = 1;
        *(unsigned short *)(object + 0x34) |= 0x41;
        *(unsigned char *)(object + 0x20) = 0;
        velocity = (char *)vars + 0x20;
        position_ptr = object + 0x10;
        vec_scale_to_length(velocity, direction, 0.33333334f);
        *(Quad_3fca40 *)position_ptr = *position;
        vec_scale_to_length(&local, velocity, -0.25f);
        FastVecAdd((char *)vars + 0x50, origin, &local);
        lifetime = (int)D_L00_001B0BB4;
        *(int *)((char *)vars + 0x38) = lifetime;
        lifetime_float = IntToFloat(lifetime);
        *(int *)((char *)vars + 0x34) = owner;
        *(float *)((char *)vars + 0x3C) = 1.0f / lifetime_float;
        ref_L00_003FCA40_00(position_ptr);
        ref_L00_003FCA40_01(ref_L00_003FCA40_02, object);
    }
    return object;
}
