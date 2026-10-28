/* func_00271FD8 - 448 bytes.  Worker attempt, 27 October 2026 (draft below).

   Semantics decoded (draft.c is a full src/game/00271FD8-g8.c; marker must be
   removed from 0026EA00.c; no cflags line needed for -g8 name).
   Size 444 vs 448. Mismatch: base-address materialisation. Retail: lui
   v1,0x19 / lui a0,0x1B at entry, a1=v1-0x61E0, a3=v1 copy, a2=0x1B53A0+...
   computed in the prologue, and D_00189E20 re-derived (addiu a0,a3,-0x61E0)
   in later blocks; mine builds the bases later and shares differently. Gp
   symbols: D_001B2520 / D_001B251C (sda int). Abs stores use `X[]
   __attribute__((sda))` (lui $at; sw) which matches.
   Tried: one pointer local, direct char[] expressions, sda array for the
   base, separate pointer locals per block. */

#include "include_asm.h"

extern char D_00189E20[];
extern int D_001B1510[] __attribute__((sda));
extern int D_001B1514[] __attribute__((sda));
extern int D_001B53A0[];
extern float D_001B5348[];
extern int D_001A79F0[] __attribute__((sda));
extern int D_001B2520 __attribute__((sda));
extern int D_001B251C __attribute__((sda));

void func_00271FD8(void) {
    char *a = D_00189E20;
    char *b = D_00189E20;
    char *c = D_00189E20;
    char *d = D_00189E20;

    D_001B2520 = 20;
    if ((unsigned)(*(int *)(a + 0x229C) - 17) < 2 || *(int *)(a + 0x2294) == 0x70)
        D_001B1510[0] = 0x34;
    if (*(int *)(b + 0x229C) != 17) {
        if (*(float *)(b + 0x330) < D_001B5348[0])
            D_001B1510[0] = 20;
    }
    if (D_001A79F0[0] == 6) {
        float x = *(float *)(c + 0x80);
        float y = *(float *)(c + 0x84);
        if (x > 485.7f && x < 570.7f && y > 250.0f && y < 334.5f)
            D_001B1510[0] = 0x34;
    }
    D_001B1514[0] = D_001B1510[0];
    D_001B1510[0] |= 0x80;
    D_001B251C = 0xB4;
    if (d[0x1495]) {
        D_001B53A0[0xC0 / 4] = 0x100;
        D_001B251C = 0x1B4;
    } else if (d[0x149B]) {
        D_001B53A0[0xC0 / 4] = 0xB00;
        D_001B251C = 0xBB4;
    } else if (d[0x1496]) {
        D_001B53A0[0xC0 / 4] = 0x300;
        D_001B251C = 0x3B4;
    } else if (d[0x149C]) {
        D_001B53A0[0xC0 / 4] = 0xD00;
        D_001B251C = 0xDB4;
    } else if (d[0x1494]) {
        D_001B53A0[0xC0 / 4] = 0;
    } else {
        D_001B251C = D_001B53A0[0xC0 / 4] | 0xB4;
    }
}
