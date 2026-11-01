#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float v[4]; } EffectVector;
typedef struct Gf2540 {
    char pad0[0xD4];
    unsigned char *fD4;
    char pad1[0x16C - 0xD8];
    unsigned char *f16C;
} Gf2540;
typedef struct Gparticle {
    char pad0[2];
    unsigned char f2;
} Gparticle;
extern Gf2540 D_001F2540;
extern char D_001A8BD0[] __attribute__((sda));
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern Gparticle *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);

/* The size is set once ahead of the loop, so gcse's constant propagation writes it directly
 * into both calls and it is not hoisted into a callee-saved register. */
void func_PAL_00332D98(TI128 *a0, void *velocity)
{
    EffectVector base;
    float vel[3];
    float pos[3];
    int i;
    int rnd;
    Gparticle *p;
    float size = 35700.0f;

    qcopy(&base, a0);
    func_00282D30(vel, velocity, 0.5f);
    func_00282CC0(&base, &base, vel);
    i = 8;
    do {
        i--;
        pos[0] = base.v[0] + func_002A78D8(0.005f, 0.035f);
        pos[1] = base.v[1] + func_002A78D8(0.005f, 0.035f);
        pos[2] = base.v[2] + func_002A78D8(0.005f, 0.035f);
        rnd = func_002A77E0(0xFF);
        p = func_002C65A0(pos, D_001A8BD0, 3, 0x808080, rnd, 0x7F, 0x3F, size, size, 0.0f, 1);
        if (p != 0)
            p->f2 = D_001F2540.f16C[1];
        p = func_002C65A0(pos, D_001A8BD0, 3, 0x406080, rnd, 0x10, 8, size, size, 0.0f, 1);
        if (p != 0)
            p->f2 = *D_001F2540.fD4;
    } while (i >= 0);
}
