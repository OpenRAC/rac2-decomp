#include "common.h"
#include "include_asm.h"

extern char *CreateMoby(int id);
extern float math_random_float_range(float a, float b);
extern float math_random_angle(void);
extern void *part_spawn_ground_effect(void *, unsigned int, int, unsigned int, int, char *, float, float, float, int);
extern char D_L11_001A8F20[] __attribute__((sda));


extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern void anim_start_blended(char *, int, int, int);
extern void moby_set_state(char *, int, int);
extern void func_002A05A8(char *);
extern void set_moby_color(char *, int, int, int);
extern int part_spawn_damage_debris(char *, char *, char *);
extern int moby_spawn_linked(char *, int, float, float);

extern void get_moby_color(char *, int *, int *, int *);

extern void func_00282D30_2(char *dst, char *src, float scale);

extern void func_32C9E0();
extern void func_32C700();
extern void func_324560(char *a0);
extern void arena_add_waiting_fighter(s32 a0, int a1);
extern void func_323688(char *a0, char *a1);
extern void mem_clear(char *a0, int a1, int a2);
typedef int TI128 __attribute__((mode(TI)));
extern void security_robot_destroy_held_item(char *self, TI128 *pos);
extern char *func_3224B0(int a0);
extern void func_324F00(char *a0);
extern void func_3362A8(char *a0, s32 a1, int a2, int a3);
extern void func_300180(void *a0);
extern void gfx_draw_two_layer_glow_sprite(char *a0, char *a1, float a2, int a3, int a4, int a5);
extern void func_338398(char *a0, char *a1, float a2, int a3, int a4);
extern void func_32E480(char *a0, char *a1, float f12, float f13, float f14,
                        int a2, int a3, int a4, int a5);
extern void func_2FD7E8(void *a0, int a1, void *a2, void *a3, int a4, int a5,
                        int a6, int a7, float f12);
extern void func_32EB98(void *a0, void *a1);
extern s32 func_441868(s32 a0, s32 a1);
extern s32 func_33C800(char *a0, s32 a1, s32 a2, s32 a3, float f12, float f13);


/* func_L11_004465F8 is defined in L11_004465F8-g32.c. */

/* func_L11_00446C78 is defined in L11_00446C78-g16.c. */

/* func_L11_00446EB8 is defined in L11_004465F8-loop-g8.c. */


/* func_L11_004471A8 is defined in L11_004465F8-g8.c. */


/* func_L11_004475A0 is defined in L11_004475A0-g8.c. */

/* func_L11_004484A8 is defined in L11_004465F8-g8.c. */

/* Finishes the robot's frame: lets go of its held item, counts up the state timer and refreshes its shadow and light effects. */
void security_robot_finish_frame(char *object)
{
    char *state = *(char **)(object + 0x68);

    func_300180(state + 0x364);
    if (*(s32 *)(state + 0x354) != 0) {
        func_3362A8(object, *(s32 *)(state + 0x354), 2, 0);
        *(u16 *)((char *)(long)*(s32 *)(state + 0x354) + 0x34) &= 0xFFFD;
    }
    if (*(u16 *)(object + 0x96) < 0xFFFF)
        *(u16 *)(object + 0x96) = *(u16 *)(object + 0x96) + 1;
    func_338398(object, state + 0x230, 3.5f, 4, 1);
    func_32E480(object, object + 0x10, 1.5f, 1.0f, 1.0f, 0x4000000, 0, 1, 0);
}

/* Makes the robot stand still, using the idle pose that matches whether it holds an item. */
void security_robot_play_idle(char *object)
{
    if (*(s32 *)(*(char **)(object + 0x68) + 0x354) != 0) {
        func_32C9E0(object, 4, 2);
        if (*(u8 *)(object + 0x43) != 0)
            func_32C700(object, 0, 0, 0xA);
    } else {
        func_32C9E0(object, 5, 2);
        if (*(u8 *)(object + 0x43) != 1)
            func_32C700(object, 1, 0, 0xA);
    }
}

