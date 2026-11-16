#include "names.h"
/* func_PAL_L22_004123B0, the PAL copy of func_L22_0040D638: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_002B0ED8 becomes func_PAL_002B1A50; scale D_L22_001B119C. */
#include "common.h"
typedef union { unsigned int q __attribute__((mode(TI))); float f[4]; } Vec;
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int math_random_int_below(int);
extern void cam_compute_view_direction(void *,void *,int);
#define U8(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define U16(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define S16(p,o) (*(short *)((char *)(p)+(o)))
#define I32(p,o) (*(int *)((char *)(p)+(o)))
#define FL(p,o) (*(float *)((char *)(p)+(o)))
#define PTR(p,o) (*(char **)((char *)(p)+(o)))
extern void moby_set_controller_speed_limits(void *,float,float,float,float);
extern void moby_set_state(void *,int,int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern int coll_test_point(void *,int,int,float);
extern int lane_pick_random_point_away_from_ship(void *,int,float);
extern void arena_push_point_out(void *,float);
extern float fast_vec_dist(void *,void *);
extern int func_PAL_002B1A50(void *,void *,int);
extern void vec_negate_and_forward(void *,void *,int);
extern char *g_space_ship_owner_moby;
extern short g_space_ship_mode;
extern int g_flying_enemy_spawn_count, g_flying_enemy_spawn_blocked;
extern char g_flying_enemy_target_point[], g_flying_enemy_home_point[];
extern float g_enemy_random_scale;
extern int g_flyer_default_state __attribute__((sda));
extern char *g_collision_l22_hit __attribute__((section(".data")));
void func_PAL_L22_004123B0(char *obj) {
    Vec offset;
    int state = U8(obj,0x20);
    char *ctx = PTR(obj,0x68);
    if (state == 0) {
        U16(obj,0x32)=80; U8(obj,0x30)=255; U16(obj,0x34)|=0x100;
        U8(ctx,0x150)=5; I32(ctx,0x188)=3;
        FL(ctx,0x17c)=0.15f; FL(ctx,0x170)=0.5f; FL(ctx,0x174)=0.5f;
        if (S16(ctx,0x24)==0) { S16(ctx,0x24)=1; FL(ctx,0x20)=1.0f; }
        I32(ctx,0x88)|=5;
        FL(ctx,0x84)=0.5f; FL(ctx,0x54)=-7.0f; FL(ctx,0x50)=7.0f;
        FL(ctx,0x58)=0.4f; FL(ctx,0x5c)=0.4f;
        FL(ctx,0x60)=1.5707964897155762f;
        FL(ctx,0x80)=1.5533431768417358f;
        moby_set_controller_speed_limits(obj,0.0096f,0.24000001f,0.0025132746f,0.25132746f);
        I32(ctx,0x288)=0; I32(ctx,0x28c)=1; I32(obj,0x98)=0;
        U16(obj,0x34)=(U16(obj,0x34)|0x41)&0xefff;
        moby_set_state(obj,1,4);
    } else if (state == 1) {
        if (!g_space_ship_owner_moby) goto finish;
        moby_set_state(obj,6,4);
        if (math_random_int_below(2)) {
            S16(ctx,0x178)=0;
            U16(obj,0x34)=(U16(obj,0x34)&0xffbe)|0x1000;
            I32(obj,0x98)=I32(PTR(obj,0x24),0x10);
            lane_pick_random_point_away_from_ship(obj+0x10,1,7.2f);
            if (coll_test_point(obj+0x10,1,0,3.0f) && S16(g_collision_l22_hit,0xaa)==0xedd && U8(g_collision_l22_hit,0x20)!=6) {
                char *axis=obj+0xc0+16*math_random_int_below(2);
                float scale;
                if (math_random_int_below(2)) scale=g_enemy_random_scale;
                else scale=-g_enemy_random_scale;
                FastVecScale(&offset,axis,scale);
                FastVecAdd(obj+0x10,obj+0x10,&offset);
                arena_push_point_out(obj+0x10,7.2f);
            }
            qcopy(ctx+0x2a0,obj+0x10);
            I32(ctx,0x284)=0;
            moby_set_state(obj,2,0);
            if (U8(obj,0x43)!=1) func_PAL_002A7E68(obj,1,0,0);
        } else I32(ctx,0x284)=state;
    } else if (g_space_ship_mode==2) {
        if ((U16(g_space_ship_owner_moby,0x34)^1)&1) {
            float distance;
            if (state == 6) goto respawn;
            {
                distance=fast_vec_dist(g_flying_enemy_target_point,obj+0x10);
                if (U8(obj,0x20)!=6 && distance<55.0f) I32(ctx,0x288)=g_space_ship_mode;
            }
            if (U8(obj,0x20)==6 || distance>55.0f) {
respawn:
                if (g_flying_enemy_spawn_count<16 && !g_flying_enemy_spawn_blocked) {
                    g_flying_enemy_spawn_count++;
                    S16(ctx,0x178)=0;
                    U16(obj,0x34)=(U16(obj,0x34)&0xffbe)|0x1000;
                    I32(obj,0x98)=I32(PTR(obj,0x24),0x10);
                    qcopy(obj+0x10,g_flying_enemy_home_point);
                    moby_set_state(obj,8,5);
                    g_flying_enemy_spawn_blocked=(((int)(g_flyer_default_state) * 5 + 2) / 6);
                    I32(ctx,0x288)=g_space_ship_mode;
                }
            }
        }
    }
finish:
    if (U8(obj,0x20)!=6) {
        FL(obj,0x2c)=FL(PTR(obj,0x24),0x24)*0.4f;
        func_PAL_002B1A50(obj,ctx+0x140,0);
        cam_compute_view_direction(obj+0x10,ctx+0x290,0);
        vec_negate_and_forward(obj+0xc0,ctx+0x290,0);
    }
}
