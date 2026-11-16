#include "include_asm.h"

#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
extern char g_hero_target_point[], g_request_l06_queue[], g_str_coin_door_message[];
typedef struct { char pad0[0x80]; float position[4]; char pad90[0x50]; float vector_e0[4]; } PlayerView;
extern PlayerView g_hero_state;
#define PLAYER_POSITION ((char *)&D_00189E20.position)
extern unsigned char g_door_destroy_flag, g_challenge_mode_flag, g_unlocked_item_flags;
extern unsigned char g_coin_door_flag NOT_SDA;
extern int g_object_state_flags_c NOT_SDA, g_pad_held_flags NOT_SDA, g_coin_door_state;
extern int g_player_bolts MACRO_ADDR;
extern struct { int pad; int flag; } g_coin_door_flags MACRO_ADDR;
extern struct { int normal, challenge; } g_coin_door_costs NOT_SDA;
extern char *g_moby_l06_table;
extern int IsPointInCuboid(char *,int);
extern void moby_reset_vars_defaults(char *), level_apply_index_for_key(char *);
extern s32 req_launch_queued(char *);
extern s32 req_push_queue(char *,int);
extern void moby_set_state(char *,int,int), func_L00_0030C710(int), text_print_localized_formatted(int,int,int);
extern int game_is_either_mode_two(void), hero_is_reachable_for_count(char *,int,float);
extern void hero_reset_position_and_direction(void *,void *,int,int), moby_set_byte_on_group(int,int), STUB_printf(char *);
extern void moby_mark_flag_and_append_to_list(int), snd_play_indexed_us2(int), moby_mark_spawned(char *);
extern int MemcardSave(int,int);
extern int FastDecTimer(char *),math_fast_float_d(char *),math_random_int_range(int,int),FloatToInt(float);
extern float math_random_float_range(float,float),vec_distance_xy(char *,char *),mat_fast_helper_a(float,float),FastDiffRots(float,float),FastVecLength(char *),FastAddRotations(float,float),fast_subtract_rotations(float,float),vec_length_xy(char *);
extern void anim_start_blended(char *,int,int,int),vec_build_spherical_offset(char *,float,float,float),FastVecAdd(char *,char *,char *),FastVecSub(char *,char *,char *),moby_update_eased_node(char *,char *,int,float,float);
static __inline__ void joint_step(char *obj,char *joint,int index,float speed,float limit)
{
    moby_update_eased_node(obj,joint,index,speed,limit);
}

