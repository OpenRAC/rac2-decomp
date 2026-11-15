#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
extern char D_00189EA0[];
extern char *D_0018C0B0;
extern void func_002A0F48(char *);

/* The second argument is supplied by the caller but never read: the body reloads the source. */
/* Copies the position and rotation from the hero's mount object onto this object. */
void func_L08_003CD600(char *obj, Quadword *unused) {
    char *source = gHeroMoby_0018C0B0;

    *(Quadword *)(obj + 0x10) = *(Quadword *)(source + 0x10);
    *(Quadword *)(obj + 0xF0) = *(Quadword *)(source + 0xF0);
    func_002A0F48(obj);
}

/* Saves the hero's current position and rotation into the given buffer, then moves this object there. */
void func_L08_003CD6C8(char *obj, Quadword *saved) {
    Quadword *transform = (Quadword *)gHeroPosition;

    Quadword *src;
    Quadword *dst;

    saved[0] = transform[0];
    src = transform + 1;
    dst = saved + 1;
    *dst = *src;
    CopyMountTransformToObject(obj, saved);
}
