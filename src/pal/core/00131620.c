#include "include_asm.h"
#include "names.h"

/* func_PAL_00131620, sceScfGetLanguage: rac1-decomp's sce_scf_get_language
   (src/core/0012CC90.c). D_PAL_001381D4 is its T10000 language byte, RAC1's
   D_001331D4; it sits between D_00138152 (0x1381D2 here) and r1_D_001331D6. */
extern void GetOsdConfigParam(unsigned int *);

extern int console_is_tool(void);

extern unsigned char g_pal_byte_table[];

/* Reads the console language setting (PAL: also from the tool-kit byte). */
int console_get_region_pal(void) {
    unsigned int config[4];
    unsigned int osd_value;
    int language;

    GetOsdConfigParam(config);
    if (console_is_tool() != 0) {
        language = g_pal_byte_table[0];
    } else {
        GetOsdConfigParam(config);
        osd_value = config[0];
        if (((osd_value >> 13) & 7) == 0) {
            language = (osd_value >> 4) & 1;
        } else {
            language = (osd_value >> 16) & 0x1F;
        }
    }
    return language;
}
