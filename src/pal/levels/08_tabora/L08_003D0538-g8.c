#include "names.h"
/* func_PAL_L08_003D0538, the PAL copy of func_L08_003CC750: the same C, where 1/60 becomes 0.02, the 180-tick
   limit becomes 150, and the fall-through speed and the shrink rate gain their 6/5 scale. */
#include "common.h"
#define F(p,T,o) (*(T *)((char *)(p)+(o)))
typedef struct { char pad[0x2294]; int mode; int unused; int action; } Globals;
extern Globals g_hero_state;
typedef struct { char pad0[0x24]; char *descriptor; char pad1[4]; float scale; } ObjectView;
extern char g_hero_position[], g_moby_group_flags[], g_moby_nibble_table[];
extern u8 g_moby_state_flags[] MACRO_ADDR;
extern struct { char pad[0x464]; u8 flags[0]; } g_moby_spawn_state_flags_a, g_moby_spawn_state_flags_b;
extern int g_current_map_index;
extern u16 g_orb_counter;
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern int g_orb_update_flag __attribute__((sda));
extern float g_orb_pickup_distance __attribute__((sda)), g_orb_fly_speed_near __attribute__((sda)), g_orb_fly_speed_far __attribute__((sda));
extern float g_orb_ease_rate __attribute__((sda)), g_orb_reset_value __attribute__((sda)), g_orb_shrink_rate __attribute__((sda));
extern void moby_set_state(void *,int,int), anim_start_blended_pal(void *,int,int,int);
extern void gfx_draw_glowing_spark_rings_pal(void *);
extern float vec_distance_xy(void *,void *), vec_length_xy(void *);
extern void FastVecSub(void *,void *,void *), vec_fast_divide_helper(void *,void *,float), FastVecAdd(void *,void *,void *);
extern int snd_play_from_class_bank(int,int,void *,int);
extern int snd_play_from_global_bank(int, int, void *);
extern void moby_mark_spawned(void *), value_set_entry_by_index_pal(int, int);
extern int level_get_saved_count(void);
/* Collectible that waits until the hero is close, then flies to the hero, shrinks, and is collected with a sound and a saved flag (PAL: 50 Hz timings). */
void orb_update_pal(char *object) {
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
        if (F(object,u8,0x43)) anim_start_blended_pal(object,0,0,0);
        break;
    case 1:
        if (vec_distance_xy(object+0x10,g_hero_position) < g_orb_pickup_distance) {
            F(state,float,0) = g_orb_reset_value;
            if (F(object,u8,0x43) != 1) anim_start_blended_pal(object,1,0,0x14);
            F(object,float,0x48) = F(state,float,0) + F(state,float,0);
            moby_set_state(object,2,-1);
        }
        if (F(object,u8,0x31)) gfx_draw_glowing_spark_rings_pal(object);
        break;
    case 2:
        F(state,float,0) += (1.0f - F(state,float,0)) * g_orb_ease_rate;
        F(object,float,0x48) = F(state,float,0) + F(state,float,0);
        FastVecSub(vector,g_hero_position,object+0x10);
        vector[2] += 0.6f;
        distance = vec_length_xy(vector);
        threshold = 0.12f;
        if (F(object,u16,0x96) < 150) {
            if (F(g_hero_position,int,0x2214) != 0x31)
                speed = g_orb_fly_speed_near * (F(state,float,0) * 0.020000001f);
            else {
                speed = g_orb_fly_speed_far * (F(state,float,0) * 0.020000001f);
                threshold = 0.8f;
            }
        } else speed = F(state,float,0) * 2.4f;
        vec_fast_divide_helper(vector,vector,speed);
        FastVecAdd(object+0x10,object+0x10,vector);
        if (((ObjectView *)object)->scale > 0.1f || distance < threshold || distance < speed)
            ((ObjectView *)object)->scale -= g_orb_shrink_rate * (F(((ObjectView *)object)->descriptor,float,0x24) * 1.2f);
        if ((distance < speed && ((ObjectView *)object)->scale < F(((ObjectView *)object)->descriptor,float,0x24)*0.01f) ||
            g_hero_state.action == 0x14 || g_hero_state.action == 0x19 ||
            g_hero_state.mode == 0x39 || g_hero_state.mode == 0x6F) {
            snd_play_from_class_bank(3,0,object,0x96A);
            g_orb_counter++;
            if (F(state,char *,4)) {
                g_moby_spawn_state_flags_a.flags[F(F(state,char *,4),short,0xB2)] = F(F(state,char *,4),u8,0xB0)+2;
                if (F(F(state,char *,4),u8,0xB0) == 0xFF ||
                    (!(g_moby_state_flags[F(F(state,char *,4),u8,0xB0)] & 0x80) &&
                     (F(g_moby_group_flags,u8,F(F(state,char *,4),u8,0xB0)+(g_current_map_index<<4)) & 0x80)))
                    g_moby_spawn_state_flags_b.flags[F(F(state,char *,4),short,0xB2)] = F(F(state,char *,4),u8,0xB0)+2;
                {
                    u16 index = F(F(state,char *,4),u16,0xB2);
                    if (index & 1) {
                        u8 *bits = (u8 *)g_moby_nibble_table + (((short)index >> 1) + (g_current_map_index << 10));
                        if (((*bits >> 4) & 7) != 7) *bits += 0x10;
                    } else {
                        u8 *bits = (u8 *)g_moby_nibble_table + (((short)index >> 1) + (g_current_map_index << 10));
                        if ((*bits & 7) != 7) ++*bits;
                    }
                }
            }
            moby_mark_spawned(object);
            if (!level_get_saved_count() && !g_item_enabled_flags[5]) {
                g_item_enabled_flags[5] = 1;
                snd_play_from_global_bank(1,0,0);
                value_set_entry_by_index_pal(0x1233,-1);
                g_orb_update_flag = 1;
            }
        } else gfx_draw_glowing_spark_rings_pal(object);
        break;
    }
}
