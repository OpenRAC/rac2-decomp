#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
extern char g_hero_position[];
extern char *g_hero_moby;
extern void func_002A0F48(char *);

/* The second argument is supplied by the caller but never read: the body reloads the source. */
/* Copies the position and rotation from the hero's mount object onto this object. */
void hero_copy_mount_transform_to_object(char *obj, Quadword *unused) {
    char *source = g_hero_moby;

    *(Quadword *)(obj + 0x10) = *(Quadword *)(source + 0x10);
    *(Quadword *)(obj + 0xF0) = *(Quadword *)(source + 0xF0);
    func_002A0F48(obj);
}

/* Saves the hero's current position and rotation into the given buffer, then moves this object there. */
void hero_save_transform_snap_object(char *obj, Quadword *saved) {
    Quadword *transform = (Quadword *)g_hero_position;

    Quadword *src;
    Quadword *dst;

    saved[0] = transform[0];
    src = transform + 1;
    dst = saved + 1;
    *dst = *src;
    hero_copy_mount_transform_to_object(obj, saved);
}
