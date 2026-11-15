#include "include_asm.h"
#include "names.h"

extern char *D_L00_001B1E9C;
extern char *D_L00_001B1EA4;
extern int D_L00_001AFD7C __attribute__((sda));
extern char *D_L00_0023DBA0[];
extern int D_L00_0023DCA0[];
extern char D_L00_001AFD80[];
extern int D_001A79F0;
extern void func_0026FEB8(const char *,...);

/* Collects up to 64 mobys of a fixed set of classes into a table, saving each one's value at +0x98.
   Reports an error if the table fills up. */
void func_L00_003B9170(void)
{
    char *moby;
    D_L00_001AFD7C=0;
    for (moby=D_L00_001B1E9C; moby<D_L00_001B1EA4; moby+=0x100) {
        short classId=*(short *)(moby+0xaa);
        if (classId==0x1146 || classId==0x1185 || classId==0x119b || classId==0x11a4 || classId==0x1204 || classId==0x11fc || classId==0x120c || classId==0x1135 || classId==0x1148 || classId==0x11fc) {
            D_L00_0023DBA0[D_L00_001AFD7C]=moby;
            D_L00_0023DCA0[D_L00_001AFD7C]=*(int *)(moby+0x98);
            D_L00_001AFD7C++;
            if (D_L00_001AFD7C>=64) {
                STUB_printf(D_L00_001AFD80,64,gCurrentMapIndex);
                return;
            }
        }
    }
}
