#include "common.h"
#include "include_asm.h"

extern void cam_compute_view_direction(void *, void *, int);
extern char *CreateMoby(int);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecCross(float *, float *, float *);

/* func_L23_0041E418 is defined in L23_0041E418-g8.c (this unit has no $gp access for it). */

/* func_L23_0041E5B0 is defined in its dedicated source unit. */

/* Creates a shot object that flies in a direction and carries a damage amount. */
char *directed_shot_create(char *pos, char *dir, float *damage) {
    char axis[16];
    char scaled[16];
    char *obj;
    char *state;
    cam_compute_view_direction(pos, axis, 1);
    obj = CreateMoby(0x118E /* moby class 4494 */);
    if (obj) {
        state = *(char **)(obj + 0x68);
        *(float *)(state + 0x1C) = *damage;
        *(int *)(state + 0x10) = 0x3C;
        *(u8 *)(obj + 0x30) = 0xFF;
        *(u16 *)(obj + 0x32) = 0xFF;
        *(u8 *)(obj + 0x20) = 0;
        qcopy(obj + 0x10, pos);
        qcopy(state, dir);
        *(int *)(state + 0x18) = 0;
        *(int *)(state + 0x14) = 0;
        vec_scale_to_length((float *)scaled, (float *)dir, 1.0f);
        qcopy(obj + 0xC0, scaled);
        FastVecCross((float *)(obj + 0xD0), (float *)(obj + 0xC0), (float *)axis);
        vec_scale_to_length((float *)(obj + 0xD0), (float *)(obj + 0xD0), 1.0f);
        FastVecCross((float *)(obj + 0xE0), (float *)(obj + 0xD0), (float *)(obj + 0xC0));
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
    }
    return obj;
}


/* func_L23_00422668 is matched in L23_00422668.c (built with -frac2-qcopy -frac2-no-annulled-wide-stores). */

/* func_L23_00422798 is matched in L23_00422798-g8.c (built with -frac2-zero-ti-por). */

/* func_L23_00422A30 is defined in L23_00422A30-g8.c. */

/* func_L23_00422E08 is defined in L23_00422E08-g8.c. */


/* func_L23_00423380 is defined in L23_0041E418-g8.c (this unit has no $gp access for it). */

/* func_L23_004234C0 is defined in L23_0041E418-g8.c (this unit has no $gp access for it). */

/* func_L23_004236B8 is matched in L23_004236B8-g8.c (built with -ffast-math). */

/* func_L23_00425568 is matched in L23_00425568.c (built with -frac2-qcopy). */

/* func_L23_004256F0 is matched in L23_004256F0.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_00425848 is matched in L23_00425848.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_00425AF8 is defined in L23_00425AF8-g8.c. */

typedef int TI16 __attribute__((mode(TI)));

extern void FastVecSub(float *, float *, float *);

extern void FastVecCross(float *, float *, float *);

extern void vec_scale_to_length(float *, float *, float);

extern int math_random_int_range(int, int);

extern float math_fast_float_g(float);

extern float math_fast_sin_or_cos_b(float);

extern void FastVecScale(float *, float *, float);

extern void FastVecAdd(float *, float *, float *);

extern float g_camera_l23_position[];

