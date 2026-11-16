#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    u8 pad0[0x90];
    int path;
    u8 pad94[0xe4-0x94];
    float start;
    float distance[3];
    u8 padf4[0x11c-0xf4];
    float speed;
} Motion;
extern u8 g_ship_sequence_event_states[] __attribute__((sda));
extern int g_frame_l07_counter[] __attribute__((sda));
extern Quad g_ship_checkpoint_states[2];
typedef struct {
    u8 pad0[0x270];
    int phase;
    u8 pad274[0x2d0-0x274];
    Quad position;
    u8 pad2e0[0x33c-0x2e0];
    u8 *riding;
    int ridingFlag;
} Player;
extern Player g_lift_state;
extern u8 *g_ship_rider_vars NOT_SDA;
extern Quad g_ship_sequence_start_pos __attribute__((sda));
extern Quad g_ship_sequence_start_rot MACRO_ADDR;
extern u8 *g_moby_l07_array[] __attribute__((sda));
extern u8 *sibEntities SDATA(D_L07_001B22DC);
extern int *g_path_l07_table[] NOT_SDA;
extern int g_hero_mode NOT_SDA;
extern float g_ship_fade_amount[] __attribute__((sda));
extern Player g_hero_l07_state_block;
extern float g_hero_reset_offset_z[] __attribute__((sda));
extern Quad g_hero_l07_reset_position __attribute__((sda));
extern u8 *g_snowfall_target_moby MACRO_ADDR;
extern int moby_count_group_not_in_state(int,int);
extern int snd_play_from_class_bank(int,int,void *,int);
extern void FastVecSub(void *,void *,void *);
extern void vec_transform_by_object_or_given(void *,void *,void *,int);
extern void moby_set_group_enabled(int,int);
extern void moby_attach_to_parent(void *,void *,void *,void *);
extern void moby_set_flag_bit(void *,int);
extern void entity_set_state_five(void *);
extern void boss_start_move_tier(void *,void *,int);
extern u8 *boss_get_attack_mode(void *);
extern float math_approach_target_with_direction_mode(void *,float,void *,int,float,float,float);
extern void moby_steer_aim_yaw(void *);
extern void timer_start_countdown(int,float);
extern void load_scene_chunk(int,int);
extern void hero_reset_position_and_direction(void *,void *,int,int);
extern void level_capture_checkpoint_state(void *,void *);
extern void cam_reset_entry(void *);
extern void ship_start_second_phase(void *,int);
extern void moby_mark_table_entry_flagged(int);
extern void moby_set_state(void *,int,int);
#define W(p,o) (*(int *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
/* Runs the 16 scripted events of the Siberius ship sequence. Each event waits for its trigger, then moves from waiting to started to finished. */
void ship_run_sequence_events(u8 *moby)
{
    Vec pos, rot;
    int i,j;
    u8 *vars=P(moby,0x68), *part_vars, *target;
    float *cursor;
    int *path;
    float remaining;
    for(i=0;i<16;i++) {
        if(g_ship_sequence_event_states[i]==2) continue;
        switch(i) {
        case 0:
            if(g_ship_sequence_event_states[i]==0) {
                if(moby_count_group_not_in_state(W(P(P(vars,0xf4),0x68),0x94),-1)==0) {
                    snd_play_from_class_bank(1,0,P(vars,0xf4),0x11d9);
                    g_ship_sequence_event_states[i]=1;
                } else if((g_frame_l07_counter[0]&7)==(((int)P(vars,0xf4)>>8)&7)) {
                    FastVecSub(&pos,g_ship_checkpoint_states,P(vars,0xf4)+0x10);
                    vec_transform_by_object_or_given(P(vars,0xf4),&pos,&pos,0);
                    if(pos.f[0]<-14.0f) {
                        snd_play_from_class_bank(1,0,P(vars,0xf4),0x11d9);
                        g_ship_sequence_event_states[i]=1;
                    }
                }
            } else {
                part_vars=P(P(vars,0xf4),0x68);
                math_approach_target_with_direction_mode(part_vars+0x114,0.0f,part_vars+0x118,0,0.0017453294713050127f,0.0017453294713050127f,0.10471977f);
                if(F(part_vars,0x114)<=0) g_ship_sequence_event_states[i]=2;
            }
            break;
        case 2:
            if(g_ship_sequence_event_states[i]==0 && g_ship_rider_vars==P(vars,0xf8)) {
                u8 *rider_vars=P(g_ship_rider_vars,0x68);
                int idx;
                moby_set_group_enabled(W(rider_vars,0x94),1);
                idx=W(rider_vars,0xb8);
                pos.q=g_ship_sequence_start_pos;
                rot.q=g_ship_sequence_start_rot;
                moby_attach_to_parent(g_moby_l07_array[0]+(idx<<8),P(vars,0xf8),&pos,&rot);
                g_ship_sequence_event_states[i]=2;
            }
            break;
        case 1:
            if(g_ship_sequence_event_states[i]==0) {
                part_vars=P(P(vars,0xf8),0x68);
                if(moby_count_group_not_in_state(W(part_vars,0x94),-1)<3) {
                    moby_set_flag_bit(g_moby_l07_array[0]+(W(part_vars,0xb8)<<8),1);
                    g_ship_sequence_event_states[i]=2;
                }
            }
            break;
        case 3:
            if(g_ship_sequence_event_states[i]==0) {
                part_vars=P(P(vars,0xf8),0x68);
                if(moby_count_group_not_in_state(W(part_vars,0x98),-1)==0 && moby_count_group_not_in_state(W(part_vars,0x9c),-1)==0) {
                    entity_set_state_five(g_moby_l07_array[0]+(W(P(P(vars,0xf8),0x68),0xb8)<<8));
                    boss_start_move_tier(g_moby_l07_array[0]+(W(vars,0xc4)<<8),P(vars,0xf8),0);
                    g_ship_sequence_event_states[i]=2;
                } else if((g_frame_l07_counter[0]&7)==(((int)P(vars,0xf8)>>8)&7)) {
                    FastVecSub(&pos,g_ship_checkpoint_states,P(vars,0xf8)+0x10);
                    vec_transform_by_object_or_given(P(vars,0xf8),&pos,&pos,0);
                    if(pos.f[0]<-12.0f) {
                        entity_set_state_five(sibEntities+(W(P(P(vars,0xf8),0x68),0xb8)<<8));
                        boss_start_move_tier(g_moby_l07_array[0]+(W(vars,0xc4)<<8),P(vars,0xf8),0);
                        g_ship_sequence_event_states[i]=2;
                    }
                }
            }
            break;
        case 4:
            if(g_ship_sequence_event_states[i]==0) {
                if(boss_get_attack_mode(g_moby_l07_array[0]+(W(vars,0xc4)<<8))==1) {
                    g_ship_sequence_event_states[i]=1;
                    break;
                }
                if(g_ship_sequence_event_states[3]==2) moby_steer_aim_yaw(moby);
            } else {
                Motion *motion=(Motion *)P(P(vars,0xf4),0x68);
                path=g_path_l07_table[motion->path];
                cursor=motion->distance;
                for(j=0;j<3;j++,cursor++) {
                    *cursor-=motion->speed*0.1f;
                    if(*cursor<0) *cursor+=(float)*path;
                }
                remaining=motion->distance[0]-motion->start;
                if(remaining<0) remaining+=(float)*path;
                if(remaining<=32.5f) {
                    g_ship_sequence_event_states[i]=2;
                    g_ship_sequence_event_states[5]=1;
                    snd_play_from_class_bank(1,0,P(vars,0xf8),0x11d9);
                }
            }
            break;
        case 5:
            if(g_ship_sequence_event_states[i]!=0) {
                part_vars=P(P(vars,0xfc),0x68);
                math_approach_target_with_direction_mode(part_vars+0x110,0.0f,part_vars+0x118,0,0.0017453294713050127f,0.0017453294713050127f,0.10471977f);
                if(F(part_vars,0x110)>=0) g_ship_sequence_event_states[i]=2;
            }
            break;
        case 6:
            if(g_ship_sequence_event_states[i]==0 && g_lift_state.riding==P(vars,0xfc) && g_lift_state.ridingFlag) {
                moby_set_group_enabled(W(P(P(vars,0xfc),0x68),0x94),1);
                g_ship_sequence_event_states[i]=2;
            }
            break;
        case 7:
            if(g_ship_sequence_event_states[i]==0) {
                part_vars=P(P(vars,0xfc),0x68);
                if(moby_count_group_not_in_state(W(part_vars,0xa0),-1)==0) {
                    W(part_vars,0x16cc)=snd_play_from_class_bank(2,4,P(vars,0xfc),0x11d9);
                    g_ship_sequence_event_states[i]=2; F(part_vars,0x16c8)=6.0f;
                }
            }
            break;
        case 8:
            if(g_ship_sequence_event_states[i]==0) {
                part_vars=P(P(vars,0xfc),0x68);
                if(moby_count_group_not_in_state(W(part_vars,0x98),-1)==0 && moby_count_group_not_in_state(W(part_vars,0x9c),-1)==0) {
                    g_ship_sequence_event_states[i]=1;
                    snd_play_from_class_bank(1,0,P(vars,0xfc),0x11d9);
                } else if((g_frame_l07_counter[0]&7)==(((int)P(vars,0xfc)>>8)&7)) {
                    FastVecSub(&pos,g_ship_checkpoint_states,P(vars,0xfc)+0x10);
                    vec_transform_by_object_or_given(P(vars,0xfc),&pos,&pos,0);
                    if(pos.f[0]<-14.0f) {
                        g_ship_sequence_event_states[i]=1;
                        snd_play_from_class_bank(1,0,P(vars,0xfc),0x11d9);
                    }
                }
            } else {
                part_vars=P(P(vars,0xfc),0x68);
                math_approach_target_with_direction_mode(part_vars+0x114,0.0f,part_vars+0x118,0,0.0017453294713050127f,0.0017453294713050127f,0.10471977f);
                if(F(part_vars,0x114)<=0) g_ship_sequence_event_states[i]=2;
            }
            break;
        case 9:
            if(g_ship_sequence_event_states[i]==0 && g_lift_state.ridingFlag && g_lift_state.riding==P(vars,0x100)) {
                FastVecSub(&pos,&g_lift_state.position,P(vars,0x100)+0x10);
                vec_transform_by_object_or_given(P(vars,0x100),&pos,&pos,0);
                if(pos.f[2]>5.8f) {
                    boss_start_move_tier(sibEntities+(W(vars,0xc4)<<8),P(vars,0x100),1);
                    g_ship_sequence_event_states[i]=2;
                }
            }
            break;
        case 10:
            if(g_ship_sequence_event_states[i]==0) {
                target=g_moby_l07_array[0]+(W(vars,0xc4)<<8);
                if(boss_get_attack_mode(target)==2 && *(u16 *)(target+0x96)>=121 && g_hero_mode!=20 && g_hero_mode!=7) g_ship_sequence_event_states[i]=1;
                else if(g_ship_sequence_event_states[9]==2) moby_steer_aim_yaw(moby);
            } else if(g_ship_sequence_event_states[i]==1) {
                timer_start_countdown(5,10.0f);
                if(g_ship_fade_amount[0]>=1.0f && g_hero_l07_state_block.phase==1) {
                    g_hero_l07_state_block.phase=60;
                    g_ship_sequence_event_states[i]=2;
                    load_scene_chunk(0,0);
                    rot.q=0; rot.f[2]=g_hero_reset_offset_z[0]; pos.q=rot.q;
                    hero_reset_position_and_direction(&g_hero_l07_reset_position,&pos,0,1);
                    level_capture_checkpoint_state(g_ship_checkpoint_states,&g_ship_checkpoint_states[1]);
                    cam_reset_entry(P(vars,0xd8));
                    {
                        u8 *child=P(vars,0x100);
                        int mode=W(vars,0xd0);
                        g_snowfall_target_moby=0;
                        ship_start_second_phase(child,mode);
                    }
                    moby_mark_table_entry_flagged(moby[0xb0]);
                    moby_set_state(moby,2,-1);
                }
            }
            break;
        }
    }
}
