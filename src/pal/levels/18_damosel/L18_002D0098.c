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
extern float fade_reduce_value_pal(float);
extern s32 FloatToInt(float);
extern void hero_clear_tracked_slots(void);
extern void FastVecSub(void *, void *, void *);
extern void hero_build_relative_point(void *, s32, float, float, float);
extern s32 hero_l18_set_move_state_pal(s32, s32);
extern u8 *part_find_owned_effect_slot(u8 *, s32, s32);
extern void AdjustPlayerHealth_pal(s32);
extern int hero_play_sound(s32, s32);
extern void hero_flatten_push_vector(void *, s32, float, float);
extern void cam_scale_view_space_height(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; } Hero;
extern float vec_distance_xy(void *, void *);
extern float ApproachValue(float *, float, float);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);

/* Handles the hero touching a hit object: checks if the touch counts, then pushes the hero and picks the reaction animation (PAL: other timings). */
s32 hero_handle_hit_object_contact_pal(s32 apply_push) {
    TI16 push_vec;
    Entry_002D01B0 *entry;
    u8 *touched_moby;
    u8 *hit_moby;
    s32 is_special;
    s32 unused_bits;

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
    touched_moby = g_hero_state.f2290;
    if (touched_moby[0xA8] == 0xFF) {
        return 0;
    }
    entry = &g_hero_contact_table[touched_moby[0xA8]];
    if (entry->f38 != touched_moby) {
        return 0;
    }
    if (g_hero_state.f22B4 == 4) {
        if (g_hero_frozen_flag != 0 || g_hero_state.f2294 == 0x6F) {
            return 0;
        }
    } else if ((entry->f24 & 9) == 0) {
        return 0;
    }
    if (entry->f2C != 0.0f) {
        g_contact_hit_flag = 0;
        g_bolt_multiplier = 1;
    }
    if (fade_get_value() != 0.0f && g_hero_state.f22B4 == 0) {
        entry->f2C = fade_reduce_value_pal(entry->f2C);
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
    if (g_hero_state.f22B4 == 4 && g_hero_frozen_flag == 0 && g_hero_state.f2294 != 0x6F) {
        u8 *moby_vars = *(u8 **)(g_hero_state.f2290 + 0x68);
        *(s16 *)(moby_vars + 0x3BC) -= 0x96;
        if (*(s16 *)(moby_vars + 0x3BC) < 0) {
            *(s16 *)(moby_vars + 0x3BC) = 0;
        }
    }
    if (apply_push == 0) {
        return 1;
    }
    is_special = 0;
    hero_clear_tracked_slots();
    if (entry->f30 & 1) {
        qcopy(&push_vec, &entry->f10);
        if (entry->f1C == 5627.9248046875f) {
            is_special = 1;
        }
    } else if (entry->f20 != 0) {
        FastVecSub(&push_vec, &g_hero_state.f80, entry->f20 + 0x10);
    } else {
        hero_build_relative_point(&push_vec, 0, -1.0f, 0.0f, 0.0f);
    }
    switch (g_hero_state.f22B4) {
    case 0:
        hit_moby = g_hero_state.f249C;
        if (hit_moby != 0 && (*(s16 *)(hit_moby + 0xAA) == 0x4EB || *(s16 *)(hit_moby + 0xAA) == 0x558)) {
            hero_l18_set_move_state_pal(0x7D, 1);
            return 1;
        }
        if ((g_hero_state.f2294 == 1 || g_hero_state.f2294 == 0x1D || g_hero_state.f1500 != 0)
            && !(entry->f24 & 8)) {
            u8 *effect_slot = part_find_owned_effect_slot(g_hero_state.f2290, 1, 0);

            if (effect_slot != 0) {
                AdjustPlayerHealth_pal(FloatToInt(*(float *)(effect_slot + 0x2C)));
            }
            if (g_hero_state.f24CC == 0) {
                hero_l18_set_move_state_pal(0x16, 1);
            }
            g_hero_state.f1DC = 0x40;
            if (g_hero_state.f21C == 0) {
                g_hero_state.f21C = 0xF;
            }
            hero_play_sound(0x14, 0);
            return 0;
        }
        if (g_hero_state.f229C == 0x12) {
            hero_l18_set_move_state_pal(0x72, 1);
        } else if (g_hero_state.f229C == 0x11) {
            hero_l18_set_move_state_pal(0x73, 1);
        } else if (entry->f24 & 8) {
            hero_l18_set_move_state_pal(0x8C, 1);
        } else {
            hero_l18_set_move_state_pal(0x16, 1);
        }
        if (g_hero_state.f2294 == 0x8C) {
            qzero(&push_vec);
        } else {
            hero_flatten_push_vector(&push_vec, is_special, g_hero_state.f1497 ? 0.0f : 0.06600001f, 0.034f);
            if (is_special != 0 && entry->f28 == 4) {
                cam_scale_view_space_height(&push_vec, &push_vec, 2.0f);
            }
        }
        break;
    case 4:
        hero_l18_set_move_state_pal(0x90, 1);
        hero_flatten_push_vector(&push_vec, is_special, 0.10000001f, 0.060000002f);
        break;
    }
    FastVecAdd(&g_hero_state.fF0, &g_hero_state.fF0, &push_vec);
    FastVecAdd(&g_hero_state.f110, &g_hero_state.f110, &push_vec);
    return 1;
}


/* func_PAL_L18_002D0738, the PAL copy of func_L18_002D0850: the same C, where the step 0.02f becomes
   0.024f and the last call takes 0.0288f, 0.432f and 0.08f. */
/* Sets the hero's movement speed targets for the current state and eases the current speeds toward them (PAL: 50 Hz step). */
void hero_l18_update_speed_targets_pal(void) {
    int mode;
    int anim_state;
    float dist;

    if (((Hero *)&g_hero_state)->b[0x22B4] == 0 || ((Hero *)&g_hero_state)->b[0x22B4] == 4) {
        ((Hero *)&g_hero_state)->f[0x258 / 4] = 0.8f;
        ((Hero *)&g_hero_state)->f[0x25C / 4] = 0.7f;
        ((Hero *)&g_hero_state)->f[0x260 / 4] = 0.45f;
    }

    mode = ((Hero *)&g_hero_state)->i[0x229C / 4];
    if (mode == 4) {
        if (((Hero *)&g_hero_state)->h[0x4AC / 2] < ((Hero *)&g_hero_state)->i[0x1B8 / 4]) {
            if (((Hero *)&g_hero_state)->b[0x49E] == 0) {
                ((Hero *)&g_hero_state)->f[0x25C / 4] = ((Hero *)&g_hero_state)->f[0x4B8 / 4];
            }
        }
    } else {
        anim_state = ((Hero *)&g_hero_state)->i[0x2294 / 4];
        if (anim_state == 6) {
            ((Hero *)&g_hero_state)->f[0x25C / 4] = 0.5f;
        } else if (anim_state == 4) {
            ((Hero *)&g_hero_state)->f[0x258 / 4] = 0.35000002384185791f;
        } else if ((u32)(mode - 0x11) < 2) {
            ((Hero *)&g_hero_state)->i[0x258 / 4] = 0;
            ((Hero *)&g_hero_state)->i[0x25C / 4] = 0;
        } else if (((Hero *)&g_hero_state)->b[0x1492] != 0 && ((Hero *)&g_hero_state)->i[0x340 / 4] != 0) {
            ((Hero *)&g_hero_state)->f[0x258 / 4] = 0.8f;
            ((Hero *)&g_hero_state)->f[0x25C / 4] = 0.9f;
        } else if (((Hero *)&g_hero_state)->i[0x2294 / 4] == 0x7C) {
            ((Hero *)&g_hero_state)->f[0x260 / 4] = 0.8f;
        }
    }

    if (((Hero *)&g_hero_state)->b[0x287] == 0)
        goto slow;
    if (((Hero *)&g_hero_state)->i[0x22A4 / 4] == 0x12)
        goto slow;
    if (((Hero *)&g_hero_state)->i[0x22B0 / 4] == 0x12)
        goto slow;
    if (((Hero *)&g_hero_state)->b[0x22B4] == 0) {
        if (((Hero *)&g_hero_state)->f[0x254 / 4] < 0.53f)
            goto slow;
    }
    if (((Hero *)&g_hero_state)->i[0x229C / 4] == 0x11)
        goto slow;
    if (((Hero *)&g_hero_state)->b[0x1494] != 0)
        goto slow;

    dist = vec_distance_xy((u8 *)&g_hero_state + 0x240, (u8 *)&g_hero_state + 0x80);
    if (dist > ((Hero *)&g_hero_state)->f[0x264 / 4] * 0.5f)
        goto slow;
    return;

slow:
    {
        /* The channel block sits 0x250 into the runtime block; the block pointer
           is taken first and the runtime block is reached back from it. */
        u8 *channels = (u8 *)&g_hero_state + 0x250;
        float step = 0.024f;
        ApproachValue((float *)channels, ((Hero *)&g_hero_state)->f[0x258 / 4], step);
        ApproachValue((float *)(channels + 4), ((Hero *)&g_hero_state)->f[0x25C / 4], step);
        math_spring_float_to_goal(
            (float *)(channels + 0x14),
            (float *)(channels + 0x18),
            ((Hero *)&g_hero_state)->f[0x260 / 4],
            0.028800001f,
            0.43200004f,
            0.080000006f);
    }
}
