#include "include_asm.h"
#include "names.h"

extern double D_L13_001AEC00 __attribute__((sda));
extern double D_L13_001AEC08 __attribute__((sda));
extern double D_L13_001AEC10 __attribute__((sda));
extern void moby_set_state(unsigned char *, int, int);
extern void *part_find_owned_effect_slot(unsigned char *, int, int);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern int D_L13_001AEC30 __attribute__((sda));
extern int PlayMobySound(int, int, void *);
extern char *moby_l00_spawn_child(void *, int, int);
extern void moby_mark_spawned(void *);

void func_PAL_L12_0038AD50(unsigned char *a0) {
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
        func_PAL_L00_0032C328(a0, &D_L13_001AEC10, &D_L13_001AEC08, &D_L13_001AEC00, 0xFFFF, 0, D_L13_001AEC30, 0,
                    0xFFFF, 0xFF, 0);
        moby_l00_spawn_child(a0, 0x1308, 0);
        moby_mark_spawned(a0);
        break;
    }
}
