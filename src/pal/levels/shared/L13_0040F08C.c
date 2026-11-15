#include "include_asm.h"

#include "common.h"
typedef struct L13C3Flags { char pad[0x88]; volatile int flags; } L13C3Flags;
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define S(p,o) (*(short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define P(p,o) (*(char **)((p)+(o)))
extern int math_random_int_below(int);
extern void moby_init_child_from_parent(char *,char *);
extern void moby_set_controller_speed_limits(char *,float,float,float,float);
extern void moby_set_state(char *,int,int);
extern void func_PAL_002A7E68(char *,int,int,int);
extern int FloatToInt(float);
extern void moby_update_ground_check(char *);
extern void moby_transform_joint_point(char *,int,void *);
extern void copy_matrix3x4(char *,void *);
extern void moby_mark_spawned(char *);
extern int func_PAL_002B1A50(char *,char *,int);
extern int weapon_select_aim_target(char *,int,float,float,int,int);
extern void func_PAL_002A7650(char *,int,int);
extern void guard_alt_alert_nearby(u8 *);
extern char D_L13_001B98C0[];
extern char *CreateMoby(int);
extern float fast_vec_dist(void *, void *);
extern u8 *D_L13_001B291C __attribute__((section(".sdata")));

int func_PAL_L13_00410C98(char *obj) {
    char mat[0x40] __attribute__((aligned(16)));
    char *s = P(obj,0x68);
    int kind;
    if (!B(obj,0x20)) {
        qcopy(s+0x360,obj+0x10);
        B(s,0x2e)=1; F(s,0x30)=1.25f;
        I(s,0x274)=I(s,0x270)+math_random_int_below(4);
        I(s,0x284)=0; I(s,0x288)=0;
        if (math_random_int_below(2)) H(obj,0x34)|=0x8000;
        B(s,0x150)=0x1a; I(s,0x188)=3;
        F(s,0x174)=F(s,0x170)=0.5f; F(s,0x17c)=0.15f; B(s,0x155)=0xb;
        if (I(s,0x35c)!=-1) I(s,0x1bc)=I(s,0x35c);
        if (!S(s,0x24)) { S(s,0x24)=1; F(s,0x20)=1.0f; }
        P(s,0x25c)=CreateMoby(0xea9);
        if (P(s,0x25c) && S(P(s,0x25c),0xaa)==0xea9) {
            moby_init_child_from_parent(P(s,0x25c),obj);
            H(P(s,0x25c),0x32)=H(obj,0x32);
            H(P(s,0x25c),0x34)|=0x100;
        }
        F(s,0x84)=0.5f;
        F(s,0x54)=0.2f; F(s,0x50)=0.825f; F(s,0x5c)=F(s,0x58)=0.4f;
        F(s,0x60)=1.5707964897155762f; F(s,0x80)=0.523598849773407f;
        if (I(s,0x2a4)) {
            ((L13C3Flags *)s)->flags|=4; F(s,0x5c)=F(s,0x58)=0.7f;
            H(obj,0x34)|=0x100; F(s,0x60)=12.56637191772461f;
            F(s,0x84)=0.5f; ((L13C3Flags *)s)->flags|=1;
        }
        if (I(s,0x2a8)) { ((L13C3Flags *)s)->flags|=5; F(s,0x50)=0; F(s,0x180)=97.5f; }
        moby_set_controller_speed_limits(obj,0.0048f,0.120000005f,0.010053098f,1.0053098f);
        moby_set_state(obj,1,0);
        if (B(obj,0x43)!=13) func_PAL_002A7E68(obj,13,0,0);
        kind=I(s,0x260);
        if (kind==1) { moby_set_state(obj,2,0); if (B(obj,0x43)!=18) func_PAL_002A7E68(obj,18,0,0); }
        else if (kind==2) { moby_set_state(obj,3,0); if (B(obj,0x43)!=kind) func_PAL_002A7E68(obj,2,0,0); }
        if (I(s,0x28c)) moby_set_state(obj,1,4);
        if (I(s,0x2b0)!=-1) {
            moby_set_state(obj,7,0); if (B(obj,0x43)!=2) func_PAL_002A7E68(obj,2,0,0);
            moby_set_controller_speed_limits(obj,0.0024f,0.050000004f,0.010053098f,1.0053098f);
        }
        if (I(s,0x298) && I(s,0x29c)!=-1) moby_set_state(obj,28,6);
        if (I(s,0x2bc)) { moby_set_state(obj,9,0); if (B(obj,0x43)!=18) func_PAL_002A7E68(obj,18,0,0); }
        if (I(s,0x2c8)) {
            I(obj,0x98)=0; H(obj,0x34)=(H(obj,0x34)|0x41)&0xefff;
            H(P(s,0x25c),0x34)|=0x41; H(P(s,0x25c),0x34)&=0xefff;
            I(P(s,0x25c),0x98)=0; moby_set_state(obj,1,8);
        }
        B(s,0x29)=1; B(s,0x48)=FloatToInt(17.0f); B(s,0x4a)=FloatToInt(12.0f);
    }
    if (B(obj,0x31) && fast_vec_dist(obj+0x10,D_L13_001B98C0)<24.0f) { moby_update_ground_check(obj); B(obj,0x6f)=22; }
    if (P(s,0x25c) && S(P(s,0x25c),0xaa)==0xea9) {
        moby_transform_joint_point(obj,0,mat); copy_matrix3x4(P(s,0x25c)+0xc0,mat); qcopy(P(s,0x25c)+0x10,mat+0x30);
    }
    if (B(s,0x2e)==2) {
        if (P(s,0x25c) && S(P(s,0x25c),0xaa)==0xea9) moby_mark_spawned(P(s,0x25c));
        moby_mark_spawned(obj); return 1;
    }
    if (func_PAL_002B1A50(obj,s+0x140,0)) guard_alt_alert_nearby((u8 *)obj);
    I(s,0x280)=weapon_select_aim_target(obj,I(s,0x27c),0.0f,0.0f,0,0);
    I(s,0x2b8)=weapon_select_aim_target(obj,I(s,0x2b4),0.0f,0.0f,0,0);
    I(s,0x250)=weapon_select_aim_target(obj,I(s,0x230),F(s,0x238),0.0f,0,0);
    I(s,0x254)=weapon_select_aim_target(obj,I(s,0x234),F(s,0x23c),0.0f,0,0);
    if (F(obj,0x18)<89.0f || (I(s,0x2a8) && F(obj,0x18)<98.0f)) {
        if (P(s,0x25c) && S(P(s,0x25c),0xaa)==0xea9) moby_mark_spawned(P(s,0x25c));
        I(s,0x20)=0; func_PAL_002A7650(obj,0,3); return 1;
    }
    return 0;
}

