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
extern float math_fabs(float x);
extern float math_step_value_toward_target(float *value, float *velocity, float target, float minimum, float acceleration, float maximum);
extern void snd_stop_voice(int index);
extern int PlayMobySound(int index, int kind, char *object);
extern void FastVecSub(void *out, void *a, void *b);
extern void mat_combine_and_store(void *matrix, void *offset, void *a, void *b);
extern u8 g_lift_sound_table[];
extern u8 g_lift_sound_table_alt[];

/* Moves a lift between two heights and plays a sound while it moves. It carries the hero standing on it (PAL: 50 Hz timings). */
void UpdateTodanoLift_pal(u8 *object)
{
    LiftQuad old_position;
    LiftQuad displacement;
    u8 *vars = *(u8 **)(object + 0x68);

    float target;
    float rate;
    float reference;
    int index;
    qcopy(&old_position, object + 0x10);
    switch (object[0x20]) {
    case 0:
        qcopy(vars + 0x70, object + 0x10);
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (!flag_is_third_pending_set(object)) break;
        if (*(int *)(vars + 0x68))
            target = *(float *)(g_path_waypoint_table + *(int *)(vars + 0x60) * 128 + 0x38);
        else
            target = *(float *)(vars + 0x78);
        if (math_fabs(target - *(float *)(object + 0x18)) < 2.0f) {
            reference = *(float *)(g_path_waypoint_table + *(int *)(vars + 0x60) * 128 + 0x38);
            if (g_hero_state.standing == object && g_hero_state.flags) {
                TryClaimNotice(8, 0x12EC, 1);
                if (g_pad_held_flags & 0x10)
                    *(int *)(vars + 0x68) = (*(int *)(vars + 0x68) + 1) & 1;
            } else if (*(int *)(vars + 0x68)) {
                if (math_fabs(g_hero_state.position[2] - *(float *)(vars + 0x78)) < 4.0f &&
                    vec_distance_xy(g_hero_state.position, object + 0x10) < 24.0f)
                    *(int *)(vars + 0x68) = 0;
            } else {
                if (math_fabs(g_hero_state.position[2] - reference) < 4.0f &&
                    vec_distance_xy(g_hero_state.position, object + 0x10) < 24.0f)
                    *(int *)(vars + 0x68) = 1;
            }
        }
        rate = 0.0056000003f;
        if (*(int *)(vars + 0x68)) {
            if (g_hero_state.position[2] < *(float *)(object + 0x18) - 1.0f &&
                IsPointInCuboid(g_hero_state.position, *(int *)(vars + 0x60))) {
                target += 3.0f;
                rate = 0.0112000005f;
            } else {
                target += 0.5f;
            }
        }
        math_step_value_toward_target((float *)(object + 0x18), (float *)(vars + 0x6C), target, 0.0028000001f, rate, 0.6f);
        if (math_fabs(target - *(float *)(object + 0x18)) < 0.8f) {
            index = *(int *)(vars + 0x80);
            if (index != -1) {
                LiftSound *sound = (LiftSound *)(index * 112 + (s32)g_lift_sound_table);
                if (sound->owner == object && sound->active)
                    snd_stop_voice(index);
            }
            *(int *)(vars + 0x80) = -1;
        } else {
            LiftSound *sound = (LiftSound *)(*(int *)(vars + 0x80) * 112 + (s32)g_lift_sound_table_alt);
            if (sound->owner != object || sound->active == 0)
                *(int *)(vars + 0x80) = PlayMobySound(0, 4, (char *)object);
        }
    }
    FastVecSub(&displacement, object + 0x10, &old_position);
    mat_combine_and_store(vars + 0x20, &displacement, object + 0xF0, object + 0xF0);
}
