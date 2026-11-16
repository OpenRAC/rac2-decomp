#include "include_asm.h"
#include "names.h"

extern double g_fade_in_param_c __attribute__((sda));
extern double g_fade_in_param_b __attribute__((sda));
extern double g_fade_in_param_a __attribute__((sda));
extern void moby_set_state(unsigned char *, int, int);
extern void *part_find_owned_effect_slot(unsigned char *, int, int);
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern int g_oozla_intro_timer;
extern int ref_L01_00412E00_00 __attribute__((sda));

void triggered_flash_update_pal(unsigned char *a0) {
    unsigned char *s1 = *(unsigned char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        ref_L01_00412E00_00 = ref_L01_00412E00_00 + 1;
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(a0, 0x04010000, 0) != 0 && *(int *)s1 == 0) {
            ref_L01_00412E00_00 = g_oozla_intro_timer - 1;
            moby_set_state(a0, 2, -1);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        part_explode_object_into_pieces_pal(a0, &g_fade_in_param_a, &g_fade_in_param_b, &g_fade_in_param_c, 0xFFFF, 0, -1, 0,
                    0xFFFF, 0xFF, 0);
        moby_mark_spawned(a0);
        break;
    }
}
