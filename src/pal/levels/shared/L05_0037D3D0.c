#include "include_asm.h"

#include "common.h"
typedef struct { int state,next,pad08[2],limit,value,pad18[4]; } L05Slot40;
extern L05Slot40 D_L05_002A1800[];
extern int D_L05_00221D10[];
extern char *D_L05_001B9710;
extern int func_L05_00445980(void);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern int func_002ED8A0(int);
extern void func_PAL_L05_004485A0(void *);
extern void func_PAL_L00_002B3000(void);

void func_PAL_L05_0037D3D0(float amount)
{
    int slot,remaining,damage;
    int *state;
    int *initial;
    if (func_L05_00445980()) amount *= 0.5f;
    damage = func_00283CF0(amount);
    initial = D_L05_00221D10;
    *(u16 *)((u8 *)initial+0x40) += damage;
    initial[0x80/4] = 1;
    slot = func_002ED8A0(6);
    if (slot >= 0) {
        remaining = D_L05_002A1800[slot].value;
        remaining -= func_00283CF0(amount);
        if (remaining <= 0) D_L05_002A1800[slot].value = 0;
        else { D_L05_002A1800[slot].value = remaining; goto finished; }
        amount = func_00283CE0(-remaining);
        if (amount == 0.0f) goto finished;
    }
    state = D_L05_00221D10;
    {
        *(u16 *)((u8 *)state+0x42) += func_00283CF0(amount);
        state[0x28/4] -= func_00283CF0(amount);
        if (state[0x28/4] <= 0) {
            state[0x88/4]++;
            state[0x28/4] = 0;
            if (*(s16 *)(D_L05_001B9710+0x86) == 25) func_PAL_L05_004485A0(D_L05_001B9710);
            else func_PAL_L00_002B3000();
        }
    }
finished:
    return;
}

