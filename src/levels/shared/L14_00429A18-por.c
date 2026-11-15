#include "names.h"
/* func_L14_00429A18: the func_L07_003E7240 launch burst without the flag and timer reset
 * (state block at +0x300). func_0032C700 returns a pointer: with a void prototype the
 * constant 1 for the stack argument is scheduled ahead of the 20.0f. */
#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void group_destroy_attached_parts(char *, char *);

extern void SetDeathBits(char *, int, int);

extern void matrix_mul_vec3(TI128 *, TI128 *, char *);

extern void FastVecAdd(TI128 *, TI128 *, char *);

extern unsigned char *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int,
                                    int, int, void *);

extern void PlayMobySound(int, int, char *);

extern void vec_scale_to_length(TI128 *, TI128 *, float);

extern void part_spawn_masked_debris(char *, int, TI128 *, float, float, float, float, int);


/* Fires a burst of effects and a sound from the object. */
void part_fire_burst_sound(char *arg)
{
    char *o;
    TI128 v[1];
    TI128 w;

    o = *(char **)(arg + 0x68);
    group_destroy_attached_parts(arg, o + 0x300);
    SetDeathBits(arg, 0, 3);
    v[0] = 0;
    ((float *)v)[2] = 0.75f;
    matrix_mul_vec3(v, v, arg + 0xC0);
    FastVecAdd(v, v, arg + 0x10);
    SpawnExplosion(v, 0, 25, 20, 20, 20, 45, 1, 0.6f, 20.0f, 1, 0, 0, 0);
    PlayMobySound(6, 0, arg);
    vec_scale_to_length(&w, o + 0x1C0, 0.05000000447034836f);
    part_spawn_masked_debris(arg, 1016, &w, 3.0f, 6.0f, 3.0f, 6.0f, 255);
}
