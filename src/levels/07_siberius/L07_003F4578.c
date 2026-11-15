#include "include_asm.h"
#include "common.h"

/* Quadword copies and clears, the spelling that reaches lq/sq. */
typedef int TI128 __attribute__((mode(TI)));

/* func_L07_003F4578 is defined in L07_003F4578-ring-g8.c. */

extern u8 D_L07_001B31AF __attribute__((sda));

/* Clears a block of 16 flag bytes to zero. */
void flag_block_clear(void)
{
    u8 *p;
    s32 i;

    for (i = 15, p = &D_L07_001B31AF; i >= 0; i--) {
        *p = 0;
        p--;
    }
}

/* func_L07_003F4970 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */

/* func_L07_003F4B08 is defined in L07_003F4B08-copy.c. */

/* func_L07_003F4C18 is defined in L07_003F4C18-copy.c. */

/* func_L07_003F4CC0 is defined in L07_003F4578-beam-g8.c. */

/* func_L07_003F59C0 is defined in L07_003F59C0-g8.c. */

/* func_L07_003F5B50 is defined in L07_003F5B50.c. */

/* func_L07_003F6328 is defined in L07_003F6328.c. */

extern void func_3109C8(u8 *a, s32 b, s32 c);

extern f32 func_2E49C8(f32 a, f32 b);

extern f32 func_2E5360(f32 a, f32 b);

extern f32 D_L07_00189E20[];

extern void swing_update_yaw(u8 *a0, f32 x);

/* Starts the swinging turret: switches to state 2, picks which way to turn toward the player and aims it. */
void turret_start_swinging(u8 *moby)
{
    u8 *vars;
    f32 side;

    func_3109C8(moby, 2, -1);
    vars = *(u8 **)(moby + 0x68);
    *(u8 *)(moby + 0x7F) = 0;
    *(f32 *)(vars + 0x20) = (f32)*(s16 *)(vars + 0x24);
    side = func_2E5360(func_2E49C8(D_L07_00189E20[0x20] - *(f32 *)(moby + 0x10),
                                D_L07_00189E20[0x21] - *(f32 *)(moby + 0x14)),
                    *(f32 *)(vars + 0x60));
    if (side > 0.0f) {
        *(f32 *)(vars + 0x54) = -1.5707964f;
    } else {
        *(f32 *)(vars + 0x54) = 1.5707964f;
    }
    swing_update_yaw(moby, 0.0f);
}

