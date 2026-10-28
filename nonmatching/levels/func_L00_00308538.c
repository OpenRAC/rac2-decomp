/* Complete C near miss; NOT linked and no exact-C credit.
 * Measured source unit: src/levels/shared/L00_00308538-g8.c
 * Game profile: -O2 -G8 -ffunction-sections
 * Compiled/retail bytes: 428/456. US: 0/27; US2: 0/27; PAL: 0/27.
 * Residual and reopening condition: Rectangle/global address construction and mixed GP versus absolute references remain different. The unaligned 16-byte local map copy and repeated selection calls are retained. Reopen with measured global declarations and case-local base lifetimes.
 * Field views describe only measured prefixes, not complete game-object extents.
 */

#include "common.h"
typedef struct { int value[4]; } IndexMap;
typedef struct { int x, y, width, height; } Rect;
extern unsigned char D_001395B8[];
extern char D_L00_001A9A50[];
extern int D_001A79F0 MACRO_ADDR;
extern int D_L00_001A9010;
extern Rect D_L00_001A99F0[];
extern void func_L00_00308408(int x, int y, int width, int height);
extern int func_003005A0(void);

int func_L00_00308538(void)
{
    IndexMap map = *(IndexMap *)D_L00_001A9A50;
    int index;
    int bit;
    if (D_001A79F0 == 2 && D_L00_001A9010 && !(D_001395B8[0x9C] & 1)) {
        func_L00_00308408(D_L00_001A99F0[0].x, D_L00_001A99F0[0].y, D_L00_001A99F0[0].width, D_L00_001A99F0[0].height);
        D_001395B8[0x9C] |= 1;
    } else if (D_001A79F0 == 11 && D_L00_001A9010 && !(D_001395B8[0x9C] & 2)) {
        func_L00_00308408(D_L00_001A99F0[1].x, D_L00_001A99F0[1].y, D_L00_001A99F0[1].width, D_L00_001A99F0[1].height);
        D_001395B8[0x9C] |= 2;
    } else if (D_001A79F0 == 7 && func_003005A0() >= 0) {
        index = func_003005A0();
        bit = map.value[index];
        if ((unsigned int)bit < 8 && !((D_001395B8[0x9C] >> bit) & 1)) {
            D_001395B8[0x9C] |= 1 << bit;
            func_L00_00308408(D_L00_001A99F0[index + 2].x, D_L00_001A99F0[index + 2].y, D_L00_001A99F0[index + 2].width, D_L00_001A99F0[index + 2].height);
        }
    }
    return 0;
}
