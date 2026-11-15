#include "include_asm.h"
#include "names.h"

extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002B9180(void *);
extern int func_L00_0031C998(int, int, float);
extern int func_00282978(short *);
extern int D_001A8F00[] __attribute__((sda));
#define FI(p,o) (*(int *)((char *)(p)+(o)))
#define FF(p,o) (*(float *)((char *)(p)+(o)))
#define FS(p,o) (*(short *)((char *)(p)+(o)))
#define FB(p,o) (*(unsigned char *)((char *)(p)+(o)))

/* Damps motion, updates an optional parent-relative position, and tweens the
 * particle's size and color over its remaining lifetime. */
/* Slows a particle down, keeps it following its parent object, and fades its size and color over its life. It removes the particle when the parent is gone or time runs out. */
void func_L00_0033C238(char *p)
{
    float v[3], local[3], world[3];
    char *q = p + 32;
    char *desc = *(char **)(q + 28);

    FF(p, 12) = IntToFloat(FS(desc, 8) * (FI(desc, 12) - FS(p, 10)) /
                             FI(desc, 12) + FS(desc, 10)) * 1000.0f;
    v[0] = FF(p, 32);
    v[1] = FF(q, 4);
    v[2] = FF(q, 8);
    FastVecScale(v, v, 0.98f);
    FF(p, 32) = v[0];
    FF(q, 4) = v[1];
    FF(q, 8) = v[2];
    if (!D_001A8F00[0]) {
        char *parent = *(char **)(q + 12);

        if (!parent)
            goto kill_parent;
        if (FB(parent, 32) == 254)
            goto kill_parent;
        if (FB(parent, 32) != 253) {
            local[0] = FF(q, 16);
            local[1] = FF(q, 20);
            local[2] = FF(q, 24);
            FastVecAdd(local, local, v);
            FF(q, 16) = local[0];
            FF(q, 20) = local[1];
            FF(q, 24) = local[2];
            matrix_mul_vec3(world, local, *(char **)(q + 12) + 192);
            FastVecAdd(p + 16, *(char **)(q + 12) + 16, world);
        } else {
kill_parent:
            KillParticle(p);
            return;
        }
    } else {
        FastVecAdd(p + 16, p + 16, v);
    }
    FB(p, 8)++;
    FI(p, 4) = LerpIntegerFraction(FI(desc, 4), FI(desc, 0),
                                (float)FS(p, 10) / IntToFloat(FI(desc, 12)));
    if (FastDecTimer((short *)(p + 10)))
        KillParticle(p);
}
