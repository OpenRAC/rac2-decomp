#include "include_asm.h"
#include "common.h"

#ifndef RAC2_T_V4_F0FBA48D3
#define RAC2_T_V4_F0FBA48D3
typedef int V4_F0fba48d3 __attribute__((mode(TI)));
#endif

extern void func_00282CF0_2(void *b, void *c, void *d);

extern void vec_scale_to_length(void *dst, void *src, float x);

extern void FastVecAdd(void *c, void *c2, void *s);

extern void func_00282CF0_2(void *b, void *c, void *p);

extern void vec_scale_to_length(void *dst, void *src, float y);

extern void FastVecAdd(void *b, void *p, void *s);

extern void func_00282CF0_2(void *b, void *s, void *e);

extern char D_L00_001BF220_1[];

extern void func_00282CF0_7(char *local, char *data);

extern float func_00282DB0_1(char *local, char *p);

extern float D_L00_001A8900 __attribute__((sda));

extern void func_00282CF0_4(float *out, char *a, char *b);

extern void lerp_vector(float *out, char *a, char *b, float k);

extern float FastVecLength(void *v);

extern void func_00282F20_3(float *out, float *in, float k);

extern char *D_L00_001BB040;

extern void func_00282CF0_8(char *dst, char *a, char *b);

extern void cam_steer_toward_target(char *a0, char *a1, float t);

extern float cam_steer_toward_direction(char *a0, char *a1, float t);

/* func_L00_004224D0 is in L00_004224D0-main-g8.c (-G8, -frac2-qcopy). */

