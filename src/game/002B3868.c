#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned char u8;

extern float func_00282E80_1(char *, float *);

extern float func_00282C48_6(float);

/* Sets the first pending flag on the object and reports whether it was newly set. */
s32 flag_set_first_pending(u8 *moby) {
 u8 flags=moby[0xbe];
 if(((flags^1)&1)!=0) {moby[0xbe]=flags|1;return 1;}
 return 0;
}

/* Sets the second pending flag and reports whether it was newly set. */
s32 flag_set_second_pending(u8 *moby) {
    u8 flags = moby[0xBE];
    if ((flags & 2) == 0) {
        moby[0xBE] = flags | 2;
        return 1;
    }
    return 0;
}

/* Tells whether the third pending flag on the object is set. */
s32 flag_is_third_pending_set(u8 *moby) {
    return moby[0xBE] & 4;
}

extern float vec_distance_xy(char *, float *);
extern float fast_vec_dist(char *, char *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern int D_001A8CA0 __attribute__((sda));
extern int g_hero_moby;

/* Rates how good a target is to aim at: its distance, made worse when it is off to the side, and worse again for the player. */
float weapon_rate_aim_target(char *object, char *target)
{
    char *position = object + 0x10;
    char *destination = target + 0x10;
    float distance;
    float value = vec_distance_xy(position, (float *)destination);
    if (D_001A8CA0 != 0)
        value = fast_vec_dist(position, destination);
    distance = value;
    if (D_001A8CA0 == 0) {
        float angle = mat_fast_helper_a(*(float *)(target + 0x10) - *(float *)(object + 0x10),
                                  *(float *)(target + 0x14) - *(float *)(object + 0x14));
        angle = FastDiffRots(angle, *(float *)(object + 0xF8));
        distance = distance + angle * distance;
    }
    if (target == (char *)g_hero_moby)
        distance += 42.0f;
    return distance;
}

/* func_002B39A0 is matched in 002B39A0-g8.c. */

/* Calls a callee on (second pointer, first pointer + 16); if the result is not below the first float argument it returns 0, otherwise it evaluates a second callee on (a float at second+8 minus a float at first+24) and returns 1 when that is below the second float argument, else 0. */
/* Checks that the target is close enough in the flat distance and also close enough in height. */
int weapon_is_target_in_range(char *moby, char *point, float maxRange, float maxHeight)
{
    float distance = func_00282E80_1(point, (float *)(moby + 16));

    if (!(distance < maxRange))
        return 0;
    if (func_00282C48_6(*(float *)(point + 8) - *(float *)(moby + 24)) < maxHeight)
        return 1;
    return 0;
}



typedef struct {
    int reserved;
    int value;
    char remainder[0xA428];
} Record_2B4038;
extern Record_2B4038 D_00240450[];

/* Tells whether the saved record at the given index holds the given value. */
int save_is_record_value(int value, int index) {
    return D_00240450[index].value == value;
}

typedef int PoseVector128 __attribute__((mode(TI)));
typedef struct {
    PoseVector128 initial, previous, current, delta;
    PoseVector128 matrix[4];
    float angles[4];
    PoseVector128 change[4];
} PoseWorkspace;
extern void euler_to_matrix(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void multiply_matrix(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void mat_get_euler_angles(float *, float *);

/* Turns the object by the given angles so that a chosen point stays where it is, moving the object to make up for it. */
void moby_rotate_about_point(char *self, PoseVector128 *point, float x, float y, float z)
{
    PoseWorkspace work;
    work.initial = *point;
    euler_to_matrix(work.matrix, self + 0xF0);
    transform_vector(&work.previous, &work.initial, work.matrix);
    work.angles[0] = x;
    work.angles[1] = y;
    work.angles[2] = z;
    euler_to_matrix(work.change, work.angles);
    multiply_matrix(work.matrix, work.matrix, work.change);
    transform_vector(&work.current, &work.initial, work.matrix);
    FastVecSub(&work.delta, &work.previous, &work.current);
    FastVecAdd(self + 0x10, self + 0x10, &work.delta);
    mat_get_euler_angles((float *)work.matrix, (float *)(self + 0xF0));
}


/* func_002B41A8 is matched in 002B41A8.c. */

/* func_002B44C0 is defined in 002B44C0-sway-g0.c. */

extern int D_001AA0F0 __attribute__((sda));

/* Stores a value in a global setting. */
void request_set_setting_a(int value) {
    D_001AA0F0 = value;
}

extern int D_001AA0F4 __attribute__((sda));

/* Stores a value in a second global setting. */
void request_set_setting_b(int value) {
    D_001AA0F4 = value;
}

extern int g_requested_game_mode __attribute__((sda));

/* Tells whether the current request slot is the given one. */
int request_is_current_slot(int value) {
    return g_requested_game_mode == value;
}

/* func_002B49E0 is matched in 002B49E0-g8.c. */

/* func_002B4B70 is matched in 002B4B70-g8.c. */



/* func_002B4C18 is matched in 002B3868-g8.c (small data through $gp). */

extern char *moby_get_controller(void *);
extern float FastAddRotations(float, float);
extern int FastDecTimer(short *);
extern int math_random_int_range(int, int);
extern int moby_step_controller(void *, void *, float);

/* Turns toward the target by a limited angle (with an optional side-to-side swing), then runs the movement step. */
int moby_turn_toward_target_and_step(char *self, float *target, float amount)
{
    char *data = moby_get_controller(self);
    float angle;
    if (data == 0)
        return 8;
    angle = mat_fast_helper_a(target[0] - *(float *)(self + 0x10),
                         target[1] - *(float *)(self + 0x14));
    angle = FastAddRotations(angle, amount);
    if (*(float *)(data + 0xDC) != 0.0f) {
        angle = FastAddRotations(angle, *(float *)(data + 0xDC));
        if (FastDecTimer((short *)(data + 0xE0))) {
            *(float *)(data + 0xDC) = -*(float *)(data + 0xDC);
            *(short *)(data + 0xE0) = math_random_int_range(*(short *)(data + 0xE2), *(short *)(data + 0xE4));
        }
    }
    return moby_step_controller(self, target, angle);
}


/* func_002B50E0 is matched in 002B50E0.c. */

extern int moby_step_controller(void *, void *, float);

/* Runs the movement step on an object using its own position and heading. */
int moby_step_at_own_position(char *moby) {
    return moby_step_controller(moby, moby + 0x10, *(float *)(moby + 0xF8));
}
