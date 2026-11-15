#include "include_asm.h"
#include "names.h"
typedef struct OBJ4 {
    char pad0[8];
    int f8;
    int fC;
} OBJ4;

extern void func_L00_00322EC8(void *);

/* Cleans up the 25 shot slots of the weapon when it is unloaded. */
void func_L00_003B60E8(OBJ4 *weapon)
{
    char *base = (char *)weapon + 0x20;
    char *slots = base + weapon->f8;
    int *flags = (int *)(base + weapon->fC);
    int i;

    for (i = 0; i < 25; i++) {
        if (flags[i] != 0)
            ReleaseSlotList(slots + i * 0x150);
    }
}
