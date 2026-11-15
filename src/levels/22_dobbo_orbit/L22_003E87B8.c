#include "names.h"
/* func_L22_003E87B8 (120 bytes): spawns into the caller's object, paints a font-mode
   string and arms its animation, like func_L22_003D4320. func_002E5DA0 returns a value;
   declaring it void reorders the argument setup of its call. */
#include "common.h"

extern void *part_find_owned_effect_slot(void *, int, int);
extern char *math_random_int_below(int);
extern int snd_play_from_class_bank(char *, int, void *, int);
extern void part_spawn_explosion_with_sparks(void *, void *, int, float, float);
extern void moby_mark_spawned(void *object);

/* Shows a text message at the object and starts its effect. Does nothing if the object has no target. */
void text_show_message_at_moby(u8 *moby, int unusedA, int unusedB) {
    u8 *mobyCopy = moby;
    void *target;
    target = part_find_owned_effect_slot(moby, -1, 0);
    if (target == 0)
        return;
    snd_play_from_class_bank(0xC + math_random_int_below(3), 0, mobyCopy, 0xE0B);
    part_spawn_explosion_with_sparks(mobyCopy, mobyCopy + 0x10, -1, 2.0f, 13.0f);
    moby_mark_spawned(mobyCopy);
}
