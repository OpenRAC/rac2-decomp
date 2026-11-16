#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;
typedef struct {
    u8 pad0[0x14];
    u8 *target;
    f32 f18;
    f32 f1C;
    f32 f20;
} FollowVars;
extern char g_hero_state[];
extern u32 g_pad_pressed_flags;
extern unsigned int shop_get_entry_for_state(int);
extern unsigned int hero_l22_set_action_pal(int, int);
extern void set_hero_animation_pal(int, int, float);
extern void hud_add_moby_marker(void *, float, u32, void *, int, float, int, float, int);
extern int CollLine(void *, void *, int, void *, void *);
extern void gfx_add_draw_callback_first(void (*)(char *), char *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern float fast_vec_dist(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern int PlayMobySound(int, int, char *);
extern s32 swingshot_hook_spawn_pal(s32 arg0, f32 fparg0);
extern void DrawWavyLinkStrip(char *);

/* Updates a swingshot target moby: spawns its hook, shows the hero's markers on it and steps its
   state machine as the hero fires, swings and releases the hook. (PAL: 50 Hz timings) */
void swingshot_l22_node_update_pal(u8 *moby)
{
    FollowVars *data;
    u8 *vars;
    f32 dist;
    f32 link_vec[4];
    f32 probe_pos[4];

    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 1)
        hero_l22_set_action_pal(0x1D, 1);
    data = *(FollowVars **)(moby + 0x68);
    if (data == 0)
        return;
    vars = 0;
    if (data->target == 0) {
        data->target = (u8 *)swingshot_hook_spawn_pal((s32)moby, 0.96000004f);
        if (data->target == 0)
            goto have;
    }
    vars = *(u8 **)(data->target + 0x68);
have:
    if ((((Hero *)g_hero_state)->i[0x2294 / 4] == 1 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x1D) && ((Hero *)g_hero_state)->i[0x1B8 / 4] >= 2) {
        hud_add_moby_marker(moby, 1.0f, 0xFF0000FF, 0, 0x24, 0.0f, -1, 90.0f, 4);
        if (((Hero *)g_hero_state)->i[0xAA8 / 4] != 0 && ((Hero *)g_hero_state)->ptr[0xAA4 / 4] != 0)
            hud_add_moby_marker(moby, 1.4f, 0xFFFF0000, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10, 0x24, 0.0f, -1, 90.0f, 4);
        else if (((Hero *)g_hero_state)->ptr[0xAD0 / 4] != 0)
            hud_add_moby_marker(moby, 1.4f, 0xFFFF0000, ((Hero *)g_hero_state)->ptr[0xAD0 / 4] + 0x10, 0x24, 0.0f, -1, 90.0f, 4);
    }

    switch (moby[0x20]) {
    case 0:
    case 1:
        if (moby[0x60] & 2) {
            if (moby[0x43] != 1)
                anim_start_blended_pal(moby, 1, 0, 8);
            moby[0x20] = 1;
        }
        if (data->target != 0) {
            u8 *hook;
            moby_transform_joint_to_world(moby, 0, data->target + 0x10);
            hook = data->target;
            *(TI128 *)(hook + 0xC0) = *(TI128 *)(moby + 0xC0);
            *(TI128 *)(hook + 0xD0) = *(TI128 *)(moby + 0xD0);
            *(TI128 *)(hook + 0xE0) = *(TI128 *)(moby + 0xE0);
        }
        if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x23 || (((Hero *)g_hero_state)->i[0x229C / 4] == 0xF && ((Hero *)g_hero_state)->i[0x684 / 4] != 0)) {
            if (vars != 0) {
                data->f20 = 0.28f;
                data->f1C = 1.0f;
                data->f18 = 0.0f;
                *(f32 *)(vars + 4) = 0.96000004f;
                if (moby[0x43] != 3)
                    anim_start_blended_pal(moby, 3, 0, 8);
                PlayMobySound(0, 0, (char *)moby);
                moby[0x20] = 2;
            }
        } else if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x8A) {
            if (vars != 0) {
                data->f20 = 0.28f;
                data->f1C = 1.0f;
                data->f18 = 0.0f;
                *(f32 *)(vars + 4) = 0.96000004f;
                if (moby[0x43] != 3)
                    anim_start_blended_pal(moby, 3, 0, 8);
                PlayMobySound(0, 0, (char *)moby);
                moby[0x20] = 0xF;
            }
        } else if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x2B) {
            if (vars != 0) {
                f32 hook_dist = fast_vec_dist(((Hero *)g_hero_state)->ptr[0xAD4 / 4] + 0x10, data->target + 0x10);
                int divisor = 6;
                if (((Hero *)g_hero_state)->i[0x1240 / 4] <= 0x18)
                    divisor = 4;
                *(f32 *)(vars + 4) = hook_dist / (f32)divisor;
                data->f20 = 0.28f;
                data->f1C = 1.0f;
                data->f18 = 0.0f;
                if (moby[0x43] != 3)
                    anim_start_blended_pal(moby, 3, 0, 8);
                PlayMobySound(0, 0, (char *)moby);
                moby[0x20] = 9;
            }
        }
        break;
    case 2:
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended_pal(moby, 4, 0, 8);
        FastVecSub(link_vec, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10, data->target + 0x10);
        dist = *(f32 *)(vars + 4);
        dist += FastVecLength(&((Hero *)g_hero_state)->b[0x150]);
        if (((Hero *)g_hero_state)->i[0x229C / 4] == 0xF) {
            dist += ((Hero *)g_hero_state)->f[0x644 / 4];
        } else if ((((Hero *)g_hero_state)->i[0x22A4 / 4] == 4 || ((Hero *)g_hero_state)->i[0x22A4 / 4] == 2) && ((Hero *)g_hero_state)->f[0x31C / 4] > 2.0f) {
            dist = 0.96000004f;
        }
        qcopy(probe_pos, &((Hero *)g_hero_state)->q[0x80 / 16]);
        probe_pos[2] += 0.5f;
        if (CollLine(probe_pos, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10, 2, 0, 0) != 0) {
            if (((Hero *)g_hero_state)->f[0x31C / 4] > 0.5f) {
                hero_l22_set_action_pal(6, 1);
            } else {
                hero_l22_set_action_pal(0, 0);
                set_hero_animation_pal(shop_get_entry_for_state(0), 0, 12.0f);
            }
            moby[0x20] = 6;
        } else if (dist < fast_vec_dist(data->target + 0x10, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10)) {
            vec_scale_to_length(link_vec, link_vec, dist);
            FastVecAdd(data->target + 0x10, data->target + 0x10, link_vec);
        } else {
            qcopy(data->target + 0x10, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10);
            moby[0x20] = 3;
        }
        break;
    case 3:
        PlayMobySound(1, 0, (char *)moby);
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        qcopy(data->target + 0x10, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10);
        moby[0x20] = 4;
        break;
    case 4:
        moby_transform_joint_to_world(moby, 0, link_vec);
        qcopy(link_vec, &((Hero *)g_hero_state)->q[0x80 / 16]);
        link_vec[2] += 0.5f;
        if (CollLine(link_vec, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10, 2, 0, 0) != 0) {
            if (((Hero *)g_hero_state)->h[0x34E / 2] != 0) {
                hero_l22_set_action_pal(6, 1);
            } else {
                hero_l22_set_action_pal(0, 1);
            }
            moby[0x20] = 6;
        } else {
            if ((moby[0x60] & 2) && moby[0x43] != 4)
                anim_start_blended_pal(moby, 4, 0, 8);
            gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
            data->f20 = data->f20 * 0.88f;
            data->f18 = data->f18 + 0.6981318f;
            if (data->f20 < 0.16800001f) {
                ((Hero *)g_hero_state)->i[0x684 / 4] = 0;
                if (data->target != 0 && fast_vec_dist(data->target + 0x10, &((Hero *)g_hero_state)->q[0x80 / 16]) > 3.5f) {
                    if ((g_pad_pressed_flags & ((Hero *)g_hero_state)->u[0x1230 / 4]) == 0) {
                        ((Hero *)g_hero_state)->i[0xAC8 / 4] = 1;
                        hero_l22_set_action_pal(0, 0);
                        set_hero_animation_pal(shop_get_entry_for_state(0), 0, 12.0f);
                        moby[0x20] = 6;
                    } else {
                        PlayMobySound(2, 0, (char *)moby);
                        if (((Hero *)g_hero_state)->i[0xAB8 / 4] != 0) {
                            hero_l22_set_action_pal(0x25, 1);
                        } else {
                            hero_l22_set_action_pal(0x24, 1);
                        }
                        moby[0x20] = 5;
                    }
                } else {
                    hero_l22_set_action_pal(0, 1);
                    moby[0x20] = 6;
                }
            }
        }
        break;
    case 5:
        qcopy(data->target + 0x10, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10);
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended_pal(moby, 4, 0, 8);
        data->f20 = data->f20 * 0.88f;
        data->f18 = data->f18 + 0.6981318f;
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x24 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x25)
            moby[0x20] = 6;
        break;
    case 6:
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        *(f32 *)(vars + 4) = 1.6000001f;
        moby[0x20] = 7;
        break;
    case 7:
        moby_transform_joint_to_world(moby, 0, probe_pos);
        FastVecSub(link_vec, probe_pos, data->target + 0x10);
        dist = *(f32 *)(vars + 4);
        dist += FastVecLength(&((Hero *)g_hero_state)->b[0x150]);
        if (dist < fast_vec_dist(data->target + 0x10, probe_pos)) {
            vec_scale_to_length(link_vec, link_vec, dist);
            FastVecAdd(data->target + 0x10, data->target + 0x10, link_vec);
            gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        } else {
            qcopy(data->target + 0x10, probe_pos);
            if (moby[0x43] != 1)
                anim_start_blended_pal(moby, 1, 0, 8);
            moby[0x20] = 1;
        }
        break;
    case 9:
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended_pal(moby, 4, 0, 8);
        FastVecSub(link_vec, ((Hero *)g_hero_state)->ptr[0xAD4 / 4] + 0x10, data->target + 0x10);
        if (*(f32 *)(vars + 4) < FastVecLength(link_vec)) {
            vec_scale_to_length(link_vec, link_vec, *(f32 *)(vars + 4));
            FastVecAdd(data->target + 0x10, data->target + 0x10, link_vec);
        } else {
            qcopy(data->target + 0x10, ((Hero *)g_hero_state)->ptr[0xAD4 / 4] + 0x10);
            moby[0x20] = 0xB;
            PlayMobySound(1, 0, (char *)moby);
        }
        break;
    case 10:
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        moby[0x20] = 0xB;
        break;
    case 11:
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended_pal(moby, 4, 0, 8);
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        data->f20 = data->f20 * 0.27999997f;
        data->f18 = data->f18 + 0.6981318f;
        if (data->f20 < 0.16800001f) {
            ((Hero *)g_hero_state)->h[0xADC / 2] = 1;
            moby[0x20] = 0xC;
        }
        break;
    case 12:
        if (((Hero *)g_hero_state)->ptr[0xAD4 / 4] != 0)
            qcopy(data->target + 0x10, ((Hero *)g_hero_state)->ptr[0xAD4 / 4] + 0x10);
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended_pal(moby, 4, 0, 8);
        data->f20 = data->f20 * 0.27999997f;
        data->f18 = data->f18 + 0.6981318f;
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x2B)
            moby[0x20] = 0xD;
        break;
    case 13:
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended_pal(moby, 4, 0, 8);
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        *(f32 *)(vars + 4) = 1.6000001f;
        moby[0x20] = 0xE;
        break;
    case 14:
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended_pal(moby, 4, 0, 8);
        moby_transform_joint_to_world(moby, 0, probe_pos);
        FastVecSub(link_vec, probe_pos, data->target + 0x10);
        if (*(f32 *)(vars + 4) < fast_vec_dist(data->target + 0x10, probe_pos)) {
            vec_scale_to_length(link_vec, link_vec, *(f32 *)(vars + 4));
            FastVecAdd(data->target + 0x10, data->target + 0x10, link_vec);
            gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        } else {
            qcopy(data->target + 0x10, probe_pos);
            if (moby[0x43] != 1)
                anim_start_blended_pal(moby, 1, 0, 8);
            moby[0x20] = 1;
        }
        if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x2B && vars != 0) {
            *(f32 *)(vars + 4) = fast_vec_dist(((Hero *)g_hero_state)->ptr[0xAD4 / 4] + 0x10, data->target + 0x10) * 0.1f;
            data->f1C = 1.0f;
            data->f20 = 0.0f;
            data->f18 = 0.0f;
            if (moby[0x43] != 3)
                anim_start_blended_pal(moby, 3, 0, 8);
            moby[0x20] = 9;
        }
        break;
    case 15:
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended_pal(moby, 4, 0, 8);
        qcopy(link_vec, &((Hero *)g_hero_state)->q[0x80 / 16]);
        link_vec[2] += 0.5f;
        if (CollLine(link_vec, ((Hero *)g_hero_state)->ptr[0xB10 / 4] + 0x10, 2, 0, 0) != 0) {
            if (((Hero *)g_hero_state)->f[0x31C / 4] > 0.5f) {
                hero_l22_set_action_pal(6, 1);
            } else {
                hero_l22_set_action_pal(0, 0);
                set_hero_animation_pal(shop_get_entry_for_state(0), 0, 12.0f);
            }
            moby[0x20] = 0x13;
        } else {
            FastVecSub(probe_pos, ((Hero *)g_hero_state)->ptr[0xB10 / 4] + 0x10, data->target + 0x10);
            if (*(f32 *)(vars + 4) < FastVecLength(probe_pos)) {
                vec_scale_to_length(probe_pos, probe_pos, *(f32 *)(vars + 4));
                FastVecAdd(data->target + 0x10, data->target + 0x10, probe_pos);
            } else {
                qcopy(data->target + 0x10, ((Hero *)g_hero_state)->ptr[0xB10 / 4] + 0x10);
                moby[0x20] = 0x11;
                PlayMobySound(1, 0, (char *)moby);
            }
        }
        break;
    case 16:
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        moby[0x20] = 0x11;
        break;
    case 17:
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended_pal(moby, 4, 0, 8);
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        data->f20 = data->f20 * 0.27999997f;
        data->f18 = data->f18 + 0.6981318f;
        if (data->f20 < 0.16800001f) {
            ((Hero *)g_hero_state)->i[0xB1C / 4] = 1;
            moby[0x20] = 0x12;
        }
        break;
    case 18:
        if (((Hero *)g_hero_state)->ptr[0xB10 / 4] != 0)
            qcopy(data->target + 0x10, ((Hero *)g_hero_state)->ptr[0xB10 / 4] + 0x10);
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended_pal(moby, 4, 0, 8);
        data->f20 = data->f20 * 0.27999997f;
        data->f18 = data->f18 + 0.6981318f;
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        if (((Hero *)g_hero_state)->i[0x229C / 4] != 0x21)
            moby[0x20] = 0x13;
        break;
    case 19:
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended_pal(moby, 4, 0, 8);
        gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        *(f32 *)(vars + 4) = 1.6000001f;
        moby[0x20] = 0x14;
        break;
    case 20:
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended_pal(moby, 4, 0, 8);
        moby_transform_joint_to_world(moby, 0, probe_pos);
        FastVecSub(link_vec, probe_pos, data->target + 0x10);
        if (*(f32 *)(vars + 4) < fast_vec_dist(data->target + 0x10, probe_pos)) {
            vec_scale_to_length(link_vec, link_vec, *(f32 *)(vars + 4));
            FastVecAdd(data->target + 0x10, data->target + 0x10, link_vec);
            gfx_add_draw_callback_first(DrawWavyLinkStrip, (char *)moby);
        } else {
            qcopy(data->target + 0x10, probe_pos);
            if (moby[0x43] != 1)
                anim_start_blended_pal(moby, 1, 0, 8);
            moby[0x20] = 1;
        }
        if (((Hero *)g_hero_state)->i[0x229C / 4] == 0x21 && vars != 0) {
            *(f32 *)(vars + 4) = fast_vec_dist(((Hero *)g_hero_state)->ptr[0xB10 / 4] + 0x10, data->target + 0x10) * 0.1f;
            data->f1C = 1.0f;
            data->f20 = 0.0f;
            data->f18 = 0.0f;
            if (moby[0x43] != 3)
                anim_start_blended_pal(moby, 3, 0, 8);
            moby[0x20] = 0xF;
        }
        break;
    case 21:
    default:
        break;
    }
}
