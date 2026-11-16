#include "include_asm.h"
#include "names.h"
extern int g_glow_ring_draw_target_moby __attribute__((sda));
extern int g_current_map_index;
extern float fast_vec_dist(void *, void *);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern void slot_add_value_clamped(int, int);
extern void func_0029CC50(int, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_mark_spawned(void *);
extern void glow_l05_ring_draw_4(void *);

/* Turns the object towards the global target and clamps its aim cone; a target within
   half a unit takes the fast path, the rest the slow one (an angle step and an update). */
void glow_pickup_collect_slot4_us2(char *object)
{
    char *state = *(char **)(object + 0x68);
    float distance;

    if (g_glow_ring_draw_target_moby != 0) {
        char *pos = object + 0x10;
        char *aim;
        float scaled;
        float capped;

        distance = fast_vec_dist((char *)g_glow_ring_draw_target_moby + 0x10, pos);
        if (g_current_map_index == 0x14) {
            vec_spring_to_target(pos, (char *)g_glow_ring_draw_target_moby + 0x10, state + 0x40,
                          0.008888889f, 0.0033333333f, 1.0666667f);
        } else {
            if (distance < 60.0f) {
                aim = *(char **)(object + 0x24);
                scaled = *(float *)(aim + 0x24) * 0.022222222f * distance;
                *(float *)(object + 0x2C) = scaled;
                capped = *(float *)(aim + 0x24) * 0.3f;
                if (capped > scaled)
                    *(float *)(object + 0x2C) = capped;
                vec_spring_to_target(pos, (char *)g_glow_ring_draw_target_moby + 0x10, state + 0x40,
                              0.0055555556f, 0.0016666667f, 0.5f);
            }
        }
        if (distance < 0.5f) {
            slot_add_value_clamped(4, 1);
            func_0029CC50(0x1285, 1, -1);
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            moby_mark_spawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.04f);
    glow_l05_ring_draw_4(object);
}
