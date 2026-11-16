#include "include_asm.h"

#include "common.h"
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define B(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))
#define U(p, o) (*(unsigned short *)((char *)(p) + (o)))
typedef struct {
    char pre[0x80];
    float x, y;
    char pad[0x154];
    short timer;
    char pad2[0x15e];
    char *target;
    int active;
    char pad3[0x14ec];
    char *owner;
    char pad4[0xa60];
    int mode;
    char pad5[0x234];
    int flag;
} Global;
extern Global g_hero_state;
extern char g_turret_debris_vectors[];
typedef struct {
    char pre[0x74];
    unsigned char active;
    char pad[0x13];
    char *owner;
} Effect;
extern char g_sound_state[];
extern int g_snivelak_voice_cue_count, g_pad_held_flags __attribute__((nosda));
extern unsigned short g_turret_stage_value __attribute__((nosda)), g_turret_target_id __attribute__((nosda));
extern char *g_moby_instance_table;
extern int g_snivelak_target, g_snivelak_turret_state;
extern int g_snivelak_turret_timer __attribute__((sda));
extern int g_turret_local_offset __attribute__((sda));
extern float g_turret_angle_offset __attribute__((sda)), g_turret_hero_range __attribute__((sda));
extern void moby_mark_spawned(char *), moby_set_state(char *, int, int);
extern float coll_get_ground_distance_below(char *, char *, char *);
extern void matrix_mul_vec3(char *, char *, char *), FastVecAdd(char *, char *, char *);
extern int func_PAL_00289730(int, int);
extern int flag_set_first_pending(char *), PlayMobySound(int, int, char *);
extern void hero_reset_position_and_direction_pal(char *, char *, int, int), SetCamera5Pose(char *, char *, int, int, int);
extern float math_fabs(float), vec_distance_xy(char *, char *), mat_fast_helper_a(float, float), FastAddRotations(float, float), fast_subtract_rotations(float, float), FastDiffRots(float, float);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern f32 math_approach_target_with_direction_mode(float *, float *, float, float, float, float, int);
extern void snd_stop_voice(int), turret_set_camera_matrices(char *), func_PAL_L16_0041C1F0(char *), cam_update_turret_follow(char *), func_PAL_L16_0041C470(char *), turret_reset_camera_state(char *), func_PAL_L16_0041BF40(char *);
extern void hud_add_moby_marker(char *, unsigned, int, int, int, int, float, float, float);
extern char *part_find_owned_effect_slot(char *, int, int);
extern void AdjustPlayerHealth_pal(int), module_l00_call_handler_with_arg_4_pal(int);
extern f32 ApproachValue(float *, float, float);
extern int FloatToInt(float);

