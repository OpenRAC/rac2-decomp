#include "include_asm.h"

INCLUDE_ASM("asm/us2/game", func_US2_002D8E60);

extern int func_002DE3A0(int);
extern void func_002B7AD0(void);
extern short D_001A63AC;
extern void func_002B7AD0(void);
extern int D_001B1840 __attribute__((sda));
extern int D_00254EA4;

int func_US2_002D8F00(char *object)
{
    if (D_001A63AC != 0 && *(int *)(object + 0x50) == 3)
        func_002B7AD0();
    func_002DE3A0(1);
    {
        int value = *(int *)(object + 0x54);
        if (value != 0) {
            D_00254EA4 = *(int *)(object + 0x38);
            D_001B1840 = value;
        }
    }
    return 0;
}


INCLUDE_ASM("asm/us2/game", func_US2_002D8F70);

INCLUDE_ASM("asm/us2/game", func_US2_002D9178);

/* func_US2_002D9718 is defined in 002D8E60-listbox.c. */
