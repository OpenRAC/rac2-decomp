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
extern char D_001B9B00[];
typedef struct {
    char pre[0x74];
    unsigned char active;
    char pad[0x13];
    char *owner;
} Effect;
extern char g_sound_state[];
extern int D_L16_001B1704, D_00138324 __attribute__((nosda));
extern unsigned short D_001941DC __attribute__((nosda)), D_0018CDF0 __attribute__((nosda));
extern char *D_L16_001B2B1C;
extern int D_L16_001B16C0, D_L16_001A8FB4;
extern int D_L16_001A8FB0 __attribute__((sda));
extern int D_L16_001B1A80 __attribute__((sda));
extern float D_L16_001B1A90 __attribute__((sda)), D_L16_001B1A94 __attribute__((sda));
extern void moby_mark_spawned(char *), moby_set_state(char *, int, int);
extern float coll_get_ground_distance_below(char *, char *, char *);
extern void matrix_mul_vec3(char *, char *, char *), FastVecAdd(char *, char *, char *);
extern int func_US2_00289840(int, int);
extern int flag_set_first_pending(char *), PlayMobySound(int, int, char *);
extern void hero_reset_position_and_direction(char *, char *, int, int), SetCamera5Pose(char *, char *, int, int, int);
extern float math_fabs(float), vec_distance_xy(char *, char *), mat_fast_helper_a(float, float), FastAddRotations(float, float), fast_subtract_rotations(float, float), FastDiffRots(float, float);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern f32 math_approach_target_with_direction_mode(float *, float *, float, float, float, float, int);
extern void snd_stop_voice(int), turret_set_camera_matrices(char *), FireAlternatingMuzzleShot(char *), cam_update_turret_follow(char *), UpdateSnivelakSteering(char *), turret_reset_camera_state(char *), turret_explode_into_debris(char *);
extern void hud_add_moby_marker(char *, unsigned, int, int, int, int, float, float, float);
extern char *part_find_owned_effect_slot(char *, int, int);
extern void func_US2_L00_002A4EF8(int), func_US2_L00_0030D9F8(int);
extern f32 ApproachValue(float *, float, float);
extern int FloatToInt(float);

void func_US2_L16_004179E8(char *self) {
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
        if (D_L16_001B1704 >= 2 && D_001941DC < 3)
            func_US2_00289840(0xa0b, 0x62);
        break;
    case 1:
    case 4:
        if (flag_set_first_pending(self))
            PlayMobySound(3, 0, self);
        state = B(self, 0x20);
        if ((state == 4 && g_hero_state.target != self) || ((g = &g_hero_state), H(g, 0x34e) >= 20))
            B(self, 0x20) = 1;
        else if (state == 1 && g->target == self && g->active) {
            matrix_mul_vec3(buf, (char *)&D_L16_001B1A80, self + 0xc0);
            FastVecAdd(buf, buf, self + 0x10);
            hero_reset_position_and_direction(buf, self + 0xf0, 0x31, 0);
            g_hero_state.owner = self;
            SetCamera5Pose(D_001B9B00, D_001B9B00 + 0x10, 3, 60, 0);
            D_0018CDF0 = 0xffff;
            D_L16_001B16C0 = (int)self;
            moby_set_state(self, 2, -1);
            break;
        }
        if (math_fabs(F(self, 0x18) - F(st, 0x78) + D_L16_001B1A90) > 0.01f)
            math_step_value_toward_target((float *)(self + 0x18), (float *)(st + 0x98), F(st, 0x78) - D_L16_001B1A90, 0.0005555555690079927f, 0.0005555555690079927f, 0.03333333507180214f);
        if (vec_distance_xy(self + 0x10, (char *)&g_hero_state.x) > D_L16_001B1A94) {
            angle = FastAddRotations(mat_fast_helper_a(g_hero_state.x - F(self, 0x10), g_hero_state.y - F(self, 0x14)), 3.1415927410125732f);
            math_approach_target_with_direction_mode((float *)(self + 0xf8), (float *)(st + 0x9c), angle, 0.0017453294713050127f, 0.0017453294713050127f, 0.10471977293491364f, 0);
        }
        break;
    case 2:
        if (flag_set_first_pending(self)) {
            PlayMobySound(3, 0, self);
            I(st, 0x90) = 0;
        }
        angle = mat_fast_helper_a(F((char *)((I(st, 0x64) << 8) + (int)D_L16_001B2B1C), 0x10) - F(self, 0x10), F((char *)((I(st, 0x64) << 8) + (int)D_L16_001B2B1C), 0x14) - F(self, 0x14));
        math_step_value_toward_target((float *)(self + 0x18), (float *)(st + 0x98), F(st, 0x78), 0.0016666667070239782f, 0.0016666667070239782f, 0.10000000894069672f);
        math_approach_target_with_direction_mode((float *)(self + 0xf8), (float *)(st + 0x9c), angle, 0.0011635529808700085f, 0.0011635529808700085f, 0.10471977293491364f, 0);
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
        D_0018CDF0 = 0xffff;
        turret_set_camera_matrices(self);
        FireAlternatingMuzzleShot(self);
        cam_update_turret_follow(self);
        break;
    case 5:
    case 6:
        break;
    case 3:
        hud_add_moby_marker(self, 0x600fff0f, 0, 0x26, -1, 4, 1.0f, 0.0f, 90.0f);
        if ((D_00138324 & 16) || g_hero_state.mode != 0x31) {
            turret_reset_camera_state(self);
            moby_set_state(self, 4, -1);
            if (I(st, 0xa4) != -1) {
                Effect *effect = (Effect *)(I(st, 0xa4) * 0x70 + (int)g_sound_state);
                if (effect->owner == self && effect->active)
                    snd_stop_voice(I(st, 0xa4));
            }
            I(st, 0xa4) = -1;
            D_L16_001A8FB4 = 2;
            D_L16_001A8FB0 = 30;
        } else {
            UpdateSnivelakSteering(self);
            FireAlternatingMuzzleShot(self);
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
        turret_explode_into_debris(self);
    } else if ((!P(hit, 0x20) || H(P(hit, 0x20), 0xaa) != 0xea7) && B(self, 0x20) == 3 && g_hero_state.mode == 0x31 && g_hero_state.timer == 0) {
        func_US2_L00_002A4EF8(FloatToInt(F(hit, 0x2c)));
        if (g_hero_state.flag == 0) {
            turret_reset_camera_state(self);
            moby_set_state(self, 4, -1);
        } else {
            g_hero_state.timer = 60;
        }
        func_US2_L00_0030D9F8(360);
    }
    B(self, 0xa8) = 0xff;
}
