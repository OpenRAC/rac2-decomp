#include "include_asm.h"

#include "common.h"
extern void path_apply_move_step_copy(void *);
extern int moby_push_away_from_hit(void *);
extern void vec_scale_to_length(float, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void func_PAL_00274928(void *, void *, void *);
extern void cam_compute_view_direction(void *, void *, int);
extern float FastVecDot(void *, void *);
extern float math_fabs(float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern float ApproachValue(float *, float, float);
extern void vec_set_direction_with_complement(void *, void *, float);
extern void vec_fast_normalize3(void *, void *, void *, float);
extern int PlayMobySound(int, int, void *);
extern int snd_play_from_global_bank(int, int, void *);
extern int snd_set_voice_offset(int, char *);
extern void vec_fast_normalize(void *, void *, void *);
extern float D_001BAFC0[];

int func_PAL_00273D38(char *object)
{
    float delta[4];
    float direction[4];
    float scaled[4];
    float correction[4];
    float length;
    char *state = *(char **)(object + 0x68);
    char *orientation;
    float distance, step, factor;
    int sound;

    path_apply_move_step_copy(object);
    if (moby_push_away_from_hit(object)) {
        orientation = state + 0x10;
        vec_scale_to_length(1.0f, D_001BAFC0, D_001BAFC0);
        FastVecCross(delta, D_001BAFC0, state);
        func_PAL_00274928(object, orientation, delta);
        cam_compute_view_direction(object + 0x10, direction, 1);
        if (FastVecDot(direction, D_001BAFC0) > 0.7f) {
            distance = FastVecDot(state, D_001BAFC0);
            step = distance * 0.5f;
            if (math_fabs(step) < 0.040000003f)
                step = 0.0f;
            vec_scale_to_length(distance + step, scaled, D_001BAFC0);
            FastVecSub(state, state, scaled);
            if (step == 0.0f) {
                length = FastVecLength(state);
                ApproachValue(&length, 0.040000003f, 0.0028000001f);
                vec_scale_to_length(length, state, state);
                FastVecCross(correction, state, D_001BAFC0);
                factor = FastVecLength(correction) * -0.5f;
                factor /= *(float *)(state + 0x2C);
                vec_set_direction_with_complement(correction, correction, factor);
                vec_fast_normalize3(orientation, orientation, correction, 0.1f);
            }
            if (math_fabs(distance) >= 0.040000003f) {
                if (*(u8 *)(state + 0x5E) != 0xFF)
                    sound = PlayMobySound(*(u8 *)(state + 0x5E), 0, object);
                else
                    sound = snd_play_from_global_bank(8, 0, object);
                if (sound != -1)
                    snd_set_voice_offset(sound, state + 0x20);
            }
        } else {
            vec_fast_normalize(state, state, D_001BAFC0);
        }
    }
    return 0;
}
