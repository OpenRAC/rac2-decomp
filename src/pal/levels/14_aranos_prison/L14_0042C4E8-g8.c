#include "include_asm.h"

extern float D_L14_001B17B8 __attribute__((sda));
extern float D_L14_001B17BC __attribute__((sda));
extern char D_00189EA0[];
extern void *func_PAL_L00_002D7850(int size);
extern void func_L00_002D7140(void *block);
extern int func_002ACBC8(void *, int);
typedef struct {
    float x;
    float y;
} EffectPair;

/* Scans the four slot words at state+0x20; at the first one that is set and passes func_002ACBC8,
   makes sure the pool record at state+0x14 exists and writes D_L14_001B17B8/BC into its first two
   floats. If none passes, frees the record. */
void func_PAL_L14_0042C4E8(char *a0)
{
    char *state = *(char **)(a0 + 0x68);
    int *slot = (int *)(state + 0x20);
    int i;

    for (i = 0; i < 4; i++, slot++) {
        if (*slot != -1 && func_002ACBC8(D_00189EA0, *slot) != 0) {
            if (*(EffectPair **)(state + 0x14) == 0) {
                *(EffectPair **)(state + 0x14) = func_PAL_L00_002D7850(5);
            }
            (*(EffectPair **)(state + 0x14))->x = D_L14_001B17B8;
            (*(EffectPair **)(state + 0x14))->y = D_L14_001B17BC;
            return;
        }
    }

    if (*(EffectPair **)(state + 0x14) != 0) {
        func_L00_002D7140(*(EffectPair **)(state + 0x14));
        *(EffectPair **)(state + 0x14) = 0;
    }
}
