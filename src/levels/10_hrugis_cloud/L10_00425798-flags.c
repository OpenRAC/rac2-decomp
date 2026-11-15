#include "names.h"

extern unsigned char *D_L10_001B2528;
extern void func_0029F338(void *);

/* Like func_L05_0037B108 without its first three kinds, with this function's own callees. */
/* Removes the leftover effect and decoration objects of several classes from the object list. */
void func_L10_00425798(void) {
    unsigned char *object = D_L10_001B2528;
    int kind;
    while (object) {
        kind = *(short *)(object + 0xAA);
        if (kind == 0x1315 /* moby class 4885 */ ||
            kind == 0x1327 /* moby class 4903 */ || kind == 0x1328 /* moby class 4904 */ || kind == 0x10F9 /* moby class 4345 */ || kind == 0x946 /* moby class 2374 */ ||
            kind == 0x10CF /* moby class 4303 */ || kind == 0x117C /* moby class 4476 */ || kind == 0x117D /* moby class 4477 */ || kind == 0x117F /* moby class 4479 */)
            MarkMobySpawned(object);
        object = *(unsigned char **)(object + 0x28);
    }
}
