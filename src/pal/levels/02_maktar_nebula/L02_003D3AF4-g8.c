#include "names.h"
/* func_PAL_L02_003D3AF4, the PAL copy of func_L02_003CFAC8: the same C at 50 Hz, where
   func_L01_0031AB20 becomes func_PAL_L01_0031C9C0, func_0032C700 becomes func_PAL_L00_003FB330
   and func_L02_003D02F0 becomes func_PAL_L02_003D4340. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
extern int g_arena_l02_active_flag NOT_SDA;
extern char *g_hit_l02_result NOT_SDA;
extern char g_hero_state[] NOT_SDA;
typedef struct { float amount; int unk4; int time; int phase; char pad[0x10]; } ShakeSlot;
typedef struct { char pad[0x160]; ShakeSlot slot[2]; } Shake;
extern Shake g_hero_effect_state;
extern u16 g_moby_link_id NOT_SDA;
extern Vector g_camera_l02_position;
extern int g_actor_stop_flag __attribute__((sda));
/* One table: [0] is a bare small symbol ($gp), [1] and [2] are symbol + offset: two-word tied absolute loads. */
extern int g_platform_pulse_colors[] __attribute__((sda));
extern float g_explosion_scale __attribute__((sda));
extern float coll_probe_ground_height_below(void *, int, float), fast_vec_dist(void *, void *), FastAddRotations(float, float), math_step_int_toward_target(int *, int, int);
extern void pushable_moby_update_pal(char *, void *, int, float, float, float), moby_set_state(u8 *, int, int), platform_respawn_timed(char *), grab_target_update_highlight_pal(char *);
extern int FloatToInt(float), flag_set_first_pending(u8 *), flag_is_third_pending_set(u8 *), math_fast_float_d(int *), PlayMobySound(int, int, char *), snd_play_from_class_bank(int, int, char *, int);
extern int PulseColor(int, int, float), coll_test_point(void *, int, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int coll_sweep_from_object(void *, float, float *, int, float, float, int, int, int);
/* Full constructor: (self + 0x10), seven register words, four stack words, and two FP inputs. */
extern void *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
/* Drives the timed platform through activation, falling, detonation and respawn. */
void UpdateCountdownExplosive_pal(char *self) {
    Vector point;
    char *state;
    float shake, radius;
    int timer, hits, i, old;
    if (g_arena_l02_active_flag) return;
    state = *(char **)(self + 0x68);
    switch (((u8 *)self)[0x20]) {
    case 0:
        ((u8 *)self)[0x30] = 0xFF; *(u16 *)(self + 0x34) |= 0x1000;
        *(float *)(state + 0x84) = 2.75f; *(float *)(state + 0xE0) = 0.333f;
        *(u32 *)(state + 0x70) |= 6; ((u8 *)self)[0x20] = 1;
        *(float *)(self + 0x18) = coll_probe_ground_height_below((self + 0x10), 0, 0.5f) + 0.7f;
        if (g_hit_l02_result) *(float *)(state + 0x88) = 14.5f;
        else *(float *)(state + 0x88) = 10.0f;
        qcopy(state + 0xA0,(self + 0x10));
        break;
    case 1:
        pushable_moby_update_pal(self, state + 0x50, -1, 0.5f, 0.5f, 0.1f);
        if (g_actor_stop_flag) { g_actor_stop_flag = 0; moby_set_state((u8 *)self, 5, -1); break; }
        if (*(char **)(g_hero_state + 0x5C0) != self) break;
        g_moby_link_id = 0xFFFF; moby_set_state((u8 *)self, 2, -1);
        *(int *)(state + 0xD4) = FloatToInt((*(float *)(state + 0xC0) * 300.0f + 2.0f) * 0.16666667f);
        break;
    case 2:
        if (flag_set_first_pending((u8 *)self)) *(int *)(state + 0xDC) = 0;
        pushable_moby_update_pal(self, state + 0x50, -1, 0.5f, 0.5f, 0.1f);
        if (*(int *)(state + 0xC4) != -1 && *(char **)(g_hero_state + 0x5C0) == self) grab_target_update_highlight_pal(self);
        timer = *(int *)(state + 0xD4);
        if (timer % 50 == 8 || (timer < 100 && timer % 25 == 8)) snd_play_from_class_bank(1, 0, self, 0x1F9);
        if (math_fast_float_d((int *)(state + 0xD4))) { moby_set_state((u8 *)self, 5, -1); break; }
        if (flag_is_third_pending_set((u8 *)self)) moby_set_state((u8 *)self, 3, -1);
        break;
    case 4:
        FastVecAdd((self + 0x10), (self + 0x10), state + 0xB0);
        *(float *)(state + 0xB8) -= 0.006f;
        hits = 0; i = 0;
        do {
            qcopy(&point,(self + 0x10));
            point.f[2] += (float)i; ++i;
            if (coll_test_point(&point, 0, self, *(float *)(state + 0xE0))) hits = 1;
        } while (i < 1);
        if (hits || *(float *)(self + 0x18) < *(float *)(state + 0xA8) - 1.0f) moby_set_state((u8 *)self, 5, -1);
        if (*(float *)((self + 0x10)) < 2 || *(float *)((self + 0x10)) > 1021 || *(float *)(self + 0x14) < 2 ||
            *(float *)(self + 0x14) > 1021 || *(float *)(self + 0x18) < 2 || *(float *)(self + 0x18) > 1021)
            moby_set_state((u8 *)self, 6, -1);
        break;
    case 5:
        if (flag_set_first_pending((u8 *)self)) {
            SpawnExplosion_pal((self + 0x10), 1, 25, 20, 20, 20, 45, 0, 1, 1, 0, 0, g_explosion_scale, 20.0f);
            ((u8 *)self)[0x31] = 0; *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) | 1) & 0xEFFF;
            PlayMobySound(1, 0, self);
            shake = (24.0f - fast_vec_dist(&g_camera_l02_position, (self + 0x10))) * 0.0062500006f;
            if (shake > 0.15f) shake = 0.15f; else if (shake < 0) shake = 0;
            if (shake != 0) {
                g_hero_effect_state.slot[1].time = 75;
                g_hero_effect_state.slot[0].phase = 0;
                g_hero_effect_state.slot[1].amount = shake;
            }
        }
        coll_sweep_from_object(self, (float)*(u16 *)(self + 0x96) * 0.6f, (float *)((self + 0x10)), 0x830000, 5.0f, 1.0f, 0, 1, 0);
        if (g_hit_l02_result && *(short *)(g_hit_l02_result + 0xAA) == 0xC82) math_step_int_toward_target((int *)(state + 0xE4), 0, 4);
        if (*(u16 *)(self + 0x96) < 9) break;
        old = *(int *)(state + 0xE4); *(int *)(state + 0xE4) = old + 1;
        if (old + 1 >= 8) {
            radius = (float)(old - 6) * 0.09514286f + 0.333f;
            *(float *)(state + 0xE0) = radius;
            if (radius > 1) *(float *)(state + 0xE0) = 1;
        } else *(float *)(state + 0xE0) = 0.333f;
        coll_sweep_from_object(self, 6.0f, (float *)((self + 0x10)), 0x830000, 10.0f, 1.0f, 0, 1, 0);
        moby_set_state((u8 *)self, 6, -1); break;
    case 6:
        qcopy(&point,state + 0xA0); point.f[2] += 0.7f;
        if (!coll_test_point(&point, 5, self, 0.75f)) platform_respawn_timed(self);
        break;
    case 3: default: break;
    }
    if (((u8 *)self)[0x31]) {
        *(float *)(self + 0xF4) = FastAddRotations(*(float *)(self + 0xF4), 0.031415932f);
        *(float *)(self + 0xF8) = FastAddRotations(*(float *)(self + 0xF4), 0.018151427f);
        if (((u8 *)self)[0x20] == 1) *(int *)(self + 0x78) = g_platform_pulse_colors[0];
        else {
            *(float *)(state + 0xD8) = FastAddRotations(*(float *)(state + 0xD8), 0.25132746f);
            *(int *)(self + 0x78) = PulseColor(g_platform_pulse_colors[1], g_platform_pulse_colors[2], *(float *)(state + 0xD8));
        }
    }
    ++*(u16 *)(self + 0x96);
}