extern u16 *g_moby_l07_group_lists[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit. */
extern u8 *g_moby_l07_array[] __attribute__((sda));
extern s32 D_L07_001B22F8[] __attribute__((sda));

extern s32 math_random_int_below(s32 n);

extern s32 math_fast_float_d(s32 *counter);

/* Picks at random one of the group's entities that are in state 1: counts them, draws an index
   below the count, then walks the list again stepping the index down (func_00282948) until it
   runs out. Returns 0 when there is none. */
u8 *group_pick_random_active_entity(s32 group)
{
    u16 *id_ptr;
    u16 *id_ptr_b;
    u8 *entity;
    s32 active_count = 0;
    s32 pick_index;

    for (id_ptr = g_moby_l07_group_lists[group];
         (group & 0xFF) != 0xFF && group <= D_L07_001B22F8[0] && id_ptr != 0 &&
         ((s16)id_ptr[-1] >= 0 || id_ptr == g_moby_l07_group_lists[group]);
         id_ptr++) {
        entity = g_moby_l07_array[0] + ((*id_ptr & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity[0x20] == 1)
            active_count++;
    }
    if (active_count == 0)
        return 0;
    pick_index = math_random_int_below(active_count);
    for (id_ptr_b = g_moby_l07_group_lists[group];
         (group & 0xFF) != 0xFF && group <= D_L07_001B22F8[0] && id_ptr_b != 0 &&
         ((s16)id_ptr_b[-1] >= 0 || id_ptr_b == g_moby_l07_group_lists[group]);
         id_ptr_b++) {
        entity = g_moby_l07_array[0] + ((*id_ptr_b & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity[0x20] == 1 && math_fast_float_d(&pick_index) != 0)
            return entity;
    }
    return 0;
}

/* func_L07_003F67B8 is defined in L07_003F67B8-copy.c. */

/* func_L07_003F68F0 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */

/* func_L07_003F6960 is defined in L07_003F4578-g8.c. */

/* func_L07_003F6C40 is defined in L07_003F6C40.c. */

/* func_L07_003F6CF0 is defined in L07_003F4578-spin-g8.c. */

/* func_L07_003F6DC0 is defined in L07_003F6DC0-copy.c. */

/* func_L07_003F7048 is defined in L07_003F7048-g8.c. */

/* An entity node: the flag word at 0x34, the counter at 0x98, two children. */
typedef struct SibNode SibNode;

struct SibNode {
    u8 pad00[0x34];
    u16 flags34;
    u8 pad36[0x68 - 0x36];
    SibNode *f68;
    u8 rest68[0x98 - 0x6C];
    s32 f98;
    u8 rest9c[0x410 - 0x9C];
    SibNode *f410;
    SibNode *f414;
};

/* Resets the object and its two child objects: sets their flags and clears their counters. */
void boss_reset_with_children(SibNode *moby)
{
    SibNode *vars = moby->f68;

    moby->flags34 = (moby->flags34 | 0x41) & 0xEFFF;
    moby->f98 = 0;
    vars->f410->flags34 |= 0x41;
    vars->f410->flags34 &= 0xEFFF;
    vars->f410->f98 = 0;
    vars->f414->flags34 |= 0x41;
    vars->f414->flags34 &= 0xEFFF;
    vars->f414->f98 = 0;
}

/* func_L07_003F7968 is defined in L07_003F7968-g32.c. */

/* Returns the boss's current attack mode. */
u8 *boss_get_attack_mode(u8 *moby)
{
    return *(u8 **)(*(u8 **)(moby + 0x68) + 0x420);
}

/* func_L07_003F7BF0 is defined in L07_003F7BF0-g8.c. */

extern void moby_update_ground_check(u8 *a);

extern void func_002A0F48(u8 *a);

extern void moby_transform_joint_point(u8 *a, s32 b, void *c);

extern void copy_matrix3x4(u8 *a, void *b);

/* func_L07_003F8010 is defined in L07_003F8010-copy.c. */

/* func_L07_003F80B8 is defined in L07_003F4578-follow-g8.c. */

/* func_L07_003F8430 is defined in L07_003F8430-g8.c. */

/* func_L07_003F8780 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */

extern void FastVecSub(u8 *a, u8 *b, u8 *c);

extern void vec_transform_by_object_or_given(u8 *a, u8 *b, u8 *c, s32 d);

/* func_L07_003F8828 is defined in L07_003F8828-copy.c. */

extern void matrix_mul_vec3(u8 *a, u8 *b, u8 *c);

extern void FastVecAdd(u8 *a, u8 *b, u8 *c);

/* func_L07_003F8898 is defined in L07_003F8898-copy.c. */


/* func_L07_003F8AB0 is defined in L07_003F4578-qcopy.c (this unit needs the grouped quadword copy). */

extern void SpawnBallisticMoby(u8 *a, u8 *b, void *c, void *d, f32 e);


extern u8 *moby_find_active_in_group(u8 *a);

extern void homing_bomb_init(u8 *a, u8 *b, void *c, f32 d);

/* One 128-byte record, its float field read by the measured index. */
typedef struct {
    u8 pad38[0x38];
    f32 f38;
    u8 rest[128 - 0x3C];
} SibRec128;

extern SibRec128 *D_L07_001B23CC;


/* func_L07_003F8D90 is defined in L07_003F8D90.c. */

extern void anim_start_blended(u8 *a0, s32 a1, s32 a2, s32 a3);

/* Picks the boss's idle animation (one set while no attack mode is active, another while one is) and changes it only if it differs. */
void boss_select_idle_anim(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u32 *)(vars + 0x420) == 0) {
        if (*(u8 *)(moby + 0x43) != 2) {
            anim_start_blended(moby, 2, 0, 10);
        }
        return;
    }
    if (*(u8 *)(moby + 0x43) != 8) {
        anim_start_blended(moby, 8, 0, 10);
    }
}

/* Picks the boss's attack animation (one set while no attack mode is active, another while one is) and changes it only if it differs. */
void boss_select_attack_anim(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u32 *)(vars + 0x420) == 0) {
        if (*(u8 *)(moby + 0x43) != 3) {
            anim_start_blended(moby, 3, 0, 10);
        }
        return;
    }
    if (*(u8 *)(moby + 0x43) != 9) {
        anim_start_blended(moby, 9, 0, 10);
    }
}

