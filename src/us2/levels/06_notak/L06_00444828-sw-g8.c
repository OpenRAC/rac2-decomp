#include "include_asm.h"

#include "common.h"
extern float D_L06_001B1090 __attribute__((sda));
extern float D_L06_001B1094 __attribute__((sda));
extern int D_L06_001B2348;
extern void notak_enemy_update(char *);
extern int flag_set_second_pending(char *);
extern int flag_set_first_pending(char *);
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void moby_set_state(char *, int, int);
extern void anim_start_blended(char *, int, int, int);
extern int moby_dispatch_action_by_kind(char *, char *);
extern void moby_l06_explode_and_remove(char *);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(char *, char *, char *);
extern int actor_set_glow_effect(char *, char *, int);
extern int moby_count_group_side_from_object(char *, int, int);
extern void actor_aim_head_at_hero(char *);
extern float mat_fast_helper_a(float, float);
extern void moby_start_effect_from_entry(char *, float);
extern int func_US2_002AF9C8(char *, float);
extern void coll_test_hit_at_bone(char *, int, int, int, int, int, float, float, float);
extern void vec_scale_to_length(char *, char *, float);
extern void actor_tick_timers_effects(char *);
extern void marker_update_pulse(char *);
#define F(p,o) (*(float *)((p)+(o)))
#define H(p,o) (*(short *)((p)+(o)))
#define U(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))

void func_US2_L06_00444828(char *obj)
{
    char *st = *(char **)(obj + 0x68);
    char tmp[16];
    float angle, speed;
    int flags, anim;
    notak_enemy_update(obj);
    if (!obj || B(obj,0x20) == 0xFE || B(obj,0x20) == 0xFD) return;
    switch (B(obj,0x95)) {
    case 0:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj, 0.005f, 0.06666667f, 0.0034906589f, 0.41887909f);
            F(st,0x124) = 0.006666667f;
            F(st,0x134) = 0.5f;
        }
        F(st,0x1D0) = D_L06_001B1094 * 0.016666667f;
        if (H(st,0x314) == 1) {
            if (math_random_int_below(5) == 0) {
                moby_set_state(obj,5,2);
            } else {
                moby_set_state(obj,6,2);
            }
        } else if (H(st,0x316)) {
            moby_set_state(obj,3,1);
            H(st,0x316) = 0;
            if (H(st,0x310) < 300) H(st,0x310) = math_random_int_range(480,600);
        }
        break;
    case 1:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj, 0.005f, 0.06666667f, 0.0034906589f, 0.41887909f);
            F(st,0x134) = 0.05f;
        }
        F(st,0x1D0) = D_L06_001B1090 * 0.016666667f;
        if (H(st,0x314) == 1) moby_set_state(obj,6,2);
        else if (!H(st,0x310)) moby_set_state(obj,1,0);
        break;
    case 2:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj, 0.005f, 0.06666667f, 0.0034906589f, 0.41887909f);
            F(st,0x124) = 0.006666667f;
            F(st,0x134) = 0.05f;
        }
        F(st,0x1D0) = D_L06_001B1090 * 0.016666667f;
        if (H(st,0x314) == 1) break;
        else {
            moby_set_state(obj,3,1);
            H(st,0x310) = math_random_int_range(580,600);
        }
        break;
    case 3:
        flags = moby_dispatch_action_by_kind(obj,st+0x50);
        if (flags & 1) moby_l06_explode_and_remove(obj);
        else if (flags & 2) {
            if (H(st,0x314) == 1) {
                moby_set_state(obj,6,2);
            } else {
                moby_set_state(obj,3,1);
                H(st,0x310) = math_random_int_range(580,600);
            }
        }
        break;
    }
    switch (B(obj,0x20)) {
    case 1:
        if (flag_set_first_pending(obj)) {
            anim = math_random_int_below(4) == 0;
            if (B(obj,0x43) != anim) anim_start_blended(obj,anim,0,10);
            H(st,0x312) = math_random_int_range(60,120);
        }
        if (B(obj,0x43) == 1) {
            if (B(obj,0x60) & 2) anim_start_blended(obj,0,0,20);
        } else if (!H(st,0x312)) moby_set_state(obj,2,-1);
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43) != 6) anim_start_blended(obj,6,0,20);
            angle = math_random_angle();
            speed = math_random_float_range(2.0f,5.0f);
            F(st,0x2F0) = math_fast_sin_or_cos_a(angle)*speed;
            F(st,0x2F4) = math_fast_sin_or_cos_b(angle)*speed;
            F(st,0x2F8) = 0;
            FastVecAdd(st+0x2F0,st+0x2F0,st+0x2E0);
        }
        actor_set_glow_effect(obj,st+0x2F0,0);
        if (U(obj,0x96)>30 && (F(st,0x1CC)<=0.5f || U(obj,0x96)>180)) moby_set_state(obj,1,-1);
        break;
    case 3:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43) != math_random_int_below(2)+4) anim_start_blended(obj,math_random_int_below(2)+4,0,10);
        }
        break;
    case 4:
        if (flag_set_first_pending(obj) && B(obj,0x43)!=6) anim_start_blended(obj,6,0,10);
        if (actor_set_glow_effect(obj,st+0x2E0,0)&0x80) moby_set_state(obj,3,-1);
        break;
    case 5:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43) != math_random_int_below(2)+2) anim_start_blended(obj,math_random_int_below(2)+2,0,10);
        }
        if (B(obj,0x60)&2) moby_set_state(obj,6,-1);
        break;
    case 6:
        if (flag_set_first_pending(obj) && B(obj,0x43)!=6) anim_start_blended(obj,6,0,5);
        if (!(U(obj,0x96)&3)) F(st,0x31C) = (float)moby_count_group_side_from_object(obj,I(st,0x200),-1)*0.087266475f;
        actor_set_glow_effect(obj,st+0x1F0,1);
        actor_aim_head_at_hero(obj);
        if (F(st,0x1CC)<=1.25f) moby_set_state(obj,7,-1);
        break;
    case 7:
        if (flag_set_first_pending(obj)) {
            F(st,0x320) = mat_fast_helper_a(F(st,0x1F0)-F(obj,0x10),F(st,0x1F4)-F(obj,0x14));
            if (B(obj,0x43)!=8) anim_start_blended(obj,8,3,6);
        }
        moby_start_effect_from_entry(obj,F(st,0x320));
        if (func_US2_002AF9C8(obj,13.0f)) coll_test_hit_at_bone(obj,1,0x4000001,0,1,0,0.75f,(float)B(st,0x34),1.0f);
        if (B(obj,0x60)&2) moby_set_state(obj,6,-1);
        break;
    case 10:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=10) anim_start_blended(obj,10,0,5);
            I(st,0x1BC) = D_L06_001B2348;
        }
        vec_scale_to_length(tmp,st+0x1A0,1.0f);
        actor_set_glow_effect(obj,tmp,0);
        if (F(st,0x190)>=F(obj,0x18)) {
            moby_set_state(obj,5,2);
            I(st,0x138) &= ~0x11;
        }
        break;
    }
    actor_tick_timers_effects(obj);
    if (B(obj,0x31)) marker_update_pulse(obj);
}
