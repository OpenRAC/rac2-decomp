#include "include_asm.h"
#include "names.h"
extern int D_L05_001B14FC __attribute__((sda));
extern int g_current_map_index;
extern float fast_vec_dist(void *, void *);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern void slot_add_value_clamped(int, int);
extern void func_0029CC50(int, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_mark_spawned(void *);
extern void glow_ring_draw_sprites(char *);

void func_US2_L05_00427E40(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (D_L05_001B14FC != 0) {
        scale = fast_vec_dist((void *)(D_L05_001B14FC + 0x10), object + 0x10);

        if (g_current_map_index == 0x14) {
            vec_spring_to_target(object + 0x10, (void *)(D_L05_001B14FC + 0x10), state + 0x40,
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
            vec_spring_to_target(object + 0x10, (void *)(D_L05_001B14FC + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
check_scale:
        if (scale < 0.5f) {
            slot_add_value_clamped(2, 10);
            func_0029CC50(0x1288, 10, -1);
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            moby_mark_spawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.04f);
    glow_ring_draw_sprites(object);
}
