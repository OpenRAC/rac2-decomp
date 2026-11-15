#include "common.h"
#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern unsigned char *D_L00_001B1E9C __attribute__((sda));
extern void moby_set_state(char *, int, int);
extern void part_spawn_masked_debris(char *, int, void *, unsigned char, float, float, float, float);
extern void PlayMobySound(int, int, char *);
extern void moby_mark_spawned(char *);

/* Waits until the two linked objects are gone, then plays a spark effect and removes itself. */
void linked_pair_watcher_update(char *obj) {
    char *child;
    char *table;
    unsigned int value;
    union { TI128 q; float f[4]; } words;

    child = *(char **)(obj + 0x68);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        moby_set_state(obj, 1, -1);
        return;
    case 1:
        if (*(int *)(child + 4) > 0 && *(int *)(child + 8) > 0) {
            table = D_L00_001B1E9C + (*(int *)(child + 4) << 8);
            if (table == 0 || (value = *(unsigned char *)(table + 0x20)) == 0xFE || value == 0xFD) {
                moby_set_state(obj, 2, -1);
            } else {
                table = D_L00_001B1E9C + (*(int *)(child + 8) << 8);
                if (table == 0 || (value = *(unsigned char *)(table + 0x20)) == 0xFE || value == 0xFD) moby_set_state(obj, 2, -1);
            }
        }
        return;
    case 2:
        words.q = 0;
        words.f[1] = 0.10000001f;
        part_spawn_masked_debris(obj, 1, &words, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(0, 0, obj);
        moby_mark_spawned(obj);
        return;
    default:
        return;
    }
}
