#include "common.h"

extern s32 func_305EE8(s32 size);
extern f32 func_310648(void);
extern u32 g_pHeroMoby[];
extern f32 D_L01_001B1A68 __attribute__((sda));
extern f32 D_L01_001B1A6C __attribute__((sda));
extern f32 D_L01_001B1A70 __attribute__((sda));
extern void func_L01_00416B30(void *a0);

/* Spawns a gold bolt moby at a position, already in its idle state, with random spin angles.
 * Adapted from the state 0 of RAC1's gold_bolt_update (GPL-3.0). */
s32 func_L01_004171C8(void *position, void *ownerA, void *ownerB, void *ownerC) {
    u8 *bolt;
    u8 *vars;
    f32 value, spinX, spinY, spinZ;

    bolt = (u8 *)func_305EE8(0x1250);
    if (bolt != 0) {
        vars = *(u8 **)(bolt + 0x68);
        *(u64 *)(bolt + 0x38) = *(u64 *)((u8 *)g_pHeroMoby[0] + 0x38);
        qcopy(bolt + 0x10, position);
        *(u16 *)(bolt + 0x32) = 0x5A;
        *(u8 *)(bolt + 0x30) = 0x40;
        *(u8 *)(bolt + 0x31) = 1;
        *(u32 *)vars = (u32)ownerA;
        qcopy(vars + 0x10, bolt + 0x10);
        value = *(f32 *)(bolt + 0xF8);
        *(f32 *)(vars + 0x1C) = value;
        value = func_310648();
        *(f32 *)(bolt + 0xF0) = value;
        value = func_310648();
        *(f32 *)(bolt + 0xF4) = value;
        value = func_310648();
        *(f32 *)(bolt + 0xF8) = value;
        value = func_310648();
        spinX = D_L01_001B1A68;
        spinY = D_L01_001B1A6C;
        spinZ = D_L01_001B1A70;
        *(f32 *)(bolt + 0xFC) = value;
        *(u32 *)(vars + 8) = (u32)ownerC;
        *(u32 *)(vars + 4) = (u32)ownerB;
        *(f32 *)(vars + 0x68) = spinX * 0.0002908882452175021f;
        *(f32 *)(vars + 0x64) = spinY * 0.0002908882452175021f;
        *(f32 *)(vars + 0x60) = spinZ * 0.0002908882452175021f;
        *(u8 *)(bolt + 0x20) = 1;
        InitGoldBoltGlow(bolt);
    }
    return (s32)bolt;
}
