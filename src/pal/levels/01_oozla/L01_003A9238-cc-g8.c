#include "names.h"
/* func_PAL_L01_003A9238, the PAL copy of func_L01_003A5BB8: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_002B0A18 becomes func_PAL_002B1588; rename func_002AC728 becomes func_PAL_002AD288; rename func_L01_003A6028 becomes func_PAL_L01_003A96A8; rename func_L00_00326110 becomes func_PAL_L00_003281C0. */
#include "common.h"

extern void FastVecAdd(char *, char *, char *);

/* func_L01_003B57A8 is defined in L01_003835D8.c. */

#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
extern void *D_L01_001FE180[];
extern float D_L01_001AF85C __attribute__((sda));
extern float D_L01_001AF860 __attribute__((sda));
extern int D_L01_001AF864 __attribute__((sda));
extern int g_current_map_index MACRO_ADDR;
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_L01_001A907C;
extern void moby_mark_spawned(void *);
extern float fast_vec_dist(void *,void *);
extern float math_fabs(float);
extern void path_sample_position(float,void *,int,void *,void *,int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern int part_find_owned_effect_slot(void *,int,int);
extern void matrix_mul_vec3(void *,void *,void *);
extern void snd_play_from_global_bank(int,int,int);
extern void func_PAL_002B1588(int,int);
extern int flag_set_first_pending(void *);
extern void func_PAL_002AD288(void *,void *,int,float,float);
extern void PlayMobySound(int,int,void *);
extern float FastAddRotations(float,float);
extern float coll_probe_ground_height_below(void *,int,float);
extern void moby_set_state(void *,int,int);
extern void func_PAL_L01_003A96A8(void *);
extern void func_PAL_L00_003281C0(void *,int,float);
extern int math_fast_float_d(void *);
void func_PAL_L01_003A9238(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *path = D_L01_001FE180[I(state,0x50)];
    float first, last, oldHeight;
    int mode, count;
    switch (object[0x20]) {
    case 0:
        if (I(state,0x50) == -1) { moby_mark_spawned(object); return; }
        D_L01_001AF864 = 0;
        first = fast_vec_dist(path + 0x10,path + 0x20);
        last = fast_vec_dist(path + 0x10,path + I(path,0)*16);
        F(state,0x74) = (D_L01_001AF85C * 0.020000001f) / first;
        I(state,0x70) = math_fabs(first-last) < 0.1f;
        F(state,0x5C) = F(state,0x58) * I(path,0);
        object[0x20] = 1;
        F(object,0x2C) *= D_L01_001AF860;
        object[0x30] = 255;
    case 1:
        oldHeight = F(object,0x18);
        path_sample_position(F(state,0x5C),path,I(state,0x70),object+0x10,object+0xF0,0);
        F(object,0xF4) *= 0.5f;
        F(object,0x18) += F(state,0x54);
        F(state,0x5C) += F(state,0x74);
        if (F(state,0x5C) > I(path,0)) F(state,0x5C) -= I(path,0);
        if (object[0x60] & 2) {
            if (oldHeight < F(object,0x18)) {
                if (object[0x43] != 0) func_PAL_002A7E68(object,0,0,10);
            } else if (object[0x43] != 1) func_PAL_002A7E68(object,1,0,10);
        }
        if (!part_find_owned_effect_slot(object,0x10000,0)) return;
        F(state,0x60) = D_L01_001AF85C * 0.010000001f;
        matrix_mul_vec3(state+0x60,state+0x60,object+0xC0);
        count = D_L01_001AF864 + 1;
        F(state,0x68) = -0.060000002f;
        if ((D_L01_001AF864 = count) > 3 && (mode = g_current_map_index) == 1 && !D_001A7A60[13]) {
            D_001A7A60[13] = 1;
            snd_play_from_global_bank(1,0,0);
            func_PAL_002B1588(0x1233,-1);
            D_L01_001A907C = mode;
        }
        moby_set_state(object,2,-1);
        break;
    case 2:
        if (flag_set_first_pending(object)) {
            func_PAL_002AD288(object,object+0x10,-1,0.5f,13.0f);
            PlayMobySound(0,0,object);
        }
        F(object,0x48) = 0.5f;
        FastVecAdd(object+0x10,object+0x10,state+0x60);
        F(state,0x68) -= 0.0043200003f;
        F(state,0x60) *= 0.976f;
        F(state,0x64) *= 0.976f;
        F(object,0xF0) = FastAddRotations(-3.1415927f,(F(object,0xF0)+3.1415927f)*0.94f);
        if (math_fabs(coll_probe_ground_height_below(object+0x10,0,0.5f)-F(object,0x18)) < 0.5f) {
            I(state,0x78) = 25;
            moby_set_state(object,3,-1);
        }
        break;
    case 3:
        if (flag_set_first_pending(object)) {
            func_PAL_L01_003A96A8(object);
            PlayMobySound(1,0,object);
            func_PAL_L00_003281C0(object,1,0.0f);
        }
        F(object,0x18) += F(state,0x68);
        if (math_fast_float_d(state+0x78)) moby_mark_spawned(object);
        return;
    default:
        return;
    }
}

typedef struct { u8 pad[0x2290]; u8 *target; } OozlaHero;
extern OozlaHero g_hero_state;
extern int D_L01_001B2088 MACRO_ADDR;
