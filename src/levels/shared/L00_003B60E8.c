#include "include_asm.h"
#include "names.h"
typedef struct OBJ4 {
    char pad0[8];
    int f8;
    int fC;
} OBJ4;

extern void level_release_slot_list(void *);

/* Cleans up the 25 shot slots of the weapon when it is unloaded. */
void weapon_release_shot_slots(OBJ4 *weapon)
{
    char *base = (char *)weapon + 0x20;
    char *slots = base + weapon->f8;
    int *flags = (int *)(base + weapon->fC);
    int i;

    for (i = 0; i < 25; i++) {
        if (flags[i] != 0)
            level_release_slot_list(slots + i * 0x150);
    }
}
