#include "include_asm.h"

#include "common.h"
extern char g_sound_state[];
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, char *);
extern int g_moby_l11_table __attribute__((sda));
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float vec_distance_xy(void *, void *);
extern char g_hero_position[];
/* Stops the object's sound if its slot still belongs to it, then forgets the slot. */
static inline void stop_owned_sound(char *state, char *p)
{
    int slot = *(int *)(state + 0x14);

    if (slot != -1) {
        char *e = g_sound_state + slot * 0x70;

        if (*(char **)(e + 0x88) == p && *(unsigned char *)(e + 0x74))
            snd_stop_voice(slot);
    }
    *(int *)(state + 0x14) = -1;
}
extern void snd_stop_voice(int a);
extern char g_sound_state[];
extern int PlayMobySound(int index, int a1, char *a2);

/* Five-stage mover driven by the parent's state byte: when the parent reaches 2 it starts its
   sound and moves out along its +0xE0 direction over half a turn (pi/120 a frame); when the
   parent leaves 2 it does the same back, only while D_00189EA0 is more than 6 away, and at a
   full turn returns to its saved position and waits again. */
void sliding_part_update_pal(char *p)
{
    char *state = *(char **)(p + 0x68);
    char *parent = (char *)(g_moby_l11_table + (*(int *)(state + 8) << 8));
    float offset[4];

    switch (*(unsigned char *)(p + 0x20)) {
    case 0:
        *(unsigned char *)(p + 0x20) = 1;
        *(float *)(state + 0xC) = 3.1415927f;
        *(float *)(state + 0x10) = 0;
        qcopy(state + 0x20, p + 0x10);
        *(unsigned short *)(p + 0x34) |= 0x800;
    case 1:
        if (*(unsigned char *)(parent + 0x20) == 2) {
            char *e = g_sound_state + *(int *)(state + 0x14) * 0x70;

            if (*(char **)(e + 0x88) != p || !*(unsigned char *)(e + 0x74))
                *(int *)(state + 0x14) = PlayMobySound(0, 4, p);
            *(unsigned char *)(p + 0x20) = 2;
            *(float *)(state + 0xC) = 3.1415927f;
            *(float *)(state + 0x10) = 0;
        } else {
            stop_owned_sound(state, p);
        }
        break;
    case 2:
        *(float *)(state + 0x10) += 0.031415932f;
        *(float *)(state + 0xC) = FastAddRotations(*(float *)(state + 0xC), 0.031415932f);
        if (*(float *)(state + 0x10) >= 3.1415927f) {
            stop_owned_sound(state, p);
            *(unsigned char *)(p + 0x20) = 3;
        } else {
            vec_scale_to_length((char *)offset, p + 0xE0, (math_fast_sin_or_cos_a(*(float *)(state + 0xC)) + 1.0f) * 5.0f);
            FastVecAdd(p + 0x10, (char *)offset, state + 0x20);
        }
        break;
    case 3:
        if (*(unsigned char *)(parent + 0x20) != 2) {
            char *e = g_sound_state + *(int *)(state + 0x14) * 0x70;

            if (*(char **)(e + 0x88) != p || !*(unsigned char *)(e + 0x74))
                *(int *)(state + 0x14) = PlayMobySound(0, 4, p);
            *(unsigned char *)(p + 0x20) = 4;
        } else {
            stop_owned_sound(state, p);
        }
        break;
    case 4:
        if (vec_distance_xy(p + 0x10, g_hero_position) > 6.0f) {
            *(float *)(state + 0x10) += 0.031415932f;
            *(float *)(state + 0xC) = FastAddRotations(*(float *)(state + 0xC), 0.031415932f);
            if (*(float *)(state + 0x10) >= 6.2831855f) {
                stop_owned_sound(state, p);
                *(unsigned char *)(p + 0x20) = 1;
                *(float *)(state + 0xC) = 3.1415927f;
                *(float *)(state + 0x10) = 0;
                qcopy(p + 0x10, state + 0x20);
            } else {
                vec_scale_to_length((char *)offset, p + 0xE0, (math_fast_sin_or_cos_a(*(float *)(state + 0xC)) + 1.0f) * 5.0f);
                FastVecAdd(p + 0x10, (char *)offset, state + 0x20);
            }
        }
        break;
    }
}
