#include "common.h"

extern char g_hero_state[];
extern char *g_area_hit_targets[];
extern int PlayMobySound(int index, int mode, void *object);
extern void hero_apply_mode_transform_reversed(void *dst, void *src, float scale);
extern void part_l00_spawn_spark_pairs(void *position, int count);

/* Type id of an object's data record, or 0 when the object or record is missing. */
static __inline__ int object_type(char *object)
{
    char *data;
    return object != 0 && (data = *(char **)(object + 0x24)) != 0
        ? *(short *)(data + 0x46) : 0;
}

/* Play sound 1 once, then for each of the first count slot objects of type 5 or 9 emit effect 4 at its scaled position. */
void part_emit_effects_at_nearby_mobys(void *object, int count)
{
    float position[4] __attribute__((aligned(16)));
    char **slot;
    int type;
    int remaining;
    char *base;

    if (count != 0) {
        base = g_hero_state;
        if (*(short *)(base + 0xbfe) == 0) {
            PlayMobySound(1, 0, object);
            *(short *)(base + 0xbfe) = 1;
        }
        if (count > 0) {
            remaining = count;
            slot = g_area_hit_targets;
            do {
                type = object_type(*slot);
                if (type == 5 || type == 9) {
                    qcopy(position, *slot + 0x10);
                    hero_apply_mode_transform_reversed(position, position, 0.5f);
                    part_l00_spawn_spark_pairs(position, 4);
                }
                remaining--;
                slot++;
            } while (remaining != 0);
        }
    }
}
