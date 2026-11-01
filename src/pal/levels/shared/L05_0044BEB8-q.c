#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    char reserved00[0x1C];
    char *row;
} TableEntry;
extern char *D_L05_001B9710;
extern TableEntry *D_L05_001B1EC4 MACRO_ADDR;
extern char *D_L05_001B251C MACRO_ADDR;
extern TI128 D_L05_001B3600 MACRO_ADDR;
extern TI128 D_L05_001B35D0 MACRO_ADDR;
extern TI128 D_L05_001B35E0 MACRO_ADDR;
extern TI128 D_L05_001B35F0 MACRO_ADDR;
extern void func_PAL_L05_00447F28(char *);

/* Saves the four 16-byte blocks of the state record and hands its bound block on. */
void func_PAL_L05_0044BEB8(void)
{
    char *state = D_L05_001B9710;

    if (*(short *)(state + 0x86) != 0x19)
        return;
    func_PAL_L05_00447F28(state);
    D_L05_001B3600 = *(TI128 *)(state + 0x30);
    D_L05_001B35D0 = *(TI128 *)(state + 0x00);
    D_L05_001B35E0 = *(TI128 *)(state + 0x10);
    D_L05_001B35F0 = *(TI128 *)(state + 0x20);
    {
        char *sub = D_L05_001B1EC4[*(short *)(state + 0x84)].row;
        char *dst = D_L05_001B251C + (*(int *)(sub + 0x20) << 8) + 0x10;

        *(TI128 *)dst = *(TI128 *)(state + 0x30);
    }
}
