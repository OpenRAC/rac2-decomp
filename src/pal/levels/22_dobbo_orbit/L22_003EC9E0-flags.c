#include "include_asm.h"

#include "common.h"
extern void *part_find_owned_effect_slot(void *, int, int);
extern s32 math_random_int_below(int);
extern int snd_play_from_class_bank(char *, int, void *, int);
extern void part_spawn_explosion_with_sparks_pal(void *, void *, int, float, float);
extern void moby_mark_spawned(void *object);

void text_show_message_at_moby_pal(u8 *a0, int a1, int a2) {
    u8 *s0 = a0;
    void *s3;
    s3 = part_find_owned_effect_slot(a0, -1, 0);
    if (s3 == 0)
        return;
    snd_play_from_class_bank(0xC + math_random_int_below(3), 0, s0, 0xE0B);
    part_spawn_explosion_with_sparks_pal(s0, s0 + 0x10, -1, 2.0f, 13.0f);
    moby_mark_spawned(s0);
}