void func_PAL_L16_0041B7E8(char *self) {
    char buf[16];
    char *st = P(self, 0x68), *hit;
    float angle;
    int state;
    Global *g;
    switch (B(self, 0x20)) {
    case 0:
        if (I(st, 0x60) == -1) {
            moby_mark_spawned(self);
            return;
        }
        coll_get_ground_distance_below(self + 0x10, self, self + 0x10);
        U(self, 0x34) |= 0x4000;
        qcopy(st + 0x70, self + 0x10);
        F(st, 0x7c) = F(self, 0xf8);
        F(st, 0x94) = 4.0f;
        moby_set_state(self, 1, -1);
        if (g_snivelak_voice_cue_count >= 2 && g_turret_stage_value < 3)
            func_PAL_00289730(0xa0b, 0x62);
        break;
    case 1:
    case 4:
        if (flag_set_first_pending(self))
            PlayMobySound(3, 0, self);
        state = B(self, 0x20);
        if ((state == 4 && g_hero_state.target != self) || ((g = &g_hero_state), H(g, 0x34e) >= 17))
            B(self, 0x20) = 1;
        else if (state == 1 && g->target == self && g->active) {
            matrix_mul_vec3(buf, (char *)&g_turret_local_offset, self + 0xc0);
            FastVecAdd(buf, buf, self + 0x10);
            hero_reset_position_and_direction_pal(buf, self + 0xf0, 0x31, 0);
            g_hero_state.owner = self;
            SetCamera5Pose(g_turret_debris_vectors, g_turret_debris_vectors + 0x10, 3, 60, 0);
            g_turret_target_id = 0xffff;
            g_snivelak_target = (int)self;
            moby_set_state(self, 2, -1);
            break;
        }
        if (math_fabs(F(self, 0x18) - F(st, 0x78) + g_turret_angle_offset) > 0.01f)
            math_step_value_toward_target((float *)(self + 0x18), (float *)(st + 0x98), F(st, 0x78) - g_turret_angle_offset, 0.00080000004f, 0.00080000004f, 0.040000003f);
        if (vec_distance_xy(self + 0x10, (char *)&g_hero_state.x) > g_turret_hero_range) {
            angle = FastAddRotations(mat_fast_helper_a(g_hero_state.x - F(self, 0x10), g_hero_state.y - F(self, 0x14)), 3.1415927410125732f);
            math_approach_target_with_direction_mode((float *)(self + 0xf8), (float *)(st + 0x9c), angle, 0.0025132746f, 0.0025132746f, 0.12566373f, 0);
        }
        break;
    case 2:
        if (flag_set_first_pending(self)) {
            PlayMobySound(3, 0, self);
            I(st, 0x90) = 0;
        }
        angle = mat_fast_helper_a(F((char *)((I(st, 0x64) << 8) + (int)g_moby_instance_table), 0x10) - F(self, 0x10), F((char *)((I(st, 0x64) << 8) + (int)g_moby_instance_table), 0x14) - F(self, 0x14));
        math_step_value_toward_target((float *)(self + 0x18), (float *)(st + 0x98), F(st, 0x78), 0.0024f, 0.0024f, 0.120000005f);
        math_approach_target_with_direction_mode((float *)(self + 0xf8), (float *)(st + 0x9c), angle, 0.0016755164f, 0.0016755164f, 0.12566373f, 0);
        if (math_fabs(fast_subtract_rotations(F(self, 0xf8), angle)) < 0.174532949924469f) {
            if (I(st, 0xa4) != -1) {
                Effect *effect = (Effect *)(I(st, 0xa4) * 0x70 + (int)g_sound_state);
                if (effect->owner == self && effect->active)
                    snd_stop_voice(I(st, 0xa4));
            }
            I(st, 0xa4) = -1;
        } else {
            Effect *effect = (Effect *)(I(st, 0xa4) * 0x70 + (int)g_sound_state);
            if (effect->owner != self || !effect->active) I(st, 0xa4) =
                PlayMobySound(4, 4, self);
        }
        if (math_fabs(F(self, 0x18) - F(st, 0x78)) <= F(st, 0x98) && FastDiffRots(F(self, 0xf8), angle) <= 0.0872664749622345f)
            moby_set_state(self, 3, -1);
        g_turret_target_id = 0xffff;
        turret_set_camera_matrices(self);
        func_PAL_L16_0041C1F0(self);
        cam_update_turret_follow(self);
        break;
    case 5:
    case 6:
        break;
    case 3:
        hud_add_moby_marker(self, 0x600fff0f, 0, 0x26, -1, 4, 1.0f, 0.0f, 90.0f);
        if ((g_pad_held_flags & 16) || g_hero_state.mode != 0x31) {
            turret_reset_camera_state(self);
            moby_set_state(self, 4, -1);
            if (I(st, 0xa4) != -1) {
                Effect *effect = (Effect *)(I(st, 0xa4) * 0x70 + (int)g_sound_state);
                if (effect->owner == self && effect->active)
                    snd_stop_voice(I(st, 0xa4));
            }
            I(st, 0xa4) = -1;
            g_snivelak_turret_state = 2;
            g_snivelak_turret_timer = 25;
        } else {
            func_PAL_L16_0041C470(self);
            func_PAL_L16_0041C1F0(self);
            cam_update_turret_follow(self);
            turret_set_camera_matrices(self);
        }
        break;
    }
    hit = part_find_owned_effect_slot(self, 1, 0);
    if (!hit)
        return;
    if (P(hit, 0x20) && H(P(hit, 0x20), 0xaa) == 0x12be)
        ApproachValue((float *)(st + 0x94), 0.0f, 1.0f);
    if (P(hit, 0x20) && (H(P(hit, 0x20), 0xaa) == 0xf79 || H(P(hit, 0x20), 0xaa) == 0x9b0 || F(st, 0x94) == 0.0f)) {
        U(self, 0x34) = (U(self, 0x34) | 0x41) & 0xefff;
        I(self, 0x98) = 0;
        if ((unsigned)(B(self, 0x20) - 2) < 2)
            turret_reset_camera_state(self);
        moby_set_state(self, 6, -1);
        B(self, 0xa8) = 0xff;
        func_PAL_L16_0041BF40(self);
    } else if ((!P(hit, 0x20) || H(P(hit, 0x20), 0xaa) != 0xea7) && B(self, 0x20) == 3 && g_hero_state.mode == 0x31 && g_hero_state.timer == 0) {
        AdjustPlayerHealth_pal(FloatToInt(F(hit, 0x2c)));
        if (g_hero_state.flag == 0) {
            turret_reset_camera_state(self);
            moby_set_state(self, 4, -1);
        } else {
            g_hero_state.timer = 50;
        }
        module_l00_call_handler_with_arg_4_pal(300);
    }
    B(self, 0xa8) = 0xff;
}
