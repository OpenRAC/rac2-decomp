#include "include_asm.h"

#include "common.h"
typedef int TI16 __attribute__((mode(TI)));
typedef struct {
    u8 pad0[0x80];
    TI16 position;
    u8 pad90[0xF0 - 0x90];
    TI16 unk_f0;
    u8 pad100[0x10];
    TI16 unk_110;
    u8 pad120[0x1DC - 0x120];
    s16 unk_1dc;
    u8 pad1DE[0x21C - 0x1DE];
    s16 unk_21c;
    u8 pad21E[0x68E - 0x21E];
    s16 unk_68e;
    u8 pad690[0x6C4 - 0x690];
    void *unk_6c4;
    u8 pad6C8[0x1497 - 0x6C8];
    u8 unk_1497;
    u8 pad1498[0x1500 - 0x1498];
    s32 unk_1500;
    u8 pad1504[0x1874 - 0x1504];
    s32 unk_1874;
    u8 pad1878[0x2290 - 0x1878];
    u8 *unk_2290;
    s32 unk_2294;
    u8 pad2298[4];
    s32 unk_229c;
    u8 pad22A0[0x22B4 - 0x22A0];
    u8 unk_22b4;
    u8 pad22B5[0x249C - 0x22B5];
    u8 *unk_249c;
    u8 pad24A0[0x24CC - 0x24A0];
    s32 unk_24cc;
} Player_002B5BF0;
typedef struct {
    u8 pad0[0x10];
    float unk_10;
    float unk_14;
    float unk_18;
    float unk_1c;
    u8 *unk_20;
    s32 unk_24;
    u8 unk_28;
    u8 pad29[3];
    float unk_2c;
    s32 unk_30;
    u8 pad34[4];
    u8 *unk_38;
    u8 pad3C[4];
} Entry_002B5BF0;
extern Player_002B5BF0 g_hero_state;
extern Entry_002B5BF0 g_contact_l19_push_table[];
extern s32 g_hero_l19_mode __attribute__((sda));
extern s32 g_hero_l19_busy_flag __attribute__((sda));
extern u8 g_bolt_multiplier __attribute__((sda));
extern u8 g_contact_hit_flag __attribute__((sda));
extern float fade_get_value(void);
extern float fade_reduce_value_pal(float);
extern s32 FloatToInt(float);
extern void hero_clear_tracked_slots(void);
extern void FastVecSub(void *, void *, void *);
extern void hero_build_relative_point(void *, s32, float, float, float);
extern s32 hero_l19_set_move_state_pal(s32, s32);
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

