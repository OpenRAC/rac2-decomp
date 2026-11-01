#include "include_asm.h"

#include "common.h"
extern int func_00282978(void *p);
extern int func_00283D38(int a0, int a1, float f12);

/* Toggle the lamp and hand the new state to the colour routine. */
void func_PAL_L02_00390950(char *arg0) {
    char *s0 = *(char **)(arg0 + 0x68);

    if (*(short *)(arg0 + 0xAA) != 0x9B0)
        return;
    if (func_00282978(s0 + 0x74) != 0) {
        *(unsigned short *)(s0 + 0x74) = 0x2A;
        *(unsigned int *)(s0 + 0x8C) = (*(unsigned int *)(s0 + 0x8C) == 0);
    }
    *(int *)(arg0 + 0x78) = func_00283D38(*(int *)(arg0 + 0x78),
        *(unsigned int *)(s0 + 0x8C) != 0 ? 0x50787878 : 0x50141414, 0.18f);
}
