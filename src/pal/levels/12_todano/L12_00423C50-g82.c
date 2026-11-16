#include "include_asm.h"
#include "names.h"

extern double ref_L12_00420838_00 __attribute__((sda));
extern double ref_L12_00420838_01 __attribute__((sda));
extern double ref_L12_00420838_02 __attribute__((sda));
extern void moby_set_state(unsigned char *, int, int);
extern void *part_find_owned_effect_slot(unsigned char *, int, int);
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern int ref_L12_00420838_03 __attribute__((sda));
extern int PlayMobySound(int, int, void *);
extern char *moby_l00_spawn_child(void *, int, int);
extern void moby_mark_spawned(void *);

/* Hand-adapted from func_L12_00388090. */
/* Waits until the hero hits it, then plays a flash, a sound and an effect (PAL: 50 Hz timings). */
void hit_l12_flash_update_pal(unsigned char *moby) {
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
        part_explode_object_into_pieces_pal(moby, &ref_L12_00420838_02, &ref_L12_00420838_01, &ref_L12_00420838_00, 0xFFFF, 0, ref_L12_00420838_03, 0,
                    0xFFFF, 0xFF, 0);
        moby_l00_spawn_child(moby, 0x110D, 0);
        moby_mark_spawned(moby);
        break;
    }
}
