/* func_US2_L08_003CDBA0, the USA v2.00 copy of func_L08_003CC750: the same C, where rename func_002B0A18 becomes func_US2_002B1880. */
#include "common.h"
#define F(p,T,o) (*(T *)((char *)(p)+(o)))
typedef struct { char pad[0x2294]; int mode; int unused; int action; } Globals;
extern Globals g_hero_state;
typedef struct { char pad0[0x24]; char *descriptor; char pad1[4]; float scale; } ObjectView;
extern char g_hero_position[], D_0019B2E8[], D_0019B4A8[];
extern u8 D_L08_001B2840[] MACRO_ADDR;
extern struct { char pad[0x464]; u8 flags[0]; } D_L08_0021DE80, D_L08_0021EAF0;
extern int g_current_map_index;
extern u16 D_001A7A1A;
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_L08_001A903C __attribute__((sda));
extern float D_L08_001AFED0 __attribute__((sda)), D_L08_001AFED4 __attribute__((sda)), D_L08_001AFED8 __attribute__((sda));
extern float D_L08_001AFEDC __attribute__((sda)), D_L08_001AFEE4 __attribute__((sda)), D_L08_001AFEE8 __attribute__((sda));
extern void moby_set_state(void *,int,int), anim_start_blended(void *,int,int,int);
extern void gfx_draw_glowing_spark_rings(void *);
extern float vec_distance_xy(void *,void *), vec_length_xy(void *);
extern void FastVecSub(void *,void *,void *), vec_fast_divide_helper(void *,void *,float), FastVecAdd(void *,void *,void *);
extern int snd_play_from_class_bank(int,int,void *,int);
extern int snd_play_from_global_bank(int, int, void *);
extern void moby_mark_spawned(void *), func_US2_002B1880(int, int);
extern int level_get_saved_count(void);
void func_US2_L08_003CDBA0(char *object) {
    char *state;
    float vector[4] __attribute__((aligned(16)));
    float distance, speed, threshold;
    F(object,u16,0x96)++;
    state = F(object,char *,0x68);
    switch (F(object,u8,0x20)) {
    case 0:
        F(object,u8,0x23) = 0x50;
        F(object,u16,0x34) |= 0x800;
        moby_set_state(object,1,-1);
        if (F(object,u8,0x43)) anim_start_blended(object,0,0,0);
        break;
    case 1:
        if (vec_distance_xy(object+0x10,g_hero_position) < D_L08_001AFED0) {
            F(state,float,0) = D_L08_001AFEE4;
            if (F(object,u8,0x43) != 1) anim_start_blended(object,1,0,0x14);
            F(object,float,0x48) = F(state,float,0) + F(state,float,0);
            moby_set_state(object,2,-1);
        }
        if (F(object,u8,0x31)) gfx_draw_glowing_spark_rings(object);
        break;
    case 2:
        F(state,float,0) += (1.0f - F(state,float,0)) * D_L08_001AFEDC;
        F(object,float,0x48) = F(state,float,0) + F(state,float,0);
        FastVecSub(vector,g_hero_position,object+0x10);
        vector[2] += 0.6f;
        distance = vec_length_xy(vector);
        threshold = 0.12f;
        if (F(object,u16,0x96) < 180) {
            if (F(g_hero_position,int,0x2214) != 0x31)
                speed = D_L08_001AFED4 * (F(state,float,0) * 0.016666668f);
            else {
                speed = D_L08_001AFED8 * (F(state,float,0) * 0.016666668f);
                threshold = 0.8f;
            }
        } else speed = F(state,float,0) + F(state,float,0);
        vec_fast_divide_helper(vector,vector,speed);
        FastVecAdd(object+0x10,object+0x10,vector);
        if (((ObjectView *)object)->scale > 0.1f || distance < threshold || distance < speed)
            ((ObjectView *)object)->scale -= D_L08_001AFEE8 * F(((ObjectView *)object)->descriptor,float,0x24);
        if ((distance < speed && ((ObjectView *)object)->scale < F(((ObjectView *)object)->descriptor,float,0x24)*0.01f) ||
            g_hero_state.action == 0x14 || g_hero_state.action == 0x19 ||
            g_hero_state.mode == 0x39 || g_hero_state.mode == 0x6F) {
            snd_play_from_class_bank(3,0,object,0x96A);
            D_001A7A1A++;
            if (F(state,char *,4)) {
                D_L08_0021DE80.flags[F(F(state,char *,4),short,0xB2)] = F(F(state,char *,4),u8,0xB0)+2;
                if (F(F(state,char *,4),u8,0xB0) == 0xFF ||
                    (!(D_L08_001B2840[F(F(state,char *,4),u8,0xB0)] & 0x80) &&
                     (F(D_0019B2E8,u8,F(F(state,char *,4),u8,0xB0)+(g_current_map_index<<4)) & 0x80)))
                    D_L08_0021EAF0.flags[F(F(state,char *,4),short,0xB2)] = F(F(state,char *,4),u8,0xB0)+2;
                {
                    u16 index = F(F(state,char *,4),u16,0xB2);
                    if (index & 1) {
                        u8 *bits = (u8 *)D_0019B4A8 + (((short)index >> 1) + (g_current_map_index << 10));
                        if (((*bits >> 4) & 7) != 7) *bits += 0x10;
                    } else {
                        u8 *bits = (u8 *)D_0019B4A8 + (((short)index >> 1) + (g_current_map_index << 10));
                        if ((*bits & 7) != 7) ++*bits;
                    }
                }
            }
            moby_mark_spawned(object);
            if (!level_get_saved_count() && !D_001A7A60[5]) {
                D_001A7A60[5] = 1;
                snd_play_from_global_bank(1,0,0);
                func_US2_002B1880(0x1233,-1);
                D_L08_001A903C = 1;
            }
        } else gfx_draw_glowing_spark_rings(object);
        break;
    }
}