extern u8 D_001A7BD0 __attribute__((sda));

extern void UpdateCuboidTriggeredMoby(u8 *a0);

/* Updates the object with the standard code, unless a global flag is set, in which case it only marks the object. */
void moby_update_unless_paused(u8 *moby)
{
    if (D_001A7BD0 != 0) {
        *(u16 *)(moby + 0x34) |= 0x2;
        return;
    }
    UpdateCuboidTriggeredMoby(moby);
}

extern void func_310D80(void *a, f32 b, f32 c);

extern f32 func_2E4280(f32 a);

extern f32 func_310B30(f32 a, f32 b);

extern void func_31AFD8(void *a, void *b, f32 c, f32 d, f32 e);

extern void func_335848(void *a, void *b, s32 c);

/* The two shared level floats; `sda` gives the retail's `lui %hi ; swc1 %lo($at)` form. */
extern f32 D_L07_001AA698 __attribute__((sda));

extern f32 D_L07_001B3198 __attribute__((sda));

/* Runs the object's own 200 steps: each step advances the shared record's third
   float, then the three angles are computed and handed to the shared passes. */
/* Throws 200 sparks out of the object in random directions. */
void part_l07_spawn_spark_burst(u8 *moby)
{
    f32 spark_velocity[4];
    f32 spark_pos[4];
    s32 i;
    f32 random_speed;
    f32 random_y;
    f32 random_x;

    D_L07_001B3198 = D_L07_001AA698;
    D_L07_001AA698 = 0.99f;
    for (i = 0xC7; i >= 0; i--) {
        func_310D80(spark_pos, 1.0f / 60.0f, 0.23333335f);
        spark_pos[2] = func_2E4280(spark_pos[2]) + 1.0f / 12.0f;
        random_x = func_310B30(-5.0f, 5.0f);
        random_y = func_310B30(-5.0f, 5.0f);
        random_speed = func_310B30(10.0f, 25.0f);
        func_31AFD8(moby, spark_velocity, random_x, random_y, random_speed);
        func_335848(spark_velocity, spark_pos, 0x1E0);
    }
}

/* func_L07_0040E198 is defined in L07_0040E198-g8.c. */

/* func_L07_0040E980 is defined in L07_0040E980-g8.c. */

/* func_L07_0040EC08 is defined in L07_0040EC08-g8.c. */


extern void func_338D68(void *a, s32 b, void *c, void *d, s32 e, f32 f);

extern f32 func_2E4508(void *a, void *b);

/* Works out the heading and tilt of a path at a given distance along it, by looking a little behind and a little ahead. */
void path_compute_heading_and_tilt(s32 *path, f32 *angles, f32 distance, f32 span)
{
    f32 ahead_point[4];
    f32 behind_point[4];
    f32 scratch[4];
    f32 behind = distance - span;
    f32 ahead;

    if (behind < 0.0f)
        behind = behind + (f32)path[0];
    ahead = distance + span;
    if ((f32)path[0] < ahead)
        ahead = ahead - (f32)path[0];
    func_338D68(path, 1, behind_point, scratch, 0, behind);
    func_338D68(path, 1, ahead_point, scratch, 0, ahead);
    angles[2] = func_2E49C8(behind_point[0] - ahead_point[0], behind_point[1] - ahead_point[1]);
    angles[1] = -func_2E49C8(func_2E4508(ahead_point, behind_point), behind_point[2] - ahead_point[2]);
}

/* func_L07_0040F0D0 is defined in L07_0040F0D0-g32.c. */

/* The object's state record up to its three group words (-1 means none). Indexing the array
   member is the spelling that gives retail's address arithmetic (the +0x94 base as a sum of its
   own, the group word read again inside the walk); a cast sum or a pointer variable does not. */
typedef struct {
    u8 pad[0x94];
    s32 groups[3];
} GroupState;

/* Walks the id list of each of the object's three groups, stopping at the first id with no
   entity; the walk itself does nothing. */
