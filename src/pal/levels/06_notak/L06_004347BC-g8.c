/* func_PAL_L06_004347BC, the PAL copy of func_L06_00430318: the same C, with 50 Hz timers and PAL message ids. */
#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
extern char g_hero_target_point[], g_request_l06_queue[], g_str_coin_door_message[];
typedef struct { char pad0[0x80]; float position[4]; char pad90[0x50]; float vector_e0[4]; } PlayerView;
extern PlayerView g_hero_state;
extern unsigned char g_door_destroy_flag, g_challenge_mode_flag, g_unlocked_item_flags;
extern unsigned char g_coin_door_flag NOT_SDA;
extern int g_object_state_flags_c NOT_SDA, g_pad_held_flags NOT_SDA, g_coin_door_state;
extern int g_player_bolts MACRO_ADDR;
/* Only +4 is accessed; the object's real base is not known. */
extern struct { int pad; int flag; } g_coin_door_flags MACRO_ADDR;
extern struct { int normal, challenge; } g_coin_door_costs NOT_SDA;
extern char *g_moby_l06_table;
extern int func_360F58(char *,int);
extern void func_35C8F8(char *), func_36F678(char *), func_3335E0(char *,int), func_333728(char *);
extern void func_35A550(char *,int,int), func_34BC10(int), func_36F4F8(int,int,int);
extern int func_3B1C70(void), func_36F588(char *,int,float);
extern void hero_reset_position_and_direction_pal(void *,void *,int,int), func_35B810(int,int), func_2E3EF0(char *);
extern void func_3623D0(int), snd_play_indexed_pal(int), func_34B958(int,int), func_350388(char *);
extern int func_32D268(char *),func_32D238(char *),func_35A660(int,int),func_32E728(float);
extern float func_35A6B8(float,float),func_32D7C0(char *,char *),func_32DC80(float,float),func_32E6B8(float,float),func_32D710(char *),func_32E5D0(float,float),func_32E618(float,float),func_32D740(char *);
extern void func_PAL_002A7E68(char *,int,int,int),func_364090(char *,float,float,float),func_32D5C8(char *,char *,char *),func_32D5F8(char *,char *,char *),func_363CD8(char *,char *,int,float,float);
static __inline__ void joint_step(char *obj,char *joint,int index,float speed,float limit)
{
    func_363CD8(obj,joint,index,speed,limit);
}

