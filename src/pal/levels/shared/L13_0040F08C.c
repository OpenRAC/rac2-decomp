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
extern void anim_start_blended_pal(char *,int,int,int);
extern int FloatToInt(float);
extern void moby_update_ground_check(char *);
extern void moby_transform_joint_point(char *,int,void *);
extern void copy_matrix3x4(char *,void *);
extern void moby_mark_spawned(char *);
extern int moby_apply_damage_to_object_pal(char *,char *,int);
extern int weapon_select_aim_target(char *,int,float,float,int,int);
extern void SetDeathBits_pal(char *,int,int);
extern void guard_alt_alert_nearby(u8 *);
extern char g_camera_l13_position[];
extern char *CreateMoby(int);
extern float fast_vec_dist(void *, void *);
extern u8 *g_object_table_base __attribute__((section(".sdata")));

/* Sets up the second guard kind on its first frame from its path and settings, then keeps its
 * ground check, glow part and aim targets up to date; returns 1 when the guard is gone. (PAL) */
int guard_alt_init_check_pal(char *moby) {
    char mat[0x40] __attribute__((aligned(16)));
    char *vars = P(moby,0x68);
    int kind;
    if (!B(moby,0x20)) {
        qcopy(vars+0x360,moby+0x10);
        B(vars,0x2e)=1; F(vars,0x30)=1.25f;
        I(vars,0x274)=I(vars,0x270)+math_random_int_below(4);
        I(vars,0x284)=0; I(vars,0x288)=0;
        if (math_random_int_below(2)) H(moby,0x34)|=0x8000;
        B(vars,0x150)=0x1a; I(vars,0x188)=3;
        F(vars,0x174)=F(vars,0x170)=0.5f; F(vars,0x17c)=0.15f; B(vars,0x155)=0xb;
        if (I(vars,0x35c)!=-1) I(vars,0x1bc)=I(vars,0x35c);
        if (!S(vars,0x24)) { S(vars,0x24)=1; F(vars,0x20)=1.0f; }
        P(vars,0x25c)=CreateMoby(0xea9);
        if (P(vars,0x25c) && S(P(vars,0x25c),0xaa)==0xea9) {
            moby_init_child_from_parent(P(vars,0x25c),moby);
            H(P(vars,0x25c),0x32)=H(moby,0x32);
            H(P(vars,0x25c),0x34)|=0x100;
        }
        F(vars,0x84)=0.5f;
        F(vars,0x54)=0.2f; F(vars,0x50)=0.825f; F(vars,0x5c)=F(vars,0x58)=0.4f;
        F(vars,0x60)=1.5707964897155762f; F(vars,0x80)=0.523598849773407f;
        if (I(vars,0x2a4)) {
            ((L13C3Flags *)vars)->flags|=4; F(vars,0x5c)=F(vars,0x58)=0.7f;
            H(moby,0x34)|=0x100; F(vars,0x60)=12.56637191772461f;
            F(vars,0x84)=0.5f; ((L13C3Flags *)vars)->flags|=1;
        }
        if (I(vars,0x2a8)) { ((L13C3Flags *)vars)->flags|=5; F(vars,0x50)=0; F(vars,0x180)=97.5f; }
        moby_set_controller_speed_limits(moby,0.0048f,0.120000005f,0.010053098f,1.0053098f);
        moby_set_state(moby,1,0);
        if (B(moby,0x43)!=13) anim_start_blended_pal(moby,13,0,0);
        kind=I(vars,0x260);
        if (kind==1) { moby_set_state(moby,2,0); if (B(moby,0x43)!=18) anim_start_blended_pal(moby,18,0,0); }
        else if (kind==2) { moby_set_state(moby,3,0); if (B(moby,0x43)!=kind) anim_start_blended_pal(moby,2,0,0); }
        if (I(vars,0x28c)) moby_set_state(moby,1,4);
        if (I(vars,0x2b0)!=-1) {
            moby_set_state(moby,7,0); if (B(moby,0x43)!=2) anim_start_blended_pal(moby,2,0,0);
            moby_set_controller_speed_limits(moby,0.0024f,0.050000004f,0.010053098f,1.0053098f);
        }
        if (I(vars,0x298) && I(vars,0x29c)!=-1) moby_set_state(moby,28,6);
        if (I(vars,0x2bc)) { moby_set_state(moby,9,0); if (B(moby,0x43)!=18) anim_start_blended_pal(moby,18,0,0); }
        if (I(vars,0x2c8)) {
            I(moby,0x98)=0; H(moby,0x34)=(H(moby,0x34)|0x41)&0xefff;
            H(P(vars,0x25c),0x34)|=0x41; H(P(vars,0x25c),0x34)&=0xefff;
            I(P(vars,0x25c),0x98)=0; moby_set_state(moby,1,8);
        }
        B(vars,0x29)=1; B(vars,0x48)=FloatToInt(17.0f); B(vars,0x4a)=FloatToInt(12.0f);
    }
    if (B(moby,0x31) && fast_vec_dist(moby+0x10,g_camera_l13_position)<24.0f) { moby_update_ground_check(moby); B(moby,0x6f)=22; }
    if (P(vars,0x25c) && S(P(vars,0x25c),0xaa)==0xea9) {
        moby_transform_joint_point(moby,0,mat); copy_matrix3x4(P(vars,0x25c)+0xc0,mat); qcopy(P(vars,0x25c)+0x10,mat+0x30);
    }
    if (B(vars,0x2e)==2) {
        if (P(vars,0x25c) && S(P(vars,0x25c),0xaa)==0xea9) moby_mark_spawned(P(vars,0x25c));
        moby_mark_spawned(moby); return 1;
    }
    if (moby_apply_damage_to_object_pal(moby,vars+0x140,0)) guard_alt_alert_nearby((u8 *)moby);
    I(vars,0x280)=weapon_select_aim_target(moby,I(vars,0x27c),0.0f,0.0f,0,0);
    I(vars,0x2b8)=weapon_select_aim_target(moby,I(vars,0x2b4),0.0f,0.0f,0,0);
    I(vars,0x250)=weapon_select_aim_target(moby,I(vars,0x230),F(vars,0x238),0.0f,0,0);
    I(vars,0x254)=weapon_select_aim_target(moby,I(vars,0x234),F(vars,0x23c),0.0f,0,0);
    if (F(moby,0x18)<89.0f || (I(vars,0x2a8) && F(moby,0x18)<98.0f)) {
        if (P(vars,0x25c) && S(P(vars,0x25c),0xaa)==0xea9) moby_mark_spawned(P(vars,0x25c));
        I(vars,0x20)=0; SetDeathBits_pal(moby,0,3); return 1;
    }
    return 0;
}

