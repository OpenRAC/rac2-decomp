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
extern int g_glow_ring_target_moby __attribute__((sda));
extern void func_PAL_L05_004225D0(char *);

void func_PAL_L05_0042232C(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (g_glow_ring_target_moby != 0) {
        scale = fast_vec_dist((void *)(g_glow_ring_target_moby + 0x10), object + 0x10);

        if (g_current_map_index == 0x14) {
            vec_spring_to_target(object + 0x10, (void *)(g_glow_ring_target_moby + 0x10), state + 0x40,
                         0.012800001f, 0.0048f, 1.2800001f);
            goto check_scale;
        }
        if (scale < 6e+01f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.3f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            vec_spring_to_target(object + 0x10, (void *)(g_glow_ring_target_moby + 0x10), state + 0x40,
                         0.008f, 0.0024f, 0.6f);
        }
    check_scale:
        if (scale < 0.5f) {
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            slot_add_value_clamped(1, 10);
            func_PAL_0029D5E8(0x1286, 10, -1);
            moby_mark_spawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.04f);
    func_PAL_L05_004225D0(object);
}
