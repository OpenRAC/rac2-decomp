#include "include_asm.h"
#include "names.h"

extern void *g_sheep_board_tiles[24];

extern void moby_mark_spawned(void *arg);

/* Removes the two Synthenoids and the 24 sheep that the board created. */
void sheep_board_destroy_objects(char *owner)
{
    void **slot = (void **)(*(char **)(owner + 0x68) + 0x48);
    int remaining = 1;
    do {
        int object = (int)*slot;
        slot++;
        remaining--;
        if (object) {
            moby_mark_spawned((void *)object);
        }
    } while (remaining >= 0);
    slot = g_sheep_board_tiles;
    remaining = 23;
    do {
        int object = (int)*slot;
        slot++;
        remaining--;
        if (object) {
            moby_mark_spawned((void *)object);
        }
    } while (remaining >= 0);
}
