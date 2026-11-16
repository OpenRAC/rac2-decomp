#include "common.h"

extern s32 func_305EE8(s32 size);
extern f32 func_310648(void);
extern u32 g_pHeroMoby[];
extern f32 g_spin_rate_x __attribute__((sda));
extern f32 g_spin_rate_y __attribute__((sda));
extern f32 g_spin_rate_z __attribute__((sda));
extern void gold_bolt_glow_init(void *a0);

/* Spawns a gold bolt moby at a position, already in its idle state, with random spin angles.
 * Adapted from the state 0 of RAC1's gold_bolt_update (GPL-3.0). */
void *SpawnGoldBolt(void *position, void *owner_a, void *owner_b, void *owner_c) {
    u8 *bolt;
    u8 *vars;
    f32 value, spin_x, spin_y, spin_z;

    bolt = (u8 *)func_305EE8(0x1250);
    if (bolt != 0) {
        vars = *(u8 **)(bolt + 0x68);
        *(u64 *)(bolt + 0x38) = *(u64 *)((u8 *)g_pHeroMoby[0] + 0x38);
        qcopy(bolt + 0x10, position);
        *(u16 *)(bolt + 0x32) = 0x5A;
        *(u8 *)(bolt + 0x30) = 0x40;
        *(u8 *)(bolt + 0x31) = 1;
        *(u32 *)vars = (u32)owner_a;
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
        spin_x = g_spin_rate_x;
        spin_y = g_spin_rate_y;
        spin_z = g_spin_rate_z;
        *(f32 *)(bolt + 0xFC) = value;
        *(u32 *)(vars + 8) = (u32)owner_c;
        *(u32 *)(vars + 4) = (u32)owner_b;
        *(f32 *)(vars + 0x68) = spin_x * 0.0002908882452175021f;
        *(f32 *)(vars + 0x64) = spin_y * 0.0002908882452175021f;
        *(f32 *)(vars + 0x60) = spin_z * 0.0002908882452175021f;
        *(u8 *)(bolt + 0x20) = 1;
        gold_bolt_glow_init(bolt);
    }
    return (s32)bolt;
}
