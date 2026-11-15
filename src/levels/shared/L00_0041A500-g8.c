#include "names.h"
/* Per-frame step over a ring of 35 entries of 0x40 bytes: now and then hands one entry to a
   helper, and now and then fires a second helper on it. */
#include "common.h"

extern char *g_lava_gun_ring_entries __attribute__((sda));
extern int func_001163B0(void);
extern void lava_gun_spawn_entry_effect(char *object, void *entry);
extern void part_spawn_white_flash(void *entry, void *next, int zero, float scale);

void lava_gun_update_ring_entries(char *object)
{
    char *state = *(char **)(object + 0x68);
    int first = *(int *)(state + 0x48);
    int last = *(int *)(state + 0x44);
    int end;
    int index;
    int random;
    end = first + 2;
    index = end - last;
    if (index <= -1)
        index += 0x23;

    random = func_001163B0();
    if (random % 7 == 0)
        lava_gun_spawn_entry_effect(object, g_lava_gun_ring_entries + (index << 6));

    random = func_001163B0();
    if (random % 0x16 == 0) {
        char *entry = g_lava_gun_ring_entries + (index << 6);
        part_spawn_white_flash(entry, entry + 0x10, 0, -1.0f);
    }
}
