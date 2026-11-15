#include "include_asm.h"
#include "names.h"

typedef signed char s8;

typedef unsigned char u8;

typedef unsigned short u16;

typedef signed short s16;

typedef signed int s32;

typedef unsigned int u32;

typedef float f32;

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char b0[16];
    char b1[16];
    char b2[16];
    char b3[16];
    int k0, k1, k2, k3;
    int z80, z84, z88;
    float f92, f96;
    int z100;
    float f104, f108;
    long long v112, v120, v128, v136;
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float v192, v196, v200, v204;
    float v208, f212, f216, v220;
} LOC_L09_003AF508;

typedef unsigned long long u64;


extern unsigned int D_L09_001FE6C0[];

extern unsigned int D_L09_001FB560[];

extern char *D_L09_001B285C __attribute__((sda));

extern int moby_get_kind_slot(u8 *object);

extern u8 *g_hero_moby;

extern int path_follow_nodes(char *object, unsigned int entry);

extern int path_set_follower_nodes(void *object, void *entry, int count, int value);

extern int vec_find_point_nearest_wanted_distance(char *object, char *entry, float base);

extern float path_l01_compute_segment_lengths(void *entry);

extern int AdvancePointAlongPolyline(char *object, unsigned int entry, void *out, int current, int direction, float step);

extern void FastVecAdd(char *first, char *second, char *third);

extern void FastVecCross(char *first, char *second, char *third);

extern void vec_scale_to_length(char *dst, char *src, float x);

extern float math_random_angle(void);

extern void math_build_axis_angle_quat(void *a, void *b, float f);

extern void FastVecScale(char *a, char *b, float f);

extern void lerp_vector(char *dst, char *src, char *extra, float f);

extern void vec_rotate_by_quaternion(char *a, char *b, char *c);

extern float fast_subtract_rotations(float a, float b);

extern void gfx_add_draw_callback_first(char *table, char *object);

extern char D_L09_003AEF78[];

extern void sprite_reset_large_record(void *p);

extern long long GetEffectTextureDescriptor(int id);

extern int math_random_int_range(int lo, int hi);

extern float mat_fast_helper_a(float x, float y);

extern float func_00282E80_1(char *a, char *b);

extern float math_random_angle(void);

extern void euler_to_matrix(void *dst, void *src);

extern float math_random_float_range(float lo, float hi);

extern void draw_world_quad(void *dst, void *src, int flag);

extern char D_L09_001BF98C0[];

extern char D_L09_001B98C0[];

extern void func_003AEFD0(void *out);

extern float func_00316AC0(float lo, float hi);

extern void func_002EA4D0(char *dst, char *src, char *extra, float f);

extern int func_002E2828(int id);

extern int func_001163B0(void);

extern int func_00316A68(int lo, int hi);

extern float func_002EAB28(float a, float b);

extern float func_00316B88(float f);

extern void func_002EACF0(char *dst, char *src);

extern void func_002E6C68(char *dst, char *src, int flag);

extern void part_spawn_spark_strips(char *object, char *v);

extern void func_0031F728(char *object, char *a1, char *a2, float f1, float f2, float f3);

extern void func_0031F7E0(char *object, char *a1, char *a2, float f1, float f2, float f3);

extern float func_002EB478(float a, float b);

extern int func_L09_0033E8B0_1(char *object, int index, void *out, int a, int b, float f);

extern int path_move_moby_turn_speed(char *object, void *buf, float f);

extern float func_00282E48_2(char *a, int b);

extern int func_L06_00382850_1(char *object, unsigned int entry, float value);

extern int func_002B6228_1(char *object, unsigned int entry, int value, int flag);

extern void FastDecTimer(void *p);

extern void vec_fast_helper_a(void *p);

extern void PlayMobySound(int a, int b, char *c);

extern void SetDeathBits(char *a, int b, int c);

extern void moby_mark_spawned(void *entry);

extern void SpawnExplosion(void *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
                          float f1, float f2, int s1, int s2, int s3, int s4);

