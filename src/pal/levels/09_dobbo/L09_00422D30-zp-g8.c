#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void moby_mark_spawned(void *);
extern void *part_spawn_object_following_effect(float *, u8 *, int, int, int, int, int, int, float, float);
extern void part_l00_spawn_spark_burst_pal(u8 *, float *, float *, int, int, float, float, float, float, float);
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern char *moby_l00_spawn_child(u8 *, int, int);
extern float g_effect_explode_params_c __attribute__((sda));
extern float g_effect_explode_params_b __attribute__((sda));
extern float g_effect_explode_params_a __attribute__((sda));

/* Three-state effect object: spawns its first effect, waits for the hit, then fires the closing effects and retires itself. */
void three_state_effect_update_pal(u8 *moby)
{
    EffectVector offset;
    EffectVector drift;
    u8 *vars = *(u8 **)(moby + 0x68);

    offset.bits = 0;
    offset.value[1] = -0.14f;
    offset.value[2] = 0.14f;
    switch (moby[0x20]) {
    case 0:
        part_spawn_object_following_effect(offset.value, moby, 0x50088030, -1, 1, -1, 0, -1, 136500.0f, 0.75f);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0)) {
            if (*(int *)vars == 0)
                moby_set_state(moby, 2, -1);
        }
        moby[0xA8] = 0xFF;
        break;
    case 2:
        drift.bits = 0;
        drift.value[1] = -0.060000002f;
        drift.value[2] = 0.020000001f;
        part_l00_spawn_spark_burst_pal(moby, offset.value, drift.value, 25, 2, 0.2f, 0.10000001f, 1.5f, 6.0f, 0.8f);
        part_explode_object_into_pieces_pal(moby, &g_effect_explode_params_a, &g_effect_explode_params_b, &g_effect_explode_params_c,
                          0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        moby_l00_spawn_child(moby, 0x1299, 0);
        moby_mark_spawned(moby);
        break;
    }
}
