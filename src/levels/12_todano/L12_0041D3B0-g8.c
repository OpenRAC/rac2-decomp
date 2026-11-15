#include "common.h"

extern struct { u8 pad[0x464]; u8 flags[0]; } D_L12_0021EDF0;
extern u8 D_0019B4A8[];
extern s32 D_001A79F0 __attribute__((sda));
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
extern s32 D_L12_001B1DC0 __attribute__((sda));
/* The burst helper reads a vector at this GP-relative address. */
extern f32 D_L12_001B1DD0[] SDATA(D_L12_001B1DD0);
extern u8 D_00189EA0[];

extern void func_0029F338(void *);
extern s32 func_L12_0041E8E8(void *);
extern void func_L12_0041E8F8(void *);
extern void func_002A7750(void *, s32, s32);
extern s32 func_00282948(void *);
/* Eight GPR inputs, four stack inputs and two FP inputs, in their EE ABI order. */
extern void *func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32,
                         s32, s32, s32, s32, f32, f32);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFEB8(void *, void *, void *, void *, f32);
extern void func_00282F20(void *, void *, f32);
extern void func_002B0A68(void *, s32, void *, u8, f32, f32, f32, f32);

/* Waits for three linked mobys to be ready, lifts them, then blows up and leaves a burst of effects. */
void func_L12_0041D3B0(u8 *self)
{
    u8 *vars = *(u8 **)(self + 0x68);
    s32 ready;
    f32 temp[4] __attribute__((aligned(16)));

    switch (self[0x20]) {
    case 0: {
        u16 id;
        s32 packed;

        self[0x20] = 1;
        *(f32 *)(vars + 0x10) = *(f32 *)(self + 0x18);
        id = *(u16 *)(self + 0xB2);
        if (D_L12_0021EDF0.flags[(s16)id])
            goto Destroy0;
        packed = D_0019B4A8[((s16)id >> 1) + (gCurrentMapIndex << 10)];
        if (id & 1) {
            if ((packed >> 4) & 7)
                goto Destroy0;
            return;
        } else {
            if (!(packed & 7))
                return;
        }
Destroy0:
        MarkMobySpawned(self);
        break;
    }
    case 1: {
        s32 *childIds;
        s32 i;

        ready = 1;
        childIds = (s32 *)vars;
        for (i = 0; i < 3; i++) {
            if (childIds[i] != -1) {
                if (!IsLinkedMobyFinished(D_L12_001B2E9C_gp + (childIds[i] << 8)))
                    ready = 0;
            }
        }
        if (ready)
            self[0x20] = 2;
        break;
    }
    case 4: {
        u8 *base = D_L12_001B2E9C;
        s32 *childIds;
        s32 i;

        *(f32 *)(vars + 0xC) += 0.0013888889f;
        *(f32 *)(self + 0x18) += *(f32 *)(vars + 0xC);
        childIds = (s32 *)vars;
        for (i = 0; i < 3; i++) {
            if (childIds[i] != -1)
                *(f32 *)((childIds[i] << 8) + (u32)base + 0x18) += *(f32 *)(vars + 0xC);
        }
        if (*(f32 *)(vars + 0x10) + 8.0f < *(f32 *)(self + 0x18))
            self[0x20] = 5;
        break;
    }
    case 2:
        SetMobyState(self, 3, -1);
        *(s32 *)(vars + 0x14) = D_L12_001B1DC0;
        break;

    case 3: {
        s32 *childIds;
        s32 i;
        s32 *childIds2;
        s32 j;

        if (FastFloatHelperD(vars + 0x14)) {
            SpawnExplosion(D_L12_001B1DD0, 1, 14, 10, 15, 10, 20, 1,
                          1, 1, 0, 0, 2.0f, 20.0f);
            *(s32 *)(self + 0x98) = 0;
            *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) | 0x41) & 0xEFFF;
            FastVecSub(temp, self + 0x10, gHeroPosition);
            TransformAndSetHeight(self, temp, temp, 0, 0.0f);
            vec_scale_to_length(temp, temp, 0.10000001f);
            SpawnDebrisForMaskedParts(self, 0xFFF, temp, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
            SetMobyState(self, 5, -1);
            childIds = (s32 *)vars;
            for (i = 0; i < 3; i++) {
                if (childIds[i] != -1) {
                    D_L12_001B2E9C_gp[(childIds[i] << 8) + 0x20] = 4;
                    TriggerLinkedMobyBurst(D_L12_001B2E9C + (childIds[i] << 8));
                }
            }
        }
        if (*(s32 *)(vars + 0x14) == D_L12_001B1DC0 / 2) {
            childIds2 = (s32 *)vars;
            for (j = 0; j < 3; j++) {
                if (childIds2[j] != -1)
                    D_L12_001B2E9C_gp[(childIds2[j] << 8) + 0x20] = 4;
            }
        }
        break;
    }
    case 5: {
        u8 *base, *child, *counter;
        u16 id;
        s32 *childIds;
        s32 i;

        childIds = (s32 *)vars;
        for (i = 0; i < 3; i++) {
            if (childIds[i] != -1) {
                base = D_L12_001B2E9C_gp;
                child = (u8 *)((childIds[i] << 8) + (u32)base);
                *(u16 *)(child + 0x34) &= 0xEFFF;
                MarkMobySpawned(base + (childIds[i] << 8));
            }
        }
        id = *(u16 *)(self + 0xB2);
        if (id & 1) {
            counter = &D_0019B4A8[((s16)id >> 1) + (gCurrentMapIndex << 10)];
            if (((*counter >> 4) & 7) != 7)
                *counter += 16;
        } else {
            counter = &D_0019B4A8[((s16)id >> 1) + (gCurrentMapIndex << 10)];
            if ((*counter & 7) != 7)
                *counter += 1;
        }
        MarkMobySpawned(self);
        break;
    }
    }
}