extern float fast_vec_dist(char *a, char *b);

extern void moby_update_ground_check(void *object);

extern char D_L09_001B9A00[];

extern void math_fast_float_d(void *a0);

extern void get_moby_color(char *object, int *out0, int *out1, int *out2);

extern void set_moby_color(char *object, int a, int b, int c);

extern void moby_mark_spawned(void *entry);

extern float vec_distance_xy(char *a, int b);

extern int func_L09_0033E690_1(char *object, int index, float value);

extern int func_L09_00329178_1(char *object, int index, int value, int flag);

extern void ref_L09_003F8858_00(char *object, int value);

/* index -> entry of a per-level table; a live entry's first word is a one-based id. */



/* Returns 1 if the object is the hero or is in one of a few special states, otherwise 0. */
int moby_is_hero_or_special(u8 *object)
{
    int state;

    if (object == g_hero_moby)
        return 1;
    state = moby_get_kind_slot(object);
    if (state == 255 || state == 10 || state == 18 || state == 53 || state == 14
        || state == 17 || state == 12)
        return 1;
    return 0;
}

/* Looks up the entry for an index in the level table and checks it against the object. Returns 0 if there is no entry. */
int path_check_entry_for_moby(char *object, int index)
{
    unsigned int entry;

    if (index == -1)
        return 0;
    entry = D_L09_001FE6C0[index];
    if (entry == 0)
        return 0;
    return path_follow_nodes(object, entry);
}

/* Looks up the entry for an index in the level table and applies a count and a value to it for the object. Returns 0 if there is no entry. */
int path_apply_entry_to_moby(char *object, int index, int count, int value)
{
    unsigned int entry;

    if (index == -1)
        return 0;
    entry = D_L09_001FE6C0[index];
    if (entry == 0)
        return 0;
    return path_set_follower_nodes(object, (void *)entry, count, value);
}

/* func_L09_003364E0 is matched in its own unit, src/levels/shared/L09_003364E0.c (default flags). */

/* func_L09_0033E658 is matched in L09_0033E658-rc2.c. */


/* Looks up the entry for an index in the level table and measures the object against it. Returns -1 if there is no entry. */
int path_measure_moby_against_entry(char *object, int index, float base)
{
    unsigned int entry;

    if (index == -1)
        return -1;
    entry = D_L09_001FE6C0[index];
    if (entry == 0)
        return -1;
    return vec_find_point_nearest_wanted_distance(object, (char *)entry, base);
}

/* Looks up the entry for an index in the level table and returns its length. Returns -1 if there is no entry. */
float path_get_entry_length(int index)
{
    unsigned int entry;

    if (index == -1)
        return -1.0f;
    entry = D_L09_001FE6C0[index];
    if (entry == 0)
        return -1.0f;
    return path_l01_compute_segment_lengths((void *)entry);
}

/* Looks up the entry for an index in the level table and steps one point along it in the given direction. Returns -1 if there is no entry. */
int path_step_along_entry(char *object, int index, void *out, int current, int direction, float step)
{
    unsigned int entry;

    if (index == -1)
        return -1;
    entry = D_L09_001FE6C0[index];
    if (entry == 0)
        return -1;
    return AdvancePointAlongPolyline(object, entry, out, current, direction, step);
}

/* func_L09_0037FCE8 is defined in L09_0037FCE8-g8.c. */


/* func_L09_003A01D8 is matched in src/levels/shared/L09_002B7238-g8.c (-G8). */

/* func_L09_003A06B0 is defined in L09_003A06B0-helpers.c. */

/* func_L09_003AE8C8 is matched in its own unit, src/levels/shared/L09_003AE8C8-g8.c (-g). */

/* func_L09_003AEA88 is matched in its own unit, src/levels/shared/L09_003AEA88.c (default flags). */

