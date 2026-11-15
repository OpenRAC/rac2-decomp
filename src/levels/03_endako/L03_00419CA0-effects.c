#include "common.h"

typedef int Quad __attribute__((mode(TI)));
extern void func_00282F20(void *, void *, float);
extern void *func_L00_0033E220(void *, void *, u32, int, int, int, int, int, float, float);
extern void func_002A7750(void *, int, int);
extern void *func_002A9640(void *, u32, int);
extern void func_L00_0032A258(void *, float *, float *, float *, int, int, int, int, int, u8, void *);
extern void func_L00_00326110(void *, int, float);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void *func_0032C700(void *, float, int, int, int, int, int, int, int, int, int, int, int, float);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, int, int, int, int, int, int, float, float, float);
extern void func_00283098(void *, void *, void *);
extern void func_L00_003263D0(float, void *, void *, int, int, void *, u32, int, float, float, float);
extern void func_0029F338(void *);

/* At -G0, the assembler emits GP accesses in delay slots and absolute
 * accesses elsewhere for this counter. The settings below use explicit GP views. */
extern int D_L03_001AEBF8 __attribute__((sda));

extern int D_L03_001B1AD0 SDATA(D_L03_001B1AD0) __attribute__((sda));
extern float D_L03_001B1AB0[2] SDATA(D_L03_001B1AB0) __attribute__((sda));
extern float D_L03_001B1AA8[2] SDATA(D_L03_001B1AA8) __attribute__((sda));
extern float D_L03_001B1AA0[2] SDATA(D_L03_001B1AA0) __attribute__((sda));

/* Waits for a hit, then blows up with sparks and flying bits. */
void func_L03_00419CA0(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float a[4] __attribute__((aligned(16)));
    Quad zero = 0;
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    int i;
    switch (moby[0x20]) {
    case 0:
        vec_scale_to_length(a, moby+0xE0, *(float *)(moby+0x2C)*20.0f);
        SpawnObjectFollowingEffect(a, moby, 0x28208080, -1, 0, -1, 0, 0x60, 367500.0f, 0.0f);
        SpawnObjectFollowingEffect(a, moby, 0x20208080, -1, 1, -1, 0, 0x60, 325500.0f, 0.75f);
        if (*(int *)vars)
            --D_L03_001AEBF8;
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (FindOwnedEffectSlot(moby, 0x4010000, 0) && !*(int *)vars) {
            --D_L03_001AEBF8;
            SetMobyState(moby, 2, -1);
        }
        moby[0xA8] = 255;
        break;
    case 2:
        ExplodeObjectIntoPieces(moby, D_L03_001B1AB0, D_L03_001B1AA8, D_L03_001B1AA0, 127, 0, D_L03_001B1AD0, 1, 65535, 255, 0);
        SpawnScaledBolts(moby, 1, 3.0f);
        *(Quad *)b = zero;
        ComputeMobyLocalPoint(moby, a, 0, 0, *(float *)(moby+0x2C)*20.0f);
        SpawnExplosion(a, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 20.0f);
        SpawnExplosionEffects(moby, b, a, 0.0f, 0.0f, 15, 0, 0, 0.0f, 0.0f, -1, 0, 0, -1, 0, 0x810001, 9.0f, 1.0f, 0.0f);
        ComputeMobyLocalPoint(moby, c, 0, 0, *(float *)(moby+0x2C)*20.0f);
        for (i = 0; i < 4; i++) {
            float d[4] __attribute__((aligned(16)));
            d[0] = (i / 2 * 2 - 1) * 0.033333335f;
            d[1] = (i % 2 * 2 - 1) * 0.033333335f;
            d[2] = 0.06666667f;
            matrix_mul_vec3(d, d, moby+0xC0);
            SpawnTintedEffects(0.25f, moby, c, 6, 1, d, 0x50404040, 0, 5, 0.75f, 1.25f);
        }
        if (D_L03_001B1AD0 >= 0) {
            *(u16 *)(moby+0x7C)=(1<<D_L03_001B1AD0)|0x8000;
            SetMobyState(moby, 3, -1);
        } else {
            MarkMobySpawned(moby);
        }
        break;
    }
}
