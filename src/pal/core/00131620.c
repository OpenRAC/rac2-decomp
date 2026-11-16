#include "include_asm.h"
#include "names.h"

/* func_PAL_00131620, sceScfGetLanguage: rac1-decomp's sce_scf_get_language
   (src/core/0012CC90.c). D_PAL_001381D4 is its T10000 language byte, RAC1's
   D_001331D4; it sits between D_00138152 (0x1381D2 here) and r1_D_001331D6. */
extern void GetOsdConfigParam(unsigned int *);

extern int console_is_tool(void);

extern unsigned char g_pal_byte_table[];

int func_PAL_00131620(void) {
    unsigned int buf[4];
    unsigned int v;
    int r;

    GetOsdConfigParam(buf);
    if (console_is_tool() != 0) {
        r = g_pal_byte_table[0];
    } else {
        GetOsdConfigParam(buf);
        v = buf[0];
        if (((v >> 13) & 7) == 0) {
            r = (v >> 4) & 1;
        } else {
            r = (v >> 16) & 0x1F;
        }
    }
    return r;
}
