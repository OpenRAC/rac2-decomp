#include "include_asm.h"

#include "common.h"
typedef int LiftQuad __attribute__((mode(TI)));
extern u8 *g_path_waypoint_table MACRO_ADDR;
typedef struct {
    u8 pad[0x80]; f32 position[4];
    u8 pad90[0x33c - 0x90]; u8 *standing; s32 flags;
} LiftPlayer;
extern LiftPlayer g_hero_state;
extern int g_pad_held_flags NOT_SDA;
typedef struct { u8 pad[0x74]; u8 active; u8 pad75[0x13]; u8 *owner; } LiftSound;
extern u8 g_sound_state[];
extern void moby_set_state(u8 *object, int animation, int frame);
extern int flag_is_third_pending_set(u8 *object);
extern float math_fabs(float x);
extern int TryClaimNotice(int channel, int message, int mode);
extern float vec_distance_xy(void *a, void *b);
extern int IsPointInCuboid(void *point, int index);
extern float math_step_value_toward_target(float *value, float *velocity, float target, float minimum, float acceleration, float maximum);
extern void snd_stop_voice(int index);
extern int PlayMobySound(int index, int kind, char *object);
extern void FastVecSub(void *out, void *a, void *b);
extern void mat_combine_and_store(void *matrix, void *offset, void *a, void *b);

void UpdateTodanoLift_us2(u8 *object)
{
    LiftQuad oldPosition;
    LiftQuad displacement;
    u8 *data = *(u8 **)(object + 0x68);

    float target;
    float rate;
    float reference;
    int index;
    qcopy(&oldPosition, object + 0x10);
    switch (object[0x20]) {
    case 0:
        qcopy(data + 0x70, object + 0x10);
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (!flag_is_third_pending_set(object)) break;
        if (*(int *)(data + 0x68))
            target = *(float *)(g_path_waypoint_table + *(int *)(data + 0x60) * 128 + 0x38);
        else
            target = *(float *)(data + 0x78);
        if (math_fabs(target - *(float *)(object + 0x18)) < 2.0f) {
            reference = *(float *)(g_path_waypoint_table + *(int *)(data + 0x60) * 128 + 0x38);
            if (g_hero_state.standing == object && g_hero_state.flags) {
                TryClaimNotice(8, 0x12EC, 1);
                if (g_pad_held_flags & 0x10)
                    *(int *)(data + 0x68) = (*(int *)(data + 0x68) + 1) & 1;
            } else if (*(int *)(data + 0x68)) {
                if (math_fabs(g_hero_state.position[2] - *(float *)(data + 0x78)) < 4.0f &&
                    vec_distance_xy(g_hero_state.position, object + 0x10) < 24.0f)
                    *(int *)(data + 0x68) = 0;
            } else {
                if (math_fabs(g_hero_state.position[2] - reference) < 4.0f &&
                    vec_distance_xy(g_hero_state.position, object + 0x10) < 24.0f)
                    *(int *)(data + 0x68) = 1;
            }
        }
        rate = 0.003888888983055949f;
        if (*(int *)(data + 0x68)) {
            if (g_hero_state.position[2] < *(float *)(object + 0x18) - 1.0f &&
                IsPointInCuboid(g_hero_state.position, *(int *)(data + 0x60))) {
                target += 3.0f;
                rate = 0.007777777966111898f;
            } else {
                target += 0.5f;
            }
        }
        math_step_value_toward_target((float *)(object + 0x18), (float *)(data + 0x6c), target, 0.0019444444915279746f, rate, 0.5f);
        if (math_fabs(target - *(float *)(object + 0x18)) < 0.8f) {
            index = *(int *)(data + 0x80);
            if (index != -1) {
                LiftSound *sound = (LiftSound *)(index * 112 + (s32)g_sound_state);
                if (sound->owner == object && sound->active)
                    snd_stop_voice(index);
            }
            *(int *)(data + 0x80) = -1;
        } else {
            LiftSound *sound = (LiftSound *)(*(int *)(data + 0x80) * 112 + (s32)g_sound_state);
            if (sound->owner != object || sound->active == 0)
                *(int *)(data + 0x80) = PlayMobySound(0, 4, (char *)object);
        }
    }
    FastVecSub(&displacement, object + 0x10, &oldPosition);
    mat_combine_and_store(data + 0x20, &displacement, object + 0xf0, object + 0xf0);
}
