#include "include_asm.h"

#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
extern char D_00189F00[], D_L06_001BFA40[], D_L06_001B0B80[];
typedef struct { char pad0[0x80]; float position[4]; char pad90[0x50]; float vector_e0[4]; } PlayerView;
extern PlayerView g_hero_state;
#define PLAYER_POSITION ((char *)&D_00189E20.position)
extern unsigned char D_001A7BCF, D_001A7C8F, D_001A7A40;
extern unsigned char D_001395CD NOT_SDA;
extern int D_001397B0 NOT_SDA, D_00138324 NOT_SDA, D_L06_001A8F00;
extern int g_player_bolts MACRO_ADDR;
extern struct { int pad; int flag; } D_L06_001B2564 MACRO_ADDR;
extern struct { int normal, challenge; } D_L06_002958D0 NOT_SDA;
extern char *D_L06_001B281C;
extern int IsPointInCuboid(char *,int);
extern void moby_reset_vars_defaults(char *), level_apply_index_for_key(char *);
extern s32 req_launch_queued(char *);
extern s32 req_push_queue(char *,int);
extern void moby_set_state(char *,int,int), func_L00_0030C710(int), text_print_localized_formatted(int,int,int);
extern int game_is_either_mode_two(void), hero_is_reachable_for_count(char *,int,float);
extern void hero_reset_position_and_direction(void *,void *,int,int), moby_set_byte_on_group(int,int), STUB_printf(char *);
extern void moby_mark_flag_and_append_to_list(int), func_US2_002AFF10(int), moby_mark_spawned(char *);
extern int MemcardSave(int,int);
extern int FastDecTimer(char *),math_fast_float_d(char *),math_random_int_range(int,int),FloatToInt(float);
extern float math_random_float_range(float,float),vec_distance_xy(char *,char *),mat_fast_helper_a(float,float),FastDiffRots(float,float),FastVecLength(char *),FastAddRotations(float,float),fast_subtract_rotations(float,float),vec_length_xy(char *);
extern void anim_start_blended(char *,int,int,int),vec_build_spherical_offset(char *,float,float,float),FastVecAdd(char *,char *,char *),FastVecSub(char *,char *,char *),moby_update_eased_node(char *,char *,int,float,float);
static __inline__ void joint_step(char *obj,char *joint,int index,float speed,float limit)
{
    moby_update_eased_node(obj,joint,index,speed,limit);
}

