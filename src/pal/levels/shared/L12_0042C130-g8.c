#include "include_asm.h"

#include "common.h"
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern int g_robot_kill_counter[3] __attribute__((sda));
extern int g_hero_l12_lock_flag __attribute__((sda));
extern char *g_hopping_enemy_vertex_table[3] __attribute__((sda));
extern char g_hopping_enemy_target_pos[16] __attribute__((sda));
extern char g_hero_prev_position[];
extern float g_hopping_enemy_hop_rate __attribute__((sda));
extern int FloatToInt(float);
extern float fast_vec_dist(void *, void *);
extern float coll_get_ground_distance_below(void *, void *, void *);
extern void moby_mark_spawned(void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern void moby_set_state(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void moby_update_ground_check(void *);
extern int func_PAL_002B1A50(void *, void *, int);
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

void func_PAL_L12_0042CD98(char *obj) {
    struct L12Private277 *s = *(struct L12Private277 **)(obj+0x68);
    int result;

    if (!B(obj,0x20)) {
        if (g_robot_kill_counter[0] == 2 && F(obj,0x18) > 400.0f) {
            if (!g_hero_l12_lock_flag) return;
            coll_get_ground_distance_below(obj+0x10,obj,obj+0x10);
            s->f358=1;
            W(obj,0x9C)=3;
            U(obj,0x34)|=0x100;
            s->f90=fast_vec_dist(obj+0x10,g_hopping_enemy_target_pos)-1.5f;
        } else {
            W(obj,0x9C)=12;
            s->f90=F(obj,0x18)-1.0f;
        }
        if (s->f230==-1) { moby_mark_spawned(obj); return; }
        { char *v=g_hopping_enemy_vertex_table[0]+s->f230*0x30;
        if (H(v,0x30)) {
            s->f238=W(P(v,0x3C),0);
            s->f13C=s->f238;
        } else s->f238=-1; }
        s->f344=math_random_float_range(1.0f,1.3329999446868896f);
        F(obj,0x2C)=F(P(obj,0x24),0x24)*s->f344;
        s->f48=FloatToInt(15.0f);
        s->f4A=FloatToInt(6.4f);
        s->f60=11; s->f98=3;
        s->f80=0.2f; s->f84=0.2f; s->f8C=0.4f;
        if(s->f230!=-1) {
            char *v=g_hopping_enemy_vertex_table[0]+(s->f230*0x30+0x20);
            if(v && H(v,0x10)>0) s->fCC=W(P(v,0x1C),0);
        }
        s->f28=3;
        s->f30=0.3330000042915344f;
        s->f134=0.05f;
        s->f104=s->f344*0.2f;
        s->f100=s->f344*0.3f;
        s->f10C=s->f108=0.4f;
        s->f110=1.5707964897155762f;
        s->f130=0.523598849773407f;
        s->f138|=0x280;
        { float angle=math_random_signed_float_range(18.0f,22.0f);
        s->f1E8=7; s->f1E9=6; s->f1E2=100; s->f1E4=150;
        s->f1DC=angle*0.01745329424738884f;
        s->f1D4=3.0f; s->f1D0=g_hopping_enemy_hop_rate*0.020000001f; }
        s->f348=math_random_angle();
        if(s->f234) {
            W(obj,0x98)=0; U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
            moby_set_state(obj,13,4);
            if(B(obj,0x43)!=10) func_PAL_002A7E68(obj,10,0,0);
        } else {
            moby_set_state(obj,1,0);
            if(B(obj,0x43)) func_PAL_002A7E68(obj,0,0,0);
        }
        qcopy((char *)s+0x300,obj+0x10);
    }
    if(B(obj,0x31) && fast_vec_dist(obj+0x10,g_hero_prev_position)<24.0f) {
        moby_update_ground_check(obj); B(obj,0x6F)=22;
    }
    result=func_PAL_002B1A50(obj,(char *)s+0x50,0);
    if(result) {
        hopping_enemy_alert_group(obj);
        if(result>=4) moby_set_state(obj,12,-1);
    }
    if((unsigned)(B(obj,0x95)-3)>=2)
        s->f334=weapon_select_aim_target(obj,s->f230,0,0,16.0f,0.0f);
    if(s->f358) cam_compute_view_direction(obj+0x10,(char *)s+0x320,0);
}
