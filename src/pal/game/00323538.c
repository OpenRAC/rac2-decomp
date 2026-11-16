#include "include_asm.h"

#include "common.h"
extern void gfx_update_color_fade_pal(char *, char *);
extern int FastDecTimer(void *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern void value_set_and_smooth_pal(char *, char *, int, int, float);

/* Does per-frame upkeep for the enemy: counts its timers down, moves its two limb chains and adds one to its age. */
void robot_update_timers_limbs_pal(char *object)
{
    char *data = *(char **)(object + 0x68);
    char *first;
    gfx_update_color_fade_pal(object, data + 0x50);
    first = data + 0x3D0;
    FastDecTimer(data + 0x270);
    FastDecTimer(data + 0x272);
    moby_update_eased_node(object, first, 5, 0.0432f, 0.43200004f);
    moby_update_eased_node(object, data + 0x450, 6, 0.0432f, 0.43200004f);
    if (*(unsigned short *)(object + 0x96) < 65535)
        (*(unsigned short *)(object + 0x96))++;
    value_set_and_smooth_pal(object, first, 5, 1, 2.5f);
}