typedef struct { float x, y, z, w; } Vector;
typedef struct { Vector row[3]; } Matrix;
typedef struct {
    Vector up, scaled, delta, endpoint, transformed, offset;
    Matrix basis;
    Vector difference;
} CameraScratch;
extern char *g_follow_camera_object;
extern char g_hero_state[];
extern int D_L00_001B184C MACRO_ADDR;
extern Vector D_L00_001BF220;
extern Vector D_L00_001B8E50;
extern void copy_matrix3x4(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern int CollLine(void *, void *, unsigned int, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);

/* Places the follow camera and rebuilds its direction vectors. When asked, it first moves the camera to its spot behind the hero, pulling it in if a wall is in the way. */
void cam_follow_update_orientation(int reposition)
{
    CameraScratch scratch;
    char *object = g_follow_camera_object;
    char *state = *(char **)(object + 0x70);
    char *movement = state + 0x160;
    char *transform = state + 0x60;
    char *position;
    char *target;
    float length;
    if (reposition) {
        scratch.offset.x = -*(float *)(movement + 0x2C);
        scratch.offset.y = 0.0f;
        scratch.offset.z = *(float *)(movement + 0x30);
        scratch.offset.w = 0.0f;
        copy_matrix3x4(&scratch.basis, g_hero_state);
        matrix_mul_vec3(&scratch.transformed, &scratch.offset, *(char **)(transform + 0xC0) + 0xC0);
        target = object + 0x30;
        FastVecAdd(target, transform, &scratch.transformed);
        FastVecScale(&scratch.scaled, *(char **)(transform + 0xC0) + 0xE0, *(float *)(transform + 0xB0));
        FastVecAdd(&scratch.endpoint, transform, &scratch.scaled);
        if (CollLine(&scratch.endpoint, target, D_L00_001B184C, *(char **)(g_hero_state + 0x2290), 0)) {
            FastVecSub(&scratch.difference, &D_L00_001BF220, &scratch.endpoint);
            length = FastVecLength(&scratch.difference);
            if (length == 0.0f) {
                qcopy(target, &scratch.endpoint);
            } else {
                FastVecScale(&scratch.difference, &scratch.difference, (length - 0.5f) / length);
                FastVecAdd(target, &scratch.endpoint, &scratch.difference);
            }
        }
    }
    position = object + 0x30;
    {
        float *previous = (float *)(object + 0x64);
        previous[0] = *(float *)position;
        previous[1] = *(float *)(position + 4);
        previous[2] = *(float *)(position + 8);
    }
    qcopy(&scratch.up, &D_L00_001B8E50);
    vec_scale_to_length(&scratch.scaled, &scratch.up, *(float *)(transform + 0xB0));
    FastVecAdd(&scratch.endpoint, &scratch.scaled, transform);
    FastVecSub(&scratch.delta, &scratch.endpoint, position);
    vec_scale_to_length(object, &scratch.delta, 1.0f);
    qcopy(object + 0x20, &scratch.up);
    FastVecCross(object + 0x10, object, object + 0x20);
    vec_scale_to_length(object + 0x10, object + 0x10, 1.0f);
    FastVecCross(object + 0x20, object + 0x10, object);
    qcopy(object + 0x40, object);
}

/* func_L00_00423038 is in a separate compilation unit. */


/* func_L00_004233F8 is in L00_004233F8-g8.c. */


/* func_L00_004237C8 is in a separate compilation unit. */

/* func_L00_004239A8 is in L00_004239A8-g8.c. */

/* Camera check that does nothing and always answers no. */
int cam_check_noop(void)
{
    char unused[80];

    return 0;
}

/* reads a pointer from the field at +112 of the first argument, advances it by 176, then runs three 16-byte records and two float parameters through a fixed sequence of seven calls that alternate between three helpers */
void cam_compute_push_out(char *camera, void *result, void *point, void *direction,
                                      void *original, float pushAmount, float blend)
{
    V4_F0fba48d3 delta, scaled, toGoal, blended;
    void *movement = (void *)(*(int *)(camera + 112));

    movement = (void *)((int)movement + 176);

    func_00282CF0_2(&delta, point, direction);
    vec_scale_to_length(&scaled, &delta, pushAmount);
    FastVecAdd(point, point, &scaled);
    func_00282CF0_2(&toGoal, point, movement);
    vec_scale_to_length(&toGoal, &toGoal, blend);
    FastVecAdd(&blended, movement, &toGoal);
    func_00282CF0_2(result, &blended, original);
}

/* func_L00_00423CA8 is in L00_00423CA8-g8.c. */

/* Returns 0 unless the second argument equals 1; then it takes a pointer out of the first argument's field at +112, adds 352 to it, passes a 16-byte stack buffer and a data symbol to one routine, passes the same buffer and the shifted pointer to a second routine that returns a float, and returns 1 only when that float is below zero. */
int cam_is_step_behind_plane(int camera, int index)
{
    char vec[16];
    int movementPtr;
    int result;

    if (index != 1) {
        result = 0;
    } else {
        movementPtr = *(int *)(camera + 112) + 352;
        func_00282CF0_7(vec, D_L00_001BF220_1);
        result = func_00282DB0_1(vec, (char *)movementPtr) < 0.0f ? 1 : 0;
    }
    return result;
}

/* func_L00_004240D8 is in L00_004240D8-g8-dbg.c. */

/* func_L00_004243C0 is in L00_004243C0-g8-dbg.c. */

extern char *g_follow_camera_object;

/* Checks whether the camera request slot holds this request and, if so, clears it. Returns -1 if the camera is not in the normal mode. */
int cam_release_request_slot(int request)
{
    char *camera = g_follow_camera_object;
    char *state;

    if (*(short *)(camera + 134) != 0) {
        return -1;
    }
    state = *(char **)(camera + 112);
    if (*(int *)(state + 576) == request) {
        *(int *)(state + 576) = 0;
        return 1;
    }
    return 0;
}

/* func_L00_00424978 is matched in L00_00424978.c (built with -mno-split-addresses). */

/* Sets a new camera goal value and its speed, and can also set the current value straight away. */
void follow_camera_set_distance(int alsoSetCurrent, float goal, float rate)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *state = *(char **)(camera + 112);
        char *block = state + 352;

        *(short *)(block + 60) = 1;
        *(float *)(block + 72) = rate;
        *(float *)(block + 64) = goal;
        if (alsoSetCurrent) {
            *(float *)(block + 88) = goal;
        }
    }
}

/* Stores the two incoming floats and a flag into the block at +352 of the owner object. */
void follow_camera_set_height(float firstValue, float secondValue)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *state = *(char **)(camera + 112);
        char *block = state + 352;

        *(short *)(block + 62) = 1;
        *(float *)(block + 76) = firstValue;
        *(float *)(block + 84) = secondValue;
    }
}

