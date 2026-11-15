/* Apply a validated contact impulse to the player. */
#include "common.h"

typedef int TI16 __attribute__((mode(TI)));

typedef struct {
    u8 pad0[0x80];
    TI16 f80;
    u8 pad90[0xF0 - 0x90];
    TI16 fF0;
    u8 pad100[0x10];
    TI16 f110;
    u8 pad120[0x1DC - 0x120];
    s16 f1DC;
    u8 pad1DE[0x21C - 0x1DE];
    s16 f21C;
    u8 pad21E[0x68E - 0x21E];
    s16 f68E;
    u8 pad690[0x6C4 - 0x690];
    void *f6C4;
    u8 pad6C8[0x1497 - 0x6C8];
    u8 f1497;
    u8 pad1498[0x1500 - 0x1498];
    s32 f1500;
    u8 pad1504[0x1874 - 0x1504];
    s32 f1874;
    u8 pad1878[0x2290 - 0x1878];
    u8 *f2290;
    s32 f2294;
    u8 pad2298[4];
    s32 f229C;
    u8 pad22A0[0x22B4 - 0x22A0];
    u8 f22B4;
    u8 pad22B5[0x249C - 0x22B5];
    u8 *f249C;
    u8 pad24A0[0x24CC - 0x24A0];
    s32 f24CC;
} PlayerContactState;

typedef struct {
    u8 pad0[0x10];
    float f10;
    float f14;
    float f18;
    float f1C;
    u8 *f20;
    s32 f24;
    u8 f28;
    u8 pad29[3];
    float f2C;
    s32 f30;
    u8 pad34[4];
    u8 *f38;
    u8 pad3C[4];
} PlayerContactEntry;

extern PlayerContactState g_hero_state;
extern PlayerContactEntry D_L16_001C41C0[];
extern s32 D_L16_001A8F00 __attribute__((sda));
extern u8 g_bolt_multiplier __attribute__((sda));
extern u8 D_001A7A33 __attribute__((sda));

extern float fade_get_value(void);
extern float fade_reduce_value(float);
extern s32 FloatToInt(float);
extern void hero_clear_tracked_slots(void);
extern void FastVecSub(void *, void *, void *);
extern void hero_build_relative_point(void *, s32, float, float, float);
extern s32 hero_l16_enter_state(unsigned long, unsigned long);
extern u8 *part_find_owned_effect_slot(u8 *, s32, s32);
extern void AdjustPlayerHealth(s32);
extern int hero_play_sound(s32, s32);
extern void hero_flatten_push_vector(void *, s32, float, float);
extern void cam_scale_view_space_height(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

/* Handles the player touching a damaging or pushing object: picks the hurt reaction and shoves the player away. */
s32 hero_handle_contact_reaction(s32 apply_reaction) {
    TI16 impulse;
    PlayerContactEntry *entry;
    u8 *moby;
    u8 *contact_moby;
    s32 fixed_direction;

    if (g_hero_state.f229C == 20 || g_hero_state.f229C == 7) {
        return 0;
    }
    if (g_hero_state.f2294 == 0x31) {
        return 0;
    }
    if (g_hero_state.f1DC != 0) {
        return 0;
    }
    if (D_L16_001A8F00 != 0) {
        return 0;
    }
    g_hero_state.f249C = 0;
    moby = g_hero_state.f2290;
    if (moby[0xA8] == 0xFF) {
        return 0;
    }
    entry = &D_L16_001C41C0[moby[0xA8]];
    if (entry->f38 != moby) {
        return 0;
    }
    if ((entry->f24 & 9) == 0) {
        return 0;
    }
    if (entry->f2C != 0.0f) {
        D_001A7A33 = 0;
        g_bolt_multiplier = 1;
    }
    if (fade_get_value() != 0.0f && g_hero_state.f22B4 == 0) {
        entry->f2C = fade_reduce_value(entry->f2C);
        if (entry->f2C == 0.0f) {
            return 0;
        }
    }
    g_hero_state.f249C = entry->f20;
    if (g_hero_state.f229C == 15) {
        g_hero_state.f6C4 = entry;
        g_hero_state.f68E = 1;
        return 0;
    }
    if (apply_reaction == 0) {
        return 1;
    }
    fixed_direction = 0;
    hero_clear_tracked_slots();
    if (entry->f30 & 1) {
        qcopy(&impulse, &entry->f10);
        if (entry->f1C == 5627.9248046875f) {
            fixed_direction = 1;
        }
    } else if (entry->f20 != 0) {
        FastVecSub(&impulse, &g_hero_state.f80, entry->f20 + 0x10);
    } else {
        hero_build_relative_point(&impulse, 0, -1.0f, 0.0f, 0.0f);
    }
    switch (g_hero_state.f22B4) {
    case 0:
        contact_moby = g_hero_state.f249C;
        if (contact_moby != 0 && (*(s16 *)(contact_moby + 0xAA) == 0x4EB /* moby class 1259 */ || *(s16 *)(contact_moby + 0xAA) == 0x558 /* moby class 1368 */)) {
            hero_l16_enter_state(0x7D, 1);
            return 1;
        }
        if ((g_hero_state.f2294 == 1 || g_hero_state.f2294 == 0x1D || g_hero_state.f1500 != 0)
            && !(entry->f24 & 8)) {
            u8 *hit_info = part_find_owned_effect_slot(g_hero_state.f2290, 1, 0);

            if (hit_info != 0) {
                AdjustPlayerHealth(FloatToInt(*(float *)(hit_info + 0x2C)));
            }
            if (g_hero_state.f24CC == 0) {
                hero_l16_enter_state(0x16, 1);
            }
            g_hero_state.f1DC = 0x4D;
            if (g_hero_state.f21C == 0) {
                g_hero_state.f21C = 0x12;
            }
            hero_play_sound(0x14, 0);
            return 0;
        }
        if (entry->f24 & 8) {
            hero_l16_enter_state(0x8C, 1);
        } else {
            hero_l16_enter_state(0x16, 1);
        }
        if (g_hero_state.f2294 == 0x8C) {
            qzero(&impulse);
        } else {
            hero_flatten_push_vector(&impulse, fixed_direction, g_hero_state.f1497 ? 0.0f : 0.055000003f, 0.028333336f);
            if (fixed_direction != 0 && entry->f28 == 4) {
                cam_scale_view_space_height(&impulse, &impulse, 2.0f);
            }
        }
        break;
    }
    FastVecAdd(&g_hero_state.fF0, &g_hero_state.fF0, &impulse);
    FastVecAdd(&g_hero_state.f110, &g_hero_state.f110, &impulse);
    return 1;
}
