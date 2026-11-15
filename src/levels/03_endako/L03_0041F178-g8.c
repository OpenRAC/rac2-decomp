#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;

extern int D_L03_001B2548 MACRO_ADDR;
extern Vector D_L03_001B1C10 __attribute__((sda));
extern Vector D_L03_001B1C20 __attribute__((sda));
extern u8 D_L03_001A8F20[] MACRO_ADDR;
extern u8 D_L03_001BFE00[];
extern Vector D_L03_001B0580 MACRO_ADDR;
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A8C00(void *, void *, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern void func_002A8E20(void *, void *);
extern void func_L03_0041F410(u8 *, Vector *, Vector *, int);

/* Traces the entity's beam, applies hit damage and records its endpoints. */
void func_L03_0041F178(u8 *self) {
    Vector from, to;
    u8 hit[0x30];
    u8 *st = *(u8 **)(self + 0x68);
    int enabled;

    if (gFrameCounter_L03 & 1) {
        *(s16 *)(st + 0x334) = (*(s16 *)(st + 0x334) + 1) % 4;
        if (*(s16 *)(st + 0x336) < 3)
            ++*(s16 *)(st + 0x336);
        D_L03_001B1C20.f[0] = *(float *)(st + 0x33C);
        matrix_mul_vec3(&from, &D_L03_001B1C10, self + 0xC0);
        FastVecAdd(&from, &from, self + 0x10);
        enabled = 0;
        matrix_mul_vec3(&to, &D_L03_001B1C20, self + 0xC0);
        FastVecAdd(&to, &to, self + 0x10);
        make_hit_descriptor(hit, self, self[0x95] == 2 ? 0x10001 : 1,
                     D_L03_001A8F20, (float)st[0x34]);
        if (CollLine(&from, &to, 0, self, hit)) {
            u8 *direction = D_L03_001BFE00;
            u8 *ctx = direction - 0x40;
            if (FastMatrixHelperA(vec_length_xy(direction), *(float *)(ctx + 0x48)) > 1.396263599395752f)
                enabled = 1;
            qcopy(&to, direction - 0x20);
            if (*(u8 **)(ctx + 0x18)) {
                u8 *obj = *(u8 **)(ctx + 0x18);
                int type = *(s16 *)(obj + 0xAA);
                if (type < 0x1F4)
                    goto no_damage;
                if (type >= 0x209)
                    goto no_damage;
                {
                    make_hit_descriptor(hit, self, 0x10000, D_L03_001A8F20, (float)st[0x34]);
                    QueueMobyImpact(*(u8 **)(ctx + 0x18), hit);
                }
            }
        }
no_damage:
        if (*(s16 *)(st + 0x336) >= 3)
            EmitLaserBeamParticles(self, &to,
                             (Vector *)((((*(s16 *)(st + 0x334) + 3) % 4) * 32) +
                                        (u32)st + 0x2B0), enabled);
        if (*(int *)(st + 0x298))
            qcopy(&D_L03_001B0580, &to);
        /* The endpoint slots do not overlap the ring index at +0x334. */
        qcopy_nc(st + 0x2A0 + *(s16 *)(st + 0x334) * 32, &from);
        qcopy(st + 0x2B0 + *(s16 *)(st + 0x334) * 32, &to);
    }
}
