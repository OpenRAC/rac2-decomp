#include "common.h"
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern int D_L12_001A79F0[3] __attribute__((sda));
extern int D_L12_001A8FF0 __attribute__((sda));
extern char *D_L12_001B2B00[3] __attribute__((sda));
extern char D_L12_001B2B10[16] __attribute__((sda));
extern char D_L12_001B9E00[];
extern float D_L12_001B21C0 __attribute__((sda));
extern int FloatToInt(float);
extern float fast_vec_dist(void *, void *);
extern void coll_get_ground_distance_below(void *, void *, void *);
extern void moby_mark_spawned(void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object(void *, void *, int);
extern void hopping_enemy_alert_group(void *);
extern int weapon_select_aim_target(void *, int, int, int, float, float);
extern void cam_compute_view_direction(void *, void *, int);

struct L12Private277 {
    char pad0[0x28];
    unsigned char f28;
    char pad29[0x7];
    float f30;
    char pad34[0x14];
    unsigned char f48;
    char pad49[0x1];
    unsigned char f4A;
    char pad4B[0x15];
    unsigned char f60;
    char pad61[0x1F];
    float f80;
    float f84;
    char pad88[0x4];
    float f8C;
    float f90;
    char pad94[0x4];
    int f98;
    char pad9C[0x30];
    int fCC;
    char padD0[0x30];
    float f100;
    float f104;
    float f108;
    float f10C;
    float f110;
    char pad114[0x1C];
    float f130;
    float f134;
    int f138;
    int f13C;
    char pad140[0x90];
    float f1D0;
    float f1D4;
    char pad1D8[0x4];
    float f1DC;
    char pad1E0[0x2];
    short f1E2;
    short f1E4;
    char pad1E6[0x2];
    unsigned char f1E8;
    unsigned char f1E9;
    char pad1EA[0x46];
    int f230;
    int f234;
    int f238;
    char pad23C[0xF8];
    short f334;
    char pad336[0xE];
    float f344;
    float f348;
    char pad34C[0xC];
    short f358;
};

/* Sets up the hopping enemy on its first frame, then handles its hit reactions and its distance check to the hero. */
void hopping_enemy_init_react(char *obj) {
    struct L12Private277 *vars = *(struct L12Private277 **)(obj+0x68);
    int hit_result;

    if (!B(obj,0x20)) {
        if (D_L12_001A79F0[0] == 2 && F(obj,0x18) > 400.0f) {
            if (!D_L12_001A8FF0) return;
            coll_get_ground_distance_below(obj+0x10,obj,obj+0x10);
            vars->f358=1;
            W(obj,0x9C)=3;
            U(obj,0x34)|=0x100;
            vars->f90=fast_vec_dist(obj+0x10,D_L12_001B2B10)-1.5f;
        } else {
            W(obj,0x9C)=12;
            vars->f90=F(obj,0x18)-1.0f;
        }
        if (vars->f230==-1) { moby_mark_spawned(obj); return; }
        { char *v=D_L12_001B2B00[0]+vars->f230*0x30;
        if (H(v,0x30)) {
            vars->f238=W(P(v,0x3C),0);
            vars->f13C=vars->f238;
        } else vars->f238=-1; }
        vars->f344=math_random_float_range(1.0f,1.3329999446868896f);
        F(obj,0x2C)=F(P(obj,0x24),0x24)*vars->f344;
        vars->f48=FloatToInt(15.0f);
        vars->f4A=FloatToInt(6.4f);
        vars->f60=11; vars->f98=3;
        vars->f80=0.2f; vars->f84=0.2f; vars->f8C=0.4f;
        if(vars->f230!=-1) {
            char *v=D_L12_001B2B00[0]+(vars->f230*0x30+0x20);
            if(v && H(v,0x10)>0) vars->fCC=W(P(v,0x1C),0);
        }
        vars->f28=3;
        vars->f30=0.3330000042915344f;
        vars->f134=0.05f;
        vars->f104=vars->f344*0.2f;
        vars->f100=vars->f344*0.3f;
        vars->f10C=vars->f108=0.4f;
        vars->f110=1.5707964897155762f;
        vars->f130=0.523598849773407f;
        vars->f138|=0x280;
        { float angle=math_random_signed_float_range(18.0f,22.0f);
        vars->f1E8=7; vars->f1E9=6; vars->f1E2=120; vars->f1E4=180;
        vars->f1DC=angle*0.01745329424738884f;
        vars->f1D4=3.0f; vars->f1D0=D_L12_001B21C0*0.01666666753590107f; }
        vars->f348=math_random_angle();
        if(vars->f234) {
            W(obj,0x98)=0; U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
            moby_set_state(obj,13,4);
            if(B(obj,0x43)!=10) anim_start_blended(obj,10,0,0);
        } else {
            moby_set_state(obj,1,0);
            if(B(obj,0x43)) anim_start_blended(obj,0,0,0);
        }
        qcopy((char *)vars+0x300,obj+0x10);
    }
    if(B(obj,0x31) && fast_vec_dist(obj+0x10,D_L12_001B9E00)<24.0f) {
        moby_update_ground_check(obj); B(obj,0x6F)=22;
    }
    hit_result=moby_apply_damage_to_object(obj,(char *)vars+0x50,0);
    if(hit_result) {
        hopping_enemy_alert_group(obj);
        if(hit_result>=4) moby_set_state(obj,12,-1);
    }
    if((unsigned)(B(obj,0x95)-3)>=2)
        vars->f334=weapon_select_aim_target(obj,vars->f230,0,0,16.0f,0.0f);
    if(vars->f358) cam_compute_view_direction(obj+0x10,(char *)vars+0x320,0);
}
