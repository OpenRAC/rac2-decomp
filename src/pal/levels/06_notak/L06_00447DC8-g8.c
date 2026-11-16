#include "names.h"
/* func_PAL_L06_00447DC8, the PAL copy of func_L06_00443280: the same C at 50 Hz, with the
   timers from func_002A7820 scaled by 5/6, frame counts and rates converted, and PAL callees. */
#include "common.h"

extern float g_creature_wander_time_a __attribute__((sda));
extern float g_creature_wander_time_b __attribute__((sda));
extern int g_game_l06_frame_counter;
extern void notak_enemy_update_pal(char *);
extern int flag_set_second_pending(char *);
extern int flag_set_first_pending(char *);
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void moby_set_state(char *, int, int);
extern void anim_start_blended_pal(char *, int, int, int);
extern int moby_dispatch_action_by_kind(char *, char *);
extern void moby_l06_explode_and_remove_pal(char *);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(char *, char *, char *);
extern int actor_set_glow_effect_pal(char *, char *, int);
extern int moby_count_group_side_from_object(char *, int, int);
extern void actor_aim_head_at_hero(char *);
extern float mat_fast_helper_a(float, float);
extern int moby_start_effect_from_entry(char *, float);
extern int math_is_value_within_step_pal(char *, float);
extern int coll_test_hit_at_bone(char *, int, int, int, int, int, float, float, float);
extern void vec_scale_to_length(char *, char *, float);
extern void actor_tick_timers_effects(char *);
extern void marker_update_pulse_pal(char *);

#define F(p,o) (*(float *)((p)+(o)))
#define H(p,o) (*(short *)((p)+(o)))
#define U(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))

