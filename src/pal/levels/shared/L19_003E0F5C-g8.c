#include "names.h"
/* func_PAL_L19_003E0F5C, the PAL copy of func_L19_003DCCC8: the same C at 50 Hz, where the last
 * argument of every func_PAL_002A7E68 call, 10, becomes 8, object[0xBC] is scaled by 5/6 and the
 * func_002B60B0 floats change. */
#include "common.h"

extern int flag_set_first_pending(u8 *);
extern int math_random_int_below(int);
extern void anim_start_blended_pal(u8 *, int, int, int);
extern void moby_set_state(u8 *, int, int);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern int path_measure_moby_against_entry(u8 *, int, float);
/* Defined in L18_003F8EA8-qcopy.c; the float takes its place among the integers here. */
extern int path_advance_waypoint_index(u8 *, u8 *, int, float, s16 *, int);
extern int moby_run_slot_handler(u8 *, int, int);
extern int protopet_try_use_counter(int);
extern void protopet_increment_counter(int);
extern float vec_distance_squared_xy(u8 *, u8 *);
extern void moby_copy_saved_point_below(u8 *, u8 *);
extern void vec_scale_to_length(u8 *, u8 *, float);
extern void FastVecAdd(u8 *, u8 *, u8 *);
extern int moby_is_state_two(u8 *);
extern s32 moby_enter_hit_state_pal(u8 *, int);
extern int moby_dispatch_action_by_kind(u8 *, u8 *);
extern void SetDeathBits_pal(u8 *, int, int);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void moby_mark_spawned(u8 *);
extern void protopet_reset_to_start_anim(u8 *);
extern int g_game_mode NOT_SDA;
extern u8 g_hero_position[];
extern u8 g_particle_effect_template[] __attribute__((sda));
extern u16 *g_group_ptr_table[];
extern u8 *g_moby_l19_array[] __attribute__((sda));
extern int g_max_l19_group_index __attribute__((sda));
extern u8 *g_linked_object_table[] __attribute__((sda));

typedef struct { u8 pad[0x30]; u8 pos[0x10]; u8 rest[0x40]; } TargetRecord;

#define WORD(p,o) (*(int *)((p)+(o)))
#define HALF(p,o) (*(s16 *)((p)+(o)))
#define UHALF(p,o) (*(u16 *)((p)+(o)))
#define FLOAT(p,o) (*(float *)((p)+(o)))
#define PTR(p,o) (*(u8 **)((p)+(o)))

