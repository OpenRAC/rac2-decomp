#include "include_asm.h"
#include "names.h"

extern int g_current_map_index;
extern float fast_vec_dist(void *, void *);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern int func_L05_0037AAC8(int);
extern int math_random_int_below(int);
extern int func_0030CBA8(int);
extern void thrown_object_update(int, int);
typedef struct L05Slot40 {
    int state;
    int next;
    int pad08[2];
    int limit;
    int value;
    int pad18[4];
} L05Slot40;
extern L05Slot40 D_002A1800[];
extern void func_0029CC50(int, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_mark_spawned(void *);
extern int D_L05_001AFAA0 __attribute__((sda));

extern void func_L05_003CD598(char *);

/* Flies the pickup toward the player, shrinking as it nears, and heals the player when it is
   collected. */
void func_L05_003CD280(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (D_L05_001AFAA0 != 0) {
        scale = fast_vec_dist((void *)(D_L05_001AFAA0 + 0x10), object + 0x10);

        if (g_current_map_index == 0x14) {
            vec_spring_to_target(object + 0x10, (void *)(D_L05_001AFAA0 + 0x10), state + 0x40,
                         0.008888889104127884f, 0.0033333334140479565f, 1.0666667222976685f);
            goto check_scale;
        }
        if (scale < 60.0f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.30000001192092896f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            vec_spring_to_target(object + 0x10, (void *)(D_L05_001AFAA0 + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
    check_scale:
        if (scale < 0.5f) {
            int slot = func_L05_0037AAC8(6);
            int add = D_002A1800[slot].limit;

            if (math_random_int_below(4) != 0) {
                thrown_object_update(func_0030CBA8(0x1283), -1);
                add = 0x21;
            } else {
                thrown_object_update(func_0030CBA8(0x1284), -1);
            }
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            D_002A1800[slot].value += add;
            if (D_002A1800[slot].limit < D_002A1800[slot].value)
                D_002A1800[slot].value = D_002A1800[slot].limit;
            moby_mark_spawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.03f);
    func_L05_003CD598(object);
}

