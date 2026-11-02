/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* GPT-6.1 Sol high, task v0855: USA v1.01, 212/212 bytes, 0/1 places.
 * Profile: -O2 -G8 -ffunction-sections (adding -g is byte-neutral).
 * Only the two LUI instructions at +0x58/+0x5C are exchanged: retail builds
 * the phase-table high half in v1 before the colour-table high half in v0.
 * Moving the RGB mask below the reflected-alpha calculation fixes constant
 * setup scheduling while separate compound assignments preserve a1 throughout.
 * Reversing pointer initialization swaps t0/t1; reversing increments does not
 * fix that. Separate base temporaries, unsigned colours, and a fresh no-debug
 * unit do not solve the high-half order. All other instructions now match.
 */
#include "common.h"

extern int D_L09_001B11D8 __attribute__((sda));
extern int D_L09_002A2658[];
extern int D_L09_002A27A0[];
extern int func_00283CF0(float);

void func_L09_003FE2D8(unsigned char *a0) {
    unsigned char *s0 = *(unsigned char **)(a0 + 0x68);
    float *pf = (float *)(s0 + 0x384);
    float v = *pf + 0.5f;
    int r;
    int *p0;
    int *p1;
    int n;
    *pf = v;
    r = func_00283CF0(v);
    if (*pf >= 1.0f)
        *pf = 0.0f;
    if (D_L09_001B11D8 > 0) {
        p1 = D_L09_002A2658;
        p0 = D_L09_002A27A0;
        n = D_L09_001B11D8;
        do {
            int a2 = *p0;
            if (a2 != 0) {
                int a1;
                a2 += r;
                a1 = *p1;
                if (a2 >= 0x91)
                    a2 -= 0x80;
                *p0 = a2;
                if (a2 >= 0x51)
                    a2 = 0xA0 - a2;
                a1 &= 0xFFFFFF;
                a1 |= a2 << 24;
                *p1 = a1;
            }
            p1++;
            p0++;
        } while (--n);
    }
}