/* Updates a wandering Notak creature: picks its state, wander target and head turns, then pulses its marker (PAL: 50 Hz timings). */
void wandering_l06_creature_update_pal(char *obj)
{
    char *vars = *(char **)(obj + 0x68);
    char glow_dir[16];
    float angle, speed;
    int flags, anim;
    notak_enemy_update_pal(obj);
    if (!obj || B(obj,0x20) == 0xFE || B(obj,0x20) == 0xFD) return;
    switch (B(obj,0x95)) {
    case 0:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj, 0.0072000003f, 0.080000006f, 0.005026549f, 0.5026549f);
            F(vars,0x124) = 0.0096f;
            F(vars,0x134) = 0.5f;
        }
        F(vars,0x1D0) = g_creature_wander_time_b * 0.020000001f;
        if (H(vars,0x314) == 1) {
            if (math_random_int_below(5) == 0) {
                moby_set_state(obj,5,2);
            } else {
                moby_set_state(obj,6,2);
            }
        } else if (H(vars,0x316)) {
            moby_set_state(obj,3,1);
            H(vars,0x316) = 0;
            if (H(vars,0x310) < 250) H(vars,0x310) = ((s32)math_random_int_range(480,600) * 5 + 2) / 6;
        }
        break;
    case 1:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj, 0.0072000003f, 0.080000006f, 0.005026549f, 0.5026549f);
            F(vars,0x134) = 0.05f;
        }
        F(vars,0x1D0) = g_creature_wander_time_a * 0.020000001f;
        if (H(vars,0x314) == 1) moby_set_state(obj,6,2);
        else if (!H(vars,0x310)) moby_set_state(obj,1,0);
        break;
    case 2:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj, 0.0072000003f, 0.080000006f, 0.005026549f, 0.5026549f);
            F(vars,0x124) = 0.0096f;
            F(vars,0x134) = 0.05f;
        }
        F(vars,0x1D0) = g_creature_wander_time_a * 0.020000001f;
        if (H(vars,0x314) == 1) break;
        else {
            moby_set_state(obj,3,1);
            H(vars,0x310) = ((s32)math_random_int_range(580,600) * 5 + 2) / 6;
        }
        break;
    case 3:
        flags = moby_dispatch_action_by_kind(obj,vars+0x50);
        if (flags & 1) moby_l06_explode_and_remove_pal(obj);
        else if (flags & 2) {
            if (H(vars,0x314) == 1) {
                moby_set_state(obj,6,2);
            } else {
                moby_set_state(obj,3,1);
                H(vars,0x310) = ((s32)math_random_int_range(580,600) * 5 + 2) / 6;
            }
        }
        break;
    }
    switch (B(obj,0x20)) {
    case 1:
        if (flag_set_first_pending(obj)) {
            anim = math_random_int_below(4) == 0;
            if (B(obj,0x43) != anim) anim_start_blended_pal(obj,anim,0,8);
            H(vars,0x312) = ((s32)math_random_int_range(60,120) * 5 + 2) / 6;
        }
        if (B(obj,0x43) == 1) {
            if (B(obj,0x60) & 2) anim_start_blended_pal(obj,0,0,17);
        } else if (!H(vars,0x312)) moby_set_state(obj,2,-1);
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43) != 6) anim_start_blended_pal(obj,6,0,17);
            angle = math_random_angle();
            speed = math_random_float_range(2.0f,5.0f);
            F(vars,0x2F0) = math_fast_sin_or_cos_a(angle)*speed;
            F(vars,0x2F4) = math_fast_sin_or_cos_b(angle)*speed;
            F(vars,0x2F8) = 0;
            FastVecAdd(vars+0x2F0,vars+0x2F0,vars+0x2E0);
        }
        actor_set_glow_effect_pal(obj,vars+0x2F0,0);
        if (U(obj,0x96)>25 && (F(vars,0x1CC)<=0.5f || U(obj,0x96)>150)) moby_set_state(obj,1,-1);
        break;
    case 3:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43) != math_random_int_below(2)+4) anim_start_blended_pal(obj,math_random_int_below(2)+4,0,8);
        }
        break;
    case 4:
        if (flag_set_first_pending(obj) && B(obj,0x43)!=6) anim_start_blended_pal(obj,6,0,8);
        if (actor_set_glow_effect_pal(obj,vars+0x2E0,0)&0x80) moby_set_state(obj,3,-1);
        break;
    case 5:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43) != math_random_int_below(2)+2) anim_start_blended_pal(obj,math_random_int_below(2)+2,0,8);
        }
        if (B(obj,0x60)&2) moby_set_state(obj,6,-1);
        break;
    case 6:
        if (flag_set_first_pending(obj) && B(obj,0x43)!=6) anim_start_blended_pal(obj,6,0,4);
        if (!(U(obj,0x96)&3)) F(vars,0x31C) = (float)moby_count_group_side_from_object(obj,I(vars,0x200),-1)*0.087266475f;
        actor_set_glow_effect_pal(obj,vars+0x1F0,1);
        actor_aim_head_at_hero(obj);
        if (F(vars,0x1CC)<=1.25f) moby_set_state(obj,7,-1);
        break;
    case 7:
        if (flag_set_first_pending(obj)) {
            F(vars,0x320) = mat_fast_helper_a(F(vars,0x1F0)-F(obj,0x10),F(vars,0x1F4)-F(obj,0x14));
            if (B(obj,0x43)!=8) anim_start_blended_pal(obj,8,3,5);
        }
        moby_start_effect_from_entry(obj,F(vars,0x320));
        if (math_is_value_within_step_pal(obj,13.0f)) coll_test_hit_at_bone(obj,1,0x4000001,0,1,0,0.75f,(float)B(vars,0x34),1.0f);
        if (B(obj,0x60)&2) moby_set_state(obj,6,-1);
        break;
    case 10:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=10) anim_start_blended_pal(obj,10,0,5);
            I(vars,0x1BC) = g_game_l06_frame_counter;
        }
        vec_scale_to_length(glow_dir,vars+0x1A0,1.0f);
        actor_set_glow_effect_pal(obj,glow_dir,0);
        if (F(vars,0x190)>=F(obj,0x18)) {
            moby_set_state(obj,5,2);
            I(vars,0x138) &= ~0x11;
        }
        break;
    }
    actor_tick_timers_effects(obj);
    if (B(obj,0x31)) marker_update_pulse_pal(obj);
}