/* func_L11_00448AA8 is in L11_00448AA8.c. */

/* Tells whether the robot holds an item and is in one of its attack or throw states. */
s32 security_robot_is_holding_item_attacking(char *object)
{
    s32 result = 0;
    u8 state_byte;

    if (*(s32 *)(*(char **)(object + 0x68) + 0x354) != 0) {
        state_byte = *(u8 *)(object + 0x20);
        if (state_byte == 0xF || state_byte == 4 || *(u8 *)(object + 0x95) == 4 || state_byte == 0xE)
            result = 1;
    }
    return result;
}

/* The id lists: halfwords whose low 15 bits index the 256-byte records of D_L11_001B359C, the
   last one with its sign bit set; a walk stops when the object's group byte (+0x21) is 0xFF or
   above the limit at D_L11_001B35B8. The records' base is read bare (`lui`/`lw` in one register:
   `sda` in this -G0 unit), the limit is a $gp word. */
extern u16 *g_group_id_lists[];
extern u8 *g_moby_l11_table __attribute__((sda));
extern s32 D_L11_001B35B8[] __attribute__((sda));
extern f32 vec_distance_xy(u8 *, u8 *);
extern s32 arena_consume_waiting_fighter(u8 *, s32);
/* Runs what the id in its second argument names on the object and returns a value the caller
   keeps; the arguments are read in this order (object, id, two floats, two ints). */
extern s32 weapon_select_aim_target(u8 *, s32, f32, f32, s32, s32);

/* The pairing step of a kind-0xD98 object (state block at +0x68: partner +0x350, phase +0x366,
   the halfword at +0x36A). Below state 4 it forgets its partner and its phase. In phase 1 it
   runs func_002B3BA8 (result to +0x36A) and takes its partner from +0x220; from any other phase
   it enters phase 1 (and does the same) when func_L11_00441868 grants a counter of its kind from
   the owner at +0xB8. In phase 2 with a partner it stays paired (+0x36A of both set to 2) while
   the partner is alive (state byte not 0xFE or 0xFD, byte +0x95 above 1), is in the same phase
   and points back at it; otherwise it drops the partner and goes back to phase 0. Without a
   partner it walks the id list of its group for the nearest other kind-0xD98 object (state byte
   3 or more, not 0xFE or 0xFD, phase 0) closer than 1000.0 and pairs with it: partner pointers,
   phase 2 and +0x36A = 2 on both sides. The state block of the partner being checked and that
   of the object chosen are two variables (one per role), and the group byte goes through a
   halfword local so that each loop test loads it once. */
