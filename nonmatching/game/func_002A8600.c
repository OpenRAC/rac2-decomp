/* Retained nonmatching reconstruction, 27 October 2026.
 * Profile: -O2 -G0 -ffunction-sections. Candidate: 216 bytes; retail: 232 bytes. USA v1.01, USA v2.00 and PAL each reject all 28 carrying places. Absolute state accesses, the GP cursor and four-argument iterator ABI were measured from retail. The remaining difference is the active/inactive filter and shared return/call control flow. Reopen with evidence for that control-flow shape; do not add volatile or synthetic dependencies.
 */
#include "common.h"
extern int D_001B1B78[] __attribute__((sda));
extern unsigned short *D_001EE5A0[] __attribute__((sda));
extern unsigned short *D_001B1D38 MACRO_ADDR;
extern char *D_001B1D40[] __attribute__((sda));
extern unsigned short D_001B1D3C[] __attribute__((sda));
extern char *D_001B1B5C[] __attribute__((sda));
extern int func_002A86E8(char **, char *, int, int);
int func_002A8600(char **out, int index, int includeInactive, int onlyInactive)
{
    unsigned int inactive;
    int key;
    if (index < 0 || D_001B1B78[0] < index) {
        *out = 0;
        return -1;
    }
    *out = 0;
    D_001B1D40[0] = 0;
    D_001B1D38 = D_001EE5A0[index];
    if (!D_001B1D38)
        return -1;
    key = *D_001B1D38 & 0x7fff;
    D_001B1D3C[0] = key;
    D_001B1D40[0] = D_001B1B5C[0] + key * 256;
    *out = D_001B1D40[0];
    inactive = (unsigned int)(int)((signed char *)D_001B1D40[0])[0x20] >> 31;
    if (!includeInactive) {
        if (!onlyInactive && !inactive)
            return 0;
    } else if (!onlyInactive || inactive)
        return 0;
    return func_002A86E8(out, D_001B1D40[0], includeInactive, onlyInactive);
}
