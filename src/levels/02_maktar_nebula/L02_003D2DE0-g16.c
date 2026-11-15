#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef struct { u8 prefix[0x2C0]; float waypoint[4]; float previousPosition[4]; } WaypointView;
/* Partial current dispatch context; the payload's full extent is not inferred. */
typedef struct {
    u8 reserved_00[0x18]; u8 enabled, count, kind; u8 reserved_1b[0x65]; u8 payload[1];
} DispatchContext;
typedef unsigned long DispatchFlags;
typedef struct { u8 prefix[0x160]; float amount; int reserved164; int kind; int detail; } EffectTuning;
extern EffectTuning D_L02_001BA3C0;
#define EFFECT (&D_L02_001BA3C0)
extern float D_L02_001B3F58 __attribute__((sda));
extern float D_L02_001B01B0[4];
extern float arenaPosition[4] SDATA(D_L02_001B01B0);
extern float D_L02_001B01C0[4] __attribute__((sda));
extern float D_L02_001B01D0[4] __attribute__((sda));
extern int D_L02_001B01E0 __attribute__((sda));
extern int D_L02_001A903C;
extern unsigned char D_001A7A60[] MACRO_ADDR;
typedef struct { u8 prefix[0x80]; float position[4]; u8 reserved90[0x240C]; char *lockTarget; } HeroPositionView;
extern HeroPositionView g_hero_state;
extern void chainblade_handle_hits(char *);
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float moby_get_anim_value(char *);
extern int flag_set_second_pending(u8 *);
extern int flag_set_first_pending(u8 *);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern void chainblade_end_chain_throw(char *);
extern int cam_hook_return_minus_one(char *);
extern void anim_start_blended(char *, int, int, int);
extern void moby_set_state(u8 *, s32, s32);
extern void chainblade_step_follow_point(char *);
extern void chainblade_steer_toward(char *, Quadword *, float, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void chainblade_clear_phase_flag(char *);
extern void brawler_advance_damage_stage(char *);
extern void arena_set_current_boss(char *, char *);
/* Keeps func_002B50E0's int result in v0. */
extern int moby_step_at_own_position(char *);
extern void chainblade_pick_idle_anim(char *, int);
extern float vec_distance_squared_xy(void *, void *);
extern int moby_l01_turn_toward_target(char *, char *);
extern float FastDiffRots(float, float);
/* Retail passes self at every site; the leaf does not read it. */
extern void chainblade_reset_trail(char *);
extern void chainblade_start_swing_hit(char *, int);
extern void chainblade_record_trail_sample(char *, int);
extern int chainblade_should_take_off(char *);
extern int chainblade_is_helper_ready(char *);
extern DispatchFlags moby_dispatch_action_by_kind(void *, DispatchContext *);
/* Extra caller slots are retained at this legacy entry; its leaf ignores them. */
extern void moby_set_anim_type_three(void *, int, int);
extern int snd_play_from_global_bank(int, int, void *);
extern void value_set_entry_by_index(int, int);
extern void part_queue_moby_for_glow(char *, int, void (*)(char *));
extern void chainblade_reset_to_idle(char *);
extern void moby_step_at_own_position_factor(u8 *, float);
extern void chainblade_pick_wander_goal(char *);
extern int FastDecTimer(short *);
extern int chainblade_should_land(char *);
extern int chainblade_move_to_throw_position(char *);
extern void vec_clear_128(Quadword *);
extern void chainblade_start_chain_throw(char *, int);
extern int chainblade_update_chain_throw(char *, int);
extern void chainblade_update_effects_timers(char *);
#define B(o) (*(u8 *)(state+(o)))
#define H(o) (*(short *)(state+(o)))
#define W(o) (*(int *)(state+(o)))
#define F(o) (*(float *)(state+(o)))
#define P(o) (*(char **)(state+(o)))
#define SET_MODE(m,r) func_002A7750((u8 *)self,(m),(r))

/* Drive the large Maktar sentry's locomotion and paired throw sequences. */
/* Per-frame update handler of the Chainblade moby (class 2552). */
void chainblade_update(char *self)
{
    char *state=*(char **)(self+0x68);
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float distance, yaw, frame, value, scale;
    int result;
    DispatchFlags events, animFlags;
    unsigned char flags;

    D_L02_001B3F58=0.7853981633974483f;
    chainblade_handle_hits(self);
    qcopy(target, P(0x30C)+0x10);
    distance=vec_distance_xy(self+0x10,target);
    yaw=mat_fast_helper_a(target[0]-*(float *)(self+0x10),target[1]-*(float *)(self+0x14));
    frame=moby_get_anim_value(self);
    flags=*(u8 *)(self+0x95);
    switch (flags) {
    case 1:
        if (flag_set_second_pending((u8 *)self)) {
            B(0xD6)=0; B(0x70)=8; W(0xA8)=3; W(0x148)&=~4; F(0x30)=3.0f;
            moby_set_controller_speed_limits((u8 *)self,0.0044444446f,0.13333334f,0.008435759f,0.20943955f);
            chainblade_end_chain_throw(self); W(0x14C)=cam_hook_return_minus_one(*(char **)(self+0xB8));
        }
    break;
    case 2:
        if (flag_set_second_pending((u8 *)self)) {
            B(0x70)=18; W(0xA8)=4; B(0xD6)=1; W(0x148)|=4;
            F(0x30)=5.0f; W(0x14C)=-1;
        }
        if (*(float *)(self+0x18)<D_L02_001B01B0[2]-1.0f)
            *(float *)(self+0x18)=D_L02_001B01B0[2]-1.0f;
    break;
    case 3:
    case 4:
        if (flag_set_second_pending((u8 *)self)) chainblade_end_chain_throw(self);
    }
    switch (*(u8 *)(self+0x20)) {
    case 1: return;
    case 2:
        if (flag_set_first_pending((u8 *)self)) {
            D_L02_001B01E0=1; *(unsigned short *)(self+0x96)=0;
            if (*(u8 *)(self+0x43)) anim_start_blended(self,0,0,10);
        }
        if (*(unsigned short *)(self+0x96)>120) {
            if (*(u8 *)(self+0x42)!=9) {
                if (*(u8 *)(self+0x43)!=9) anim_start_blended(self,9,0,10);
                *(u8 *)(self+0x95)=2; qcopy(state+0x2D0, self+0x10);
                qcopy(((WaypointView *)state)->waypoint, D_L02_001B01D0);
            } else {
                chainblade_step_follow_point(self); *(Quadword *)position=*(Quadword *)(state+0x2D0);
                chainblade_steer_toward(self,(Quadword *)position,
                    mat_fast_helper_a(target[0]-*(float *)(self+0x10),target[1]-*(float *)(self+0x14)),0.0f);
            }
        }
        if (vec_distance_xy(self+0x10,arenaPosition)<18.0f) { H(0x32E)=0; SET_MODE(20,2); }
        break;
    case 3:
        if (flag_set_first_pending((u8 *)self)) {
            if (*(u8 *)(self+0x43)!=9) anim_start_blended(self,9,0,10);
            qcopy(state+0x2D0, self+0x10);
            value=math_random_float_range(20.0f,40.0f);
            scale=0.017453294f;
            value*=scale;
            if (math_random_int_below(2)) value=-value;
            F(0x308)=value; qcopy(((WaypointView *)state)->waypoint, D_L02_001B01C0);
            chainblade_clear_phase_flag(self); brawler_advance_damage_stage(P(0x310));
            arena_set_current_boss(*(char **)(self+0xB8),P(0x310));
        }
        chainblade_step_follow_point(self); *(Quadword *)position=*(Quadword *)(state+0x2D0);
        chainblade_steer_toward(self,(Quadword *)position,
            mat_fast_helper_a(g_hero_state.position[0]-*(float *)(self+0x10),g_hero_state.position[1]-*(float *)(self+0x14)),0.0f);
        if (fast_vec_dist(self+0x10,((WaypointView *)state)->waypoint)<0.5f) SET_MODE(4,1);
        break;
    case 4:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)) anim_start_blended(self,0,0,15);
        moby_step_at_own_position(self);
        if (H(0x318)) SET_MODE(2,1);
        break;
    case 6:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)!=1) anim_start_blended(self,1,0,10);
        if (!math_random_int_below(400)) chainblade_pick_idle_anim(self,-1);
        if (vec_distance_squared_xy(target,arenaPosition)<529.0f)
            moby_l01_turn_toward_target(self,(char *)target);
        else chainblade_pick_idle_anim(self,1);
        if ((*(u8 *)(self+0x42)==1 && frame>1.0f && frame<3.0f) || (frame>16.0f && frame<18.0f)) {
            EFFECT->amount=0.05f; EFFECT->kind=25; EFFECT->detail=0;
        }
        if (distance<9.0f && FastDiffRots(yaw,*(float *)(self+0xF8))<0.087266475f
                && frame>3.0f && frame<15.0f) SET_MODE(7,1);
        break;
    case 7:
        if (flag_set_first_pending((u8 *)self)) {
            if (*(u8 *)(self+0x43)!=2) anim_start_blended(self,2,0,10);
            chainblade_reset_trail(self); *(u8 *)(self+0xBC)=0;
        }
        if (*(u8 *)(self+0x42)==2 && frame>19.0f && frame<23.0f) {
            chainblade_start_swing_hit(self,0); chainblade_record_trail_sample(self,0);
        } else if (*(u8 *)(self+0xBC)==0 && *(u8 *)(self+0x42)==2 && frame>23.0f) {
            chainblade_reset_trail(self); *(u8 *)(self+0xBC)=1;
        } else if (*(u8 *)(self+0x42)==2 && frame>32.0f && frame<36.0f) {
            chainblade_start_swing_hit(self,1); chainblade_record_trail_sample(self,1);
        } else if (*(u8 *)(self+0xBC)==1 && *(u8 *)(self+0x42)==2 && frame>36.0f) {
            chainblade_reset_trail(self); *(u8 *)(self+0xBC)=2;
        }
        if (*(u8 *)(self+0x60)&2) {
            if (chainblade_should_take_off(self) || chainblade_is_helper_ready(self)) SET_MODE(19,1); else SET_MODE(6,1);
            if (!math_random_int_below(3) || g_hero_state.lockTarget==self)
                chainblade_pick_idle_anim(self,g_hero_state.lockTarget==self ? 0 : -1);
        }
        break;
    case 8:
        qcopy(position,self+0x10);
        if (F(0x20)>0.0f) {
            events=moby_dispatch_action_by_kind(self,(void *)(state+0x60));
            if ((events&2)==2) if (chainblade_should_take_off(self) || chainblade_is_helper_ready(self)) SET_MODE(19,1); else SET_MODE(6,1);
        } else if (frame>95.0f && frame<97.0f) {
            EFFECT->amount=0.4f; EFFECT->kind=25; EFFECT->detail=0;
        } else if (frame>110.0f) SET_MODE(9,-1);
        if (vec_distance_xy(self+0x10,arenaPosition)>18.0f)
            qcopy(self+0x10, position);
        break;
    case 9:
        if (flag_set_first_pending((u8 *)self)) {
            *(int *)(self+0x48)=0; *(short *)(self+0x96)=0;
            moby_set_anim_type_three(self,0,-1); *(int *)(self+0x98)=*(int *)(*(char **)(self+0x24)+0x10);
        }
        if (*(unsigned short *)(self+0x96)>60) {
            int storyActive = D_L02_001B01E0;
            *(float *)(self+0x48)=1.0f;
            if (storyActive && !D_001A7A60[1]) {
                D_001A7A60[1]=1; snd_play_from_global_bank(1,0,0); value_set_entry_by_index(0x1233,-1); D_L02_001A903C=1;
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
            chainblade_steer_toward(self,(Quadword *)position,yaw,0.0f);
        } else moby_step_at_own_position_factor((u8 *)self,*(float *)(self+0xF8));
        if (*(u8 *)(self+0x60)&2) { SET_MODE(H(0x324),H(0x326)); *(int *)(self+0x48)=0; }
        break;
    case 11:
        if (flag_set_first_pending((u8 *)self)) {
            if (*(u8 *)(self+0x43)!=9) anim_start_blended(self,9,0,10);
            H(0x31C)=0; qcopy(state+0x2D0, self+0x10);
            value=math_random_float_range(20.0f,40.0f);
            scale=0.017453294f;
            value*=scale;
            if (math_random_int_below(2)) value=-value;
            F(0x308)=value;
        }
        chainblade_pick_wander_goal(self); chainblade_step_follow_point(self);
        *(Quadword *)position=*(Quadword *)(state+0x2D0);
        chainblade_steer_toward(self,(Quadword *)position,yaw,0.0f);
        if (!math_random_int_below(400)) chainblade_pick_idle_anim(self,0);
        if (distance<40.0f && distance>5.0f && FastDecTimer((short *)(state+0x31C))) {
            if (math_random_int_below(2)) {
                SET_MODE(12,2);
                if (!math_random_int_below(6)) chainblade_pick_idle_anim(self,0);
            } else {
                SET_MODE(15,2);
                if (!math_random_int_below(6)) chainblade_pick_idle_anim(self,0);
            }
        }
        if (chainblade_should_land(self)) SET_MODE(20,2);
        if (chainblade_is_helper_ready(self)) SET_MODE(3,2);
        break;
    case 12:
        if (flag_set_first_pending((u8 *)self)) H(0x328)=0;
        if (!H(0x328)) {
            result=chainblade_move_to_throw_position(self);
            switch (result) {
            case 0: chainblade_end_chain_throw(self); SET_MODE(11,-1); break;
            case 2:
                if (*(u8 *)(self+0x42)!=10 && *(u8 *)(self+0x43)!=10) anim_start_blended(self,10,0,7);
                break;
            }
        } else {
            *(Quadword *)position=*(Quadword *)(self+0x10);
            chainblade_steer_toward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        }
        if (!H(0x328) && *(u8 *)(self+0x42)==10 && frame>19.0f) {
            vec_clear_128((Quadword *)(state+0x1B0)); chainblade_start_chain_throw(self,0); H(0x328)=1;
        }
        if (H(0x328)) {
            result=chainblade_update_chain_throw(self,0);
            switch (result) {
            case 1: SET_MODE(14,2); break;
            case 2: chainblade_end_chain_throw(self); H(0x328)=0; break;
            }
        }
        if (H(0x328)==1 && *(u8 *)(self+0x42)==10 && frame>27.0f) SET_MODE(13,2);
        break;
    case 13:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)!=11) anim_start_blended(self,11,0,7);
        *(Quadword *)position=*(Quadword *)(self+0x10);
        chainblade_steer_toward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (H(0x328) && chainblade_update_chain_throw(self,0)==2) {
            SET_MODE(14,2); chainblade_end_chain_throw(self); H(0x328)=0;
        }
        break;
    case 14:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)!=12) anim_start_blended(self,12,0,7);
        if (H(0x328) && chainblade_update_chain_throw(self,0)==2) { chainblade_end_chain_throw(self); H(0x328)=0; }
        *(Quadword *)position=*(Quadword *)(self+0x10);
        chainblade_steer_toward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (!H(0x328) && *(u8 *)(self+0x42)==12 && frame>6.0f) { chainblade_end_chain_throw(self); SET_MODE(11,2); }
        break;
    case 15:
        if (flag_set_first_pending((u8 *)self)) H(0x328)=0;
        if (!H(0x328)) {
            result=chainblade_move_to_throw_position(self);
            switch (result) {
            case 0: chainblade_end_chain_throw(self); SET_MODE(11,-1); break;
            case 2:
                if (*(u8 *)(self+0x42)!=13 && *(u8 *)(self+0x43)!=13) anim_start_blended(self,13,0,7);
                break;
            }
        } else {
            *(Quadword *)position=*(Quadword *)(self+0x10);
            chainblade_steer_toward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        }
        if (!H(0x328) && *(u8 *)(self+0x42)==13 && frame>19.0f) {
            vec_clear_128((Quadword *)(state+0x1B0)); chainblade_start_chain_throw(self,1); H(0x328)=1;
        }
        if (H(0x328)) {
            result=chainblade_update_chain_throw(self,1);
            switch (result) {
            case 1: SET_MODE(17,2); break;
            case 2: chainblade_end_chain_throw(self); H(0x328)=0; break;
            }
        }
        if (H(0x328)==1 && *(u8 *)(self+0x42)==13 && frame>27.0f) SET_MODE(16,2);
        break;
    case 16:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)!=14) anim_start_blended(self,14,0,7);
        *(Quadword *)position=*(Quadword *)(self+0x10);
        chainblade_steer_toward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (H(0x328) && chainblade_update_chain_throw(self,1)==2) { SET_MODE(17,2); chainblade_end_chain_throw(self); H(0x328)=0; }
        break;
    case 17:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)!=15) anim_start_blended(self,15,0,7);
        if (H(0x328) && chainblade_update_chain_throw(self,1)==2) { chainblade_end_chain_throw(self); H(0x328)=0; }
        *(Quadword *)position=*(Quadword *)(self+0x10);
        chainblade_steer_toward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (!H(0x328) && *(u8 *)(self+0x42)==15 && frame>6.0f) { chainblade_end_chain_throw(self); SET_MODE(11,2); }
        break;
    case 18:
        *(Quadword *)position=*(Quadword *)(state+0x2D0);
        chainblade_steer_toward(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        events=moby_dispatch_action_by_kind(self,(void *)(state+0x60));
        if ((events&1)==1) { SET_MODE(20,2); H(0x32C)=1; break; }
        animFlags=events&2;
        goto modeEleven;
    case 19:
        if (flag_set_first_pending((u8 *)self) && *(u8 *)(self+0x43)!=17) anim_start_blended(self,17,0,10);
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
            if (*(u8 *)(self+0x43)!=9) anim_start_blended(self,9,0,10);
            chainblade_end_chain_throw(self);
        }
        if (*(float *)(self+0x18)<D_L02_001B01B0[2]+1.0f && *(float *)(self+0x18)>D_L02_001B01B0[2]) {
            if (*(u8 *)(self+0x42)!=18 && *(u8 *)(self+0x43)!=18) anim_start_blended(self,18,0,10);
            moby_step_at_own_position_factor((u8 *)self,yaw);
        } else {
            qcopy_nc(position,self+0x10); position[2]=D_L02_001B01B0[2];
            chainblade_steer_toward(self,(Quadword *)position,yaw,0.0f);
        }
        if (*(u8 *)(self+0x42)==18 && (H(0x1D0)!=0 || *(float *)(self+0x18)<D_L02_001B01B0[2]+0.2f)) {
            if (H(0x32C)) { anim_start_blended(self,4,0,3); B(0x7A)=0; SET_MODE(8,3); }
            else SET_MODE(6,1);
            if (*(u8 *)(self+0x42)==18 && frame>8.0f && frame<10.0f) {
                EFFECT->amount=0.2f; EFFECT->kind=25; EFFECT->detail=0;
            }
        }
        break;
    }
    chainblade_update_effects_timers(self);
}
