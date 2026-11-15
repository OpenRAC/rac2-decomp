#include "include_asm.h"
#include "common.h"
extern float D_L23_001B38E8[] __attribute__((sda));
extern int D_L23_001B3900[] __attribute__((sda));
extern int g_slot_effect_in_use[] __attribute__((sda));
extern float g_active_slot_effect_count __attribute__((sda));
extern char g_camera_l23_position[];
extern float fast_vec_dist(void *, void *);
extern int FastDecTimer(void *);
extern void moby_mark_spawned(void *);
extern void gfx_add_draw_callback_second(void *, void *);
extern void DrawExpandingBillboardEffect(void *);

/* Per-frame update of an effect object. It picks its strength from the distance to the
   camera and removes itself when it is done. */
void slot_effect_update(char *object)
{
    char *state = *(char **)(object + 0x68);

    if (!*(unsigned char *)(object + 0x20)) {
        D_L23_001B38E8[*(int *)(state + 0x3C)] = 0.01f;
        D_L23_001B3900[*(int *)(state + 0x3C)] = 0xFF;
        *(unsigned char *)(object + 0x20) = 1;
        if (fast_vec_dist(object + 0x10, g_camera_l23_position) > 200.0f)
            *(float *)(state + 0x40) = 4.0f;
        else if (fast_vec_dist(object + 0x10, g_camera_l23_position) > 100.0f)
            *(float *)(state + 0x40) = 2.0f;
        else if (fast_vec_dist(object + 0x10, g_camera_l23_position) > 25.0f)
            *(float *)(state + 0x40) = 1.0f;
        else if (fast_vec_dist(object + 0x10, g_camera_l23_position) > 0.0f)
            *(float *)(state + 0x40) = 0.5f;
    }
    if (!FastDecTimer(state)) {
        FastDecTimer(state + 4);
        gfx_add_draw_callback_second(DrawExpandingBillboardEffect, object);
    } else {
        g_slot_effect_in_use[*(int *)(state + 0x3C)] = 0;
        g_active_slot_effect_count -= 1.0f;
        moby_mark_spawned(object);
    }
}