/* builds two vectors from the sources, rotates one by the measured angle and writes the result */
/* Works out a curve control point by turning a sideways direction by a random angle. */
void math_compute_curve_control_point(u8 *obj, float *dst, TI16 *src1, TI16 *src2, float scale) {
    TI16 loc[6];
    TI16 va;
    TI16 vb;
    u8 *vars;
    s16 randRange;
    s32 angle_deg;
    float angle;
    float offset;

    va = *src2;
    vb = *src1;
    loc[1] = va;
    loc[0] = vb;
    vars = *(u8 **)(obj + 0x68);
    FastVecSub((float *)&loc[2], (float *)&loc[0], (float *)&loc[1]);
    FastVecSub((float *)&loc[3], (float *)&loc[0], g_camera_l23_position);
    FastVecCross((float *)&loc[4], (float *)&loc[3], (float *)&loc[2]);
    vec_scale_to_length((float *)&loc[4], (float *)&loc[4], 1.0f);
    randRange = *(s16 *)(vars + 0xC);
    angle_deg = math_random_int_range(-randRange, randRange);
    angle_deg = (((s32)*(u16 *)(obj + 0x96) << *(s16 *)(vars + 0xE)) + angle_deg) % 360 - 180;
    angle = math_fast_float_g((float)angle_deg * 0.017453294f);
    offset = math_fast_sin_or_cos_b(angle) * scale;
    FastVecScale((float *)&loc[5], (float *)&loc[4], offset);
    FastVecAdd(dst, (float *)&loc[0], (float *)&loc[5]);
}

/* func_L23_00426248 is defined in L23_00426248-g8.c. */

/* func_L23_004265D0 is defined in L23_004265D0-g8.c. */
extern void boss_part_init_health(u8 *);
extern void boss_part_count_frame(u8 *);

/* Per-frame update of the boss part object: runs its main update, then counts a frame. */
void boss_part_update(u8 *moby) {
    boss_part_init_health(moby);
    boss_part_count_frame(moby);
}

/* func_L23_004277E8 is matched in L23_0041E418-g8.c */


/* increments the 16-bit counter at object + 0x96 while it stays below 0xFFFF */
/* Counts one more frame for the object, stopping at the largest value. */
void boss_part_count_frame(u8 *moby) {
    u16 *counter = (u16 *)(moby + 0x96);
    u16 value = *counter;

    if (value <= 0xFFFE) {
        *counter = value + 1;
    }
}

/* func_L23_004278D8 is matched in L23_004278D8-g8.c (built with -g). */

/* func_L23_00427CE8 is matched in L23_00427CE8-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L23_00428490 is defined in L23_00428490-g8.c. */

/* func_L23_00428CF8 is matched in L23_00428CF8-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier -frac2-no-annulled-wide-stores). */

/* func_L23_00429098 is defined in L23_00429098-g8.c. */

/* func_L23_00429430 is defined in its dedicated source unit. */


/* func_L23_00429DC8 is matched in L23_00429DC8-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier -frac2-zero-ti-por). */

/* increments the 16-bit counter at object + 0x96 while it stays below 0xFFFF */
/* Counts one more frame for the object, stopping at the largest value. */
void effect_controller_count_frame(u8 *moby) {
    u16 *counter = (u16 *)(moby + 0x96);
    u16 value = *counter;

    if (value <= 0xFFFE) {
        *counter = value + 1;
    }
}

/* func_L23_0042A018 is defined in L23_0042A018-g8.c. */

/* func_L23_0042A438 is defined in L23_0042A438-g8.c. */

/* func_L23_0042A8C0 is defined in L23_0042A8C0-g8.c. */

/* Defined in L23_0042AD10.c. */

/* increments the 16-bit counter at object + 0x96 while it stays below 0xFFFF */
/* Counts one more frame for the object, stopping at the largest value. */
void counter_effect_count_frame(u8 *moby) {
    u16 *counter = (u16 *)(moby + 0x96);
    u16 value = *counter;

    if (value <= 0xFFFE) {
        *counter = value + 1;
    }
}

/* func_L23_0042ADB0 is defined in L23_0042ADB0-g8.c. */

extern void cam_swingshot_update(void);

extern void cam_aim_at_hero(s32);

/* prepares the shared object then hands it to the shared starter */
/* Prepares the shared object and then starts it with the given value. */
void shared_object_start_with_value(s32 param) {
    cam_swingshot_update();
    cam_aim_at_hero(param);
}

/* func_L23_004402D8 is matched in L23_004402D8-g8.c (built with -g). */
