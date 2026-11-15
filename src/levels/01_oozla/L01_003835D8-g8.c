#include "include_asm.h"
#include "common.h"

extern float D_L01_001AF87C __attribute__((sda));

extern float D_L01_001AFE18 __attribute__((sda));

/* Returns the height of the water surface in this level. */
float level_get_water_height(void) {
    return D_L01_001AFE18;
}

extern char *g_moby_l01_table __attribute__((sda));

extern char D_L01_001BF930[];

extern u8 *D_L01_001FB020[];

extern void FastVecAdd(char *, char *, char *);

extern void FastVecSub(char *, char *, char *);

extern void vec_scale_to_length(char *, char *, float);

extern int coll_test_point(char *, int, char *, float);

/* Moves the object by its speed for one frame and pushes it back along the surface if it hits something. */
void moby_move_with_collision(char *object) {
    char buf[16];

    vec_scale_to_length(buf, object + 0xE0, D_L01_001AF87C);
    FastVecAdd(buf, buf, object + 0x10);
    if (coll_test_point(buf, 0, object, D_L01_001AF87C) != 0) {
        FastVecSub(buf, D_L01_001BF930, buf);
        FastVecAdd(object + 0x10, object + 0x10, buf);
    }
}

/* Wakes up every swamp beast in the same group as this object, so they all notice the player. */
void swamp_beast_alert_group(u8 *object) {
    char *moby_base;
    u8 *entry;
    u8 *group_list;

    if (object[0x21] == 0xFF)
        return;
    group_list = D_L01_001FB020[object[0x21]];
    if (group_list == 0)
        return;
    entry = group_list;
    moby_base = g_moby_l01_table;
    for (;;) {
        char *other = moby_base + ((*(unsigned short *)entry & 0x7FFF) << 8);

        if (*(signed char *)(other + 0x20) >= 0) {
            if (*(short *)(other + 0xAA) == MOBY_CLASS_MUTANT_SWAMP_BEAST) {
                *(int *)(*(char **)(other + 0x68) + 0x350) = 1;
            }
        }
        if (*(short *)entry < 0)
            break;
        entry += 2;
    }
}

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
extern void anim_start_blended(void *,int,int,int);
extern void *part_find_owned_effect_slot(void *,int,int);
extern void matrix_mul_vec3(void *,void *,void *);
extern int snd_play_from_global_bank(int,int,int);
extern void value_set_entry_by_index(int,int);
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
void path_flying_target_update(u8 *object)
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
        F(state,0x74) = (D_L01_001AF85C * 0.016666668f) / first;
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
                if (object[0x43] != 0) anim_start_blended(object,0,0,10);
            } else if (object[0x43] != 1) anim_start_blended(object,1,0,10);
        }
        if (!part_find_owned_effect_slot(object,0x10000,0)) return;
        F(state,0x60) = D_L01_001AF85C * 0.008333334f;
        matrix_mul_vec3(state+0x60,state+0x60,object+0xC0);
        count = D_L01_001AF864 + 1;
        F(state,0x68) = -0.0500000045f;
        if ((D_L01_001AF864 = count) > 3 && (mode = g_current_map_index) == 1 && !D_001A7A60[13]) {
            D_001A7A60[13] = 1;
            snd_play_from_global_bank(1,0,0);
            value_set_entry_by_index(0x1233,-1);
            D_L01_001A907C = mode;
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

#define P(p,o) (*(int **)((u8 *)(p)+(o)))
#define C(p,o) (*(u8 **)((u8 *)(p)+(o)))
typedef int OozlaQuad __attribute__((mode(TI)));
extern float D_L01_001B94C0[];
typedef struct { u8 pad[0x2290]; u8 *target; } OozlaHero;
extern OozlaHero g_hero_state;
extern float g_hero_position[];
extern int D_L01_001B2088 MACRO_ADDR;
extern void moby_update_ground_check(void *);
extern int weapon_select_aim_target(void *,int,int,int,float,float);
extern float vec_distance_xy(void *,void *);
extern char *moby_get_private_value_0(u8 *);
extern int moby_apply_damage_to_object(void *,void *,int);
extern void swamp_beast_release_group_slot(void *);
extern float mat_fast_helper_a(float,float);
extern float fast_subtract_rotations(float,float);
extern void moby_update_eased_node(void *,void *,int,float,float);
extern int math_random_int_below(int);
extern void swamp_beast_spawn_bubbles(void *);
extern int GetFirstMobyInGroup(void *,int,int,int);
extern int GetNextMobyInGroup(void *,void *,int,int);
/* Main behaviour for a swimming creature. It checks for the player, steers toward its goal, makes bubbles near the surface and picks its group mates. */
void swamp_beast_update_awareness(u8 *object)
{
    OozlaQuad saved[2];
    u8 *iterator;
    u8 *common;
    u8 *state = C(object,0x68);
    u8 *target, *detail;
    float angle, distance, best;
    if (object[0x31] && fast_vec_dist(object+0x10,D_L01_001B94C0) < 24.0f) {
        moby_update_ground_check(object);
        object[0x6F] = 22;
    }
    saved[0] = *(OozlaQuad *)(state+0x230);
    saved[1] = *(OozlaQuad *)(state+0x240);
    if (weapon_select_aim_target(object,I(state,0x398),0,0,F(state,0x388),0.5f) != 1 && ((int *)saved)[5] == 1) {
        target = ((u8 **)saved)[4];
        if (target && target[0x20] != 254 && target[0x20] != 253 && vec_distance_xy(object+0x10,target+0x10) < F(state,0x39C)) {
            *(OozlaQuad *)(state+0x230) = saved[0];
            *(OozlaQuad *)(state+0x240) = saved[1];
            target = C(state,0x240);
            if (target == g_hero_state.target) {
                qcopy(state+0x230, (u8 *)&g_hero_state+0xD0);
            } else {
                qcopy(state+0x230, target+0x10);
                detail = (u8 *)moby_get_private_value_0(target);
                if (detail) F(state,0x238) += F(detail,0x10);
            }
        }
    }
    common = C(object,0x68);
    if (moby_apply_damage_to_object(object,common+0x60,0)) {
        if (F(common,0x20) <= 0.0f) I(common,0xDC) = -1;
        else I(common,0xDC) = I(common,0x14C);
        swamp_beast_release_group_slot(object);
        swamp_beast_alert_group(object);
        if (object[0x95] < 3) {
            common[0x7A] = 2;
            if (object[0x43] != 4) anim_start_blended(object,4,0,15);
            I(common,0x320) = 0;
            moby_set_state(object,1,1);
        }
    }
    if (object[0x31]) {
        u8 *goal = C(state,0x240);
        angle = mat_fast_helper_a(F(goal,0x10)-F(object,0x10),F(goal,0x14)-F(object,0x14));
        F(state,0x2B8) = fast_subtract_rotations(angle,F(object,0xF8));
        moby_update_eased_node(object,state+0x250,4,0.03f,0.3f);
        if (F(object,0x18) <= level_get_water_height()+0.3f && (object[0x95] >= 2 || math_random_int_below(9) == 0))
            swamp_beast_spawn_bubbles(object);
    }
    if (object[0x21] != 255 && *P(state,0x368) != D_L01_001B2088) {
        if (*P(state,0x36C) == -1 || *P(state,0x368) < D_L01_001B2088-10) {
            *P(state,0x36C) = -1;
            *P(state,0x370) = -1;
            best = 100000.0f;
            GetFirstMobyInGroup(&iterator,object[0x21],0,0);
            while (iterator) {
                if (*(short *)(iterator+0xAA) == *(short *)(object+0xAA)) {
                    distance = vec_distance_xy(iterator+0x10,g_hero_position);
                    if (distance < best && iterator[0x95] == 3 && iterator[0x20] < 3) {
                        best = distance;
                        *P(state,0x370) = *P(state,0x36C);
                        *P(state,0x36C) = *(short *)(iterator+0xB2);
                    }
                }
                GetNextMobyInGroup(&iterator,iterator,0,0);
            }
            *P(state,0x368) = D_L01_001B2088;
        }
    }
}