void func_PAL_L06_004347BC(char *obj)
{
    float target[4], origin[4], delta[4];
    char *s=*(char **)(obj+0x68);
    float speed, limit, yaw, pitch, angle;
    int active;
    switch(B(obj,0x20)) {
    case 0:
        if(g_door_destroy_flag) goto destroy;
        func_35C8F8(obj);
        if(I(s,0x124)) func_35A550(obj,6,-1);
        else if(g_object_state_flags_c&0x400) func_35A550(obj,2,-1);
        else func_35A550(obj,1,-1);
        break;
    case 1:
        if(func_360F58(((char *)&g_hero_state.position),I(s,0x128))) {
            func_36F678(obj);
            func_3335E0(g_request_l06_queue,0x4a);
            func_333728(g_request_l06_queue);
            func_35A550(obj,2,-1);
        }
        break;
    case 2: {
        g_coin_door_flags.flag=1;
        if(g_coin_door_state==2) {B(obj,0x31)=0;H(obj,0x34)|=1;}
        if(func_3B1C70()) break;
        g_coin_door_flags.flag=0;
        H(obj,0x34)&=0xfffe; B(obj,0x31)=1;
        target[0]=456.0800f;target[1]=251.2400f;target[2]=68.9200f;
        origin[2]=-2.094395399093628f;
        hero_reset_position_and_direction_pal(target,origin,0,1);
        {
            int challenge = g_challenge_mode_flag;
            int coins = g_player_bolts;
            if(challenge) {
                if(coins>=g_coin_door_costs.challenge) {func_35A550(obj,4,-1);break;}
            } else if(coins>=g_coin_door_costs.normal) goto state4;
            func_35A550(obj,3,-1);
            break;
        state4:
            func_35A550(obj,4,-1);break;
        }
    }
    case 3: {
        int challenge = g_challenge_mode_flag;
        int coins = g_player_bolts;
        if(challenge ? g_coin_door_costs.challenge<coins : g_coin_door_costs.normal<coins) {
            func_35A550(obj,4,-1); break;
        }
        if(func_36F588(obj,10,2.5f)) {
            func_34BC10(150);
            func_36F4F8(0x1320,g_challenge_mode_flag ? g_coin_door_costs.challenge : g_coin_door_costs.normal,-1);
            func_36F678(obj);
        }
        break;
    }
    case 4: {
        int challenge = g_challenge_mode_flag;
        int coins = g_player_bolts;
        if(challenge ? coins<g_coin_door_costs.challenge : coins<g_coin_door_costs.normal) {
            func_34BC10(150);func_35A550(obj,3,-1);break;
        }
        if(func_36F588(obj,10,2.5f)) {
            func_34BC10(150);
            func_36F4F8(0x1321,g_challenge_mode_flag ? g_coin_door_costs.challenge : g_coin_door_costs.normal,-1);
            func_36F678(obj);
            if(g_pad_held_flags&0x10) {
                func_3335E0(g_request_l06_queue,0x4b);func_3335E0(g_request_l06_queue,7);func_3335E0(g_request_l06_queue,0x4c);func_333728(g_request_l06_queue);func_35A550(obj,5,-1);
            }
        }
        break;
    }
    case 5:
        g_coin_door_flags.flag=1;
        if(g_coin_door_state==2) {B(obj,0x31)=0;H(obj,0x34)|=1;}
        if(func_3B1C70()) break;
        g_coin_door_flags.flag=0;B(obj,0x31)=1;H(obj,0x34)&=0xfffe;
        if(B(obj,0x21)!=255) func_35B810(B(obj,0x21),1);
        func_2E3EF0(g_str_coin_door_message);
        g_coin_door_flag=1;
        if(!g_door_destroy_flag) {
            func_3623D0(7);snd_play_indexed_pal(7);
            {
                int challenge = g_challenge_mode_flag;
                int coins = g_player_bolts;
                int left;
                if(challenge) left=coins-g_coin_door_costs.challenge;
                else left=coins-g_coin_door_costs.normal;
                g_player_bolts=left;
            }
            func_34BC10(150);
        }
        if(I(s,0x120)!=-1) B(g_moby_l06_table,(I(s,0x120)<<8)+0xbc)=1;
        func_34B958(0,-1);
        goto destroy;
    case 6:
        if(g_coin_door_state==2) {B(obj,0x31)=0;H(obj,0x34)|=1;}
        else {B(obj,0x31)=1;H(obj,0x34)&=0xfffe;}
        if(g_door_destroy_flag) {destroy:func_350388(obj);return;}
        break;
    }
    if(B(obj,0x20)) {
        if(B(obj,0x43)==2 && func_32D268(s+0x11e)) {
            H(s,0x11e)=func_32E728((func_35A6B8(1200,2400)*5.0f+2.0f)*0.16666667f);
            if(B(obj,0x43)!=3) func_PAL_002A7E68(obj,3,0,(func_35A660(10,20)*5+2)/6);
        } else if(B(obj,0x60)&2) {
            if(B(obj,0x43)!=2) func_PAL_002A7E68(obj,2,0,(func_35A660(10,20)*5+2)/6);
            F(obj,0x48)=func_35A6B8(0.9f,1.1f);
        }
    }
    speed=0.02f;
    limit=0.3f;
    active=0;
    if(B(obj,0x43)==2) {
        active=1;
        if(func_32D7C0(obj+0x10,((char *)&g_hero_state.position))<8.0f && func_32E6B8(F(obj,0xf8),func_32DC80(g_hero_state.vector_e0[0]-F(obj,0x10),g_hero_state.vector_e0[1]-F(obj,0x14)))<1.5707964897155762f) {
            if(func_32D710(((char *)&g_hero_state.position)+0x90)>0.01f) I(s,0x114)=100;
            else func_32D238(s+0x114);
        } else if(I(s,0x114)) {I(s,0x114)=0;qcopy(s+0x100,g_hero_target_point);}
        if(func_32D238(s+0x118)) {
            I(s,0x118)=func_32E728((func_35A6B8(180,300)*5.0f+2.0f)*0.16666667f);
            angle=func_32E5D0(F(obj,0xf8),func_35A6B8(-90,90)*0.01745329424738884f);
            func_364090(s+0x100,6,angle,func_35A6B8(0,30)*0.01745329424738884f);
            func_32D5C8(s+0x100,s+0x100,obj+0x10);
        }
        if(I(s,0x114)) {qcopy(target,g_hero_target_point);speed=0.04f;limit=0.3f;}
        else qcopy(target,s+0x100);
    }
    if(active) {
        qcopy(origin,obj+0x10);origin[2]+=2;
        func_32D5F8((char *)delta,(char *)target,(char *)origin);
        yaw=func_32E618(func_32DC80(delta[0],delta[1]),F(obj,0xf8));
        pitch=-func_32DC80(func_32D740((char *)delta),delta[2]);
        if(yaw>1.5707964897155762f) yaw=1.5707964897155762f;
        else if(yaw< -1.5707964897155762f) yaw= -1.5707964897155762f;
        if(pitch>0.523598849773407f) pitch=0.523598849773407f;
        else if(pitch< -0.523598849773407f) pitch= -0.523598849773407f;
        F(s,0x64)=pitch;F(s,0x68)=yaw*0.6f;F(s,0xe8)=yaw*0.4f;
    }
    if(g_unlocked_item_flags) F(s,0x70)=2.75f;
    joint_step(obj,s,0,speed*1.44f,limit*1.44f);joint_step(obj,s+0x80,1,speed*1.44f,limit*1.44f);
}
