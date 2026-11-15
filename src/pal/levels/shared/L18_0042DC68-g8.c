#include "names.h"
/* func_PAL_L18_0042DC68, the PAL copy of func_L18_00428F08: the same C, with frame counts scaled to
 * 50 Hz, per-frame float rates multiplied by 6/5 or 36/25, and D_L18_001B1260 read as a word.  The
 * callback passed to func_PAL_0029C0F0 is a different function in level 20, hence its ref_ name. */
/* EE argument banks are independent; the interleaved call declaration agrees
 * with the matched motion callers and preserves each bank's argument order. */
#include "common.h"

typedef struct { int q __attribute__((mode(TI))); } Vec4;

extern int g_current_map_index MACRO_ADDR;
extern u8 D_0013965E[];
extern u8 g_sound_state[];
typedef union { u8 b[0x1000]; s16 h[0x800]; u16 uh[0x800]; s32 i[0x400]; u32 ui[0x400]; f32 f[0x400]; u8 *p[0x400]; } View;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *p[0x980]; } Hero;
extern u8 g_hero_state[];
extern u8 g_hero_position[];
extern u8 g_subtitle_history[];
extern u8 D_0019B2E8[];
extern u8 D_0019B4A8[];
extern u8 D_L18_001A8F20[] MACRO_ADDR;
extern s32 D_L18_001AFBB0 MACRO_ADDR;
extern float D_L18_001B1230 __attribute__((sda));
extern float D_L18_001B1238 __attribute__((sda));
extern s32 D_L18_001B1258 __attribute__((sda));
extern s32 D_L18_001B125C __attribute__((sda));
extern s32 D_L18_001B1260 __attribute__((sda));
extern s32 D_L18_001B1274 __attribute__((sda));
extern s32 D_L18_001B1278 __attribute__((sda));
extern s32 D_L18_001B127C __attribute__((sda));
extern s32 D_L18_001B1290 __attribute__((sda));
extern float D_L18_001B1294 __attribute__((sda));
extern float D_L18_001B1298 __attribute__((sda));
extern float D_L18_001B129C __attribute__((sda));
extern s32 D_L18_001B2564[] __attribute__((sda));
extern u8 D_L18_001B2660[] MACRO_ADDR;
extern s32 g_moby_l18_table MACRO_ADDR;
extern Vec4 g_camera_l18_position[];
extern u8 D_L18_0021DB40[][0x464];
extern u8 D_L18_0021E7B0[][0x464];
extern u8 D_L18_002571A0[];

