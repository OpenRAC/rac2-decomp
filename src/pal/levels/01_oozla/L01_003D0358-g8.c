#include "include_asm.h"

#include "common.h"
extern void swamp_monster_release_attack_slot(u8 *);
extern s32 FloatToInt(f32);
extern void moby_set_state(u8 *, s32, s32);
extern u8 *g_moby_l01_table;
extern s32 D_L01_001B2578[] __attribute__((sda));
extern u8 *D_L01_001B255C_base[] __asm__("D_L01_001B255C") __attribute__((sda));
extern u16 *D_L01_001FB020[];
extern u8 g_hero_position[], D_L01_001B94C0[];
extern u8 D_L01_001AFE18[] __attribute__((sda));
extern f32 D_L01_001B2F40;
extern u8 *part_find_owned_effect_slot(void *, s32, s32);
extern f32 func_PAL_002AA108(void *, void *);
extern u8 *moby_get_private_value_0(void *);
extern void func_PAL_002AC290(void *, void *);
extern void func_PAL_002AC3C0(void *, void *);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern s32 math_random_int_below(s32);
extern void vec_add_random_offset(void *, f32);
extern f32 func_PAL_L01_003BEB40(void);
extern f32 math_random_float_range(f32, f32);
extern void *part_spawn_drifting(void *, void *, u32, f32, f32);
extern int weapon_select_aim_target(void *, s32, s32, s32, f32, f32);
extern f32 fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);

/* Applies incoming damage to the linked group or this object's timer, updates its
   animation and effects, and adjusts the nearby-object reaction and height.
   The isolated profile retains the timer branch's state + 0x50 calculation and
   keeps the shared floating-point branch labels on their hazard nops. */
void func_PAL_L01_003D0358(u8 *a0)
{
    u8 pos[16] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(a0 + 0x68);
    u8 *ent, *e, *r, *linked;
    u16 *p;
    f32 damage, w;
    s32 duration, kind, exempt;
    s32 color;
    u16 cls;

    if (a0[0x95] == 1 || ((a0[0x95] >= 5 && a0[0x95] <= 6) && 0.0f < *(f32 *)(state + 0x20))) {
        ent = part_find_owned_effect_slot(a0, 0x10000, 0);
        if (*(short *)(state + 0x26) >= 1)
            ent = 0;
        damage = func_PAL_002AA108(a0, ent);
        if (ent && 0.0f < damage && a0[0x95] >= 5) {
            if (*(s32 *)(state + 0xB0) != -1) {
                *(s32 *)(state + 0xC0) = 200;
                if (a0[0x21] != 0xFF) {
                    cls = *(u16 *)(*(u8 **)(ent + 0x20) + 0xAA);
                    duration = (cls == 0xCE4 || cls == 0xCE5) ? 50 : 0;
                    for (p = D_L01_001FB020[a0[0x21]];
                         a0[0x21] != 0xFF && a0[0x21] <= D_L01_001B2578[0] && p &&
                         ((p != 0 && (short)p[-1] >= 0) || p == D_L01_001FB020[a0[0x21]]); p++) {
                        e = g_moby_l01_table + ((*p & 0x7FFF) << 8);
                        if (!e)
                            break;
                        r = moby_get_private_value_0(e);
                        if (r) {
                            *(u16 *)(r + 6) = duration;
                            *(f32 *)r -= damage;
                            r[0x17] = state[0x37];
                            *(s32 *)(r + 0x18) = *(s32 *)(state + 0x38);
                            *(u16 *)(r + 0x1C) = *(u16 *)(state + 0x3C);
                        }
                        e[0xA8] = 0xFF;
                    }
                }
            } else {
                *(f32 *)(state + 0x20) -= damage;
            }
        }
        a0[0xA8] = 0xFF;

        if (0.0f < damage) {
            state[0x57] = FloatToInt(damage * 20.0f) + 100;
            func_PAL_002AC290(a0, state + 0x50);
        }
        if (a0[0x95] == 1 && ent) {
            *(s32 *)(state + 0xBC) = 0;
            if (a0[0x20] == 0)
                moby_set_state(a0, 1, -1);
        } else {
            if (*(f32 *)(state + 0x20) < 0.0f ||
                (*(s32 *)(state + 0xB0) != -1 && (!(linked = D_L01_001B255C_base[0] + (*(s32 *)(state + 0xB0) << 8)) || (kind = linked[0x20]) == 0xFE || kind == 0xFD))) {
                swamp_monster_release_attack_slot(a0);
                if (a0[0x43] != 4)
                    func_PAL_002A7E68(a0, 4, 0, 10);
                *(u32 *)(state + 0x20) = 0;
                *(u16 *)(a0 + 0x34) &= 0xEFFF;
                moby_set_state(a0, 0, 7);
            } else {
                exempt = 0;
                if (ent && *(u8 **)(ent + 0x20))
                    exempt = *(short *)(*(u8 **)(ent + 0x20) + 0xAA) == 0x47;
                if (!exempt) {
                    if (1.0f <= damage) {
                        swamp_monster_release_attack_slot(a0);
                        if (a0[0x42] == 1) {
                            if (a0[0x43] != 3)
                                func_PAL_002A7E68(a0, 3, 5, 5);
                        } else if (a0[0x42] == 2) {
                            if (a0[0x43] != 3)
                                func_PAL_002A7E68(a0, 3, 0, 20);
                        } else if (a0[0x43] != 3) {
                            func_PAL_002A7E68(a0, 3, 2, 10);
                        }
                        *(u16 *)(a0 + 0x34) &= 0xEFFF;
                        moby_set_state(a0, 0, 7);
                    }
                    if (0.1f < damage) {
                        FastVecSub(state + 0xA0, a0 + 0x10, g_hero_position);
                        w = (damage + damage + 3.0f) * 0.020000001f;
                        if (0.24000001f < w)
                            w = 0.24000001f;
                        vec_scale_to_length(state + 0xA0, state + 0xA0, w);
                        *(s32 *)(state + 0xA8) = 0;
                    }
                }
            }
        }
    } else {
        a0[0xA8] = 0xFF;
    }
    func_PAL_002AC3C0(a0, state + 0x50);
    if (0.0f < *(f32 *)(a0 + 0x48) && a0[0x95] != 2 && a0[0x31] && math_random_int_below(9) == 0) {
        qcopy(pos, a0 + 0x10);
        vec_add_random_offset(&pos, 0.15f);
        ((f32 *)pos)[2] = func_PAL_L01_003BEB40();
        damage = math_random_float_range(0.5f, 3.0f);
        color = ((math_random_int_below(6) + 20) << 24) | 0x5060;
        part_spawn_drifting(&pos, D_L01_001AFE18, color, damage, 14400.001f);
    }
    weapon_select_aim_target(a0, *(s32 *)(state + 0xF0), 0, a0[0x95] < 5, 0.0f, 0.0f);
    kind = a0[0x31];
    if (kind && fast_vec_dist(a0 + 0x10, D_L01_001B94C0) < 48.0f) {
        moby_update_ground_check(a0);
        a0[0x6F] = 45;
    }
    *(f32 *)(a0 + 0x74) = 1.0f;
    *(f32 *)(a0 + 0x70) = 109.0f - *(f32 *)(a0 + 0x18);
    if (a0[0x95] >= 3 && a0[0x95] <= 7)
        D_L01_001B2F40 = 0.20943953f;
}
