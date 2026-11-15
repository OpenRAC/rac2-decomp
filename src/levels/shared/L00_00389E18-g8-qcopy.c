#include "common.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef int TI128 __attribute__((mode(TI)));

extern float ref_L00_00389E18_00 __attribute__((sda));
extern void FastVecAdd(void *a, void *b, void *c);
extern void vec_add_object_direction_scaled(void *a, void *b, float c);
extern int CollLine(void *a, void *b, int c, void *d, int e);

/* The level's copy of func_00304AD0: same body, the $gp word is the level's. */
/* Moves the projectile forward and checks if it hit something; if so it switches to its hit state. */
void projectile_l00_move_check_hit_2(void *moby)
{
    void *owner = moby;
    void *target = (char *)owner + 0x10;
    void *source = *(void **)((char *)owner + 0x68);
    TI128 local;

    *(TI128 *)&local = *(TI128 *)target;
    FastVecAdd(target, target, source);
    vec_add_object_direction_scaled(target, source, ref_L00_00389E18_00 * 2.7777778e-05f);
    if (CollLine(&local, target, 0x10, owner, 0) != 0)
        *(unsigned char *)((char *)owner + 0x20) = 8;
}
