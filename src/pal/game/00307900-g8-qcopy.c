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
void func_PAL_00308540(void *obj)
{
    void *s2 = obj;
    void *s0 = (char *)s2 + 0x10;
    void *s1 = *(void **)((char *)s2 + 0x68);
    TI128 local;

    *(TI128 *)&local = *(TI128 *)s0;
    FastVecAdd(s0, s0, s1);
    vec_add_object_direction_scaled(s0, s1, g_object_direction_scale * 4.0000003e-05f);
    if (CollLine(&local, s0, 0x10, s2, 0) != 0)
        *(unsigned char *)((char *)s2 + 0x20) = 8;
}


