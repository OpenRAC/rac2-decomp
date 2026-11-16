#include "include_asm.h"
#include "names.h"

extern int g_current_map_index;
extern float fast_vec_dist(void *, void *);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern void slot_add_value_clamped(int, int);
extern void func_PAL_0029D5E8(int, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_mark_spawned(void *);
extern int g_glow_ring_follow_moby __attribute__((sda));
extern void glow_l05_ring_draw_3_pal(char *);

/* Same shape as func_L05_004260B8, on its own data slot and with its own tail. */
/* Flies the pickup toward the player and adds to the second counter slot when it arrives. */
void homing_pickup_slot2_update_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    float distance;

    if (g_glow_ring_follow_moby != 0) {
        distance = fast_vec_dist((void *)(g_glow_ring_follow_moby + 0x10), object + 0x10);

        if (g_current_map_index == 0x14) {
            vec_spring_to_target(object + 0x10, (void *)(g_glow_ring_follow_moby + 0x10), state + 0x40,
                         0.012800001f, 0.0048f, 1.2800001f);
            goto check_scale;
        }
        if (distance < 60.0f) {
            float *class_data = *(float **)(object + 0x24);
            float new_scale = class_data[9] * 0.02222222276031971f * distance;

            *(float *)(object + 0x2C) = new_scale;
            {
                float cap = class_data[9] * 0.30000001192092896f;

                if (new_scale < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            vec_spring_to_target(object + 0x10, (void *)(g_glow_ring_follow_moby + 0x10), state + 0x40,
                         0.008f, 0.0024f, 0.6f);
        }
check_scale:
        if (distance < 0.5f) {
            slot_add_value_clamped(2, 10);
            func_PAL_0029D5E8(0x1288, 10, -1);
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            moby_mark_spawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.04f);
    glow_l05_ring_draw_3_pal(object);
}