/* Sets up the starting direction and size of a new projectile. */
void projectile_init_direction(char *object)
{
    char *vars = *(char **)(object + 104);
    char *position = object + 0x10;

    FastVecAdd(vars, position, vars + 0x30);
    FastVecCross(vars, vars, position);
    vec_scale_to_length(vars, vars, 0.25f);
    *(float *)(vars + 0x5C) = math_random_angle();
}

/* rebuilds the object's orientation matrix from its stored angles and hands it to the stage */
void projectile_update_orientation(char *object)
{
    char *vars = *(char **)(object + 0x68);
    float matrix[4];
    char *position = object + 0x10;
    char *basis = vars + 0x10;

    vec_scale_to_length((char *)matrix, vars + 0x30, 1.0f);
    math_build_axis_angle_quat(matrix, matrix, *(float *)(vars + 0x5C));
    FastVecScale(basis, vars, *(float *)(vars + 0x50));
    vec_rotate_by_quaternion(basis, basis, (char *)matrix);
    *(float *)(vars + 0x20) = -*(float *)(vars + 0x10);
    *(float *)(vars + 0x24) = -*(float *)(vars + 0x14);
    *(float *)(vars + 0x28) = -*(float *)(vars + 0x18);
    FastVecAdd(basis, position, basis);
    FastVecAdd(vars + 0x20, position, vars + 0x20);
    *(float *)(vars + 0x5C) = fast_subtract_rotations(*(float *)(vars + 0x5C), 0.3141593039035797f);
    gfx_add_draw_callback_first(D_L09_003AEF78, object);
}

/* func_L09_003AF060 is defined in L09_003AF060.c. */

/* the effect's record: four blocks, four colour words, a matrix and a vector */

/* measures the object against the level's target point and hands the effect to the stage */
void part_spawn_targeted_spark_quad(char *object)
{
    LOC_L09_003AF508 local;
    char *frame;
    char *data;
    float len;
    float scale;
    int color;

    frame = *(char **)(object + 0x68);
    sprite_reset_large_record(&local);
    local.v120 = GetEffectTextureDescriptor(11);
    local.v128 = 0xFF9000000260LL;
    local.v136 = 0x0000008000000048LL;
    local.v112 = 0;
    color = (math_random_int_range(0x20, 0x30) << 24) + 0x103080;
    local.k0 = local.k1 = local.k2 = local.k3 = color;
    data = D_L09_001BF98C0;
    local.v220 = 0.0f;
    local.f216 = mat_fast_helper_a(*(float *)(data + 0x140) - *(float *)(object + 0x10),
                               *(float *)(data + 0x144) - *(float *)(object + 0x14));
    len = func_00282E80_1(object + 0x10, data + 0x140);
    local.f212 = -mat_fast_helper_a(len, *(float *)(data + 0x148) - *(float *)(object + 0x18));
    local.v208 = math_random_angle();
    euler_to_matrix(&local.m00, &local.v208);
    local.v192 = *(float *)(object + 0x10);
    local.v196 = *(float *)(object + 0x14);
    local.v200 = *(float *)(object + 0x18);
    local.v204 = 1.0f;
    scale = math_random_float_range(0.35f, 0.45f) * *(float *)(frame + 0x50);
    FastVecScale((char *)&local.b0, (char *)&local.b0, scale);
    FastVecScale((char *)&local.b1, (char *)&local.b1, scale);
    FastVecScale((char *)&local.b2, (char *)&local.b2, scale);
    FastVecScale((char *)&local.b3, (char *)&local.b3, scale);
    draw_world_quad(&local, &local.m00, 0);
}