void func_US2_L06_004318A0(char *obj)
{
    float target[4], origin[4], delta[4];
    char *s=*(char **)(obj+0x68);
    float speed, yaw, pitch, angle;
    int active;
    switch(B(obj,0x20)) {
    case 0:
        if(D_001A7BCF) goto destroy;
        moby_reset_vars_defaults(obj);
        if(I(s,0x124)) moby_set_state(obj,6,-1);
        else if(D_001397B0&0x400) moby_set_state(obj,2,-1);
        else moby_set_state(obj,1,-1);
        break;
    case 1:
        if(IsPointInCuboid(PLAYER_POSITION,I(s,0x128))) {
            level_apply_index_for_key(obj);
            req_push_queue(D_L06_001BFA40,0x4a);
            req_launch_queued(D_L06_001BFA40);
            moby_set_state(obj,2,-1);
        }
        break;
    case 2: {
        D_L06_001B2564.flag=1;
        if(D_L06_001A8F00==2) {B(obj,0x31)=0;H(obj,0x34)|=1;}
        if(game_is_either_mode_two()) break;
        D_L06_001B2564.flag=0;
        H(obj,0x34)&=0xfffe; B(obj,0x31)=1;
        target[0]=456.0800f;target[1]=251.2400f;target[2]=68.9200f;
        origin[2]=-2.094395399093628f;
        hero_reset_position_and_direction(target,origin,0,1);
        {
            int challenge = D_001A7C8F;
            int coins = g_player_bolts;
            if(challenge) {
                if(coins>=D_L06_002958D0.challenge) {moby_set_state(obj,4,-1);break;}
            } else if(coins>=D_L06_002958D0.normal) goto state4;
            moby_set_state(obj,3,-1);
            break;
        state4:
            moby_set_state(obj,4,-1);break;
        }
    }
    case 3: {
        int challenge = D_001A7C8F;
        int coins = g_player_bolts;
        if(challenge ? D_L06_002958D0.challenge<coins : D_L06_002958D0.normal<coins) {
            moby_set_state(obj,4,-1); break;
        }
        if(hero_is_reachable_for_count(obj,10,2.5f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x1320,D_001A7C8F ? D_L06_002958D0.challenge : D_L06_002958D0.normal,-1);
            level_apply_index_for_key(obj);
        }
        break;
    }
    case 4: {
        int challenge = D_001A7C8F;
        int coins = g_player_bolts;
        if(challenge ? coins<D_L06_002958D0.challenge : coins<D_L06_002958D0.normal) {
            func_L00_0030C710(180);moby_set_state(obj,3,-1);break;
        }
        if(hero_is_reachable_for_count(obj,10,2.5f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x1321,D_001A7C8F ? D_L06_002958D0.challenge : D_L06_002958D0.normal,-1);
            level_apply_index_for_key(obj);
            if(D_00138324&0x10) {
                req_push_queue(D_L06_001BFA40,0x4b);req_push_queue(D_L06_001BFA40,7);req_push_queue(D_L06_001BFA40,0x4c);req_launch_queued(D_L06_001BFA40);moby_set_state(obj,5,-1);
            }
        }
        break;
    }
    case 5:
        D_L06_001B2564.flag=1;
        if(D_L06_001A8F00==2) {B(obj,0x31)=0;H(obj,0x34)|=1;}
        if(game_is_either_mode_two()) break;
        D_L06_001B2564.flag=0;B(obj,0x31)=1;H(obj,0x34)&=0xfffe;
        if(B(obj,0x21)!=255) moby_set_byte_on_group(B(obj,0x21),1);
        STUB_printf(D_L06_001B0B80);
        D_001395CD=1;
        if(!D_001A7BCF) {
            moby_mark_flag_and_append_to_list(7);func_US2_002AFF10(7);
            {
                int challenge = D_001A7C8F;
                int coins = g_player_bolts;
                int left;
                if(challenge) left=coins-D_L06_002958D0.challenge;
                else left=coins-D_L06_002958D0.normal;
                g_player_bolts=left;
            }
            func_L00_0030C710(180);
        }
        if(I(s,0x120)!=-1) B(D_L06_001B281C,(I(s,0x120)<<8)+0xbc)=1;
        MemcardSave(0,-1);
        goto destroy;
    case 6:
        if(D_L06_001A8F00==2) {B(obj,0x31)=0;H(obj,0x34)|=1;}
        else {B(obj,0x31)=1;H(obj,0x34)&=0xfffe;}
        if(D_001A7BCF) {destroy:moby_mark_spawned(obj);return;}
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
        } else if(I(s,0x114)) {I(s,0x114)=0;qcopy(s+0x100,D_00189F00);}
        if(math_fast_float_d(s+0x118)) {
            I(s,0x118)=FloatToInt(math_random_float_range(180,300));
            angle=FastAddRotations(F(obj,0xf8),math_random_float_range(-90,90)*0.01745329424738884f);
            vec_build_spherical_offset(s+0x100,6,angle,math_random_float_range(0,30)*0.01745329424738884f);
            FastVecAdd(s+0x100,s+0x100,obj+0x10);
        }
        if(I(s,0x114)) {qcopy(target,D_00189F00);speed=0.04f;}
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
    if(D_001A7A40) F(s,0x70)=2.75f;
    joint_step(obj,s,0,speed,0.3f);joint_step(obj,s+0x80,1,speed,0.3f);
}
