#include "common.h"
extern int D_L05_001B2048[] __attribute__((sda));
extern int D_L05_00221D10[];
extern void *D_L05_00225DD0[];
extern int D_L05_001AC4D8 __attribute__((sda));
extern int D_L05_001AC4DC __attribute__((sda));
extern void func_L05_00379968(void);
extern int func_002A7820(int,int);
extern int func_L05_0037B3A0(void *);
extern void func_L05_0037A218(void *);
extern void func_L00_002E6EF8(void (*)(void *),void *);
/* Picks a random live object that can be chosen and sets up its follow-up update. */
void func_L05_00379B60(void)
{
    /* The initial state pointer and subsequent search flag have disjoint lifetimes. */
    union { int *state; int found; } phase;
    int *state;
    int *selection;
    if (D_L05_001B2048[0] < 10) InitSlotFlagsFromEquipment();
    phase.state = D_L05_00221D10;
    if (phase.state[0x84/4] != 0) return;
    {
        if (D_L05_001AC4D8 >= 2) {
            D_L05_001AC4DC = RandomIntRange(0,D_L05_001AC4D8-1);
            selection = phase.state;
            phase.found = 0;
            while (!phase.found) {
                if (selection[4] == 0) phase.found = 1;
                if (CountReadyListObjects(D_L05_00225DD0[D_L05_001AC4DC])) phase.found = 1;
                if (!phase.found) {
                    D_L05_001AC4DC++;
                    if (D_L05_001AC4DC >= D_L05_001AC4D8) D_L05_001AC4DC = 0;
                }
            }
        } else D_L05_001AC4DC = 0;
    }
    state = D_L05_00221D10;
    *(unsigned short *)((char *)state+0x40) = 0;
    *(unsigned short *)((char *)state+0x42) = 0;
    if (state[0x78/4]) AddDrawCallbackToList3(UpdateSpaceProjectilePool,(void *)state[0x78/4]);
}
