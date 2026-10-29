/* Complete C near miss; not linked and no matching credit.
 * Default -O2 -G8 -ffunction-sections: 648/624 bytes, USA 0/28.
 * Six checks. Explicit byte mask keeps the measured andi0xFF; the compiler
 * still hoists three requirement-field bases instead of the retail common
 * record base and field displacements. Fine GCSE-edge/force-mem profiles and
 * GCSE suppression tie; strength-reduction control expands the frame.
 * Requirement rows have the measured 0xE0 stride, word 0 enabled, and three
 * 32-bit requirements at 0x98/0x9C/0xA0. No invented table bounds or volatility.
 * Actual 341540 only stores three input words; actual 341610 consumes selected
 * real global menu records. This routine creates no local/undersized buffer.
 * Current RAC1 pause.c reward-menu function supplied family context only;
 * no donor C, raw aliases or assembler fragments were copied.
 * Reopen with new canonical record-base/requirement lifetime evidence.
 */
#include "common.h"

typedef struct {
    int enabled;
    u8 prefix04[0x94];
    int requirement[3];
    u8 suffixA4[0x3C];
} ClassRecord;
extern u8 *D_001A8CFC;
extern int D_001AA438 __attribute__((sda));
extern int D_001AA43C __attribute__((sda));
extern int D_001AA440 __attribute__((sda));
extern u8 D_00139568[];
extern ClassRecord D_00239BA0[];
extern u8 D_001A7AF8[];
extern u8 D_001A7A80[];
extern u8 D_001A7A0A;
extern u8 D_00261750[];
extern u8 D_0025C450[];
extern u8 D_0025C5E8[];
extern u8 D_0025CCF8[];
extern u8 D_002615F8[];
extern u8 D_00261698[];
extern void func_00341540(u8 *, s32, s32, s32);
extern void func_00341610(char *, int);

int func_002CF340(void)
{
    int i;
    if (D_001A8CFC != 0) {
        D_001AA438 = D_001AA43C = D_001AA440 = 1;
        for (i = 0; i < 56; ++i) {
            if (D_00239BA0[D_00139568[i]].enabled != 0 && i != 9 && i != 10) {
                if (D_001A7AF8[i] == 0) {
                    D_001AA438 = 0;
                    D_001AA43C = 0;
                    D_001AA440 = 0;
                } else {
                    int allFirst = D_001AA43C;
                    int allSecond = D_001AA440;
                    int j;
                    for (j = 0; j < 3; ++j) {
                        int needed;
                        switch (j) {
                        case 0:
                            needed = D_00239BA0[D_00139568[i]].requirement[0];
                            break;
                        case 1:
                            needed = D_00239BA0[D_00139568[i]].requirement[1];
                            break;
                        case 2:
                            needed = D_00239BA0[D_00139568[i]].requirement[2];
                            break;
                        default:
                            needed = 0;
                            break;
                        }
                        if (needed != 0) {
                            u8 mask = 1 << (j * 2);
                            if (!(D_001A7A80[i] & mask)) {
                                allFirst = 0;
                                allSecond = 0;
                            }
                        }
                    }
                    D_001AA440 = allSecond;
                    D_001AA43C = allFirst;
                }
            }
        }
        if (D_001A7A0A == 0) {
            *(int *)(D_00261750 + 0x68) = 0x2DC0;
            *(int *)(D_00261750 + 0x70) = 0;
            *(int *)(D_00261750 + 0x40) = 0x2DC0;
            *(int *)(D_00261750 + 0x48) = 0;
            *(int *)(D_00261750 + 0x54) = 0x2DC0;
            *(int *)(D_00261750 + 0x5C) = 0;
        } else {
            *(u8 **)(D_00261750 + 0x70) = D_0025CCF8;
            *(int *)(D_00261750 + 0x40) = 0x3202;
            *(u8 **)(D_00261750 + 0x48) = D_0025C450;
            *(int *)(D_00261750 + 0x54) = 0x320C;
            *(u8 **)(D_00261750 + 0x5C) = D_0025C5E8;
            *(int *)(D_00261750 + 0x68) = 0x323F;
        }
        func_00341540(D_001A8CFC + 0x3BE08, (int)D_002615F8,
                      (int)D_00261698, (int)D_00261750);
        func_00341610((char *)D_001A8CFC + 0x3BE08, 2);
    }
    return 0;
}
