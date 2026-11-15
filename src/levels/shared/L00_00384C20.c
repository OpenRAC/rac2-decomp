#include "include_asm.h"
#include "names.h"

extern void *D_L00_00232A60[24];

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
    slot = D_L00_00232A60;
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
