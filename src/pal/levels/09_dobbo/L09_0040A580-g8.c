/* func_PAL_L09_0040A580, the PAL copy of func_L09_00405610 in L09_00405610-g8.c: the same C, where the
   timers take the 50 Hz scale, the turn and blend rates change, and callees take their PAL names. */
#include "common.h"

typedef int DobboQuad __attribute__((mode(TI)));
extern int D_L09_001B1428 __attribute__((sda));
extern float D_L09_001B13F4 __attribute__((sda));
extern float D_L09_001B13F8 __attribute__((sda));
extern float D_L09_001B13F8_1[] __attribute__((sda)); /* { lower, upper } bounds, read as a pair */
extern char D_L09_00189EA0[];
extern void func_PAL_L09_00409DC8(char *);
extern int flag_set_second_pending(char *);
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern int math_fast_float_d(void *);
extern int math_random_int_below(int);
extern void moby_set_state(char *, int, int);
extern int math_random_int_range(int, int);
extern int moby_dispatch_action_by_kind(char *, void *);
extern void func_PAL_L09_0040A050(char *);
extern int flag_set_first_pending(char *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_PAL_L09_00409AC8(char *, int);
extern void func_PAL_L09_00409B48(char *, int);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern void path_clamp_move_to_area(void *, void *, void *, int, float);
extern int func_PAL_L09_00409F00(char *, void *, int);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern int moby_check_target_point_from_offset(char *, void *);
extern float mat_fast_helper_a(float, float);
extern int func_PAL_002B5E30(char *, float);
extern int moby_count_group_side_from_object(char *, void *, int);
extern void moby_turn_toward_target_limited(char *);
extern int moby_start_effect_from_entry(char *, float);
extern int func_PAL_002AF6C0(char *, float);
extern int coll_test_hit_at_bone(char *, int, int, int, int, int, float, float, float);
extern void func_PAL_L09_00409F38(char *);
extern void func_PAL_L09_0040A268(char *);

#define BYTE(p,o) (*(u8 *)((p)+(o)))
#define HALF(p,o) (*(s16 *)((p)+(o)))
#define WORD(p,o) (*(s32 *)((p)+(o)))
#define FLOAT(p,o) (*(float *)((p)+(o)))

void func_PAL_L09_0040A580(char *obj)
{
    DobboQuad position;
    char *data;
    char *target;
    int flags;
    int animation;
    float angle, speed;
    if (D_L09_001B1428) return;
    data = *(char **)(obj + 0x68);
    func_PAL_L09_00409DC8(obj);
    if (!obj || BYTE(obj,0x20) == 0xFE || BYTE(obj,0x20) == 0xFD) return;
    switch (BYTE(obj,0x95)) {
    case 0:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.0016000001f,0.040000003f,0.010053098f,0.5026549f);
            FLOAT(data,0x124)=0.0096f;
            FLOAT(data,0x134)=0.5f;
        }
        if (HALF(data,0x334)==1 && math_fast_float_d(data+0x35C)) {
            if (!math_random_int_below(4)) moby_set_state(obj,9,2);
            else moby_set_state(obj,8,2);
        } else if (HALF(data,0x336)) {
            if (!math_random_int_below(1)) moby_set_state(obj,7,1);
            else moby_set_state(obj,6,1);
            HALF(data,0x336)=0;
            if (HALF(data,0x330)<250) HALF(data,0x330)=(((int)(math_random_int_range(480,600)) * 5 + 2) / 6);
        }
        break;
    case 1:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.0032000002f,0.10000001f,0.010053098f,0.5026549f);
            FLOAT(data,0x1D0)=D_L09_001B13F4*0.020000001f;
            FLOAT(data,0x134)=0.05f;
        }
        if (HALF(data,0x334)==1) moby_set_state(obj,9,2);
        else if (!HALF(data,0x330)) moby_set_state(obj,1,0);
        break;
    case 2:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.0048f,0.10000001f,0.010053098f,0.5026549f);
            FLOAT(data,0x1D0)=D_L09_001B13F4*0.020000001f;
            FLOAT(data,0x124)=0.0096f;
            FLOAT(data,0x134)=0.05f;
            WORD(data,0x35C)=(((int)(math_random_int_range(0,30)) * 5 + 2) / 6);
        }
        if (HALF(data,0x334)!=1 && math_fast_float_d(data+0x35C)) {
            moby_set_state(obj,3,1);
            HALF(data,0x330)=(((int)(math_random_int_range(580,600)) * 5 + 2) / 6);
        }
        break;
    case 3:
        flags=moby_dispatch_action_by_kind(obj,data+0x50);
        if (flags&1) func_PAL_L09_0040A050(obj);
        else if (flags&2) {
            if (HALF(data,0x334)==1) moby_set_state(obj,9,2);
            else {
                moby_set_state(obj,3,1);
                HALF(data,0x330)=(((int)(math_random_int_range(580,600)) * 5 + 2) / 6);
            }
        }
        break;
    }
    switch (BYTE(obj,0x20)) {
    case 1:
        if (!BYTE(obj,0x31)) break;
        if (flag_set_first_pending(obj)) {
            animation=!math_random_int_below(4);
            if (BYTE(obj,0x43)!=animation) func_PAL_002A7E68(obj,animation,0,17);
            HALF(data,0x332)=(((int)(math_random_int_range(60,120)) * 5 + 2) / 6);
        }
        if (BYTE(obj,0x43)==1) {
            if (BYTE(obj,0x60)&2) func_PAL_002A7E68(obj,0,0,17);
        } else if (!HALF(data,0x332)) moby_set_state(obj,2,-1);
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            func_PAL_L09_00409AC8(obj,20);
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
        func_PAL_L09_00409F00(obj,(data+0x310),0);
        if (*(u16 *)(obj+0x96)>25 && (FLOAT(data,0x1CC)<=0.5f || *(u16 *)(obj+0x96)>150)) moby_set_state(obj,1,-1);
        break;
    case 3:
        if (flag_set_first_pending(obj)) {
            if (BYTE(obj,0x43)!=math_random_int_below(2)+4) func_PAL_002A7E68(obj,math_random_int_below(2)+4,0,8);
        }
        if (fast_vec_dist(obj+0x10,D_L09_00189EA0)<D_L09_001B13F8) moby_set_state(obj,4,-1);
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
            if (BYTE(obj,0x43)!=math_random_int_below(2)+2) func_PAL_002A7E68(obj,math_random_int_below(2)+2,0,8);
        }
        moby_check_target_point_from_offset(obj,data+0x1F0);
        if (BYTE(obj,0x60)&2) moby_set_state(obj,3,-1);
        break;
    case 7:
        if (flag_set_first_pending(obj)) {
            if (BYTE(obj,0x43)!=12) func_PAL_002A7E68(obj,12,0,8);
        }
        moby_check_target_point_from_offset(obj,data+0x1F0);
        if (BYTE(obj,0x60)&2) moby_set_state(obj,3,-1);
        break;
    case 4:
        if (flag_set_first_pending(obj)) {
            func_PAL_L09_00409B48(obj,10);
            FLOAT(data,0x238)=math_random_float_range(D_L09_001B13F8,D_L09_001B13F8_1[1])+0.5f;
        }
        if ((func_PAL_L09_00409F00(obj,data+0x300,0)&0x80) || FLOAT(data,0x238)<vec_distance_xy(obj+0x10,D_L09_00189EA0)) {
            if (math_random_int_below(2)) moby_set_state(obj,6,-1);
            else moby_set_state(obj,7,-1);
        }
        break;
    case 5:
        if (flag_set_first_pending(obj)) {
            func_PAL_L09_00409B48(obj,20);
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
        func_PAL_L09_00409F00(obj,(data+0x310),0);
        if (*(u16 *)(obj+0x96)>25 && (FLOAT(data,0x1CC)<=0.5f || *(u16 *)(obj+0x96)>150)) moby_set_state(obj,3,-1);
        break;
    case 8:
        if (flag_set_first_pending(obj)) {
            FLOAT(data,0x114)=0.025551625f;
            FLOAT(data,0x11C)=1.2775812f;
            if (BYTE(obj,0x43)!=math_random_int_below(2)+2) func_PAL_002A7E68(obj,math_random_int_below(2)+2,0,8);
        }
        target=*(char **)(data+0x200);
        func_PAL_002B5E30(obj,mat_fast_helper_a(FLOAT(target,0x10)-FLOAT(obj,0x10),FLOAT(target,0x14)-FLOAT(obj,0x14)));
        flags = BYTE(obj,0x60);
        flags &= 2;
        if (flags) {
            FLOAT(data,0x114)=0.010053098f;
            FLOAT(data,0x11C)=0.5026549f;
            moby_set_state(obj,9,-1);
        }
        break;
    case 9:
        if (flag_set_first_pending(obj)) func_PAL_L09_00409B48(obj,5);
        if (!(*(u16 *)(obj+0x96)&3)) FLOAT(data,0x33C)=moby_count_group_side_from_object(obj,*(void **)(data+0x200),-1)*0.08726647496f;
        func_PAL_L09_00409F00(obj,data+0x1F0,1);
        moby_turn_toward_target_limited(obj);
        if (FLOAT(data,0x1CC)<=1.25f) moby_set_state(obj,10,-1);
        break;
    case 10:
        if (flag_set_first_pending(obj)) {
            FLOAT(data,0x340)=mat_fast_helper_a(FLOAT(data,0x1F0)-FLOAT(obj,0x10),FLOAT(data,0x1F4)-FLOAT(obj,0x14));
            if (BYTE(obj,0x43)!=8) func_PAL_002A7E68(obj,8,2,8);
        }
        moby_start_effect_from_entry(obj,FLOAT(data,0x340));
        if (func_PAL_002AF6C0(obj,13.0f)) coll_test_hit_at_bone(obj,1,0x4000001,0,1,0,0.75f,(float)BYTE(data,0x34),1.0f);
        if (BYTE(obj,0x60)&2) moby_set_state(obj,9,-1);
        break;
    }
    func_PAL_L09_00409F38(obj);
    if (BYTE(obj,0x31)) func_PAL_L09_0040A268(obj);
}
