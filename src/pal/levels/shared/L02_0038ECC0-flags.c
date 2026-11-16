#include "include_asm.h"

#include "common.h"
extern int FastDecTimer(void *p);
extern int FastTweenColor(int a0, int a1, float f12);

/* Toggle the lamp and hand the new state to the colour routine. */
void blinking_lamp_update_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (*(short *)(moby + 0xAA) != 0x9B0)
        return;
    if (FastDecTimer(vars + 0x74) != 0) {
        *(unsigned short *)(vars + 0x74) = 0x2A;
        *(unsigned int *)(vars + 0x8C) = (*(unsigned int *)(vars + 0x8C) == 0);
    }
    *(int *)(moby + 0x78) = FastTweenColor(*(int *)(moby + 0x78),
        *(unsigned int *)(vars + 0x8C) != 0 ? 0x50787878 : 0x50141414, 0.18f);
}
