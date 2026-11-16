#include "include_asm.h"

#include "common.h"
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern int g_robot_kill_counter MACRO_ADDR;
extern int g_hero_l12_control_mode MACRO_ADDR;
struct L12GlobalState {
    char pad0[0x24]; int f24;
    char pad28[0x40]; int f68; short f6C;
    char pad6E[4]; short f72;
};
extern struct L12GlobalState g_path_shooter_state;
extern char *g_path_zone_table[];
extern void path_enemy_init_scale_pal(void *);
extern int moby_dispatch_action_by_kind(void *,void *);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *,int,int);
extern int math_random_int_below(int);
extern void anim_start_blended_pal(void *,int,int,int);
extern int enemy_claim_attack_turn(void *,int);
extern int moby_step_at_own_position_factor_pal(void *,float);
extern s32 snd_resume_music_stream(void);
extern void tourist_increment_counters(int);
extern int path_find_next_stop_point(void *,int);
extern int AimAtPathCursorAndAdvance_pal(void *);
extern float FastAddRotations(float,float);
extern int math_fast_float_d(void *);
extern int flag_set_first_pending(void *);
extern void spawn_effect_particle_ring_pal(void *);
extern void enemy_tick_timers_age(void *);

/* Updates a path-walking enemy (moby class 4076): it waits, shoots at the hero in bursts, walks its route and comes back to its start spot. */
void path_shooter_update_pal(char *obj) {
    char *vars=P(obj,0x68);
    int attack_index;
    if(g_robot_kill_counter==13) {
        if(g_hero_l12_control_mode!=2) {
            U(obj,0x34)=(U(obj,0x34)&0xFFBE)|0x1000;
            W(obj,0x98)=W(P(obj,0x24),0x10);
        } else {
            W(obj,0x98)=0;
            U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
        }
        return;
    }
    path_enemy_init_scale_pal(obj);
    switch(B(obj,0x95)) {
    case 1:
        { int flags=moby_dispatch_action_by_kind(obj,vars+0x60);
        if(flags&1) {moby_mark_spawned(obj);return;}
        if(flags&2) moby_set_state(obj,4,0); }
        break;
    case 0: break;
    }
    switch(B(obj,0x20)) {
    case 2:
        if((B(obj,0x60)&2) && enemy_claim_attack_turn(obj,W(vars,0x11C))) {
            moby_set_state(obj,8,-1);
            attack_index=math_random_int_below(4);
            if(attack_index==W(vars,0x258)) {if(attack_index!=3) attack_index++; else attack_index=0;}
            goto set_attack_animation;
        }
        break;
    case 8:
        moby_step_at_own_position_factor_pal(obj,F(vars,0x228));
        if(g_path_shooter_state.f72==3 && g_path_shooter_state.f6C<6000) {
            snd_resume_music_stream(); moby_set_state(obj,5,-1);
        }
        break;
    case 5:
        if(!g_path_shooter_state.f68 && g_path_shooter_state.f24==-1) {
            tourist_increment_counters(W(vars,0x114));
            moby_set_state(obj,6,-1);
            if(B(obj,0x43)) anim_start_blended_pal(obj,0,0,17);
            W(vars,0x220)=path_find_next_stop_point(obj,W(vars,0x224));
        } else if(B(obj,0x60)&2) {
            attack_index=math_random_int_below(4);
            if(attack_index==W(vars,0x258)) {if(attack_index!=3)attack_index++;else attack_index=0;}
            if(B(obj,0x43)!=attack_index+1) anim_start_blended_pal(obj,attack_index+1,0,17);
            W(vars,0x258)=attack_index;
        }
        break;
    case 6:
        if(AimAtPathCursorAndAdvance_pal(obj)) {
            if(W(vars,0x220)==W(g_path_zone_table[W(vars,0x110)],0)-1) {
                moby_set_state(obj,3,-1);
                if(B(obj,0x43)!=9)anim_start_blended_pal(obj,9,0,17);
            } else {
                moby_set_state(obj,7,-1);
                if(B(obj,0x43))anim_start_blended_pal(obj,0,0,17);
                W(vars,0x22C)=100;
                F(vars,0x228)=FastAddRotations(F(obj,0xF8),3.141590118408203f);
            }
        }
        break;
    case 7:
        moby_step_at_own_position_factor_pal(obj,F(vars,0x228));
        if(math_fast_float_d(vars+0x22C) && enemy_claim_attack_turn(obj,W(vars,0x11C))) {
            moby_set_state(obj,8,-1);
            attack_index=math_random_int_below(4);
            if(attack_index==W(vars,0x258)){if(attack_index!=3)attack_index++;else attack_index=0;}
set_attack_animation:
            if(B(obj,0x43)!=attack_index+1)anim_start_blended_pal(obj,attack_index+1,0,17);
            W(vars,0x258)=attack_index;
            W(vars,0x11C)++;
        }
        break;
    case 3:
        if(B(obj,0x60)&2) {
            W(vars,0x220)=0; W(vars,0x224)=0; W(vars,0x11C)=0;
            moby_set_state(obj,10,-1);
        }
        break;
    case 10:
        if(flag_set_first_pending(obj)) {
            W(vars,0x25C)=21; W(obj,0x98)=0;
            U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
        }
        if(math_fast_float_d(vars+0x25C)) {
            moby_set_state(obj,1,-1);
            qcopy(obj+0x10,vars+0x210);
        }
        spawn_effect_particle_ring_pal(obj);
        break;
    case 1:
        W(obj,0x98)=0; U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
        break;
    }
    enemy_tick_timers_age(obj);
}
