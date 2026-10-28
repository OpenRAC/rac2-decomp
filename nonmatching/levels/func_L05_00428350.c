/* func_L05_00428350 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections -fno-force-mem.
 * Measured in src/levels/shared/L05_00428350-init-g8.c: 456/456 bytes.
 * US: 0/4 local places; PAL: 0/4 local places; US2: 0/4 local places.
 * No strict linked build was run because no local placement matched.
 * The entry table-address/index GPRs and final table-address schedule differ. Scoped vector lifetimes recover the frame; named bases and fno-force-mem tied. Reopen with allocator evidence.
 */

#include "common.h"

extern float func_00282E48(void *, void *);
extern int func_00282978(void *);
extern void func_0029F338(void *);
extern void func_L00_002E6DB8(void (*)(void *), void *);
extern void func_L05_00428518(void *);
extern float D_L05_001B3580[];
extern int D_L05_001B3598[];
extern int D_L05_001B35B0[];
extern char D_L05_001B96C0[];
extern float D_L05_001B157C __attribute__((sda));

void func_L05_00428350(char *object)
{
    char *state = *(char **)(object + 0x68);
    if (*(unsigned char *)(object + 0x20) == 0) {
        char *position;
        char *reference;
        float *speeds = D_L05_001B3580;
        int *timers = D_L05_001B3598;
        speeds[*(int *)(state + 0x3C)] = 0.01f;
        timers[*(int *)(state + 0x3C)] = 0x80;
        object[0x20] = 1;
        position = object + 0x10;
        reference = D_L05_001B96C0;
        if (func_00282E48(position, reference) > 200.0f)
            *(float *)(state + 0x40) = 4.0f;
        else if (func_00282E48(position, reference) > 100.0f)
            *(float *)(state + 0x40) = 2.0f;
        else if (func_00282E48(position, reference) > 25.0f)
            *(float *)(state + 0x40) = 1.0f;
        else if (func_00282E48(position, reference) > 0.0f)
            *(float *)(state + 0x40) = 0.5f;
    }
    if (!func_00282978(state)) {
        func_00282978(state + 4);
        func_L00_002E6DB8(func_L05_00428518, object);
    } else {
        int *entries = D_L05_001B35B0;
        entries[*(int *)(state + 0x3C)] = 0;
        D_L05_001B157C -= 1.0f;
        func_0029F338(object);
    }
}