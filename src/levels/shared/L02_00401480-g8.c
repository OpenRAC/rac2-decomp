/* Builds a 16-byte record (zero with two floats set), walks it through two helpers, then picks one of two
   scalars read through $gp by the owner's id and hands both to the level 0 stepping helper. Same shape as
   func_L00_003CA688. Needs -frac2-zero-ti-por and -G8. */
#include "include_asm.h"
#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Quad_401480;

extern int ref_L02_00401480_00 __attribute__((sda));
extern int ref_L02_00401480_01 __attribute__((sda));
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_002EC608(void *, int);
extern void func_L00_002EC970(void *, char *, int, int, float, float);

/* Starts a trailing effect just behind the object, using one of two settings depending on the kind of object. */
void func_L02_00401480(char *owner)
{
    Quad_401480 local;
    char *inner;
    int v;

    local.q = 0;
    local.f[0] = -0.3f;
    local.f[3] = 1.0f;
    inner = *(char **)(owner + 0x68);
    matrix_mul_vec3(&local, &local, owner + 0xC0);
    FastVecAdd(&local, &local, owner + 0x10);
    if (*(short *)(owner + 0xAA) == 0xB5A /* moby class 2906 */)
        v = ref_L02_00401480_00;
    else
        v = ref_L02_00401480_01;
    DrawGlowQuad_L00(&local, v);
    DrawTaperedBeam(&local, inner + 0x20, v, 4, *(float *)(inner + 0x60), 0.25f);
}
