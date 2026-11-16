#include "include_asm.h"

#include "common.h"
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(u16 *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern void hover_enemy_init_pal(void *), moby_update_ground_check(void *), moby_transform_joint_point(void *,int,void *), vec_clear_128(void *), transform_vector(void *,void *,void *), FastVecAdd(void *,void *,void *), mat_get_euler_angles(void *,void *), moby_rotate_about_point(void *,void *,float,float,float), SetDeathBits_pal(void *,int,int), moby_mark_spawned(void *), hover_enemy_alert_group(void *), group_pick_nearest_target(void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern int weapon_select_aim_target(void *,int,int,int,float,float);
extern float fast_vec_dist(void *,void *),coll_probe_ground_height_below(void *,int,float);
extern int moby_apply_damage_to_object_pal(void *,void *,int),CollLine(void *,void *,int,void *,int),moby_count_group_not_in_state(int,int);
extern int GetCollHitMaterial(void);
extern int group_pass_lead_token(void *);
extern char g_camera_eye_state[];
extern char g_default_effect_vector[16] MACRO_ADDR;
extern int g_moby_group_count MACRO_ADDR;
extern short *g_moby_group_lists[];
extern char *g_moby_pool_start MACRO_ADDR;
extern char *g_hero_moby NOT_SDA;

/* Per-frame body update of the hovering enemy: ground checks, damage reactions and alerting its group (PAL build). */
void hover_enemy_update_body_group_pal(char *self)
{
    float matrix[16];
    float pos_a[4],pos_b[4];
    char *data=P(self,0x68);
    float height;
    int result,kind,mode;
    short *list;
    char *other;
    if(B(self,0x20)==0) hover_enemy_init_pal(self);
    if(B(self,0x31) && fast_vec_dist(self+0x10,g_camera_eye_state)<24.0f) {
        moby_update_ground_check(self);
        B(self,0x6F)=22;
    }
    moby_transform_joint_to_world(self,0,data+0x300);
    moby_transform_joint_to_world(self,1,data+0x310);
    moby_transform_joint_to_world(self,2,data+0x320);
    moby_transform_joint_point(self,3,matrix);
    vec_clear_128(data+0x330);
    F(data,0x338)=0.0f;
    F(data,0x330)=0.25f;
    transform_vector(data+0x330,data+0x330,matrix);
    FastVecAdd(data+0x330,data+0x330,matrix+12);
    result=moby_apply_damage_to_object_pal(self,data+0x80,0);
    height=coll_probe_ground_height_below(self+0x10,0,0.5f);
    if(height==0.0f || F(self,0x18)-height>20.0f) {
        if(B(data,0x9A)==1) {
            if(H(self,0x34)&0x100) {
                mat_get_euler_angles(self+0xC0,self+0xF0);
                H(self,0x34)&=~0x100;
            }
            qcopy(pos_a,g_default_effect_vector);
            pos_a[2]+=0.5f;
            moby_rotate_about_point(self,pos_a,0.05f,0.05f,0.0f);
        }
    } else {
        qcopy(pos_a,self+0x10);
        qcopy(pos_b,self+0x10);
        pos_b[2]-=1.0f;
        if(CollLine(pos_a,pos_b,0,self,0)) {
            kind=GetCollHitMaterial();
            if(kind==1 || kind==11) {
                SetDeathBits_pal(self,0,3);
                moby_mark_spawned(self);
                return;
            }
        }
    }
    if(result) {
        if(result==5) {
            I(data,0x110)=0;
            F(data,0x114)=1.0053098f;
        }
        hover_enemy_alert_group(self);
        group_pass_lead_token(self);
        if((result==4 || result==5) && g_moby_group_count>=B(self,0x21) && moby_count_group_not_in_state(B(self,0x21),-1)>=2) {
            list=g_moby_group_lists[B(self,0x21)];
            do {
                other=g_moby_pool_start+((*list&0x7FFF)<<8);
                if(*(short *)(other+0xAA)==0x9B4 && I(P(other,0x68),0x2A4)==0) {
                    I(P(other,0x68),0x2A4)=1;
                    goto done_list;
                }
            } while(*list++>=0);
        }
    }
done_list:
    weapon_select_aim_target(self,I(data,0x400),0,0,0.0f,0.0f);
    mode=B(self,0x20);
    if(mode!=3 && mode!=12 && mode!=13 && mode!=14 && mode!=16 && I(data,0x350) && P(data,0x30)==g_hero_moby)
        group_pick_nearest_target(self);
}
