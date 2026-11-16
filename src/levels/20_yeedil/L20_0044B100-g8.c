#include "names.h"
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
extern void part_l11_spawn_spark_ring(char *, int);
extern int snd_play_from_class_bank(int, int, char *, int);

/* Creates a homing shot (moby class 4855) at a position, aimed at a target, and returns it. */
char *homing_l20_shot_spawn(char *template, char *position, char *direction, char *target_pos, int travel_frames,
                        float power) {
    char *shot;
    char *state;
    char *pos;
    TI128 predicted;
    float value;

    shot = CreateMoby(0x12F7 /* moby class 4855 */);
    if (shot != 0) {
        moby_init_child_from_parent((u8 *)shot, (u8 *)template);
        pos = shot + 0x10;
        qcopy(pos, position);
        *(float *)(shot + 0x2C) =
            *(float *)(*(u32 *)(shot + 0x24) + 0x24) * g_homing_shot_speed_scale;
        state = *(char **)(shot + 0x68);
        qcopy(state, direction);
        *(float *)(state + 0x20) = power;
        *(float *)(state + 0x24) = math_random_angle();
        *(float *)(state + 0x28) = math_random_float_range(0.052359886f, 0.10471977f);
        *(int *)(state + 0x30) = 0;
        value = IntToFloat(travel_frames);
        *(float *)(state + 0x34) = 1.0f / value;
        FastVecScale(&predicted, direction, (float)(travel_frames >> 1));
        FastVecAdd(&predicted, &predicted, position);
        FastVecSub(state + 0x10, target_pos, &predicted);
        value = FastVecLength(state);
        vec_scale_to_length(state + 0x10, state + 0x10, value);
        part_l11_spawn_spark_ring(pos, g_homing_shot_spark_count);
        snd_play_from_class_bank(0, 0, shot, 0x12F7);
    }
    return shot;
}
