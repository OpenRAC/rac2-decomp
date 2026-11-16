#include "include_asm.h"

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
} Player_002D01B0;
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
} Entry_002D01B0;
extern Player_002D01B0 g_hero_state;
extern Entry_002D01B0 g_hero_contact_table[];
extern s32 g_game_l18_mode_state __attribute__((sda));
extern s32 g_hero_frozen_flag __attribute__((sda));
extern u8 g_bolt_multiplier __attribute__((sda));
extern u8 g_contact_hit_flag __attribute__((sda));
extern float fade_get_value(void);
extern float fade_reduce_value(float);
extern s32 FloatToInt(float);
extern void hero_clear_tracked_slots(void);
extern void FastVecSub(void *, void *, void *);
extern void hero_build_relative_point(void *, s32, float, float, float);
extern s32 func_US2_L18_002E02E8(s32, s32);
extern u8 *part_find_owned_effect_slot(u8 *, s32, s32);
extern void AdjustPlayerHealth_us2(s32);
extern int hero_play_sound(s32, s32);
extern void hero_flatten_push_vector(void *, s32, float, float);
extern void cam_scale_view_space_height(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

s32 hero_handle_hit_object_contact_us2(s32 arg0) {
    TI16 vec;
    Entry_002D01B0 *e;
    u8 *moby;
    u8 *other;
    s32 flag;
    s32 bits;

    if (g_hero_state.f229C == 20 || g_hero_state.f229C == 7) {
        return 0;
    }
    if (g_hero_state.f2294 == 0x31) {
        return 0;
    }
    if (g_hero_state.f1DC != 0) {
        return 0;
    }
    if (g_game_l18_mode_state != 0) {
        return 0;
    }
    g_hero_state.f249C = 0;
    moby = g_hero_state.f2290;
    if (moby[0xA8] == 0xFF) {
        return 0;
    }
    e = &g_hero_contact_table[moby[0xA8]];
    if (e->f38 != moby) {
        return 0;
    }
    if (g_hero_state.f22B4 == 4) {
        if (g_hero_frozen_flag != 0 || g_hero_state.f2294 == 0x6F) {
            return 0;
        }
    } else if ((e->f24 & 9) == 0) {
        return 0;
    }
    if (e->f2C != 0.0f) {
        g_contact_hit_flag = 0;
        g_bolt_multiplier = 1;
    }
    if (fade_get_value() != 0.0f && g_hero_state.f22B4 == 0) {
        e->f2C = fade_reduce_value(e->f2C);
        if (e->f2C == 0.0f) {
            return 0;
        }
    }
    g_hero_state.f249C = e->f20;
    if (g_hero_state.f229C == 15) {
        g_hero_state.f6C4 = e;
        g_hero_state.f68E = 1;
        return 0;
    }
    if (g_hero_state.f22B4 == 4 && g_hero_frozen_flag == 0 && g_hero_state.f2294 != 0x6F) {
        u8 *m = *(u8 **)(g_hero_state.f2290 + 0x68);
        *(s16 *)(m + 0x3BC) -= 0xB4;
        if (*(s16 *)(m + 0x3BC) < 0) {
            *(s16 *)(m + 0x3BC) = 0;
        }
    }
    if (arg0 == 0) {
        return 1;
    }
    flag = 0;
    hero_clear_tracked_slots();
    if (e->f30 & 1) {
        qcopy(&vec, &e->f10);
        if (e->f1C == 5627.9248046875f) {
            flag = 1;
        }
    } else if (e->f20 != 0) {
        FastVecSub(&vec, &g_hero_state.f80, e->f20 + 0x10);
    } else {
        hero_build_relative_point(&vec, 0, -1.0f, 0.0f, 0.0f);
    }
    switch (g_hero_state.f22B4) {
    case 0:
        other = g_hero_state.f249C;
        if (other != 0 && (*(s16 *)(other + 0xAA) == 0x4EB || *(s16 *)(other + 0xAA) == 0x558)) {
            func_US2_L18_002E02E8(0x7D, 1);
            return 1;
        }
        if ((g_hero_state.f2294 == 1 || g_hero_state.f2294 == 0x1D || g_hero_state.f1500 != 0)
            && !(e->f24 & 8)) {
            u8 *r = part_find_owned_effect_slot(g_hero_state.f2290, 1, 0);

            if (r != 0) {
                AdjustPlayerHealth_us2(FloatToInt(*(float *)(r + 0x2C)));
            }
            if (g_hero_state.f24CC == 0) {
                func_US2_L18_002E02E8(0x16, 1);
            }
            g_hero_state.f1DC = 0x4D;
            if (g_hero_state.f21C == 0) {
                g_hero_state.f21C = 0x12;
            }
            hero_play_sound(0x14, 0);
            return 0;
        }
        if (g_hero_state.f229C == 0x12) {
            func_US2_L18_002E02E8(0x72, 1);
        } else if (g_hero_state.f229C == 0x11) {
            func_US2_L18_002E02E8(0x73, 1);
        } else if (e->f24 & 8) {
            func_US2_L18_002E02E8(0x8C, 1);
        } else {
            func_US2_L18_002E02E8(0x16, 1);
        }
        if (g_hero_state.f2294 == 0x8C) {
            qzero(&vec);
        } else {
            hero_flatten_push_vector(&vec, flag, g_hero_state.f1497 ? 0.0f : 0.055000003f, 0.028333336f);
            if (flag != 0 && e->f28 == 4) {
                cam_scale_view_space_height(&vec, &vec, 2.0f);
            }
        }
        break;
    case 4:
        func_US2_L18_002E02E8(0x90, 1);
        hero_flatten_push_vector(&vec, flag, 0.083333336f, 0.050000004f);
        break;
    }
    FastVecAdd(&g_hero_state.fF0, &g_hero_state.fF0, &vec);
    FastVecAdd(&g_hero_state.f110, &g_hero_state.f110, &vec);
    return 1;
}

