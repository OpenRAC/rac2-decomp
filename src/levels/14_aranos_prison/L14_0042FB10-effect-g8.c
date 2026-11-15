#include "common.h"

extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern float vec_distance_xy(void *, void *);
extern int FloatToInt(float);
extern int PlayMobySound(int, int, void *);
extern void moby_set_state(void *, int, int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void snd_stop_voice(int);
extern void moby_set_flag_bit(void *, int);
extern void moby_mark_table_entry_flagged(int);

typedef struct {
    char pad[0x80];
    float pos[4];
    char gap[0x2AC];
    void *owner;
    int active;
} PrisonHero;

extern PrisonHero g_hero_state;
extern unsigned char g_sound_state[];
extern unsigned char *g_moby_l14_pool __attribute__((sda));
/* The second read of the same pointer uses absolute addressing. */
extern unsigned char *D_L14_001B259C_1[] __attribute__((sda));
extern unsigned char D_001395E3 NOT_SDA;

/* Pulses a glowing marker with a looping sound. When the player reaches it, the sound stops and the linked objects are triggered. */
void glow_marker_update(unsigned char *object)
{
    float pos[4];
    unsigned char *state = *(unsigned char **)(object + 0x68), *entry, *soundSlot;
    int glow, soundId;
    float distance;

    if (!state)
        return;
    *(float *)(state + 8) = FastAddRotations(*(float *)(state + 8), 0.10471977293491364f);
    glow = FloatToInt((math_fast_sin_or_cos_b(*(float *)(state + 8)) * 4.0f - 3.0f) * 128.0f);
    if (glow > 128)
        glow = 128;
    else if (glow < 32)
        glow = 32;

    if (object[0x20] == 0) {
        *(unsigned short *)(object + 0x34) |= 16;
        moby_set_state(object, 1, -1);
        *(int *)(state + 0x14) = -1;
    } else if (object[0x20] == 1) {
        soundSlot = g_sound_state + *(int *)(state + 0x14) * 112;
        if (*(void **)(soundSlot + 0x88) != object || !soundSlot[0x74])
            *(int *)(state + 0x14) = PlayMobySound(1, 4, object);
        moby_transform_joint_to_world(object, 0, pos);
        distance = vec_distance_xy(g_hero_state.pos, pos);
        *(int *)(state + 0xC) = 0;
        if (g_hero_state.owner == object && g_hero_state.active && distance < 0.5f) {
            moby_set_state(object, 2, -1);
            soundId = *(int *)(state + 0x14);
            if (soundId != -1) {
                entry = g_sound_state + soundId * 112;
                if (*(void **)(entry + 0x88) == object && entry[0x74])
                    snd_stop_voice(soundId);
            }
            *(int *)(state + 0x14) = -1;
            PlayMobySound(0, 0, object);
            PlayMobySound(2, 0, object);
            D_001395E3 = 1;
            if (*(int *)state != -1) {
                moby_set_flag_bit(g_moby_l14_pool + (*(int *)state << 8), 1);
                {
                    int child = *(int *)(state + 4);
                    unsigned char *base = D_L14_001B259C_1[0];
                    moby_set_flag_bit(base + (child << 8), 1);
                }
            }
            moby_mark_table_entry_flagged(*(int *)(state + 0x10));
        }
        *(unsigned int *)(object + 0x78) = glow | (int)0x80000000;
    } else if (object[0x20] == 2) {
        if (!*(int *)(state + 0xC))
            *(int *)(state + 0xC) = 1;
        {
            unsigned int green = (glow << 8) | 0x80000000;
            *(unsigned int *)(object + 0x78) = (glow << 16) | green;
        }
    }
}
