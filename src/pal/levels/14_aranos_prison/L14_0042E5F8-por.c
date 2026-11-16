#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void group_destroy_attached_parts(char *, char *);
extern void SetDeathBits_pal(char *, int, int);
extern void matrix_mul_vec3(TI128 *, TI128 *, char *);
extern void FastVecAdd(TI128 *, TI128 *, char *);
extern unsigned char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int,
                                    int, int, void *);
extern int PlayMobySound(int, int, char *);
extern void vec_scale_to_length(TI128 *, TI128 *, float);
extern void func_PAL_002B15D8(char *, int, TI128 *, float, float, float, float, int);

void func_PAL_L14_0042F200(char *arg)
{
    char *o;
    TI128 v[1];
    TI128 w;

    o = *(char **)(arg + 0x68);
    group_destroy_attached_parts(arg, o + 0x300);
    SetDeathBits_pal(arg, 0, 3);
    v[0] = 0;
    ((float *)v)[2] = 0.75f;
    matrix_mul_vec3(v, v, arg + 0xC0);
    FastVecAdd(v, v, arg + 0x10);
    SpawnExplosion_pal(v, 0, 25, 20, 20, 20, 45, 1, 0.6f, 20.0f, 1, 0, 0, 0);
    PlayMobySound(6, 0, arg);
    vec_scale_to_length(&w, o + 0x1C0, 0.060000002f);
    func_PAL_002B15D8(arg, 1016, &w, 3.0f, 6.0f, 3.0f, 6.0f, 255);
}
