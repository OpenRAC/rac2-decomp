#include "names.h"
/* func_US2_L01_00398790, the USA v2.00 copy of func_L01_003973A0: the same C, where rename func_002B0A18 becomes func_US2_002B1880. */
#include "common.h"
extern int g_current_map_index MACRO_ADDR;
extern short D_0018A16E NOT_SDA;
extern unsigned char D_0019B278[];
extern char g_hero_state[];
extern int D_L01_001B22A8;
extern float D_L01_001AF50C __attribute__((sda));
extern float D_L01_001AF510 __attribute__((sda));
extern float D_L01_001AF514 __attribute__((sda));
extern float D_L01_001AF51C __attribute__((sda));
extern float D_L01_001AF528 __attribute__((sda));
extern float D_L01_001AF520 __attribute__((sda));
extern float D_L01_001AF524 __attribute__((sda));
extern int D_L01_001AF54C __attribute__((sda));
extern int D_L01_001AF550 __attribute__((sda));
extern int D_L01_001B21B0 __attribute__((sda));
extern int D_L01_001B1FA8 __attribute__((sda));
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float,float);
extern float vec_distance_xy(void*,void*);
extern float math_fabs(float);
extern int math_random_int_below(int);
extern void moby_init_randomized_vars(void*),part_draw_bolt_glow_rings(void*),part_spawn_sparkle_trail_above_ground(void*),teleporter_start_arrival(void*),cam_blend_moby_update(void*),bobbing_l01_moby_update(void*);
extern void func_US2_002B1880(int,int), moby_mark_spawned(void*), moby_set_state(void*,int,int), anim_start_blended(void*,int,int,int);
extern int PlayMobySound(int,int,void*);
extern int MemcardSave(int,int);
extern void set_hero_animation(int,int,float),hero_reset_position_and_direction(void*,void*,int,int),cam_set_mode_state(int);
extern int math_fast_float_d(void*);

void func_US2_L01_00398790(unsigned char *m)
{
    char *p = *(char **)(m+0x68);
    int i;
    switch ((unsigned char)m[0x20]) {
    case 0:
        if (*(int *)p == -1 || D_0019B278[*(int *)p + (g_current_map_index << 2)]) goto remove;
        {
            qcopy_nc(p+0x10,m+0x10);
            *(float *)(p+0x1C)=*(float *)(m+0xF8);
            *(float *)(m+0xF0)=math_random_angle();
            *(float *)(m+0xF4)=math_random_angle();
            *(float *)(m+0xF8)=math_random_angle();
            ((float *)m)[0xFC/4]=math_random_angle();
            ((float *)p)[0x68/4]=D_L01_001AF51C*0.0002908882452175021f;
            ((float *)p)[0x64/4]=D_L01_001AF520*0.0002908882452175021f;
            ((float *)p)[0x60/4]=D_L01_001AF524*0.0002908882452175021f;
            if (*(short *)(m+0x32)<64) *(short *)(m+0x32)=64;
            m[0x20]=1;
            moby_init_randomized_vars(m);
        }
        break;
    case 1: {
        char *player;
        *(float *)(m+0x2C)=*(float *)(*(char **)(m+0x24)+0x24)*D_L01_001AF50C;
        {
            float phase = math_fast_sin_or_cos_b(*(float *)(m+0xFC));
            float height = *(float *)(p+0x18)+D_L01_001AF510+D_L01_001AF514*phase;
            float step = D_L01_001AF51C*0.0002908882452175021f;
            float angle;
            *(float *)(m+0x18)=height;
            angle=FastAddRotations(*(float *)(m+0xF0),step);
            step=D_L01_001AF520*0.0002908882452175021f;
            *(float *)(m+0xF0)=angle;
            angle=FastAddRotations(*(float *)(m+0xF4),step);
            step=D_L01_001AF524*0.0002908882452175021f;
            *(float *)(m+0xF4)=angle;
            angle=FastAddRotations(*(float *)(m+0xF8),step);
            step=D_L01_001AF528*0.0002908882452175021f;
            *(float *)(m+0xF8)=angle;
            *(float *)(m+0xFC)=FastAddRotations(*(float *)(m+0xFC),step);
        }
        part_draw_bolt_glow_rings(m);
        if (!math_random_int_below(D_L01_001AF54C)) part_spawn_sparkle_trail_above_ground(m);
        player=g_hero_state+0x80;
        if (!(vec_distance_xy(m+0x10,player)<3.0f)) break;
        player -= 0x80;
        if (math_fabs(*(float *)(m+0x18)-*(float *)(player+0x88))<2.0f &&
            *(int *)(player+0x24CC) &&
            ((unsigned char)player[0x22B4]==3 || !player[0x22B4])) {
            if (!*(short *)(p+0xC) && *(int *)(player+0x2294)!=0x31) goto inactive;
            D_L01_001B21B0=180;
            func_US2_002B1880(0x124B,-1);
            D_0019B278[*(int *)p+(g_current_map_index<<2)]=1;
            D_L01_001AF550++;
            MemcardSave(0,-1);
            PlayMobySound(1,0,m);
        remove:
            moby_mark_spawned(m);
        }
        break;
    }
    inactive:
        if (*(int *)(p+0x78)) {
            *(unsigned short *)(m+0x34) |= 0x41;
            moby_set_state(m,3,-1);
            break;
        }
        goto initialize;
    case 3:
        if (D_0018A16E) break;
    initialize:
        teleporter_start_arrival(m);
        break;
    case 2: {
        {
            char *player = g_hero_state;
            D_L01_001B22A8=1;
            *(short *)(player+0x1DC)=3;
            cam_blend_moby_update(m);
            qcopy_nc(m+0x10,player+0x80);
            player += 0x90;
            qcopy_nc(m+0xF0,player);
        }
        if ((unsigned char)m[0x42]==1) {
            bobbing_l01_moby_update(m);
            if (!math_random_int_below(10)) part_spawn_sparkle_trail_above_ground(m);
            if (m[0x60]&2) {
                if (m[0x43]) anim_start_blended(m,0,0,0);
                *(unsigned short *)(m+0x34)|=1;
                m[0x31]=0;
                for (i=3;i>=0;i--) part_spawn_sparkle_trail_above_ground(m);
            }
        }
        {
        char *player = g_hero_state;
        if (*(int *)(player+0xC28)&2) set_hero_animation(0,0,30.0f);
        if (!m[0x42] && math_fast_float_d(p+0x6C)) {
            D_L01_001B21B0=180;
            func_US2_002B1880(0x124B,-1);
            D_0019B278[*(int *)p+(g_current_map_index<<2)]=1;
            D_L01_001AF550++;
            D_L01_001B1FA8=0;
            hero_reset_position_and_direction(player+0x80,player+0x90,0,0);
            cam_set_mode_state(0);
            MemcardSave(0,-1);
            moby_mark_spawned(m);
        }
        }
        break;
    }
    }
}
