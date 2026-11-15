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
extern void moby_mark_spawned(void *), value_set_entry_by_index(int, int);
extern int level_get_saved_count(void);
/* Collectible that waits until the hero is close, then flies to the hero, shrinks, and is collected with a sound and a saved flag. */
void orb_update(char *moby) {
    char *vars;
    float to_hero[4] __attribute__((aligned(16)));
    float hero_distance, fly_speed, arrive_distance;
    F(moby,u16,0x96)++;
    vars = F(moby,char *,0x68);
    switch (F(moby,u8,0x20)) {
    case 0:
        F(moby,u8,0x23) = 0x50;
        F(moby,u16,0x34) |= 0x800;
        moby_set_state(moby,1,-1);
        if (F(moby,u8,0x43)) anim_start_blended(moby,0,0,0);
        break;
    case 1:
        if (vec_distance_xy(moby+0x10,g_hero_position) < D_L08_001AFED0) {
            F(vars,float,0) = D_L08_001AFEE4;
            if (F(moby,u8,0x43) != 1) anim_start_blended(moby,1,0,0x14);
            F(moby,float,0x48) = F(vars,float,0) + F(vars,float,0);
            moby_set_state(moby,2,-1);
        }
        if (F(moby,u8,0x31)) gfx_draw_glowing_spark_rings(moby);
        break;
    case 2:
        F(vars,float,0) += (1.0f - F(vars,float,0)) * D_L08_001AFEDC;
        F(moby,float,0x48) = F(vars,float,0) + F(vars,float,0);
        FastVecSub(to_hero,g_hero_position,moby+0x10);
        to_hero[2] += 0.6f;
        hero_distance = vec_length_xy(to_hero);
        arrive_distance = 0.12f;
        if (F(moby,u16,0x96) < 180) {
            if (F(g_hero_position,int,0x2214) != 0x31)
                fly_speed = D_L08_001AFED4 * (F(vars,float,0) * 0.016666668f);
            else {
                fly_speed = D_L08_001AFED8 * (F(vars,float,0) * 0.016666668f);
                arrive_distance = 0.8f;
            }
        } else fly_speed = F(vars,float,0) + F(vars,float,0);
        vec_fast_divide_helper(to_hero,to_hero,fly_speed);
        FastVecAdd(moby+0x10,moby+0x10,to_hero);
        if (((ObjectView *)moby)->scale > 0.1f || hero_distance < arrive_distance || hero_distance < fly_speed)
            ((ObjectView *)moby)->scale -= D_L08_001AFEE8 * F(((ObjectView *)moby)->descriptor,float,0x24);
        if ((hero_distance < fly_speed && ((ObjectView *)moby)->scale < F(((ObjectView *)moby)->descriptor,float,0x24)*0.01f) ||
            g_hero_state.action == 0x14 || g_hero_state.action == 0x19 ||
            g_hero_state.mode == 0x39 || g_hero_state.mode == 0x6F) {
            snd_play_from_class_bank(3,0,moby,0x96A);
            D_001A7A1A++;
            if (F(vars,char *,4)) {
                D_L08_0021DE80.flags[F(F(vars,char *,4),short,0xB2)] = F(F(vars,char *,4),u8,0xB0)+2;
                if (F(F(vars,char *,4),u8,0xB0) == 0xFF ||
                    (!(D_L08_001B2840[F(F(vars,char *,4),u8,0xB0)] & 0x80) &&
                     (F(D_0019B2E8,u8,F(F(vars,char *,4),u8,0xB0)+(g_current_map_index<<4)) & 0x80)))
                    D_L08_0021EAF0.flags[F(F(vars,char *,4),short,0xB2)] = F(F(vars,char *,4),u8,0xB0)+2;
                {
                    u16 flag_index = F(F(vars,char *,4),u16,0xB2);
                    if (flag_index & 1) {
                        u8 *flag_bits = (u8 *)D_0019B4A8 + (((short)flag_index >> 1) + (g_current_map_index << 10));
                        if (((*flag_bits >> 4) & 7) != 7) *flag_bits += 0x10;
                    } else {
                        u8 *flag_bits = (u8 *)D_0019B4A8 + (((short)flag_index >> 1) + (g_current_map_index << 10));
                        if ((*flag_bits & 7) != 7) ++*flag_bits;
                    }
                }
            }
            moby_mark_spawned(moby);
            if (!level_get_saved_count() && !D_001A7A60[5]) {
                D_001A7A60[5] = 1;
                snd_play_from_global_bank(1,0,0);
                value_set_entry_by_index(0x1233,-1);
                D_L08_001A903C = 1;
            }
        } else gfx_draw_glowing_spark_rings(moby);
        break;
    }
}
