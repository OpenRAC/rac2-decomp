#include "include_asm.h"
#include "names.h"

extern char D_00189E20_2[];
extern void anim_start_blended(void *, int, int, int);

/* Routes the object the state word names to the mode the helper reports: the helper's value
   and the caller's index are handed over with the caller's float as an int, otherwise the
   object's own flag picks the fixed mode 7. Same two gates as its sibling below. */
void hero_start_linked_object_anim_pal(int anim_key, int blend_arg, float speed)
{
    char *base = D_00189E20_2;
    int anim_id;

    if (*(int *)(base + 0x2494) == 0)
        return;
    if (*(int *)(base + 0x2498) == 0)
        return;
    if (hero_lookup_anim_by_key(anim_key, &anim_id) != 0) {
        anim_start_blended(*(void **)(base + 0x2494), anim_id, blend_arg, (int)speed);
    } else if (*(unsigned char *)(*(char **)(base + 0x2494) + 0x43) != 0) {
        anim_start_blended(*(void **)(base + 0x2494), 0, 0, 6);
    }
}

