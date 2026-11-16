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
extern unsigned int stub_empty(int);
extern unsigned int stub_empty_8(int, int);
extern void stub_empty_12(int, int, float);
extern void hud_add_moby_marker(void *, float, u32, void *, int, float, int, float, int);
extern int CollLine(void *, void *, int, void *, void *);
extern void gfx_register_world_draw_callback(void (*)(char *), char *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern float fast_vec_dist(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void anim_start_blended(void *, int, int, int);
extern int PlayMobySound(int, int, char *);
extern s32 swingshot_hook_spawn(s32 arg0, f32 fparg0);
extern void gfx_draw_wavy_link_strip(char *);

/* Runs the swingshot's grapple hook: spawns the hook object, fires it at the target, and reels or releases it as the hero swings (v2.00 copy). */
void swingshot_update_us2(u8 *moby)
{
    FollowVars *follow;
    u8 *vars;
    f32 dist;
    f32 vec_a[4];
    f32 vec_b[4];

    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 1)
        stub_empty_8(0x1D, 1);
    follow = *(FollowVars **)(moby + 0x68);
    if (follow == 0)
        return;
    vars = 0;
    if (follow->target == 0) {
        follow->target = (u8 *)swingshot_hook_spawn((s32)moby, 0.8000001f);
        if (follow->target == 0)
            goto have;
    }
    vars = *(u8 **)(follow->target + 0x68);
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
                anim_start_blended(moby, 1, 0, 10);
            moby[0x20] = 1;
        }
        if (follow->target != 0) {
            u8 *hook;
            moby_transform_joint_to_world(moby, 0, follow->target + 0x10);
            hook = follow->target;
            *(TI128 *)(hook + 0xC0) = *(TI128 *)(moby + 0xC0);
            *(TI128 *)(hook + 0xD0) = *(TI128 *)(moby + 0xD0);
            *(TI128 *)(hook + 0xE0) = *(TI128 *)(moby + 0xE0);
        }
        if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x23 || (((Hero *)g_hero_state)->i[0x229C / 4] == 0xF && ((Hero *)g_hero_state)->i[0x684 / 4] != 0)) {
            if (vars != 0) {
                follow->f20 = 0.28f;
                follow->f1C = 1.0f;
                follow->f18 = 0.0f;
                *(f32 *)(vars + 4) = 0.8000001f;
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 10);
                PlayMobySound(0, 0, (char *)moby);
                moby[0x20] = 2;
            }
        } else if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x8A) {
            if (vars != 0) {
                follow->f20 = 0.28f;
                follow->f1C = 1.0f;
                follow->f18 = 0.0f;
                *(f32 *)(vars + 4) = 0.8000001f;
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 10);
                PlayMobySound(0, 0, (char *)moby);
                moby[0x20] = 0xF;
            }
        } else if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x2B) {
            if (vars != 0) {
                f32 hook_dist = fast_vec_dist(((Hero *)g_hero_state)->ptr[0xAD4 / 4] + 0x10, follow->target + 0x10);
                int step_count = 7;
                if (((Hero *)g_hero_state)->i[0x1240 / 4] <= 0x1D)
                    step_count = 5;
                *(f32 *)(vars + 4) = hook_dist / (f32)step_count;
                follow->f20 = 0.28f;
                follow->f1C = 1.0f;
                follow->f18 = 0.0f;
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 10);
                PlayMobySound(0, 0, (char *)moby);
                moby[0x20] = 9;
            }
        }
        break;
    case 2:
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended(moby, 4, 0, 10);
        FastVecSub(vec_a, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10, follow->target + 0x10);
        dist = *(f32 *)(vars + 4);
        dist += FastVecLength(&((Hero *)g_hero_state)->b[0x150]);
        if (((Hero *)g_hero_state)->i[0x229C / 4] == 0xF) {
            dist += ((Hero *)g_hero_state)->f[0x644 / 4];
        } else if ((((Hero *)g_hero_state)->i[0x22A4 / 4] == 4 || ((Hero *)g_hero_state)->i[0x22A4 / 4] == 2) && ((Hero *)g_hero_state)->f[0x31C / 4] > 2.0f) {
            dist = 0.8000001f;
        }
        qcopy(vec_b, &((Hero *)g_hero_state)->q[0x80 / 16]);
        vec_b[2] += 0.5f;
        if (CollLine(vec_b, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10, 2, 0, 0) != 0) {
            if (((Hero *)g_hero_state)->f[0x31C / 4] > 0.5f) {
                stub_empty_8(6, 1);
            } else {
                stub_empty_8(0, 0);
                stub_empty_12(stub_empty(0), 0, 14.0f);
            }
            moby[0x20] = 6;
        } else if (dist < fast_vec_dist(follow->target + 0x10, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10)) {
            vec_scale_to_length(vec_a, vec_a, dist);
            FastVecAdd(follow->target + 0x10, follow->target + 0x10, vec_a);
        } else {
            qcopy(follow->target + 0x10, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10);
            moby[0x20] = 3;
        }
        break;
    case 3:
        PlayMobySound(1, 0, (char *)moby);
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        qcopy(follow->target + 0x10, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10);
        moby[0x20] = 4;
        break;
    case 4:
        moby_transform_joint_to_world(moby, 0, vec_a);
        qcopy(vec_a, &((Hero *)g_hero_state)->q[0x80 / 16]);
        vec_a[2] += 0.5f;
        if (CollLine(vec_a, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10, 2, 0, 0) != 0) {
            if (((Hero *)g_hero_state)->h[0x34E / 2] != 0) {
                stub_empty_8(6, 1);
            } else {
                stub_empty_8(0, 1);
            }
            moby[0x20] = 6;
        } else {
            if ((moby[0x60] & 2) && moby[0x43] != 4)
                anim_start_blended(moby, 4, 0, 10);
            gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
            follow->f20 = follow->f20 * 0.9f;
            follow->f18 = follow->f18 + 0.6981318f;
            if (follow->f20 < 0.16800001f) {
                ((Hero *)g_hero_state)->i[0x684 / 4] = 0;
                if (follow->target != 0 && fast_vec_dist(follow->target + 0x10, &((Hero *)g_hero_state)->q[0x80 / 16]) > 3.5f) {
                    if ((g_pad_pressed_flags & ((Hero *)g_hero_state)->u[0x1230 / 4]) == 0) {
                        ((Hero *)g_hero_state)->i[0xAC8 / 4] = 1;
                        stub_empty_8(0, 0);
                        stub_empty_12(stub_empty(0), 0, 14.0f);
                        moby[0x20] = 6;
                    } else {
                        PlayMobySound(2, 0, (char *)moby);
                        if (((Hero *)g_hero_state)->i[0xAB8 / 4] != 0) {
                            stub_empty_8(0x25, 1);
                        } else {
                            stub_empty_8(0x24, 1);
                        }
                        moby[0x20] = 5;
                    }
                } else {
                    stub_empty_8(0, 1);
                    moby[0x20] = 6;
                }
            }
        }
        break;
    case 5:
        qcopy(follow->target + 0x10, ((Hero *)g_hero_state)->ptr[0xAA4 / 4] + 0x10);
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended(moby, 4, 0, 10);
        follow->f20 = follow->f20 * 0.9f;
        follow->f18 = follow->f18 + 0.6981318f;
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x24 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x25)
            moby[0x20] = 6;
        break;
    case 6:
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        *(f32 *)(vars + 4) = 1.3333334f;
        moby[0x20] = 7;
        break;
    case 7:
        moby_transform_joint_to_world(moby, 0, vec_b);
        FastVecSub(vec_a, vec_b, follow->target + 0x10);
        dist = *(f32 *)(vars + 4);
        dist += FastVecLength(&((Hero *)g_hero_state)->b[0x150]);
        if (dist < fast_vec_dist(follow->target + 0x10, vec_b)) {
            vec_scale_to_length(vec_a, vec_a, dist);
            FastVecAdd(follow->target + 0x10, follow->target + 0x10, vec_a);
            gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        } else {
            qcopy(follow->target + 0x10, vec_b);
            if (moby[0x43] != 1)
                anim_start_blended(moby, 1, 0, 10);
            moby[0x20] = 1;
        }
        break;
    case 9:
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended(moby, 4, 0, 10);
        FastVecSub(vec_a, ((Hero *)g_hero_state)->ptr[0xAD4 / 4] + 0x10, follow->target + 0x10);
        if (*(f32 *)(vars + 4) < FastVecLength(vec_a)) {
            vec_scale_to_length(vec_a, vec_a, *(f32 *)(vars + 4));
            FastVecAdd(follow->target + 0x10, follow->target + 0x10, vec_a);
        } else {
            qcopy(follow->target + 0x10, ((Hero *)g_hero_state)->ptr[0xAD4 / 4] + 0x10);
            moby[0x20] = 0xB;
            PlayMobySound(1, 0, (char *)moby);
        }
        break;
    case 10:
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        moby[0x20] = 0xB;
        break;
    case 11:
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended(moby, 4, 0, 10);
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        follow->f20 = follow->f20 * 0.39999998f;
        follow->f18 = follow->f18 + 0.6981318f;
        if (follow->f20 < 0.16800001f) {
            ((Hero *)g_hero_state)->h[0xADC / 2] = 1;
            moby[0x20] = 0xC;
        }
        break;
    case 12:
        if (((Hero *)g_hero_state)->ptr[0xAD4 / 4] != 0)
            qcopy(follow->target + 0x10, ((Hero *)g_hero_state)->ptr[0xAD4 / 4] + 0x10);
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended(moby, 4, 0, 10);
        follow->f20 = follow->f20 * 0.39999998f;
        follow->f18 = follow->f18 + 0.6981318f;
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x2B)
            moby[0x20] = 0xD;
        break;
    case 13:
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended(moby, 4, 0, 10);
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        *(f32 *)(vars + 4) = 1.3333334f;
        moby[0x20] = 0xE;
        break;
    case 14:
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended(moby, 4, 0, 10);
        moby_transform_joint_to_world(moby, 0, vec_b);
        FastVecSub(vec_a, vec_b, follow->target + 0x10);
        if (*(f32 *)(vars + 4) < fast_vec_dist(follow->target + 0x10, vec_b)) {
            vec_scale_to_length(vec_a, vec_a, *(f32 *)(vars + 4));
            FastVecAdd(follow->target + 0x10, follow->target + 0x10, vec_a);
            gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        } else {
            qcopy(follow->target + 0x10, vec_b);
            if (moby[0x43] != 1)
                anim_start_blended(moby, 1, 0, 10);
            moby[0x20] = 1;
        }
        if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x2B && vars != 0) {
            *(f32 *)(vars + 4) = fast_vec_dist(((Hero *)g_hero_state)->ptr[0xAD4 / 4] + 0x10, follow->target + 0x10) * 0.1f;
            follow->f1C = 1.0f;
            follow->f20 = 0.0f;
            follow->f18 = 0.0f;
            if (moby[0x43] != 3)
                anim_start_blended(moby, 3, 0, 10);
            moby[0x20] = 9;
        }
        break;
    case 15:
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended(moby, 4, 0, 10);
        qcopy(vec_a, &((Hero *)g_hero_state)->q[0x80 / 16]);
        vec_a[2] += 0.5f;
        if (CollLine(vec_a, ((Hero *)g_hero_state)->ptr[0xB10 / 4] + 0x10, 2, 0, 0) != 0) {
            if (((Hero *)g_hero_state)->f[0x31C / 4] > 0.5f) {
                stub_empty_8(6, 1);
            } else {
                stub_empty_8(0, 0);
                stub_empty_12(stub_empty(0), 0, 14.0f);
            }
            moby[0x20] = 0x13;
        } else {
            FastVecSub(vec_b, ((Hero *)g_hero_state)->ptr[0xB10 / 4] + 0x10, follow->target + 0x10);
            if (*(f32 *)(vars + 4) < FastVecLength(vec_b)) {
                vec_scale_to_length(vec_b, vec_b, *(f32 *)(vars + 4));
                FastVecAdd(follow->target + 0x10, follow->target + 0x10, vec_b);
            } else {
                qcopy(follow->target + 0x10, ((Hero *)g_hero_state)->ptr[0xB10 / 4] + 0x10);
                moby[0x20] = 0x11;
                PlayMobySound(1, 0, (char *)moby);
            }
        }
        break;
    case 16:
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        moby[0x20] = 0x11;
        break;
    case 17:
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended(moby, 4, 0, 10);
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        follow->f20 = follow->f20 * 0.39999998f;
        follow->f18 = follow->f18 + 0.6981318f;
        if (follow->f20 < 0.16800001f) {
            ((Hero *)g_hero_state)->i[0xB1C / 4] = 1;
            moby[0x20] = 0x12;
        }
        break;
    case 18:
        if (((Hero *)g_hero_state)->ptr[0xB10 / 4] != 0)
            qcopy(follow->target + 0x10, ((Hero *)g_hero_state)->ptr[0xB10 / 4] + 0x10);
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended(moby, 4, 0, 10);
        follow->f20 = follow->f20 * 0.39999998f;
        follow->f18 = follow->f18 + 0.6981318f;
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        if (((Hero *)g_hero_state)->i[0x229C / 4] != 0x21)
            moby[0x20] = 0x13;
        break;
    case 19:
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended(moby, 4, 0, 10);
        gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        *(f32 *)(vars + 4) = 1.3333334f;
        moby[0x20] = 0x14;
        break;
    case 20:
        if ((moby[0x60] & 2) && moby[0x43] != 4)
            anim_start_blended(moby, 4, 0, 10);
        moby_transform_joint_to_world(moby, 0, vec_b);
        FastVecSub(vec_a, vec_b, follow->target + 0x10);
        if (*(f32 *)(vars + 4) < fast_vec_dist(follow->target + 0x10, vec_b)) {
            vec_scale_to_length(vec_a, vec_a, *(f32 *)(vars + 4));
            FastVecAdd(follow->target + 0x10, follow->target + 0x10, vec_a);
            gfx_register_world_draw_callback(gfx_draw_wavy_link_strip, (char *)moby);
        } else {
            qcopy(follow->target + 0x10, vec_b);
            if (moby[0x43] != 1)
                anim_start_blended(moby, 1, 0, 10);
            moby[0x20] = 1;
        }
        if (((Hero *)g_hero_state)->i[0x229C / 4] == 0x21 && vars != 0) {
            *(f32 *)(vars + 4) = fast_vec_dist(((Hero *)g_hero_state)->ptr[0xB10 / 4] + 0x10, follow->target + 0x10) * 0.1f;
            follow->f1C = 1.0f;
            follow->f20 = 0.0f;
            follow->f18 = 0.0f;
            if (moby[0x43] != 3)
                anim_start_blended(moby, 3, 0, 10);
            moby[0x20] = 0xF;
        }
        break;
    case 21:
    default:
        break;
    }
}
