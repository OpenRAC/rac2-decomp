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
void hit_l12_flash_update_pal(unsigned char *a0) {
    unsigned char *s1 = *(unsigned char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(a0, 0x04010000, 0) != 0 && *(int *)s1 == 0) {
            moby_set_state(a0, 2, -1);
            PlayMobySound(0, 0, a0);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        part_explode_object_into_pieces_pal(a0, &ref_L12_00420838_02, &ref_L12_00420838_01, &ref_L12_00420838_00, 0xFFFF, 0, ref_L12_00420838_03, 0,
                    0xFFFF, 0xFF, 0);
        moby_l00_spawn_child(a0, 0x110D, 0);
        moby_mark_spawned(a0);
        break;
    }
}