/* builds the effect's frame, colour word and query box, then hands the result to the stage */
void part_spawn_targeted_trail_sparks(char *object)
{
    LOC_L09_003AF508 local;
    float pos[3];
    char *frame = *(char **)(object + 0x68);
    char *data;
    float len;
    float scale;
    int color;

    sprite_reset_large_record(&local);
    lerp_vector(pos, frame + 0x10, frame + 0x20, math_random_float_range(0.0f, 1.0f));
    pos[0] += math_random_float_range(-0.1f, 0.1f) * *(float *)(frame + 0x50);
    pos[1] += math_random_float_range(-0.1f, 0.1f) * *(float *)(frame + 0x50);
    pos[2] += math_random_float_range(-0.1f, 0.1f) * *(float *)(frame + 0x50);
    local.v120 = GetEffectTextureDescriptor(11);
    local.v128 = 0xFF9000000260LL;
    local.v112 = 0;
    local.v136 = 0x0000008000000040LL | ((long long)(func_001163B0() % 2 + 1) << 2);
    color = math_random_int_range(0x40, 0x7F) << 24;
    local.v220 = 0.0f;
    local.k0 = local.k1 = local.k2 = local.k3 = color + 0x103080;
    data = D_L09_001B98C0;     /* the level's target point: three floats at +0x140 */
    local.f216 = mat_fast_helper_a(*(float *)(data + 0x140) - pos[0],
                               *(float *)(data + 0x144) - pos[1]);
    len = func_00282E80_1(pos, data + 0x140);
    local.f212 = -mat_fast_helper_a(len, *(float *)(data + 0x148) - pos[2]);
    local.v208 = math_random_angle();
    euler_to_matrix(&local.m00, &local.v208);
    local.v192 = pos[0];
    local.v196 = pos[1];
    local.v200 = pos[2];
    local.v204 = 1.0f;
    scale = math_random_float_range(0.05f, 0.15f) * *(float *)(frame + 0x50);
    FastVecScale(&local.b0, &local.b0, scale);
    FastVecScale(&local.b1, &local.b1, scale);
    FastVecScale(&local.b2, &local.b2, scale);
    FastVecScale(&local.b3, &local.b3, scale);
    draw_world_quad(&local, &local.m00, 0);
    local.k0 = local.k1 = local.k2 = local.k3 = color + 0x7F7F7F;
    FastVecScale(&local.b0, &local.b0, 0.5f);
    FastVecScale(&local.b1, &local.b1, 0.5f);
    FastVecScale(&local.b2, &local.b2, 0.5f);
    FastVecScale(&local.b3, &local.b3, 0.5f);
    draw_world_quad(&local, &local.m00, 0);
    part_spawn_spark_strips(object, pos);
}


/* func_L09_003B6550 is in L09_003B6550-zp-g8.c. */

/* snapshots the object's frame and re-seeds its four steering angles from the new one */
/* func_L09_003E99E0 is matched in its own unit, src/levels/shared/L09_003E99E0-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

/* func_L09_003E9AA0 is matched in src/levels/shared/L09_002B7238-g8.c ($gp-relative small data). */

/* Defined in L09_003E9E60.c. */

/* steps the run's frame index and hands the sample it lands on to the linked stage */
int path_advance_index_and_move(char *object, int index) {
    char *frame = *(char **)(object + 0x68);
    char buf[16];
    short value = *(short *)(frame + 0x118);
    int dir = value < *(short *)(frame + 0x11A) ? 1 : -1;
    float distance;
    int off;
    unsigned int base;

    *(short *)(frame + 0x118) =
        func_L09_0033E8B0_1(object, index, buf, value, dir, *(float *)(frame + 0x78) * 10.0f);
    base = D_L09_001FE6C0[index];
    off = (*(short *)(frame + 0x11A) << 4) + 0x10;
    distance = func_00282E48_2(object + 0x10, base + off);
    return path_move_moby_turn_speed(object, buf, distance);
}

/* func_L09_003EA108 is in L09_003EA108-qcopy.c. */

/* Starts the object moving along the level table entry for an index. Returns the current point, or -1 if there is no entry. */
int path_start_moby_on_entry(char *object, int index, int value)
{
    unsigned int entry = D_L09_001FE6C0[index];
    char *vars = *(char **)(object + 0x68);
    int result;

    if (entry != 0) {
        result = func_L06_00382850_1(object + 0x10, entry, 0.0f);
        result = func_002B6228_1(object, entry, value, result);
        return *(short *)(vars + 0x118);
    }
    *(short *)(vars + 0x118) = 0;
    return -1;
}

