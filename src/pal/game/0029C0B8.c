#include "include_asm.h"
#include "names.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern void menu_set_flag_restart_fades(void *, int);

void func_PAL_0029C0B8(int value) {
    if (D_001A8CFC[0] != 0)
        menu_set_flag_restart_fades(D_001A8CFC[0] + 0x37ED0, value);
}

typedef int BatchA_A08_s32;
extern BatchA_A08_s32 D_L00_001A904C[] __attribute__((sda));

/* A08-sda-offset-40 freshly exact-verified under family reservation */
void func_PAL_0029C0F0(BatchA_A08_s32 a0, BatchA_A08_s32 a1) {
    BatchA_A08_s32 base = D_L00_001A904C[0];
    BatchA_A08_s32 *p;
    if (base == 0) return;
    p = (BatchA_A08_s32 *)(base + 0x38000);
    p[0x7AA0/4] = a0;
    p[0x7AA4/4] = a1;
}

int func_PAL_0029C118(void) {
    int base = D_L00_001A904C[0];
    if (base != 0) {
        int *state = (int *)(base + 0x38000);
        if (state[0x7AA0 / 4] != 0 || state[0x7AA4 / 4] != 0)
            return 1;
    }
    return 0;
}

