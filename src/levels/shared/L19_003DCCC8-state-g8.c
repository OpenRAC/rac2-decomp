#include "names.h"
/* State update of a level 19/20 object, the same instructions as func_L18_003F80A0. Its own unit
 * for the same reasons: -G8 for the $gp limit and -frac2-gcse-unsplit-edges, because the repeated
 * object+0x10 and state+0x700 are shared by PRE (no locals).
 */
#include "common.h"

extern int flag_set_first_pending(u8 *);
extern int math_random_int_below(int);
extern void anim_start_blended(u8 *, int, int, int);
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
extern void moby_enter_hit_state(u8 *, int);
extern int moby_dispatch_action_by_kind(u8 *, u8 *);
extern void SetDeathBits(u8 *, int, int);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void moby_mark_spawned(u8 *);
extern void protopet_reset_to_start_anim(u8 *);
extern int D_0018C0B4 NOT_SDA;
extern u8 g_hero_position[];
extern u8 D_L19_001A8F20[] __attribute__((sda));
extern u16 *D_L19_001FB5A0[];
extern u8 *g_moby_l19_array[] __attribute__((sda));
extern int D_L19_001B2A38 __attribute__((sda));
extern u8 *D_L19_001B2B0C[] __attribute__((sda));

typedef struct { u8 pad[0x30]; u8 pos[0x10]; u8 rest[0x40]; } TargetRecord;

#define WORD(p,o) (*(int *)((p)+(o)))
#define HALF(p,o) (*(s16 *)((p)+(o)))
#define UHALF(p,o) (*(u16 *)((p)+(o)))
#define FLOAT(p,o) (*(float *)((p)+(o)))
#define PTR(p,o) (*(u8 **)((p)+(o)))