void group_walk_entities(u8 *a0)
{
    GroupState *state = *(GroupState **)(a0 + 0x68);
    s32 i;
    u16 *p;
    u8 *e;

    for (i = 0; i < 3; i++) {
        if (state->groups[i] == -1)
            continue;
        for (p = g_moby_l07_group_lists[state->groups[i]];
             (state->groups[i] & 0xFF) != 0xFF && state->groups[i] <= D_L07_001B22F8[0] && p != 0 &&
             ((s16)p[-1] >= 0 || p == g_moby_l07_group_lists[state->groups[i]]);
             p++) {
            e = g_moby_l07_array[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
        }
    }
}

/* func_L07_0040F6B8 is defined in L07_003F4578-geometry-g8.c. */

/* func_L07_0040F760 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */


typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) Vec4;
extern Vec4 D_L07_002A0100[][18];
extern void func_2E4310(void *a, void *b, void *c);
extern void func_2E4398(void *a, void *b, f32 c);
extern f32 func_2E44D0(void *a, void *b);

/* For each of three paths, finds the middle of its points and stores it after the last point, along with the largest distance of any point from it. */
void path_compute_centers_and_radii(void)
{
    s32 i, point_count, j, test_index, sum_index;
    f32 center[4];
    f32 distance;

    for (i = 0; i < 3; i++) {
        point_count = 0;
        test_index = 0;
        sum_index = 0;
        qzero(center);
        /* separate counters for the test (testIndex) and the call (sumIndex); pointCount stays for after the loop */
        while (D_L07_002A0100[i][test_index].w == 1.0f) {
            func_2E4310(center, center, &D_L07_002A0100[i][sum_index]);
            point_count++;
            sum_index++;
            test_index++;
        }
        func_2E4398(&D_L07_002A0100[i][point_count], &D_L07_002A0100[i][point_count], 1.0f / point_count);
        D_L07_002A0100[i][point_count].w = 0.0f;
        for (j = 0; j < point_count; j++) {
            distance = func_2E44D0(&D_L07_002A0100[i][j], &D_L07_002A0100[i][point_count]) + 4.0f;
            if (D_L07_002A0100[i][point_count].w < distance)
                D_L07_002A0100[i][point_count].w = distance;
        }
    }
}

extern u8 *D_L07_001B1F40 MACRO_ADDR;
extern s32 *D_L07_001FDEC0[];
extern void func_2E4DD8(void *, void *);
extern void func_2E47F8(void *, void *, void *);

/* Turns the stored path points into world positions using the object's own matrix and position, and saves them for its record. */
void path_upload_points_to_world(u8 *moby, s32 index)
{
    f32 matrix[16];
    f32 end_point[4];
    u8 *state = *(u8 **)(moby + 0x68);
    s32 *dest;
    u8 *record;
    f32 radius;
    s32 i;

    if (*(s32 *)(state + 0xBC) == -1)
        return;
    record = D_L07_001B1F40 + *(s32 *)(state + 0xBC) * 0x30;
    dest = D_L07_001FDEC0[**(s32 **)(record + 0x3C)];
    *dest = 0;
    func_2E4DD8(matrix, moby + 0xC0);
    qcopy(matrix + 12, moby + 0x10);
    matrix[15] = 1.0f;
    for (i = 0; (D_L07_002A0100[index] + i)->w == 1.0f; i++) {
        func_2E47F8(dest + 4 + i * 4, D_L07_002A0100[index] + i, matrix);
        (*dest)++;
    }
    qcopy(end_point, &D_L07_002A0100[index][*dest]);
    radius = end_point[3];
    end_point[3] = 1.0f;
    func_2E47F8(D_L07_001B1F40 + (*(s32 *)(state + 0xBC) * 0x30 + 0x20), end_point, matrix);
    {
        u8 *table = D_L07_001B1F40;
        table += *(s32 *)(state + 0xBC) * 0x30;
        ((f32 *)table)[11] = radius;
    }
}

/* func_L07_0040FC88 is defined in L07_0040FC88-g16.c. */

/* func_L07_00410588 is defined in L07_00410588-snapshot.c. */

extern void euler_rotation_basis(u8 *a, u8 *b);

extern void moby_update_attached_transforms(u8 *a, u8 *b);

/* Builds the object's matrix from its angles, then updates its attached record. */
void moby_build_matrix(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    euler_rotation_basis(moby + 0xC0, moby + 0xF0);
    moby_update_attached_transforms(moby, vars + 0x1B0);
}

/* func_L07_00410700 is defined in L07_00410700-g8.c. */

/* func_L07_00410930 is defined in L07_003F4578-g8.c (it takes the address of $gp data). */

/* func_L07_00410C50 is defined in L07_00410C50.c. */
