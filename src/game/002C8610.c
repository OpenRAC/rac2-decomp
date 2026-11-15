#include "common.h"

extern float D_001B5348;
extern int D_001B1DD4[] __attribute__((sda));
extern int D_001B1DD4_sda __attribute__((sda));
extern int g_game_time[] __attribute__((sda));
extern char D_001B1DF0[] __attribute__((sda));
extern char D_001B5580[];

extern int FastDecTimer(void *);
extern void part_kill(void *);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

/* Updates a short-lived particle: it fades as its counter runs down, spins a little, drifts, and is removed at the end. */
void part_update_fading_spin(char *particle)
{
    float wobble[4];
    char *params = particle + 0x20;
    char *position;
    int remaining;
    int header;

    if (*(float *)(particle + 0x18) - D_001B5348 < -7.0f ||
        (*(int *)(params + 0x14) != 0 && FastDecTimer(particle + 0xA) != 0)) {
        remaining = *(int *)(params + 0x10) - 1;
        *(int *)(params + 0x10) = remaining;
        if (remaining <= 0) {
            part_kill(particle);
            D_001B1DD4_sda = D_001B1DD4[0] - 1;
            return;
        }
        *(int *)(particle + 4) = (*(int *)(particle + 4) & 0xFFFFFF) + (remaining << 24);
    } else {
        header = *(int *)(particle + 4);
        if ((header >> 24) < *(int *)(params + 0x10))
            *(int *)(particle + 4) = header + 0x1000000;
    }
    if (((int)particle & 0x80) == 0)
        *(unsigned char *)(particle + 8) += 2;
    else
        *(unsigned char *)(particle + 8) -= 2;
    position = particle + 0x10;
    FastVecAdd(position, position, params);
    FastVecAdd(position, position, D_001B1DF0);
    if (*(int *)(params + 0x14) == 0) {
        short period = *(short *)(particle + 0xA);
        float sway = math_fast_sin_or_cos_b((float)(g_game_time[0] & (period - 1)) / (float)period * 6.2831855f);
        FastVecScale(wobble, D_001B5580, sway * 0.016666668f);
        FastVecAdd(position, wobble, position);
    }
}
