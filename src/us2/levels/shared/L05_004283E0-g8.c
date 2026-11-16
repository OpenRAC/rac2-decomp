#include "include_asm.h"
#include "names.h"
extern int g_current_map_index;
extern float fast_vec_dist(void *, void *);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern void slot_add_value_clamped(int, int);
extern void func_0029CC50(int, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_mark_spawned(void *);
extern int g_glow_ring_follow_moby __attribute__((sda));
extern void glow_l05_ring_draw(char *);

/* Same shape as func_L05_004260B8, on its own data slot and with its own tail. */
void glow_pickup_collect_slot3_us2(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (g_glow_ring_follow_moby != 0) {
        scale = fast_vec_dist((void *)(g_glow_ring_follow_moby + 0x10), object + 0x10);

        if (g_current_map_index == 0x14) {
            vec_spring_to_target(object + 0x10, (void *)(g_glow_ring_follow_moby + 0x10), state + 0x40,
                         0.008888889104127884f, 0.0033333334140479565f, 1.0666667222976685f);
            goto check_scale;
        }
        if (scale < 60.0f) {
            float *class_data = *(float **)(object + 0x24);
            float scaled = class_data[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = scaled;
            {
                float cap = class_data[9] * 0.30000001192092896f;

                if (scaled < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            vec_spring_to_target(object + 0x10, (void *)(g_glow_ring_follow_moby + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
check_scale:
        if (scale < 0.5f) {
            slot_add_value_clamped(3, 10);
            func_0029CC50(0x1287, 10, -1);
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            moby_mark_spawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.04f);
    glow_l05_ring_draw(object);
}
