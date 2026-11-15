#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
extern char g_hero_position[];
extern void func_002A0F48(char *);
/* The caller deliberately supplies source even though this callee reloads it. */
extern void hero_copy_mount_transform_to_object(char *, Quadword *);

/* Moves the hero and the object it is riding to a new position and rotation, then syncs this object to it. */
void hero_move_with_mount_to_transform(char *context, Quadword *source)
{
    char *actor;
    Quadword *transform = (Quadword *)g_hero_position;
    transform[0] = source[0];
    transform[1] = source[1];
    actor = *(char **)(g_hero_position + 0x2210);
    if (actor != 0) {
        *(Quadword *)(actor + 0x10) = transform[0];
        *(Quadword *)(actor + 0xF0) = transform[1];
        func_002A0F48(actor);
    }
    hero_copy_mount_transform_to_object(context, source);
}