void coin_gated_door_update_us2(char *obj)
{
    float target[4], origin[4], delta[4];
    char *s=*(char **)(obj+0x68);
    float speed, yaw, pitch, angle;
    int active;
    switch(B(obj,0x20)) {
    case 0:
        if(g_door_destroy_flag) goto destroy;
        moby_reset_vars_defaults(obj);
        if(I(s,0x124)) moby_set_state(obj,6,-1);
        else if(g_object_state_flags_c&0x400) moby_set_state(obj,2,-1);
        else moby_set_state(obj,1,-1);
        break;
    case 1:
        if(IsPointInCuboid(PLAYER_POSITION,I(s,0x128))) {
            level_apply_index_for_key(obj);
            req_push_queue(g_request_l06_queue,0x4a);
            req_launch_queued(g_request_l06_queue);
            moby_set_state(obj,2,-1);
        }
        break;
    case 2: {
        g_coin_door_flags.flag=1;
        if(g_coin_door_state==2) {B(obj,0x31)=0;H(obj,0x34)|=1;}
        if(game_is_either_mode_two()) break;
        g_coin_door_flags.flag=0;
        H(obj,0x34)&=0xfffe; B(obj,0x31)=1;
        target[0]=456.0800f;target[1]=251.2400f;target[2]=68.9200f;
        origin[2]=-2.094395399093628f;
        hero_reset_position_and_direction(target,origin,0,1);
        {
            int challenge = g_challenge_mode_flag;
            int coins = g_player_bolts;
            if(challenge) {
                if(coins>=g_coin_door_costs.challenge) {moby_set_state(obj,4,-1);break;}
            } else if(coins>=g_coin_door_costs.normal) goto state4;
            moby_set_state(obj,3,-1);
            break;
        state4:
            moby_set_state(obj,4,-1);break;
        }
    }
    case 3: {
        int challenge = g_challenge_mode_flag;
        int coins = g_player_bolts;
        if(challenge ? g_coin_door_costs.challenge<coins : g_coin_door_costs.normal<coins) {
            moby_set_state(obj,4,-1); break;
        }
        if(hero_is_reachable_for_count(obj,10,2.5f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x1320,g_challenge_mode_flag ? g_coin_door_costs.challenge : g_coin_door_costs.normal,-1);
            level_apply_index_for_key(obj);
        }
        break;
    }
    case 4: {
        int challenge = g_challenge_mode_flag;
        int coins = g_player_bolts;
        if(challenge ? coins<g_coin_door_costs.challenge : coins<g_coin_door_costs.normal) {
            func_L00_0030C710(180);moby_set_state(obj,3,-1);break;
        }
        if(hero_is_reachable_for_count(obj,10,2.5f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x1321,g_challenge_mode_flag ? g_coin_door_costs.challenge : g_coin_door_costs.normal,-1);
            level_apply_index_for_key(obj);
            if(g_pad_held_flags&0x10) {
                req_push_queue(g_request_l06_queue,0x4b);req_push_queue(g_request_l06_queue,7);req_push_queue(g_request_l06_queue,0x4c);req_launch_queued(g_request_l06_queue);moby_set_state(obj,5,-1);
            }
        }
        break;
    }
    case 5:
        g_coin_door_flags.flag=1;
        if(g_coin_door_state==2) {B(obj,0x31)=0;H(obj,0x34)|=1;}
        if(game_is_either_mode_two()) break;
        g_coin_door_flags.flag=0;B(obj,0x31)=1;H(obj,0x34)&=0xfffe;
        if(B(obj,0x21)!=255) moby_set_byte_on_group(B(obj,0x21),1);
        STUB_printf(g_str_coin_door_message);
        g_coin_door_flag=1;
        if(!g_door_destroy_flag) {
            moby_mark_flag_and_append_to_list(7);snd_play_indexed_us2(7);
            {
                int challenge = g_challenge_mode_flag;
                int coins = g_player_bolts;
                int left;
                if(challenge) left=coins-g_coin_door_costs.challenge;
                else left=coins-g_coin_door_costs.normal;
                g_player_bolts=left;
            }
            func_L00_0030C710(180);
        }
        if(I(s,0x120)!=-1) B(g_moby_l06_table,(I(s,0x120)<<8)+0xbc)=1;
        MemcardSave(0,-1);
        goto destroy;
    case 6:
        if(g_coin_door_state==2) {B(obj,0x31)=0;H(obj,0x34)|=1;}
        else {B(obj,0x31)=1;H(obj,0x34)&=0xfffe;}
        if(g_door_destroy_flag) {destroy:moby_mark_spawned(obj);return;}
        break;
    }
    if(B(obj,0x20)) {
        if(B(obj,0x43)==2 && FastDecTimer(s+0x11e)) {
            H(s,0x11e)=FloatToInt(math_random_float_range(1200,2400));
            if(B(obj,0x43)!=3) anim_start_blended(obj,3,0,math_random_int_range(10,20));
        } else if(B(obj,0x60)&2) {
            if(B(obj,0x43)!=2) anim_start_blended(obj,2,0,math_random_int_range(10,20));
            F(obj,0x48)=math_random_float_range(0.9f,1.1f);
        }
    }
    speed=0.02f;
    active=0;
    if(B(obj,0x43)==2) {
        active=1;
        if(vec_distance_xy(obj+0x10,PLAYER_POSITION)<8.0f && FastDiffRots(F(obj,0xf8),mat_fast_helper_a(g_hero_state.vector_e0[0]-F(obj,0x10),g_hero_state.vector_e0[1]-F(obj,0x14)))<1.5707964897155762f) {
            if(FastVecLength(PLAYER_POSITION+0x90)>0.01f) I(s,0x114)=120;
            else math_fast_float_d(s+0x114);
        } else if(I(s,0x114)) {I(s,0x114)=0;qcopy(s+0x100,g_hero_target_point);}
        if(math_fast_float_d(s+0x118)) {
            I(s,0x118)=FloatToInt(math_random_float_range(180,300));
            angle=FastAddRotations(F(obj,0xf8),math_random_float_range(-90,90)*0.01745329424738884f);
            vec_build_spherical_offset(s+0x100,6,angle,math_random_float_range(0,30)*0.01745329424738884f);
            FastVecAdd(s+0x100,s+0x100,obj+0x10);
        }
        if(I(s,0x114)) {qcopy(target,g_hero_target_point);speed=0.04f;}
        else qcopy(target,s+0x100);
    }
    if(active) {
        qcopy(origin,obj+0x10);origin[2]+=2;
        FastVecSub((char *)delta,(char *)target,(char *)origin);
        yaw=fast_subtract_rotations(mat_fast_helper_a(delta[0],delta[1]),F(obj,0xf8));
        pitch=-mat_fast_helper_a(vec_length_xy((char *)delta),delta[2]);
        if(yaw>1.5707964897155762f) yaw=1.5707964897155762f;
        else if(yaw< -1.5707964897155762f) yaw= -1.5707964897155762f;
        if(pitch>0.523598849773407f) pitch=0.523598849773407f;
        else if(pitch< -0.523598849773407f) pitch= -0.523598849773407f;
        F(s,0x64)=pitch;F(s,0x68)=yaw*0.6f;F(s,0xe8)=yaw*0.4f;
    }
    if(g_unlocked_item_flags) F(s,0x70)=2.75f;
    joint_step(obj,s,0,speed,0.3f);joint_step(obj,s+0x80,1,speed,0.3f);
}
