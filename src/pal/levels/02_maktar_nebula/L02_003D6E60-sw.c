#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef struct { u8 prefix[0x2C0]; float waypoint[4]; float previousPosition[4]; } WaypointView;
typedef struct {
    u8 reserved_00[0x18]; u8 enabled, count, kind; u8 reserved_1b[0x65]; u8 payload[1];
} DispatchContext;
typedef unsigned long DispatchFlags;
typedef struct { u8 prefix[0x160]; float amount; int reserved164; int kind; int detail; } EffectTuning;
extern EffectTuning g_hero_effect_state;
#define EFFECT (&D_L02_001BA3C0)
extern float g_chainblade_angle_step __attribute__((sda));
extern float g_chainblade_landing_point[4];
extern float arenaPosition[4] SDATA(D_L02_001B01B0);
extern float g_chainblade_start_waypoint[4] __attribute__((sda));
extern float g_chainblade_alt_waypoint[4] __attribute__((sda));
extern int g_chainblade_story_active __attribute__((sda));
extern int g_one_shot_flag;
extern unsigned char g_item_enabled_flags[] MACRO_ADDR;
typedef struct { u8 prefix[0x80]; float position[4]; u8 reserved90[0x240C]; char *lockTarget; } HeroPositionView;
extern HeroPositionView g_hero_state;
extern void chainblade_handle_hits_pal(char *);
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float moby_get_anim_value(char *);
extern int flag_set_second_pending(u8 *);
extern int flag_set_first_pending(u8 *);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern void chainblade_end_chain_throw(char *);
extern int cam_hook_return_minus_one(char *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void moby_set_state(u8 *, s32, s32);
extern void chainblade_step_follow_point_pal(char *);
extern void chainblade_steer_toward_pal(char *, Quadword *, float, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void chainblade_clear_phase_flag(char *);
extern void brawler_advance_damage_stage(char *);
extern void arena_set_current_boss(char *, char *);
extern int moby_step_at_own_position_pal(char *);
extern void func_PAL_L02_003D8B70(char *, int);
extern float vec_distance_squared_xy(void *, void *);
extern int moby_l01_turn_toward_target_pal(char *, char *);
extern float FastDiffRots(float, float);
extern void chainblade_reset_trail(char *);
extern void chainblade_start_swing_hit(char *, int);
extern void chainblade_record_trail_sample_pal(char *, int);
extern int func_PAL_L02_003D8D80(char *);
extern int chainblade_is_helper_ready(char *);
extern DispatchFlags moby_dispatch_action_by_kind(void *, DispatchContext *);
extern void moby_set_anim_type_three_pal(void *, int, int);
extern int snd_play_from_global_bank(int, int, void *);
extern void value_set_entry_by_index_pal(int, int);
extern void part_queue_moby_for_glow(char *, int, void (*)(char *));
extern void chainblade_reset_to_idle(char *);
extern int moby_step_at_own_position_factor_pal(u8 *, float);
extern void chainblade_pick_wander_goal(char *);
extern int FastDecTimer(short *);
extern int func_PAL_L02_003D8E08(char *);
extern int chainblade_move_to_throw_position_pal(char *);
extern void vec_clear_128(Quadword *);
extern void chainblade_start_chain_throw(char *, int);
extern int func_PAL_L02_003D9808(char *, int);
extern void chainblade_update_effects_timers_pal(char *);
#define B(o) (*(u8 *)(state+(o)))
#define H(o) (*(short *)(state+(o)))
#define W(o) (*(int *)(state+(o)))
#define F(o) (*(float *)(state+(o)))
#define P(o) (*(char **)(state+(o)))
#define SET_MODE(m,r) func_002A7750((u8 *)self,(m),(r))

/* Drive the large Maktar sentry's locomotion and paired throw sequences. */
void chainblade_update_pal(char *self)
{
    char *state=*(char **)(self+0x68);
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float distance, yaw, frame, value, scale;
    int result;
    DispatchFlags events, animFlags;
    unsigned char flags;

    g_chainblade_angle_step=0.7853981633974483f;
    chainblade_handle_hits_pal(self);
    qcopy(target, P(0x30C)+0x10);
    distance=vec_distance_xy(self+0x10,target);
    yaw=mat_fast_helper_a(target[0]-*(float *)(self+0x10),target[1]-*(float *)(self+0x14));
    frame=moby_get_anim_value(self);
    flags=*(u8 *)(self+0x95);
    switch (flags) {
    case 1:
        if (flag_set_second_pending((u8 *)self)) {
            B(0xD6)=0; B(0x70)=8; W(0xA8)=3; W(0x148)&=~4; F(0x30)=3.0f;
            moby_set_controller_speed_limits((u8 *)self,0.0064000003f,0.16000001f,0.012147494f,0.25132746f);
            chainblade_end_chain_throw(self); W(0x14C)=cam_hook_return_minus_one(*(char **)(self+0xB8));
        }
    break;
    case 2:
        if (flag_set_second_pending((u8 *)self)) {
            B(0x70)=18; W(0xA8)=4; B(0xD6)=1; W(0x148)|=4;
            F(0x30)=5.0f; W(0x14C)=-1;
        }
        if (*(float *)(self+0x18)<g_chainblade_landing_point[2]-1.0f)
            *(float *)(self+0x18)=g_chainblade_landing_point[2]-1.0f;
    break;
    case 3:
    case 4:
        if (flag_set_second_pending((u8 *)self)) chainblade_end_chain_throw(self);
    }
    switch (*(u8 *)(self+0x20)) {
    case 1: return;
    case 2:
        if (flag_set_first_pending((u8 *)self)) {
            g_chainblade_story_active=1; *(unsigned short *)(self+0x96)=0;
            if (*(u8 *)(self+0x43)) func_PAL_002A7E68(self,0,0,8);
        }
        if (*(unsigned short *)(self+0x96)>120) {
            if (*(u8 *)(self+0x42)!=9) {
                if (*(u8 *)(self+0x43)!=9) func_PAL_002A7E68(self,9,0,8);
                *(u8 *)(self+0x95)=2; qcopy(state+0x2D0, self+0x10);
                qcopy(((WaypointView *)state)->waypoint, g_chainblade_alt_waypoint);
            } else {
                chainblade_step_follow_point_pal(self); *(Quadword *)position=*(Quadword *)(state+0x2D0);
                chainblade_steer_toward_pal(self,(Quadword *)position,
                    mat_fast_helper_a(target[0]-*(float *)(self+0x10),target[1]-*(float *)(self+0x14)),0.0f);
            }
        }
        if (vec_distance_xy(self+0x10,arenaPosition)<18.0f) { H(0x32E)=0; SET_MODE(20,2); }
        break;
    case 3:
        if (flag_set_first_pending((u8 *)self)) {
            if (*(u8 *)(self+0x43)!=9) func_PAL_002A7E68(self,9,0,8);
            qcopy(state+0x2D0, self+0x10);
            value=math_random_float_range(20.0f,40.0f);
            scale=0.017453294f;
            value*=scale;
            if (math_random_int_below(2)) value=-value;
            F(0x308)=value; qcopy(((WaypointView *)state)->waypoint, g_chainblade_start_waypoint);
            chainblade_clear_phase_flag(self); brawler_advance_damage_stage(P(0x310));
            arena_set_current_boss(*(char **)(self+0xB8),P(0x310));
        }
        chainblade_step_follow_point_pal(self); *(Quadword *)position=*(Quadword *)(state+0x2D0);
        chainblade_steer_toward_pal(self,(Quadword *)position,
            mat_fast_helper_a(g_hero_state.position[0]-*(float *)(self+0x10),g_hero_state.position[1]-*(float *)(self+0x14)),0.0f);
        if (fast_vec_dist(self+0x10,((WaypointView *)state)->waypoint)<0.5f) SET_MODE(4,1);
        break;
    case 4:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)) func_PAL_002A7E68(self,0,0,12);
        moby_step_at_own_position_pal(self);
        if (H(0x318)) SET_MODE(2,1);
        break;
    case 6:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)!=1) func_PAL_002A7E68(self,1,0,8);
        if (!math_random_int_below(400)) func_PAL_L02_003D8B70(self,-1);
        if (vec_distance_squared_xy(target,arenaPosition)<529.0f)
            moby_l01_turn_toward_target_pal(self,(char *)target);
        else func_PAL_L02_003D8B70(self,1);
        if ((*(u8 *)(self+0x42)==1 && frame>1.0f && frame<3.0f) || (frame>16.0f && frame<18.0f)) {
            EFFECT->amount=0.05f; EFFECT->kind=21; EFFECT->detail=0;
        }
        if (distance<9.0f && FastDiffRots(yaw,*(float *)(self+0xF8))<0.087266475f
                && frame>3.0f && frame<15.0f) SET_MODE(7,1);
        break;
    case 7:
        if (flag_set_first_pending((u8 *)self)) {
            if (*(u8 *)(self+0x43)!=2) func_PAL_002A7E68(self,2,0,8);
            chainblade_reset_trail(self); *(u8 *)(self+0xBC)=0;
        }
        if (*(u8 *)(self+0x42)==2 && frame>19.0f && frame<23.0f) {
            chainblade_start_swing_hit(self,0); chainblade_record_trail_sample_pal(self,0);
        } else if (*(u8 *)(self+0xBC)==0 && *(u8 *)(self+0x42)==2 && frame>23.0f) {
            chainblade_reset_trail(self); *(u8 *)(self+0xBC)=1;
        } else if (*(u8 *)(self+0x42)==2 && frame>32.0f && frame<36.0f) {
            chainblade_start_swing_hit(self,1); chainblade_record_trail_sample_pal(self,1);
        } else if (*(u8 *)(self+0xBC)==1 && *(u8 *)(self+0x42)==2 && frame>36.0f) {
            chainblade_reset_trail(self); *(u8 *)(self+0xBC)=2;
        }
        if (*(u8 *)(self+0x60)&2) {
            if (func_PAL_L02_003D8D80(self) || chainblade_is_helper_ready(self)) SET_MODE(19,1); else SET_MODE(6,1);
            if (!math_random_int_below(3) || g_hero_state.lockTarget==self)
                func_PAL_L02_003D8B70(self,g_hero_state.lockTarget==self ? 0 : -1);
        }
        break;
    case 8:
        qcopy(position,self+0x10);
        if (F(0x20)>0.0f) {
            events=moby_dispatch_action_by_kind(self,(void *)(state+0x60));
            if ((events&2)==2) if (func_PAL_L02_003D8D80(self) || chainblade_is_helper_ready(self)) SET_MODE(19,1); else SET_MODE(6,1);
        } else if (frame>95.0f && frame<97.0f) {
            EFFECT->amount=0.4f; EFFECT->kind=21; EFFECT->detail=0;
        } else if (frame>110.0f) SET_MODE(9,-1);
        if (vec_distance_xy(self+0x10,arenaPosition)>18.0f)
            qcopy(self+0x10, position);
        break;
    case 9:
        if (flag_set_first_pending((u8 *)self)) {
            *(int *)(self+0x48)=0; *(short *)(self+0x96)=0;
            moby_set_anim_type_three_pal(self,0,-1); *(int *)(self+0x98)=*(int *)(*(char **)(self+0x24)+0x10);
        }
        if (*(unsigned short *)(self+0x96)>50) {
            int storyActive = g_chainblade_story_active;
            *(float *)(self+0x48)=1.0f;
            if (storyActive && !g_item_enabled_flags[1]) {
                g_item_enabled_flags[1]=1; snd_play_from_global_bank(1,0,0); value_set_entry_by_index_pal(0x1233,-1); g_one_shot_flag=1;
            }
            part_queue_moby_for_glow(self,0,chainblade_reset_to_idle);
            if (P(0x310) && (u8)P(0x310)[0x20]!=254 && (u8)P(0x310)[0x20]!=253 && (u8)P(0x310)[0x20]>2) {
                brawler_advance_damage_stage(P(0x310)); arena_set_current_boss(*(char **)(self+0xB8),P(0x310));
            }
        }
        break;
    case 10:
        if (*(u8 *)(self+0x95)==2) {
            *(Quadword *)position=*(Quadword *)((WaypointView *)state)->waypoint;
            chainblade_steer_toward_pal(self,(Quadword *)position,yaw,0.0f);
        } else moby_step_at_own_position_factor_pal((u8 *)self,*(float *)(self+0xF8));
        if (*(u8 *)(self+0x60)&2) { SET_MODE(H(0x324),H(0x326)); *(int *)(self+0x48)=0; }
        break;
    case 11:
        if (flag_set_first_pending((u8 *)self)) {
            if (*(u8 *)(self+0x43)!=9) func_PAL_002A7E68(self,9,0,8);
            H(0x31C)=0; qcopy(state+0x2D0, self+0x10);
            value=math_random_float_range(20.0f,40.0f);
            scale=0.017453294f;
            value*=scale;
            if (math_random_int_below(2)) value=-value;
            F(0x308)=value;
        }
        chainblade_pick_wander_goal(self); chainblade_step_follow_point_pal(self);
        *(Quadword *)position=*(Quadword *)(state+0x2D0);
        chainblade_steer_toward_pal(self,(Quadword *)position,yaw,0.0f);
        if (!math_random_int_below(400)) func_PAL_L02_003D8B70(self,0);
        if (distance<40.0f && distance>5.0f && FastDecTimer((short *)(state+0x31C))) {
            if (math_random_int_below(2)) {
                SET_MODE(12,2);
                if (!math_random_int_below(6)) func_PAL_L02_003D8B70(self,0);
            } else {
                SET_MODE(15,2);
                if (!math_random_int_below(6)) func_PAL_L02_003D8B70(self,0);
            }
        }
        if (func_PAL_L02_003D8E08(self)) SET_MODE(20,2);
        if (chainblade_is_helper_ready(self)) SET_MODE(3,2);
        break;
    case 12:
        if (flag_set_first_pending((u8 *)self)) H(0x328)=0;
        if (!H(0x328)) {
            result=chainblade_move_to_throw_position_pal(self);
            switch (result) {
            case 0: chainblade_end_chain_throw(self); SET_MODE(11,-1); break;
            case 2:
                if (*(u8 *)(self+0x42)!=10 && *(u8 *)(self+0x43)!=10) func_PAL_002A7E68(self,10,0,6);
                break;
            }
        } else {
            *(Quadword *)position=*(Quadword *)(self+0x10);
            chainblade_steer_toward_pal(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        }
        if (!H(0x328) && *(u8 *)(self+0x42)==10 && frame>19.0f) {
            vec_clear_128((Quadword *)(state+0x1B0)); chainblade_start_chain_throw(self,0); H(0x328)=1;
        }
        if (H(0x328)) {
            result=func_PAL_L02_003D9808(self,0);
            switch (result) {
            case 1: SET_MODE(14,2); break;
            case 2: chainblade_end_chain_throw(self); H(0x328)=0; break;
            }
        }
        if (H(0x328)==1 && *(u8 *)(self+0x42)==10 && frame>27.0f) SET_MODE(13,2);
        break;
    case 13:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)!=11) func_PAL_002A7E68(self,11,0,6);
        *(Quadword *)position=*(Quadword *)(self+0x10);
        chainblade_steer_toward_pal(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (H(0x328) && func_PAL_L02_003D9808(self,0)==2) {
            SET_MODE(14,2); chainblade_end_chain_throw(self); H(0x328)=0;
        }
        break;
    case 14:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)!=12) func_PAL_002A7E68(self,12,0,6);
        if (H(0x328) && func_PAL_L02_003D9808(self,0)==2) { chainblade_end_chain_throw(self); H(0x328)=0; }
        *(Quadword *)position=*(Quadword *)(self+0x10);
        chainblade_steer_toward_pal(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (!H(0x328) && *(u8 *)(self+0x42)==12 && frame>6.0f) { chainblade_end_chain_throw(self); SET_MODE(11,2); }
        break;
    case 15:
        if (flag_set_first_pending((u8 *)self)) H(0x328)=0;
        if (!H(0x328)) {
            result=chainblade_move_to_throw_position_pal(self);
            switch (result) {
            case 0: chainblade_end_chain_throw(self); SET_MODE(11,-1); break;
            case 2:
                if (*(u8 *)(self+0x42)!=13 && *(u8 *)(self+0x43)!=13) func_PAL_002A7E68(self,13,0,6);
                break;
            }
        } else {
            *(Quadword *)position=*(Quadword *)(self+0x10);
            chainblade_steer_toward_pal(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        }
        if (!H(0x328) && *(u8 *)(self+0x42)==13 && frame>19.0f) {
            vec_clear_128((Quadword *)(state+0x1B0)); chainblade_start_chain_throw(self,1); H(0x328)=1;
        }
        if (H(0x328)) {
            result=func_PAL_L02_003D9808(self,1);
            switch (result) {
            case 1: SET_MODE(17,2); break;
            case 2: chainblade_end_chain_throw(self); H(0x328)=0; break;
            }
        }
        if (H(0x328)==1 && *(u8 *)(self+0x42)==13 && frame>27.0f) SET_MODE(16,2);
        break;
    case 16:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)!=14) func_PAL_002A7E68(self,14,0,6);
        *(Quadword *)position=*(Quadword *)(self+0x10);
        chainblade_steer_toward_pal(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (H(0x328) && func_PAL_L02_003D9808(self,1)==2) { SET_MODE(17,2); chainblade_end_chain_throw(self); H(0x328)=0; }
        break;
    case 17:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)!=15) func_PAL_002A7E68(self,15,0,6);
        if (H(0x328) && func_PAL_L02_003D9808(self,1)==2) { chainblade_end_chain_throw(self); H(0x328)=0; }
        *(Quadword *)position=*(Quadword *)(self+0x10);
        chainblade_steer_toward_pal(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (!H(0x328) && *(u8 *)(self+0x42)==15 && frame>6.0f) { chainblade_end_chain_throw(self); SET_MODE(11,2); }
        break;
    case 18:
        *(Quadword *)position=*(Quadword *)(state+0x2D0);
        chainblade_steer_toward_pal(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        events=moby_dispatch_action_by_kind(self,(void *)(state+0x60));
        if ((events&1)==1) { SET_MODE(20,2); H(0x32C)=1; break; }
        animFlags=events&2;
        goto modeEleven;
    case 19:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)!=17) func_PAL_002A7E68(self,17,0,8);
        { float animationFrame=moby_get_anim_value(self);
        if (*(u8 *)(self+0x42)==17 && animationFrame>9.0f) { *(u8 *)(self+0x95)=2; *(u8 *)(self+0xBE)&=~2; }
        animFlags=*(u8 *)(self+0x60)&2;
        }
    modeEleven:
        if (animFlags) SET_MODE(11,2);
        break;
    case 20:
        if (flag_set_first_pending((u8 *)self)) {
            W(0x148)&=~4;
            if (*(u8 *)(self+0x43)!=9) func_PAL_002A7E68(self,9,0,8);
            chainblade_end_chain_throw(self);
        }
        if (*(float *)(self+0x18)<g_chainblade_landing_point[2]+1.0f && *(float *)(self+0x18)>g_chainblade_landing_point[2]) {
            if (*(u8 *)(self+0x42)!=18 && *(u8 *)(self+0x43)!=18) func_PAL_002A7E68(self,18,0,8);
            moby_step_at_own_position_factor_pal((u8 *)self,yaw);
        } else {
            qcopy_nc(position,self+0x10); position[2]=g_chainblade_landing_point[2];
            chainblade_steer_toward_pal(self,(Quadword *)position,yaw,0.0f);
        }
        if (*(u8 *)(self+0x42)==18 && (H(0x1D0)!=0 || *(float *)(self+0x18)<g_chainblade_landing_point[2]+0.2f)) {
            if (H(0x32C)) { func_PAL_002A7E68(self,4,0,2); B(0x7A)=0; SET_MODE(8,3); }
            else SET_MODE(6,1);
            if (*(u8 *)(self+0x42)==18 && frame>8.0f && frame<10.0f) {
                EFFECT->amount=0.2f; EFFECT->kind=21; EFFECT->detail=0;
            }
        }
        break;
    }
    chainblade_update_effects_timers_pal(self);
}