/* Updates a small flying enemy: it idles, patrols, chases a target, dives at a nearby object, and splits into pieces when hit. */
void flying_enemy_update_state(u8 *object)
{
    u8 temp[16] __attribute__((aligned(16)));
    u8 position[16] __attribute__((aligned(16)));
    u8 *state = PTR(object, 0x68);
    u8 *entity;
    u16 *listEntry;
    float best, distance;
    int hit;
    switch (object[0x20]) {
    case 0: break;
    case 1:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != math_random_int_below(2))
                anim_start_blended(object, math_random_int_below(2), 0, 10);
        }
        break;
    case 2:
        if (flag_set_first_pending(object)) {
            moby_set_controller_speed_limits(object, 0.0022222223f, 0.06666667f, 0.006981317885220051f, 0.20943955f);
            if (object[0x43] != math_random_int_below(2))
                anim_start_blended(object, math_random_int_below(2), 0, 10);
        } else if (HALF(state, 0x768)) {
            moby_set_state(object, 5, 2);
            moby_set_state(object, 4, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != math_random_int_below(2) + 4)
                anim_start_blended(object, math_random_int_below(2) + 4, 0, 10);
            object[0xBC] = math_random_int_below(180) + 120;
        } else if (UHALF(object, 0x96) > object[0xBC])
            moby_set_state(object, object[0x94], -1);
        break;
    case 4:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != math_random_int_below(2) + 2)
                anim_start_blended(object, math_random_int_below(2) + 2, 0, 10);
        } else if (object[0x60] & 2)
            moby_set_state(object, object[0x94], -1);
        break;
    case 5:
        if (flag_set_first_pending(object)) {
            if (WORD(state, 0x714) == -1 || D_0018C0B4 == 0x6F) {
                goto enter_pause;
            }
            object[0xBC] = 0;
            moby_set_controller_speed_limits(object, 0.004166667f, 0.125f, 0.006981317885220051f, 0.20943955f);
            if (object[0x43] != math_random_int_below(2) + 6)
                anim_start_blended(object, math_random_int_below(2) + 6, 0, 10);
            HALF(state, 0x760) = path_measure_moby_against_entry(object+0x10, WORD(state, 0x714), 0.0f);
        } else if (object[0xBC] == 0) {
            path_advance_waypoint_index(object, state+0x700, WORD(state, 0x714), 4.0f, (s16 *)(state+0x760), HALF(state, 0x76C));
            if (D_0018C0B4 == 0x6F || (UHALF(object, 0x96) % 180 == 0 && math_random_int_below(4) == 0)) {
enter_pause:
                object[0xBC] = 1;
                if (object[0x43] != math_random_int_below(2) + 4)
                    anim_start_blended(object, math_random_int_below(2)+4, 0, 10);
            }
        } else if (object[0xBC] == 1 && (object[0x60] & 2)) {
            moby_set_state(object, 5, -1);
            moby_set_state(object, 4, -1);
        }
        if (!HALF(state, 0x768)) {
            if (WORD(state, 0x750)) moby_set_state(object, 7, -1);
            else if (WORD(state, 0x744) != -1) moby_set_state(object, 8, -1);
            else moby_set_state(object, 2, -1);
        } else if (WORD(state, 0x754) != -1) {
            if (moby_run_slot_handler(object+0x10, WORD(state, 0x754), 0) &&
                moby_run_slot_handler(g_hero_position, WORD(state, 0x754), 0) &&
                protopet_try_use_counter(WORD(object, 0xB8)))
                moby_set_state(object, 6, -1);
        } else if (protopet_try_use_counter(WORD(object, 0xB8)))
            moby_set_state(object, 6, -1);
        break;
    case 6:
        if (flag_set_first_pending(object)) {
            object[0xBC] = 0;
            if (object[0x43] != math_random_int_below(2)+2)
                anim_start_blended(object, math_random_int_below(2)+2, 0, 10);
        } else if (object[0xBC] == 0 && (object[0x60] & 2)) {
            object[0xBC] = 1;
            moby_set_controller_speed_limits(object, 0.004166667f, 0.125f, 0.006981317885220051f, 0.20943955f);
            if (object[0x43] != math_random_int_below(2)+6)
                anim_start_blended(object, math_random_int_below(2)+6, 0, 10);
        } else if (object[0xBC] == 1) {
            qcopy(state+0x700, g_hero_position);
            HALF(state, 0x76A) = 1;
            if (WORD(state, 0x754) != -1 &&
                (!moby_run_slot_handler(object+0x10, WORD(state, 0x754), 0) ||
                 !moby_run_slot_handler(g_hero_position, WORD(state, 0x754), 0))) {
                protopet_increment_counter(WORD(object, 0xB8));
                moby_set_state(object, 5, -1);
            } else if (vec_distance_squared_xy(object+0x10, state+0x700) < FLOAT(state, 0x72C)*FLOAT(state, 0x72C)) {
                object[0xBC] = 2;
                if (object[0x43] != math_random_int_below(2)+4)
                    anim_start_blended(object, math_random_int_below(2)+4, 0, 10);
            }
        } else if (object[0xBC] == 2 && (object[0x60] & 2))
            moby_set_state(object, 6, -1);
        if (!HALF(state, 0x768)) {
            protopet_increment_counter(WORD(object, 0xB8));
            if (WORD(state, 0x750)) moby_set_state(object, 7, -1);
            else if (WORD(state, 0x744) != -1) moby_set_state(object, 8, -1);
            else moby_set_state(object, 2, -1);
        }
        break;
    case 7:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != math_random_int_below(2)+6)
                anim_start_blended(object, math_random_int_below(2)+6, 0, 10);
            best = 1000.0f;
            for (listEntry=D_L19_001FB5A0[WORD(state, 0x74C)];
                 (WORD(state, 0x74C)&255)!=255 && WORD(state, 0x74C)<=D_L19_001B2A38 && listEntry &&
                 ((listEntry != 0 && (s16)listEntry[-1]>=0) || listEntry==D_L19_001FB5A0[WORD(state, 0x74C)]); listEntry++) {
                entity=g_moby_l19_array[0]+((*listEntry&0x7FFF)<<8);
                if (!entity) break;
                distance=vec_distance_squared_xy(object+0x10, entity+0x10);
                if (distance<best) { PTR(state, 0x750)=entity; best=distance; }
            }
            moby_copy_saved_point_below(PTR(state, 0x750), position);
            vec_scale_to_length(temp, PTR(state, 0x750)+0xD0, -1.0f);
            FastVecAdd(state+0x700, position, temp);
        }
        HALF(state, 0x76A)=1;
        if (vec_distance_squared_xy(object+0x10, state+0x700)<0.25f) {
            if (HALF(state, 0x76E)>=5) moby_mark_spawned(object);
            else { HALF(state, 0x76E)++; protopet_reset_to_start_anim(object); }
        } else if (!moby_is_state_two(PTR(state, 0x750))) {
            moby_copy_saved_point_below(PTR(state, 0x750), temp);
            if (vec_distance_squared_xy(object+0x10, temp)<4.0f)
                moby_enter_hit_state(PTR(state, 0x750), 0);
        }
        break;
    case 8:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != math_random_int_below(2)+6)
                anim_start_blended(object, math_random_int_below(2)+6, 0, 10);
            qcopy(state+0x700, ((TargetRecord *)D_L19_001B2B0C[0])[WORD(state, 0x744)].pos);
        }
        HALF(state, 0x76A)=1;
        if (vec_distance_squared_xy(object+0x10, state+0x700)<0.25f)
            moby_set_state(object, 2, -1);
        break;
    case 9:
        hit=moby_dispatch_action_by_kind(object, state+0x60);
        if ((object[0x42]==9 && math_random_int_below(30)==0) || (hit&1)) {
                if (object[0x94]==6) protopet_increment_counter(WORD(object, 0xB8));
                SetDeathBits(object, 0, 3);
                SpawnExplosionEffects(object, D_L19_001A8F20, object+0x10, 0.0f, 0.0f, 20, 0, 10,
                             0.0f, 0.0f, 9.0f, 1.0f, -1, 3.0f, 1, 5, -1, 0, 0x810001);
                if (HALF(state, 0x76E)>=4) moby_mark_spawned(object);
                else { HALF(state, 0x76E)++; protopet_reset_to_start_anim(object); }
        } else if (hit&2) moby_set_state(object, object[0x94], 2);
        break;
    }
}