/* func_L09_003EA360 is defined in L09_003EA360-g8.c. */

/* func_L09_003EA798 is defined in L09_003EA798-g8.c. */

/* Adds one to the object frame counter (up to its limit) and restarts two timers. */
void enemy_bump_frame_counter(char *object)
{
    unsigned short count = *(unsigned short *)(object + 0x96);
    char *vars = *(char **)(object + 104);

    if (count <= 0xFFFE)
        *(unsigned short *)(object + 0x96) = count + 1;
    FastDecTimer(vars + 0x36A);
    vec_fast_helper_a(vars + 0x368);
}

/* Plays a sound, spawns an explosion at the object and destroys it. */
void moby_destroy_with_explosion(char *object)
{
    PlayMobySound(2, 0, object);
    SetDeathBits(object, 0, 3);
    SpawnExplosion(object + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1,
                  1.0f, 20.0f, 1, 1, 0, 0);
    moby_mark_spawned(object);
}

/* func_L09_003F65E0 is in L09_003F65E0-g8.c. */

/* Defined in L09_003F65E0.c. */

/* Per-frame update for trooper torso objects: when the hero is close, wakes them up and switches them to their next state. */
void trooper_torso_update(char *object)
{
    if (*(unsigned char *)(object + 0x31) != 0) {
        if (fast_vec_dist(object + 0x10, D_L09_001B9A00) < 24.0f) {
            moby_update_ground_check(object);
            *(unsigned char *)(object + 0x6F) = 0x16;
        }
    }
}

/* func_L09_003F71C8 is defined in L09_002B7238-g8.c (it reads the group count through $gp). */

/* func_L09_003F72A8 is defined in L09_002B7238-g8.c (it reads the group count through $gp). */

/* spawns one measured stage with the object's placement lifted by DY */
/* func_L09_003F7370 is matched in its own unit, src/levels/shared/L09_003F7370.c (default flags). */

/* Gives back the shared counter this object was holding, if it had taken one. */
void shared_counter_release(char *object)
{
    char *vars = *(char **)(object + 104);

    if (*(unsigned char *)(object + 33) != 0xFF && *(unsigned char *)(vars + 0x2EB) != 0) {
        math_fast_float_d(*(void **)(vars + 0x304));
    }
    *(unsigned char *)(vars + 0x2EB) = 0;
}

/* Takes one use of the shared counter if the object does not hold it yet. */
void shared_counter_acquire(char *object)
{
    char *vars = *(char **)(object + 104);
    char *counter;

    if (*(unsigned char *)(object + 33) == 0xFF)
        return;
    if (*(unsigned char *)(vars + 0x2EB) != 0)
        return;
    counter = *(char **)(vars + 0x304);
    (*(int *)counter)++;
    *(unsigned char *)(vars + 0x2EB) = 1;
}

/* Clears a value on the object and on its parent Megacorp Trooper Torso, unless they are already gone. */
void trooper_clear_value_self_torso(char *object)
{
    char *parent;

    char *vars;

    vars = *(char **)(object + 104);
    *(int *)(object + 152) = 0;
    parent = *(char **)(vars + 0x2F8);
    if (parent == 0)
        return;
    if (*(short *)(parent + 170) != 3342 /* Megacorp Trooper Torso */)
        return;
    if (*(unsigned char *)(parent + 32) == 254)
        return;
    if (*(unsigned char *)(parent + 32) != 253)
        *(int *)(parent + 152) = 0;
}

/* shared native body of family cd6f3d9eca5f8edd */
/* attempt 1 - shape read straight off the disassembly:
   save object's word 152 from its owner's field 16, then repeat for a second
   object found through two pointer hops, skipping the sentinel byte values. */

