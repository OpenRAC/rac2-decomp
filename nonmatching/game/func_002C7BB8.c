/* func_002C7BB8 - 416 bytes, 28 places (src/game/002C7748.c): spawns a
   particle (func_002B9030(0x62)) and fills it like func_002C7970, with a
   colour from the table at D_001F26C8 and a random byte.  Needs -g (the nop
   pair before div.s), so it would join src/game/002C7970.c, whose flags are
   `-O2 -G0 -ffunction-sections -g`, with its marker removed from 002C7748.c.

   Near miss: exact size and instruction stream; only the callee-saved
   registers of three arguments differ.  Retail: $s5 = a7 ($t3),
   $s6 = a4 ($t0), $s7 = a5 ($t1).  Here: $s5 = a4, $s6 = a5, $s7 = a7.

   Tried: the table lookup earlier or after the random byte, the table base
   in a local (420 bytes), the bounds byte and a4's store moved. */

#include "include_asm.h"
#include "common.h"

extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern int func_002A7820(int, int);
extern unsigned char *D_001F26C8;
extern void func_002C7D58(char *a0);

char *func_002C7BB8(void *a0, float *a1, int a2, int a3, int a4, int a5, int a6, int a7, float f0, float f1, float f2)
{
    char *p = func_002B9030(0x62);
    char *s;

    if (p != 0) {
        qcopy(p + 0x10, a0);
        *(int *)(p + 4) = (a5 << 24) | a3;
        p[9] = func_00283CF0(4.0f) + 0x40;
        p[1] = 0;
        *(float *)(p + 0xC) = f0;
        p[3] = 0x48;
        p[8] = func_002A7820(0, a4 * 100) % 255;
        p[2] = D_001F26C8[a7];
        *(short *)(p + 0xA) = a2;
        s = p + 0x20;
        *(float *)s = a1[0];
        *(float *)(s + 4) = a1[1];
        *(float *)(s + 8) = a1[2];
        *(float *)(s + 0xC) = f2;
        s[0x15] = a4;
        *(float *)(s + 0x10) = (f1 - f0) / func_00283CE0(a2);
        *(int *)(s + 0x18) = 60;
        s[0x14] = (a6 - a5) / a2;
        *(void **)(s + 0x1C) = (void *)func_002C7D58;
    }
    return p;
}
