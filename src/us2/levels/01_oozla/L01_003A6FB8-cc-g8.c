#include "names.h"
/* func_US2_L01_003A6FB8, the USA v2.00 copy of func_L01_003A5BB8: the same C, where rename func_002B0A18 becomes func_US2_002B1880. */
#include "common.h"

extern void FastVecAdd(char *, char *, char *);

/* func_L01_003B57A8 is defined in L01_003835D8.c. */

#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
extern void *g_path_l01_table[];
extern float g_flying_target_speed_scale __attribute__((sda));
extern float g_flying_target_damping __attribute__((sda));
extern int g_flying_target_tick_count __attribute__((sda));
extern int g_current_map_index MACRO_ADDR;
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern int g_flying_path_mode;
extern void moby_mark_spawned(void *);
extern float fast_vec_dist(void *,void *);
extern float math_fabs(float);
extern void path_sample_position(float,void *,int,void *,void *,int);
extern void anim_start_blended(void *,int,int,int);
extern void *part_find_owned_effect_slot(void *,int,int);
extern void matrix_mul_vec3(void *,void *,void *);
extern int snd_play_from_global_bank(int,int,int);
extern void value_set_entry_by_index_us2(int,int);
extern int flag_set_first_pending(void *);
extern void part_spawn_explosion_with_sparks(void *,void *,int,float,float);
extern int PlayMobySound(int,int,void *);
extern float FastAddRotations(float,float);
extern float coll_probe_ground_height_below(void *,int,float);
extern void moby_set_state(void *,int,int);
extern void OozlaSpawnSplashParticles(void *);
extern void part_spawn_scaled_bolts(void *,int,float);
extern int math_fast_float_d(void *);
/* Flies a target along its path. When it is shot it falls into the water, makes a splash and disappears. */
void path_flying_target_update_us2(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *path = g_path_l01_table[I(state,0x50)];
    float first, last, old_height;
    int mode, count;
    switch (object[0x20]) {
    case 0:
        if (I(state,0x50) == -1) { moby_mark_spawned(object); return; }
        g_flying_target_tick_count = 0;
        first = fast_vec_dist(path + 0x10,path + 0x20);
        last = fast_vec_dist(path + 0x10,path + I(path,0)*16);
        F(state,0x74) = (g_flying_target_speed_scale * 0.016666668f) / first;
        I(state,0x70) = math_fabs(first-last) < 0.1f;
        F(state,0x5C) = F(state,0x58) * I(path,0);
        object[0x20] = 1;
        F(object,0x2C) *= g_flying_target_damping;
        object[0x30] = 255;
    case 1:
        old_height = F(object,0x18);
        path_sample_position(F(state,0x5C),path,I(state,0x70),object+0x10,object+0xF0,0);
        F(object,0xF4) *= 0.5f;
        F(object,0x18) += F(state,0x54);
        F(state,0x5C) += F(state,0x74);
        if (F(state,0x5C) > I(path,0)) F(state,0x5C) -= I(path,0);
        if (object[0x60] & 2) {
            if (old_height < F(object,0x18)) {
                if (object[0x43] != 0) anim_start_blended(object,0,0,10);
            } else if (object[0x43] != 1) anim_start_blended(object,1,0,10);
        }
        if (!part_find_owned_effect_slot(object,0x10000,0)) return;
        F(state,0x60) = g_flying_target_speed_scale * 0.008333334f;
        matrix_mul_vec3(state+0x60,state+0x60,object+0xC0);
        count = g_flying_target_tick_count + 1;
        F(state,0x68) = -0.0500000045f;
        if ((g_flying_target_tick_count = count) > 3 && (mode = g_current_map_index) == 1 && !g_item_enabled_flags[13]) {
            g_item_enabled_flags[13] = 1;
            snd_play_from_global_bank(1,0,0);
            value_set_entry_by_index_us2(0x1233,-1);
            g_flying_path_mode = mode;
        }
        moby_set_state(object,2,-1);
        break;
    case 2:
        if (flag_set_first_pending(object)) {
            part_spawn_explosion_with_sparks(object,object+0x10,-1,0.5f,13.0f);
            PlayMobySound(0,0,object);
        }
        F(object,0x48) = 0.5f;
        FastVecAdd(object+0x10,object+0x10,state+0x60);
        F(state,0x68) -= 0.003f;
        F(state,0x60) *= 0.98f;
        F(state,0x64) *= 0.98f;
        F(object,0xF0) = FastAddRotations(-3.1415927f,(F(object,0xF0)+3.1415927f)*0.95f);
        if (math_fabs(coll_probe_ground_height_below(object+0x10,0,0.5f)-F(object,0x18)) < 0.5f) {
            I(state,0x78) = 30;
            moby_set_state(object,3,-1);
        }
        break;
    case 3:
        if (flag_set_first_pending(object)) {
            OozlaSpawnSplashParticles(object);
            PlayMobySound(1,0,object);
            part_spawn_scaled_bolts(object,1,0.0f);
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
extern int g_oozla_intro_stage MACRO_ADDR;