/* Updates a small flying enemy: it idles, patrols, chases a target, dives at a nearby object, and splits into pieces when hit (PAL: 50 Hz timings). */
void flying_enemy_update_state_pal(u8 *moby)
{
    u8 temp_vec[16] __attribute__((aligned(16)));
    u8 saved_pos[16] __attribute__((aligned(16)));
    u8 *vars = PTR(moby, 0x68);
    u8 *target;
    u16 *group_list;
    float best_dist, dist;
    int hit;
    switch (moby[0x20]) {
    case 0: break;
    case 1:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43] != math_random_int_below(2))
                anim_start_blended_pal(moby, math_random_int_below(2), 0, 8);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            moby_set_controller_speed_limits(moby, 0.0032000002f, 0.080000006f, 0.010053098f, 0.25132746f);
            if (moby[0x43] != math_random_int_below(2))
                anim_start_blended_pal(moby, math_random_int_below(2), 0, 8);
        } else if (HALF(vars, 0x768)) {
            moby_set_state(moby, 5, 2);
            moby_set_state(moby, 4, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43] != math_random_int_below(2) + 4)
                anim_start_blended_pal(moby, math_random_int_below(2) + 4, 0, 8);
            moby[0xBC] = ((s32)(math_random_int_below(180) + 120) * 5 + 2) / 6;
        } else if (UHALF(moby, 0x96) > moby[0xBC])
            moby_set_state(moby, moby[0x94], -1);
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43] != math_random_int_below(2) + 2)
                anim_start_blended_pal(moby, math_random_int_below(2) + 2, 0, 8);
        } else if (moby[0x60] & 2)
            moby_set_state(moby, moby[0x94], -1);
        break;
    case 5:
        if (flag_set_first_pending(moby)) {
            if (WORD(vars, 0x714) == -1 || g_game_mode == 0x6F) {
                goto enter_pause;
            }
            moby[0xBC] = 0;
            moby_set_controller_speed_limits(moby, 0.006f, 0.15f, 0.010053098f, 0.25132746f);
            if (moby[0x43] != math_random_int_below(2) + 6)
                anim_start_blended_pal(moby, math_random_int_below(2) + 6, 0, 8);
            HALF(vars, 0x760) = path_measure_moby_against_entry(moby+0x10, WORD(vars, 0x714), 0.0f);
        } else if (moby[0xBC] == 0) {
            path_advance_waypoint_index(moby, vars+0x700, WORD(vars, 0x714), 4.0f, (s16 *)(vars+0x760), HALF(vars, 0x76C));
            if (g_game_mode == 0x6F || (UHALF(moby, 0x96) % 180 == 0 && math_random_int_below(4) == 0)) {
enter_pause:
                moby[0xBC] = 1;
                if (moby[0x43] != math_random_int_below(2) + 4)
                    anim_start_blended_pal(moby, math_random_int_below(2)+4, 0, 8);
            }
        } else if (moby[0xBC] == 1 && (moby[0x60] & 2)) {
            moby_set_state(moby, 5, -1);
            moby_set_state(moby, 4, -1);
        }
        if (!HALF(vars, 0x768)) {
            if (WORD(vars, 0x750)) moby_set_state(moby, 7, -1);
            else if (WORD(vars, 0x744) != -1) moby_set_state(moby, 8, -1);
            else moby_set_state(moby, 2, -1);
        } else if (WORD(vars, 0x754) != -1) {
            if (moby_run_slot_handler(moby+0x10, WORD(vars, 0x754), 0) &&
                moby_run_slot_handler(g_hero_position, WORD(vars, 0x754), 0) &&
                protopet_try_use_counter(WORD(moby, 0xB8)))
                moby_set_state(moby, 6, -1);
        } else if (protopet_try_use_counter(WORD(moby, 0xB8)))
            moby_set_state(moby, 6, -1);
        break;
    case 6:
        if (flag_set_first_pending(moby)) {
            moby[0xBC] = 0;
            if (moby[0x43] != math_random_int_below(2)+2)
                anim_start_blended_pal(moby, math_random_int_below(2)+2, 0, 8);
        } else if (moby[0xBC] == 0 && (moby[0x60] & 2)) {
            moby[0xBC] = 1;
            moby_set_controller_speed_limits(moby, 0.006f, 0.15f, 0.010053098f, 0.25132746f);
            if (moby[0x43] != math_random_int_below(2)+6)
                anim_start_blended_pal(moby, math_random_int_below(2)+6, 0, 8);
        } else if (moby[0xBC] == 1) {
            qcopy(vars+0x700, g_hero_position);
            HALF(vars, 0x76A) = 1;
            if (WORD(vars, 0x754) != -1 &&
                (!moby_run_slot_handler(moby+0x10, WORD(vars, 0x754), 0) ||
                 !moby_run_slot_handler(g_hero_position, WORD(vars, 0x754), 0))) {
                protopet_increment_counter(WORD(moby, 0xB8));
                moby_set_state(moby, 5, -1);
            } else if (vec_distance_squared_xy(moby+0x10, vars+0x700) < FLOAT(vars, 0x72C)*FLOAT(vars, 0x72C)) {
                moby[0xBC] = 2;
                if (moby[0x43] != math_random_int_below(2)+4)
                    anim_start_blended_pal(moby, math_random_int_below(2)+4, 0, 8);
            }
        } else if (moby[0xBC] == 2 && (moby[0x60] & 2))
            moby_set_state(moby, 6, -1);
        if (!HALF(vars, 0x768)) {
            protopet_increment_counter(WORD(moby, 0xB8));
            if (WORD(vars, 0x750)) moby_set_state(moby, 7, -1);
            else if (WORD(vars, 0x744) != -1) moby_set_state(moby, 8, -1);
            else moby_set_state(moby, 2, -1);
        }
        break;
    case 7:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43] != math_random_int_below(2)+6)
                anim_start_blended_pal(moby, math_random_int_below(2)+6, 0, 8);
            best_dist = 1000.0f;
            for (group_list=g_group_ptr_table[WORD(vars, 0x74C)];
                 (WORD(vars, 0x74C)&255)!=255 && WORD(vars, 0x74C)<=g_max_l19_group_index && group_list &&
                 ((group_list != 0 && (s16)group_list[-1]>=0) || group_list==g_group_ptr_table[WORD(vars, 0x74C)]); group_list++) {
                target=g_moby_l19_array[0]+((*group_list&0x7FFF)<<8);
                if (!target) break;
                dist=vec_distance_squared_xy(moby+0x10, target+0x10);
                if (dist<best_dist) { PTR(vars, 0x750)=target; best_dist=dist; }
            }
            moby_copy_saved_point_below(PTR(vars, 0x750), saved_pos);
            vec_scale_to_length(temp_vec, PTR(vars, 0x750)+0xD0, -1.0f);
            FastVecAdd(vars+0x700, saved_pos, temp_vec);
        }
        HALF(vars, 0x76A)=1;
        if (vec_distance_squared_xy(moby+0x10, vars+0x700)<0.25f) {
            if (HALF(vars, 0x76E)>=5) moby_mark_spawned(moby);
            else { HALF(vars, 0x76E)++; protopet_reset_to_start_anim(moby); }
        } else if (!moby_is_state_two(PTR(vars, 0x750))) {
            moby_copy_saved_point_below(PTR(vars, 0x750), temp_vec);
            if (vec_distance_squared_xy(moby+0x10, temp_vec)<4.0f)
                moby_enter_hit_state_pal(PTR(vars, 0x750), 0);
        }
        break;
    case 8:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43] != math_random_int_below(2)+6)
                anim_start_blended_pal(moby, math_random_int_below(2)+6, 0, 8);
            qcopy(vars+0x700, ((TargetRecord *)g_linked_object_table[0])[WORD(vars, 0x744)].pos);
        }
        HALF(vars, 0x76A)=1;
        if (vec_distance_squared_xy(moby+0x10, vars+0x700)<0.25f)
            moby_set_state(moby, 2, -1);
        break;
    case 9:
        hit=moby_dispatch_action_by_kind(moby, vars+0x60);
        if ((moby[0x42]==9 && math_random_int_below(30)==0) || (hit&1)) {
                if (moby[0x94]==6) protopet_increment_counter(WORD(moby, 0xB8));
                SetDeathBits_pal(moby, 0, 3);
                SpawnExplosionEffects_pal(moby, g_particle_effect_template, moby+0x10, 0.0f, 0.0f, 20, 0, 10,
                             0.0f, 0.0f, 9.0f, 1.0f, -1, 3.0f, 1, 5, -1, 0, 0x810001);
                if (HALF(vars, 0x76E)>=4) moby_mark_spawned(moby);
                else { HALF(vars, 0x76E)++; protopet_reset_to_start_anim(moby); }
        } else if (hit&2) moby_set_state(moby, moby[0x94], 2);
        break;
    }
}
