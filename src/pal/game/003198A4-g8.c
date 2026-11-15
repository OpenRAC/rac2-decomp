#include "include_asm.h"

#include "common.h"
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(u16 *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern void func_PAL_0031B110(void *), moby_update_ground_check(void *), moby_transform_joint_point(void *,int,void *), vec_clear_128(void *), transform_vector(void *,void *,void *), FastVecAdd(void *,void *,void *), mat_get_euler_angles(void *,void *), moby_rotate_about_point(void *,void *,float,float,float), func_PAL_002A7650(void *,int,int), moby_mark_spawned(void *), hover_enemy_alert_group(void *), group_pick_nearest_target(void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern int weapon_select_aim_target(void *,int,int,int,float,float);
extern float fast_vec_dist(void *,void *),coll_probe_ground_height_below(void *,int,float);
extern int func_PAL_002B1A50(void *,void *,int),CollLine(void *,void *,int,void *,int),moby_count_group_not_in_state(int,int);
extern int GetCollHitMaterial(void);
extern int group_pass_lead_token(void *);
extern char g_camera_eye_state[];
extern char D_001A8BD0[16] MACRO_ADDR;
extern int D_001B1B78 MACRO_ADDR;
extern short *D_001EE5A0[];
extern char *D_001B1B5C MACRO_ADDR;
extern char *g_hero_moby NOT_SDA;

void func_PAL_0031AD58(char *self)
{
    float matrix[16];
    float a[4],b[4];
    char *d=P(self,0x68);
    float height;
    int result,kind,mode;
    short *list;
    char *moby;
    if(B(self,0x20)==0) func_PAL_0031B110(self);
    if(B(self,0x31) && fast_vec_dist(self+0x10,g_camera_eye_state)<24.0f) {
        moby_update_ground_check(self);
        B(self,0x6F)=22;
    }
    moby_transform_joint_to_world(self,0,d+0x300);
    moby_transform_joint_to_world(self,1,d+0x310);
    moby_transform_joint_to_world(self,2,d+0x320);
    moby_transform_joint_point(self,3,matrix);
    vec_clear_128(d+0x330);
    F(d,0x338)=0.0f;
    F(d,0x330)=0.25f;
    transform_vector(d+0x330,d+0x330,matrix);
    FastVecAdd(d+0x330,d+0x330,matrix+12);
    result=func_PAL_002B1A50(self,d+0x80,0);
    height=coll_probe_ground_height_below(self+0x10,0,0.5f);
    if(height==0.0f || F(self,0x18)-height>20.0f) {
        if(B(d,0x9A)==1) {
            if(H(self,0x34)&0x100) {
                mat_get_euler_angles(self+0xC0,self+0xF0);
                H(self,0x34)&=~0x100;
            }
            qcopy(a,D_001A8BD0);
            a[2]+=0.5f;
            moby_rotate_about_point(self,a,0.05f,0.05f,0.0f);
        }
    } else {
        qcopy(a,self+0x10);
        qcopy(b,self+0x10);
        b[2]-=1.0f;
        if(CollLine(a,b,0,self,0)) {
            kind=GetCollHitMaterial();
            if(kind==1 || kind==11) {
                func_PAL_002A7650(self,0,3);
                moby_mark_spawned(self);
                return;
            }
        }
    }
    if(result) {
        if(result==5) {
            I(d,0x110)=0;
            F(d,0x114)=1.0053098f;
        }
        hover_enemy_alert_group(self);
        group_pass_lead_token(self);
        if((result==4 || result==5) && D_001B1B78>=B(self,0x21) && moby_count_group_not_in_state(B(self,0x21),-1)>=2) {
            list=D_001EE5A0[B(self,0x21)];
            do {
                moby=D_001B1B5C+((*list&0x7FFF)<<8);
                if(*(short *)(moby+0xAA)==0x9B4 && I(P(moby,0x68),0x2A4)==0) {
                    I(P(moby,0x68),0x2A4)=1;
                    goto done_list;
                }
            } while(*list++>=0);
        }
    }
done_list:
    weapon_select_aim_target(self,I(d,0x400),0,0,0.0f,0.0f);
    mode=B(self,0x20);
    if(mode!=3 && mode!=12 && mode!=13 && mode!=14 && mode!=16 && I(d,0x350) && P(d,0x30)==g_hero_moby)
        group_pick_nearest_target(self);
}
