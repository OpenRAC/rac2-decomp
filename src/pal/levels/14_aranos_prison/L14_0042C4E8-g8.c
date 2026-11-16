#include "include_asm.h"
#include "names.h"

extern float g_searchlight_effect_x __attribute__((sda));
extern float g_searchlight_effect_y __attribute__((sda));
extern char g_hero_position[];
extern void *cam_alloc_override_slot_pal(int size);
extern void cam_end_override(void *block);
extern int IsPointInCuboid(void *, int);
typedef struct {
    float x;
    float y;
} EffectPair;

/* Scans the four slot words at state+0x20; at the first one that is set and passes func_002ACBC8,
   makes sure the pool record at state+0x14 exists and writes D_L14_001B17B8/BC into its first two
   floats. If none passes, frees the record. */
void part_update_slot_triggered_record_pal(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    int *slot = (int *)(state + 0x20);
    int i;

    for (i = 0; i < 4; i++, slot++) {
        if (*slot != -1 && IsPointInCuboid(g_hero_position, *slot) != 0) {
            if (*(EffectPair **)(state + 0x14) == 0) {
                *(EffectPair **)(state + 0x14) = cam_alloc_override_slot_pal(5);
            }
            (*(EffectPair **)(state + 0x14))->x = g_searchlight_effect_x;
            (*(EffectPair **)(state + 0x14))->y = g_searchlight_effect_y;
            return;
        }
    }

    if (*(EffectPair **)(state + 0x14) != 0) {
        cam_end_override(*(EffectPair **)(state + 0x14));
        *(EffectPair **)(state + 0x14) = 0;
    }
}
