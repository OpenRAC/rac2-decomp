#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float g_projectile_speed __attribute__((sda));
extern void FastVecAdd(void *a, void *b, void *c);
extern void vec_add_object_direction_scaled(void *a, void *b, float c);
extern int CollLine(void *a, void *b, int c, void *d, int e);

extern float g_object_direction_scale __attribute__((sda));

/* Copies the owner's position, asks the vector unit whether it is inside the
   field, and marks the object when it is. */
void megaturret_update_fall_pal(void *obj)
{
    void *moby = obj;
    void *position = (char *)moby + 0x10;
    void *vars = *(void **)((char *)moby + 0x68);
    TI128 local;

    *(TI128 *)&local = *(TI128 *)position;
    FastVecAdd(position, position, vars);
    vec_add_object_direction_scaled(position, vars, g_object_direction_scale * 4.0000003e-05f);
    if (CollLine(&local, position, 0x10, moby, 0) != 0)
        *(unsigned char *)((char *)moby + 0x20) = 8;
}


