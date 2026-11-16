#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern int coll_process_hit(float, void *, int, void *, void *);
extern char *g_blocker_moby_table[];
/* Returns 0 if a nearby object of type 5 blocks this spot, otherwise 1. */
int moby_is_spot_free_of_blockers(char *object)
{
    Vector128 position[1];
    int count;
    int i;
    char *entry;
    *(Vector128 *)position = *(Vector128 *)(object+0x10);
    count=coll_process_hit(5.0f, position, 0, object, 0);
    if (count != 0) {
    for (i=0;i<count;i++) {
        entry=g_blocker_moby_table[i];
        if (entry != 0 && (entry=*(char **)(entry+0x24)) != 0 && *(short *)(entry+0x46)==5) return 0;
    }
    }
    return 1;
}
