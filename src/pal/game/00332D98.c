#include "include_asm.h"


#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern f32 func_002A78D8(f32 low, f32 high);
extern f32 D_001A8BD0[] __attribute__((sda));
typedef union { TI128 quad; float v[4]; } EffectVector;
extern unsigned char *D_001F2540[];
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);
extern unsigned char *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void func_00282CC0(void *, void *, void *);
typedef int L_34730TI __attribute__((mode(TI)));
extern L_34730TI func_00334710(int, L_34730TI *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
typedef int TI __attribute__((mode(TI)));
extern TI func_00334710(int, TI *);
extern void func_00282CC0(void *, void *, void *);

/* func_003304D8 is defined in 0032EB28-ground-g8.c. */


/* func_00330BC0 uses small data in 0032EB28-g8.c. */

/* func_00330CA0 is in 0032EB28-damage-g8.c. */


/* func_00330E48 is in 0032EB28-g8.c. */

/* func_00330EC0 is in 0032EB28-ring-g8.c. */

/* func_00331238 is in 0032EB28-spark.c. */


void func_PAL_00332F40(TI128 *a0, void *dir)
{
    EffectVector base;
    float vel[4];
    float pos[3];
    float size = 84000.0f;
    int i;
    int rnd;
    unsigned char *p;

    qcopy(&base, a0);
    func_00282D30(vel, dir, 0.5f);
    func_00282CC0(&base, &base, vel);
    i = 8;
    do {
        i--;
        pos[0] = base.v[0] + func_002A78D8(0.0f, 0.1f);
        pos[1] = base.v[1] + func_002A78D8(0.0f, 0.1f);
        pos[2] = base.v[2] + func_002A78D8(0.0f, 0.1f);
        rnd = func_002A77E0(0xFF);
        p = func_002C65A0(pos, D_001A8BD0, 8, 0x407FFF, rnd, 0x7F, 0, size, size, 0.0f, 1);
        if (p != 0)
            p[2] = D_001F2540[92][5];
        p = func_002C65A0(pos, D_001A8BD0, 8, 0x406080, rnd, 0x7F, 0, size, size, 0.0f, 1);
        if (p != 0)
            p[2] = D_001F2540[53][0];
    } while (i >= 0);
}


extern s32 func_00283D38(s32, s32, f32);
extern s32 func_00283CF0(f32 value);
extern u8 *func_PAL_002C23B8(f32 *pos, f32 *sym, s32 a2, s32 a3, u32 color, s32 alpha, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
extern u8 *D_001F26B0;

void func_PAL_003330E0(f32 *pos, f32 scale)
{
    f32 v[3];
    f32 size = scale * 6300.0f;
    u8 *effect;
    s32 i;
    for (i = 1; i >= 0; i--) {
    v[0] = pos[0] + func_002A78D8(0.0f, 0.04f);
    v[1] = pos[1] + func_002A78D8(0.0f, 0.04f);
    v[2] = pos[2] + func_002A78D8(0.0f, 0.04f);
    func_PAL_002C23B8(v, D_001A8BD0, 12, 0x5F, 0x7F7F7F, func_00283CF0(func_002A78D8(1.0f, 3.0f)), size, 500.0f, 1.0f, 0.0f, 0.0f);
    }
    effect = func_PAL_002C23B8(v, D_001A8BD0, 12, 0x7F, 0x407FFF, func_00283CF0(func_002A78D8(1.0f, -1.0f)), size * 0.8f, 500.0f, 1.0f, 0.0f, 0.0f);
    if (effect != 0) {
        effect[2] = D_001F26B0[5];
    }
}

