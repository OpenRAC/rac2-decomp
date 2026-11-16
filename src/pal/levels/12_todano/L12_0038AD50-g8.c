#include "include_asm.h"
#include "names.h"

extern double g_fade_in_param_c __attribute__((sda));
extern double g_fade_in_param_b __attribute__((sda));
extern double g_fade_in_param_a __attribute__((sda));
extern void moby_set_state(unsigned char *, int, int);
extern void *part_find_owned_effect_slot(unsigned char *, int, int);
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern int g_level_effect_param __attribute__((sda));
extern int PlayMobySound(int, int, void *);
extern char *moby_l00_spawn_child(void *, int, int);
extern void moby_mark_spawned(void *);

/* Moby class 4871 update. Waits for a hit, then plays its effect and sound (PAL: its own object-explode helper). */
void hit_trigger_update_pal(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x04010000, 0) != 0 && *(int *)vars == 0) {
            moby_set_state(moby, 2, -1);
            PlayMobySound(0, 0, moby);
        }
        moby[0xA8] = 0xFF;
        break;
    case 2:
        part_explode_object_into_pieces_pal(moby, &g_fade_in_param_a, &g_fade_in_param_b, &g_fade_in_param_c, 0xFFFF, 0, g_level_effect_param, 0,
                    0xFFFF, 0xFF, 0);
        moby_l00_spawn_child(moby, 0x1308, 0);
        moby_mark_spawned(moby);
        break;
    }
}