/* Sets a flag and a value on the block at +96; the value is offset by a shared float when a0 is set. */
void cam_set_aim_offset_target(int addBase, float offset, float speed)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *state = *(char **)(camera + 112);
        char *block = state + 0x60;

        *(short *)(block + 0xDA) = 1;
        *(float *)(block + 0xB8) = speed;
        if (addBase) {
            *(float *)(block + 0xB4) = *(float *)(D_L00_001BB040 + 0x110) + offset;
        } else {
            *(float *)(block + 0xB4) = offset;
        }
    }
}

/* Stores one float and two scaled by an arcsecond-sized constant into the block at +32. */
void cam_set_turn_limits(float distance, float yaw, float pitch)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *state = *(char **)(camera + 112);
        char *block = state + 32;

        *(float *)(block + 44) = distance;
        *(float *)(block + 52) = yaw * 4.848137450608192e-06f;
        *(float *)(block + 56) = pitch * 4.848137450608192e-06f;
    }
}

/* Sets one camera tuning value. */
void cam_set_tuning_value(float value)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *state = *(char **)(camera + 112);
        *(float *)(state + 484) = value;
    }
}

/* Sets the camera's on/off value. */
void set_follow_camera_orbit_clamp_mode(int value)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *state = *(char **)(camera + 112);
        *(short *)(state + 16) = (short)value;
    }
}

/* Stores each incoming float only when it is not zero. */
void cam_set_speeds_if_nonzero(float first, float second)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *state = *(char **)(camera + 112);
        char *block = state + 0x60;

        if (first != 0.0f) {
            *(float *)(block + 0xDC) = first;
        }
        if (second != 0.0f) {
            *(float *)(block + 0xE0) = second;
        }
    }
}

/* Sets two camera speed values, skipping any that are zero. */
void cam_set_turn_speeds_if_nonzero(float first, float second)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *state = *(char **)(camera + 112);
        char *block = state + 0x60;

        if (first != 0.0f) {
            *(float *)(block + 228) = first;
        }
        if (second != 0.0f) {
            *(float *)(block + 232) = second;
        }
    }
}

/* Turns on a camera flag. */
void cam_set_snap_flag(void)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *state = *(char **)(camera + 112);
        *(short *)(state + 582) = 1;
    }
}

/* Turns on a camera lock flag. */
void cam_set_lock_flag(void)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *state = *(char **)(camera + 112);
        *(char *)(state + 310) = 1;
    }
}

/* Turns on two input flags for the camera. */
void cam_set_input_flags(void)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *state = *(char **)(camera + 112);
        char *block = state + 448;

        *(int *)(block + 16) |= 3;
    }
}

extern char D_L00_001B8E20[];
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern float math_fast_angle_helper(float);
extern float fast_subtract_rotations(float, float);
extern float math_fabs(float);
extern float cubic_hermite_scalar(float, float, float, float, float);

/* Turns the camera sideways to face a direction. It works out the signed angle between the camera and the target and stores a steering amount. */
float cam_steer_toward_direction(char *object, char *vector, float threshold)
{
    float temporary[4] __attribute__((aligned(16)));
    float first[4] __attribute__((aligned(16)));
    float second[4] __attribute__((aligned(16)));
    float cross[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x70);
    char *output = state + 0x1C0;
    char *direction = state + 0x160;
    char *camera = D_L00_001B8E20;
    char *up = camera + 0x20;
    float dot;
    float length;
    float angle;
    float signedAngle = 0.0f;
    float sign;
    float factor;
    FastVecScale(temporary, up, FastVecDot(vector, up));
    FastVecSub(first, vector, temporary);
    FastVecScale(temporary, up, FastVecDot(direction, up));
    FastVecSub(second, direction, temporary);
    dot = FastVecDot(first, second);
    length = FastVecLength(first);
    if (length == 0.0f) return 0.0f;
    length *= FastVecLength(second);
    if (length == 0.0f) return 0.0f;
    angle = 1.57079632679f - math_fast_angle_helper(dot / length);
    sign = -1.0f;
    FastVecCross(cross, first, up);
    if (FastVecDot(cross, second) >= 0.0f) sign = 1.0f;
    signedAngle = fast_subtract_rotations(3.14159265359f, angle);
    if (threshold != 0.0f && math_fabs(signedAngle) > threshold) return signedAngle;
    factor = cubic_hermite_scalar(-1.0f, 0.0f, 1.0f, 0.0f, signedAngle * 0.63661975f);
    if (factor > 1.0f) factor = 1.0f;
    *(float *)(output + 0x1C) = factor * sign;
    return signedAngle;
}

