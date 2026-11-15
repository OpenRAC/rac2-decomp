#include "common.h"

typedef s32 Quadword __attribute__((mode(__TI__)));
extern void func_L00_0032A258(void *, void *, void *, void *, s32, s32, s32, s32, s32, u8, void *);
extern void func_L00_00324F18(void *, void *, f32, f32, f32);
extern void *func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
extern s32 func_00282948(void *);
extern void func_002A7750(void *, s32, s32);
extern void func_00283098(void *, void *, void *);
extern s32 func_002A7820(s32, s32);
extern void func_L00_002EC248(void *, void *, void *, f32, f32, s32, s32, f32, f32, f32);
/* The complete range record is 32 bytes; this unit uses -G32. */
extern f32 D_L12_001B1FD0[8] SDATA(D_L12_001B1FD0) __attribute__((sda));
extern f32 D_L12_001B1FC8[2] __attribute__((sda));
extern f32 D_L12_001B1FC0[2] __attribute__((sda));
extern s32 D_L12_001B2000 __attribute__((sda));
/* Retail reads Y/Z absolutely and X through GP,  and passes the same vector. */
extern f32 D_L12_001B1FF0[] __attribute__((sda));
extern f32 D_L12_001B1FF0_gp SDATA(D_L12_001B1FF0) __attribute__((sda));

/* Plays a flash and a big burst, then keeps throwing out puffs of sparks for a while before it stops. */
void func_L12_004212C0(u8 *self) {
    s32 *st = *(s32 **)(self + 0x68);
    f32 vec[4];
    switch (self[0x20]) {
    case 0:
        ExplodeObjectIntoPieces(self, D_L12_001B1FD0, D_L12_001B1FC8, D_L12_001B1FC0, 65535, 0, D_L12_001B2000, 0, 65535, 255, 0);
        *(s16 *)(self + 0x7c) = 0;
        LocalOffsetToWorld(self, vec, D_L12_001B1FF0_gp, D_L12_001B1FF0[1], D_L12_001B1FF0[2]);
        SpawnExplosion(vec, 0, 25, 20, 20, 20, 45, 0, 1, 1, 1, 0, *(f32 *)(self + 0x2c)*7.0f, 20.0f);
        st[0] = 20;
        SetMobyState(self, 1, -1);
        break;
    case 1:
        if (FastFloatHelperD(st)) {
            LocalOffsetToWorld(self, vec, D_L12_001B1FF0_gp, D_L12_001B1FF0[1], D_L12_001B1FF0[2]);
            SpawnExplosion(vec, 0, 25, 20, 20, 20, 45, 0, 0, 0, 0, 0, *(f32 *)(self + 0x2c)*3.5f, 20.0f);
            st[1] = 120;
            SetMobyState(self, 2, -1);
        }
        break;
    case 2:
        if (FastFloatHelperD(st + 1) || st[1] >= 91) {
            *(Quadword *)vec = 0;
            vec[1] = -0.0166666675f;
            vec[2] = 0.0500000045f;
            matrix_mul_vec3(vec, vec, self + 0xc0);
            SpawnSparkBurst_L00(self, &D_L12_001B1FF0_gp, vec, 0.0f, 0.0333333351f, RandomIntRange(3, 6), 0, 0.5f, 15.0f, 2.0f);
            SpawnSparkBurst_L00(self, &D_L12_001B1FF0_gp, vec, 0.0f, 0.0333333351f, RandomIntRange(3, 6), 1, 0.5f, 15.0f, 2.0f);
            st[1] = RandomIntRange(45, 90);
        }
        break;
    }
}