extern s32 FastDecTimer(void *);
extern void mem_clear(void *, u32, s32);
extern void add_vectors(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern float IntToFloat(s32);
extern s32 func_PAL_00289730(s32, s32);
extern void func_PAL_0029C0F0(s32, void *);
extern void moby_mark_spawned(void *);
extern void func_PAL_002A7650(void *, s32, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void moby_set_state(void *, s32, s32);
extern s32 math_random_int_range(s32, s32);
extern float math_approach_target_with_direction_mode(void *out, float, void *in, s32, float, float, float);
extern void func_PAL_002AC3C0(void *, void *);
extern float math_wrap_angle_to_pi(float);
extern void func_PAL_002AC718(void *, void *, void *, float, float, s32, s32, s32, float, float,
                          float, float, s32, float, s32, s32, s32, s32, s32);
extern s32 moby_is_in_selected_zone(void *);
extern int TryClaimNotice(s32, s32, s32);
extern s32 moby_dispatch_action_by_kind(void *, void *);
extern s32 flag_set_second_pending(void *);
extern s32 func_PAL_002B5E10(void *);
extern int func_PAL_002B5E30(void *, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void snd_stop_voice(s32);
extern s32 snd_play_from_class_bank(s32, s32, void *, s32);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern void cam_set_mode_state(s32);
extern s32 func_001163B0(void);
extern s32 coll_point_inside_region(void *, s32);
extern s32 moby_fuse_linked_objects(void *, void *, void *, void *, s32);
extern int moby_aim_move_record_at_target(void *, void *, float, float);
extern s32 func_PAL_L07_00324F58(void *, float, float, float);
extern void func_PAL_L18_002CFC50(s32, s32, void *);
extern void func_PAL_L18_002CFE30(s32);
extern s32 moby_run_slot_handler(void *, s32, s32);
extern float path_find_best_point_by_id(void *, void *, void *, s32, float);
extern void ref_PAL_L18_0042DC68_00(void);
extern void moby_reset_color_grey(void *);
extern s32 shooter_is_enemy_alive(void *);
extern s32 moby_is_target_in_sight(void *, void *);
extern void func_PAL_L18_0042BA90(void *, s32, s32, float);
extern void moby_release_shared_resource(void *);
extern void moby_acquire_shared_resource(void *);
extern s32 moby_set_anim(void *, s32, s32);
extern void func_PAL_L18_0042BD70(void *);
extern void shooter_flag_group(void *, s32);
extern void func_PAL_L18_0042C768(void *);
extern void func_PAL_L18_0042CC40(void *);
extern s32 enemy_get_kind_index(void *);
extern int func_PAL_L18_0042D3B8(void *);
extern void func_PAL_L18_0042D7E0(void *);

void func_PAL_L18_0042DC68(u8 *a0) {
    float ref[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float ang[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    u8 *v;
    s32 sel;

    if (moby_is_in_selected_zone(a0 + 0x10) == 0)
        return;
    v = ((View *)a0)->p[0x68 / 4];
    func_PAL_L18_0042C768(a0);
    switch (((View *)a0)->b[0x95]) {
    case 1:
        if (((View *)a0)->b[0x42] == 0xD)
            ((View *)a0)->i[0x48 / 4] = 0;
        break;
    case 2:
        if (!(((View *)v)->b[0x399] & 1) && (((View *)v)->i[0x234 / 4] == 1 || ((View *)v)->h[0x390 / 2] != 0)
            && (shooter_is_enemy_alive(*(void **)(v + 0x230)) == 0
                || moby_is_target_in_sight(a0, *(void **)(v + 0x230)) != 0)) {
            shooter_flag_group(a0, ((View *)a0)->b[0x21]);
            ((View *)v)->i[0x37C / 4] = ((View *)v)->i[0x364 / 4];
            ((View *)v)->i[0x13C / 4] = ((View *)v)->i[0x384 / 4];
            ((View *)v)->h[0x392 / 2] = ((View *)v)->b[0x398];
            if (((View *)v)->i[0x368 / 4] != -1
                && (((View *)v)->i[0x3A4 / 4] == -1 || coll_point_inside_region(v + 0x220, ((View *)v)->i[0x3A4 / 4]) == 0)) {
                if (**(s32 **)(v + 0x3A8) == 0 && **(s32 **)(v + 0x3AC) < D_L18_001B127C) {
                    **(s32 **)(v + 0x3A8) = ((s32)math_random_int_range(D_L18_001B1274, D_L18_001B1278) * 5 + 2) / 6;
                    moby_acquire_shared_resource(a0);
                    moby_set_state(a0, 1, 4);
                }
            } else {
                moby_set_anim(a0, ((View *)v)->i[0x370 / 4], -1);
                moby_set_state(a0, 1, 3);
            }
        }
        break;
    case 3:
        if (((View *)v)->h[0x392 / 2] == 0) {
            func_PAL_L18_0042BA90(a0, 3, 0, 5.0f);
            if (((View *)v)->i[0x370 / 4] != -1) {
                moby_set_state(a0, 3, 5);
            } else {
                moby_set_anim(a0, ((View *)v)->i[0x374 / 4], -1);
                ((View *)v)->h[0x390 / 2] = ((s32)math_random_int_range(D_L18_001B1258, D_L18_001B125C) * 5 + 2) / 6;
                moby_set_state(a0, 3, 6);
            }
        }
        break;
    case 4:
        if (((View *)v)->h[0x392 / 2] == 0) {
            ((View *)a0)->b[0x31] = 1;
            ((View *)a0)->uh[0x34 / 2] &= ~1;
            path_find_best_point_by_id(ref, a0 + 0x10, g_hero_position, ((View *)v)->i[0x368 / 4], 0.0f);
            func_PAL_L18_0042BA90(a0, 6, 0, 5.0f);
            moby_aim_move_record_at_target(a0, ref, D_L18_001B1238 * 0.020000001f, D_L18_001B1230 * 0.00040000002f);
            moby_set_state(a0, 5, 10);
        }
        break;
    case 5:
        if (((View *)v)->i[0x234 / 4] == 1 && ((View *)v)->h[0x390 / 2] == 0)
            ((View *)v)->h[0x390 / 2] = ((s32)math_random_int_range(D_L18_001B1258, D_L18_001B125C) * 5 + 2) / 6;
        break;
    case 6:
        if ((((View *)v)->i[0x234 / 4] != 1 && ((View *)v)->h[0x390 / 2] == 0)
            || (((View *)v)->b[0x3B2] != 0 && ((View *)v)->b[0x3B3] == 0)
            || (((View *)v)->b[0x3B3] != 0 && (((View *)v)->p[0x230 / 4])[0xBC] == 0)) {
            ((View *)v)->h[0x390 / 2] = 0;
            func_PAL_L18_0042BA90(a0, (func_001163B0() & 1) | 4, 0, 10.0f);
            moby_set_state(a0, 2, 2);
        } else if (((View *)v)->b[0x3B0] == 0 && ((View *)v)->i[0x368 / 4] != -1 && ((View *)v)->i[0x3A4 / 4] != -1
                   && coll_point_inside_region(v + 0x220, ((View *)v)->i[0x3A4 / 4]) == 0
                   && **(s32 **)(v + 0x3A8) == 0 && **(s32 **)(v + 0x3AC) < D_L18_001B127C) {
            **(s32 **)(v + 0x3A8) = ((s32)math_random_int_range(D_L18_001B1274, D_L18_001B1278) * 5 + 2) / 6;
            moby_acquire_shared_resource(a0);
            moby_set_state(a0, 0, 4);
        }
        break;
    case 9: {
        s32 r = moby_dispatch_action_by_kind(a0, v + 0x50);

        if (r & 1) {
            func_PAL_002A7650(a0, 0, 3);
            moby_set_state(a0, 12, -1);
        } else if (r & 2) {
            ((View *)v)->h[0x390 / 2] = ((s32)math_random_int_range(D_L18_001B1258, D_L18_001B125C) * 5 + 2) / 6;
            shooter_flag_group(a0, ((View *)a0)->b[0x21]);
            if (((View *)a0)->b[0xBC] == 1) {
                func_PAL_L18_0042BA90(a0, 13, 0, 10.0f);
                moby_set_state(a0, 7, 8);
            } else {
                func_PAL_L18_0042BA90(a0, (func_001163B0() & 1) | 4, 0, 10.0f);
                moby_set_state(a0, 4, 6);
            }
        }
        break;
    }
    case 11: {
        s32 idx;
        u8 *m;

        ((View *)v)->f[0x100 / 4] = 0.699999988f;
        idx = ((View *)v)->i[0x3B4 / 4];
        if (idx != -1 && (m = (u8 *)((idx << 8) + g_moby_l18_table), *(s16 *)(m + 0xAA) == 0x114D)
            && m[0x20] != 0xFE && m[0x20] != 0xFD) {
            if (m[0xBC] == 0) {
                ((View *)a0)->b[0x23] = 0x80;
                ((View *)a0)->f[0x2C / 4] = *(float *)(((View *)a0)->p[0x24 / 4] + 0x24);
                ((View *)a0)->b[0x31] = 1;
                ((View *)a0)->uh[0x34 / 2] &= ~1;
                moby_set_state(a0, 0, 12);
            }
        } else {
            ((View *)a0)->b[0x31] = 1;
            ((View *)a0)->uh[0x34 / 2] &= ~1;
            moby_fuse_linked_objects(a0, a0 + 0x10, a0 + 0xF0, 0, 0);
            moby_set_state(a0, 0, 14);
        }
        break;
    }
    case 12: {
        u8 *m;

        *(Vec4 *)(a0 + 0x10) = *(Vec4 *)((u8 *)((((View *)v)->i[0x3B4 / 4] << 8) + g_moby_l18_table) + 0x10);
        m = (u8 *)((((View *)v)->i[0x3B4 / 4] << 8) + g_moby_l18_table);
        if (m[0xBC] == 2) {
            if (((View *)a0)->b[0x43] != 2)
                func_PAL_002A7E68(a0, 2, 0, 10);
            moby_set_state(a0, 4, 13);
        }
        break;
    }
    case 13:
        if (((u8 *)((((View *)v)->i[0x3B4 / 4] << 8) + g_moby_l18_table))[0xBC] == 3) {
            u8 *t = ((View *)a0)->p[0x24 / 4];

            ((View *)a0)->b[0x30] = ((View *)v)->b[0x3E0];
            ((View *)a0)->i[0x98 / 4] = *(s32 *)(t + 0x10);
            ((View *)a0)->uh[0x34 / 2] |= 0x1000;
            ((View *)a0)->f[0x2C / 4] = *(float *)(t + 0x24);
            ((View *)v)->h[0x392 / 2] = 0;
            if (((View *)a0)->h[0xAA / 2] == 0xED4)
                ((View *)v)->f[0x100 / 4] = 1.0f;
            if (((View *)a0)->h[0xAA / 2] == 0xEE1)
                ((View *)v)->f[0x100 / 4] = 1.10000002f;
            moby_set_state(a0, 2, 2);
        }
        break;
    case 14: {
        u8 *t = ((View *)a0)->p[0x24 / 4];

        ((View *)a0)->b[0x23] = 0x80;
        if (*(float *)(t + 0x24) <= ((View *)a0)->f[0x2C / 4]) {
            ((View *)a0)->b[0x30] = ((View *)v)->b[0x3E0];
            ((View *)a0)->i[0x98 / 4] = *(s32 *)(t + 0x10);
            ((View *)a0)->uh[0x34 / 2] |= 0x1000;
            ((View *)a0)->f[0x2C / 4] = *(float *)(t + 0x24);
            if (((View *)a0)->h[0xAA / 2] == 0xED4)
                ((View *)v)->f[0x100 / 4] = 1.0f;
            if (((View *)a0)->h[0xAA / 2] == 0xEE1)
                ((View *)v)->f[0x100 / 4] = 1.10000002f;
            if (((View *)v)->b[0x3E8] != 0) {
                if (((View *)a0)->b[0x43] != 13)
                    func_PAL_002A7E68(a0, 13, 0, 10);
                moby_set_state(a0, 0, 1);
            } else {
                ((View *)v)->h[0x392 / 2] = 0;
                moby_set_state(a0, 2, 2);
            }
        }
        break;
    }
    case 7: {
        s32 h;
        float f;
        float t;

        TryClaimNotice(6, 0, 20);
        if (flag_set_second_pending(a0) != 0)
            snd_play_from_class_bank(6, 0, a0, 0xEE1);
        if (((View *)v)->i[0x3F0 / 4] != -1) {
            u8 *e = g_sound_state + ((View *)v)->i[0x3F0 / 4] * 0x70;
            if (*(u8 **)(e + 0x88) == a0 && e[0x74] != 0)
                goto have;
        }
        ((View *)v)->i[0x3F0 / 4] = snd_play_from_class_bank(9, 4, a0, 0xEE1);
    have:
        func_PAL_002AC3C0(a0, v + 0x50);
        math_approach_target_with_direction_mode(a0 + 0xF8,
                      mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - ((View *)a0)->f[0x10 / 4],
                                    ((Hero *)g_hero_state)->f[0x84 / 4] - ((View *)a0)->f[0x14 / 4]),
                      v + 0x1B4, 0, ((View *)v)->f[0x114 / 4], ((View *)v)->f[0x118 / 4], ((View *)v)->f[0x11C / 4]);
        D_L18_001B2564[1] = 1;
        qcopy(ref, g_camera_l18_position);
        ((Hero *)g_hero_state)->h[0x1DC / 2] = 5;
        ((Hero *)g_hero_state)->h[0x1E0 / 2] = 8;
        if (FastDecTimer(v + 0x396) != 0) {
            func_PAL_0029C0F0(0, ref_PAL_L18_0042DC68_00);
            ((View *)v)->uh[0x3BC / 2] = ((s32)((View *)v)->h[0x3BE / 2] * 5 + 2) / 6;
            f = ((View *)a0)->f[0xF8 / 4];
            if (((Hero *)g_hero_state)->b[0x22B4] == 4) {
                if (g_current_map_index == 0x14)
                    D_0013965E[0] = 1;
                func_PAL_L18_002CFE30(1);
            }
            moby_reset_color_grey(a0);
            ((View *)a0)->b[0xBC] = 1;
            ((View *)v)->i[0x13C / 4] = -1;
            ((View *)v)->h[0x392 / 2] = 25;
            mem_clear(D_L18_002571A0, 0, 0x50);
            func_PAL_L18_002CFC50(4, 0x8D, a0);
            ((Hero *)g_hero_state)->f[0x98 / 4] = f;
            ((View *)a0)->f[0xF8 / 4] = f;
            D_L18_001B2564[1] = 0;
            if (g_current_map_index == 0x13) {
                if (((View *)g_subtitle_history)->uh[0x504 / 2] == 0)
                    func_PAL_00289730(0xA14, 0x6B);
                else
                    ((View *)g_subtitle_history)->uh[0x504 / 2] = 0xFFFF;
            }
            D_L18_001AFBB0 = 0;
            moby_set_state(a0, 7, 8);
            h = ((View *)v)->i[0x3F0 / 4];
            if (h != -1) {
                u8 *e = g_sound_state + h * 0x70;
                if (*(u8 **)(e + 0x88) == a0 && e[0x74] != 0)
                    snd_stop_voice(h);
            }
            ((View *)v)->i[0x3F0 / 4] = -1;
        }
        t = 1.0f - IntToFloat(((View *)v)->h[0x396 / 2]) / (float)(((s32)D_L18_001B1290 * 5 + 2) / 6);
        if (t > 1.0f)
            t = 1.0f;
        else if (t < 0.0f)
            t = 0.0f;
        FastVecSub(c, g_hero_position, a0 + 0x10);
        *(Vec4 *)b = *(Vec4 *)c;
        b[2] = 0.0f;
        vec_scale_to_length(b, b, D_L18_001B1294);
        add_vectors(c, b, a0 + 0x10);
        b[2] += D_L18_001B1298;
        FastVecSub(c, ref, b);
        *(Vec4 *)a = *(Vec4 *)c;
        vec_scale_to_length(a, a, ((View *)v)->f[0x3B8 / 4] * IntToFloat(((View *)v)->h[0x396 / 2]));
        add_vectors(c, a, b);
        ang[2] = mat_fast_helper_a(((View *)a0)->f[0x10 / 4] - a[0], ((View *)a0)->f[0x14 / 4] - a[1]);
        ang[1] = -mat_fast_helper_a(vec_distance_xy(a, a0 + 0x10), ((View *)a0)->f[0x18 / 4] - a[2]);
        ang[0] = D_L18_001B129C * (math_fast_sin_or_cos_b(math_wrap_angle_to_pi(t * 6.28318548f)) * 0.0174532942f);
        object_copy_vector_to_selected(a);
        cam_set_state_rotation(ang);
        if (((View *)a0)->b[0x95] == 8)
            cam_set_mode_state(1);
        break;
    }
    case 8:
        TryClaimNotice(6, 0, 20);
        if ((((Hero *)g_hero_state)->b[0x22B4] != 4 || ((Hero *)g_hero_state)->p[0x2290 / 4] != a0) && ((View *)v)->h[0x392 / 2] == 0) {
            if (((Hero *)g_hero_state)->b[0x22B4] != 4)
                func_PAL_0029C0F0(0, 0);
            D_L18_001AFBB0 = 0;
            ((View *)v)->i[0x13C / 4] = ((View *)v)->i[0x384 / 4];
            ((View *)v)->i[0x37C / 4] = ((View *)v)->i[0x360 / 4];
            ((View *)v)->i[0x38C / 4] = -1;
            ((View *)a0)->b[0xBC] = 0;
            moby_set_controller_speed_limits(a0, ((View *)v)->f[0x3C4 / 4] * 0.00040000002f, ((View *)v)->f[0x3C0 / 4] * 0.020000001f,
                          ((View *)v)->f[0x3D4 / 4] * 6.981318e-06f, ((View *)v)->f[0x3D0 / 4] * 0.0003490659f);
            ((View *)a0)->uh[0x34 / 2] &= 0xFFBE;
            sel = enemy_get_kind_index(a0);
            func_PAL_002AC718(a0, D_L18_001A8F20, 0, 2.0f, (float)((View *)v)->b[0x35], 5, 2, 9, 6.0f, 4.0f, 9.0f, 1.10000002f,
                          sel, 0.0f, 1, 1, -2, 0, 0x850001);
            moby_set_state(a0, 11, -1);
        }
        break;
    }

    switch (((View *)a0)->b[0x20]) {
    case 1:
        func_PAL_002B5E30(a0, mat_fast_helper_a(((View *)v)->f[0x220 / 4] - ((View *)a0)->f[0x10 / 4],
                                        ((View *)v)->f[0x224 / 4] - ((View *)a0)->f[0x14 / 4]));
        break;
    case 2:
        func_PAL_002B5E10(a0);
        if (((View *)v)->h[0x392 / 2] == 0) {
            ((View *)v)->h[0x392 / 2] = ((s32)D_L18_001B1260 * 5 + 2) / 6;
            func_PAL_L18_0042BA90(a0, 2, 0, 10.0f);
            moby_set_state(a0, 4, -1);
        }
        break;
    case 3:
        math_approach_target_with_direction_mode(a0 + 0xF8,
                      mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - ((View *)a0)->f[0x10 / 4],
                                    ((Hero *)g_hero_state)->f[0x84 / 4] - ((View *)a0)->f[0x14 / 4]),
                      v + 0x1B4, 0, ((View *)v)->f[0x114 / 4], ((View *)v)->f[0x118 / 4], ((View *)v)->f[0x11C / 4]);
        if (((View *)a0)->b[0x60] & 2) {
            func_PAL_L18_0042BA90(a0, 2, 0, 10.0f);
            moby_set_state(a0, 4, -1);
        }
        break;
    case 4:
        func_PAL_L18_0042D7E0(a0);
        break;
    case 5:
        if (func_PAL_L07_00324F58(a0, 7.0f, 32.0f, 37.0f) != 0) {
            if (moby_run_slot_handler(a0 + 0x10, ((View *)v)->i[0x380 / 4], 0) != 0) {
                ((View *)v)->h[0x392 / 2] = 0;
                moby_set_state(a0, 0, 4);
            } else {
                s32 n;

                func_PAL_L18_0042BA90(a0, 2, 0, 10.0f);
                n = ((View *)v)->i[0x370 / 4];
                if (n != -1) {
                    moby_set_anim(a0, n, -1);
                    moby_set_state(a0, 4, 5);
                } else {
                    if (((View *)v)->i[0x374 / 4] != -1)
                        moby_set_anim(a0, ((View *)v)->i[0x374 / 4], -1);
                    else
                        ((View *)v)->i[0x38C / 4] = -1;
                    moby_set_state(a0, 4, 6);
                }
            }
        }
        break;
    case 6:
        func_PAL_L18_0042D3B8(a0);
        break;
    case 12:
        sel = enemy_get_kind_index(a0);
        func_PAL_002AC718(a0, D_L18_001A8F20, 0, 0.0f, 0.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f,
                      sel, 15.0f, 1, 1, -1, 0, 0x810001);
    case 11: {
        u16 b2;
        u8 *p;
        u8 c;

        moby_release_shared_resource(a0);
        b2 = ((View *)a0)->uh[0xB2 / 2];
        if (b2 & 1) {
            u8 *q = D_0019B4A8 + (((s16)b2 >> 1) + (g_current_map_index << 10));
            if (((*q >> 4) & 7) != 7)
                *q += 0x10;
        } else {
            u8 *q = D_0019B4A8 + (((s16)b2 >> 1) + (g_current_map_index << 10));
            if ((*q & 7) != 7)
                *q += 1;
        }
        D_L18_0021DB40[1][((View *)a0)->h[0xB2 / 2]] = ((View *)a0)->b[0xB0] + 2;
        if (((View *)a0)->b[0xB0] == 0xFF || (!(D_L18_001B2660[((View *)a0)->b[0xB0]] & 0x80) && (D_0019B2E8[((View *)a0)->b[0xB0] + (g_current_map_index << 4)] & 0x80)))
            D_L18_0021E7B0[1][((View *)a0)->h[0xB2 / 2]] = ((View *)a0)->b[0xB0] + 2;
        c = ((View *)v)->b[0x3B1];
        if (c != 0 && c != 0xFE
            && (((View *)a0)->b[0xB0] == 0xFF || !(D_0019B2E8[((View *)a0)->b[0xB0] + (g_current_map_index << 4)] & 0x80))) {
            func_PAL_L18_0042BD70(a0);
        } else {
            moby_mark_spawned(a0);
            return;
        }
        break;
    }
    }
    func_PAL_L18_0042CC40(a0);
}
