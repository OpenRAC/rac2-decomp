#include "names.h"
/* func_PAL_L20_00450D78, the PAL copy of func_L20_0044B100: the same C, where the motion
 * range constants are scaled by 6/5 and the rate takes the 50 Hz scale. */
/* Creates the child, copies both full vectors and initializes its motion.
 * Returns the created object or null; the fifth integer slot and float input are preserved. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float g_homing_shot_speed_scale __attribute__((sda));
extern int g_homing_shot_spark_count __attribute__((sda));

extern void *CreateMoby(int);
extern void moby_init_child_from_parent(u8 *, u8 *);
extern float math_random_angle(void);
extern float math_random_float_range(float a, float b);
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void part_l11_spawn_spark_ring_pal(char *, int);
extern int snd_play_from_class_bank(int, int, char *, int);

char *homing_l20_shot_spawn_pal(char *template, char *position, char *direction, char *target_pos, int travel_frames,
                        float speed) {
    char *homing_shot;
    char *state;
    char *dst;
    TI128 buf;
    float r;

    homing_shot = CreateMoby(0x12F7);
    if (homing_shot != 0) {
        moby_init_child_from_parent((u8 *)homing_shot, (u8 *)template);
        dst = homing_shot + 0x10;
        qcopy(dst, position);
        *(float *)(homing_shot + 0x2C) =
            *(float *)(*(u32 *)(homing_shot + 0x24) + 0x24) * g_homing_shot_speed_scale;
        state = *(char **)(homing_shot + 0x68);
        qcopy(state, direction);
        *(float *)(state + 0x20) = speed;
        *(float *)(state + 0x24) = math_random_angle();
        *(float *)(state + 0x28) = math_random_float_range(0.062831864f, 0.12566373f);
        *(int *)(state + 0x30) = 0;
        r = IntToFloat(travel_frames);
        *(float *)(state + 0x34) = 1.0f / ((r * 5.0f + 2.0f) * 0.16666667f);
        FastVecScale(&buf, direction, (float)(travel_frames >> 1));
        FastVecAdd(&buf, &buf, position);
        FastVecSub(state + 0x10, target_pos, &buf);
        r = FastVecLength(state);
        vec_scale_to_length(state + 0x10, state + 0x10, r);
        part_l11_spawn_spark_ring_pal(dst, g_homing_shot_spark_count);
        snd_play_from_class_bank(0, 0, homing_shot, 0x12F7);
    }
    return homing_shot;
}
