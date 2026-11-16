#include "include_asm.h"

#include "common.h"
typedef int DobboQuad __attribute__((mode(TI)));
extern int g_dobbo_wander_disabled __attribute__((sda));
extern float g_dobbo_slow_move_speed __attribute__((sda));
extern float g_dobbo_wander_range __attribute__((sda));
extern float D_L09_001B13F8_1[] __attribute__((sda));
extern char g_dobbo_target_point[];
extern void dobbo_update_release_record(char *);
extern int flag_set_second_pending(char *);
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern int math_fast_float_d(void *);
extern int math_random_int_below(int);
extern void moby_set_state(char *, int, int);
extern int math_random_int_range(int, int);
extern int moby_dispatch_action_by_kind(char *, void *);
extern void dobbo_destroy_with_debris(char *);
extern int flag_set_first_pending(char *);
extern void anim_start_blended(char *, int, int, int);
extern void dobbo_start_fast_move_anim(char *, int);
extern void dobbo_start_slow_move_anim(char *, int);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern void path_clamp_move_to_area(void *, void *, void *, int, float);
extern int dobbo_move_toward_point(char *, void *, int);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern int moby_check_target_point_from_offset(char *, void *);
extern float mat_fast_helper_a(float, float);
extern int moby_step_at_own_position_factor(char *, float);
extern int moby_count_group_side_from_object(char *, void *, int);
extern void moby_turn_toward_target_limited(char *);
extern int moby_start_effect_from_entry(char *, float);
extern int math_is_value_within_step_us2(char *, float);
extern int coll_test_hit_at_bone(char *, int, int, int, int, int, float, float, float);
extern void dobbo_tick_timers_effects(char *);
extern void dobbo_update_pulsing_tint(char *);
#define BYTE(p,o) (*(u8 *)((p)+(o)))
#define HALF(p,o) (*(s16 *)((p)+(o)))
#define WORD(p,o) (*(s32 *)((p)+(o)))
#define FLOAT(p,o) (*(float *)((p)+(o)))

