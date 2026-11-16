#include "include_asm.h"
#include "names.h"

typedef int Copy128 __attribute__((mode(TI)));
typedef union { Copy128 q; float f[4]; } Vector16;
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char g_hero_position[];
extern void SetDeathBits_pal(char *, int, int);
extern int PlayMobySound(int, int,char*);
extern void matrix_mul_vec3(void *, void *, void *);
extern void part_spawn_explosion_with_sparks_pal(char *, void *, int,float, float);
extern void func_PAL_002B15D8(char *, int, float *,unsigned char,float, float,float, float);
extern void moby_mark_spawned(void *);

void dobbo_destroy_with_debris_pal(char *object)
{
    Vector16 position, offset, impulse;
    char *origin = object + 0x10;
    float zero;
    SetDeathBits_pal(object, 0, 3);
    zero = 0.0f;
    PlayMobySound(1, 0, object);
    offset.q = 0;
    offset.f[2] = 0.75f;
    matrix_mul_vec3(&position, &offset, object + 0xC0);
    FastVecAdd(&position, &position, origin);
    part_spawn_explosion_with_sparks_pal(object, &position, -1, 0.333f, zero);
    FastVecSub(&impulse, origin, g_hero_position);
    impulse.f[2] = zero;
    vec_scale_to_length(&impulse, &impulse, 0.120000005f);
    func_PAL_002B15D8(object, 0x1F, impulse.f, 255, 3.0f, 6.0f, 3.0f, 6.0f);
    moby_mark_spawned(object);
}
