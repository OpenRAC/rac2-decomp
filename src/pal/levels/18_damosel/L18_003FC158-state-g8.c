#include "names.h"
/* func_PAL_L18_003FC158, the PAL copy of func_L18_003F80A0: the same C with PAL's 50 Hz values.
 * Own unit for the same reasons as the USA one: -G8 and -frac2-gcse-unsplit-edges.
 */
#include "common.h"

extern int flag_set_first_pending(u8 *);
extern int math_random_int_below(int);
extern void func_PAL_002A7E68(u8 *, int, int, int);
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
extern void func_PAL_L18_003FF648(u8 *, int);
extern int moby_dispatch_action_by_kind(u8 *, u8 *);
extern void func_PAL_002A7650(u8 *, int, int);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void moby_mark_spawned(u8 *);
extern void protopet_reset_to_start_anim(u8 *);
extern int D_0018C0B4 NOT_SDA;
extern u8 g_hero_position[];
extern u8 D_L18_001A8F20[] __attribute__((sda));
extern u16 *D_L18_001FB320[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern int D_L18_001B2838 __attribute__((sda));
extern u8 *g_waypoint_table[] __attribute__((sda));

typedef struct { u8 pad[0x30]; u8 pos[0x10]; u8 rest[0x40]; } TargetRecord;

#define WORD(p,o) (*(int *)((p)+(o)))
#define HALF(p,o) (*(s16 *)((p)+(o)))
#define UHALF(p,o) (*(u16 *)((p)+(o)))
#define FLOAT(p,o) (*(float *)((p)+(o)))
#define PTR(p,o) (*(u8 **)((p)+(o)))

void func_PAL_L18_003FC158(u8 *object)
{
    u8 temp[16] __attribute__((aligned(16)));
    u8 position[16] __attribute__((aligned(16)));
    u8 *state = PTR(object, 0x68);
    u8 *entity;
    u16 *p;
    float best, distance;
    int hit;
    switch (object[0x20]) {
    case 0: break;
    case 1:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != math_random_int_below(2))
                func_PAL_002A7E68(object, math_random_int_below(2), 0, 8);
        }
        break;
    case 2:
        if (flag_set_first_pending(object)) {
            moby_set_controller_speed_limits(object, 0.0032000002f, 0.080000006f, 0.010053098f, 0.25132746f);
            if (object[0x43] != math_random_int_below(2))
                func_PAL_002A7E68(object, math_random_int_below(2), 0, 8);
        } else if (HALF(state, 0x768)) {
            moby_set_state(object, 5, 2);
            moby_set_state(object, 4, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != math_random_int_below(2) + 4)
                func_PAL_002A7E68(object, math_random_int_below(2) + 4, 0, 8);
            object[0xBC] = ((s32)(math_random_int_below(180) + 120) * 5 + 2) / 6;
        } else if (UHALF(object, 0x96) > object[0xBC])
            moby_set_state(object, object[0x94], -1);
        break;
    case 4:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != math_random_int_below(2) + 2)
                func_PAL_002A7E68(object, math_random_int_below(2) + 2, 0, 8);
        } else if (object[0x60] & 2)
            moby_set_state(object, object[0x94], -1);
        break;
    case 5:
        if (flag_set_first_pending(object)) {
            if (WORD(state, 0x714) == -1 || D_0018C0B4 == 0x6F) {
                goto enter_pause;
            }
            object[0xBC] = 0;
            moby_set_controller_speed_limits(object, 0.006f, 0.15f, 0.010053098f, 0.25132746f);
            if (object[0x43] != math_random_int_below(2) + 6)
                func_PAL_002A7E68(object, math_random_int_below(2) + 6, 0, 8);
            HALF(state, 0x760) = path_measure_moby_against_entry(object+0x10, WORD(state, 0x714), 0.0f);
        } else if (object[0xBC] == 0) {
            path_advance_waypoint_index(object, state+0x700, WORD(state, 0x714), 4.0f, (s16 *)(state+0x760), HALF(state, 0x76C));
            if (D_0018C0B4 == 0x6F || (UHALF(object, 0x96) % 180 == 0 && math_random_int_below(4) == 0)) {
enter_pause:
                object[0xBC] = 1;
                if (object[0x43] != math_random_int_below(2) + 4)
                    func_PAL_002A7E68(object, math_random_int_below(2)+4, 0, 8);
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
                func_PAL_002A7E68(object, math_random_int_below(2)+2, 0, 8);
        } else if (object[0xBC] == 0 && (object[0x60] & 2)) {
            object[0xBC] = 1;
            moby_set_controller_speed_limits(object, 0.006f, 0.15f, 0.010053098f, 0.25132746f);
            if (object[0x43] != math_random_int_below(2)+6)
                func_PAL_002A7E68(object, math_random_int_below(2)+6, 0, 8);
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
                    func_PAL_002A7E68(object, math_random_int_below(2)+4, 0, 8);
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
                func_PAL_002A7E68(object, math_random_int_below(2)+6, 0, 8);
            best = 1000.0f;
            for (p=D_L18_001FB320[WORD(state, 0x74C)];
                 (WORD(state, 0x74C)&255)!=255 && WORD(state, 0x74C)<=D_L18_001B2838 && p &&
                 ((p != 0 && (s16)p[-1]>=0) || p==D_L18_001FB320[WORD(state, 0x74C)]); p++) {
                entity=g_moby_l18_table[0]+((*p&0x7FFF)<<8);
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
                func_PAL_L18_003FF648(PTR(state, 0x750), 0);
        }
        break;
    case 8:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != math_random_int_below(2)+6)
                func_PAL_002A7E68(object, math_random_int_below(2)+6, 0, 8);
            qcopy(state+0x700, ((TargetRecord *)g_waypoint_table[0])[WORD(state, 0x744)].pos);
        }
        HALF(state, 0x76A)=1;
        if (vec_distance_squared_xy(object+0x10, state+0x700)<0.25f)
            moby_set_state(object, 2, -1);
        break;
    case 9:
        hit=moby_dispatch_action_by_kind(object, state+0x60);
        if ((object[0x42]==9 && math_random_int_below(30)==0) || (hit&1)) {
                if (object[0x94]==6) protopet_increment_counter(WORD(object, 0xB8));
                func_PAL_002A7650(object, 0, 3);
                func_PAL_002AC718(object, D_L18_001A8F20, object+0x10, 0.0f, 0.0f, 20, 0, 10,
                             0.0f, 0.0f, 9.0f, 1.0f, -1, 3.0f, 1, 5, -1, 0, 0x810001);
                if (HALF(state, 0x76E)>=4) moby_mark_spawned(object);
                else { HALF(state, 0x76E)++; protopet_reset_to_start_anim(object); }
        } else if (hit&2) moby_set_state(object, object[0x94], 2);
        break;
    }
}