/* Per-frame update of the wandering Dobbo creature (moby class 3472): it walks about, turns to the hero, spits and bursts when hit. (USA v2.00) */
void dobbo_wandering_update_us2(char *obj)
{
    DobboQuad position;
    char *data;
    char *target;
    int flags;
    int animation;
    float angle, speed;
    if (g_dobbo_wander_disabled) return;
    data = *(char **)(obj + 0x68);
    dobbo_update_release_record(obj);
    if (!obj || BYTE(obj,0x20) == 0xFE || BYTE(obj,0x20) == 0xFD) return;
    switch (BYTE(obj,0x95)) {
    case 0:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.001111111138f,0.033333335f,0.006981317885f,0.4188790917f);
            FLOAT(data,0x124)=0.006666666828f;
            FLOAT(data,0x134)=0.5f;
        }
        if (HALF(data,0x334)==1 && math_fast_float_d(data+0x35C)) {
            if (!math_random_int_below(4)) moby_set_state(obj,9,2);
            else moby_set_state(obj,8,2);
        } else if (HALF(data,0x336)) {
            if (!math_random_int_below(1)) moby_set_state(obj,7,1);
            else moby_set_state(obj,6,1);
            HALF(data,0x336)=0;
            if (HALF(data,0x330)<300) HALF(data,0x330)=math_random_int_range(480,600);
        }
        break;
    case 1:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.002222222276f,0.083333336f,0.006981317885f,0.4188790917f);
            FLOAT(data,0x1D0)=g_dobbo_slow_move_speed*0.0166666675f;
            FLOAT(data,0x134)=0.05f;
        }
        if (HALF(data,0x334)==1) moby_set_state(obj,9,2);
        else if (!HALF(data,0x330)) moby_set_state(obj,1,0);
        break;
    case 2:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.003333333414f,0.083333336f,0.006981317885f,0.4188790917f);
            FLOAT(data,0x1D0)=g_dobbo_slow_move_speed*0.0166666675f;
            FLOAT(data,0x124)=0.006666666828f;
            FLOAT(data,0x134)=0.05f;
            WORD(data,0x35C)=math_random_int_range(0,30);
        }
        if (HALF(data,0x334)!=1 && math_fast_float_d(data+0x35C)) {
            moby_set_state(obj,3,1);
            HALF(data,0x330)=math_random_int_range(580,600);
        }
        break;
    case 3:
        flags=moby_dispatch_action_by_kind(obj,data+0x50);
        if (flags&1) dobbo_destroy_with_debris(obj);
        else if (flags&2) {
            if (HALF(data,0x334)==1) moby_set_state(obj,9,2);
            else {
                moby_set_state(obj,3,1);
                HALF(data,0x330)=math_random_int_range(580,600);
            }
        }
        break;
    }
    switch (BYTE(obj,0x20)) {
    case 1:
        if (!BYTE(obj,0x31)) break;
        if (flag_set_first_pending(obj)) {
            animation=!math_random_int_below(4);
            if (BYTE(obj,0x43)!=animation) anim_start_blended(obj,animation,0,20);
            HALF(data,0x332)=math_random_int_range(60,120);
        }
        if (BYTE(obj,0x43)==1) {
            if (BYTE(obj,0x60)&2) anim_start_blended(obj,0,0,20);
        } else if (!HALF(data,0x332)) moby_set_state(obj,2,-1);
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            dobbo_start_fast_move_anim(obj,20);
            angle=math_random_angle(); speed=math_random_float_range(2.0f,5.0f);
            FLOAT(data,0x310)=math_fast_sin_or_cos_a(angle)*speed;
            FLOAT(data,0x314)=math_fast_sin_or_cos_b(angle)*speed;
            WORD(data,0x318)=0;
            FastVecAdd((data+0x310),(data+0x310),data+0x300);
            if (WORD(data,0x234)!=-1) {
                position=*(DobboQuad *)(data+0x300);
                path_clamp_move_to_area(&position,(data+0x310),(data+0x310),WORD(data,0x234),1.5f);
            }
        }
        dobbo_move_toward_point(obj,(data+0x310),0);
        if (*(u16 *)(obj+0x96)>30 && (FLOAT(data,0x1CC)<=0.5f || *(u16 *)(obj+0x96)>180)) moby_set_state(obj,1,-1);
        break;
    case 3:
        if (flag_set_first_pending(obj)) {
            if (BYTE(obj,0x43)!=math_random_int_below(2)+4) anim_start_blended(obj,math_random_int_below(2)+4,0,10);
        }
        if (fast_vec_dist(obj+0x10,g_dobbo_target_point)<g_dobbo_wander_range) moby_set_state(obj,4,-1);
        else if (BYTE(obj,0x60)&2) {
            switch (math_random_int_below(3)) {
            case 0: moby_set_state(obj,6,-1); break;
            case 1: moby_set_state(obj,7,-1); break;
            case 2: moby_set_state(obj,5,-1); break;
            }
        }
        break;
    case 6:
        if (flag_set_first_pending(obj)) {
            if (BYTE(obj,0x43)!=math_random_int_below(2)+2) anim_start_blended(obj,math_random_int_below(2)+2,0,10);
        }
        moby_check_target_point_from_offset(obj,data+0x1F0);
        if (BYTE(obj,0x60)&2) moby_set_state(obj,3,-1);
        break;
    case 7:
        if (flag_set_first_pending(obj)) {
            if (BYTE(obj,0x43)!=12) anim_start_blended(obj,12,0,10);
        }
        moby_check_target_point_from_offset(obj,data+0x1F0);
        if (BYTE(obj,0x60)&2) moby_set_state(obj,3,-1);
        break;
    case 4:
        if (flag_set_first_pending(obj)) {
            dobbo_start_slow_move_anim(obj,10);
            FLOAT(data,0x238)=math_random_float_range(g_dobbo_wander_range,D_L09_001B13F8_1[1])+0.5f;
        }
        if ((dobbo_move_toward_point(obj,data+0x300,0)&0x80) || FLOAT(data,0x238)<vec_distance_xy(obj+0x10,g_dobbo_target_point)) {
            if (math_random_int_below(2)) moby_set_state(obj,6,-1);
            else moby_set_state(obj,7,-1);
        }
        break;
    case 5:
        if (flag_set_first_pending(obj)) {
            dobbo_start_slow_move_anim(obj,20);
            angle=math_random_angle(); speed=math_random_float_range(2.0f,5.0f);
            FLOAT(data,0x310)=math_fast_sin_or_cos_a(angle)*speed;
            FLOAT(data,0x314)=math_fast_sin_or_cos_b(angle)*speed;
            WORD(data,0x318)=0;
            FastVecAdd((data+0x310),(data+0x310),data+0x300);
            if (WORD(data,0x234)!=-1) {
                position=*(DobboQuad *)(data+0x300);
                path_clamp_move_to_area(&position,(data+0x310),(data+0x310),WORD(data,0x234),1.5f);
            }
        }
        dobbo_move_toward_point(obj,(data+0x310),0);
        if (*(u16 *)(obj+0x96)>30 && (FLOAT(data,0x1CC)<=0.5f || *(u16 *)(obj+0x96)>180)) moby_set_state(obj,3,-1);
        break;
    case 8:
        if (flag_set_first_pending(obj)) {
            FLOAT(data,0x114)=0.01774418354f;
            FLOAT(data,0x11C)=1.0646510124f;
            if (BYTE(obj,0x43)!=math_random_int_below(2)+2) anim_start_blended(obj,math_random_int_below(2)+2,0,10);
        }
        target=*(char **)(data+0x200);
        moby_step_at_own_position_factor(obj,mat_fast_helper_a(FLOAT(target,0x10)-FLOAT(obj,0x10),FLOAT(target,0x14)-FLOAT(obj,0x14)));
        flags = BYTE(obj,0x60);
        flags &= 2;
        if (flags) {
            FLOAT(data,0x114)=0.006981317885f;
            FLOAT(data,0x11C)=0.4188790917f;
            moby_set_state(obj,9,-1);
        }
        break;
    case 9:
        if (flag_set_first_pending(obj)) dobbo_start_slow_move_anim(obj,5);
        if (!(*(u16 *)(obj+0x96)&3)) FLOAT(data,0x33C)=moby_count_group_side_from_object(obj,*(void **)(data+0x200),-1)*0.08726647496f;
        dobbo_move_toward_point(obj,data+0x1F0,1);
        moby_turn_toward_target_limited(obj);
        if (FLOAT(data,0x1CC)<=1.25f) moby_set_state(obj,10,-1);
        break;
    case 10:
        if (flag_set_first_pending(obj)) {
            FLOAT(data,0x340)=mat_fast_helper_a(FLOAT(data,0x1F0)-FLOAT(obj,0x10),FLOAT(data,0x1F4)-FLOAT(obj,0x14));
            if (BYTE(obj,0x43)!=8) anim_start_blended(obj,8,2,10);
        }
        moby_start_effect_from_entry(obj,FLOAT(data,0x340));
        if (math_is_value_within_step_us2(obj,13.0f)) coll_test_hit_at_bone(obj,1,0x4000001,0,1,0,0.75f,(float)BYTE(data,0x34),1.0f);
        if (BYTE(obj,0x60)&2) moby_set_state(obj,9,-1);
        break;
    }
    dobbo_tick_timers_effects(obj);
    if (BYTE(obj,0x31)) dobbo_update_pulsing_tint(obj);
}
