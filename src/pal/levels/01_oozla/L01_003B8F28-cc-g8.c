#include "names.h"
/* func_PAL_L01_003B8F28, the PAL copy of func_L01_003B53C8: the same C, where rename func_002B0ED8 becomes func_PAL_002B1A50; rename func_002A7470 becomes func_PAL_002A7E68; rename func_002AEC48 becomes func_PAL_L01_003BEB40; rename func_L01_003B4480 becomes func_PAL_L01_003B7FC0; lit 0.3f becomes 0.43200004f; rename func_PAL_L01_003BEB40 becomes func_002AEC48; rename func_L01_003BAFB0 becomes func_PAL_L01_003BEB40. */
#include "common.h"

float func_PAL_L01_003BEB40(void);

void swamp_beast_alert_group(u8 *arg0);

/* func_L01_003B57A8 is defined in L01_003835D8.c. */

#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
extern int g_current_map_index MACRO_ADDR;
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern float fast_vec_dist(void *,void *);
extern void func_PAL_002A7E68(void *,int,int,int);
extern void moby_set_state(void *,int,int);
#define P(p,o) (*(int **)((u8 *)(p)+(o)))
#define C(p,o) (*(u8 **)((u8 *)(p)+(o)))
typedef int OozlaQuad __attribute__((mode(TI)));
extern float g_level_origin_vec[];
typedef struct { u8 pad[0x2290]; u8 *target; } OozlaHero;
extern OozlaHero g_hero_state;
extern float g_hero_position[];
extern int g_oozla_intro_stage MACRO_ADDR;
extern void moby_update_ground_check(void *);
extern int weapon_select_aim_target(void *,int,int,int,float,float);
extern float vec_distance_xy(void *,void *);
extern char *moby_get_private_value_0(u8 *);
extern int func_PAL_002B1A50(void *,void *,int);
extern void swamp_beast_release_group_slot(void *);
extern float mat_fast_helper_a(float,float);
extern float fast_subtract_rotations(float,float);
extern void moby_update_eased_node(void *,void *,int,float,float);
extern int math_random_int_below(int);
extern void swamp_beast_spawn_bubbles_pal(void *);
extern int GetFirstMobyInGroup(void *,int,int,int);
extern int GetNextMobyInGroup(void *,void *,int,int);
void func_PAL_L01_003B8F28(u8 *object)
{
    OozlaQuad saved[2];
    u8 *iterator;
    u8 *common;
    u8 *state = C(object,0x68);
    u8 *target, *detail;
    float angle, distance, best;
    if (object[0x31] && fast_vec_dist(object+0x10,g_level_origin_vec) < 24.0f) {
        moby_update_ground_check(object);
        object[0x6F] = 22;
    }
    saved[0] = *(OozlaQuad *)(state+0x230);
    saved[1] = *(OozlaQuad *)(state+0x240);
    if (weapon_select_aim_target(object,I(state,0x398),0,0,F(state,0x388),0.5f) != 1 && ((int *)saved)[5] == 1) {
        target = ((u8 **)saved)[4];
        if (target && target[0x20] != 254 && target[0x20] != 253 && vec_distance_xy(object+0x10,target+0x10) < F(state,0x39C)) {
            *(OozlaQuad *)(state+0x230) = saved[0];
            *(OozlaQuad *)(state+0x240) = saved[1];
            target = C(state,0x240);
            if (target == g_hero_state.target) {
                qcopy(state+0x230, (u8 *)&g_hero_state+0xD0);
            } else {
                qcopy(state+0x230, target+0x10);
                detail = (u8 *)moby_get_private_value_0(target);
                if (detail) F(state,0x238) += F(detail,0x10);
            }
        }
    }
    common = C(object,0x68);
    if (func_PAL_002B1A50(object,common+0x60,0)) {
        if (F(common,0x20) <= 0.0f) I(common,0xDC) = -1;
        else I(common,0xDC) = I(common,0x14C);
        swamp_beast_release_group_slot(object);
        swamp_beast_alert_group(object);
        if (object[0x95] < 3) {
            common[0x7A] = 2;
            if (object[0x43] != 4) func_PAL_002A7E68(object,4,0,15);
            I(common,0x320) = 0;
            moby_set_state(object,1,1);
        }
    }
    if (object[0x31]) {
        u8 *goal = C(state,0x240);
        angle = mat_fast_helper_a(F(goal,0x10)-F(object,0x10),F(goal,0x14)-F(object,0x14));
        F(state,0x2B8) = fast_subtract_rotations(angle,F(object,0xF8));
        moby_update_eased_node(object,state+0x250,4,0.0432f,0.43200004f);
        if (F(object,0x18) <= func_PAL_L01_003BEB40()+0.3f && (object[0x95] >= 2 || math_random_int_below(9) == 0))
            swamp_beast_spawn_bubbles_pal(object);
    }
    if (object[0x21] != 255 && *P(state,0x368) != g_oozla_intro_stage) {
        if (*P(state,0x36C) == -1 || *P(state,0x368) < g_oozla_intro_stage-10) {
            *P(state,0x36C) = -1;
            *P(state,0x370) = -1;
            best = 100000.0f;
            GetFirstMobyInGroup(&iterator,object[0x21],0,0);
            while (iterator) {
                if (*(short *)(iterator+0xAA) == *(short *)(object+0xAA)) {
                    distance = vec_distance_xy(iterator+0x10,g_hero_position);
                    if (distance < best && iterator[0x95] == 3 && iterator[0x20] < 3) {
                        best = distance;
                        *P(state,0x370) = *P(state,0x36C);
                        *P(state,0x36C) = *(short *)(iterator+0xB2);
                    }
                }
                GetNextMobyInGroup(&iterator,iterator,0,0);
            }
            *P(state,0x368) = g_oozla_intro_stage;
        }
    }
}
