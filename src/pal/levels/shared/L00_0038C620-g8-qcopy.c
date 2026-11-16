#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float g_projectile_speed __attribute__((sda));
extern void FastVecAdd(void *a, void *b, void *c);
extern void vec_add_object_direction_scaled(void *a, void *b, float c);
extern int CollLine(void *a, void *b, int c, void *d, int e);

/* Copies the owner's position, asks the vector unit whether it is inside the
   field, and marks the object when it is. */
void projectile_l00_move_check_hit_2_pal(void *obj)
{
    void *owner = obj;
    void *target = (char *)owner + 0x10;
    void *source = *(void **)((char *)owner + 0x68);
    TI128 local;

    *(TI128 *)&local = *(TI128 *)target;
    FastVecAdd(target, target, source);
    vec_add_object_direction_scaled(target, source, g_projectile_speed * 4.0000003e-05f);
    if (CollLine(&local, target, 0x10, owner, 0) != 0)
        *(unsigned char *)((char *)owner + 0x20) = 8;
}