/* Copies a value from the owner of the object and of its linked Megacorp Trooper Torso into each of them. */
void trooper_copy_owner_value_self_torso(char *moby)
{
    char *owner;
    char *vars;
    char *linked;
    int linkedOwner;

    if (moby == 0)
        return;
    if (*(unsigned char *)(moby + 32) == 254)
        return;
    if (*(unsigned char *)(moby + 32) == 253)
        return;

    owner = *(char **)(moby + 36);
    vars = *(char **)(moby + 104);
    *(int *)(moby + 152) = *(int *)(owner + 16);

    linked = *(char **)(vars + 760);
    if (linked == 0)
        return;
    if (*(short *)(linked + 170) != 3342 /* Megacorp Trooper Torso */)
        return;
    if (*(unsigned char *)(linked + 32) == 254)
        return;
    if (*(unsigned char *)(linked + 32) == 253)
        return;

    linkedOwner = *(int *)(linked + 36);
    *(int *)(linked + 152) = *(int *)(linkedOwner + 16);
}

/* func_L09_003F7518 is in L09_003F7518-g8.c. */

/* Copies the color of one object onto another. */
void moby_copy_color(char *object, char *target)
{
    int out0, out1, out2;

    get_moby_color(object, &out0, &out1, &out2);
    set_moby_color(target, out0, out1, out2);
}

/* Destroys the objects linked to this one and clears the links. */
void moby_destroy_linked(char *object)
{
    char *descriptor = *(char **)(object + 0x68);
    char *slots;
    int i;

    if (*(int *)(descriptor + 0x2F8) != 0) {
        moby_mark_spawned(*(void **)(descriptor + 0x2F8));
        *(int *)(descriptor + 0x2F8) = 0;
    }
    slots = descriptor + 0x2F0;
    for (i = 0; i < 2; ++i) {
        if (*(int *)(slots + i * 4) != 0) {
            moby_mark_spawned(*(void **)(slots + i * 4));
            *(int *)(slots + i * 4) = 0;
        }
    }
}


/* reports whether the index still names a reachable entry, or whether the frame moved close enough */
int path_is_entry_reachable(char *object, int index) {
    char *frame = *(char **)(object + 0x68);
    int entry = path_check_entry_for_moby(object, index);

    if (entry == 0 && index != -1) {
        int off = (*(short *)(frame + 0x1CA) << 4) + 0x10;

        if (vec_distance_xy(object + 0x10, D_L09_001FE6C0[index] + off) <
            *(float *)(frame + 0x134))
            entry = 1;
    }
    return entry;
}



/* func_L09_003F7CE0 is defined in L09_003F7CE0-g8.c. */

/* func_L09_003F8598 is defined in L09_003F8598-g8.c. */

/* Marks every Megacorp Trooper Legs object in a group so it knows to react. */
void trooper_flag_legs_in_group(char *unused, int index)
{
    unsigned int entry;
    unsigned short *idList;

    if (index == 0xFF)
        return;
    entry = D_L09_001FB560[index];
    if (entry == 0)
        return;
    idList = (unsigned short *)entry;
    do {
        char *target = D_L09_001B285C + ((idList[0] & 0x7FFF) << 8);

        if (*(signed char *)(target + 0x20) >= 0 && *(short *)(target + 0xAA) == 0xD0F /* Megacorp Trooper Legs */)
            *(unsigned char *)(*(int *)(target + 0x68) + 0x2EA) = 1;
    } while ((short)*idList++ >= 0);
}

/* Passes two stored values of the object to a shared helper, one after the other. */
void enemy_apply_stored_values_helper(char *object)
{
    char *vars = *(char **)(object + 104);

    ref_L09_003F8858_00(object, *(unsigned char *)(object + 33));
    ref_L09_003F8858_00(object, *(int *)(vars + 0x308));
}

/* func_L09_003F8898 lives in the L09_002B7238-g8.c sibling: its four counters are small data. */



/* func_L09_003F9108 is defined in L09_003F9108-partner.c. */
