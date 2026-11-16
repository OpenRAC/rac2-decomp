#include "common.h"

/* func_L20_0039D880 sheds damage effects as health falls below each threshold (compare
   func_002B3380). Its unit is built with -g: retail has the two nops -g leaves before the
   div.s. The final copy uses qcopy (the retail materialises both transfer addresses). */

extern int FloatToInt(float);
extern float math_random_signed_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void *cam_moby_create(void *, int, int, int, void *, void *, void *, float, float, int);
extern int snd_play_from_global_bank(int, int, int);
extern void moby_mark_spawned(void *);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void moby_fade_out_update(unsigned char *);
extern char g_hero_l20_extra_state[];

/* Drops pieces off the trooper as its health falls, and removes its parts when it is out of health. */
void SpawnHealthThresholdEffects(char *self) {
    char *state = *(char **)(self + 0x68);
    float buf[4];
    int i;
    unsigned int threshold;
    int bit;
    float angle, speed;
    char *effect;
    char *global;
    void (*callback)(unsigned char *);

    if (*(char **)(state + 0x254) == 0) return;
    {
        float health = *(float *)(state + 0x20);
        float maximum = (float)*(short *)(state + 0x24);
        float fraction;
        fraction = health / maximum;
        threshold = FloatToInt(fraction * 255.0f) & 0xFF;
        global = g_hero_l20_extra_state;
        callback = moby_fade_out_update;
        for (i = 0; i < 10; i++) {
            if ((unsigned int)(i - 4) < 2) continue;
            if (i == 7) continue;
            bit = 1 << i;
            if ((*(unsigned short *)(*(char **)(state + 0x254) + 0x7C) & bit) == 0) continue;
            if (threshold >= *(unsigned char *)(state + i + 0x270)) continue;
            angle = FastAddRotations(math_random_signed_float_range(90.0f, 120.0f) * 0.017453294f, *(float *)(global + 0x158));
            speed = math_random_float_range(2.0f, 4.0f) * 0.016666668f;
            buf[0] = math_fast_sin_or_cos_a(angle) * speed;
            buf[1] = math_fast_sin_or_cos_b(angle) * speed;
            buf[2] = 0.0f;
            buf[2] = math_random_float_range(5.0f, 8.0f) * 0.016666668f;
            effect = cam_moby_create(*(char **)(state + 0x254), 1,
                *(short *)(*(char **)(state + 0x254) + 0xAA), i,
                *(char **)(state + 0x254) + 0x10, *(char **)(state + 0x254) + 0xF0,
                buf, 90.0f, 15.0f, 255);
            if (effect) *(void (**)(unsigned char *))(effect + 0x64) = callback;
            *(unsigned short *)(*(char **)(state + 0x254) + 0x7C) &= ~bit;
            snd_play_from_global_bank(7, 0, 0);
        }
    }
    if (*(float *)(state + 0x20) <= 0.0f) {
        char **p = (char **)(state + 0x258);
        int j;
        for (j = 1; j >= 0; j--, p++) {
            if (*p != 0) {
                moby_mark_spawned(*p);
                *p = 0;
            }
        }
        if (*(char **)(state + 0x254) != 0) {
            moby_mark_spawned(*(char **)(state + 0x254));
            *(char **)(state + 0x254) = 0;
            qcopy(buf, self + 0x10);
            buf[2] += 1.0f;
            SpawnExplosion(buf, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, 0.5f, 20.0f, 1, 0, 0, 0);
        }
    }
}