/* Applies a contact push to the hero from the moby it touches: checks it may push, then knocks the hero back or hurts it (PAL: 50 Hz speeds). */
s32 hero_l19_apply_contact_push_pal(s32 apply) {
    TI16 vec;
    Entry_002B5BF0 *entry;
    u8 *moby;
    u8 *other;
    s32 flag;
    s32 bits;

    if (g_hero_state.unk_229c == 20 || g_hero_state.unk_229c == 7) {
        return 0;
    }
    if (g_hero_state.unk_2294 == 0x31) {
        return 0;
    }
    if (g_hero_state.unk_1dc != 0) {
        return 0;
    }
    if (g_hero_l19_mode != 0) {
        return 0;
    }
    g_hero_state.unk_249c = 0;
    moby = g_hero_state.unk_2290;
    if (moby[0xA8] == 0xFF) {
        return 0;
    }
    entry = &g_contact_l19_push_table[moby[0xA8]];
    if (entry->unk_38 != moby) {
        return 0;
    }
    if (g_hero_state.unk_22b4 == 4) {
        if (g_hero_l19_busy_flag != 0 || g_hero_state.unk_2294 == 0x6F) {
            return 0;
        }
    } else if ((entry->unk_24 & 9) == 0) {
        return 0;
    }
    if (entry->unk_2c != 0.0f) {
        g_contact_hit_flag = 0;
        g_bolt_multiplier = 1;
    }
    if (fade_get_value() != 0.0f && g_hero_state.unk_22b4 == 0) {
        entry->unk_2c = fade_reduce_value_pal(entry->unk_2c);
        if (entry->unk_2c == 0.0f) {
            return 0;
        }
    }
    g_hero_state.unk_249c = entry->unk_20;
    if (g_hero_state.unk_22b4 == 4 && g_hero_l19_busy_flag == 0 && g_hero_state.unk_2294 != 0x6F) {
        u8 *vars = *(u8 **)(g_hero_state.unk_2290 + 0x68);
        *(s16 *)(vars + 0x3BC) -= 0x96;
        if (*(s16 *)(vars + 0x3BC) < 0) {
            *(s16 *)(vars + 0x3BC) = 0;
        }
    }
    if (apply == 0) {
        return 1;
    }
    flag = 0;
    hero_clear_tracked_slots();
    if (entry->unk_30 & 1) {
        qcopy(&vec, &entry->unk_10);
        if (entry->unk_1c == 5627.9248046875f) {
            flag = 1;
        }
    } else if (entry->unk_20 != 0) {
        FastVecSub(&vec, &g_hero_state.position, entry->unk_20 + 0x10);
    } else {
        hero_build_relative_point(&vec, 0, -1.0f, 0.0f, 0.0f);
    }
    switch (g_hero_state.unk_22b4) {
    case 0:
        other = g_hero_state.unk_249c;
        if (other != 0 && (*(s16 *)(other + 0xAA) == 0x4EB || *(s16 *)(other + 0xAA) == 0x558)) {
            hero_l19_set_move_state_pal(0x7D, 1);
            return 1;
        }
        if ((g_hero_state.unk_2294 == 1 || g_hero_state.unk_2294 == 0x1D || g_hero_state.unk_1500 != 0)
            && !(entry->unk_24 & 8)) {
            u8 *effect_slot = part_find_owned_effect_slot(g_hero_state.unk_2290, 1, 0);

            if (effect_slot != 0) {
                AdjustPlayerHealth_pal(FloatToInt(*(float *)(effect_slot + 0x2C)));
            }
            if (g_hero_state.unk_24cc == 0) {
                hero_l19_set_move_state_pal(0x16, 1);
            }
            g_hero_state.unk_1dc = 0x40;
            if (g_hero_state.unk_21c == 0) {
                g_hero_state.unk_21c = 0xF;
            }
            hero_play_sound(0x14, 0);
            return 0;
        }
        if (g_hero_state.unk_229c == 0x12) {
            hero_l19_set_move_state_pal(0x72, 1);
        } else if (g_hero_state.unk_229c == 0x11) {
            hero_l19_set_move_state_pal(0x73, 1);
        } else if (entry->unk_24 & 8) {
            hero_l19_set_move_state_pal(0x8C, 1);
        } else {
            hero_l19_set_move_state_pal(0x16, 1);
        }
        if (g_hero_state.unk_2294 == 0x8C) {
            qzero(&vec);
        } else {
            hero_flatten_push_vector(&vec, flag, g_hero_state.unk_1497 ? 0.0f : 0.06600001f, 0.034f);
            if (flag != 0 && entry->unk_28 == 4) {
                cam_scale_view_space_height(&vec, &vec, 2.0f);
            }
        }
        break;
    case 4:
        hero_l19_set_move_state_pal(0x90, 1);
        hero_flatten_push_vector(&vec, flag, 0.10000001f, 0.060000002f);
        break;
    }
    FastVecAdd(&g_hero_state.unk_f0, &g_hero_state.unk_f0, &vec);
    FastVecAdd(&g_hero_state.unk_110, &g_hero_state.unk_110, &vec);
    return 1;
}


/* func_PAL_L19_002B6160, the PAL copy of func_L19_002B6278: the same C, where the
   ramp step 0.02f becomes 0.024f and the last call's 0.02f, 0.3f and 0.06666667f become
   0.028800001f, 0.43200004f and 0.080000006f. */
void hero_l19_update_speed_targets_pal(void) {
    int mode;
    int state;
    float distance;

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
        state = ((Hero *)&g_hero_state)->i[0x2294 / 4];
        if (state == 6) {
            ((Hero *)&g_hero_state)->f[0x25C / 4] = 0.5f;
        } else if (state == 4) {
            ((Hero *)&g_hero_state)->f[0x258 / 4] = 0.35000002384185791f;
        } else if ((u32)(mode - 0x11) < 2) {
            ((Hero *)&g_hero_state)->i[0x258 / 4] = 0;
            ((Hero *)&g_hero_state)->i[0x25C / 4] = 0;
        } else if (state == 0x7C) {
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

    distance = vec_distance_xy((u8 *)&g_hero_state + 0x240, (u8 *)&g_hero_state + 0x80);
    if (distance > ((Hero *)&g_hero_state)->f[0x264 / 4] * 0.5f)
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
