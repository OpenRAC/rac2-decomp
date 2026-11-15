#include "include_asm.h"
#include "names.h"
typedef int Copy128 __attribute__((mode(TI)));
typedef union { Copy128 q; float f[4]; } Vector16;

extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char g_hero_position[];
extern void SetDeathBits(char *, int, int);
extern int PlayMobySound(int, int,char*);
extern void matrix_mul_vec3(void *, void *, void *);
extern unsigned char *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void part_spawn_masked_debris(char *, int, float *, unsigned char, float, float, float, float);
extern void moby_mark_spawned(void *);

/* The func_L09_004050E0 burst with a particle spray (func_0032C700) in place of the
   area hit, offset 1.0 up. func_0032C700 returns a pointer; a void prototype puts the
   stack constant 1 ahead of the 20.0f. */
/* Blows the object up: sprays particles, pushes the hero away, then removes the object. */
void moby_l06_explode_and_remove(char *object)
{
    Vector16 position, offset, impulse;
    char *origin = object + 0x10;
    SetDeathBits(object, 0, 3);
    PlayMobySound(1, 0, object);
    offset.q = 0;
    offset.f[2] = 1.0f;
    matrix_mul_vec3(&position, &offset, object + 0xC0);
    FastVecAdd(&position, &position, origin);
    SpawnExplosion(origin, 0, 0, 0, 0, 10, 20, 0, 0.333f, 20.0f, 1, 0, 0, 0);
    FastVecSub(&impulse, origin, g_hero_position);
    impulse.f[2] = 0.0f;
    vec_scale_to_length(&impulse, &impulse, 0.10000001f);
    part_spawn_masked_debris(object, 0x1F, impulse.f, 255, 3.0f, 6.0f, 3.0f, 6.0f);
    moby_mark_spawned(object);
}
