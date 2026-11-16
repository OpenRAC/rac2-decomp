/* func_PAL_L23_003C2268, the PAL copy of func_L23_003BEA00: the same C, where rename func_L23_003BF9B0 becomes func_PAL_L23_003C3258; rename func_0032C700 becomes func_PAL_L00_003FB330; rename func_L23_003BFFC0 becomes func_PAL_L23_003C3868; rename func_L23_003C00D0 becomes func_PAL_L23_003C3978; rename func_L23_003C01F8 becomes func_PAL_L23_003C3AA0; rename func_L23_003C1B58 becomes func_PAL_L23_003C5480; rename func_L11_003404E0 becomes func_PAL_L11_00342558; rename func_L23_003C02C8 becomes func_PAL_L23_003C3B70; rename func_002AEB60 becomes func_PAL_002AF6C0; rename func_L23_003BFE90 becomes func_PAL_L23_003C3738; rename func_L23_003C16D8 becomes func_PAL_L23_003C4FC0; rename func_L23_003C1AE8 becomes func_PAL_L23_003C5410; .... */
#include "common.h"

/* func_PAL_L23_003C2268 is a unit of its own: it reads $gp (hence -g8) and has a switch.
   Two return types decide its bytes, and both are the callees' real ones:
   - func_PAL_L11_00342558 returns int: it leaves func_L02_00333480's status in v0, which that function
     sets on every path. A call's unused result still occupies v0 for a local set by the next insn,
     so the f110 test right after the call loads into v1 as retail does.
   - func_002A8F70 is void (002A7750-records.c): a result would change the post-reload ranking of
     its argument setup. */

typedef int Quad __attribute__((mode(TI)));
typedef struct Moby_003BF9B0 Moby_003BF9B0;
typedef struct {
    u8 reserved_00[0x18]; u8 enabled,count,kind;
    u8 reserved_1b[0x65]; u8 payload[1];
} Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext;
typedef struct {
    u8 pad_000[0x26];
    short f26;
    u8 pad_028[0x10];
    char * f38;
    u8 pad_03C[0xD4];
    short f110;
    u8 pad_112[0x62];
    float f174;
    unsigned short f178;
    u8 pad_17A[0xD6];
    int f250;
    u8 pad_254[0x1C];
    float f270;
    u8 pad_274[0x8];
    float f27C;
    u8 pad_280[0x20];
    char * f2A0;
    short f2A4;
    short f2A6;
    float f2A8;
    u8 pad_2AC[0x74];
    char * f320;
    short f324;
    short f326;
    char * f328;
    char * f32C;
    u8 pad_330[0x84];
    int f3B4;
    float f3B8;
    short f3BC;
    short f3BE;
} DispatchState;
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
extern int g_boss_part_age_counter,g_enemy_effect_param;
extern u8 *g_selected_moby;
typedef struct { u8 pad00[0x80]; float position[4] __attribute__((aligned(16))); u8 pad90[0x2200]; u8 *object; } DispatchHero;
extern DispatchHero g_hero_state;
extern u8 *g_hero_moby __attribute__((nosda));
extern float g_mothership_surface_radius,g_mothership_effect_radius,g_mothership_impact_param;
extern float g_boss_hit_point[4] __attribute__((aligned(16))) MACRO_ADDR;
extern float g_coll_line_hit_point_2[] __attribute__((aligned(16)));
extern u8 g_hero_target_point[];
extern float g_mothership_state_param_b;
extern float g_enemy_state_anim_blend __attribute__((sda));
extern int g_beam_level_limit __attribute__((sda));
extern float g_enemy_arrive_distance __attribute__((sda));
extern float g_enemy_timer_float_base __attribute__((sda));
extern float g_enemy_timer_float_alt __attribute__((sda));
extern float g_enemy_timer_float_idle __attribute__((sda));
extern float g_enemy_range __attribute__((sda));
extern float g_enemy_facing_limit __attribute__((sda));
extern float g_enemy_attack_time_limit __attribute__((sda));
extern float g_enemy_chase_time_limit __attribute__((sda));
extern float g_enemy_min_state_time __attribute__((sda));
extern float g_enemy_retreat_time_limit __attribute__((sda));
extern int g_enemy_high_health_threshold __attribute__((sda));
extern int g_enemy_low_health_threshold __attribute__((sda));
extern int g_enemy_flee_health_threshold __attribute__((sda));
extern void flying_enemy_init_and_update_pal(Moby_003BF9B0 *);
extern int boss_is_fight_state_four(void),boss_pick_random_ready_attack(void);
extern void part_start_effect_default_table(int,int,int,int,float);
extern void part_queue_impact_effect(int,int,int,int,int,float);
extern int coll_sweep_from_object(void *,void *,int,int,int,int,float,float,float);
extern u8 *SpawnExplosion_pal(void *,int,int,int,int,int,int,int,float,float,int,int,int,void *);
extern void moby_clear_selected(char *),moby_stop_effects(char *);
extern void moby_reset_idle_clear_links(char *),enemy_reset_calm_pal(char *);
extern void enemy_relocate_near_hero_pal(char *),tether_update_glow_pal(char *);
extern void child_update_orientation_pal(char *),moby_tick_timers(char *);
extern void gfx_draw_pulsing_beam(void *);
extern void enemy_snap_to_ground_pal(char *,int);
extern void path_following_update_pal(u8 *);
extern float gravity_get_center_distance(char *);
extern void FastVecSub(void *,void *,void *);
extern float moby_measure_step_angle(char *,Quad *,char *);
extern float fast_vec_dist(void *,void *),FastVecLength(void *);
extern int IsPathClear(void *,void *,void *);
extern void mothership_project_point_onto_surface(char *,float);
extern unsigned long moby_dispatch_action_by_kind(void *,Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *);
extern void snd_stop_voice(int);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float),FastVecScale(void *,void *,float);
extern int snd_play_from_class_bank(int,int,char *,int);
extern void stored_object_forward(int,int);
extern int flag_set_first_pending(u8 *),flag_set_second_pending(u8 *);
extern int snd_start_in_slot(int,int,int);
extern void moby_play_anim_and_link_pal(char *,int,int,int,int,float);
extern void hero_launch_hit_effect_pal(char *,float,int,int);
extern void moby_set_state(u8 *,s32,int);
extern void gfx_add_draw_callback_first(void (*)(void *),void *);
extern int moby_call_helper_with_blocks_pal(char *);
extern int CollLine(void *,void *,int,void *,void *);
extern float moby_get_anim_value(char *),math_random_float_range(float,float);
extern int math_is_value_within_step_pal(char *,float);
extern void *ribbon_trail_create(u8 *,u8 *,u8 *,u8,u8,float,float,float,float,short,short,int,int,int,int,int);
extern void moby_transform_joint_to_world(char *,int,char *);
extern int queue_copy_record_by_index(unsigned int);

