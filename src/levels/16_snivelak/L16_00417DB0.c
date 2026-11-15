#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));
typedef struct {
    Vector128 player, velocity, previous, point;
} SparkWorkspace;

extern char *D_L16_001B2B1C MACRO_ADDR;
/* Resident position and collision pointer, at +0 and +0x2210. */
extern struct {
    float position[4];
    char pad[0x2200];
    char *collision;
} D_00189EA0;
extern struct {
    char pad[0x18];
    char *owner;
    char pad1[4];
    Vector128 point;
} D_L16_001BFF40;
/* These offsets are relative to a 0x70-stride sound anchor, not an array element extent. */
struct SoundAnchor {
    char pad[0x74];
    unsigned char active;
    char pad1[0x13];
    char *owner;
};
extern char g_sound_state[];

extern int IsPointInCuboid(void *, int);
extern float math_random_float_range(float, float);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void moby_bind_small_data_words(void *);
extern int moby_count_group_not_in_state(int, int);
extern int coll_test_point(void *, int, void *, float);
extern int PlayMobySound(int, int, char *);
extern int math_random_int_below(int);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(float *, float, float, float);
extern float math_random_signed_float_range(float, float);
/* The integer and FP argument banks retain their independent EE ABI order. */
extern void *part_spawn_ground_effect(void *, int, unsigned int, float, float, int, int, void *, float, int);
extern void snd_stop_voice(int);

/* Animate the emitter and spawn three sparks at the qualifying collision point. */
void UpdateSnivelakContactSparks(char *object)
{
    SparkWorkspace local;
    char *state = *(char **)(object + 0x68);
    char *target;
    struct SoundAnchor *sound;
    float speed, firstAngle, secondAngle, magnitude;
    int i, index, handle;

    if (*(unsigned char *)(object + 0x20) == 0) {
        object[0x20] = 1;
        *(int *)(object + 0x98) = 0;
        *(unsigned short *)(object + 0x34) |= 0x41;
    }
    if (*(unsigned char *)(object + 0x20) == 1) {
        target = D_L16_001B2B1C + *(int *)state*0x100;
        if (target == 0 || *(unsigned char *)(target + 0x20) == 0xfe || *(unsigned char *)(target + 0x20) == 0xfd) {
            if (IsPointInCuboid(&g_hero_position, *(int *)(state + 8)) != 0) {
                int snapshot = *(int *)(*(char **)(object + 0x24) + 0x10);
                object[0x20] = 2;
                *(int *)(object + 0x98) = snapshot;
            }
        }
    }
    if (*(unsigned char *)(object + 0x20) != 2)
        return;
    *(float *)(state + 0x10) += *(float *)(state + 0x14);
    *(float *)(state + 0x18) += *(float *)(state + 0x1c);
    if (*(float *)(state + 0x10) >= 8.0f)
        *(float *)(state + 0x10) -= 8.0f;
    if (*(float *)(state + 0x18) >= 8.0f)
        *(float *)(state + 0x18) -= 8.0f;
    *(float *)(state + 0x14) = math_random_float_range(0.003f, 0.005f);
    *(float *)(state + 0x1c) = math_random_float_range(0.001f, 0.0025f);
    gfx_add_draw_callback_third(moby_bind_small_data_words, object);
    if (moby_count_group_not_in_state(*(int *)(state + 4), -1) == 0) {
        *(int *)(object + 0x98) = 0;
        object[0x20] = 3;
    }
    qcopy(&local.player, &g_hero_position);
    ((float *)&local.player)[2] = ((float *)&local.player)[2] + 0.75f;
    if (coll_test_point(&local.player, 0, g_hero_position.collision, 0.5f) != 0 && D_L16_001BFF40.owner != 0 && *(short *)(D_L16_001BFF40.owner + 0xaa) == 0x10fb) {
        qcopy(&local.point, &D_L16_001BFF40.point);
        {
            char *audioBank = g_sound_state;
            for (i = 2; i >= 0; i--) {
                int loopHandle = *(int *)(state + 12);
                struct SoundAnchor *loopSound = (struct SoundAnchor *)(audioBank + 0x70*loopHandle);
                if (loopSound->owner != object || loopSound->active == 0)
                    *(int *)(state + 12) = PlayMobySound(1, 4, object);
                speed = math_random_float_range(1.0f, 2.0f);
                index = math_random_int_below(2);
                if (index == 0)
                    index--;
                firstAngle = math_random_angle();
                secondAngle = math_random_float_range(0.3490658998f, 1.535889864f);
                magnitude = math_random_float_range(0.05f, 0.1f);
                vec_build_spherical_offset((float *)&local.velocity, magnitude, firstAngle, secondAngle);
                qcopy(&local.previous, &local.point);
                ((float *)&local.point)[0] += math_random_signed_float_range(0.0f, 0.15f);
                ((float *)&local.point)[1] += math_random_signed_float_range(0.0f, 0.15f);
                ((float *)&local.point)[2] += math_random_signed_float_range(0.0f, 0.15f);
                part_spawn_ground_effect(&local.point, 15, 0xff803040u, speed*0.1f, speed, 0, index, &local.velocity, 0.006f, 0);
            }
        }
        return;
    }
    handle = *(int *)(state + 12);
    if (handle != -1) {
        sound = (struct SoundAnchor *)(g_sound_state + 0x70*handle);
        if (sound->owner == object && sound->active != 0)
            snd_stop_voice(handle);
    }
    *(int *)(state + 12) = -1;
}
