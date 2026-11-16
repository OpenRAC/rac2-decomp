#include "common.h"
extern void group_entity_base_update(void *);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern void anim_start_blended(void *, int, int, int);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern float entity_move_to_tracked_height(void *,void *,float,float);
extern float math_random_signed_float_range(float,float);
extern int coll_sweep_from_object(void *,void *,float,float,float,int,int,int,int);
extern float FastVecLength(void *);
extern void vec_clamp_length(void *,float);
extern void entity_spawn_particle_pair(void *);
extern float math_step_value_toward_target(void *,float,void *,float,float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void entity_tick_timers(void *);
extern float g_group_entity_accel_param __attribute__((sda));
extern float g_group_entity_speed_param __attribute__((sda));
extern float g_group_entity_length_threshold __attribute__((sda));
extern float g_group_entity_sweep_radius __attribute__((sda));
extern float g_group_entity_turn_range[] __attribute__((sda));
struct PlayerState1310 { char pad[0x229C]; int state; char pad2[0x1FC]; void *target; };
extern struct PlayerState1310 g_hero_state;
/* Advance the entity state machine, movement and recovery scaling. */
/* Per-frame update for moby class 3357: runs its behaviour states and eases the object toward
   its goals. */
void group_entity_update(unsigned char *moby)
{
    float goal_pos[4] __attribute__((aligned(16)));
    float lengths[2];
    char *vars=*(char **)(moby+0x68);
    int i;
    group_entity_base_update(moby);
    switch(moby[0x95]) {
    case 0:
        if (*(int *)(vars+0x114)==1) moby_set_state(moby,5,2);
        break;
    case 2:
        if (*(int *)(vars+0x114)!=1) moby_set_state(moby,1,0);
        break;
    }
    switch(moby[0x20]) {
    case 1:
        if (flag_set_first_pending(moby) && moby[0x43]) anim_start_blended(moby,0,0,20);
        if (*(char **)(vars+0x260)) {
            matrix_mul_vec3(goal_pos,vars+0x220,*(char **)(vars+0x260)+0xC0);
            FastVecAdd(goal_pos,goal_pos,*(char **)(vars+0x260)+0x10);
        } else qcopy(goal_pos,vars+0x220);
        entity_move_to_tracked_height(moby,goal_pos,0,1);
        break;
    case 3:
        if(flag_set_first_pending(moby)) *(float *)(vars+0x250)=math_random_signed_float_range(g_group_entity_turn_range[0],g_group_entity_turn_range[1])*0.01745329424738884f;
        if(entity_move_to_tracked_height(moby,vars+0x100,*(float *)(vars+0x250),1)<2) moby_set_state(moby,4,-1);
        break;
    case 4:
        if(flag_set_first_pending(moby) && moby[0x43]!=2) anim_start_blended(moby,2,0,5);
        entity_move_to_tracked_height(moby,vars+0x100,*(float *)(vars+0x250),1);
        if(moby[0x60]&2) moby_set_state(moby,5,-1);
        break;
    case 5:
        if(flag_set_first_pending(moby) && moby[0x43]!=3) anim_start_blended(moby,3,0,2);
        entity_move_to_tracked_height(moby,vars+0x100,*(float *)(vars+0x250),1);
        if(*(unsigned short *)(moby+0x96)>10)
            coll_sweep_from_object(moby,moby+0x10,g_group_entity_sweep_radius,(float)*(unsigned char *)(vars+0x34),1,0x4000001,0,1,0);
        if(*(unsigned short *)(moby+0x96)>30 &&
            (g_hero_state.state==7 || g_hero_state.state==20) &&
            g_hero_state.target==moby) moby_set_state(moby,6,-1);
        break;
    case 6:
        if(flag_set_first_pending(moby) && moby[0x43]!=4) anim_start_blended(moby,4,0,1);
        if(moby[0x60]&2) moby_set_state(moby,5,-1);
        break;
    case 9: {
        float tolerance=0.08333333582f;
        FastVecSub(goal_pos,vars+0x230,moby+0x10);
        if(FastVecLength(goal_pos)>tolerance) vec_clamp_length(goal_pos,tolerance);
        else moby_set_state(moby,10,-1);
        FastVecAdd(moby+0x10,moby+0x10,goal_pos);
        entity_spawn_particle_pair(moby);
        break;
    }
    case 10:
        if(flag_set_first_pending(moby)) *(int *)(moby+0x98)=*(int *)(*(char **)(moby+0x24)+0x10);
        lengths[1]=FastVecLength(moby+0xC0);
        lengths[0]=FastVecLength(moby+0xE0);
        {
            float a=g_group_entity_accel_param*0.0002777777845f;
            float b=g_group_entity_speed_param*0.01666666754f;
            math_step_value_toward_target(&lengths[0],1,vars+0x254,a,a,b);
            if(lengths[0]>g_group_entity_length_threshold) math_step_value_toward_target(&lengths[1],1,vars+0x258,a,a,b);
        }
        for(i=0;i<2;i++) vec_scale_to_length(moby+0xC0+i*16,moby+0xC0+i*16,lengths[1]);
        vec_scale_to_length(moby+0xE0,moby+0xE0,lengths[0]);
        if(lengths[1]>=1) {
            for(i=0;i<3;i++) vec_scale_to_length(moby+0xC0+i*16,moby+0xC0+i*16,1);
            moby_set_state(moby,3,2);
        }
        entity_spawn_particle_pair(moby);
        break;
    }
    entity_tick_timers(moby);
}
