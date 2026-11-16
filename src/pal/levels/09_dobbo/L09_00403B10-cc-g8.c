#include "names.h"
/* func_PAL_L09_00403B10, the PAL copy of func_L09_003FEF00: the same C, where rename func_L09_003FE670 becomes func_PAL_L09_00403220; rename func_L09_003FDED8 becomes func_PAL_L09_00402A88; rename func_002A7470 becomes func_PAL_002A7E68; rename func_002ABBB8 becomes func_PAL_002AC718; rename func_002B0A68 becomes func_PAL_002B15D8; rename func_002A6C58 becomes func_PAL_002A7650; rename func_002BDCE8 becomes func_PAL_002BE9A8; rename func_L09_003FEAE8 becomes func_PAL_L09_00403698; rename func_L09_003FECF0 becomes func_PAL_L09_00403900; swap args at 13775; lit 0.060000002f becomes 0.05f; lit 0.1f becomes 1e+01f. */
#include "common.h"

/* The gate suppresses updates between its two height bands. */
typedef struct {
    int state;
    char pad04[8];
    int active;
    char pad10[0x18];
    float low;
    char pad2c[0xC];
    float high;
} DobboUpdateGate;
extern DobboUpdateGate g_dobbo_limits;
extern char g_sound_state[];
extern char g_hero_state[];
extern char g_default_particle_vec[] __attribute__((sda));
extern char *g_patrol_drone_sound_primary __attribute__((sda));
extern char *g_patrol_drone_sound_secondary __attribute__((sda));
extern int g_frame_l09_counter[] __attribute__((sda));
extern char g_collision_l09_hit_point[];
extern char *g_impact_l09_moby_table[];
extern char *g_path_l09_table[];
extern void patrol_drone_init_pal(char *);
extern void gfx_update_color_pulse_table(char *);
extern void child_objects_draw(char *);
extern void record_release_rebuild_effect(char *);
extern void counter_tick_restart_tracks(char *);
extern void group_flag_peers(char *);
extern void func_PAL_L09_00403698(char *);
extern void func_PAL_L09_00403900(char *);
extern int aim_update_at_target(char *, int);
extern void sub_object_ramp_channels(char *);
extern void path_move_moby_smooth(char *);
extern void sub_object_update_turn_ramps_pal(char *);
extern void moby_rebuild_frame_if_visible(char *);
extern void gfx_queue_draw_callback(void (*)(char *), char *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern float FastAddRotations(float, float);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern void snd_stop_voice(int);
extern int PlayMobySound(void *, int, void *);
extern void lerp_vector(void *, void *, void *, float);
extern int coll_process_hit(void *, int, int, int, float);
extern int CollLine(void *, void *, int, int, int);
extern float IntToFloat(int);
extern float math_wrap_angle_to_pi(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_spring_float_to_goal(void *, float, void *, float, float, float);
extern int path_push_point_away(int, void *, void *, float);
extern int find_nearest_path_point(void *, void *, void *, void *, void *, int, float, float, float);
extern int math_fast_helper_a(void *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float math_random_signed_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void func_PAL_002B15D8(void *, float, int, float, float, void *, float, int);
extern void FastVecAdd(void *, void *, void *);
extern float math_fabs(float);
extern int FastDecTimer(void *);
extern int coll_test_point(void *, int, void *, float);
extern void SetDeathBits_pal(void *, int, int);
extern void moby_mark_spawned(void *);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void *part_spawn_trailing_spark(void *, void *, int, int, int, int, float);
extern char *func_PAL_002BE9A8(void *, float, float, float, int, void *, float, int, int);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))

/* State 1 patrols and picks a target (hero or classes 0xCB, 0x76C, 0xEB0), state 2 falls or lands,
 * state 3 chases, state 4 starts breaking up, state 6 is falling debris that vanishes out of
 * bounds and explodes on timeout or contact. */
void func_PAL_L09_00403B10(char *obj)
{
    float a[4], b[4], previous[4];
    char *data = P(obj, 0x68);
    if (g_dobbo_limits.active) {
        if (F(obj, 0x18) < g_dobbo_limits.low && g_dobbo_limits.state == 1) return;
        if (g_dobbo_limits.low < F(obj, 0x18) && g_dobbo_limits.state == 0) return;
        if (g_dobbo_limits.active == 2) {
            if (g_dobbo_limits.high < F(obj, 0x18) && g_dobbo_limits.state == 1) return;
            if (F(obj, 0x18) < g_dobbo_limits.high && g_dobbo_limits.state == 2) return;
        }
    }
    if (B(obj, 0x20) == 0) patrol_drone_init_pal(obj);
    if (B(data, 0x2E) == 2) {
        I(data, 0x42C) = 0;
        SetDeathBits_pal(obj, 0, 3);
        moby_mark_spawned(obj);
        return;
    }
    {
        if (B(obj, 0x20) == 5) {
            gfx_update_color_pulse_table(obj);
            gfx_queue_draw_callback(child_objects_draw, obj);
            return;
        }
        I(data, 0x42C) = 0;
        record_release_rebuild_effect(obj);
        if ((unsigned)(B(obj, 0x20) - 1) < 3) H(data, 0x420) = 0;
        switch (B(obj, 0x20)) {
        case 0: goto tail;
        case 1: {
            int live, count, i;
            I(obj, 0x78) = 0xFFAAAAAA;
            {
                char *entry = (char *)((int)g_sound_state + I(data, 0x3F0) * 0x70);
                if (P(entry, 0x88) != obj || !B(entry, 0x74))
                    I(data, 0x3F0) = PlayMobySound(g_patrol_drone_sound_primary, 4, obj);
            }
            if (B(data, 0x440)) {
                B(data, 0x440) = 0;
                moby_set_state(obj, 3, -1);
                {
                    int sound = I(data, 0x3F0);
                    if (sound != -1) {
                        {
                            char *entry = (char *)((int)g_sound_state + sound * 0x70);
                            if (P(entry, 0x88) == obj && B(entry, 0x74)) snd_stop_voice(sound);
                        }
                    }
                }
                I(data, 0x3F0) = -1;
                {
                    char *entry = (char *)((int)g_sound_state + I(data, 0x3F0) * 0x70);
                    if (P(entry, 0x88) != obj || !B(entry, 0x74))
                        I(data, 0x3F0) = PlayMobySound(g_patrol_drone_sound_secondary, 4, obj);
                }
                H(data, 0x412) = 500;
            }
            H(data, 0x422) = 0;
            H(data, 0x420) = 1;
            live = aim_update_at_target(obj, 1);
            sub_object_ramp_channels(obj);
            path_move_moby_smooth(obj);
            sub_object_update_turn_ramps_pal(obj);
            if (live) {
                lerp_vector(a, data + 0x330, data + 0x370, 0.5f);
                qcopy(b, data + 0x330);
                count = coll_process_hit(a, 0, 0, 0, F(data, 0x434) * 0.48f);
                if (!count) count = coll_process_hit(b, 0, 0, 0, F(data, 0x434) * 0.9f);
                if (count) {
                    for (i = 0; i < count; i++) {
                        char *candidate = g_impact_l09_moby_table[i];
                        char *hero = g_hero_state;
                        if (candidate != P(hero, 0x2290)) {
                            int first = 0xCB;
                            int kind;
                            if (!candidate) continue;
                            kind = H(candidate, 0xAA);
                            if (kind != first && kind != 0x76C && kind != 0xEB0) continue;
                        }
                        {
                            group_flag_peers(obj);
                            candidate = g_impact_l09_moby_table[i];
                            P(data, 0x3AC) = candidate;
                            I(data, 0x44C) = H(candidate, 0xAA);
                            moby_set_state(obj, 3, -1);
                            {
                                int sound = I(data, 0x3F0);
                                if (sound != -1) {
                                    {
                                        char *entry = (char *)((int)g_sound_state + sound * 0x70);
                                        if (P(entry, 0x88) == obj && B(entry, 0x74)) snd_stop_voice(sound);
                                    }
                                }
                            }
                            I(data, 0x3F0) = -1;
                            {
                                char *entry = (char *)((int)g_sound_state + I(data, 0x3F0) * 0x70);
                                if (P(entry, 0x88) != obj || !B(entry, 0x74))
                                    I(data, 0x3F0) = PlayMobySound(g_patrol_drone_sound_secondary, 4, obj);
                            }
                            H(data, 0x412) = 500;
                            if (g_impact_l09_moby_table[i] != P(hero, 0x2290)) break;
                        }
                    }
                }
            }
            break;
        }
        case 2:
            if (F(data, 0x20) <= 0.0f) {
                int live;

                if (B(obj, 0x43)) func_PAL_002A7E68(obj, 0, 0, 10);
                live = I(data, 0x3F0);
                if (live != -1) {
                    {
                        char *entry = (char *)((int)g_sound_state + live * 0x70);
                        if (P(entry, 0x88) == obj && B(entry, 0x74)) snd_stop_voice(live);
                    }
                }
                I(data, 0x3F0) = -1;
                moby_set_state(obj, 4, -1);
            } else if (B(obj, 0x60) & 2) {
                if (B(obj, 0x43)) func_PAL_002A7E68(obj, 0, 0, 10);
                H(data, 0x412) = 500;
                moby_set_state(obj, 3, -1);
            }
            break;
        case 3: {
            char *target;
            I(obj, 0x78) = 0xFF00FFFF;
            target = P(data, 0x3AC);
            if (target && H(target, 0xAA) == I(data, 0x44C) &&
                B(target, 0x20) != 0xFE && B(target, 0x20) != 0xFD) {
                float phase, angle1, angle2, step1, step2;
                H(data, 0x420) = 1;
                H(data, 0x422) = 1;
                aim_update_at_target(obj, 1);
                qcopy(a, P(data, 0x3AC) + 0x10);
                a[2] += 0.5f;
                qcopy(b, a);
                b[2] -= 4.0f;
                if (CollLine(a, b, 0x12, 0, 0)) qcopy(a, g_collision_l09_hit_point);
                else a[2] -= 0.5f;
                qcopy(previous, data + 0x390);
                phase = IntToFloat(g_frame_l09_counter[0]) + H(obj, 0xB2) * 36;
                angle1 = math_wrap_angle_to_pi(phase * 0.025f);
                angle2 = math_wrap_angle_to_pi(phase * 0.016666668f);
                step1 = math_fast_sin_or_cos_b(angle1) + 1.5f;
                step2 = math_fast_sin_or_cos_b(angle2) + 1.5f;
                a[0] += math_fast_sin_or_cos_b(angle2);
                a[1] += math_fast_sin_or_cos_a(angle2);
                math_spring_float_to_goal(data + 0x390, a[0], data + 0x3A0, step1 * 0.003f, 0.2f, 0.0f);
                math_spring_float_to_goal(data + 0x394, a[1], data + 0x3A4, step2 * 0.003f, 0.2f, 0.0f);
                if (I(data, 0x444) != -1) {
                    if (path_push_point_away(I(data, 0x444), data + 0x390, data + 0x390, F(data, 0x434) * 1.3f)) {
                        F(data, 0x3A0) = F(data, 0x390) - previous[0];
                        F(data, 0x3A4) = F(data, 0x394) - previous[1];
                        B(data, 0x441) = 1;
                    } else B(data, 0x441) = 0;
                }
            } else {
                char *replacement = P(data, 0x150);
                P(data, 0x3AC) = replacement;
                if (replacement && B(replacement, 0x20) != 0xFE && B(replacement, 0x20) != 0xFD)
                    I(data, 0x44C) = H(replacement, 0xAA);
            }
            find_nearest_path_point(g_path_l09_table[I(data, 0x314)], data + 0x390, a,
                             data + 0x324, data + 0x3EC, 1, 20.0f, 5.0f, 0.0f);
            path_move_moby_smooth(obj);
            qcopy(a, obj + 0x10);
            a[3] = 4.0f;
            if (math_fast_helper_a(a, IntToFloat(H(obj, 0x32))) >= 0) {
                float *dst;
                moby_transform_joint_to_world(obj, 8, b);
                dst = (float *)(data + 0x3F4);
                dst[0] = b[0];
                dst[1] = b[1];
                dst[2] = b[2];
                I(data, 0x42C) |= 8;
                sub_object_update_turn_ramps_pal(obj);
            }
            if (I(data, 0x154) != 1) {
                if (H(data, 0x412) == 0) {
                    int live;

                    moby_set_state(obj, 1, -1);
                    live = I(data, 0x3F0);
                    if (live != -1) {
                        {
                            char *entry = (char *)((int)g_sound_state + live * 0x70);
                            if (P(entry, 0x88) == obj && B(entry, 0x74)) snd_stop_voice(live);
                        }
                    }
                    I(data, 0x3F0) = -1;
                    {
                        char *entry = (char *)((int)g_sound_state + I(data, 0x3F0) * 0x70);
                        if (P(entry, 0x88) != obj || !B(entry, 0x74))
                            I(data, 0x3F0) = PlayMobySound(g_patrol_drone_sound_primary, 4, obj);
                    }
                }
            }
            if (I(data, 0x154) == 1) {
                if (P(data, 0x3AC)) P(data, 0x3AC) = P(data, 0x150);
                B(data, 0x42B) = 1;
            }
            break;
        }
        case 4: {
            int live;

            H(data, 0x410) = 150;
            group_flag_peers(obj);
            live = I(data, 0x3F0);
            if (live != -1) {
                {
                    char *entry = (char *)((int)g_sound_state + live * 0x70);
                    if (P(entry, 0x88) == obj && B(entry, 0x74)) snd_stop_voice(live);
                }
            }
            I(data, 0x3F0) = -1;
            SpawnExplosionEffects_pal(obj, data + 0x400, obj + 0x10, 0.0f, 0.0f, 5, 2, 4,
                         4.0f, 2.0f, 9.0f, 1.0f, 1, 15.0f, 1, 5, -1, 0, 0x810001);
            FastVecSub(a, obj + 0x10, (g_hero_state + 0x80));
            a[2] = 0.0f;
            vec_scale_to_length(a, a, math_random_float_range(0.09f, 0.24000001f));
            FastVecCross(b, g_hero_state + 0x2C0, a);
            math_apply_axis_rotation_to_quat(data + 0x400, a, g_hero_state + 0x2C0, math_random_signed_float_range(0.698131799697876f, 1.2217305898666382f));
            F(data, 0x408) = math_random_float_range(0.120000005f,0.24000001f);
            func_PAL_002B15D8(obj, 3.0f, 0x7F, 6.0f, 3.0f, g_default_particle_vec, 6.0f, 0xFF);
            F(obj, 0x2C) *= 0.1f;
            F(data, 0x280) = 1e+01f;
            F(data, 0x414) = math_random_signed_float_range(0.0f, 0.087266475f);
            F(data, 0x418) = math_random_signed_float_range(0.0f, 0.0872664749622345f);
            F(data, 0x41C) = math_random_signed_float_range(0.0f, 0.0872664749622345f);
            F(obj, 0xF0) = FastAddRotations(F(obj, 0xF0), math_random_signed_float_range(0.0f, 0.78539824f));
            F(obj, 0xF4) = FastAddRotations(F(obj, 0xF4), math_random_signed_float_range(0.0f, 0.78539824f));
            moby_set_state(obj, 6, -1);
            moby_rebuild_frame_if_visible(obj);
            return;
        }
        case 5: goto tail;
        case 6: {
            int i;
            char *vel = data + 0x400;
            FastVecAdd(obj + 0x10, obj + 0x10, vel);
            if (math_fabs(F(data, 0x400)) > 0.060000002f) F(data, 0x400) *= 0.96400005f;
            if (math_fabs(F(data, 0x404)) > 0.060000002f) F(data, 0x404) *= 0.96400005f;
            if (F(data, 0x408) > 0.0f) F(data, 0x408) *= 0.96400005f;
            F(data, 0x408) -= 0.0043200003f;
            F(obj, 0xF8) = FastAddRotations(F(obj, 0xF8), F(data, 0x41C));
            F(data, 0x280) = 10.0f;
            if (F(obj, 0x10) < 2.0f || F(obj, 0x10) > 1021.0f ||
                F(obj, 0x14) < 2.0f || F(obj, 0x14) > 1021.0f ||
                F(obj, 0x18) < 2.0f || F(obj, 0x18) > 1021.0f) {
                moby_mark_spawned(obj);
                return;
            }
            if (FastDecTimer(data + 0x410) || coll_test_point(obj + 0x10, 0, obj, 0.5f)) {
                SpawnExplosionEffects_pal(obj, data + 0x400, obj + 0x10, 2.0f, 1.0f, 5, 2, 4,
                             2.0f, 1.0f, 9.0f, 1.0f, 1, 15.0f, 1, 5, -1, 0, 0x810001);
                SetDeathBits_pal(obj, 0, 3);
                moby_mark_spawned(obj);
                return;
            }
            part_spawn_trailing_spark(obj + 0x10, g_default_particle_vec, 0x4F007FFF, 0x1FFFFFFF,
                         math_random_int_range(8, 17), 1, 60000.0f);
            for (i = -2; i < 0; i++) {
                int spin = math_random_int_below(6);
                float energy;
                int colour, tint;
                char *particle;
                if (math_random_int_below(2)) spin = -spin;
                energy = math_random_float_range(40000.0f, 100000.0f);
                colour = math_random_int_range(0x30, 0xFF);
                tint = (colour << 8) | 0x60000000;
                colour = colour | ((colour << 16) | tint);
                particle = func_PAL_002BE9A8(obj + 0x10, 0.025f, 1.0f, 1.0f, spin, g_default_particle_vec,
                                       energy, colour, 0);
                if (particle) {
                    char *extra = particle + 0x20;
                    B(particle, 3) = 0x44;
                    H(particle, 0xA) = 50;
                    I(extra, 4) = 2;
                    B(extra, 0xA) = 0x60;
                    B(extra, 0xB) = B(particle, 0xA);
                }
            }
            moby_rebuild_frame_if_visible(obj);
            return;
        }
        }
    }
tail:
    counter_tick_restart_tracks(obj);
    moby_update_eased_node(obj, data + 0x210, 0, 0.21600002f, 0.43200004f);
    func_PAL_L09_00403698(obj);
    F(data, 0x2F8) = FastAddRotations(F(data, 0x2D8), 0.062831864f);
    moby_update_eased_node(obj, data + 0x290, 11, 0.21600002f, 0.43200004f);
    func_PAL_L09_00403900(obj);
}