/* Runs the enemy's state machine: updates its distance to the hero, then handles its states (idle, charge, beam attack, retreat). (PAL) */
void enemy_update_state_machine_pal(u8 *moby)
{
    float difference[4] __attribute__((aligned(16))),point[4] __attribute__((aligned(16))),local[4] __attribute__((aligned(16)));
    char *vars=*(char **)(moby+0x68);
    int facing,selected,index,mask;
    unsigned long flags;
    float distance,range;
    flying_enemy_init_and_update_pal((Moby_003BF9B0 *)moby);
    if (g_boss_part_age_counter>200) return;
    if (boss_is_fight_state_four())
        part_start_effect_default_table((int)moby,(int)moby,0x10000,(int)(moby+0x10),(float)g_enemy_effect_param);
    selected=g_selected_moby==moby;
    facing=0;
    ((DispatchState *)vars)->f326=0;
    if (selected && (unsigned int)(moby[0x20]-9)>2)
        moby_clear_selected((char *)moby);
    if (moby[0x20]!=13) {
        ((DispatchState *)vars)->f270=gravity_get_center_distance((char *)moby+0x10);
        FastVecSub(difference,g_hero_state.position,moby+0x10);
        if (moby_measure_step_angle((char *)moby,(Quad *)difference,0)<=0.7853982f) facing=1;
        distance=fast_vec_dist(g_hero_state.position,moby+0x10);
        range=g_enemy_range;
        ((DispatchState *)vars)->f27C=distance;
        ((DispatchState *)vars)->f324=0;
        if (distance<range)
            ((DispatchState *)vars)->f324=IsPathClear(moby,moby+0x10,g_hero_state.position);
        qcopy((vars+0x300), (moby+0x10));
        mothership_project_point_onto_surface(vars+0x300,0.0f);
    }
    if (moby[0x95]==3) {
        flags=moby_dispatch_action_by_kind(moby,(Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *)(vars+0x140));
        if (((DispatchState *)vars)->f3B4!=-1) {
            snd_stop_voice(((DispatchState *)vars)->f3B4); ((DispatchState *)vars)->f3B4=-1;
        }
        if (moby[0x43]==8 && FastVecLength(vars+0x1C0)>0.0f) {
            if (((DispatchState *)vars)->f270<g_mothership_surface_radius) mothership_project_point_onto_surface((char *)moby+0x10,0.0f);
            *(Quad *)local=0; local[2]=((DispatchState *)vars)->f174;
            *(Quad *)point=*(Quad *)local;
            matrix_mul_vec3(point,point,moby+0xC0);
            FastVecAdd(point,point,moby+0x10);
            vec_scale_to_length(difference,vars+0x1C0,4.0f);
            FastVecAdd(point,point,difference);
            coll_sweep_from_object(moby,point,0x90000,0,1,0,5.0f,100.0f,0.0f);
        }
        if ((((DispatchState *)vars)->f178&1) && ((DispatchState *)vars)->f2A4==0) {
            snd_play_from_class_bank(5,0,(char *)moby,0x7E5);
            SpawnExplosion_pal(((DispatchState *)vars)->f2A0+0x10,1,35,20,20,20,45,1,2.5f,20.0f,1,0,0,0);
            ((DispatchState *)vars)->f2A4=1;
            if (((DispatchState *)vars)->f38==(char *)g_hero_state.object) {
                qcopy(difference, (moby+0x10));
                mothership_project_point_onto_surface((char *)difference,0.0f);
                index=boss_pick_random_ready_attack();
                if (index!=-1) stored_object_forward((int)g_hero_state.position,index);
            }
            qcopy((moby+0x10), g_hero_state.position);
            mothership_project_point_onto_surface((char *)moby+0x10,(-g_mothership_surface_radius)*2.0f);
        }
        if ((flags & 1UL) == 1UL) moby_reset_idle_clear_links((char *)moby);
        else if (flag_set_first_pending(moby) && moby[0x43]==8) {
            snd_start_in_slot(31,0,0);
            moby_play_anim_and_link_pal((char *)moby,8,0,3,2,1.0f);
            ((DispatchState *)vars)->f26=21; ((DispatchState *)vars)->f2A6=0;
            SpawnExplosion_pal(((DispatchState *)vars)->f2A0+0x10,0,10,15,15,15,15,0,1.0f,20.0f,0,0,0,0);
        } else if ((flags & 2UL) == 2UL) moby_set_state(moby,5,0);
    }
    switch (moby[0x20]) {
    case 5:
        if (flag_set_second_pending(moby)) {
            moby_play_anim_and_link_pal((char *)moby,3,0,3,3,1.0f);
            if (((DispatchState *)vars)->f3B4!=-1) { snd_stop_voice(((DispatchState *)vars)->f3B4); ((DispatchState *)vars)->f3B4=-1; }
        }
        if (U(moby,0x96)>7) moby_set_state(moby,7,1);
        else if (U(moby,0x96)>=9) {
            mask=0;
            if (moby[0x43]!=3) mask|=1;
            if (((u8 *)((DispatchState *)vars)->f2A0)[0x43]!=3) mask|=2;
            if (mask) moby_play_anim_and_link_pal((char *)moby,3,0,17,mask,1.0f);
            moby_call_helper_with_blocks_pal((char *)moby);
        }
        break;
    case 1:
        if (flag_set_second_pending(moby)) enemy_reset_calm_pal((char *)moby);
        else if (U(moby,0x96)>=5) moby_set_state(moby,3,0);
        break;
    case 2:
        I(moby,0x98)=0;
        if (flag_set_second_pending(moby)) {
            enemy_reset_calm_pal((char *)moby);
            moby_play_anim_and_link_pal((char *)moby,9,0,0,1,1.0f);
            moby_play_anim_and_link_pal((char *)moby,1,0,0,2,1.0f);
            enemy_snap_to_ground_pal((char *)moby,1);
            ((DispatchState *)vars)->f3BC=1; ((DispatchState *)vars)->f3B8=(float)g_beam_level_limit;
        }
        gfx_add_draw_callback_first(gfx_draw_pulsing_beam,moby);
        break;
    case 6:
        enemy_relocate_near_hero_pal((char *)moby); break;
    case 3:
        if (flag_set_second_pending(moby) && moby[0x43]!=1)
            moby_play_anim_and_link_pal((char *)moby,1,0,3,3,1.0f);
        moby_call_helper_with_blocks_pal((char *)moby);
        if (((DispatchState *)vars)->f110) {
            moby_set_state(moby,5,0);
            moby_play_anim_and_link_pal((char *)moby,3,0,8,3,1.0f);
        } else {
            FastVecScale(point,moby+0xE0,-3.0f);
            FastVecAdd(point,point,moby+0x10);
            FastVecScale(difference,moby+0xE0,0.2f);
            FastVecAdd(difference,difference,moby+0x10);
            if (CollLine(difference,point,18,0,0) && fast_vec_dist(g_coll_line_hit_point_2,moby+0x10)<4.0f)
                moby_set_state(moby,4,0);
        }
        break;
    case 4:
        if (flag_set_second_pending(moby) && moby[0x43]!=2)
            moby_play_anim_and_link_pal((char *)moby,2,0,5,3,1.0f);
        else if ((moby[0x60]&2) || moby_get_anim_value((char *)moby)>12.0f) {
            moby_set_state(moby,5,0);
            moby_play_anim_and_link_pal((char *)moby,3,0,17,3,1.0f);
        }
        moby_call_helper_with_blocks_pal((char *)moby);
        break;
    case 7:
        if (flag_set_second_pending(moby)) {
            ((DispatchState *)vars)->f250=167;
            ((DispatchState *)vars)->f2A8=g_enemy_timer_float_base+math_random_float_range(0.0f,g_enemy_timer_float_base*0.5f);
            ((DispatchState *)vars)->f320=(char *)g_hero_state.position;
        }
        if (!moby[0x31]) ((DispatchState *)vars)->f2A8=g_enemy_timer_float_idle;
        else if (((DispatchState *)vars)->f2A8==g_enemy_timer_float_idle)
            ((DispatchState *)vars)->f2A8=g_enemy_timer_float_base+math_random_float_range(0.0f,g_enemy_timer_float_base*0.5f);
        if (((DispatchState *)vars)->f250==0) moby_set_state(moby,5,0);
        else if (((DispatchState *)vars)->f324 && facing && ((DispatchState *)vars)->f27C<g_enemy_facing_limit)
            moby_set_state(moby,8,2);
        else path_following_update_pal(moby);
        break;
    case 8:
        if (flag_set_first_pending(moby)) ((DispatchState *)vars)->f2A8=g_enemy_timer_float_base+math_random_float_range(0.0f,g_enemy_timer_float_base*0.5f);
        if (((u8 *)((DispatchState *)vars)->f2A0)[0x43]!=4) {
            moby_play_anim_and_link_pal((char *)moby,4,0,8,2,1.0f);
            F(((DispatchState *)vars)->f2A0,0x48)=g_mothership_state_param_b;
        }
        if (!((DispatchState *)vars)->f324 || ((DispatchState *)vars)->f27C>g_enemy_attack_time_limit) {
            moby_set_state(moby,5,0); ((DispatchState *)vars)->f250=0;
        } else if (((DispatchState *)vars)->f27C>g_enemy_chase_time_limit ||
                   ((unsigned int)(moby[0x43]-5)<2 && ((DispatchState *)vars)->f27C>g_enemy_chase_time_limit-2.0f)) {
            ((DispatchState *)vars)->f320=(char *)g_hero_state.position; path_following_update_pal(moby);
        } else {
            moby_play_anim_and_link_pal((char *)moby,3,0,8,1,1.0f); moby_call_helper_with_blocks_pal((char *)moby);
        }
        if (math_is_value_within_step_pal(((DispatchState *)vars)->f2A0,28.0f)) hero_launch_hit_effect_pal((char *)moby,g_mothership_effect_radius+g_mothership_effect_radius,(int)g_hero_target_point,0);
        else if (math_is_value_within_step_pal(((DispatchState *)vars)->f2A0,14.0f)) hero_launch_hit_effect_pal((char *)moby,g_mothership_effect_radius+g_mothership_effect_radius,(int)g_hero_target_point,1);
        break;
    case 9:
        if (flag_set_first_pending(moby)) {
            moby_play_anim_and_link_pal((char *)moby,6,0,10,1,g_enemy_state_anim_blend);
            moby_play_anim_and_link_pal((char *)moby,8,0,10,2,4.0f);
            moby_stop_effects((char *)moby);
            ((DispatchState *)vars)->f328=ribbon_trail_create((u8 *)vars+0x330,moby,(u8 *)vars+0x340,50,70,0.7f,0.85f,0.5f,1.2f,30,5,0x7F7F7F,0x7F7F7F,0,-1,0);
            ((DispatchState *)vars)->f32C=ribbon_trail_create((u8 *)vars+0x330,moby,(u8 *)vars+0x340,50,70,1.9f,2.05f,0.5f,1.2f,10,2,0x3F00000,0x3F0000,0,-1,0);
            ((DispatchState *)vars)->f2A8=g_enemy_timer_float_alt;
            ((DispatchState *)vars)->f3B4=snd_play_from_class_bank(4,4,(char *)moby,0x7E5);
        }
        if (!((DispatchState *)vars)->f324 || ((DispatchState *)vars)->f27C>g_enemy_attack_time_limit) {
            moby_set_state(moby,5,0); ((DispatchState *)vars)->f250=0; break;
        }
        moby_transform_joint_to_world(((DispatchState *)vars)->f2A0,1,vars+0x330);
        moby_transform_joint_to_world(((DispatchState *)vars)->f2A0,0,vars+0x340);
        if ((int)U(moby,0x96)>g_enemy_high_health_threshold) {
            ((DispatchState *)vars)->f320=(char *)g_hero_state.position;
            if (((DispatchState *)vars)->f27C<g_enemy_min_state_time) moby_set_state(moby,10,2);
            path_following_update_pal(moby);
        }
        break;
    case 10:
        if (!((DispatchState *)vars)->f324 || ((DispatchState *)vars)->f27C>g_enemy_retreat_time_limit) { moby_set_state(moby,5,0); break; }
        moby_transform_joint_to_world(((DispatchState *)vars)->f2A0,1,vars+0x330);
        moby_transform_joint_to_world(((DispatchState *)vars)->f2A0,0,vars+0x340);
        if (flag_set_first_pending(moby)) {
            moby_stop_effects((char *)moby);
            ((DispatchState *)vars)->f328=ribbon_trail_create((u8 *)vars+0x330,moby,(u8 *)g_boss_hit_point,95,80,4.0f,4.25f,0.7f,1.3f,35,5,0x5F0000,0x5F2020,0,-1,0);
            ((DispatchState *)vars)->f32C=ribbon_trail_create((u8 *)vars+0x340,moby,(u8 *)g_boss_hit_point,95,80,4.0f,4.25f,0.7f,1.3f,35,5,0x5F0000,0x5F2020,0,-1,0);
            break;
        }
        if ((int)U(moby,0x96)<=g_enemy_low_health_threshold) break;
        FastVecAdd(difference,vars+0x330,vars+0x340);
        FastVecScale(difference,difference,0.5f);
        if (fast_vec_dist(difference,g_boss_hit_point)<g_enemy_arrive_distance) {
            vec_scale_to_length(point,((DispatchState *)vars)->f2A0+0xE0,0.25f);
            FastVecAdd(point,point,((DispatchState *)vars)->f2A0+0xC0);
            FastVecScale(point,point,15.0f); point[3]=5627.9248f;
            part_queue_impact_effect((int)g_hero_moby,(int)moby,0x10007,(int)(moby+0x10),(int)point,g_mothership_impact_param);
            queue_copy_record_by_index(43);
            SpawnExplosion_pal(g_boss_hit_point,1,10,10,10,10,45,0,1.2f,20.0f,0,1,0,0);
            ((DispatchState *)vars)->f3BE=1;
        }
        moby_set_state(moby,11,2);
        break;
    case 11:
        if (flag_set_first_pending(moby)) {
            if (((DispatchState *)vars)->f3B4!=-1) { snd_stop_voice(((DispatchState *)vars)->f3B4); ((DispatchState *)vars)->f3B4=-1; }
        } else if ((int)U(moby,0x96)>(((int)(g_enemy_flee_health_threshold) * 5 + 2) / 6)) { moby_clear_selected((char *)moby); moby_set_state(moby,5,0); } else {
            if ((int)U(moby,0x96)>=(((int)(g_enemy_flee_health_threshold-5) * 5 + 2) / 6) && ((DispatchState *)vars)->f3BE) {
                snd_start_in_slot(29,0,0); ((DispatchState *)vars)->f3BE=0; queue_copy_record_by_index(43);
            }
        }
        break;
    case 12:
    case 13:
        break;
    }
    moby_tick_timers((char *)moby);
    if (moby[0x20]!=13) { child_update_orientation_pal((char *)moby); tether_update_glow_pal((char *)moby); }
}