/* Builds a vector from a1 and the +96 source block, then feeds it to the inner routine. */
void cam_steer_toward_target(char *camera, char *target, float threshold)
{
    char direction[16];

    func_00282CF0_8(direction, target, *(char **)(camera + 112) + 96);
    cam_steer_toward_direction(camera, direction, threshold);
}

/* Stores a non-zero value, then hands it to the inner routine. */
void cam_set_strength_and_steer(char *target, float strength, float threshold)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0 && strength != 0.0f) {
        char *state = *(char **)(camera + 112);

        *(float *)(state + 468) = strength;
        cam_steer_toward_direction(camera, target, threshold);
    }
}

/* Stores the value, then builds a vector and hands it to the inner routine. */
void cam_set_strength_and_steer_target(char *target, float strength, float threshold)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *state = *(char **)(camera + 112);

        *(float *)(state + 468) = strength;
        cam_steer_toward_target(camera, target, threshold);
    }
}


/* func_L00_00425118 is in L00_00425118-g8.c. */

/* Builds three vectors from an owner block, blends the stored value toward the closest of the sampled vector length and the stored reference gap, and writes the remaining gap back. */
void cam_follow_update_reach(char *camera)
{
    char *state = *(char **)(camera + 112);
    char *follow = state + 496;
    char *movement = state + 352;
    float offset[4];
    float reach, maxReach, current;

    if (*(short *)(state + 16) <= 0) return;
    func_00282CF0_4(offset, state, state + 176);
    lerp_vector((float *)movement, movement, (char *)offset, D_L00_001A8900);
    reach = FastVecLength((float *)movement);
    maxReach = *(float *)(movement + 44);
    if (maxReach < reach) {
        reach = maxReach;
        func_00282F20_3((float *)movement, (float *)movement, reach);
        current = *(float *)(movement + 44);
    } else {
        float minReach = maxReach - *(float *)(follow + 48);
        if (reach < minReach) {
            reach = minReach;
            func_00282F20_3((float *)movement, (float *)movement, reach);
        }
        current = *(float *)(movement + 44);
    }
    *(float *)(follow + 48) = current - reach;
}

/* func_L00_00425560 is in L00_004224D0-follow-g8.c. */

/* func_L00_00425A98 is in a separate compilation unit. */

/* func_L00_00425CD0 is in L00_004224D0-g8.c (-G8). */

/* Walks the 64x64 owner table and dispatches every type-5 entry of each populated block. */
/* One 0x30-byte entry of a collision-grid cell (layout as in L00_002D7940-grid.c);
 * entries of type 5 carry an index into the 0x80-byte records at D_L00_001B1F94. */
typedef struct GridCellEntry {
    unsigned char unknown_00[16];
    int type;
    int index;
    unsigned char unknown_18[24];
} GridCellEntry;

/* The grid base pointer uses the measured absolute macro-address form. */
extern char *D_L00_001B1880[] __attribute__((sda));
extern char *D_L00_001B1F94[] __attribute__((sda));

/* Visits every cell of the 64x64 collision grid and passes each type-5 entry's record to func_00282DF0. */
void coll_visit_grid_entries(void)
{
    int y, x, k;

    for (y = 0; y < 64; y++) {
        for (x = 0; x < 64; x++) {
            int idx = y * 64 + x;
            char *base = D_L00_001B1880[0];
            int cell = ((int *)base)[idx];

            if (cell == 0) {
                continue;
            }
            cell += (int)base;
            for (k = 0; k < *(int *)cell; k++) {
                GridCellEntry *entry = (GridCellEntry *)((char *)cell + 16) + k;

                if (entry->type == 5) {
                    FastVecLength(D_L00_001B1F94[0] + (entry->index << 7));
                }
            }
        }
    }
}