void security_robot_update_pairing(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    u16 *id_ptr;
    u8 *entry;
    u8 *best;
    u8 *partner;
    u8 *partner_state;
    u8 *best_state;
    f32 best_distance;
    u16 group;

    if (self[0x20] < 4) {
        *(u8 **)(state + 0x350) = 0;
    } else {
        if (*(s16 *)(state + 0x366) == 1) {
            *(s16 *)(state + 0x36A) =
                weapon_select_aim_target(self, *(s32 *)(state + 0x360), 100.0f, 100.0f, 0, 0);
            *(u8 **)(state + 0x350) = *(u8 **)(state + 0x220);
            return;
        } else if (arena_consume_waiting_fighter(*(u8 **)(self + 0xB8), *(s16 *)(self + 0xAA))) {
            *(s16 *)(state + 0x366) = 1;
            *(s16 *)(state + 0x36A) =
                weapon_select_aim_target(self, *(s32 *)(state + 0x360), 100.0f, 100.0f, 0, 0);
            *(u8 **)(state + 0x350) = *(u8 **)(state + 0x220);
            return;
        }
        if (*(s16 *)(state + 0x366) == 2 && *(u8 **)(state + 0x350) != 0) {
            partner = *(u8 **)(state + 0x350);
            partner_state = *(u8 **)(partner + 0x68);
            if (partner[0x20] != 0xFE) {
                if (partner[0x20] != 0xFD) {
                    if (partner[0x95] != 0) {
                        if (partner[0x95] != 1) {
                            if (*(s16 *)(partner_state + 0x366) == *(s16 *)(state + 0x366)) {
                                if (*(u8 **)(partner_state + 0x350) == self) {
                                    *(s16 *)(state + 0x36A) = 2;
                                    *(s16 *)(partner_state + 0x36A) = 2;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            *(u8 **)(state + 0x350) = 0;
            *(s16 *)(state + 0x366) = 0;
            return;
        }
        best = 0;
        best_distance = 1000.0f;
        for (id_ptr = g_group_id_lists[self[0x21]];
             (group = self[0x21]) != 0xFF && group <= D_L11_001B35B8[0] && id_ptr != 0 &&
             ((id_ptr != 0 && (s16)id_ptr[-1] >= 0) || id_ptr == g_group_id_lists[group]);
             id_ptr++) {
            entry = g_moby_l11_table + ((*id_ptr & 0x7FFF) << 8);
            if (entry == 0)
                break;
            if (entry[0x20] != 0xFE) {
                if (entry[0x20] != 0xFD) {
                    if (entry != self && entry[0x20] >= 3 && *(s16 *)(entry + 0xAA) == 0xD98 /* moby class 3480 */ &&
                        *(s16 *)(*(u8 **)(entry + 0x68) + 0x366) == 0) {
                        if (vec_distance_xy(self + 0x10, entry + 0x10) < best_distance) {
                            best = entry;
                            best_distance = vec_distance_xy(self + 0x10, entry + 0x10);
                        }
                    }
                }
            }
        }
        if (best != 0) {
            *(u8 **)(state + 0x350) = best;
            *(s16 *)(state + 0x366) = 2;
            *(s16 *)(state + 0x36A) = 2;
            best_state = *(u8 **)(best + 0x68);
            *(u8 **)(best_state + 0x350) = self;
            *(s16 *)(best_state + 0x366) = 2;
            *(s16 *)(best_state + 0x36A) = 2;
            return;
        }
    }
    *(s16 *)(state + 0x366) = 0;
}

extern float moby_get_anim_value(char *);
extern void moby_transform_joint_to_world(char *, int, void *);
extern f32 coll_project_point_on_segment(void *, void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern int coll_sweep_from_object(char *, void *, int, float, float, float, int, int, int);
extern int PlayMobySound(int, int, char *);

/* While the robot swings its arm, hurts the hero if the arm sweeps through the hero's position. */
void security_robot_damage_along_arm_swing(char *object)
{
    float start[4], end[4], closest[4], remaining[4], span[4];
    char *state;
    float time, fraction;

    time = moby_get_anim_value(object);
    state = *(char **)(object + 0x68);
    if (19.0f <= time && time <= 31.0f) {
        moby_transform_joint_to_world(object, 0, start);
        moby_transform_joint_to_world(object, 1, end);
        coll_project_point_on_segment(closest, start, end,
                         *(char **)(state + 0x350) + 0x10);
        FastVecSub(remaining, closest, end);
        FastVecSub(span, start, end);
        fraction = FastVecLength(remaining);
        fraction /= FastVecLength(span);
        if (fraction < 0.0f)
            fraction = 0.0f;
        if (fraction > 1.0f)
            fraction = 1.0f;
        if (coll_sweep_from_object(object, closest, 0x10001,
                         fraction * 0.35f + 0.15f,
                         (float)*(unsigned char *)(state + 0x34), 1.0f, 0, 1, 0)
            && *(short *)(state + 0x368) == 0) {
            PlayMobySound(5, 0, object);
            *(short *)(state + 0x368) = 1;
        }
        coll_sweep_from_object(object, end, 0x10001, 0.5f,
                      (float)*(unsigned char *)(state + 0x34), 1.0f, 0, 1, 0);
    }
}

/* Creates the item the robot holds and attaches it to the robot. */
void security_robot_spawn_held_item(char *object)
{
    char *state = *(char **)(object + 0x68);
    s32 child = (s32)(long)func_3224B0(0x9D8 /* moby class 2520 */);

    *(s32 *)(state + 0x354) = child;
    if (child == 0)
        return;
    *(u8 *)((char *)(long)child + 0x30) = *(u8 *)(object + 0x30);
    *(u16 *)((char *)(long)*(s32 *)(state + 0x354) + 0x32) = *(u16 *)(object + 0x32);
    *(u8 *)((char *)(long)*(s32 *)(state + 0x354) + 0x31) = 1;
    *(u64 *)((char *)(long)*(s32 *)(state + 0x354) + 0x38) = *(u64 *)(object + 0x38);
    func_324F00((char *)(long)*(s32 *)(state + 0x354));
    *(s32 *)((char *)(long)*(s32 *)(state + 0x354) + 0x98) = 0;
    *(s32 *)(*(char **)((char *)(long)*(s32 *)(state + 0x354) + 0x68) + 0x3C) = 1;
}

/* func_L11_00449330 is in L11_00449330.c: PAL's level 11 has other code at its place,
   so the calls to it from this unit go through its symbol. */

/* Sets the security robot up when it appears: its turn speeds, starting pose, flags and held item. */
void security_robot_init(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);
    int colors[3];
    int green, blue;

    *(short *)(state + 0x88) = 0;
    *(short *)(state + 0x366) = 0;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x36E) = active;
    moby_set_controller_speed_limits(object, 0.0055555556900799274f, 0.10333333909511566f,
                  0.0034906589426100254f, 0.41887909173965454f);
    *(u8 *)(state + 0x6A) = 0;
    *(u8 *)(state + 0x2E) = 1;
    *(u8 *)(object + 0x7F) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    if (*(short *)(state + 0x36E) != 0) {
        moby_set_state(object, 4, 2);
        *(u16 *)(object + 0x34) |= 0x100;
        anim_start_blended(object, 0, 0, 0);
        func_002A05A8(object);
        moby_spawn_linked(object, 0, 2.0f, 2.0f);
    } else {
        if (*(u8 *)(object + 0x43) != 0)
            anim_start_blended(object, 0, 0, 10);
        moby_set_state(object, 3, 1);
        *(u8 *)(object + 0x31) = 1;
        *(u16 *)(object + 0x34) &= 0xFEFE;
    }
    security_robot_spawn_held_item(object);
    *(short *)(state + 0x36C) = mode;
    *(int *)(state + 0x200) = 0;
    part_spawn_damage_debris(object, state + 0x1F0, state + 0x20);
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        set_moby_color(object, *(u8 *)(state + 0x54), *(u8 *)(state + 0x55),
                      *(u8 *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
    if (*(char **)(state + 0x354) != 0) {
        get_moby_color(object, &colors[0], &colors[1], &colors[2]);
        green = colors[1];
        blue = colors[2];
        set_moby_color(*(char **)(state + 0x354), colors[0], green, blue);
    }
}

/* Puts the security robot to rest: hides it, lets go of its partner and held item, and resets its effects. */
void security_robot_deactivate(char *object_arg)
{
    char *object = object_arg;
    char *state;
    TI128 item_pos;

    func_32C9E0(object_arg, 1, 0);
    func_32C700(object_arg, 0, 0, 3);
    func_324560(object_arg);
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xEFFF) | 0x47;
    *(u8 *)(object + 0x31) = 0;
    *(s32 *)(object + 0x98) = 0;
    state = *(char **)(object + 0x68);
    if (*(s16 *)(state + 0x366) == 1)
        arena_add_waiting_fighter(*(s32 *)(object + 0xB8), 0xD98);
    *(s16 *)(state + 0x366) = 0;
    *(s32 *)(state + 0x350) = 0;
    if (*(s32 *)(state + 0x354) != 0) {
        item_pos = *(TI128 *)((char *)(long)*(s32 *)(state + 0x354) + 0x10);
        security_robot_destroy_held_item(object, &item_pos);
    }
    if (*(u8 *)(state + 0x2B1) != 0) {
        f32 unit = 1.0f;

        *(u8 *)(state + 0x2B2) = 0;
        *(f32 *)(state + 0x2D8) = unit;
        *(f32 *)(state + 0x2D4) = unit;
        *(f32 *)(state + 0x2D0) = unit;
        func_323688(object, state + 0x2B0);
        mem_clear(state + 0x2B0, 0, 0x40);
    }
}

extern void AttachManipulator(char *a0, int a1, char *a2);
extern void vec_random_direction(void *a0, float f12, float f13);
extern void part_spawn_masked_debris(char *a0, int a1, void *a2, float f12, float f13, float f14,
                        float f15, int a3);
extern void moby_set_anim_type_three(char *a0, int a1, int a2);
extern void part_queue_moby_for_glow(char *a0, int a1, char *a2);

/* The moby's death path: clears the spawn flags, hands the last position to the scene
   manager, resets the 0x2B0 rig and leaves the object in its dead state. */
/* Kills the security robot, then either resets it right away or schedules the reset. */
void security_robot_kill(char *object, int skip_fade, int reset_now)
{
    char *state = *(char **)(object + 0x68);
    char *rig;
    TI128 burst_dir;
    float tiny;

    *(s32 *)(state + 0x20) = 0;
    if (*(s16 *)(state + 0x366) == 1)
        arena_add_waiting_fighter(*(s32 *)(object + 0xB8), 0xD98);
    *(s16 *)(state + 0x366) = 0;
    *(s32 *)(state + 0x350) = 0;
    if (*(s32 *)(state + 0x354) != 0) {
        burst_dir = *(TI128 *)((char *)(long)*(s32 *)(state + 0x354) + 0x10);
        security_robot_destroy_held_item(object, &burst_dir);
    }
    if (*(u8 *)(state + 0x2B1) == 0) {
        rig = state + 0x2B0;
        mem_clear(rig, 0, 0x40);
        AttachManipulator(object, 3, rig);
        tiny = 1.0e-4f;
        *(u8 *)(state + 0x2B2) = 1;
        *(f32 *)(state + 0x2D8) = tiny;
        *(f32 *)(state + 0x2D4) = tiny;
        *(f32 *)(state + 0x2D0) = tiny;
        vec_random_direction((char *)&burst_dir, 1.0f / 60.0f, 0.0500000045f);
        part_spawn_masked_debris(object, 0x20, (char *)&burst_dir, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    *(s32 *)(object + 0x98) = 0;
    if (skip_fade == 0)
        moby_set_anim_type_three(object, 0, -1);
    if (reset_now == 0)
        part_queue_moby_for_glow(object, 0, (char *)security_robot_deactivate);
    else
        security_robot_deactivate(object);
}

/* func_L11_00449AD8 is defined in L11_00449AD8-helpers.c. */

/* func_L11_00449C70 is defined in L11_004465F8-aim-g8.c. */

/* func_L11_0044AFC8 is defined in L11_0044AFC8-g8.c. */

/* func_L11_0044BD68 is in L11_0044BD68-g8.c. */

/* Finishes the smasher robot's frame: counts up the state timer and refreshes its shadow and light effects. */
void smasher_robot_finish_frame(char *object)
{
    char *state = *(char **)(object + 0x68);

    if (*(u16 *)(object + 0x96) < 0xFFFF)
        *(u16 *)(object + 0x96) = *(u16 *)(object + 0x96) + 1;
    func_338398(object, state + 0x4E0, 4.0f, 7, 1);
    func_32E480(object, object + 0x10, 1.3f, 1.0f, 1.0f, 0x4000000, 0, 1, 0);
}

/* advances the sub-object's ring cursor, hands the new slot of the 0x370 table to the scene
   manager, and refreshes the matching slot of the 0x270 table from the live 0x4A4 record */
/* func_L11_0044C180 is defined in L11_0044C180-helpers.c. */

/* func_L11_0044C220 is defined in L11_004465F8-g8.c (its globals are reached through $gp). */

/* state handler: clears the 0x490 word while the frame byte is out of the 0..3 window, otherwise
   arms the 0x4CA gate through the 0xB8 handle and runs the 100-unit smash into it */
/*W23B*/
/* Same body as func_L02_003F16F0, with this function's own callees. */
void smasher_robot_update_pairing(char *object) {
    char *state = *(char **)(object + 0x68);

    if (*(unsigned char *)(object + 0x20) < 4) {
        *(int *)(state + 0x490) = 0;
        goto done;
    }

    if (*(short *)(state + 0x4CA) == 1) {
        *(short *)(state + 0x4C8) =
            weapon_select_aim_target(object, *(int *)(state + 0x4C4), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x490) = *(int *)(state + 0x220);
    } else {
        if (arena_consume_waiting_fighter(*(int *)(object + 0xB8), *(short *)(object + 0xAA)) == 0)
            goto done;
        *(short *)(state + 0x4CA) = 1;
        *(short *)(state + 0x4C8) =
            weapon_select_aim_target(object, *(int *)(state + 0x4C4), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x490) = *(int *)(state + 0x220);
    }
    return;

done:
    *(short *)(state + 0x4CA) = 0;
}
/*W23E*/


/* Sets the smasher robot up when it appears: its turn speeds, starting pose and flags. */
void smasher_robot_init(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);
    char **slot;
    char *collision, *health;
    int i;

    *(short *)(state + 0x4CA) = 0;
    *(short *)(state + 0x88) = 0;
    *(u8 *)(state + 0x2E) = 1;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x4D2) = active;
    moby_set_controller_speed_limits(object, 0.004444444552063942f, 0.13333334028720856f,
                  0.0011635529808700085f, 0.10471977293491364f);
    *(u8 *)(object + 0x7F) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    if (*(short *)(state + 0x4D2) != 0) {
        moby_set_state(object, 4, 2);
        *(u16 *)(object + 0x34) |= 0x100;
        anim_start_blended(object, 2, 0, 0);
        func_002A05A8(object);
        moby_spawn_linked(object, 0, 2.0f, 2.0f);
    } else {
        moby_set_state(object, 3, 0);
        *(u8 *)(object + 0x31) = 1;
        *(u16 *)(object + 0x34) &= 0xFEFE;
    }
    *(u8 *)(state + 0x6A) = 0;
    collision = state + 0x1F0;
    health = state + 0x20;
    for (i = 0; i < 2; i++) {
        slot = (char **)(state + 0x4A0 + i * 4);
        if (*slot != 0) {
            *(u16 *)(*slot + 0x34) &= 0xFFFE;
            *(u8 *)(*slot + 0x31) = 1;
            *(int *)(*slot + 0x98) = *(int *)(*(char **)(*slot + 0x24) + 0x10);
        }
    }
    *(short *)(state + 0x4D0) = mode;
    *(int *)(state + 0x200) = 0;
    part_spawn_damage_debris(object, collision, health);
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        set_moby_color(object, *(u8 *)(state + 0x54), *(u8 *)(state + 0x55),
                      *(u8 *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
}

extern void arena_add_waiting_fighter(int, int);
extern char *SpawnExplosion(char *, int, int, int, int, int, int, int,
                         float, float, int, int, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void vec_random_direction(void *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void part_spawn_masked_debris(char *, int, void *, float, float, float, float, int);

/* Puts the smasher robot to rest: lets go of its pairing, shows a burst of effects and hides it. */
void smasher_robot_deactivate(char *object) {
    char *state = *(char **)(object + 0x68);
    float direction[4];
    char **slot;
    int i;

    if (*(short *)(state + 0x4CA) == 1)
        arena_add_waiting_fighter(*(int *)(object + 0xB8), 0xDCF /* moby class 3535 */);
    *(short *)(state + 0x4CA) = 0;
    *(int *)(state + 0x490) = 0;
    if (*(u8 *)(object + 0x31) != 0) {
        SpawnExplosion(object + 0x10, 0, 0x1E, 5, 5, 5, 0x2D, 1,
                     0.5f, 0.0f, 1, 0, 0, 0);
        snd_play_from_class_bank(0, 0, object, 0xDF7);
        vec_random_direction(direction, 0.033333335071802139f, 0.083333335816860199f);
        FastVecAdd(direction, direction, state + 0xD0);
        part_spawn_masked_debris(object, 0x7F0, direction, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    slot = (char **)(state + 0x4A0);
    for (i = 1; i >= 0; i--) {
        if (*slot != 0) {
            *(u16 *)(*slot + 0x34) |= 1;
            *(u8 *)(*slot + 0x31) = 0;
            *(int *)(*slot + 0x98) = 0;
        }
        slot++;
    }
    anim_start_blended(object, 0, 0, 3);
    func_002A05A8(object);
    moby_set_state(object, 1, 0);
    *(u8 *)(object + 0x31) = 0;
    *(int *)(object + 0x98) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xEFFF) | 0x47;
}

/* func_L11_0044C688 is defined in L11_0044C688-helpers.c. */

/* Remembers what the smasher robot was doing and makes it turn around. */
void smasher_robot_start_turn_around(char *object)
{
    char *state = *(char **)(object + 0x68);

    *(u16 *)(state + 0x4CC) = *(u8 *)(object + 0x20);
    *(u16 *)(state + 0x4CE) = *(u8 *)(object + 0x95);
    func_32C9E0(object, 6, 4);
}

/* func_L11_0044C850 is defined in L11_004465F8-aim-0044C850-g8.c. */

/* Spawns a small flying bit from the robot with the given speed, spin and position. */
char *robot_spawn_debris(char *owner, TI128 *velocity, TI128 *position, float life_scale)
{
    char *projectile = CreateMoby(0xDD9 /* moby class 3545 */);

    if (projectile != 0) {
        char *vars;
        float size;

        *(unsigned char *)(projectile + 0x30) = 0xFF;
        *(short *)(projectile + 0x32) = 0xFF;
        projectile[0x31] = 1;
        projectile[0x20] = 0;
        *(long long *)(projectile + 0x38) = *(long long *)(owner + 0x38);
        qcopy(projectile + 0x10, position);
        vars = *(char **)(projectile + 0x68);
        qcopy(vars, velocity);
        *(float *)(vars + 0x14) = life_scale;
        *(char **)(vars + 0x10) = owner;
        *(float *)(vars + 0x18) = math_random_angle();
        *(float *)(vars + 0x1C) = math_random_float_range(0.20943954586982727f, 0.6283186078071594f);
        *(float *)(vars + 0x20) = 0.15f;
        *(unsigned char *)(projectile + 0x23) = 0x80;
        *(unsigned short *)(projectile + 0x34) |= 0x100;
        *(float *)(projectile + 0x2C) = math_random_float_range(0.005f, 0.00625f);
        *(int *)(vars + 0x24) = 0;
        *(unsigned short *)(projectile + 0x34) |= 0x200;
        size = math_random_float_range(2.0f, 4.0f);
        *(unsigned short *)(projectile + 0x34) |= 0x41;
        part_spawn_ground_effect(projectile + 0x10, 4, 0x801060E0, 0, 10, D_L11_001A8F20, size * 0.3f, size, 0.0f, 0);
        part_spawn_ground_effect(projectile + 0x10, 4, -1, 1, -10, D_L11_001A8F20, size * 0.04f, size * 0.4f, 0.0f, 0);
    }
    return projectile;
}


/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void vec_l11_scale_four(char *vectors, float scale)
{
    func_00282D30_2(vectors, vectors, scale);
    func_00282D30_2(vectors + 16, vectors + 16, scale);
    func_00282D30_2(vectors + 32, vectors + 32, scale);
    func_00282D30_2(vectors + 48, vectors + 48, scale);
}

/* func_L11_00451178 is in L11_00451178-gu-g8.c. */

/* func_L11_00452450 is defined in L11_004465F8-g8.c. */

/* Finishes the flamethrower robot's frame: counts up the state timer and refreshes its shadow and light effects. */
void flamethrower_robot_finish_frame(char *object)
{
    char *state = *(char **)(object + 0x68);

    if (*(u16 *)(object + 0x96) < 0xFFFF)
        *(u16 *)(object + 0x96) = *(u16 *)(object + 0x96) + 1;
    func_338398(object, state + 0x2E0, 4.0f, 5, 1);
    func_32E480(object, object + 0x10, 1.3f, 1.0f, 1.0f, 0x4000000, 0, 1, 0);
}

/* Adds three small light effects on the flamethrower robot while it is active. */
void flamethrower_robot_add_lights(char *object)
{
    char *state = *(char **)(object + 0x68);
    float size;

    if (*(u8 *)(object + 0x95) != 0) {
        gfx_draw_two_layer_glow_sprite(object, state + 0x270, 0.125f, 0x36F6, 0x20000000, 0x20000000);
        size = 0.15f;
        gfx_draw_two_layer_glow_sprite(object, state + 0x280, size, 0x1050B0, 0x30000000, 0x20000000);
        gfx_draw_two_layer_glow_sprite(object, state + 0x290, size, 0x1050B0, 0x10000000, 0x30000000);
    }
}

/* Sets the flamethrower robot up when it appears: its turn speeds, starting pose and flags. */
void flamethrower_robot_init(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);

    *(u8 *)(state + 0x2E) = 1;
    *(short *)(state + 0x88) = 0;
    *(short *)(state + 0x2D2) = 1;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x2D8) = active;
    moby_set_controller_speed_limits(object, 0.004444444552063942f, 0.13333334028720856f,
                  0.0011635529808700085f, 0.10471977293491364f);
    if (*(u8 *)(object + 0x43) != 2)
        anim_start_blended(object, 2, 0, 0);
    *(u8 *)(object + 0x7F) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    if (*(short *)(state + 0x2D8) != 0) {
        moby_set_state(object, 4, 2);
        *(u16 *)(object + 0x34) |= 0x100;
        anim_start_blended(object, 2, 0, 0);
        func_002A05A8(object);
        moby_spawn_linked(object, 0, 2.0f, 2.0f);
    } else {
        moby_set_state(object, 3, 0);
        *(u8 *)(object + 0x31) = 1;
        *(u16 *)(object + 0x34) &= 0xFEFE;
    }
    *(short *)(state + 0x2D4) = mode;
    *(u8 *)(state + 0x6A) = 0;
    *(int *)(state + 0x200) = 0;
    part_spawn_damage_debris(object, state + 0x1F0, state + 0x20);
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        set_moby_color(object, *(u8 *)(state + 0x54), *(u8 *)(state + 0x55),
                      *(u8 *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
}

/* Puts the flamethrower robot to rest: shows a burst of effects and hides it. */
void flamethrower_robot_deactivate(char *object) {
    char *state = *(char **)(object + 0x68);
    float direction[4];

    *(short *)(state + 0x2D2) = 0;
    *(int *)(state + 0x2C4) = 0;
    if (*(u8 *)(object + 0x31) != 0) {
        SpawnExplosion(object + 0x10, 0, 5, 5, 25, 20, 10, 1,
                     0.5f, 0.0f, 1, 0, 0, 0);
        snd_play_from_class_bank(0, 0, object, 0xDF7);
        vec_random_direction(direction, 0.083333335816860199f, 0.11666667461395264f);
        FastVecAdd(direction, direction, state + 0xD0);
        part_spawn_masked_debris(object, 0xFF0, direction, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    anim_start_blended(object, 0, 0, 3);
    func_002A05A8(object);
    moby_set_state(object, 1, 0);
    *(u8 *)(object + 0x31) = 0;
    *(int *)(object + 0x98) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xEFFF) | 0x47;
}


/* func_L11_00452F30 is defined in L11_00452F30-helpers.c. */

/* Makes the flamethrower robot turn around. */
void flamethrower_robot_start_turn_around(char *object)
{
    func_32C9E0(object, 6, 3);
}

/* func_L11_004530E0 is defined in L11_004465F8-aim-004530E0-g8.c. */
