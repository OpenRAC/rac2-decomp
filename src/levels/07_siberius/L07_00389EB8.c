#include "common.h"
#include "include_asm.h"


/* func_L07_003B72E8 is in L07_003B72E8-g8.c. */

/* func_L07_003E4BD0 is in L07_003E4BD0-g8.c. */

/* func_L07_003E5070 is in L07_003E5070-g8.c. */

/* func_L07_003E5198 is in L07_003E5198-g8.c. */

/* func_L07_003E56B8 is in L07_003E56B8-g8.c. */


extern int FastDecTimer(char *);

/* Clear the two resource slots and step the state counter while it has room. */
/* Ticks two countdown timers and advances the object's frame counter. */
void entity_tick_timers(char *moby)
{
    char *vars = *(char **)(moby + 104);
    unsigned short counter;

    FastDecTimer(vars + 0x240);
    FastDecTimer(vars + 0x242);
    counter = *(unsigned short *)(moby + 0x96);
    if (counter <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) = counter + 1;
}

extern unsigned short *g_moby_l07_group_lists[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit. */
extern unsigned char *g_moby_l07_array[] __attribute__((sda));
extern int D_L07_001B22F8[] __attribute__((sda));

/* Sets the +0x244 word of every entity of the object's group state to 1. */
/* Raises an alert flag on every object in this object's group. */
void entity_set_group_alert_a(unsigned char *moby)
{
    unsigned short *member_list;
    unsigned char *member;

    if (moby[0x21] == 0xFF)
        return;
    member_list = g_moby_l07_group_lists[moby[0x21]];
    while (moby[0x21] != 0xFF && moby[0x21] <= D_L07_001B22F8[0] && member_list != 0 &&
           ((member_list != 0 && (short)member_list[-1] >= 0) || member_list == g_moby_l07_group_lists[moby[0x21]])) {
        member = g_moby_l07_array[0] + ((*member_list & 0x7FFF) << 8);
        if (member == 0)
            break;
        *(int *)(*(char **)(member + 0x68) + 0x244) = 1;
        member_list++;
    }
}

/* Counts the entities of the group whose class is 0xD1D and whose state byte is neither 0xFE nor
   0xFD into *count; returns the last entity of the group in state 8, or 0. */
/* Counts the live group members of moby class 3357 and returns the last one that is idle. */
unsigned char *entity_find_last_idle_member(int group, int *count)
{
    unsigned short *member_list;
    unsigned char *member;
    unsigned char *result;

    *count = 0;
    if (group == -1)
        return 0;
    result = 0;
    for (member_list = g_moby_l07_group_lists[group];
         (unsigned char)group != 0xFF && group <= D_L07_001B22F8[0] && member_list != 0 &&
         ((short)member_list[-1] >= 0 || member_list == g_moby_l07_group_lists[group]);
         member_list++) {
        member = g_moby_l07_array[0] + ((*member_list & 0x7FFF) << 8);
        if (member == 0)
            break;
        if (*(short *)(member + 0xAA) == 0xD1D /* moby class 3357 */ && member[0x20] != 0xFE && member[0x20] != 0xFD)
            (*count)++;
        if (member[0x20] == 8)
            result = member;
    }
    return result;
}

/* func_L07_003E5C78 is defined in L07_003E5C78-helpers.c. */

/* func_L07_003E5FA8 is in L07_003E5FA8-g8.c. */

extern int moby_transform_point_and_rotation_by_parent(char *, int, char *, char *, char *, char *);

/* Run the shared pass on both halves of the object, then again on the
   secondary half with a stack buffer when the state byte reads nine. */
/* Moves the object along with the platform it stands on. */
void entity_follow_platform(char *moby)
{
    char *vars = *(char **)(moby + 104);
    char scratch[16];

    moby_transform_point_and_rotation_by_parent(moby, *(int *)(vars + 0x260), moby + 0x10, moby + 0xF0, moby + 0x10, moby + 0xF0);
    if (*(unsigned char *)(moby + 0x20) == 9)
        moby_transform_point_and_rotation_by_parent(moby, *(int *)(vars + 0x260), vars + 0x230, scratch, vars + 0x230, scratch);
}

/* func_L07_003E61B8 is in the sibling file L07_00389EB8-g8.c: its body
   reaches a small-data global through $gp. */

/* func_L07_003E61E0 is in L07_003E61E0-g8.c. */

/* func_L07_003E69B8 is in L07_003E69B8-g8.c. */

/* func_L07_003E6E00 is in the sibling file L07_00389EB8-qcopy.c: its body
   copies a 16-byte vector, which needs the grouped-copy profile. */

/* Sets the +0x2D0 word of every entity of the object's group state to 1. */
/* Raises an alert flag on every object in this object's group. */
void entity_set_group_alert_b(unsigned char *moby)
{
    unsigned short *member_list;
    unsigned char *member;

    if (moby[0x21] == 0xFF)
        return;
    member_list = g_moby_l07_group_lists[moby[0x21]];
    while (moby[0x21] != 0xFF && moby[0x21] <= D_L07_001B22F8[0] && member_list != 0 &&
           ((member_list != 0 && (short)member_list[-1] >= 0) || member_list == g_moby_l07_group_lists[moby[0x21]])) {
        member = g_moby_l07_array[0] + ((*member_list & 0x7FFF) << 8);
        if (member == 0)
            break;
        *(int *)(*(char **)(member + 0x68) + 0x2D0) = 1;
        member_list++;
    }
}

extern int CollLine(void *,void *,int,void *,int);
extern char *moby_get_private_value_2(char *);
extern void FastVecSub(void *,void *,void *);
extern void vec_transform_by_object_or_given(void *,void *,void *,int);
extern int moby_get_attachment_rotation_angles(void *,void *,void *,void *,void *,void *);
extern int coll_apply_push_to_object(void *,void *,void *,void *,void *,void *);
extern void euler_rotation_basis(void *,void *);
extern void mat_align_to_dir(void *,void *,int);
extern void mat_get_euler_angles(void *,void *);
extern void FastVecScale(void *,void *,float);
typedef int Quad128 __attribute__((mode(TI)));
extern void matrix_mul_vec3(Quad128 *, Quad128 *, char *);
typedef struct { char pad[24]; char *object; } Collision;
extern Collision D_L07_001BF640;

/* With no platform attached, probe below the object and attach to the object hit when it is
   a platform (flag 2), recording the relative offset; otherwise carry the object along with
   the attached platform and rebuild its orientation. */
void RideMobyBelow(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    float rayStart[4] __attribute__((aligned(16)));
    float rayEnd[4] __attribute__((aligned(16)));
    float localOffset[4] __attribute__((aligned(16)));
    char *pos, *platform;

    platform = *(char **)(state + 0x338);
    if (platform == 0) {
        pos = moby + 0x10;
        qcopy(rayStart, pos);
        qcopy(rayEnd, pos);
        rayStart[2] += 2.0f;
        rayEnd[2] -= 3.0f;
        if (CollLine(rayStart, rayEnd, 0, moby, 0) && D_L07_001BF640.object != 0) {
            if (*(int *)(moby_get_private_value_2(D_L07_001BF640.object) + 0x3C) & 2) {
                *(char **)(state + 0x338) = D_L07_001BF640.object;
                FastVecSub(localOffset, pos, *(char **)(state + 0x338) + 0x10);
                vec_transform_by_object_or_given(*(char **)(state + 0x338), localOffset, localOffset, 0);
                *(float *)(state + 0x33C) = localOffset[2] - 1.0f;
                moby_get_attachment_rotation_angles(moby, *(char **)(state + 0x338), pos, moby + 0xF0,
                             state + 0x310, state + 0x320);
            }
            *(int *)(state + 0x88) |= 0x100;
        }
    } else {
        if (*(unsigned char *)(moby + 0x20) == 9 || *(unsigned char *)(moby + 0x20) == 11) {
            coll_apply_push_to_object(moby, platform, state + 0x310, state + 0x320, moby + 0x10, moby + 0xF0);
        } else {
            moby_transform_point_and_rotation_by_parent(moby, (int)platform, moby + 0x10, moby + 0xF0, moby + 0x10, moby + 0xF0);
        }
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        mat_align_to_dir(moby + 0xC0, *(char **)(state + 0x338) + 0xE0, 0);
        mat_get_euler_angles(moby + 0xC0, moby + 0xF0);
        if (*(unsigned short *)(moby + 0x34) & 0x8000)
            FastVecScale(moby + 0xD0, moby + 0xD0, -1.0f);
        if (*(unsigned char *)(moby + 0x95) == 3) {
            FastVecSub(rayStart, moby + 0x10, *(char **)(state + 0x338) + 0x10);
            vec_transform_by_object_or_given(*(char **)(state + 0x338), rayStart, rayStart, 0);
            rayStart[2] = *(float *)(state + 0x33C);
            matrix_mul_vec3((Quad128 *)rayStart, (Quad128 *)rayStart, *(char **)(state + 0x338) + 0xC0);
            *(float *)(state + 0x180) = rayStart[2] + *(float *)(*(char **)(state + 0x338) + 0x18);
        }
    }
}

/* The 16-byte vector the object keeps. */
typedef int TI128 __attribute__((mode(TI)));

extern void group_destroy_attached_parts(char *, char *);

extern void SetDeathBits(char *, int, int);

extern void matrix_mul_vec3(TI128 *, TI128 *, char *);

extern void FastVecAdd(TI128 *, TI128 *, char *);

extern char *SpawnExplosion(TI128 *, int, int, int, int, int, int, int, float, float, int, int, int,
                          int);

extern int PlayMobySound(int, int, char *);

extern void vec_scale_to_length(TI128 *, TI128 *, float);

extern void part_spawn_masked_debris(char *, int, TI128 *, float, float, float, float, int);

/* Arm the object's mode, then set up its position and hand it to the launcher.
   func_002B0A68's integer mask is its last parameter, and this compiler sets the
   arguments up in parameter order: the mask's store then comes after the four
   float copies, in the call's delay slot, as the retail has it. */
/* Plays the entity's death effects: an explosion, a sound and a burst of flying pickups. */
void entity_spawn_death_effects(char *moby)
{
    char *vars;
    TI128 burst_pos[1];
    TI128 impulse;

    vars = *(char **)(moby + 0x68);
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
    *(int *)(moby + 0x98) = 0;
    group_destroy_attached_parts(moby, vars + 0x330);
    SetDeathBits(moby, 0, 3);
    burst_pos[0] = 0;
    ((float *)burst_pos)[2] = 0.75f;
    matrix_mul_vec3(burst_pos, burst_pos, moby + 0xC0);
    FastVecAdd(burst_pos, burst_pos, moby + 0x10);
    SpawnExplosion(burst_pos, 0, 25, 20, 20, 20, 45, 1, 0.6f, 20.0f, 1, 0, 0, *(int *)(vars + 0x338));
    PlayMobySound(6, 0, moby);
    vec_scale_to_length(&impulse, vars + 0x1C0, 0.05000000447034836f);
    part_spawn_masked_debris(moby, 1016, &impulse, 3.0f, 6.0f, 3.0f, 6.0f, 255);
}

extern void moby_set_state(int, int, int);

extern int math_random_int_range(int, int);

extern void *part_spawn_between_points_depth_push(char *, int, int, char *, int, int, int);

/* Arm the object's mode ten and hand it to the shared launcher. */
/* Throws a group member at a target and switches it to its launched state. */
void entity_launch_member_a(char *moby, int from_pos, int to_pos, int owner, int flag)
{
    int random_value;

    moby_set_state(moby, 10, -1);
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
    random_value = math_random_int_range(0x2D, 0x4B);
    part_spawn_between_points_depth_push(moby, from_pos, to_pos, moby + 0xF0, random_value, owner, flag);
}

/* func_L07_003EA900 is in L07_003EA900-g8.c. */

/* func_L07_003EB2C0 is in L07_003EB2C0-g8.c. */

extern int math_fast_float_d(char *);

extern void value_set_and_smooth(char *, char *, int, int, float);

extern int D_L07_001C9780;

/* Ticks two countdown timers, advances the frame counter and carries the object on its
   platform. */
void entity_tick_timers_ride_platform(char *moby)
{
    char *vars = *(char **)(moby + 104);
    unsigned short counter;

    math_fast_float_d(vars + 0x2D4);
    math_fast_float_d(vars + 0x2D8);
    counter = *(unsigned short *)(moby + 0x96);
    if (counter <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) = counter + 1;
    if (D_L07_001C9780 != 0)
        entity_ride_platform_snap_height(moby);
    value_set_and_smooth(moby, vars + 0x230, 5, 1, 2.5f);
}

/* Twin of func_L07_003E6F40. */
/* Raises an alert flag on every object in this object's group. */
void entity_set_group_alert_c(unsigned char *moby)
{
    unsigned short *member_list;
    unsigned char *member;

    if (moby[0x21] == 0xFF)
        return;
    member_list = g_moby_l07_group_lists[moby[0x21]];
    while (moby[0x21] != 0xFF && moby[0x21] <= D_L07_001B22F8[0] && member_list != 0 &&
           ((member_list != 0 && (short)member_list[-1] >= 0) || member_list == g_moby_l07_group_lists[moby[0x21]])) {
        member = g_moby_l07_array[0] + ((*member_list & 0x7FFF) << 8);
        if (member == 0)
            break;
        *(int *)(*(char **)(member + 0x68) + 0x2D0) = 1;
        member_list++;
    }
}

/* func_L07_003EB838 is in L07_003EB838.c. */

/* Plays the entity's death effects: an explosion, a sound and a burst of flying pickups. */
void entity_spawn_death_effects_b(char *moby)
{
    float position[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    char *state = *(char **)(moby + 0x68);
    *(int *)(moby + 0x98) = 0;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xefff;
    SetDeathBits(moby, 0, 3);
    *(TI128 *)position = 0;
    position[2] = 0.75f;
    matrix_mul_vec3((TI128 *)position, (TI128 *)position, moby + 0xc0);
    FastVecAdd((TI128 *)position, (TI128 *)position, moby + 0x10);
    SpawnExplosion((TI128 *)position, 0, 25, 20, 20, 20, 45, 1, 0.6f, 20.0f,
                 1, 0, 0, *(int *)(state + 0x314));
    PlayMobySound(9, 0, moby);
    vec_scale_to_length((TI128 *)direction, (TI128 *)(state + 0x1c0), 0.0500000045f);
    part_spawn_masked_debris(moby, 0x7f8, (TI128 *)direction, 3.0f, 6.0f, 3.0f, 6.0f, 0xff);
}


/* Twin of func_L07_003E7380 with the mode eight instead of ten. */
/* Throws a group member at a target and switches it to its launched state. */
void entity_launch_member_b(char *moby, int from_pos, int to_pos, int owner, int flag)
{
    int random_value;

    moby_set_state(moby, 8, -1);
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
    random_value = math_random_int_range(0x2D, 0x4B);
    part_spawn_between_points_depth_push(moby, from_pos, to_pos, moby + 0xF0, random_value, owner, flag);
}

/* func_L07_003EE3B0 is in L07_003EE3B0-g8.c. */

extern void moby_set_state(int, int, int);

extern int IsPointInCuboid(int, int);

extern void moby_set_group_enabled(int, int);

extern char g_hero_position[];

/* Per-frame update for moby class 3388: when each of up to eight conditions is met, it
   triggers the linked object once. */
void timed_trigger_slots_update(char *moby)
{
    int *vars = *(int **)(moby + 104);
    int *target_ids;
    int *condition_ids;
    int i;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        condition_ids = vars;
        target_ids = vars + 8;
        for (i = 0; i < 8; i++) {
            if (target_ids[i] != -1) {
                if (IsPointInCuboid((int)g_hero_position, *condition_ids) != 0) {
                    moby_set_group_enabled(target_ids[i], 1);
                    target_ids[i] = -1;
                }
            }
            condition_ids++;
        }
        break;
    }
}

/* func_L07_003EE708 is matched in L07_003EE708-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* Attaches this object to a parent object at a given offset and stores its starting position
   and facing. */
void moby_attach_to_parent(char *moby, char *parent, TI128 *offset_pos, TI128 *second_vec)
{
    TI128 offsets[2];
    TI128 *second = &offsets[1];
    char *vars;
    unsigned short flags;

    offsets[0] = *offset_pos;
    *second = *second_vec;

    flags = *(unsigned short *)(moby + 0x34);
    *(unsigned short *)(moby + 0x34) = (flags & 0xFFBE) | 0x1000;

    vars = *(char **)(moby + 0x68);
    *(int *)(moby + 0x98) = *(int *)(*(int *)(moby + 0x24) + 0x10);
    moby_set_state((unsigned char *)moby, 2, -1);

    *(unsigned char *)(moby + 0x30) = 0xFF;
    *(short *)(moby + 0x32) = 0xFF;

    *(int *)(vars + 0x110) = (int)parent;

    matrix_mul_vec3((TI128 *)(moby + 0x10), &offsets[0], parent + 0xC0);
    FastVecAdd((TI128 *)(moby + 0x10), (TI128 *)(moby + 0x10),
                  (char *)(*(int *)(vars + 0x110) + 0x10));

    flags = *(unsigned short *)(moby + 0x34);
    *(unsigned short *)(moby + 0x34) = flags & 0xEFFF;

    qcopy(vars + 0xF0, moby + 0x10);
    qcopy(vars + 0xD0, second);
}


/* func_L07_003EECE0 is in L07_003EECE0.c. */

/* Play the fixed mode/value pair for this object. */
void entity_set_state_five(char *moby)
{
    moby_set_state(moby, 5, -1);
}

/* func_L07_003EEE28 is defined in L07_003EEE28-g8.c. */

extern float func_002E5460(int);

extern void func_003109C8(char *, int, int);

/* Store the mode value and the inverse of the launch factor. */
/* func_L07_003EF1E0 is matched in L07_003EF1E0.c (built with -g). */

/* func_L07_003F3E80 is in L07_00389EB8-trail-g8.c (-G8 with -frac2-hazard-labels). */

/* func_L07_003F43E0 is in the sibling file L07_00389EB8-g8.c: its body
   reads small-data globals through $gp. */
