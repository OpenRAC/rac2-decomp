#include "include_asm.h"
#include "names.h"

/* func_L00_00387370 is a unit of its own: the 16-byte block the level copies out of
   the object needs the opt-in grouped quadword-copy profile (-frac2-qcopy
   -frac2-qcopy-barrier, config/cflags.txt), which gives retail's grouped
   `lq $v0,0($s0) ; sq $v0,0($sp)` with the copy held before the call's argument
   moves, and the -G8 profile the level's small-data float is read through. */

typedef int L00_00387370_TI128 __attribute__((mode(TI)));

extern void FastVecAdd(void *out, void *target, void *source);
extern void vec_add_object_direction_scaled(void *target, void *source, float value);
extern int CollLine(void *out, void *target, int size, void *owner, int mode);

extern float g_projectile_hit_push_scale __attribute__((sda));

/* Copies the object's 16-byte block into the local copy, hands it to the shared
   test and, when the test accepts it, marks the object. */
void projectile_l00_move_check_hit(void *owner)
{
    char *target = (char *)owner + 0x10;
    char *source = *(char **)((char *)owner + 0x68);
    char local[16];

    *(L00_00387370_TI128 *)local = *(L00_00387370_TI128 *)target;
    FastVecAdd(target, target, source);
    vec_add_object_direction_scaled(target, source, g_projectile_hit_push_scale * 2.7777778086601757e-05f);
    if (CollLine(local, target, 0x10, owner, 0) != 0)
        *((unsigned char *)owner + 0x20) = 8;
}
