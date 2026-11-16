#include "names.h"
/* func_PAL_L01_003B93DC, the PAL copy of func_L01_003B5878: a creature's per-frame state machine on object[0x95] (idle, waiting, airborne
 * leap, pursuit, attack, dispatch, removal), followed by the head-tracking ease of the angles at
 * +0xF4/+0xF0, each clamped to 40 degrees; same template as func_L01_003DAE58.
 * Its own unit: it needs -G8 ($gp reads) and -fno-expensive-optimizations, which keeps constant
 * call arguments out of pseudos (preserve_subexpressions_p), so they are rematerialised per call.
 * Reading the state words by index marks them as aggregate elements (MEM_IN_STRUCT_P), which lets
 * the scheduler move the 0x380 index read above the stack store of the leave weave, as retail does.
 */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef struct {
    Quadword previous_position, delta, target;
    Quadword rotation[4], inverse[4], object_inverse[4];
} MotionWorkspace;
/* The dispatcher context is opaque here; its payload extent is not established. */
typedef struct DispatchContext DispatchContext;
typedef unsigned long DispatchFlags;

extern void swamp_beast_update_awareness_pal(u8 *);
extern void swamp_beast_init_state_pal(u8 *);
extern float ApproachValue(float *,float,float);
extern int math_fast_float_d(int *);
extern int math_random_int_range(int,int);
extern int math_random_int_below(int);
extern void anim_start_blended_pal(u8 *,int,int,int);
extern void moby_set_state(u8 *,int,int);
extern void swamp_beast_move_pal(u8 *,void *);
extern int swamp_beast_move_with_speed_pal(u8 *,void *,float *);
extern void swamp_beast_find_best_patrol_position(u8 *,void *);
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *,void *,float);
extern float weapon_compute_shot_launch_speed(void *,void *,float *,float,float);
extern int PlayMobySound(int,int,char *);
extern float moby_get_anim_value(char *);
extern float mat_fast_helper_a(float,float);
extern void MobySpringTurn(void *,float,float,float,float,void *);
extern float math_fabs(float);
extern int coll_check_object_inside_polygon(unsigned char *);
extern int func_001163B0(void);
extern void part_spawn_surface_particles(char *,int,float);
extern int moby_step_at_own_position_pal(char *);
extern int moby_step_at_own_position_factor_pal(u8 *,float);
extern float IntToFloat(int);
extern float math_wrap_angle_to_pi(float);
extern float math_fast_sin_or_cos_b(float);
extern float vec_distance_xy(void *,void *);
extern float FastDiffRots(float,float);
extern int swamp_beast_claim_group_slot(u8 *);
extern void swamp_beast_release_group_slot(u8 *);
extern float math_approach_target_with_direction_mode(void *,float,float,float,float,void *,int);
extern int coll_test_hit_at_bone(float,float,float,void *,int,int,int,int,int);
extern DispatchFlags moby_dispatch_action_by_kind(void *,DispatchContext *);
extern void moby_mark_spawned(void *);
extern void swamp_beast_spawn_bubbles_pal(u8 *);
extern int GetCollHitMaterial(void);
extern void swamp_beast_alert_group(u8 *);
extern void SetDeathBits_pal(u8 *,int,int);
/* Called with a null callback; a callback would receive the object. */
extern void part_queue_moby_for_glow(u8 *,int,void (*)(u8 *));
extern void euler_to_matrix(void *,void *);
extern void matrix_from_basis_rows(void *,void *);
extern int level_has_pending_inner_flag(char *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void swamp_beast_update_timers_pal(u8 *);
/* Prefix views of the hero record (position, object) and of the collision query's hit object. */
typedef struct {
    u8 prefix[0x80];
    float position[4];
    u8 rest[0x2290-0x90];
    u8 *object;
} HeroTargetPrefix;
typedef struct { u8 prefix[0x18]; u8 *object; } CollisionQueryPrefix;
extern u8 g_hero_state[];
/* Mixed absolute/GP reads of the same mutable frame counter. */
extern int g_oozla_intro_stage MACRO_ADDR;
extern int g_swamp_beast_anim_blend_frames __attribute__((sda));
extern u8 *g_moby_l01_table __attribute__((sda));
/* 128-byte destination records with a 16-byte position at +0x30. */
typedef struct { u8 prefix[0x30]; float position[4]; u8 rest[0x40]; } DestinationRecord;
extern DestinationRecord *g_swamp_patrol_positions MACRO_ADDR;
extern u8 g_collision_l01_hit[];
extern u8 g_monster_vector_template[] MACRO_ADDR;

#define STATE_INT(o) (((int *)state)[(o)/4])
#define STATE_UINT(o) (((unsigned int *)state)[(o)/4])
#define STATE_FLOAT(o) (((float *)state)[(o)/4])
#define STATE_POINTER(o) (((u8 **)state)[(o)/4])

/* Updates this creature's idle, pursuit, airborne, attack and recovery phases. */
void mutant_swamp_beast_update_pal(u8 *moby)
{
    /* Label tables for the phase and pursuit-action dispatches. */
    static void *const phases[8]={&&phase_idle,&&phase_wait,&&phase_airborne,&&phase_pursuit,
                           &&phase_attack,&&phase_dispatch,&&phase_removed,&&phase_removed};
    static void *const actions[8]={&&pursuit_idle,&&pursuit_wait,&&pursuit_weave,&&pursuit_done,
                            &&pursuit_straight,&&pursuit_done,&&pursuit_group,&&pursuit_leave};
    MotionWorkspace local;
    float duration, weave, straight, pursuit;
    u8 *state;
    float speed,frame,angle,pitch,yaw;
    int animation,blend_frames,i;
    unsigned int phase,action;
    /* Preserve the full dispatcher return while testing its two low status bits. */
    DispatchFlags flags;

    qcopy(&local.previous_position, moby+0x10);
    state=*(u8 **)(moby+0x68);
    if (moby[0x95]) swamp_beast_update_awareness_pal(moby);
    phase=moby[0x95];
    if (phase<8) goto *phases[phase];
    goto phase_done;

phase_idle:
    swamp_beast_init_state_pal(moby);
    goto phase_done;

phase_wait:
    switch (moby[0x20]) {
    case 0:
        if (STATE_INT(0x32C)>=18)
            ApproachValue((float *)(state+0x214),0.040000003f,0.0016000001f);
        else ApproachValue((float *)(state+0x214),0.0f,0.0016000001f);
        if (math_fast_float_d((int *)(state+0x32C))) {
            if (moby[0x43]!=4) anim_start_blended_pal(moby,4,0,math_random_int_range(18,24));
            moby_set_state(moby,1,-1);
        }
        if (STATE_INT(0x308)!=-1) swamp_beast_move_pal(moby,state+0x200);
        break;
    case 1:
        if (moby[0x60]&2) {
            STATE_INT(0x32C)=math_random_int_range(100,333);
            if (moby[0x43]!=4) anim_start_blended_pal(moby,4,0,math_random_int_range(20,30));
            moby_set_state(moby,0,-1);
        }
        break;
    case 2:
        qcopy(state+0x2E0, state+0x2D0);
        break;
    case 3:
        if (math_fast_float_d((int *)(state+0x360))) {
            swamp_beast_find_best_patrol_position(moby,&local.target);
            FastVecSub(&local.delta,&local.target,moby+0x10);
            if (FastVecLength(&local.delta)*0.03333333507180214f < 0.16000001f)
                speed=FastVecLength(&local.delta)*0.03333333507180214f;
            else speed=0.16000001f;
            vec_scale_to_length(&local.delta,&local.delta,speed);
            duration=0.0f;
            ((float *)&local.delta)[2]=weapon_compute_shot_launch_speed(moby+0x10,&local.target,&duration,speed,-0.0072000003f);
            qcopy(state+0x2F0, &local.delta);
            qcopy(state+0x2E0, &local.target);
            PlayMobySound(5,0,(char *)moby);
            if (moby[0x43]!=3) anim_start_blended_pal(moby,3,0,10);
            if (duration>0.0f) *(float *)(moby+0x48)=38.0f/duration;
            moby_set_state(moby,1,2);
        }
        break;
    }
    if (moby[0x20]!=3 && STATE_INT(0x310)!=-1 && moby[0x95]==1) {
        STATE_UINT(0x398)=STATE_UINT(0x390);
        STATE_INT(0x39C)=0;
        if (STATE_INT(0x244)==1 || STATE_INT(0x330)) {
            *(float *)(moby+0x18)=STATE_FLOAT(0x34C);
            STATE_INT(0x39C)=0;
            STATE_UINT(0x398)=STATE_UINT(0x390);
            moby_set_state(moby,3,1);
        }
    }
    goto phase_done;

phase_airborne:
    if (moby[0x42]!=3) goto phase_done;
    frame=moby_get_anim_value((char *)moby);
    if (!(frame>5.0f)) goto phase_done;
    FastVecAdd(moby+0x10,moby+0x10,state+0x2F0);
    angle=mat_fast_helper_a(STATE_FLOAT(0x2E0)-*(float *)(moby+0x10),STATE_FLOAT(0x2E4)-*(float *)(moby+0x14));
    MobySpringTurn(moby,angle,STATE_FLOAT(0x124)*10.0f,STATE_FLOAT(0x134)*10.0f,STATE_FLOAT(0x12C)*10.0f,
                  state+0x1C4);
    STATE_FLOAT(0x2F8)-=0.0072000003f;
    if (!(STATE_FLOAT(0x2F8)<0.0f)) goto phase_done;
    if (!(math_fabs(*(float *)(moby+0x18)-STATE_FLOAT(0x2E8)) < -STATE_FLOAT(0x2F8))) goto phase_done;
    *(int *)(moby+0x98)=*(int *)(*(u8 **)(moby+0x24)+0x10);
    STATE_UINT(0x14C)=STATE_UINT(0x30C);
    qcopy(state+0x200, moby+0x10);
    moby[0xBC]=1;
    STATE_INT(0x330)=200;
    coll_check_object_inside_polygon(moby);
    if (moby[0x43]!=8) anim_start_blended_pal(moby,8,0,10);
    goto finish_attack;

phase_pursuit:
    action=moby[0x20];
    if (action<8) goto *actions[action];
    goto pursuit_done;
pursuit_idle:
    if (STATE_INT(0x32C)>=18)
        ApproachValue((float *)(state+0x214),0.040000003f,0.0016000001f);
    else ApproachValue((float *)(state+0x214),0.0f,0.0016000001f);
    if (math_fast_float_d((int *)(state+0x32C))) {
        if (!moby[0xBC]) {
            STATE_INT(0x32C)=150;
            animation=moby[0x43];
            if (animation!=(func_001163B0()&1)) {
                animation=func_001163B0()&1;
                blend_frames=math_random_int_range(30,40);
                anim_start_blended_pal(moby,animation,0,blend_frames);
            }
        } else {
            STATE_INT(0x32C)=100;
            animation=moby[0x43];
            if (animation!=(func_001163B0()&1)+6)
                anim_start_blended_pal(moby,(func_001163B0()&1)+6,0,math_random_int_range(30,40));
        }
        moby_set_state(moby,1,-1);
    }
    swamp_beast_move_pal(moby,state+0x200);
    part_spawn_surface_particles((char *)moby,1,-1.0f);
    goto pursuit_done;
pursuit_wait:
    if (!math_random_int_below(7)) moby_step_at_own_position_pal((char *)moby);
    if (math_fast_float_d((int *)(state+0x32C)) && (moby[0x60]&2)) {
        STATE_INT(0x32C)=math_random_int_range(100,333);
        animation=19;
        if (*(u16 *)(moby+0xB2)&1) animation=8;
        anim_start_blended_pal(moby,animation,0,math_random_int_range(25,35));
        moby_set_state(moby,0,-1);
    }
    goto pursuit_done;
pursuit_weave:
    weave=math_fast_sin_or_cos_b(math_wrap_angle_to_pi(IntToFloat(g_oozla_intro_stage)*0.013962637f))*0.8726646900177002f;
    if (vec_distance_xy(moby+0x10,state+0x230)<4.75f) weave=0.0f;
    swamp_beast_move_with_speed_pal(moby,state+0x2E0,&weave);
    part_spawn_surface_particles((char *)moby,1,-1.0f);
    if (vec_distance_xy(moby+0x10,STATE_POINTER(0x240)+0x10)<3.75f) {
        if (math_fabs(*(float *)(moby+0x18)-*(float *)(STATE_POINTER(0x240)+0x18))<0.5f) {
            angle=mat_fast_helper_a(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(moby+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(moby+0x14));
            if (FastDiffRots(*(float *)(moby+0xF8),angle)<0.174532949924469f) {
                qzero(state+0x1B0);
                state[0x35C]=0;
                if (moby[0x43]!=10) anim_start_blended_pal(moby,10,g_swamp_beast_anim_blend_frames,math_random_int_range(16,22));
                moby_set_state(moby,1,4);
            }
        }
    }
    goto pursuit_done;
pursuit_straight:
    {
        int destination=STATE_INT(0x310);
        straight=0.0f;
        if (destination==-1) swamp_beast_move_with_speed_pal(moby,state+0x2D0,&straight);
        else swamp_beast_move_with_speed_pal(moby,g_swamp_patrol_positions[destination].position,&straight);
    }
    part_spawn_surface_particles((char *)moby,1,-1.0f);
    if ((moby[0x60]&2) && (*(u64 *)(state+0x1A0)&0x18000000000ULL)!=0x10000000000ULL) {
        animation=moby[0x43];
        if (animation!=(func_001163B0()&1)) {
            animation=func_001163B0()&1;
            blend_frames=math_random_int_range(30,40);
            anim_start_blended_pal(moby,animation,0,blend_frames);
        }
        moby_set_state(moby,1,-1);
    }
    goto pursuit_done;
pursuit_group:
    STATE_UINT(0x398)=STATE_UINT(0x390);
    STATE_FLOAT(0x39C)=STATE_FLOAT(0x388);
    swamp_beast_move_pal(moby,state+0x200);
    part_spawn_surface_particles((char *)moby,1,-1.0f);
    if (STATE_INT(0x244)==1 && (STATE_INT(0x38C)==-1 ||
        g_moby_l01_table[STATE_INT(0x38C)*256+0xBC])) moby_set_state(moby,7,-1);
    goto pursuit_done;
pursuit_leave:
    pursuit=math_fast_sin_or_cos_b(math_wrap_angle_to_pi(IntToFloat(g_oozla_intro_stage)*0.013962637f))*0.8726646900177002f;
    qcopy(state+0x2E0, g_swamp_patrol_positions[STATE_INT(0x380)].position);
    swamp_beast_move_with_speed_pal(moby,state+0x2E0,&pursuit);
    part_spawn_surface_particles((char *)moby,1,-1.0f);
    if ((STATE_UINT(0x1A4)&0x80) && !moby[0x31]) {
        moby_mark_spawned(moby);
        return;
    }

pursuit_done:
    if (moby[0x95]!=3) goto mirror_hero;
    if (moby[0x20]==4) goto mirror_hero;
    if (moby[0x20]==7) goto mirror_hero;
    if (moby[0x20]==6) goto mirror_hero;
    STATE_UINT(0x398)=STATE_UINT(0x394);
    STATE_FLOAT(0x39C)=STATE_FLOAT(0x388);
    if (STATE_INT(0x244)!=1 && !STATE_INT(0x330)) goto cancel_pursuit;
    {
        if (moby[0x21]!=255 && **(int **)(state+0x36C)!=*(short *)(moby+0xB2) &&
            **(int **)(state+0x370)!=*(short *)(moby+0xB2)) goto cancel_pursuit;
        if (!(math_fabs(*(float *)(moby+0x18)-*(float *)(STATE_POINTER(0x240)+0x18))<1.0f)) goto cancel_pursuit;
        STATE_INT(0x330)=200;
        moby[0xBC]=1;
        STATE_UINT(0x14C)=STATE_UINT(0x30C);
        if (moby[0x20]==2) goto copy_pursuit_target;
        if (moby[0x21]!=255 && **(int **)(state+0x33C)>1) goto pursuit_distance;
        if (STATE_INT(0x334)) goto pursuit_distance;
        if (!(vec_distance_xy(moby+0x10,STATE_POINTER(0x240)+0x10)<14.0f)) goto pursuit_distance;
        qcopy(state+0x2E0, STATE_POINTER(0x240)+0x10);
        animation=19;
        if (*(u16 *)(moby+0xB2)&1) animation=8;
        anim_start_blended_pal(moby,animation,0,math_random_int_range(20,30));
        swamp_beast_claim_group_slot(moby);
        moby_set_state(moby,2,-1);
        goto pursuit_distance;
    }
copy_pursuit_target:
    qcopy(state+0x2E0, STATE_POINTER(0x240)+0x10);
    goto pursuit_distance;
cancel_pursuit:
    if (moby[0x20]==2) {
        swamp_beast_release_group_slot(moby);
        moby[0xBC]=0;
        animation=moby[0x43];
        if (animation!=(func_001163B0()&1)) {
            animation=func_001163B0()&1;
            blend_frames=math_random_int_range(30,40);
            anim_start_blended_pal(moby,animation,0,blend_frames);
        }
        moby_set_state(moby,1,-1);
    }
    goto pursuit_distance;
mirror_hero:
    if (STATE_POINTER(0x240)==((HeroTargetPrefix *)g_hero_state)->object)
        qcopy(state+0x2E0, ((HeroTargetPrefix *)g_hero_state)->position);
pursuit_distance:
    if (vec_distance_xy(moby+0x10,STATE_POINTER(0x240)+0x10)<3.5f) {
        if (math_fabs(*(float *)(moby+0x18)-*(float *)(STATE_POINTER(0x240)+0x18))<0.5f) {
            angle=mat_fast_helper_a(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(moby+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(moby+0x14));
            if (FastDiffRots(*(float *)(moby+0xF8),angle)<0.523598849773407f) {
                qzero(state+0x1B0);
                state[0x35C]=0;
                if (moby[0x43]!=10) anim_start_blended_pal(moby,10,g_swamp_beast_anim_blend_frames,math_random_int_range(8,12));
                moby_set_state(moby,1,4);
            } else {
                float *heading=(float *)(moby+0xF8);
                angle=mat_fast_helper_a(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(moby+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(moby+0x14));
                math_approach_target_with_direction_mode(heading,angle,STATE_FLOAT(0x124),STATE_FLOAT(0x128),STATE_FLOAT(0x12C),state+0x1C4,0);
            }
        }
    }
    goto phase_done;

phase_attack:
    if (STATE_POINTER(0x240)) {
        if (!math_random_int_below(7)) {
            angle=mat_fast_helper_a(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(moby+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(moby+0x14));
            moby_step_at_own_position_factor_pal(moby,angle);
        } else {
            float *heading=(float *)(moby+0xF8);
            angle=mat_fast_helper_a(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(moby+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(moby+0x14));
            math_approach_target_with_direction_mode(heading,angle,STATE_FLOAT(0x124),STATE_FLOAT(0x128),STATE_FLOAT(0x12C),state+0x1C4,0);
        }
    } else if (!math_random_int_below(7)) moby_step_at_own_position_pal((char *)moby);
    frame=moby_get_anim_value((char *)moby);
    if (moby[0x42]==10 && frame>=18.0f && frame<=25.0f) {
        for (i=0;i<5;i++) {
            if (coll_test_hit_at_bone(0.5f,(float)state[0x34],1.0f,moby,i,0x4000001,0,1,0) &&
                ((CollisionQueryPrefix *)g_collision_l01_hit)->object==((HeroTargetPrefix *)g_hero_state)->object) state[0x35C]=1;
        }
    }
    if (!(frame>30.0f) && (moby[0x42]==10 || moby[0x43]==10)) goto phase_done;
    if (state[0x35C]) {
        STATE_INT(0x334)=83;
        if (moby[0x43]!=11) anim_start_blended_pal(moby,11,0,math_random_int_range(25,30));
    } else {
        STATE_INT(0x334)=33;
        if (moby[0x43]!=8) anim_start_blended_pal(moby,8,0,math_random_int_range(25,30));
    }
    state[0x35C]=0;
    swamp_beast_release_group_slot(moby);
finish_attack:
    STATE_UINT(0x398)=STATE_UINT(0x394);
    STATE_FLOAT(0x39C)=STATE_FLOAT(0x388);
    moby_set_state(moby,1,3);
    goto phase_done;

phase_dispatch:
    flags=moby_dispatch_action_by_kind(moby,(DispatchContext *)(state+0x60));
    if ((flags&1UL)==1UL) moby_set_state(moby,0,7);
    else if ((flags&2UL)==2UL) {
        *(int *)(moby+0x98)=*(int *)(*(u8 **)(moby+0x24)+0x10);
        swamp_beast_spawn_bubbles_pal(moby);
        swamp_beast_release_group_slot(moby);
        if (GetCollHitMaterial()==3) {
            if (moby[0x43]!=4) anim_start_blended_pal(moby,4,0,110);
            moby_set_state(moby,0,6);
        } else {
            STATE_INT(0x384)=-1;
            STATE_UINT(0x398)=STATE_UINT(0x394);
            STATE_FLOAT(0x39C)=STATE_FLOAT(0x388);
            animation=19;
            if (*(u16 *)(moby+0xB2)&1) animation=8;
            anim_start_blended_pal(moby,animation,0,math_random_int_range(18,24));
            if (!coll_check_object_inside_polygon(moby)) moby_set_state(moby,4,3);
            else moby_set_state(moby,1,3);
        }
    }
    goto phase_done;

phase_removed:
    swamp_beast_alert_group(moby);
    SetDeathBits_pal(moby,0,3);
    swamp_beast_spawn_bubbles_pal(moby);
    part_spawn_surface_particles((char *)moby,5,-1.0f);
    swamp_beast_release_group_slot(moby);
    part_queue_moby_for_glow(moby,0,0);

phase_done:
    if ((unsigned int)(moby[0x95]-3)<2) {
        local.target=0;
        ((float *)&local.target)[2]=*(float *)(moby+0xF8);
        local.delta=local.target;
        euler_to_matrix(local.rotation,&local.delta);
        matrix_from_basis_rows(local.inverse,local.rotation);
        matrix_from_basis_rows(local.object_inverse,moby+0xC0);
        {
            Quadword *v;
            u8 *target = STATE_POINTER(0x198);

            if (target && !level_has_pending_inner_flag((char *)target)) {
                v = &local.target;
                qcopy(v, g_monster_vector_template);
            } else
                vec_scale_to_length(&local.target,state+0x160,1.0f);
            v = &local.target;
            matrix_mul_vec3(v,v,local.inverse);
        }
        yaw=mat_fast_helper_a(((float *)&local.target)[2],((float *)&local.target)[0]);
        pitch=-mat_fast_helper_a(((float *)&local.target)[2],((float *)&local.target)[1]);
        if (yaw>0.698131799697876f) yaw=0.698131799697876f;
        else if (yaw<-0.698131799697876f) yaw=-0.698131799697876f;
        if (pitch>0.698131799697876f) pitch=0.698131799697876f;
        else if (pitch<-0.698131799697876f) pitch=-0.698131799697876f;
        math_approach_target_with_direction_mode(moby+0xF4,yaw,0.0025132746f,0.0025132746f,0.12566373f,state+0x358,0);
        math_approach_target_with_direction_mode(moby+0xF0,pitch,0.0025132746f,0.0025132746f,0.12566373f,state+0x354,0);
    }
    swamp_beast_update_timers_pal(moby);
}
