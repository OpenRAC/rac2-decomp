#include "include_asm.h"

#include "common.h"
extern void *part_find_owned_effect_slot(void *, int, int);
extern s32 math_random_int_below(int);
extern int snd_play_from_class_bank(char *, int, void *, int);
extern void part_spawn_explosion_with_sparks_pal(void *, void *, int, float, float);
extern void moby_mark_spawned(void *object);

/* Shows a text message at the object and starts its effect. Does nothing if the object has no target. */
void text_show_message_at_moby_pal(u8 *moby, int unused_a, int unused_b) {
    u8 *moby_copy = moby;
    void *target;
    target = part_find_owned_effect_slot(moby, -1, 0);
    if (target == 0)
        return;
    snd_play_from_class_bank(0xC + math_random_int_below(3), 0, moby_copy, 0xE0B);
    part_spawn_explosion_with_sparks_pal(moby_copy, moby_copy + 0x10, -1, 2.0f, 13.0f);
    moby_mark_spawned(moby_copy);
}
