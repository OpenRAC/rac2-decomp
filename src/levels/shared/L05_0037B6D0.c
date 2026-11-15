#include "common.h"

extern float func_332BB0(float, float);
extern int func_307778(float);
extern int func_332AF8(int, int);
extern void func_332C60(void *, float, float);
extern char *func_352B28(void *, void *, int, int, int, int, int, int, float, float, float);
extern float func_306CD0(float, float);
extern float func_307620(float, float);
extern char *func_347040(void *, int, void *, int, float, float, float, float, int);
extern float func_307768(int);
typedef struct {
    char pad[0x140];
    float pos[4];
} ParticleCamera99268;
extern ParticleCamera99268 D_L05_001B9580;
extern unsigned char *D_L05_001FF240[];
typedef struct {
    int v[2];
} __attribute__((packed)) ParticleColors99268;
extern ParticleColors99268 D_L05_001AEC00;
extern void func_33B330(void *, float, float, float);

extern int D_L05_00221D3C;
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern char *D_L05_001BFB18;
extern void copy_matrix_rotation(void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern int math_fast_helper_a(void *, float);

extern int moby_get_motion_data(char *);

extern void follower_set_state(char *, int);

extern int func_002A7820_1(int, int);

extern int func_001163B0(void);

extern int D_L05_00221D10[];

extern int D_L05_00221D28;

extern /* Clears all the link fields of an object so it is free again. */
void moby_clear_links(char *);

extern void group_swap_with_free_member(char *);

extern void group_free_members_and_self(char *);

extern void group_layout_members_in_grid(char *);

extern float func_332B50(float, float);

extern char *func_379CA0(char *);

extern void func_379FA0(char *, int, int, int, float, float, float, float, int, int, int);

extern int func_332AB8(int);

extern void func_3719A8(int, int, char *, int);

extern void func_306AD8(void *, void *, void *);

extern void func_306630(void *, void *, void *);

typedef struct {
    float f[38];
    int timer;
    char *owner;
    int active;
    int pad;
    int dying;
    int pad2;
} Record233560;
extern Record233560 D_L05_00233560[24];
extern void gfx_draw_jittered_curve(char *, char *);
extern float math_random_float_range(float, float);
extern void gfx_draw_billboard_quad(void *, int, int, int, float, float, float);

extern void FastVecAdd(void *, void *, void *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecSub(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern int math_fast_float_d(void *);

typedef unsigned int Quad37DA58 __attribute__((mode(TI)));
extern char D_L05_001B96C0[];
extern void vec_scale_to_length(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, float, float, int, int, int, void *, int, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern int FloatToInt(float);

/* looks up an object, then sets flags, arms a stored value and calls one of two helper pairs before building a timer */
void moby_start_movement_state(char *obj)
{
    char *vars;

    vars = (char *)moby_get_motion_data(obj);
    if (vars == 0)
        return;
    if (*(int *)(vars + 288) == 0)
        return;
    if (*(int *)(vars + 284) != 0) {
        int *counters = D_L05_00221D10;
        int one = 1;

        *(int *)(vars + 280) = one;
        counters[3] += one;
        if (moby_get_state_value(obj) != 5) {
            follower_set_state(obj, 4);
            *(float *)(vars + 120) = (func_001163B0() & 1) ? -1.0f : 1.0f;
            if (func_001163B0() & 1)
                *(float *)(vars + 116) = -1.0f;
            else
                *(float *)(vars + 116) = 1.0f;
            *(int *)(vars + 252) = one;
            *(int *)(vars + 112) = 0;
            *(int *)(vars + 124) = 0;
        } else {
            follower_set_state(obj, 7);
        }
        *(int *)(vars + 304) = func_002A7820_1(120, 500);
    } else {
        int *counters = D_L05_00221D10;

        *(int *)(vars + 280) = 1;
        counters[3] += 1;
        if (moby_get_state_value(obj) != 5)
            follower_set_state(obj, 4);
        else
            follower_set_state(obj, 7);
        *(int *)(vars + 304) = func_002A7820_1(120, 500);
        *(int *)(vars + 252) = 0;
    }
}





/* Checks if the player is close enough, in front of the object and visible, and sets two flags for it. */
void moby_check_player_in_view_and_range(char *obj, int check, float range)
{
    float angles[4];
    float matrix[16];
    float sphere[4];
    char *vars = (char *)moby_get_motion_data(obj);
    float angle;
    float elevation;
    float limit;
    if (!vars)
        return;
    if (!*(char **)(vars + 0x120))
        return;
    *(int *)(vars + 0x104) = 0;
    *(int *)(vars + 0x108) = 0;
    limit = 0.7068582773f;
    if (D_L05_00221D3C == 1)
        return;
    if (fast_vec_dist(*(char **)(vars + 0x120) + 0x10, obj + 0x10) > range)
        return;
    if (CollLine(obj + 0x10, *(char **)(vars + 0x120) + 0x10, 0, obj, 0)) {
        if (!D_L05_001BFB18)
            return;
        if (*(short *)(D_L05_001BFB18 + 0xAA) != *(short *)(*(char **)(vars + 0x120) + 0xAA))
            return;
    }
    copy_matrix_rotation(matrix, obj + 0xC0);
    mat_get_euler_angles(matrix, angles);
    angle = FastDiffRots(mat_fast_helper_a(
        *(float *)(*(char **)(vars + 0x120) + 0x10) - *(float *)(obj + 0x10),
        *(float *)(*(char **)(vars + 0x120) + 0x14) - *(float *)(obj + 0x14)), angles[2]);
    elevation = vec_distance_xy(*(char **)(vars + 0x120) + 0x10, obj + 0x10);
    elevation = FastDiffRots(mat_fast_helper_a(elevation,
        *(float *)(*(char **)(vars + 0x120) + 0x18) - *(float *)(obj + 0x18)), 0.0f);
    if (angle <= limit && elevation <= limit)
        *(int *)(vars + 0x104) = 1;
    if (check) {
        qcopy(sphere, obj + 0x10);
        sphere[3] = 0.1f;
        if (math_fast_helper_a(sphere, 256.0f) == -1)
            return;
    }
    *(int *)(vars + 0x108) = 1;
}

extern void func_3065F8(int);

struct S_L05_0037BB28 {
    char pad0[0x10];
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
};

void moby_clear_links(char *object)
{
    struct S_L05_0037BB28 *p = (struct S_L05_0037BB28 *)func_379CA0(object);

    if (p == 0)
        return;
    func_3065F8((int)p);
    p->f20 = -1;
    p->f1C = -1;
    p->f14 = 0;
    p->f18 = -1;
    p->f10 = 0;
}

/* Returns the object's link value, or zero. */
int moby_get_link_value(char *obj)
{
    int *vars = (int *)moby_get_motion_data(obj);

    if (vars == 0)
        return 0;
    return vars[5];
}

/* Returns 1 if the object is in use, else 0. */
int moby_is_in_use(char *obj)
{
    int *vars = (int *)moby_get_motion_data(obj);

    if (vars == 0)
        return 0;
    if (vars[5] == 0 && vars[4] == 0)
        return 0;
    return 1;
}

/* Frees an object from its parent and rearranges the remaining group members. */
void moby_release_from_group(char *obj)
{
    int *parent_vars = (int *)moby_get_motion_data(obj);
    char *child;
    int *group_vars;

    if (parent_vars == 0)
        return;
    if (moby_get_link_value(obj) != 0)
        group_swap_with_free_member(obj);
    child = (char *)parent_vars[4];
    group_vars = (int *)moby_get_motion_data(child);
    group_vars[6] = group_vars[6] - 1;
    moby_clear_links(obj);
    if (group_vars[6] < D_L05_00221D28)
        group_free_members_and_self(child);
    else
        group_layout_members_in_grid(child);
}

/* func_L05_0037BF48 is in L05_0037BF48.c. */

/* func_L05_0037C160 is in L05_0037C160.c. */

/* Stores a value on the object. */
void moby_l05_set_state_value(char *obj, int value)
{
    int *vars = (int *)moby_get_motion_data(obj);

    if (vars != 0)
        *(int *)((char *)vars + 0x114) = value;
}


/* Returns the value stored on the object, or zero. */
int moby_get_state_value(char *obj)
{
    int *p = (int *)moby_get_motion_data(obj);

    if (p == 0)
        return 0;
    return *(int *)((char *)p + 0x114);
}

/* func_L05_0037CEE0 is in L05_0037CEE0-g8.c. */


struct S_L05_002A1800 {
    char pad0[0xC];
    int f0C;
    int f10;
    int f14;
    char pad1[0x10];
};

extern struct S_L05_002A1800 D_L05_002A1800[];

extern int table_find_last_used_entry(int);

/* Copies the default values into the working values of 15 table entries and picks one entry from a lookup. */
void table_reset_working_values(void)
{
    int i;

    for (i = 0; i < 15; i++)
        D_L05_002A1800[i].f14 = D_L05_002A1800[i].f0C;
    D_L05_002A1800[7].f14 = D_L05_002A1800[7].f0C;
    D_L05_002A1800[13].f14 = D_L05_002A1800[13].f0C;
    i = table_find_last_used_entry(6);
    D_L05_002A1800[i].f14 = D_L05_002A1800[i].f10;
}



/* Emits count pairs of particles at position, jittering it each time; each pair drifts at a random
   angle around the flattened direction from position to the camera, and rises at a random speed. */
void EmitParticlePairBurst(float *position, int count, int color, int duration)
{
    float velocity[4], point[4], direction[4], axis[4], half[4];
    float size, angle;
    int sign, i;
    char *particle;
    *(Quad37DA58 *)axis = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    FastVecSub(direction, D_L05_001B96C0, position);
    vec_scale_to_length(half, direction, 0.5f);
    direction[2] = 0;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (!sign) --sign;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        vec_scale_to_length(velocity, velocity, math_random_float_range(0.05f, 3.0f) * (1.0f/60.0f));
        velocity[2] = math_random_float_range(1.0f, 5.0f) * (1.0f/60.0f);
        FastVecAdd(point, position, half);
        position[0] += math_random_signed_float_range(0, 0.15f);
        position[1] += math_random_signed_float_range(0, 0.15f);
        position[2] += math_random_signed_float_range(0, 0.15f);
        particle = part_spawn_ground_effect(position, duration, size * 0.1f, size, color, 0, sign, velocity, 0, 0.002f);
        if (particle) {
            particle[2] = D_L05_001FF240[0x61][6];
            particle[9] = FloatToInt(4.0f) + 0x70;
        }
        particle = part_spawn_ground_effect(position, duration, size * 0.07f, size * 0.7f, 0x7f7f7f7f, 1, -sign, velocity, 0, 0.002f);
        if (particle) {
            particle[2] = D_L05_001FF240[0x61][6];
            particle[9] = FloatToInt(4.0f) + 0x70;
        }
    }
}

/* func_L05_003979B0 is in L05_003979B0-g8.c. */

/* func_L05_00397B30 is in L05_0037B6D0-g8.c. */

/* func_L05_00397F48 is in L05_00397F48-g8.c. */

/* Walks the twenty-four records, and for each one the object owns updates it and, while it is
   not active, lays the three colours over its vector. */
void record_update_owned_effects(char *owner)
{
    int i;
    for (i = 0; i < 24; i++) {
        Record233560 *record = &D_L05_00233560[i];
        float *position = &record->f[12];
        if (record->owner == owner) {
            gfx_draw_jittered_curve(owner, (char *)record);
            if (record->active == 0) {
                gfx_draw_billboard_quad(position, 0x31, 0x3F0000FF, 1, math_random_float_range(0.065f, 0.1f) * 5.0f, 1.25f, 0.0f);
                gfx_draw_billboard_quad(position, 0x31, 0x5F7F7F7F, 1, math_random_float_range(0.0325f, 0.06f) * 5.0f, 1.24f, 0.0f);
                gfx_draw_billboard_quad(position, 0xB, 0x1000003F, 1, math_random_float_range(0.07f, 0.15f) * 5.0f, 1.23f, 0.0f);
            }
        }
    }
}


/* Walks the twenty-four records: for each one the object owns, jitters its position, moves it to
   the object carrying its offset along, steps its six angles (faster while active), rebuilds its two
   vectors and interpolates between position and end; both timers then retire the record. */
void record_animate_owned(char *obj)
{
    float delta[4] __attribute__((aligned(16)));
    int i;
    char *state = *(char **)(obj + 0x68);
    for (i = 0; i < 24; i++) {
        Record233560 *r = &D_L05_00233560[i];
        if (r->owner == obj) {
            Record233560 *p = r;
            float *end = &p->f[16];
            float *pos = &p->f[8];
            p->f[8] += math_random_float_range(-0.1f, 0.1f);
            p->f[9] += math_random_float_range(-0.1f, 0.1f);
            p->f[10] += math_random_float_range(-0.1f, 0.1f);
            FastVecSub(delta, end, pos);
            qcopy(pos, obj + 0x10);
            FastVecAdd(end, pos, delta);
            if (p->active) {
                p->f[20] = FastAddRotations(p->f[20], p->f[23] * 100.0f);
                p->f[21] = FastAddRotations(p->f[21], p->f[24] * 100.0f);
                p->f[22] = FastAddRotations(p->f[22], p->f[25] * 100.0f);
                p->f[29] = FastAddRotations(p->f[29], p->f[32] * 100.0f);
                p->f[30] = FastAddRotations(p->f[30], p->f[33] * 100.0f);
                p->f[31] = FastAddRotations(p->f[31], p->f[34] * 100.0f);
            } else {
                p->f[20] = FastAddRotations(p->f[20], p->f[23] * 50.0f);
                p->f[21] = FastAddRotations(p->f[21], p->f[24] * 50.0f);
                p->f[22] = FastAddRotations(p->f[22], p->f[25] * 50.0f);
                p->f[29] = FastAddRotations(p->f[29], p->f[32] * 50.0f);
                p->f[30] = FastAddRotations(p->f[30], p->f[33] * 50.0f);
                p->f[31] = FastAddRotations(p->f[31], p->f[34] * 50.0f);
            }
            p->f[0] = math_fast_sin_or_cos_a(p->f[20]) * p->f[26];
            p->f[1] = math_fast_sin_or_cos_b(p->f[21]) * p->f[27];
            p->f[2] = -math_fast_sin_or_cos_b(p->f[22]) * p->f[28];
            p->f[4] = math_fast_sin_or_cos_a(p->f[29]) * p->f[35];
            p->f[5] = math_fast_sin_or_cos_b(p->f[30]) * p->f[36];
            p->f[6] = -math_fast_sin_or_cos_b(p->f[31]) * p->f[37];
            if (*(int *)(state + 0x24))
                lerp_vector(&p->f[12], &p->f[8], &p->f[16], 0.55f);
            else
                lerp_vector(&p->f[12], &p->f[8], &p->f[16], 0.4f);
            if (math_fast_float_d(&p->active)) {
                if (p->dying == 0) p->dying = 1;
                if (math_fast_float_d(&p->timer)) p->owner = 0;
            }
        }
    }
}

/* func_L05_00398A38 is in L05_00398A38.c. */

/* func_L05_00398F18 is in L05_00398F18.c. */

/* Spawns a burst of particles around the object: debris, smoke and sparks. */
void EmitScaledParticleBurst(char *obj)
{
    float pos[4];
    float vel[4];
    ParticleColors99268 colors;
    char *s = *(char **)(obj + 0x68);
    int i, j, k, sign;
    float angle;
    char *p, *d;

    for (i = 0; i < *(int *)(s + 0x20); i++) {
        int type, life;
        float scale;

        type = func_307778(func_332BB0(2.0f, 5.0f));
        life = func_332AF8(30, 50);
        pos[0] = *(float *)(obj + 0x10) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        pos[1] = *(float *)(obj + 0x14) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        pos[2] = *(float *)(obj + 0x18) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        scale = func_332B50(0.6f, 1.0f) * *(float *)(s + 0x14);
        func_332C60(vel, 0.06f, 0.1f);
        func_352B28(pos, vel, life, 0x102FFF, type, 255, 0, 1, scale * 210000.0f, scale * 105000.0f, 0.0019444444915279746f);
    }

    for (j = 0; j < *(int *)(s + 0x24); j++) {
        int type, life;
        float scale;

        type = func_307778(func_332BB0(2.0f, 5.0f));
        life = func_332AF8(30, 50);
        pos[0] = *(float *)(obj + 0x10) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        pos[1] = *(float *)(obj + 0x14) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        pos[2] = *(float *)(obj + 0x18) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        scale = func_332B50(0.75f, 1.5f) * *(float *)(s + 0x14);
        func_332C60(vel, 0.5f, 0.8f);
        func_352B28(pos, vel, life, 0x8FFF, type, 127, 127, 5, scale * 210000.0f, *(float *)(s + 0x14) * 2100.0f, 0.004055555909872055f);
    }

    angle = func_306CD0(D_L05_001B9580.pos[0] - *(float *)(obj + 0x10), D_L05_001B9580.pos[1] - *(float *)(obj + 0x14));
    sign = 1;
    for (k = 0; (float)k < (float)*(int *)(s + 0x2C) * 3.0f + (float)(*(int *)(s + 0x3C) * 10); k++) {
        float scale, a, b;

        pos[0] = *(float *)(obj + 0x10) + func_332BB0(0.0f, 0.5f) * *(float *)(s + 0x14);
        sign = -sign;
        pos[1] = *(float *)(obj + 0x14) + func_332BB0(0.0f, 0.5f) * *(float *)(s + 0x14);
        pos[2] = *(float *)(obj + 0x18) + func_332BB0(0.0f, 0.5f) * *(float *)(s + 0x14);
        scale = func_332B50(0.01666666753590107f, 0.02500000223517418f) * *(float *)(s + 0x14);
        a = func_332BB0(0.0f, 1.396263599395752f);
        b = func_332BB0(0.0f, 1.5707964897155762f);
        func_33B330(vel, scale, func_307620(angle, b), a);
        p = func_347040(pos, sign, vel, *(int *)(s + 0x3C) ? 0xD10572 : 0x5A182, 0.0f, 1.0f, 1.01f, *(float *)(s + 0x14) * 31500.001953125f, 0);
        colors = D_L05_001AEC00;
        if (p) {
            d = p + 0x20;
            {
                int index = func_001163B0() % 2;
                p[3] = colors.v[index];
            }
            if (*(int *)(s + 0x3C))
                *(short *)(p + 0xA) = func_332AF8(120, 150);
            else
                *(short *)(p + 0xA) = func_332AF8(90, 120);
            p[9] = func_307778(4.0f) + 64;
            *(int *)(d + 4) = 3;
            *(float *)(d + 0x1C) = func_307768(func_332AF8(1, 10));
            d[0xA] = func_332AF8(64, 128);
            d[0xB] = p[0xA];
            if (func_332AB8(4) != 0)
                p[2] = D_L05_001FF240[34][0];
            else
                p[2] = D_L05_001FF240[105][0];
        }
    }
}

/* func_L05_003CD1A8 is in L05_003CD1A8-g8.c. */


/* Fills in the starting values of the object's private variables. */
void moby_init_private_vars(char *object)
{
    char *state = *(char **)(object + 0x68);
    float *f = (float *)state;
    int *w;
    int i;
    int j;
    int v;

    for (i = 3; i >= 0; i--)
        *f++ = (float)func_332AB8(0xFF);
    *(float *)(state + 0x10) = -1.0f;
    *(float *)(state + 0x14) = -2.25f;
    *(float *)(state + 0x18) = 1.25f;
    *(float *)(state + 0x1C) = 2.5f;
    j = 3;
    w = (int *)(state + 0x2C);
    v = 0xFF;
    for (; j >= 0; j--) {
        *w = v;
        w = (int *)((char *)w - 4);
        v -= 0x40;
    }
    *(float *)(state + 0x30) = 2.8f;
    *(float *)(state + 0x34) = 3.5f;
    *(float *)(state + 0x3C) = 2.8f;
    *(float *)(state + 0x38) = 3.5f;
}


/* func_L05_003CEFA0 is in L05_003CEFA0.c. */

/* func_L05_003CF040 is in L05_003CF040-g8.c. */

/* func_L05_003CF350 is in L05_003CF350-g8.c. */

/* func_L05_003CFAB8 is in L05_0037B6D0-g8.c. */

/* Converts an object id into a table index. */
int moby_class_id_to_table_index(int class_id)
{
    if (class_id == 0x971)
        return 4;
    return class_id - 0x953;
}

/* func_L05_003CFC48 is in L05_003CFC48-g8.c. */

/* func_L05_003CFCF0 is in L05_003CFCF0-g8.c. */

/* func_L05_003CFF90 is in L05_003CFF90.c. */

extern int D_L05_00221D10[];

extern char *D_L05_001B2614 __attribute__((sda));

extern void func_37AEC0(char *, int);

extern float func_332C18(void);

extern void func_33B330(void *, float, float, float);

/* Gives the object its reach: the table's entry for the object's id picks the record, and
 * the record takes the cone the object was given. */
void moby_init_reach_and_position(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_379CA0(obj) + 0x148) = 1;
    func_37AEC0(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(int *)(sub + 0x1BC) = -1;
    *(int *)(sub + 0x1C0) = -1;
    *(float *)(sub + 0x180) = 1.0f;
    *(int *)(sub + 0x1B8) = 0;
    *(float *)(obj + 0x2C) = 0.06f;
    a = func_332B50(0.0f, *(float *)table);
    b = func_332C18();
    c = func_332C18();
    func_33B330(obj + 0x10, a, b, c);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
}


/* func_L05_003D0728 is in the sibling unit L05_003D0728-g8.c. */

/* Picks a random point inside a box and moves it by a matrix. */
void math_random_point_in_box_transformed(float *out, char *matrix)
{
    out[0] = func_332B50(-1.0f, 1.0f);
    out[1] = func_332B50(-1.0f, 1.0f);
    out[2] = func_332B50(-1.0f, 1.0f);
    out[3] = 1.0f;
    func_306AD8(out, out, matrix);
    func_306630(out, out, matrix + 0x30);
}

/* func_L05_003D0960 is in L05_003D0960-g8.c. */

/* func_L05_003D0B20 is in L05_003D0B20-g8.c. */

extern void cam_compute_view_direction(char *a0, char *a1, int a2);

extern float *moby_get_private_value_0(char *a0);

extern void FastVecScale(void *a0, void *a1, float a2);

extern void FastVecAdd(void *a0, void *a1, void *a2);

extern void moby_rotate_toward_vector(void *a0, void *a1, void *a2, void *a3,
                              float f0, float f1, float f2, void *a4);

/* Builds the pair of vectors the timer wants: the object's own matrix, scaled by the value the
 * looked-up sub-object holds, and that scaled matrix combined with the sub-object's table. */
void moby_build_timer_vectors_from_matrix(char *a0, char *a1, char *a2, char *a3, float f0, float f1, float f2)
{
    float v0[4];
    float v1[4];
    float v2[4];
    float *p;

    if (a2 == 0)
        return;
    if (*(unsigned char *)(a2 + 0x20) == 0xFE)
        return;
    if (*(unsigned char *)(a2 + 0x20) == 0xFD)
        return;
    cam_compute_view_direction(a0, (char *)v0, 1);
    p = moby_get_private_value_0(a2);
    FastVecScale(v1, v0, *(float *)((char *)p + 0x10));
    FastVecAdd(v2, (float *)(a2 + 0x10), v1);
    moby_rotate_toward_vector(a0, a1, v2, a3, f0, f1, f2, v0);
}

extern void FastVecSub(void *out, void *a, void *b);

extern float FastVecLength(void *v);

extern void FastVecCross(void *out, void *a, void *b);

extern float FastVecDot(void *a, void *b);

extern void vec_scale_to_length(void *out, void *in, float scale);

extern void FastVecScale(void *out, void *in, float scale);

extern float math_fabs(float x);

extern float math_fast_angle_helper(float x);

extern float math_fast_sin_or_cos_b(float x);

extern float math_fast_sin_or_cos_a(float x);

extern void mat_build_rotation_toward_vector(void *out, void *in, void *tmp, int mode, float value);

extern void vec_rotate_by_quaternion(void *out, void *in, void *v);

extern float math_step_spring_damper_stored(void *obj, float p1, float p2, float p3, float p4, float p5);

/* Rotates an object onto a vector: builds the axis vectors, then hands the object a
   quaternion-like value scaled by the angle it makes with the target. */
void moby_rotate_toward_vector(void *a0, void *a1, void *a2, void *a3,
                      float f0, float f1, float f2, void *a4)
{
    float v0[4];
    float v1[4];
    float v2[4];
    float len;
    float dot;
    float prod;
    float ang;
    float diff;
    float r;

    FastVecSub(v0, a2, a0);
    len = FastVecLength(v0);
    if (len == 0.0f)
        return;
    if (len < 1.5f) {
        mat_build_rotation_toward_vector(a1, a1, v0, 0, 0.5f);
        return;
    }
    FastVecCross(v1, v0, a1);
    dot = FastVecDot(a1, v0);
    prod = FastVecLength(a1) * FastVecLength(v0);
    if (prod == 0.0f)
        return;
    ang = math_fast_angle_helper(dot / prod);
    diff = 1.5707964f - ang;
    if (math_fabs(diff) > 2.879793643951416f) {
        FastVecCross(v2, a1, a4);
        FastVecCross(v1, v2, a1);
    }
    vec_scale_to_length(v1, v1, 1.0f);
    r = math_step_spring_damper_stored(a3, 0.0f, diff * 0.5f, f0, f1, f2);
    FastVecScale(v1, v1, math_fast_sin_or_cos_b(r));
    v1[3] = math_fast_sin_or_cos_a(r);
    vec_rotate_by_quaternion(a1, a1, v1);
}

/* func_L05_003D1368 is in L05_003D1368-g8.c. */

/* func_L05_003D15E8 is in L05_003D15E8.c. */

/* Starts the object: sets its state, a flag and a random starting position. */
void moby_init_state_and_position(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_379CA0(obj) + 0x148) = 5;
    func_37AEC0(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(float *)(sub + 0x180) = 5.0f;
    *(int *)(sub + 0x2F0) = -1;
    *(int *)(sub + 0x2F4) = -1;
    *(int *)(sub + 0x268) = 0;
    *(float *)(obj + 0x2C) = 0.04f;
    a = func_332B50(0.0f, *(float *)table);
    b = func_332C18();
    c = func_332C18();
    func_33B330(obj + 0x10, a, b, c);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
    *(int *)(sub + 0x26C) = 0;
}



/* Spawns the object's effect after three guards, then runs the timer. */
void moby_spawn_effect_after_guards(char *object)
{
    char *s1 = *(char **)(object + 0x68);
    char *r;

    r = func_379CA0(object);
    if (r == 0)
        return;
    if (*(int *)(r + 0x120) == 0)
        return;
    if (*(int *)(s1 + 0x268) != 0)
        return;
    func_379FA0(object, 0x60000090, 1, 0, 0.6f, 2.0f, 1.0f, 1.3f, 0, -1, 0);
    if (func_332AB8(3) == 0)
        func_3719A8(0, 0, object, 0x97C);
    *(int *)(s1 + 0x268) = 0x3C;
}

/* func_L05_003D1AB8 is in L05_003D1AB8-g8.c. */



/* func_L05_003D2048 is in L05_003D2048-g8.c. */

/* func_L05_003D2618 is in L05_003D2618-g8.c. */

