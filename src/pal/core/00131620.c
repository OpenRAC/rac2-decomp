#include "include_asm.h"

/* func_PAL_00131620, sceScfGetLanguage: rac1-decomp's sce_scf_get_language
   (src/core/0012CC90.c). D_PAL_001381D4 is its T10000 language byte, RAC1's
   D_001331D4; it sits between D_00138152 (0x1381D2 here) and r1_D_001331D6. */
extern void func_0011ACD0(unsigned int *);

extern int func_001315E0(void);

extern unsigned char D_PAL_001381D4[];

int func_PAL_00131620(void) {
    unsigned int buf[4];
    unsigned int v;
    int r;

    func_0011ACD0(buf);
    if (func_001315E0() != 0) {
        r = D_PAL_001381D4[0];
    } else {
        func_0011ACD0(buf);
        v = buf[0];
        if (((v >> 13) & 7) == 0) {
            r = (v >> 4) & 1;
        } else {
            r = (v >> 16) & 0x1F;
        }
    }
    return r;
}
